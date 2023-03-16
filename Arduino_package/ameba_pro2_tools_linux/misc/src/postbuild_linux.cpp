/*

Compile:

windows:
mingw32-g++.exe -o postbuild_windows.exe postbuild_windows.cpp -static

linux:
g++ -o postbuild_linux postbuild_linux.cpp -static

macos:
g++ -o postbuild_macos postbuild_macos.cpp

*/

#include <iostream>
#include <sstream>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <unistd.h>
#include <vector>

using namespace std;

string fc_data_name, voe_name, iq_name, sensor_name;
string name_buf[4];

string upload_mode_user_selection, upload_mode_user_selection_nn, upload_mode_user_selection_voe;
string common_nn_models_path;

int readtxt(int line_number)
{
    ifstream myFile_Handler;
    string myLine;
    myFile_Handler.open("misc/video_img/sensor_bin_name.txt");
    int str_count = 0;

    if(myFile_Handler.is_open())
    {
        while (getline(myFile_Handler, myLine))
        {
            //cout << myLine << endl;
            name_buf[str_count] = myLine;
            str_count++;
            if (str_count == line_number) {
                break;
            } else {
                name_buf[str_count-1].erase(name_buf[str_count-1].size() - 1);
            }
        }
        myFile_Handler.close();
    }
    else
    {
        cout << "Unable to open the file!";
    }

    fc_data_name = name_buf[0];
    voe_name = name_buf[1];
    iq_name = name_buf[2];
    sensor_name = name_buf[3];

    return 0;
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

    //upload_mode_user_selection = argv[6];
    common_nn_models_path = argv[7];
    upload_mode_user_selection_nn = argv[8];
    upload_mode_user_selection_voe = argv[9];
    // *** NN pre requires ISP, can not avoid the ISP when using NN
    if (upload_mode_user_selection_nn == "NNyes") {
        if (upload_mode_user_selection_voe != "VOEyes") {
            upload_mode_user_selection_voe = "VOEyes";
        }
    }

    if (argv[6]) {
        upload_mode_user_selection = argv[6];
    } else {
        upload_mode_user_selection = "NormalEnable";
    }

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

    if (upload_mode_user_selection_voe == "VOEyes") {
        readtxt(4);

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
    }

    if (upload_mode_user_selection_nn == "NNyes") {
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

    cmd = "cp application.ntz application.ntz.axf";
    cout << cmd << endl;
    system(cmd.c_str());

    //    cmdss.clear();
    //    cmdss << path_arm_none_eabi_gcc << "arm-none-eabi-objcopy -j .bluetooth_trace.text -Obinary application.ntz.axf APP.trace";
    //    getline(cmdss, cmd);
    //    cout << cmd << endl;
    //    system(cmd.c_str());

    //    cmdss.clear();
    //    cmdss << path_arm_none_eabi_gcc << "arm-none-eabi-objcopy -R .bluetooth_trace.text application.ntz.axf";
    //    getline(cmdss, cmd);
    //    cout << cmd << endl;
    //    system(cmd.c_str());

    // 8. generate .bin
    // 8.1 firmware_ntz.bin
    if (upload_mode_user_selection_voe == "VOEyes") {
        cmd = "./misc/elf2bin.linux convert amebapro2_sensor_set.json ISP_SENSOR_SETS isp_iq.bin";
        cout << cmd << endl;
        system(cmd.c_str());

        cmd = "./misc/elf2bin.linux convert amebapro2_isp_iq.json FIRMWARE firmware_isp_iq.bin";
        cout << cmd << endl;
        system(cmd.c_str());

        cmd = "./misc/elf2bin.linux convert amebapro2_firmware.json FIRMWARE firmware_ntz.bin";
        cout << cmd << endl;
        system(cmd.c_str());
    } else {
        cmd = "./misc/elf2bin.linux convert amebapro2_firmware_NA_cam.json FIRMWARE firmware_ntz.bin";
        cout << cmd << endl;
        system(cmd.c_str());
    }

    if (upload_mode_user_selection_nn == "NNyes") {
        cmd = "./misc/elf2bin.linux convert amebapro2_fwfs_nn_models.json FWFS fwfs_nn_model.bin";
        cout << cmd << endl;
        system(cmd.c_str());

        cmd = "./misc/elf2bin.linux convert amebapro2_nn_model.json FIRMWARE nn_model.bin";
        cout << cmd << endl;
        system(cmd.c_str());
    }

    // 8.1 flash_ntz.bin
    if (upload_mode_user_selection == "SpeedEnable") {
        cmd = "cp firmware_ntz.bin flash_ntz.bin";
        cout << cmd << endl;
        system(cmd.c_str());
    } else {
        cmd = "cp firmware_ntz.bin firmware.bin";
        cout << cmd << endl;
        system(cmd.c_str());

        if (upload_mode_user_selection_voe == "VOEyes") {
            if (upload_mode_user_selection_nn == "NNyes") {
                cmdss.clear();
                cmdss << "./misc/elf2bin.linux " << "combine amebapro2_partitiontable.json flash_ntz.bin PT_PT=partition.bin,CER_TBL=certable.bin,KEY_CER1=certificate.bin,PT_BL_PRI=boot.bin,PT_FW1=firmware.bin,PT_NN_MDL=nn_model.bin,PT_ISP_IQ=firmware_isp_iq.bin,PT_FCSDATA=boot_fcs.bin";
                getline(cmdss, cmd);
                cout << cmd << endl;
                system(cmd.c_str());
            } else {
                cmdss.clear();
                cmdss << "./misc/elf2bin.linux " << "combine amebapro2_partitiontable.json flash_ntz.bin PT_PT=partition.bin,CER_TBL=certable.bin,KEY_CER1=certificate.bin,PT_BL_PRI=boot.bin,PT_FW1=firmware.bin,PT_ISP_IQ=firmware_isp_iq.bin,PT_FCSDATA=boot_fcs.bin";
                getline(cmdss, cmd);
                cout << cmd << endl;
                system(cmd.c_str());
            }
        } else {
            if (upload_mode_user_selection_nn == "NNyes") {
                cmdss.clear();
                //cmdss << "./misc/elf2bin.linux " << "combine amebapro2_partitiontable.json flash_ntz.bin PT_PT=partition.bin,CER_TBL=certable.bin,KEY_CER1=certificate.bin,PT_BL_PRI=boot.bin,PT_FW1=firmware.bin,PT_NN_MDL=nn_model.bin,PT_FCSDATA=boot_fcs.bin";
                cmdss << "./misc/elf2bin.linux " << "combine amebapro2_partitiontable.json flash_ntz.bin PT_PT=partition.bin,CER_TBL=certable.bin,KEY_CER1=certificate.bin,PT_BL_PRI=boot.bin,PT_FW1=firmware.bin,PT_NN_MDL=nn_model.bin,PT_ISP_IQ=firmware_isp_iq.bin,PT_FCSDATA=boot_fcs.bin";
                getline(cmdss, cmd);
                cout << cmd << endl;
                system(cmd.c_str());
            } else {
                cmdss.clear();
                cmdss << "./misc/elf2bin.linux " << "combine amebapro2_partitiontable.json flash_ntz.bin PT_PT=partition.bin,CER_TBL=certable.bin,KEY_CER1=certificate.bin,PT_BL_PRI=boot.bin,PT_FW1=firmware.bin,PT_FCSDATA=boot_fcs.bin";
                getline(cmdss, cmd);
                cout << cmd << endl;
                system(cmd.c_str());
            }
        }
    }

    return 0;
}
