/*

Compile:

windows:
mingw32-g++.exe -o test.exe test.cpp -static

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

void readtxt(int line_number)
{
    string buf[line_number];
    ifstream file("test/sensor_bin_name.txt");
    string str;
    int str_count = 0;
    while (std::getline(file, str)) {
        buf[str_count] = str;
        str_count++;
        if (str_count == line_number) {
            break;
        }
    }
    fc_data_name = buf[0];
    voe_name = buf[1];
    iq_name = buf[2];
    sensor_name = buf[3];
}

int main(int argc, char *argv[]) {
    string cmd, line, msg;
    string video_init_user_selection = "Enable";
    if (video_init_user_selection == "Enable") {
        readtxt(4);

        cmd = "readtxt";
        cout << cmd << endl;
    } else {
        cmd = "else";
        cout << cmd << endl;
    }

    return 0;
}
