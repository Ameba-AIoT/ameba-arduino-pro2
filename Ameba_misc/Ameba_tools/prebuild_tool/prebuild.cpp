/*

Compile:

windows:
mingw32-g++.exe -o prebuild_windows.exe prebuild.cpp -static
g++.exe -o prebuild_windows.exe prebuild.cpp -static
strip prebuild_windows.exe

linux:
g++ -o prebuild_linux prebuild.cpp -static

macos:
g++ -o prebuild_macos prebuild.cpp

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

string common_libs_path, common_sensor_sel_libs_path, isp_camera_option;

int main(int argc, char *argv[]) {
    stringstream cmdss;
    string cmd;

    chdir(argv[1]);
    chdir("..");

    isp_camera_option = argv[6];

#if defined(__WIN32__) // MINGW64
    string string_temp_1 = "copy ";
    string string_temp_2 = "\\";

    common_libs_path = argv[5];
    common_libs_path = common_libs_path + "\\variants\\common_libs\\libarduino_sensor_sel.a";
    common_sensor_sel_libs_path = argv[5];
    common_sensor_sel_libs_path = common_sensor_sel_libs_path + "\\variants\\common_sensor_sel_libs\\";

    cmdss.clear();
    cmdss << "if exist " << common_libs_path << "del " << common_libs_path;
    getline(cmdss, cmd);
    //cout << cmd << endl;
    system(cmd.c_str());

    cmdss.clear();
    cmdss << "if exist " << argv[4] << " xcopy /y /s \"" << argv[4] << "\" \"" << argv[3] << "\"";
    getline(cmdss, cmd);
    //cout << cmd << endl;
    system(cmd.c_str());

    cmdss.clear();
    cmdss << "if exist " << argv[4] << " rmdir /s /q  " << argv[4];
    getline(cmdss, cmd);
    //cout << cmd << endl;
    system(cmd.c_str());

    //cmdss.clear();
    //cmdss << " mkdir " << argv[4];
    //getline(cmdss, cmd);
    ////cout << cmd << endl;
    //system(cmd.c_str());
#if 0
    cmd = "if exist 1.0.0-p2 xcopy /y /s \"1.0.0-p2\" \"1.0.0-p1\"";
    cout << cmd << endl;
    system(cmd.c_str());

    cmd = "if exist 1.0.0-p2 rmdir 1.0.0-p2";
    cout << cmd << endl;
    system(cmd.c_str());
#endif

#elif defined(__linux__) || defined(__APPLE__) // ubuntu 32 bits and OS X 64bits
    string string_temp_1 = "cp ";
    string string_temp_2 = "/";

    common_libs_path = argv[5];
    common_libs_path = common_libs_path + "/variants/common_libs/libarduino_sensor_sel.a";
    common_sensor_sel_libs_path = argv[5];
    common_sensor_sel_libs_path = common_sensor_sel_libs_path + "/variants/common_sensor_sel_libs/";

    cmdss.clear();
    cmdss << "rm -f " << common_libs_path;
    getline(cmdss, cmd);
    //cout << cmd << endl;
    system(cmd.c_str());

    cmdss.clear();
//    cmdss << "cp -r ./" << argv[4] << "/* " << argv[3] << " 2> /dev/null " ;
//    cmdss << "find ./ -mindepth 1 -maxdepth 1 -type d -name \"" << argv[3] << "\" | xargs -i cp -r {}/*" << " ./"<< argv[3];
    cmdss << "find ./" << argv[4] << " -mindepth 1 -maxdepth 1 -type d -name \"*\" 2>/dev/null | xargs -i cp -r {}" << " ./"<< argv[3];
    getline(cmdss, cmd);
    //cout << cmd << endl;
    system(cmd.c_str());

    cmdss.clear();
    cmdss << "rm -rf " << argv[4] <<"/*";
    getline(cmdss, cmd);
    //cout << cmd << endl;
    system(cmd.c_str());
#else
    #error compiler is not supported!
#endif

    if (isp_camera_option == "JXF37") {
        cmdss.clear();
        cmdss << string_temp_1 << common_sensor_sel_libs_path << "SENSOR_F37" << string_temp_2 << "libarduino_sensor_sel.a " << common_libs_path;
        getline(cmdss, cmd);
        //cout << cmd << endl;
        system(cmd.c_str());
    } else if (isp_camera_option == "GC5035") {
        cmdss.clear();
        cmdss << string_temp_1 << common_sensor_sel_libs_path << "SENSOR_GC5035" << string_temp_2 << "libarduino_sensor_sel.a " << common_libs_path;
        getline(cmdss, cmd);
        //cout << cmd << endl;
        system(cmd.c_str());
    } else {
        cout << "Unable to find correct camera option!" << endl;
    }

    return 0;
}
