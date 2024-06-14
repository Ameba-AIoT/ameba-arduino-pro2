/*

Compile:

windows:
g++.exe -o postbuild_windows.exe postbuild.cpp -static
strip postbuild_windows.exe
### g++.exe -o postbuild_windows.exe postbuild.cpp -static ico-out.o -static
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

string isp_camera_option, isp_sensor_set_json_name, isp_sys_file_folder_name, fc_data_name, voe_name, iq_name, sensor_name, isp_fw_dummy_name;
string isp_file_name_buf[100];

string nn_model_yolotiny_name, nn_model_srcfd_name, nn_model_mobilefacenet_name, nn_model_yamnet_name, nn_model_imgclass_name, nn_header_name1, nn_header_name2, nn_header_name3, nn_header_name4, nn_header_name5, isp_bin_check_name;
string ino_name_buf[100];

int isp_selection_check = 0;
int nn_model_selection_check = 0;

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

    if (mode_isp_ino == 0) {
#if defined(__WIN32__) // MINGW64
        ifstream file("misc/video_img/sensor_bin_name.txt");
        while (std::getline(file, str)) {
            isp_file_name_buf[str_count] = str;
            str_count++;
            //if (str_count == line_number) {
            //    break;
            //}
        }
#elif defined(__linux__) || defined(__APPLE__) // ubuntu 32 bits and OS X 64bits
        myFile_Handler.open("misc/video_img/sensor_bin_name.txt");

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

        if (isp_camera_option == "JXF37") {
            fc_data_name = isp_file_name_buf[0];
            voe_name = isp_file_name_buf[1];
            iq_name = isp_file_name_buf[2];
            sensor_name = isp_file_name_buf[3];
            isp_fw_dummy_name = isp_file_name_buf[4];
            isp_sensor_set_json_name = "amebapro2_sensor_set0.json";
            isp_sys_file_folder_name = "SENSOR_F37";
        } else if (isp_camera_option == "GC5035") {
            fc_data_name = isp_file_name_buf[0 + 6];
            voe_name = isp_file_name_buf[1 + 6];
            iq_name = isp_file_name_buf[2 + 6];
            sensor_name = isp_file_name_buf[3 + 6];
            isp_fw_dummy_name = isp_file_name_buf[4 + 6];
            isp_sensor_set_json_name = "amebapro2_sensor_set1.json";
            isp_sys_file_folder_name = "SENSOR_GC5035";
        } else {
            cout << "Unable to find correct camera option!" << endl;
        }

    } else if (mode_isp_ino == 1) {
#if defined(__WIN32__) // MINGW64
        ifstream file("misc/ino_validation.txt");
        while (std::getline(file, str)) {
            ino_name_buf[str_count] = str;
            str_count++;
            //if (str_count == line_number) {
            //    break;
            //}
        }
#elif defined(__linux__) || defined(__APPLE__) // ubuntu 32 bits and OS X 64bits
        myFile_Handler.open("misc/ino_validation.txt");

        if(myFile_Handler.is_open()) {
            while (getline(myFile_Handler, myLine)) {
                ino_name_buf[str_count] = myLine;
                str_count++;
                ino_name_buf[str_count-1].erase(ino_name_buf[str_count-1].size() - 1);
            }
            myFile_Handler.close();
        } else {
            cout << "Unable to open the file!" << endl;
        }
#else
    #error compiler is not supported!
#endif
        nn_model_yolotiny_name = ino_name_buf[2];
        nn_model_srcfd_name = ino_name_buf[3];
        nn_model_mobilefacenet_name = ino_name_buf[4];
        nn_model_yamnet_name = ino_name_buf[5];
        nn_model_imgclass_name = ino_name_buf[6];
        nn_header_name1 = ino_name_buf[16];
        nn_header_name2 = ino_name_buf[17];
        nn_header_name3 = ino_name_buf[18];
        nn_header_name4 = ino_name_buf[19];
        nn_header_name5 = ino_name_buf[20];
        isp_bin_check_name = ino_name_buf[23];
    }
}

void isp_bin_check(string isp_bin_check_name) {
    if (isp_bin_check_name != "NA") {
        isp_selection_check = 1;
    }
}

void nn_bin_check(string nn_model_yolotiny_name, string nn_model_srcfd_name, string nn_model_mobilefacenet_name, string nn_model_yamnet_name, string nn_model_imgclass_name, string nn_header_name1, string nn_header_name2, string nn_header_name3, string nn_header_name4, string nn_header_name5) {
    if ((nn_model_yolotiny_name != "NA") || (nn_model_srcfd_name != "NA") || (nn_model_mobilefacenet_name != "NA") || (nn_model_yamnet_name != "NA") || (nn_model_imgclass_name != "NA")) {
        if ((nn_header_name1 != "NA") || (nn_header_name2 != "NA") || (nn_header_name3 != "NA") || (nn_header_name4 != "NA") || (nn_header_name5 != "NA")) {
            nn_model_selection_check = 1;
        }
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

    // 1. remove previous files
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
    isp_bin_check(isp_bin_check_name);
    nn_bin_check(nn_model_yolotiny_name, nn_model_srcfd_name, nn_model_mobilefacenet_name, nn_model_yamnet_name, nn_model_imgclass_name, nn_header_name1, nn_header_name2, nn_header_name3, nn_header_name4, nn_header_name5);

#if defined(__WIN32__) // MINGW64
    string string_temp_1 = "copy misc\\video_img\\";
    string string_temp_2 = " .\\";
    string string_temp_3 = "copy misc\\nn_img\\";
    string string_temp_4 = "xcopy /y ";
    string string_temp_5 = "";
    string string_temp_6 = "copy image_tool\\";
    string string_temp_7 = "misc\\video_img\\";
#elif defined(__linux__) || defined(__APPLE__) // ubuntu 32 bits and OS X 64bits
    string string_temp_1 = "cp misc/video_img/";
    string string_temp_2 = " ./";
    string string_temp_3 = "cp misc/nn_img/";
    string string_temp_4 = "cp ";
    string string_temp_5 = "/*";
    string string_temp_6 = "cp image_tool/";
    string string_temp_7 = "misc/video_img/";
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
        cmdss.clear();
        cmdss << string_temp_1 << voe_name << string_temp_2;
        getline(cmdss, cmd);
        cout << cmd << endl;
        system(cmd.c_str());

        cmdss.clear();
        cmdss << string_temp_1 << "amebapro2_isp_iq.json" << string_temp_2;
        getline(cmdss, cmd);
        cout << cmd << endl;
        system(cmd.c_str());

        cmdss.clear();
        cmdss << string_temp_1 << isp_sensor_set_json_name << string_temp_2;
        getline(cmdss, cmd);
        cout << cmd << endl;
        system(cmd.c_str());

        cmdss.clear();
        cmdss << string_temp_1 << fc_data_name << string_temp_2;
        getline(cmdss, cmd);
        cout << cmd << endl;
        system(cmd.c_str());

        cmdss.clear();
        cmdss << string_temp_1 << iq_name << string_temp_2;
        getline(cmdss, cmd);
        cout << cmd << endl;
        system(cmd.c_str());

        cmdss.clear();
        cmdss << string_temp_1 << sensor_name << string_temp_2;
        getline(cmdss, cmd);
        cout << cmd << endl;
        system(cmd.c_str());
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
        cmdss << string_temp_4 << common_nn_models_path << string_temp_5 << string_temp_2;
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

#if 0
    // 4. grep sram, xip/flash and psram information

    // 5. generate image 2, image xip and image psram

    // 6. fulfill header
    // 6.1 remove bss sections
    // 6.2 add header
    // 6.3 generate km4_image2_all

    // 7. prepare image 1
    // 7.1 power save mode bins
#endif

    // 8. generate .bin
    // 8.1 firmware.bin firmware_isp_iq.bin nn_model.bin
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

    cmdss.clear();
    cmdss << string_temp_1 << "combine amebapro2_partitiontable.json system_files.bin PT_PT=partition.bin,CER_TBL=certable.bin,KEY_CER1=certificate.bin,PT_BL_PRI=boot.bin,PT_FCSDATA=boot_fcs.bin";
    getline(cmdss, cmd);
    cout << cmd << endl;
    system(cmd.c_str());

    if (nn_model_selection_check == 1) {
        cmdss.clear();
        cmdss << string_temp_1 << "combine amebapro2_partitiontable.json flash_ntz.bin PT_PT=partition.bin,CER_TBL=certable.bin,KEY_CER1=certificate.bin,PT_BL_PRI=boot.bin,PT_FW1=firmware.bin,PT_NN_MDL=nn_model.bin,PT_ISP_IQ=firmware_isp_iq.bin,PT_FCSDATA=boot_fcs.bin";
        getline(cmdss, cmd);
        cout << cmd << endl;
        system(cmd.c_str());
    } else {
        cmdss.clear();
        cmdss << string_temp_1 << "combine amebapro2_partitiontable.json flash_ntz.bin PT_PT=partition.bin,CER_TBL=certable.bin,KEY_CER1=certificate.bin,PT_BL_PRI=boot.bin,PT_FW1=firmware.bin,PT_ISP_IQ=firmware_isp_iq.bin,PT_FCSDATA=boot_fcs.bin";
        getline(cmdss, cmd);
        cout << cmd << endl;
        system(cmd.c_str());
    }

#if 0
    // 9. add checksum
    // cmd = ".\\tools\\windows\\checksum.exe ota.bin";
    // cout << cmd << endl;
    // system(cmd.c_str());
#endif

    return 0;
}
