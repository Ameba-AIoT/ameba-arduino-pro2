/*

Compile:

windows:
g++.exe -o postbuild_windows.exe postbuild.cpp -static
strip postbuild_windows.exe
### g++.exe -o postbuild_windows.exe postbuild.cpp -static ../../Ameba_icon/ico-out.o -static
### mingw32-g++.exe -o postbuild_windows.exe postbuild.cpp -static

If you encounter any issue while generating exe with icon, you may refer to: https://www.rodneybeede.com/programming/compiling_a_c___windows_executable_with_a_custom_icon.html

linux:
g++ -o postbuild_linux postbuild.cpp -static
strip postbuild_linux

macos:
g++ -arch x86_64 -arch arm64 -o postbuild_macos postbuild.cpp
strip postbuild_macos

*/

#include <iostream>
#include <sstream>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <unistd.h>
#include <vector>

using namespace std;

string common_nn_models_path;
string ota_mode_check_name, fcs_mode_check_name;

string isp_camera_option, isp_sensor_set_json_name, isp_sys_file_folder_name, fc_data_name, voe_name, iq_name, sensor_name, isp_fw_dummy_name, isp_iq_json_name;
string isp_file_name_buf[100];

string partitiontable_json_name, partition_bin_name;

int isp_selection_check = 0;
int nn_model_selection_check = 0;
int ota_mode_selection_check = 0;
int fcs_mode_selection_check = 0;

std::vector<std::string> model_names;
std::vector<std::string> model_header;
std::vector<std::string> isp_status;
bool is_model_section = false;
bool is_header_section = false;
bool is_isp_section = false;

#if defined(__WIN32__) // MINGW64
void replaceAll( string& source, const string& from, const string& to ) {
    string newString;
    newString.reserve(source.length()); //avoids a few memory allocations

    string::size_type lastPos = 0;
    string::size_type findPos;

    while (string::npos != (findPos = source.find(from, lastPos))) {
        newString.append( source, lastPos, (findPos - lastPos));
        newString += to;
        lastPos = findPos + from.length();
    }

    // Care for the rest after last occurrence
    newString += source.substr(lastPos);

    source.swap(newString);
}
#endif

