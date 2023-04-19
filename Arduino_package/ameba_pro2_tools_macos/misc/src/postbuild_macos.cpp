/*

Compile:

windows:
g++.exe -o postbuild_windows.exe postbuild_windows.cpp -static
strip postbuild_windows.exe
### mingw32-g++.exe -o postbuild_windows.exe postbuild_windows.cpp -static

linux:
g++ -o postbuild_linux postbuild_linux.cpp -static
strip postbuild_linux

macos:
g++ -o postbuild_macos postbuild_macos.cpp
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

string nn_model_yolotiny_name, nn_model_srcfd_name, nn_model_mobilefacenet_name, nn_header_name1, nn_header_name2, nn_header_name3, isp_bin_check_name;
string ino_name_buf[100];

int isp_selection_check = 0;
int nn_model_selection_check = 0;


//void readtxt(int line_number, int mode_isp_nn) {
void readtxt(int mode_isp_ino) {
    ifstream myFile_Handler;
    string myLine;
    int str_count = 0;

    if (mode_isp_ino == 0) {
        myFile_Handler.open("misc/video_img/sensor_bin_name.txt");

        if(myFile_Handler.is_open()) {
            while (getline(myFile_Handler, myLine)) {
                //cout << myLine << endl;
                isp_file_name_buf[str_count] = myLine;
                str_count++;
                //if (str_count == line_number) {
                //    break;
                //} else {
                isp_file_name_buf[str_count-1].erase(isp_file_name_buf[str_count-1].size() - 1);
                //}
            }
            myFile_Handler.close();
        } else {
            cout << "Unable to open the file!" << endl;
        }
        fc_data_name = isp_file_name_buf[0];
        voe_name = isp_file_name_buf[1];
        iq_name = isp_file_name_buf[2];
        sensor_name = isp_file_name_buf[3];
        isp_fw_dummy_name = isp_file_name_buf[4];

    } else if (mode_isp_ino == 1) {
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
        nn_model_yolotiny_name = ino_name_buf[2];
        nn_model_srcfd_name = ino_name_buf[3];
        nn_model_mobilefacenet_name = ino_name_buf[4];
        nn_header_name1 = ino_name_buf[7];
        nn_header_name2 = ino_name_buf[8];
        nn_header_name3 = ino_name_buf[9];
        isp_bin_check_name = ino_name_buf[12];
    }
}

void isp_bin_check(string isp_bin_check_name) {
    if (isp_bin_check_name != "NA") {
        isp_selection_check = 1;
    }
}

void nn_bin_check(string nn_model_yolotiny_name, string nn_model_srcfd_name, string nn_model_mobilefacenet_name, string nn_header_name1, string nn_header_name2, string nn_header_name3) {
    if ((nn_model_yolotiny_name != "NA") || (nn_model_srcfd_name != "NA") || (nn_model_mobilefacenet_name != "NA")) {
        if ((nn_header_name1 != "NA") || (nn_header_name2 != "NA") || (nn_header_name3 != "NA")) {
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

    cmd = "cp image_tool/flash_loader_nor.bin ./";
    cout << cmd << endl;
    system(cmd.c_str());

    cmd = "cp misc/normal_img/* ./";
    cout << cmd << endl;
    system(cmd.c_str());

    readtxt(0);
    readtxt(1);
    isp_bin_check(isp_bin_check_name);
    nn_bin_check(nn_model_yolotiny_name, nn_model_srcfd_name, nn_model_mobilefacenet_name, nn_header_name1, nn_header_name2, nn_header_name3);

    if (isp_selection_check == 1) {
        cmdss.clear();
        cmdss << "cp misc/video_img/" << voe_name << " ./";
        getline(cmdss, cmd);
        cout << cmd << endl;
        system(cmd.c_str());

        cmd = "cp misc/video_img/amebapro2_isp_iq.json ./";
        cout << cmd << endl;
        system(cmd.c_str());

        cmd = "cp misc/video_img/amebapro2_sensor_set.json ./";
        cout << cmd << endl;
        system(cmd.c_str());

        cmdss.clear();
        cmdss << "cp misc/video_img/" << fc_data_name << " ./";
        getline(cmdss, cmd);
        cout << cmd << endl;
        system(cmd.c_str());

        cmdss.clear();
        cmdss << "cp misc/video_img/" << iq_name << " ./";
        getline(cmdss, cmd);
        cout << cmd << endl;
        system(cmd.c_str());

        cmdss.clear();
        cmdss << "cp misc/video_img/" << sensor_name << " ./";
        getline(cmdss, cmd);
        cout << cmd << endl;
        system(cmd.c_str());
    } else {
        cmdss.clear();
        cmdss << "cp misc/video_img/" << isp_fw_dummy_name << " ./";
        getline(cmdss, cmd);
        cout << cmd << endl;
        system(cmd.c_str());
    }

    if (nn_model_selection_check == 1) {
        cmd = "cp misc/nn_img/amebapro2_nn_model.json ./";
        cout << cmd << endl;
        system(cmd.c_str());

        cmdss.clear();
        cmdss << "cp " << common_nn_models_path << "/* ./";
        getline(cmdss, cmd);
        cout << cmd << endl;
        system(cmd.c_str());
    }

    // 2. copy elf application.ntz to current folder
    cmdss.clear();
    cmdss << "cp " << argv[2] << " ./";
    getline(cmdss, cmd);
    cout << cmd << endl;
    system(cmd.c_str());

    cmdss.clear();
    cmdss << "cp " << argv[5] << " ./";
    getline(cmdss, cmd);
    cout << cmd << endl;
    system(cmd.c_str());

    // 3. generate information files
    path_arm_none_eabi_gcc.assign(argv[3]);

    cmdss.clear();
    cmdss << path_arm_none_eabi_gcc << "arm-none-eabi-nm application.ntz | sort > application.ntz.nm.map";
    getline(cmdss, cmd);
    cout << cmd << endl;
    system(cmd.c_str());

    cmdss.clear();
    cmdss << path_arm_none_eabi_gcc << "arm-none-eabi-objdump -d application.ntz > application.ntz.asm";
    getline(cmdss, cmd);
    cout << cmd << endl;
    system(cmd.c_str());

    // 3.1 check if any forbidden symbols
    path_symbol_black_list.assign(argv[4]);
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

    if (isp_selection_check == 1) {
        cmd = "./misc/elf2bin.darwin convert amebapro2_sensor_set.json ISP_SENSOR_SETS isp_iq.bin";
        cout << cmd << endl;
        system(cmd.c_str());

        cmd = "./misc/elf2bin.darwin convert amebapro2_isp_iq.json FIRMWARE firmware_isp_iq.bin";
        cout << cmd << endl;
        system(cmd.c_str());

        cmd = "./misc/elf2bin.darwin convert amebapro2_firmware.json FIRMWARE firmware.bin";
        cout << cmd << endl;
        system(cmd.c_str());
    } else {
        cmd = "./misc/elf2bin.darwin convert amebapro2_firmware_NA_cam.json FIRMWARE firmware.bin";
        cout << cmd << endl;
        system(cmd.c_str());
    }

    if (nn_model_selection_check == 1) {
        cmd = "./misc/elf2bin.darwin convert amebapro2_fwfs_nn_models.json FWFS fwfs_nn_model.bin";
        cout << cmd << endl;
        system(cmd.c_str());

        cmd = "./misc/elf2bin.darwin convert amebapro2_nn_model.json FIRMWARE nn_model.bin";
        cout << cmd << endl;
        system(cmd.c_str());
    }

    cmdss.clear();
    cmdss << "./misc/elf2bin.darwin " << "combine amebapro2_partitiontable.json system_files.bin PT_PT=partition.bin,CER_TBL=certable.bin,KEY_CER1=certificate.bin,PT_BL_PRI=boot.bin,PT_FCSDATA=boot_fcs.bin";
    getline(cmdss, cmd);
    cout << cmd << endl;
    system(cmd.c_str());

    if (nn_model_selection_check == 1) {
        cmdss.clear();
        cmdss << "./misc/elf2bin.darwin " << "combine amebapro2_partitiontable.json flash_ntz.bin PT_PT=partition.bin,CER_TBL=certable.bin,KEY_CER1=certificate.bin,PT_BL_PRI=boot.bin,PT_FW1=firmware.bin,PT_NN_MDL=nn_model.bin,PT_ISP_IQ=firmware_isp_iq.bin,PT_FCSDATA=boot_fcs.bin";
        getline(cmdss, cmd);
        cout << cmd << endl;
        system(cmd.c_str());
    } else {
        cmdss.clear();
        cmdss << "./misc/elf2bin.darwin " << "combine amebapro2_partitiontable.json flash_ntz.bin PT_PT=partition.bin,CER_TBL=certable.bin,KEY_CER1=certificate.bin,PT_BL_PRI=boot.bin,PT_FW1=firmware.bin,PT_ISP_IQ=firmware_isp_iq.bin,PT_FCSDATA=boot_fcs.bin";
        getline(cmdss, cmd);
        cout << cmd << endl;
        system(cmd.c_str());
    }

    return 0;
}
