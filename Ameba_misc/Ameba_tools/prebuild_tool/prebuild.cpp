/*

Compile:

windows:
g++.exe -o prebuild_windows.exe prebuild.cpp -static
strip prebuild_windows.exe
### g++.exe -o prebuild_windows.exe prebuild.cpp -static ../../Ameba_icon/ico-out.o -static
### mingw32-g++.exe -o prebuild_windows.exe prebuild.cpp -static

linux:
g++ -o prebuild_linux prebuild.cpp -static
strip prebuild_linux

macos:
g++ -arch x86_64 -arch arm64 -o prebuild_macos prebuild.cpp
### g++ -o prebuild_macos prebuild.cpp
### strip prebuild_macos

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

string common_libs_path, common_sensor_sel_libs_path, common_nn_libs_path, nn_tool_name_path;
string isp_camera_option, nn_tool_name;

int main(int argc, char *argv[]) {
    stringstream cmdss;
    string cmd;

    // runtime tool path
    chdir(argv[1]);
    chdir("../..");

    isp_camera_option = argv[7];
    nn_tool_name_path = argv[8]; //"ameba_pro2_nn_models/1.0.0";
    nn_tool_name = argv[9]; //"ameba_pro2_nn_models";

#if defined(__WIN32__) // MINGW64
    string string_temp_1 = "copy ";
    string string_temp_2 = "\\";

    common_libs_path = argv[6];
    common_libs_path = common_libs_path + "\\variants\\common_libs\\libarduino_sensor_sel.a";
    common_sensor_sel_libs_path = argv[6];
    common_sensor_sel_libs_path = common_sensor_sel_libs_path + "\\variants\\common_sensor_sel_libs\\";
    common_nn_libs_path = argv[6];
    common_nn_libs_path = common_nn_libs_path + "\\variants";

    cmdss.clear();
    cmdss << "if exist \"" << common_libs_path << "\" del \"" << common_libs_path << "\"";
    getline(cmdss, cmd);
    cout << cmd << endl;
    system(cmd.c_str());

    cmdss.clear();
    cmdss << "if exist " << argv[3] << " xcopy /y /s \"" << argv[3] << "\" \"" << argv[2] << "\"";
    getline(cmdss, cmd);
    cout << cmd << endl;
    system(cmd.c_str());

    cmdss.clear();
    cmdss << "if exist " << argv[5] << " rmdir /s /q " << argv[5];
    getline(cmdss, cmd);
    cout << cmd << endl;
    system(cmd.c_str());

    cmdss.clear();
//     cmdss << "if exist " << nn_tool_name_path <<" xcopy /y /s \"" << nn_tool_name_path << "\" \"" << common_nn_libs_path << "\"";
    cmdss << "if exist " << nn_tool_name_path <<  " xcopy /y /s \"" << nn_tool_name_path << "\" \"" << common_nn_libs_path << "\"";
    getline(cmdss, cmd);
    cout << cmd << endl;
    system(cmd.c_str());

    cmdss.clear();
    cmdss << "if exist " << nn_tool_name << " rmdir /s /q " << nn_tool_name;
    getline(cmdss, cmd);
    cout << cmd << endl;
    system(cmd.c_str());

#elif defined(__linux__) || defined(__APPLE__) // ubuntu 32 bits and OS X 64bits
    string string_temp_1 = "cp ";
    string string_temp_2 = "/";

    common_libs_path = argv[6];
    common_libs_path = common_libs_path + "/variants/common_libs/libarduino_sensor_sel.a";
    common_sensor_sel_libs_path = argv[6];
    common_sensor_sel_libs_path = common_sensor_sel_libs_path + "/variants/common_sensor_sel_libs/";
    common_nn_libs_path = argv[6];
    common_nn_libs_path = common_nn_libs_path + "/variants";

    cmdss.clear();
    cmdss << "rm -f " << common_libs_path;
    getline(cmdss, cmd);
    cout << cmd << endl;
    system(cmd.c_str());

//    cmdss << "cp -r ./" << argv[3] << "/* " << argv[2] << " 2> /dev/null " ;
//    cmdss << "find ./ -mindepth 1 -maxdepth 1 -type d -name \"" << argv[3] << "\" | xargs -i cp -r {}/*" << " ./"<< argv[2];
    cmdss.clear();
#if defined(__APPLE__) // OS X 64bits
    cmdss << "find ./" << argv[3] << "/ -mindepth 1 -maxdepth 1 -type d -name \"*\" 2>/dev/null | xargs -I \"{}\" cp -r \"{}\"" << " ./"<< argv[2] << "/";
#else
    cmdss << "find ./" << argv[3] << "/ -mindepth 1 -maxdepth 1 -type d -name \"*\" 2>/dev/null | xargs -i cp -r {}" << " ./"<< argv[2] << "/";
#endif
    getline(cmdss, cmd);
    cout << cmd << endl;
    system(cmd.c_str());

    cmdss.clear();
    cmdss << "rm -rf " << argv[5];
    getline(cmdss, cmd);
    cout << cmd << endl;
    system(cmd.c_str());

    cmdss.clear();
#if defined(__APPLE__) // OS X 64bits
    cmdss << "find ./" << nn_tool_name_path << "/ -mindepth 1 -maxdepth 1 -type d -name \"*\" 2>/dev/null | xargs -I \"{}\" cp -r \"{}\" "<< common_nn_libs_path << "/";
#else
    cmdss << "find ./" << nn_tool_name_path << "/ -mindepth 1 -maxdepth 1 -type d -name \"*\" 2>/dev/null | xargs -i cp -r {} "<< common_nn_libs_path << "/";
#endif
    getline(cmdss, cmd);
    cout << cmd << endl;
    system(cmd.c_str());

    cmdss.clear();
    cmdss << "rm -rf " << nn_tool_name;
    getline(cmdss, cmd);
    cout << cmd << endl;
    system(cmd.c_str());
#else
    #error compiler is not supported!
#endif

    cmdss.clear();
#if _WIN32
    cmdss << string_temp_1 << "\"" << common_sensor_sel_libs_path << isp_camera_option << string_temp_2 << "libarduino_sensor_sel.a\" \"" << common_libs_path << "\"";
#else
    cmdss << string_temp_1 << common_sensor_sel_libs_path << isp_camera_option << string_temp_2 << "libarduino_sensor_sel.a " << common_libs_path;
#endif
    getline(cmdss, cmd);
    cout << cmd << endl;
    system(cmd.c_str());

    return 0;
}