void readtxt(int mode_isp_ino) {
#if defined(__WIN32__) // MINGW64
    string str;
    int str_count = 0;
#elif defined(__linux__) || defined(__APPLE__) // ubuntu 32 bits and OS X 64bits
    ifstream myFile_Handler;
    string myLine;
    int str_count = 0;
#else
    #error compiler is not supported!
#endif

    string str_temp = "misc/video_img//sensor_bin_name.txt";
    str_temp.insert(15, isp_camera_option);

    if (mode_isp_ino == 0) {
#if defined(__WIN32__) // MINGW64
        ifstream file(str_temp);
        while (std::getline(file, str)) {
            isp_file_name_buf[str_count] = str;
            str_count++;
            //if (str_count == line_number) {
            //    break;
            //}
        }
#elif defined(__linux__) || defined(__APPLE__) // ubuntu 32 bits and OS X 64bits
        myFile_Handler.open(str_temp);

        if(myFile_Handler.is_open()) {
            while (getline(myFile_Handler, myLine)) {
                //cout << myLine << endl;
                isp_file_name_buf[str_count] = myLine;
                str_count++;
                //if (str_count == line_number) {
                //    break;
                //} else {
                isp_file_name_buf[str_count - 1].erase(isp_file_name_buf[str_count-1].size() - 1);
                //}
            }
            myFile_Handler.close();
        } else {
            cout << "Unable to open the file!" << endl;
        }
#else
    #error compiler is not supported!
#endif

    fc_data_name = isp_file_name_buf[3];
    voe_name = isp_file_name_buf[1];
    iq_name = isp_file_name_buf[4];
    sensor_name = isp_file_name_buf[5];
    isp_fw_dummy_name = isp_file_name_buf[2];
    isp_sensor_set_json_name = "amebapro2_sensor_set.json";
    isp_iq_json_name = "amebapro2_isp_iq.json";
    isp_sys_file_folder_name = isp_camera_option;
//    isp_sys_file_folder_name = isp_file_name_buf[0];

    } else if (mode_isp_ino == 1) {
#if defined(__WIN32__) // MINGW64
    
    ifstream file("misc/ino_validation.txt");
    while (std::getline(file, str)) {
        // Skip empty lines or separators
        if (str.empty() || str == "----------------------------------") {
            continue;
        }

        if (str.find("Current ino contains model(s):") != std::string::npos) {
            is_model_section = true;
            is_header_section = false; // Reset type section flag
            is_isp_section = false;
            continue;
        }
        if (str.find("Current NN header file(s):") != std::string::npos) {
            is_model_section = false;
            is_header_section = true;
            is_isp_section = false;
            continue;
        }
        if (str.find("Current ino video status:") != std::string::npos) {
            is_model_section = false;
            is_header_section = false;
            is_isp_section = true;
            continue;
        }

        // Extract model names
        if (is_model_section) {
            model_names.push_back(str); // Add model name to the vector
        }

        // Extract model types (Default/Customized)
        if (is_header_section) {
            model_header.push_back(str); // Add model type to the vector
        }

        if (is_isp_section) {
            isp_status.push_back(str); // Add model type to the vector
        }
    }

#elif defined(__linux__) || defined(__APPLE__) // ubuntu 32 bits and OS X 64bits
        myFile_Handler.open("misc/ino_validation.txt");

        if(myFile_Handler.is_open()) {
            while (getline(myFile_Handler, myLine)) {
                // ino_name_buf[str_count] = myLine;
                // str_count++;
                // ino_name_buf[str_count-1].erase(ino_name_buf[str_count-1].size() - 1);

                // Skip empty lines or separators
                if (myLine.empty() || myLine == "----------------------------------") {
                    continue;
                }

                if (myLine.find("Current ino contains model(s):") != std::string::npos) {
                    is_model_section = true;
                    is_header_section = false; // Reset type section flag
                    is_isp_section = false;
                    continue;
                }
                if (myLine.find("Current NN header file(s):") != std::string::npos) {
                    is_model_section = false;
                    is_header_section = true;
                    is_isp_section = false;
                    continue;
                }
                if (myLine.find("Current ino video status:") != std::string::npos) {
                    is_model_section = false;
                    is_header_section = false;
                    is_isp_section = true;
                    continue;
                }

                // Extract model names
                if (is_model_section) {
                    model_names.push_back(myLine); // Add model name to the vector
                }

                // Extract model types (Default/Customized)
                if (is_header_section) {
                    model_header.push_back(myLine); // Add model type to the vector
                }

                if (is_isp_section) {
                    isp_status.push_back(myLine); // Add model type to the vector
                }
            }
            myFile_Handler.close();
        } else {
            cout << "Unable to open the file!" << endl;
        }
#else
    #error compiler is not supported!
#endif
    }
}

bool isp_notNA = false;
void isp_bin_check(void) {
    for (const auto& status : isp_status) {
        if (status != "NA") {
            isp_notNA = true;
        }
    }
    if (isp_notNA) {
        isp_selection_check = 1;
    }
}

bool headerfile_notNA = false;
bool model_notNA = false;
void nn_bin_check(void) {
    for (const auto& header : model_header) {
        if (header != "NA") {
            headerfile_notNA = true;
        }
    }
    for (const auto& model : model_names) {
        if (model != "NA") {
            model_notNA = true;
        }
    }

    if (headerfile_notNA && model_notNA) {
        nn_model_selection_check = 1;
    }
}

void ota_mode_check(string ota_mode_check_name) {
    if (ota_mode_check_name == "Enable") {
        ota_mode_selection_check = 1;
    }
}

