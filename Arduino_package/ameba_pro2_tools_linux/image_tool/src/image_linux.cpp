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

string auto_board, auto_user_selection, flash_erase_mode_user_selection, flash_speed;
string serial_port, auto_tool_name, flash_tool_name, fw1_address;
string upload_mode_user_selection, upload_mode_user_selection_nn, upload_mode_user_selection_voe;

string VOE_address_PT_ISP_IQ = "0x400000";
string NN_address_PT_NN_MDL = "0x840000";
int upload_delay = 1000; // 1s 
int check_upload_mode = 0x0;

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
       if (upload_mode_user_selection == "SpeedEnable") {
            if (upload_mode_user_selection_voe == "VOEyes") {
                if (upload_mode_user_selection_nn == "NNyes") {
                    check_upload_mode = 0x111;
                } else {
                    check_upload_mode = 0x110;
                }
            } else {
                if (upload_mode_user_selection_nn == "NNyes") {
                    check_upload_mode = 0x101;
                } else {
                    check_upload_mode = 0x100;
                }
            }
        } else {
            if (upload_mode_user_selection_voe == "VOEyes") {
                if (upload_mode_user_selection_nn == "NNyes") {
                    check_upload_mode = 0x011;
                } else {
                    check_upload_mode = 0x010;
                }
            } else {
                if (upload_mode_user_selection_nn == "NNyes") {
                    check_upload_mode = 0x001;
                } else {
                    check_upload_mode = 0x0;
                }
            }
        }

        if (check_upload_mode == 0x111) {
            cout << "    Speed Mode unable to process more than 1 bin   " << endl;
        } else if (check_upload_mode == 0x110) {
            cmdss.clear();
            cmdss << "./image_tool/" << flash_tool_name << " -p " << serial_port << " -f firmware_isp_iq.bin -b " << flash_speed << " -s " << VOE_address_PT_ISP_IQ << " -U -r ";
            getline(cmdss, cmd);
            system(cmd.c_str());
            check_image_upload = 0;
        } else if (check_upload_mode == 0x101) {
            cmdss.clear();
            cmdss << "./image_tool/" << flash_tool_name << " -p " << serial_port << " -f nn_model.bin -b " << flash_speed << " -s " << NN_address_PT_NN_MDL << " -U -r ";
            getline(cmdss, cmd);
            system(cmd.c_str());
        } else if (check_upload_mode == 0x100) {
            cmdss.clear();
            cmdss << "./image_tool/" << flash_tool_name << " -p " << serial_port << " -f flash_ntz.bin -b " << flash_speed << " -s " << fw1_address << " -U -r ";
            getline(cmdss, cmd);
            system(cmd.c_str());
        } else {
            cmdss.clear();
            cmdss << "./image_tool/" << flash_tool_name << " -p " << serial_port << " -f flash_ntz.bin -b " << flash_speed << " -U -r ";
            getline(cmdss, cmd);
            system(cmd.c_str());
        }

        check_upload_mode = 0x0;
        check_image_upload = 0;
    }
    check_download_process = 100;
}

void download_indicate(void) {
    if (upload_mode_user_selection_nn == "NNyes") {
        upload_delay = 2000;
    }

    if (check_flash_erase == 100) {
        cout << "    Erasing." << flush;
        while (1) {
            msleep(upload_delay);
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
            msleep(upload_delay);
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
    // 0. change work folder
    chdir(argv[1]);

    // 1. set up all strings
    serial_port = argv[2];
    auto_board = argv[3];
    auto_user_selection = argv[4];
    flash_erase_mode_user_selection = argv[5];
    flash_speed = argv[6];
    flash_tool_name = argv[7];
    auto_tool_name = argv[8];
    //upload_mode_user_selection = argv[9];
    fw1_address = argv[10];
    upload_mode_user_selection_nn = argv[11];
    upload_mode_user_selection_voe = argv[12];

    if (argv[9]) {
        upload_mode_user_selection = argv[9];
    } else {
        upload_mode_user_selection = "NormalEnable";
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

    if (flash_erase_mode_user_selection == "Enable") {
        cout << "    Start Erase Flash" << endl;
        check_flash_erase = 100;
    } else {
        cout << "    Start Upload Flash" << endl;
        check_image_upload = 100;
    }

    thread t2(download_indicate);
    thread t1(download_process);

    t2.join();
    t1.join();

    return 0;
}
