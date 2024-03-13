/*

Compile:

windows:
g++.exe -o postbuild_windows.exe postbuild_windows.cpp -static
strip postbuild_windows.exe
### g++.exe -o postbuild_windows.exe postbuild_windows.cpp -static ico-out.o -static
### mingw32-g++.exe -o postbuild_windows.exe postbuild_windows.cpp -static

If you encounter any issue while generating exe with icon, you may refer to: https://www.rodneybeede.com/programming/compiling_a_c___windows_executable_with_a_custom_icon.html

linux:
g++ -o postbuild_linux postbuild_linux.cpp -static
strip postbuild_linux

macos:
g++ -arch x86_64 -arch arm64 -o postbuild_macos postbuild_macos.cpp
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

string fc_data_name, voe_name, iq_name, sensor_name, isp_fw_dummy_name;
string isp_file_name_buf[100];

string nn_model_yolotiny_name, nn_model_srcfd_name, nn_model_mobilefacenet_name, nn_model_yamnet_name, nn_model_imgclass_name, nn_header_name1, nn_header_name2, nn_header_name3, nn_header_name4, nn_header_name5, isp_bin_check_name;
string ino_name_buf[100];

int isp_selection_check = 0;
int nn_model_selection_check = 0;

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

//void readtxt(int line_number, int mode_isp_nn) {
void readtxt(int mode_isp_ino) {
    string str;
    int str_count = 0;

    if (mode_isp_ino == 0) {
        ifstream file("misc/video_img/sensor_bin_name.txt");
        while (std::getline(file, str)) {
            isp_file_name_buf[str_count] = str;
            str_count++;
            //if (str_count == line_number) {
            //    break;
            //}
        }
        fc_data_name = isp_file_name_buf[0];
        voe_name = isp_file_name_buf[1];
        iq_name = isp_file_name_buf[2];
        sensor_name = isp_file_name_buf[3];
        isp_fw_dummy_name = isp_file_name_buf[4];

    } else if (mode_isp_ino == 1) {
        ifstream file("misc/ino_validation.txt");
        while (std::getline(file, str)) {
            ino_name_buf[str_count] = str;
            str_count++;
            //if (str_count == line_number) {
            //    break;
            //}
        }
        nn_model_yolotiny_name = ino_name_buf[2];
        nn_model_srcfd_name = ino_name_buf[3];
        nn_model_mobilefacenet_name = ino_name_buf[4];
        nn_model_yamnet_name = ino_name_buf[5];
        nn_model_imgclass_name = ino_name_buf[6];
        nn_header_name1 = ino_name_buf[9];
        nn_header_name2 = ino_name_buf[10];
        nn_header_name3 = ino_name_buf[11];
        nn_header_name4 = ino_name_buf[12];
        nn_header_name5 = ino_name_buf[13];
        isp_bin_check_name = ino_name_buf[16];
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

    common_nn_models_path = argv[6];

    // 1. remove previous files
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

    cmd = "copy image_tool\\flash_loader_nor.bin .\\";
    cout << cmd << endl;
    system(cmd.c_str());

    cmdss.clear();
    cmdss << "xcopy /y " << "misc\\normal_img" << " .\\";
    getline(cmdss, cmd);
    cout << cmd << endl;
    system(cmd.c_str());

    readtxt(0);
    readtxt(1);
    isp_bin_check(isp_bin_check_name);
    nn_bin_check(nn_model_yolotiny_name, nn_model_srcfd_name, nn_model_mobilefacenet_name, nn_model_yamnet_name, nn_model_imgclass_name, nn_header_name1, nn_header_name2, nn_header_name3, nn_header_name4, nn_header_name5);

    if (isp_selection_check == 1) {
        cmdss.clear();
        cmdss << "copy misc\\video_img\\" << voe_name << " .\\";
        getline(cmdss, cmd);
        cout << cmd << endl;
        system(cmd.c_str());

        cmd = "copy misc\\video_img\\amebapro2_isp_iq.json .\\";
        cout << cmd << endl;
        system(cmd.c_str());

        cmd = "copy misc\\video_img\\amebapro2_sensor_set.json .\\";
        cout << cmd << endl;
        system(cmd.c_str());

        cmdss.clear();
        cmdss << "copy misc\\video_img\\" << fc_data_name << " .\\";
        getline(cmdss, cmd);
        cout << cmd << endl;
        system(cmd.c_str());

        cmdss.clear();
        cmdss << "copy misc\\video_img\\" << iq_name << " .\\";
        getline(cmdss, cmd);
        cout << cmd << endl;
        system(cmd.c_str());

        cmdss.clear();
        cmdss << "copy misc\\video_img\\" << sensor_name << " .\\";
        getline(cmdss, cmd);
        cout << cmd << endl;
        system(cmd.c_str());
    } else {
        cmdss.clear();
        cmdss << "copy misc\\video_img\\" << isp_fw_dummy_name << " .\\";
        getline(cmdss, cmd);
        cout << cmd << endl;
        system(cmd.c_str());
    }

    if (nn_model_selection_check == 1) {
        cmd = "copy misc\\nn_img\\amebapro2_nn_model.json .\\";
        cout << cmd << endl;
        system(cmd.c_str());

        cmdss.clear();
        cmdss << "xcopy /y " << common_nn_models_path << " .\\";
        getline(cmdss, cmd);
        cout << cmd << endl;
        system(cmd.c_str());
    }

    // 2. copy elf application.ntz to current folder
    cmdss.clear();
    cmdss << "xcopy /y " << argv[2] << " .\\";
    getline(cmdss, cmd);
    cout << cmd << endl;
    system(cmd.c_str());

    cmdss.clear();
    cmdss << "xcopy /y " << argv[5] << " .\\";
    getline(cmdss, cmd);
    cout << cmd << endl;
    system(cmd.c_str());

    // 3. generate information files
    path_arm_none_eabi_gcc.assign(argv[3]);
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
    getline(cmdss, cmd);
    cout << cmd << endl;
    system(cmd.c_str());

    // 3.1 check if any forbidden symbols
    path_symbol_black_list.assign(argv[4]);
    replaceAll(path_symbol_black_list, "/", "\\");
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

    if (isp_selection_check == 1) {
        cmd = ".\\misc\\elf2bin.win.exe convert amebapro2_sensor_set.json ISP_SENSOR_SETS isp_iq.bin";
        cout << cmd << endl;
        system(cmd.c_str());

        cmd = ".\\misc\\elf2bin.win.exe convert amebapro2_isp_iq.json FIRMWARE firmware_isp_iq.bin";
        cout << cmd << endl;
        system(cmd.c_str());

        cmd = ".\\misc\\elf2bin.win.exe convert amebapro2_firmware.json FIRMWARE firmware.bin";
        cout << cmd << endl;
        system(cmd.c_str());
    } else {
        cmd = ".\\misc\\elf2bin.win.exe convert amebapro2_firmware_NA_cam.json FIRMWARE firmware.bin";
        cout << cmd << endl;
        system(cmd.c_str());
    }

    if (nn_model_selection_check == 1) {
        cmd = ".\\misc\\elf2bin.win.exe convert amebapro2_fwfs_nn_models.json FWFS fwfs_nn_model.bin";
        cout << cmd << endl;
        system(cmd.c_str());

        cmd = ".\\misc\\elf2bin.win.exe convert amebapro2_nn_model.json FIRMWARE nn_model.bin";
        cout << cmd << endl;
        system(cmd.c_str());
    }

    cmdss.clear();
    cmdss << ".\\misc\\elf2bin.win.exe " << "combine amebapro2_partitiontable.json system_files.bin PT_PT=partition.bin,CER_TBL=certable.bin,KEY_CER1=certificate.bin,PT_BL_PRI=boot.bin,PT_FCSDATA=boot_fcs.bin";
    getline(cmdss, cmd);
    cout << cmd << endl;
    system(cmd.c_str());

    if (nn_model_selection_check == 1) {
        cmdss.clear();
        cmdss << ".\\misc\\elf2bin.win.exe " << "combine amebapro2_partitiontable.json flash_ntz.bin PT_PT=partition.bin,CER_TBL=certable.bin,KEY_CER1=certificate.bin,PT_BL_PRI=boot.bin,PT_FW1=firmware.bin,PT_NN_MDL=nn_model.bin,PT_ISP_IQ=firmware_isp_iq.bin,PT_FCSDATA=boot_fcs.bin";
        getline(cmdss, cmd);
        cout << cmd << endl;
        system(cmd.c_str());
    } else {
        cmdss.clear();
        cmdss << ".\\misc\\elf2bin.win.exe " << "combine amebapro2_partitiontable.json flash_ntz.bin PT_PT=partition.bin,CER_TBL=certable.bin,KEY_CER1=certificate.bin,PT_BL_PRI=boot.bin,PT_FW1=firmware.bin,PT_ISP_IQ=firmware_isp_iq.bin,PT_FCSDATA=boot_fcs.bin";
        getline(cmdss, cmd);
        cout << cmd << endl;
        system(cmd.c_str());
    }

#if 0
    // 9. add checksum
    cmd = ".\\tools\\windows\\checksum.exe ota.bin";
    cout << cmd << endl;
    system(cmd.c_str());
#endif

    return 0;
}
