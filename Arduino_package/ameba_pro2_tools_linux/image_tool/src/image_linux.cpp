/*
Compile:

windows:
mingw32-g++.exe -o image_windows.exe image_windows.cpp -static
i686-w64-mingw32-g++.exe -o image_windows.exe image_windows.cpp -static

linux (ubuntu 20.04 TLS ,64 bits app generated):
g++ -o image_linux image_linux.cpp -static
g++ -std=c++11 -lpthread -o image_linux image_linux.cpp

macos:
g++ -o image_macos image_macos.cpp

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

//#include <windows.h>

#include <thread>
#include <time.h>
#include <errno.h>

using namespace std;

#if defined(__WIN32__) // MINGW64
#include <windows.h>

#elif defined(__linux__) || defined(__APPLE__)// ubuntu 32 bits  and OS X 64bits
#include <sys/ioctl.h>
#include <fcntl.h>

#else

#error compiler is not supported!

#endif

int msleep(long msec) {
    struct timespec ts;
    int res;

    if (msec < 0) {
        errno = EINVAL;
        return -1;
    }

    ts.tv_sec = msec / 1000;
    ts.tv_nsec = (msec % 1000) * 1000000;

    do {
        res = nanosleep(&ts, &ts);
    } while (res && errno == EINTR);

    return res;
}

stringstream cmdss;
string cmd;
int check_flash_erase = 0;
int check_image_upload = 0;
int check_download_process = 0;

string auto_board, auto_user_selection, flash_erase_mode_user_selection, flash_speed, serial_port, auto_tool_name, flash_tool_name, video_init_user_selection;

void download_process(void) {
    if (check_flash_erase == 100) {
        cmdss.clear();
        cmdss << "./image_tool/" << flash_tool_name << " -p " << serial_port <<" -b " << flash_speed << " -e chip -r ";
        getline(cmdss, cmd);
        //cout << cmd << endl;
        system(cmd.c_str());
        check_flash_erase = 0;
    }
    if (check_image_upload == 100) {
        cmdss.clear();
        if (video_init_user_selection == "Enable") {
            cmdss << "./image_tool/" << flash_tool_name << " -p " << serial_port << " -f flash_ntz.bin -b " << flash_speed << " -r ";
        } else {
            cmdss << "./image_tool/" << flash_tool_name << " -p " << serial_port << " -f flash_ntz.bin -b " << flash_speed << " -s 0x100000 -r ";
        }
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
            msleep(1000);
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
            msleep(1000);
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
    video_init_user_selection = argv[9];

    if (argv[9]) {
        video_init_user_selection = argv[9];
    } else {
        video_init_user_selection = "Disable";
    }

    if (auto_user_selection == "Enable") {
        cout << "    Enter Auto Flash Mode!" << endl;
        cmdss.clear();
        cmdss << "./image_tool/" << auto_tool_name << " ./ " << serial_port <<" 115200";
        getline(cmdss, cmd);
        //cout << cmd << endl;
        system(cmd.c_str());
    } else {
        cout << "    Please Enter Flash Mode Manually!" << endl;
        for (int i = 5; i > 0; i--) {
            msleep(1000);
            cmd = to_string(i);
            cout << "            0" << cmd << endl;
        }
    }

#if 0
    if (flash_erase_mode_user_selection == "Enable") {
        cout << "    Start Erase Flash" << endl;
        cmdss.clear();
        cmdss << "./image_tool/" << argv[7] << " -p " << argv[2] <<" -b " << argv[6] << " -e chip -r ";
        getline(cmdss, cmd);
        //cout << cmd << endl;
        system(cmd.c_str());
        return 0;
    } else {
        cout << "    Start Upload Flash" << endl;
        cmdss.clear();
        cmdss << "./image_tool/" << argv[7] << " -p " << argv[2] << " -f flash_ntz.bin -b " << argv[6] << " -r ";
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
