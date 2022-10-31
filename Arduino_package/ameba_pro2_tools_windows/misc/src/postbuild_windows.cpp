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
string name_buf[4] = {fc_data_name, voe_name, iq_name, sensor_name};

void readtxt(int line_number)
{
    ifstream file("misc/video_img/sensor_bin_name.txt");
    string str;
    int str_count = 0;
    while (std::getline(file, str)) {
        name_buf[str_count] = str;
        str_count++;
        if (str_count == line_number) {
            break;
        }
    }
}

void replaceAll( string& source, const string& from, const string& to )
{
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

    string video_init_user_selection;

    if (argv[6]) {
        video_init_user_selection = argv[6];
    } else {
        video_init_user_selection = "Disable";
    }

    // 0. change work folder
    chdir(argv[1]);

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

//    cmd = "copy misc\\image\\voe.bin .\\";
//    cout << cmd << endl;
//    system(cmd.c_str());

//    cmd = "copy misc\\image\\firmware_isp_iq.bin .\\";
//    cout << cmd << endl;
//    system(cmd.c_str());

    cmd = "copy misc\\image\\boot.bin .\\";
    cout << cmd << endl;
    system(cmd.c_str());

    cmd = "copy misc\\image\\boot_fcs.bin .\\";
    cout << cmd << endl;
    system(cmd.c_str());

    cmd = "copy misc\\image\\partition.bin .\\";
    cout << cmd << endl;
    system(cmd.c_str());

    cmd = "copy misc\\image\\certable.bin .\\";
    cout << cmd << endl;
    system(cmd.c_str());

    cmd = "copy misc\\image\\certificate.bin .\\";
    cout << cmd << endl;
    system(cmd.c_str());

    cmd = "copy misc\\image\\amebapro2_partitiontable.json .\\";
    cout << cmd << endl;
    system(cmd.c_str());

    if (video_init_user_selection == "Enable") {
        readtxt(4);

        //cmd = "copy misc\\video_img\\voe.bin .\\";
        //cout << cmd << endl;
        //system(cmd.c_str());

        cmdss.clear();
        cmdss << "copy misc\\video_img\\" << voe_name << " .\\";
        getline(cmdss, cmd);
        cout << cmd << endl;
        system(cmd.c_str());

        cmd = "copy misc\\image\\amebapro2_firmware.json .\\";
        cout << cmd << endl;
        system(cmd.c_str());

        cmd = "copy misc\\video_img\\amebapro2_isp_iq.json .\\";
        cout << cmd << endl;
        system(cmd.c_str());

        cmd = "copy misc\\video_img\\amebapro2_sensor_set.json .\\";
        cout << cmd << endl;
        system(cmd.c_str());

        //cmd = "copy misc\\video_img\\fcs_data_dummy.bin .\\";
        //cout << cmd << endl;
        //system(cmd.c_str());

        //cmd = "copy misc\\video_img\\iq.bin .\\";
        //cout << cmd << endl;
        //system(cmd.c_str());

        //cmd = "copy misc\\video_img\\sensor_jxf37.bin .\\";
        //cout << cmd << endl;
        //system(cmd.c_str());

        //cmd = "copy misc\\video_img\\sensor_fixp.bin .\\";
        //cout << cmd << endl;
        //system(cmd.c_str());

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
        cmd = "copy misc\\image\\amebapro2_firmware_NA_cam.json .\\";
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

    //cmd = "cp application.ntz application.ntz.axf";
    cmd = "copy application.ntz application.ntz.axf";
    cout << cmd << endl;
    system(cmd.c_str());

    cmdss.clear();
    cmdss << "\"" <<path_arm_none_eabi_gcc << "arm-none-eabi-objcopy.exe\" -j .bluetooth_trace.text -Obinary application.ntz.axf APP.trace";
    getline(cmdss, cmd);
    cout << cmd << endl;
    system(cmd.c_str());

    cmdss.clear();
    cmdss << "\"" << path_arm_none_eabi_gcc << "arm-none-eabi-objcopy.exe\" -R .bluetooth_trace.text application.ntz.axf";
    getline(cmdss, cmd);
    cout << cmd << endl;
    system(cmd.c_str());

    // 8. generate .bin
    if (video_init_user_selection == "Enable") {
        cmd = ".\\misc\\elf2bin.exe convert amebapro2_sensor_set.json ISP_SENSOR_SETS isp_iq.bin";
        cout << cmd << endl;
        system(cmd.c_str());

        cmd = ".\\misc\\elf2bin.exe convert amebapro2_isp_iq.json FIRMWARE firmware_isp_iq.bin";
        cout << cmd << endl;
        system(cmd.c_str());

        cmd = ".\\misc\\elf2bin.exe convert amebapro2_firmware.json FIRMWARE firmware_ntz.bin";
        cout << cmd << endl;
        system(cmd.c_str());
    } else {
        cmd = ".\\misc\\elf2bin.exe convert amebapro2_firmware_NA_cam.json FIRMWARE firmware_ntz.bin";
        cout << cmd << endl;
        system(cmd.c_str());
    }

    if (video_init_user_selection == "Enable") {
        //cmd = "cp firmware_ntz.bin firmware.bin";
        cmd = "copy firmware_ntz.bin firmware.bin";
        cout << cmd << endl;
        system(cmd.c_str());

        cmdss.clear();
        cmdss << ".\\misc\\elf2bin.exe " << "combine amebapro2_partitiontable.json flash_ntz.bin PT_PT=partition.bin,CER_TBL=certable.bin,KEY_CER1=certificate.bin,PT_BL_PRI=boot.bin,PT_FW1=firmware.bin,PT_ISP_IQ=firmware_isp_iq.bin,PT_FCSDATA=boot_fcs.bin";
        getline(cmdss, cmd);
        cout << cmd << endl;
        system(cmd.c_str());
    } else {
        //cmdss << ".\\misc\\elf2bin.exe " << "combine amebapro2_partitiontable.json flash_ntz.bin //PT_PT=partition.bin,CER_TBL=certable.bin,KEY_CER1=certificate.bin,PT_BL_PRI=boot.bin,PT_FW1=firmware.bin,PT_FCSDATA=boot_fcs.bin";

        cmd = "copy firmware_ntz.bin flash_ntz.bin";
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
