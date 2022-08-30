/*

Compile:

windows:
mingw32-g++.exe -o prebuild_windows.exe prebuild_windows.cpp -static

linux:
g++ -o prebuild_linux prebuild_linux.cpp -static

macos:
g++ -o prebuild__macos prebuild__macos.cpp

*/

#include <iostream>
#include <sstream>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <unistd.h>
#include <vector>
#include <string>

using namespace std;

int main(int argc, char *argv[]) {
    stringstream cmdss;
    string cmd;

    chdir(argv[1]);
    chdir("..");

    cmdss.clear();
    cmdss << "if exist " << argv[3] << " xcopy /y /s \"" << argv[3] << "\" \"" << argv[2] << "\"";
    getline(cmdss, cmd);
    cout << cmd << endl;
    system(cmd.c_str());

    cmdss.clear();
    //cmdss << "if exist " << argv[3] << " rm -rf " << argv[3];
    cmdss << "if exist " << argv[3] << " rmdir /s /q  " << argv[3];
    getline(cmdss, cmd);
    cout << cmd << endl;
    system(cmd.c_str());

#if 0
    cmd = "if exist 1.0.0-p2 xcopy /y /s \"1.0.0-p2\" \"1.0.0-p1\"";
    cout << cmd << endl;
    system(cmd.c_str());

    cmd = "if exist 1.0.0-p2 rmdir 1.0.0-p2";
    cout << cmd << endl;
    system(cmd.c_str());
#endif

    return 0;
}
