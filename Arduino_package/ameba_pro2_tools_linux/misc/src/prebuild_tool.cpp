/*

Compile:

windows:
mingw32-g++.exe -o prebuild_windows.exe prebuild_tool.cpp -static

linux:
g++ -o prebuild_linux prebuild_tool.cpp -static

macos:
g++ -o prebuild_macos prebuild_tool.cpp

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

#if defined(__WIN32__)
    cmdss << "if exist " << argv[3] << " xcopy /y /s \"" << argv[3] << "\" \"" << argv[2] << "\"";
    getline(cmdss, cmd);
    cout << cmd << endl;
    system(cmd.c_str());

    cmdss.clear();
    cmdss << "if exist " << argv[3] << " rmdir /s /q  " << argv[3];
    getline(cmdss, cmd);
    //cout << cmd << endl;
    system(cmd.c_str());

    cmdss.clear();
    cmdss << " mkdir " << argv[3];

#else

#if defined(__APPLE__)
    cmdss << "cp -r ./" << argv[3] << "/* " << argv[2] << " 2>/dev/null " ;
#else
//    cmdss << "find ./ -mindepth 1 -maxdepth 1 -type d -name \"" << argv[3] << "\" | xargs -i cp -r {}/*" << " ./"<< argv[2];
    cmdss << "find ./" << argv[3] << " -mindepth 1 -maxdepth 1 -type d -name \"*\" 2>/dev/null | xargs -i cp -r {}" << " ./"<< argv[2];
#endif

    getline(cmdss, cmd);
    cout << cmd << endl;
    system(cmd.c_str());

    cmdss.clear();
    cmdss << "rm -rf " << argv[3] <<"/*";
#endif

    getline(cmdss, cmd);
    //cout << cmd << endl;
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