void fcs_mode_check(string fcs_mode_check_name) {
    if (fcs_mode_check_name == "Enable") {
        fcs_mode_selection_check = 1;
    }
}

int main(int argc, char *argv[]) {
    int ret = 0;
    stringstream cmdss;
    string cmd, line, msg;
    vector<string> lines;
    vector<string>::iterator iter;
    string path_tool;
    string path_arm_none_eabi_gcc;
    string path_symbol_black_list;
    string bksym;
    ifstream fin;
    ofstream fout;

    bool has_xip = false;
    bool has_psram = false;

    size_t pos;

    // 0. change work folder
    chdir(argv[1]);

#if defined(__WIN32__) // MINGW64
    common_nn_models_path = argv[6];
    common_nn_models_path = common_nn_models_path + "\\variants\\common_nn_models";
#elif defined(__linux__) || defined(__APPLE__) // ubuntu 32 bits and OS X 64bits
    common_nn_models_path = argv[6];
    common_nn_models_path = common_nn_models_path + "/variants/common_nn_models";
#else
    #error compiler is not supported!
#endif

    // 1. remove and copy files
#if defined(__WIN32__) // MINGW64
    cmd = "if exist application.ntz del application.ntz";
    cout << cmd << endl;
    system(cmd.c_str());

    cmd = "if exist *.json del *.json";
    cout << cmd << endl;
    system(cmd.c_str());

    cmd = "if exist *.axf del *.axf";
    cout << cmd << endl;
    system(cmd.c_str());

    cmd = "if exist *.map del *.map";
    cout << cmd << endl;
    system(cmd.c_str());

    cmd = "if exist *.asm del *.asm";
    cout << cmd << endl;
    system(cmd.c_str());

    cmd = "if exist *.bin del *.bin";
    cout << cmd << endl;
    system(cmd.c_str());

    cmd = "if exist *.nb del *.nb";
    cout << cmd << endl;
    system(cmd.c_str());

    cmdss.clear();
    cmdss << "xcopy /y " << "misc\\sys_img" << " .\\";
    getline(cmdss, cmd);
    cout << cmd << endl;
    system(cmd.c_str());
#elif defined(__linux__) || defined(__APPLE__) // ubuntu 32 bits and OS X 64bits
    cmd = "rm -f application.ntz";
    cout << cmd << endl;
    system(cmd.c_str());

    cmd = "rm -f *.json";
    cout << cmd << endl;
    system(cmd.c_str());

    cmd = "rm -f *.axf";
    cout << cmd << endl;
    system(cmd.c_str());

    cmd = "rm -f *.map";
    cout << cmd << endl;
    system(cmd.c_str());

    cmd = "rm -f *.asm";
    cout << cmd << endl;
    system(cmd.c_str());

    cmd = "rm -f *.bin";
    cout << cmd << endl;
    system(cmd.c_str());

    cmd = "rm -f *.nb";
    cout << cmd << endl;
    system(cmd.c_str());

    cmd = "cp misc/sys_img/* ./";
    cout << cmd << endl;
    system(cmd.c_str());
#else
    #error compiler is not supported!
#endif
    isp_camera_option = argv[7];
    readtxt(0);
    readtxt(1);
    isp_bin_check();
    nn_bin_check();

#if defined(__WIN32__) // MINGW64
    string string_temp_1 = "copy misc\\video_img\\";
    string string_temp_2 = " .\\";
    string string_temp_3 = "copy misc\\nn_img\\";
    string string_temp_4 = "xcopy /y ";
    string string_temp_5 = "";
    string string_temp_6 = "copy image_tool\\";
    string string_temp_7 = "misc\\video_img\\";
    string string_temp_8 = "\\";
#elif defined(__linux__) || defined(__APPLE__) // ubuntu 32 bits and OS X 64bits
    string string_temp_1 = "cp misc/video_img/";
    string string_temp_2 = " ./";
    string string_temp_3 = "cp misc/nn_img/";
    string string_temp_4 = "cp -r ";
    string string_temp_5 = "/*";
    string string_temp_6 = "cp image_tool/";
    string string_temp_7 = "misc/video_img/";
    string string_temp_8 = "/";
#else
    #error compiler is not supported!
#endif

    cmdss.clear();
    cmdss << string_temp_6 << "flash_loader_nor.bin" << string_temp_2;
    getline(cmdss, cmd);
    cout << cmd << endl;
    system(cmd.c_str());

    cmdss.clear();
    cmdss << string_temp_4 << string_temp_7 << isp_sys_file_folder_name << string_temp_5 << string_temp_2;
    getline(cmdss, cmd);
    cout << cmd << endl;
    system(cmd.c_str());

    if (isp_selection_check == 1) {

        fcs_mode_check_name = argv[9];
        fcs_mode_check(fcs_mode_check_name);

        cmdss.clear();
        cmdss << string_temp_1 << voe_name << string_temp_2;
        getline(cmdss, cmd);
        cout << cmd << endl;
        system(cmd.c_str());

        cmdss.clear();
        cmdss << string_temp_1 << "fcs_data_dummy.bin" << string_temp_2;
        getline(cmdss, cmd);
        cout << cmd << endl;
        system(cmd.c_str());

        cmdss.clear();
        cmdss << string_temp_1 << "iq.bin" << string_temp_2;
        getline(cmdss, cmd);
        cout << cmd << endl;
        system(cmd.c_str());

        cmdss.clear();
        cmdss << string_temp_1 << "sensor.bin" << string_temp_2;
        getline(cmdss, cmd);
        cout << cmd << endl;
        system(cmd.c_str());

        if (fcs_mode_selection_check != 1) {
            cmdss.clear();
            cmdss << string_temp_1 << isp_sys_file_folder_name << string_temp_8 << "non_fcs" << string_temp_8 << isp_iq_json_name << string_temp_2;
            getline(cmdss, cmd);
            cout << cmd << endl;
            system(cmd.c_str());
        } else {
            cmdss.clear();
            cmdss << string_temp_1 << isp_sys_file_folder_name << string_temp_8 << isp_iq_json_name << string_temp_2;
            getline(cmdss, cmd);
            cout << cmd << endl;
            system(cmd.c_str());
        }

        if (fc_data_name != "fcs_data_dummy.bin") {
            cmdss.clear();
            cmdss << string_temp_1 << fc_data_name << string_temp_2;
            getline(cmdss, cmd);
            cout << cmd << endl;
            system(cmd.c_str());
        }

        if (iq_name != "iq.bin") {
            cmdss.clear();
            cmdss << string_temp_1 << iq_name << string_temp_2;
            getline(cmdss, cmd);
            cout << cmd << endl;
            system(cmd.c_str());
        }

        if (sensor_name != "sensor.bin") {
            cmdss.clear();
            cmdss << string_temp_1 << sensor_name << string_temp_2;
            getline(cmdss, cmd);
            cout << cmd << endl;
            system(cmd.c_str());
        }
    } else {
        cmdss.clear();
        cmdss << string_temp_1 << isp_fw_dummy_name << string_temp_2;
        getline(cmdss, cmd);
        cout << cmd << endl;
        system(cmd.c_str());
    }

    if (nn_model_selection_check == 1) {
        cmdss.clear();
        cmdss << string_temp_3 << "amebapro2_nn_model.json" << string_temp_2;
        getline(cmdss, cmd);
        cout << cmd << endl;
        system(cmd.c_str());

        cmdss.clear();
        cmdss << string_temp_4 << "\"" << common_nn_models_path << "\"" << string_temp_5 << string_temp_2;
        getline(cmdss, cmd);
        cout << cmd << endl;
        system(cmd.c_str());
    }

    // 2. copy elf application.ntz to current folder
    cmdss.clear();
    cmdss << string_temp_4 << argv[2] << string_temp_2;
    getline(cmdss, cmd);
    cout << cmd << endl;
    system(cmd.c_str());

    cmdss.clear();
    cmdss << string_temp_4 << argv[5] << string_temp_2;
    getline(cmdss, cmd);
    cout << cmd << endl;
    system(cmd.c_str());

    // 3. generate information files
    path_arm_none_eabi_gcc.assign(argv[3]);
#if defined(__WIN32__) // MINGW64
    replaceAll(path_arm_none_eabi_gcc, "/", "\\");

    cmdss.clear();
    cmdss << "\"" << path_arm_none_eabi_gcc << "arm-none-eabi-nm.exe\" application.ntz | sort > application.ntz.nm.map";
    getline(cmdss, cmd);
    cout << cmd << endl;
    system(cmd.c_str());

//    fin.open("application.ntz.nm.map");
//    while (getline(fin, line)) {
//        lines.push_back(line);
//    }
//    fin.close();

    cmdss.clear();
    cmdss << "\"" <<path_arm_none_eabi_gcc << "arm-none-eabi-objdump.exe\" -d application.ntz > application.ntz.asm";
#elif defined(__linux__) || defined(__APPLE__) // ubuntu 32 bits and OS X 64bits
    cmdss.clear();
    cmdss << path_arm_none_eabi_gcc << "arm-none-eabi-nm application.ntz | sort > application.ntz.nm.map";
    getline(cmdss, cmd);
    cout << cmd << endl;
    system(cmd.c_str());

    cmdss.clear();
    cmdss << path_arm_none_eabi_gcc << "arm-none-eabi-objdump -d application.ntz > application.ntz.asm";
#else
    #error compiler is not supported!
#endif
    getline(cmdss, cmd);
    cout << cmd << endl;
    system(cmd.c_str());

    // 3.1 check if any forbidden symbols
    path_symbol_black_list.assign(argv[4]);
#if defined(__WIN32__) // MINGW64
    replaceAll(path_symbol_black_list, "/", "\\");
#endif
    fin.open(path_symbol_black_list.c_str(), ifstream::in);
    cout << path_symbol_black_list << endl;
    ret = 0;
    if (fin) {
        while (!fin.eof() && ret == 0) {
            fin >> bksym;
            getline(fin, msg);

            // check if this symbole appears in the map file
            for (iter = lines.begin(); iter != lines.end(); ++iter) {
                if ((iter->find(bksym)) != string::npos) {
                    cerr << "ERROR: " << msg << endl;
                    ret = -1;
                    break;
                }
            }
        }
    }
    fin.close();

    if (ret != 0) {
        return -1;
    }

    // 4. generate .bin
    // 4.1 firmware.bin firmware_isp_iq.bin nn_model.bin
#if defined(__WIN32__) // MINGW64
    cmd = "copy application.ntz application.ntz.axf";
    cout << cmd << endl;
    system(cmd.c_str());

    //cmdss.clear();
    //cmdss << "\"" <<path_arm_none_eabi_gcc << "arm-none-eabi-objcopy.exe\" -j .bluetooth_trace.text -Obinary application.ntz.axf APP.trace";
    //getline(cmdss, cmd);
    //cout << cmd << endl;
    //system(cmd.c_str());

    //cmdss.clear();
    //cmdss << "\"" << path_arm_none_eabi_gcc << "arm-none-eabi-objcopy.exe\" -R .bluetooth_trace.text application.ntz.axf -w";
    //getline(cmdss, cmd);
    //cout << cmd << endl;
    //system(cmd.c_str());
#elif defined(__linux__) || defined(__APPLE__) // ubuntu 32 bits and OS X 64bits
    cmd = "cp application.ntz application.ntz.axf";
    cout << cmd << endl;
    system(cmd.c_str());

    //cmdss.clear();
    //cmdss << path_arm_none_eabi_gcc << "arm-none-eabi-objcopy -j .bluetooth_trace.text -Obinary application.ntz.axf APP.trace";
    //getline(cmdss, cmd);
    //cout << cmd << endl;
    //system(cmd.c_str());

    //cmdss.clear();
    //cmdss << path_arm_none_eabi_gcc << "arm-none-eabi-objcopy -R .bluetooth_trace.text application.ntz.axf";
    //getline(cmdss, cmd);
    //cout << cmd << endl;
    //system(cmd.c_str());
#else
    #error compiler is not supported!
#endif

#if defined(__WIN32__) // MINGW64
    string_temp_1 = ".\\misc\\elf2bin.win.exe ";
#elif defined(__linux__) // ubuntu 32 bits
    string_temp_1 = "./misc/elf2bin.linux ";
#elif defined(__APPLE__) // OS X 64bits
    string_temp_1 = "./misc/elf2bin.darwin ";
#else
    #error compiler is not supported!
#endif
    if (isp_selection_check == 1) {
        cmdss.clear();
        cmdss << string_temp_1 << "convert " << isp_sensor_set_json_name << " ISP_SENSOR_SETS isp_iq.bin";
        getline(cmdss, cmd);
        cout << cmd << endl;
        system(cmd.c_str());

        cmdss.clear();
        cmdss << string_temp_1 << "convert amebapro2_isp_iq.json FIRMWARE firmware_isp_iq.bin";
        getline(cmdss, cmd);
        cout << cmd << endl;
        system(cmd.c_str());

        cmdss.clear();
        cmdss << string_temp_1 << "convert amebapro2_firmware.json FIRMWARE firmware.bin";
        getline(cmdss, cmd);
        cout << cmd << endl;
        system(cmd.c_str());
    } else {
        cmdss.clear();
        cmdss << string_temp_1 << "convert amebapro2_firmware_NA_cam.json FIRMWARE firmware.bin";
        getline(cmdss, cmd);
        cout << cmd << endl;
        system(cmd.c_str());
    }

    if (nn_model_selection_check == 1) {
        cmdss.clear();
        cmdss << string_temp_1 << "convert amebapro2_fwfs_nn_models.json FWFS fwfs_nn_model.bin";
        getline(cmdss, cmd);
        cout << cmd << endl;
        system(cmd.c_str());

        cmdss.clear();
        cmdss << string_temp_1 << "convert amebapro2_nn_model.json FIRMWARE nn_model.bin";
        getline(cmdss, cmd);
        cout << cmd << endl;
        system(cmd.c_str());
    }

    ota_mode_check_name = argv[8];
    ota_mode_check(ota_mode_check_name);

    if (ota_mode_selection_check == 1){
        partitiontable_json_name = "amebapro2_partitiontable_OTA.json";
        partition_bin_name = "partition_ota.bin";
    } else {
        partitiontable_json_name = "amebapro2_partitiontable.json";
        partition_bin_name = "partition.bin";
    }

    cmdss.clear();
    cmdss << string_temp_1 << "combine "<< partitiontable_json_name << " system_files.bin PT_PT=" << partition_bin_name << ",CER_TBL=certable.bin,KEY_CER1=certificate.bin,PT_BL_PRI=boot.bin,PT_FCSDATA=boot_fcs.bin";
    getline(cmdss, cmd);
    cout << cmd << endl;
    system(cmd.c_str());

    if (nn_model_selection_check == 1) {
        cmdss.clear();
        cmdss << string_temp_1 << "combine "<< partitiontable_json_name << " flash_ntz.bin PT_PT=" << partition_bin_name << ",CER_TBL=certable.bin,KEY_CER1=certificate.bin,PT_BL_PRI=boot.bin,PT_FW1=firmware.bin,PT_NN_MDL=nn_model.bin,PT_ISP_IQ=firmware_isp_iq.bin,PT_FCSDATA=boot_fcs.bin";
        getline(cmdss, cmd);
        cout << cmd << endl;
        system(cmd.c_str());
    } else {
        cmdss.clear();
        cmdss << string_temp_1 << "combine "<< partitiontable_json_name << " flash_ntz.bin PT_PT=" << partition_bin_name << ",CER_TBL=certable.bin,KEY_CER1=certificate.bin,PT_BL_PRI=boot.bin,PT_FW1=firmware.bin,PT_ISP_IQ=firmware_isp_iq.bin,PT_FCSDATA=boot_fcs.bin";
        getline(cmdss, cmd);
        cout << cmd << endl;
        system(cmd.c_str());
    }

    // 5. OTA add checksum
#if defined(__WIN32__) // MINGW64
    string_temp_1 = ".\\misc\\cmake.win.exe ";
    string_temp_2 = ".\\misc\\checksum.exe ";
    string_temp_3 = ".\\";
#elif defined(__linux__) // ubuntu 32 bits
    string_temp_1 = "./misc/cmake.linux ";
    string_temp_2 = "./misc/checksum.linux ";
    string_temp_3 = "./";
#elif defined(__APPLE__) // OS X 64bits
    #if defined(__arm__) // apple silicon
    string_temp_1 = "./misc/cmake.darwin ";
    string_temp_2 = "./misc/checksum.arm.darwin ";
    string_temp_3 = "./";
    #else
    string_temp_1 = "./misc/cmake.darwin ";
    string_temp_2 = "./misc/checksum.darwin ";
    string_temp_3 = "./";
    #endif
#else
    #error compiler is not supported!
#endif

    if (ota_mode_selection_check == 1) {
        cmdss.clear();
        cmdss << string_temp_1 << " -E copy "<< string_temp_3 << "firmware.bin "<< string_temp_3 << "ota.bin";
        getline(cmdss, cmd);
        cout << cmd << endl;
        system(cmd.c_str());

        cmdss.clear();
        cmdss << string_temp_2 << string_temp_3 << "ota.bin";
        getline(cmdss, cmd);
        cout << cmd << endl;
        system(cmd.c_str());

        cmdss.clear();
        cmdss << string_temp_1 << " -E copy "<< string_temp_3 << "firmware_isp_iq.bin "<< string_temp_3 << "isp_iq_ota.bin";
        getline(cmdss, cmd);
        cout << cmd << endl;
        system(cmd.c_str());

        cmdss.clear();
        cmdss << string_temp_2 << string_temp_3 << "isp_iq_ota.bin";
        getline(cmdss, cmd);
        cout << cmd << endl;
        system(cmd.c_str());

        cmdss.clear();
        cmdss << string_temp_1 << " -E copy "<< string_temp_3 << "boot.bin "<< string_temp_3 << "boot_ota.bin";
        getline(cmdss, cmd);
        cout << cmd << endl;
        system(cmd.c_str());

        cmdss.clear();
        cmdss << string_temp_2 << string_temp_3 << "boot_ota.bin";
        getline(cmdss, cmd);
        cout << cmd << endl;
        system(cmd.c_str());

        cmdss.clear();
        cmdss << string_temp_1 << " -E copy "<< string_temp_3 << "boot.bin "<< string_temp_3 << "boot_ota.bin";
        getline(cmdss, cmd);
        cout << cmd << endl;
        system(cmd.c_str());

        cmdss.clear();
        cmdss << string_temp_2 << string_temp_3 << "boot_ota.bin";
        getline(cmdss, cmd);
        cout << cmd << endl;
        system(cmd.c_str());

        cmdss.clear();
        cmdss << string_temp_1 << " -E copy "<< string_temp_3 << "certificate.bin "<< string_temp_3 << "certificate_ota.bin";
        getline(cmdss, cmd);
        cout << cmd << endl;
        system(cmd.c_str());

        cmdss.clear();
        cmdss << string_temp_2 << string_temp_3 << "certificate_ota.bin";
        getline(cmdss, cmd);
        cout << cmd << endl;
        system(cmd.c_str());
    }

    return 0;
}
