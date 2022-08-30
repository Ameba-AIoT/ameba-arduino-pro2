/*

Compile:

windows:
mingw32-g++.exe -o image_windows.exe image_windows.cpp -static
i686-w64-mingw32-g++.exe -o image_windows.exe image_windows.cpp -static
*/

#include <iostream>
#include <sstream>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <string>
#include <cstdio>
#include <sys/stat.h>
#include <fstream>
#include <unistd.h>

#include <windows.h>

#include <thread>

using namespace std;

stringstream cmdss;
string cmd;
int check_flash_erase = 0;
int check_image_upload = 0;
int check_download_process = 0;

string auto_board, auto_user_selection, flash_erase_mode_user_selection, flash_speed, serial_port, auto_tool_name, flash_tool_name;

void download_process(void) {
    if (check_flash_erase == 100) {
        cmdss.clear();
        cmdss << ".\\image_tool\\" << flash_tool_name << " -p " << serial_port <<" -b " << flash_speed << " -e chip -r ";
        getline(cmdss, cmd);
        //cout << cmd << endl;
        system(cmd.c_str());
        check_flash_erase = 0;
    }
    if (check_image_upload == 100) {
        cmdss.clear();
        cmdss << ".\\image_tool\\" << flash_tool_name << " -p " << serial_port << " -f flash_ntz.bin -b " << flash_speed << " -r ";
        getline(cmdss, cmd);
        //cout << cmd << endl;
        system(cmd.c_str());
        check_image_upload = 0;
    }
    check_download_process = 100;
}

void download_indicate(void) {
    if (check_flash_erase == 100) {
        cout << "    Erasing." << flush;
        while (1) {
            Sleep(1000);
            if (check_download_process != 0) {
                break;
            } else {
                cout << "." << flush;
            }
        }
        cout << "    End Erase Flash" << endl;
    } else {
        cout << "    Uploading." << flush;
        while (1) {
            Sleep(1000);
            if (check_download_process != 0) {
                break;
            } else {
                cout << "." << flush;
            }
        }
        cout << "    End Upload Flash" << endl;
    }
}

int main(int argc, char *argv[]) {
    //string auto_board, auto_user_selection, flash_erase_mode_user_selection, flash_speed;

    // 0. change work folder
    chdir(argv[1]);

    // 1. rset up all strings 
    auto_board = argv[3];
    auto_user_selection = argv[4];
    flash_erase_mode_user_selection = argv[5];
    flash_speed = argv[6];
    serial_port = argv[2];
    auto_tool_name = argv[8];
    flash_tool_name = argv[7];

    if (auto_user_selection == "Enable") {
        cout << "    Enter Auto Flash Mode!" << endl;
        cmdss.clear();
        cmdss << ".\\image_tool\\" << argv[8] << " .\\ " << argv[2] <<" 115200";
        getline(cmdss, cmd);
        //cout << cmd << endl;
        system(cmd.c_str());
    } else {
        cout << "    Please Enter Flash Mode Manually!" << endl;
        for (int i = 5; i > 0; i--) {
            Sleep(1000);
            cmd = to_string(i);
            cout << "            0" << cmd << endl;
        }
    }

#if 0
    if (flash_erase_mode_user_selection == "Enable") {
        cout << "    Start Erase Flash" << endl;
        cmdss.clear();
        cmdss << ".\\image_tool\\" << argv[7] << " -p " << argv[2] <<" -b " << argv[6] << " -e chip -r ";
        getline(cmdss, cmd);
        //cout << cmd << endl;
        system(cmd.c_str());
        return 0;
    } else {
        cout << "    Start Upload Flash" << endl;
        cmdss.clear();
        cmdss << ".\\image_tool\\" << argv[7] << " -p " << argv[2] << " -f flash_ntz.bin -b " << argv[6] << " -r ";
        getline(cmdss, cmd);
        //cout << cmd << endl;
        system(cmd.c_str());
    }
#else
    if (flash_erase_mode_user_selection == "Enable") {
        cout << "    Start Erase Flash" << endl;
        check_flash_erase = 100;
    } else {
        cout << "    Start Upload Flash" << endl;
        check_image_upload = 100;
    }
#endif

    thread t2(download_indicate);
    thread t1(download_process);

    t2.join();
    t1.join();

    return 0;
}
