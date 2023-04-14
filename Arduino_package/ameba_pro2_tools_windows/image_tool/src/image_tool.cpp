/*
Compile:

windows:
g++.exe -o image_windows.exe image_tool.cpp -static
strip image_windows.exe
### mingw32-g++.exe -o image_windows.exe image_tool.cpp -static
### i686-w64-mingw32-g++.exe -o image_windows.exe image_tool.cpp -static

linux (ubuntu 20.04 TLS ,64 bits app generated):
g++ -o image_linux image_tool.cpp -static
g++ -std=c++11 -lpthread -o image_linux image_tool.cpp
strip image_linux

macos:
g++ -o image_macos image_tool.cpp
g++ -std=c++17 -o image_macos image_tool.cpp
strip image_macos

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
#include <filesystem>

#if defined(__WIN32__) // MINGW64
#include <windows.h>

int msleep(long msec) {
    return sleep(msec/1000);
}

#elif defined(__linux__) || defined(__APPLE__)// ubuntu 32 bits  and OS X 64bits

#include <time.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <fcntl.h>

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

#else

#error compiler is not supported!

#endif

#include <thread>

using namespace std;

stringstream cmdss;
string cmd;
int check_flash_erase = 0;
int check_image_upload = 0;
int check_flash_erase_upload = 0;
int check_upload_process_flash_erase = 0;
int check_upload_process_image_upload = 0;

string auto_board, auto_user_selection, flash_erase_mode_user_selection, flash_speed;
string serial_port, auto_tool_name, flash_tool_name, fw1_address;
string upload_mode_backdoor;

// fw1_address reserved for OTA "0x80000"
string ISP_address_PT_ISP_IQ = "0x400000";
string NN_address_PT_NN_MDL = "0x840000";
int upload_delay = 1000; // 1s 

string arduino_firmware_fileName = "arduino_firmware.bin";
string firmware_isp_iq_fileName = "firmware_isp_iq.bin";
string nn_model_fileName = "nn_model.bin";
bool check_nn_bin;

#if defined(__WIN32__) // MINGW64
string image_tool_folder_name = ".\\image_tool\\";
#elif defined(__linux__) || defined(__APPLE__) // ubuntu 32 bits  and OS X 64bits
string image_tool_folder_name = "./image_tool/";
#else
#error compiler is not supported!
#endif


bool fileExistsInCurrentDir(string fileName) {
#if defined(__APPLE__)
    namespace fs = __fs::filesystem;
#else
    namespace fs = filesystem;
#endif
    fs::path filePath = fs::current_path() / fileName;
    return fs::exists(filePath);
}

void upload_process(void) {
    if (check_flash_erase == 100) {
        cmdss.clear();
        if (check_flash_erase_upload == 100) {
            cmdss << image_tool_folder_name << flash_tool_name << " -p " << serial_port <<" -b " << flash_speed << " -e chip -U -x 32 ";
        } else {
            cmdss << image_tool_folder_name << flash_tool_name << " -p " << serial_port <<" -b " << flash_speed << " -e chip -U -x 32 -r ";
        }
        getline(cmdss, cmd);
        system(cmd.c_str());
        check_flash_erase = 0;
        check_upload_process_flash_erase = 100;
    }

    if (check_image_upload == 100) {
        if (check_flash_erase_upload == 100) {
            cmdss.clear();
            cmdss << image_tool_folder_name << flash_tool_name << " -p " << serial_port << " -f system_files.bin -b " << flash_speed << " -x 32 ";
            getline(cmdss, cmd);
            //cout << cmd << endl;
            system(cmd.c_str());
        } else {
            cmdss.clear();
            cmdss << image_tool_folder_name << flash_tool_name << " -p " << serial_port << " -f system_files.bin -b " << flash_speed << " -U -x 32 ";
            getline(cmdss, cmd);
            system(cmd.c_str());
        }

        if (check_nn_bin) {
            cmdss.clear();
            cmdss << image_tool_folder_name << flash_tool_name << " -p " << serial_port << " -f firmware.bin -b " << flash_speed << " -s " << fw1_address << " -x 32 ";
            getline(cmdss, cmd);
            system(cmd.c_str());

            cmdss.clear();
            cmdss << image_tool_folder_name << flash_tool_name << " -p " << serial_port << " -f firmware_isp_iq.bin -b " << flash_speed << " -s " << ISP_address_PT_ISP_IQ << " -x 32 ";
            getline(cmdss, cmd);
            system(cmd.c_str());

            cmdss.clear();
            cmdss << image_tool_folder_name << flash_tool_name << " -p " << serial_port << " -f nn_model.bin -b " << flash_speed << " -s " << NN_address_PT_NN_MDL << " -x 32 -r ";
            getline(cmdss, cmd);
            system(cmd.c_str());
        } else {
            cmdss.clear();
            cmdss << image_tool_folder_name << flash_tool_name << " -p " << serial_port << " -f firmware.bin -b " << flash_speed << " -s " << fw1_address << " -x 32";
            getline(cmdss, cmd);
            system(cmd.c_str());

            cmdss.clear();
            cmdss << image_tool_folder_name << flash_tool_name << " -p " << serial_port << " -f firmware_isp_iq.bin -b " << flash_speed << " -s " << ISP_address_PT_ISP_IQ << " -x 32 -r ";
            getline(cmdss, cmd);
            system(cmd.c_str());
        }

        check_flash_erase_upload = 0;
        check_image_upload = 0;
        check_upload_process_image_upload = 100;
    }
}

void upload_indicate(void) {
    if (check_flash_erase == 100) {
        cout << "    Erasing." << flush;
        while (1) {
            msleep(upload_delay);
            if (check_upload_process_flash_erase != 0) {
                break;
            } else {
                cout << "." << flush;
            }
        }
        cout << "    End Erase Flash" << endl;
    }

    if (check_image_upload == 100) {
        cout << "    Uploading." << flush;
        while (1) {
            msleep(upload_delay);
            if (check_upload_process_image_upload != 0) {
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
    fw1_address = argv[9];
//    upload_mode_backdoor = argv[10];

    check_nn_bin = fileExistsInCurrentDir(nn_model_fileName);
    if (check_nn_bin) {
        upload_delay = 2000;
    }

    if (auto_user_selection == "Enable") {
        cout << "    Enter Auto Flash Mode!" << endl;
        cmdss.clear();
        cmdss << image_tool_folder_name << auto_tool_name << " . " << serial_port <<" 115200";
        getline(cmdss, cmd);
        system(cmd.c_str());
    } else {
#if 0
        cout << "    Please Enter Flash Mode Manually!" << endl;
        for (int i = 5; i > 0; i--) {
            msleep(1000);
            cmd = to_string(i);
            cout << "            0" << cmd << endl;
        }
#endif
        cout << "    Enter Flash Mode!" << endl;
    }

    if (flash_erase_mode_user_selection == "Enable") {
        cout << "    Start Erase Flash" << endl;
        check_flash_erase = 100;
    } else if (flash_erase_mode_user_selection == "Enable_Upload") {
        cout << "    Start Erase Flash then Upload Flash" << endl;
        check_flash_erase = 100;
        check_image_upload = 100;
        check_flash_erase_upload = 100;
    } else {
        cout << "    Start Upload Flash" << endl;
        check_image_upload = 100;
    }

    thread t2(upload_indicate);
    thread t1(upload_process);

    t2.join();
    t1.join();

    return 0;
}
