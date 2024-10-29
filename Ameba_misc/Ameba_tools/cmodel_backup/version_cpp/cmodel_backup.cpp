/*

Compile:

windows:
g++.exe -o cmodel_backup_windows.exe cmodel_backup.cpp -static
strip cmodel_backup_windows.exe
### g++.exe -o cmodel_backup_windows.exe cmodel_backup.cpp -static ico-out.o -static
### mingw32-g++.exe -o cmodel_backup_windows.exe cmodel_backup.cpp -static

If you encounter any issue while generating exe with icon, you may refer to: https://www.rodneybeede.com/programming/compiling_a_c___windows_executable_with_a_custom_icon.html

linux:
g++ -o cmodel_backup_linux cmodel_backup.cpp -static
strip cmodel_backup_linux

macos:
g++ -arch x86_64 -arch arm64 -o cmodel_backup_macos cmodel_backup.cpp
strip cmodel_backup_macos

*/

#include <iostream>
#include <sstream>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <unistd.h>
#include <vector>
#include <string>
#if _WIN32
#include <Windows.h>
#include <locale>
#include <codecvt>
#include <Lmcons.h>
#endif
#include <dirent.h>  // Include necessary headers for Linux/macOS
#include <sys/stat.h>
#include <sys/types.h>
#include "cJSON.h" // Assuming cJSON library is used
#include "cJSON.c" // Assuming cJSON library is used
#include <algorithm>
#include <unordered_map>
#include <cstring> // For strcat
#include <ctime>
#include <cstdio>

#define PRINT_DEBUG         0
#define MAX_PATH_LENGTH     1024
#define BUFFER_SIZE 		4096

#define NUMBER_OF_MODELS 5
using namespace std;

// Declare global variables
std::vector<std::string> ino_name_buf; // Vector to store lines from the file
std::string nn_model_yolotiny_name, nn_model_srcfd_name, nn_model_mobilefacenet_name, nn_model_yamnet_name, nn_model_imgclass_name, nn_default_customized_yolotiny, nn_default_customized_srcfd, nn_default_customized_mobilefacenet, nn_default_customized_yamnet, nn_default_customized_imgclass;
std::string path_root, path_arduino15, path_pro2, path_model, path_library, path_txtfile, load_nn_model_src, ver_pro2, folder_example,  pathModel;
std::string path_build_options_json;
std::string path_example, path_example_ino;
std::string rootDir;
std::string key_portable = "portable";
std::string filename_txt = "ino_validation.txt";
std::string key_json = "build";
std::string ext_json = ".json";
std::string filenameModified;
std::string sourcePath, destinationPath, destinationPath2;
bool flag_Dbackup = false;

//Keywords
std::string yolov3_model = "yolov3";
std::string yolov4_model = "yolov4";
std::string yolov7_model = "yolov7";
std::string scrfd_model = "scrfd";
std::string mobilefacenet_model = "mobilefacenet";
std::string yamnet_model = "yamnet";
std::string cnn_model = "img_class";
std::string cnn_key = "img";

// Declare common file paths
#ifdef _WIN32
std::string path_arduino15_add = "\\AppData\\Local\\Arduino15\\";
std::string path_ambpro2_add = "\\packages\\realtek\\hardware\\AmebaPro2\\";
//std::string path_arduino15_add_portable = "";						// TODO: added for portable
std::string path_model_add = "\\variants\\common_nn_models\\";
std::string path_library_add = "\\libraries\\";
std::string path_txtfile_add = "\\misc\\";
std::string backspace = "\\";
#elif __linux__
std::string path_arduino15_add = "/.arduino15/";
//char* path_arduino15_add_portable = "";						// TODO: added for portable
std::string path_ambpro2_add = "/packages/realtek/hardware/AmebaPro2/";
std::string path_model_add = "/variants/common_nn_models/";
std::string path_library_add = "/libraries/";
std::string path_txtfile_add = "/misc/";
std::string backspace = "/";
#else
std::string path_arduino15_add = "/Library/Arduino15/";
//char* path_arduino15_add_portable = "";						// TODO: added for portable
std::string path_ambpro2_add = "/packages/realtek/hardware/AmebaPro2/";
std::string path_model_add = "/variants/common_nn_models/";
std::string path_library_add = "/libraries/";
std::string path_txtfile_add = "/misc/";
std::string backspace = "/";
#endif

// -------------------------------
//           Functions
// -------------------------------
#ifdef _WIN32
std::wstring get_username() {
    wchar_t username[MAX_PATH];
    DWORD size = sizeof(username) / sizeof(username[0]);
    if (GetUserNameW(username, &size)) {
        return std::wstring(username);
    } else {
        std::wcerr << L"Failed to retrieve username. Error code: " << GetLastError() << std::endl;
        return L"Unknown";
    }
}

std::wstring utf8_to_utf16(const std::string& utf8str) {
    int len = MultiByteToWideChar(CP_UTF8, 0, utf8str.c_str(), -1, nullptr, 0);
    wchar_t* wstr = new wchar_t[len];
    MultiByteToWideChar(CP_UTF8, 0, utf8str.c_str(), -1, wstr, len);
    std::wstring result(wstr);
    delete[] wstr;
    return result;
}

std::string convert_to_utf8(const std::wstring& wide_str) {
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    return converter.to_bytes(wide_str);
}

// Check if username is correct or have weird symbols between Users and AppData
// ** For chinese version laptop such as using 使用者, TBD
std::string getUsernameChecked(const std::string& path) {
	std::string newPath = path;
	std::wstring username_wide = get_username();
    std::string username_utf8 = convert_to_utf8(username_wide);

    size_t usersPos = newPath.find("Users\\");
    if (usersPos == std::string::npos) {
        return newPath; // 'Users\\' not found, return original path
    }
    usersPos += 6; // Move past 'Users\\'

    size_t appDataPos = newPath.find("\\AppData", usersPos);
    if (appDataPos == std::string::npos) {
        return newPath; // '\\AppData' not found after 'Users\\', return original path
    }

    std::string currentSegment = newPath.substr(usersPos, appDataPos - usersPos);
    if (currentSegment != username_utf8) {
        newPath.replace(usersPos, appDataPos - usersPos, username_utf8);
    }

    return newPath;
}
#endif
std::string dirName(const std::string& directory_path) {
int sdk_counter = 0;

#ifdef _WIN32
	std::wstring sdk_name;
	std::wstring directory_path_utf16 = utf8_to_utf16(directory_path);
	// Use Windows API to open directory and list contents
	WIN32_FIND_DATAW findData;
	HANDLE hFind = FindFirstFileW((directory_path_utf16 + L"\\*").c_str(), &findData);
	if (hFind == INVALID_HANDLE_VALUE) {
		DWORD error = GetLastError();
		std::cerr << "5 Failed to open directory: " << error << std::endl;
		return "Failed to open directory.";
	}

	do {
		// Assuming SDK folders are identified by specific criteria, adjust as per your requirements
		if (wcscmp(findData.cFileName, L".") != 0 && wcscmp(findData.cFileName, L"..") != 0) {
			++sdk_counter;
			if (PRINT_DEBUG) std::wcout << findData.cFileName << std::endl;
			sdk_name = findData.cFileName; // Store the SDK folder name	
		}
	} while (FindNextFileW(hFind, &findData) != 0);

	FindClose(hFind);

	// Check number of SDK folders found
	if (sdk_counter > 1) {
		std::string errorMessage = "AmebaPro2 directory allows only 1 SDK folder. Please check again.";
		std::cerr << "[Error] " << errorMessage << std::endl;
		exit(EXIT_FAILURE);
	} 
	std::string sdk_name_utf8 = convert_to_utf8(sdk_name);
	return sdk_name_utf8;
#else
	struct dirent* entry;
	DIR* directory = opendir(directory_path.c_str());
	const char* sdk_name = "";

	// Check directory validation
	if (directory) {
		while ((entry = readdir(directory)) != nullptr) {
#ifdef __APPLE__
			if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0 || strcmp(entry->d_name, ".DS_Store") == 0) {
#else
			if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
#endif
				continue;
			}
			else {
				sdk_counter++;
				sdk_name = entry->d_name;
			}
		}
				
		// Validate if there's more than 1 SDK folder found in AmebaPro2 folder 
		if (sdk_counter > 1) {
			std::string errorMessage = "AmebaPro2 directory only allows 1 SDK!!! Please check again.";
			std::cerr << "[Error] " << errorMessage << std::endl;
			exit(EXIT_FAILURE);
		}
		else {
			return sdk_name;
		}
	} 
	else {
		std::string errorMessage = "Failed to open directory.";
		std::cerr << "[Error] " << errorMessage << std::endl;
		exit(EXIT_FAILURE);
	}
	closedir(directory);
#endif
}

// Function to search for a keyword in a path and return the path up to that keyword
std::string findKeywordPath(const std::string& path, const std::string& keyword) {
	std::string result;
	// Search for the keyword in the path
    size_t found = path.find(keyword);
    if (found != std::string::npos) {
        // Calculate the length up to the end of the keyword
        size_t length = found + keyword.length();
        // Copy the relevant part of the path to the result
        result = path.substr(0, length);
		return result;
    } else {
		// Return NULL if the keyword is not found
		return NULL;
	}
}

// // Return the file path that can be found in  build.options.json, where build.options.json can be found in Temp folder of Arduino
// // The path returned is the sketchLocation in build.options.json
std::string pathTempJSON(const std::string& directory_path, const std::string& ext, const std::string& key) {
#if _WIN32
    WIN32_FIND_DATAW findFileData; // Use WIN32_FIND_DATAW for wide-character version
    HANDLE hFind;

    std::wstring directory_path_utf16 = utf8_to_utf16(directory_path);
    std::wstring search_path = directory_path_utf16 + L"\\*"; // Append * to get all files in directory
    hFind = FindFirstFileW(search_path.c_str(), &findFileData);

    if (hFind == INVALID_HANDLE_VALUE) {
        std::cerr << "[" << __func__ << "][" << __LINE__ << "][Error] Failed to open dir at: " << directory_path << std::endl;
        return "";
    } else {
        do {
            if (findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
                continue; // Skip directories
            }

            std::string file_name = convert_to_utf8(findFileData.cFileName);
            if (file_name.find(ext) != std::string::npos && file_name.find(key) != std::string::npos) {
               if (PRINT_DEBUG) std::wcout << "[" << __func__ << "][INFO] File: " << findFileData.cFileName << std::endl;

                std::string file_path = directory_path + "\\" + file_name;
                if (PRINT_DEBUG) std::cout << "[" << __func__ << "][INFO] File path: " << file_path << std::endl;
                FindClose(hFind);
                return file_path;
            }
        } while (FindNextFileW(hFind, &findFileData) != 0);

        FindClose(hFind);
    }

    return ""; // Return empty string if not found
#else
    DIR* dir;
    struct dirent* entry;
    if ((dir = opendir(directory_path.c_str())) == nullptr) {
#if PRINT_DEBUG
        perror("opendir() error");
        std::cerr << "[" << __func__ << "][" << __LINE__ << "][Error] Failed to open dir at: " << directory_path << std::endl;
#endif
    } else {
        while ((entry = readdir(dir)) != nullptr) {
            if (entry->d_type == DT_REG && //d_type: file type, d_name: file name
                std::string(entry->d_name).find(ext) != std::string::npos &&
                std::string(entry->d_name).find(key) != std::string::npos) {
#if PRINT_DEBUG
                std::cout << "[" << __func__ << "][" << __LINE__ << "][INFO] File: " << entry->d_name << std::endl;
#endif
                std::string file_path = directory_path + backspace + entry->d_name;
				//std::cout << "[" << __func__ << "][" << __LINE__ << "][INFO] File: " << file_path << std::endl;
                return file_path;
            }
        }
        closedir(dir);
    }
    return ""; // Return empty string if not found
#endif
}

// Load and parse JSON file function using Windows API
cJSON* loadTempJSONFile(const std::string& file_path) {
#ifdef _WIN32
	// Convert UTF-8 file path to UTF-16 for Windows API
	std::wstring file_path_wide = utf8_to_utf16(file_path);

	// Open the file using Unicode version of CreateFile
	HANDLE hFile = CreateFileW(file_path_wide.c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE) {
		std::cerr << "Failed to open file: " << file_path << std::endl;
		return nullptr;
	}

	// Get file size
	DWORD file_size = GetFileSize(hFile, NULL);
	if (file_size == INVALID_FILE_SIZE) {
		CloseHandle(hFile);
		std::cerr << "Error getting file size: " << file_path << std::endl;
		return nullptr;
	}

	// Allocate buffer for file data
	std::string json_data(file_size, '\0');

	// Read file content into buffer
	DWORD bytes_read;
	if (!ReadFile(hFile, &json_data[0], file_size, &bytes_read, NULL)) {
		CloseHandle(hFile);
		std::cerr << "Error reading file: " << file_path << std::endl;
		return nullptr;
	}

	CloseHandle(hFile);

	// Parse the JSON data
	cJSON* data = cJSON_Parse(json_data.c_str());
	if (data == nullptr) {
		std::cerr << "Error parsing JSON in file: " << file_path << std::endl;
	}

	return data;
#else 
	std::ifstream file(file_path);
	std::string json_data;
	
	if (!file.is_open()) {
		std::cerr << "Error opening file: " << file_path << std::endl;
		return nullptr;
	}

	// Read the file contents into a string
	file.seekg(0, std::ios::end);
	json_data.reserve(file.tellg());
	file.seekg(0, std::ios::beg);
	json_data.assign((std::istreambuf_iterator<char>(file)),
						std::istreambuf_iterator<char>());
	
	file.close();

	// Parse the JSON data
	cJSON* data = cJSON_Parse(json_data.c_str());
	if (data == nullptr) {
		std::cerr << "Error parsing JSON in file: " << file_path << std::endl;
	}

	return data;
#endif
}

/* convert \\ in file path to \ (??) */ 
// not sure
/* What this function is actually doing is to convert \ to \\ */
std::string pathTidy(const std::string& input) {
    size_t input_length = input.length();
    std::string output;
    output.reserve(input_length * 2); // Reserve space for worst-case scenario

    for (size_t i = 0; i < input_length; i++) {
        if (input[i] == '\\') {
            output += '\\'; // Add escape character
            output += '\\'; // Add additional backslash
        } else {
            output += input[i]; // Copy character as is
        }
    }
    return output;
}

/* Validate example in directory_path and returns example path */
std::string validateINO(const std::string& directory_path) {
#if _WIN32
	if (PRINT_DEBUG) std::cout << "[" << __func__ << "][INFO] directory_path: " << directory_path << std::endl;
	if (PRINT_DEBUG) std::cout << "[" << __func__ << "][INFO] path_build_options_json: " << path_build_options_json << std::endl;

	std::wstring directory_path_utf16 = utf8_to_utf16(directory_path);
	std::wstring path_build_options_json_utf16 = utf8_to_utf16(path_build_options_json);

	// Convert wide-character path back to UTF-8 for cJSON functions
	int path_build_path_len = WideCharToMultiByte(CP_UTF8, 0, path_build_options_json_utf16.c_str(), -1, nullptr, 0, nullptr, nullptr);
	std::string path_build_path(path_build_path_len, '\0');
	WideCharToMultiByte(CP_UTF8, 0, path_build_options_json_utf16.c_str(), -1, &path_build_path[0], path_build_path_len, nullptr, nullptr);

	// Load and parse build.options.json
	cJSON* data = loadTempJSONFile(path_build_path.c_str());
	if (!data) {
		std::cerr << "[" << __func__ << "][Error] Failed to load JSON file: " << path_build_path << std::endl;
		return "";
	}
#if PRINT_DEBUG
	char * jsonString = cJSON_Print(data);
	std::string jsonData(jsonString);
	free(jsonString);
	std::cout << "JSON Data: " << jsonData << std::endl;
#endif
	cJSON* path_example = cJSON_GetObjectItem(data, "sketchLocation"); // Extract the contents in sketchLocation
	std::string path2 = getUsernameChecked(pathTidy(path_example->valuestring));
#if PRINT_DEBUG
	std::cout << "[" << __func__ << "][INFO] Current example path2: " << path2 << std::endl;
#endif
	return path2; // Get the value represented as string from path example

#else
	cJSON* data = loadTempJSONFile(path_build_options_json.c_str()); // load build.options.json
#if PRINT_DEBUG
		char * jsonString = cJSON_Print(data);
		std::string jsonData(jsonString);
		free(jsonString);
		std::cout << "JSON Data: " << jsonData << std::endl;
#endif
    	cJSON* path_example = cJSON_GetObjectItem(data, "sketchLocation"); // Extract the contents in sketchLocation
#if PRINT_DEBUG
    	std::cout << "[" << __func__ << "][INFO] Current example path2: " << pathTidy(path_example->valuestring) << std::endl;
#endif
    	return pathTidy(path_example->valuestring); // Get the value represented as string from path example
#endif	
}

void removeChar(std::string& str, char c) {
	size_t len = str.length();
	size_t j = 0;
	for (size_t i = 0; i < len; i++) {
        if (str[i] != c) {
            str[j++] = str[i];
        }
    }
	str.erase(j); // Erase the characters beyond the new length
}

// search for the first file found matching the criteria which is path having the exampleName.
// Return directory of example
std::string listExampleDir(const std::string& basePath, const std::string& exampleName) {
#ifdef _WIN32
	std::string path = basePath;
	std::string folder_example;
	
	std::wstring basePathUtf16 = utf8_to_utf16(basePath);
    std::wstring exampleNameUtf16 = utf8_to_utf16(exampleName);
    std::wstring path_utf16 = utf8_to_utf16(path);

    WIN32_FIND_DATAW findData;
    HANDLE hFind = FindFirstFileW((basePathUtf16 + L"\\*").c_str(), &findData);
    
    if (hFind == INVALID_HANDLE_VALUE) {
        DWORD error = GetLastError();
        std::cerr << "1 Failed to open directory: " << error << std::endl;
        return "Failed to open directory.";
    }
	
    do {
		if ((findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) &&
            wcscmp(findData.cFileName, L".") != 0 && wcscmp(findData.cFileName, L"..") != 0) {
			//if (PRINT_DEBUG) std::wcout << findData.cFileName << std::endl;
			std::wstring currentFileName = findData.cFileName;
			std::wstring currentPath = basePathUtf16  + L"\\" + currentFileName;

			// Check if exampleName is part of the currentFileName
			if (currentFileName.find(exampleNameUtf16) != std::wstring::npos) {
				folder_example = convert_to_utf8(currentPath);
			}

			// Recursively search within current directory
			std::string foundPath = listExampleDir(convert_to_utf8(currentPath), exampleName);
			if (!foundPath.empty()) {
				folder_example = foundPath;
			}
	    }
	} while (FindNextFileW(hFind, &findData) != 0);

    FindClose(hFind);
	
 	return folder_example;
#else
	std::string path = basePath + backspace;
    DIR* dir = opendir(path.c_str());
    struct dirent* dp;
 
    if (!dir)
        return "";
 
    while ((dp = readdir(dir)) != NULL) {
        if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0) { // skip entries in current directory and parent directory
            std::string currentFileName = dp->d_name;
            std::string currentPath = path + currentFileName;
 
            if (currentFileName.find(exampleName) != std::string::npos &&
                currentFileName.substr(currentFileName.length() - exampleName.length()) == exampleName) {
                folder_example = currentPath.c_str();
				closedir(dir);
				return folder_example;
            }
 
            std::string foundPath = listExampleDir(currentPath, exampleName); // continue until the first file with matching criteria is found.
			if (!foundPath.empty()) {
				closedir(dir);
				return foundPath;
			}
	    }
    }
    closedir(dir);
	return "";
#endif
}

// check IDE version and get the file path for example
std::string getIDEFilePath (const std::string &path) {
#ifdef _WIN32
	WIN32_FIND_DATAW findFileData;
    HANDLE hFind;

	// Check if the directory path itself contains a .ino file
	//std::cout << "Found .ino file directly in directory path: " << path << std::endl;
	if (std::string(path).find(".ino") == std::string::npos) {
		// IDE2 creates temp dir
		if (PRINT_DEBUG) std::cout << "[" << __LINE__ << "] IDE2" << std::endl;

			// Construct search path as directory_path + L"\\*.ino"
		std::wstring search_path = utf8_to_utf16(path) + L"\\*.ino";
		hFind = FindFirstFileW(search_path.c_str(), &findFileData);
		if (hFind == INVALID_HANDLE_VALUE) {
			std::cerr << "Unable to find .ino file in directory: " << convert_to_utf8(utf8_to_utf16(path)) << std::endl;
			return "";
		}

		// Iterate through all .ino files in the directory
		std::string file_path = path + "\\" + convert_to_utf8(findFileData.cFileName);
		//std::cout << "Found .ino file: " << file_path << std::endl;
		FindClose(hFind);

		return file_path;
	} else {
		// IDE1 creates temp file
        if (PRINT_DEBUG) std::cout << "[" << __LINE__ << "] IDE1" << std::endl;

		// unmodified example
        std::string file_path = std::string(path); // example directory path
		if (PRINT_DEBUG) std::cout << "[" << __LINE__ << "] file_path: " << file_path << std::endl; 
		
		// modified example
		if (std::string(path).find("modified") != std::string::npos) {
#ifdef _WIN32
			std::string example_name = path.substr(path.find_last_of("\\") + 1);
			removeChar(example_name, '\\');	
#else
			std::string example_name = path.substr(path.find_last_of("/") + 1);
			removeChar(example_name, '/');	
#endif
			//file_path = listExampleDir(path_library, example_name); // return example directory path
			//if (PRINT_DEBUG) std::cout << "[" << __LINE__ << "] 123" << std::endl;
			if (PRINT_DEBUG) std::cout << "[" << __LINE__ << "] file_path: " << file_path << std::endl;
			return file_path;
		}
		return file_path;
	}
#else
	// check IDE Version
	std::string file_path;

    if (std::string(path).find(".ino") == std::string::npos) {
        // IDE2 creates temp dir
        if (PRINT_DEBUG) std::cout << "[" << __LINE__ << "] IDE2" << std::endl;
		DIR* dir;
		struct dirent* entry;
		dir = opendir(path.c_str());

		if (dir == NULL) {
			std::cout << "[" << __LINE__ << "] Unable to open directory: " << path << std::endl;
		}
		while ((entry = readdir(dir)) != nullptr) {
			if (entry->d_type == DT_REG) {
				if (std::string(entry->d_name).find(".ino") != std::string::npos) { 
					file_path = std::string(path) + backspace + entry->d_name; // return example directory path
                    if (PRINT_DEBUG) std::cout << "[" << __LINE__ << "] file_path: " << file_path << std::endl;
					return file_path;
					break;
				}
			}
		}
		closedir(dir);
		return "";
    }
    else {
        // IDE1 creates temp file
        if (PRINT_DEBUG) std::cout << "[" << __LINE__ << "] IDE1" << std::endl;

		// unmodified example
        file_path = std::string(path); // example directory path
		if (PRINT_DEBUG) std::cout << "[" << __LINE__ << "] file_path: " << file_path << std::endl; 
		
		// modified example
		if (std::string(path).find("modified") != std::string::npos) {

		std::string example_name = path.substr(path.find_last_of("/") + 1);
		removeChar(example_name, '/');	

		//file_path = listExampleDir(path_library, example_name); // return example directory path
		if (PRINT_DEBUG) std::cout << "[" << __LINE__ << "] file_path: " << file_path << std::endl;
		return file_path;
		}
		return file_path;
    }
#endif
}

std::string input2nbfile(const std::string& input) {
std::string input_new, input_lower;
    
#if __APPLE__
    std::string input_no_spaces = input;
    input_no_spaces.erase(std::remove_if(input_no_spaces.begin(), input_no_spaces.end(), ::isspace), input_no_spaces.end());
    input_new = input_no_spaces;
    
    std::unordered_map<std::string, std::string> model_mapping;
    model_mapping.insert(std::make_pair("yolov3_tiny", "yolov3_tiny.nb"));
    model_mapping.insert(std::make_pair("yolov4_tiny", "yolov4_tiny.nb"));
    model_mapping.insert(std::make_pair("yolov7_tiny", "yolov7_tiny.nb"));
    model_mapping.insert(std::make_pair("mobilefacenet_i8", "mobilefacenet_int8.nb"));
    model_mapping.insert(std::make_pair("mobilefacenet_i16", "mobilefacenet_int16.nb"));
    model_mapping.insert(std::make_pair("scrfd320p", "scrfd_500m_bnkps_576x320_u8.nb"));
    model_mapping.insert(std::make_pair("scrfd640", "scrfd_500m_bnkps_640x640_u8.nb"));
    model_mapping.insert(std::make_pair("yamnet_fp16", "yamnet_fp16.nb"));
    model_mapping.insert(std::make_pair("img_class", "img_class_cnn.nb"));
#else
    std::unordered_map<std::string, std::string> model_mapping = {
        {"yolov3_tiny", "yolov3_tiny.nb"},
        {"yolov4_tiny", "yolov4_tiny.nb"},
        {"yolov7_tiny", "yolov7_tiny.nb"},
        {"mobilefacenet_i8", "mobilefacenet_int8.nb"},
        {"mobilefacenet_i16", "mobilefacenet_int16.nb"},
        {"scrfd320p", "scrfd_500m_bnkps_576x320_u8.nb"},
        {"scrfd640", "scrfd_500m_bnkps_640x640_u8.nb"},
        {"yamnet_fp16", "yamnet_fp16.nb"},
        {"img_class", "img_class_cnn.nb"},
    };
#endif
    
    // Convert input string to lowercase for case-insensitive comparison
#if __APPLE__
    input_lower = input_new;
#else
    input_lower = input;
#endif
    
    std::transform(input_lower.begin(), input_lower.end(), input_lower.begin(), ::tolower);
 
    for (const auto& pair : model_mapping) {
        std::string key_lower = pair.first;
        std::transform(key_lower.begin(), key_lower.end(), key_lower.begin(), ::tolower);
 
        if (input_lower == key_lower) {
            return pair.second;
        }
    }
    return "NA";
}

std::string extractRootDirectory(const std::string& filepath) {
#ifdef _WIN32
    size_t lastSeparator = filepath.find_last_of("\\"); // find last occurrence of either '/' or '\'
#else
	size_t lastSeparator = filepath.find_last_of("/"); // find last occurrence of either '/' or '\'
#endif
    if (lastSeparator == std::string::npos) {
        rootDir = ""; // set as empty string if not found
        return "";
    }
    rootDir = filepath.substr(0, lastSeparator + 1);
	return rootDir;
}

#include <chrono>
#include <iomanip>  // for std::put_time
std::string dspFileProp(const std::string& filename) {
#ifdef _WIN32
    // Convert filename to wide-character string for Windows API
    std::wstring filename_utf16 = utf8_to_utf16(filename);

    // Get a handle to the file
    HANDLE hFile = CreateFileW(filename_utf16.c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile == INVALID_HANDLE_VALUE) {
        DWORD error = GetLastError();
        if (error == ERROR_FILE_NOT_FOUND || error == ERROR_PATH_NOT_FOUND) {
            std::cerr << "[Error][" << __LINE__ << "] Default model " << filename << " does not exist. Please check " << filename << " again." << std::endl;
        } else {
            std::cerr << "[Error][" << __LINE__ << "] Error opening file " << filename << ". Error code: " << error << std::endl;
        }
        exit(1);
    }

    // Get file creation time
    FILETIME ftCreate, ftAccess, ftWrite;
    if (!GetFileTime(hFile, &ftCreate, &ftAccess, &ftWrite)) {
        std::cerr << "[Error][" << __LINE__ << "] Error getting file time for " << filename << ". Error code: " << GetLastError() << std::endl;
        CloseHandle(hFile);
        exit(1);
    }

    CloseHandle(hFile);

    // Convert FILETIME to SYSTEMTIME
    SYSTEMTIME stUTC, stLocal;
    FileTimeToSystemTime(&ftCreate, &stUTC);
    SystemTimeToTzSpecificLocalTime(nullptr, &stUTC, &stLocal);

    // Format the file creation time
    std::stringstream ss;
    ss << std::setfill('0') << std::setw(4) << stLocal.wYear << "-"
       << std::setfill('0') << std::setw(2) << stLocal.wMonth << "-"
       << std::setfill('0') << std::setw(2) << stLocal.wDay;

    if (PRINT_DEBUG) std::cout << "[INFO] File creation date: " << ss.str() << std::endl;
    return ss.str();

#else
    struct stat fileModelStats;
	
	std::cout << "filename: " << filename << std::endl; 

    if (stat(filename.c_str(), &fileModelStats) == -1) {
        std::cerr << "[Error][" << __LINE__ << "] Default model " << filename << " does not exist. Please check " << filename << " again." << std::endl;
        exit(1);
    }
 
    time_t fileCreationTime = fileModelStats.st_mtime; // Get the file creation time
    char fileCreationDate[11]; // Format the file creation time
    strftime(fileCreationDate, sizeof(fileCreationDate), "%Y-%m-%d", localtime(&fileCreationTime));
    if (PRINT_DEBUG) std::cout << "[INFO] File creation date: " << fileCreationDate << std::endl;
    return std::string(fileCreationDate);
#endif
}

void copyFile(const std::string& sourcePath, const std::string& destinationPath) {
#if _WIN32
	HANDLE hSourceFile, hDestinationFile;
    DWORD bytesRead, bytesWritten;
    BYTE buffer[BUFFER_SIZE];
	std::wstring sourcePath_utf16 = utf8_to_utf16(sourcePath);
	std::wstring destinationPath_utf16 = utf8_to_utf16(destinationPath);
    // Open the source file for reading
    hSourceFile = CreateFileW(sourcePath_utf16.c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hSourceFile == INVALID_HANDLE_VALUE) {
        if (PRINT_DEBUG) std::cout << "[Wrn][" << __LINE__ << "] Failed to open the source file:" << sourcePath << std::endl;
        return;
    }

    // Open the destination file for writing
    hDestinationFile = CreateFileW(destinationPath_utf16.c_str(), GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hDestinationFile == INVALID_HANDLE_VALUE) {
        if (PRINT_DEBUG) std::cout << "[Wrn][" << __LINE__ << "] Failed to create the destination file:" << destinationPath << std::endl;
        CloseHandle(hSourceFile);
        return;
    }

    // Copy data from source file to destination file
    while (ReadFile(hSourceFile, buffer, BUFFER_SIZE, &bytesRead, NULL) && bytesRead > 0) {
        WriteFile(hDestinationFile, buffer, bytesRead, &bytesWritten, NULL);
        if (bytesRead != bytesWritten) {
            if (PRINT_DEBUG) std::cout << "[Wrn][" << __LINE__ << "] Error writing to destination file:" << destinationPath << std::endl;
            break;
        }
    }

    // Close the files
    CloseHandle(hSourceFile);
    CloseHandle(hDestinationFile);
#else
	FILE* sourceFile;
	FILE* destinationFile;
	char buffer[BUFFER_SIZE];
	size_t bytesRead;

	// Open the source file for reading
	sourceFile = fopen(sourcePath.c_str(), "rb");
	if (sourceFile == NULL) {
		if (PRINT_DEBUG) std::cout << "[Wrn][" << __LINE__ << "] Failed to open the source file:" << sourcePath << std::endl;
		return;
	}

	// Open the destination file for writing
	destinationFile = fopen(destinationPath.c_str(), "wb");
	if (destinationFile == NULL) {
		if (PRINT_DEBUG) std::cout << "[Wrn][" << __LINE__ << "] Failed to create the destination file:" << destinationPath << std::endl;
		fclose(sourceFile);
		return;
	}

	// Copy data from source file to destination file
	while ((bytesRead = fread(buffer, 1, BUFFER_SIZE, sourceFile)) > 0) {
		fwrite(buffer, 1, bytesRead, destinationFile);
	}

    // Close the files
	fclose(sourceFile);
	fclose(destinationFile);
#endif
    if (PRINT_DEBUG) std::cout << "[" << __func__ << "][" << __LINE__ << "][INFO] File copied successfully: " << destinationPath << std::endl;
}

void revertModel(const std::string& dmodel_name, const std::string& dmodel_name_backup, const std::string& dmodel_path) {
    std::string source_path = dmodel_path + backspace + dmodel_name_backup;
    std::string destination_path = dmodel_path + backspace + dmodel_name;
	
	if (PRINT_DEBUG) std::cout << "[" << __func__ << "][INFO] source_path:" << source_path << std::endl;
	if (PRINT_DEBUG) std::cout << "[" << __func__ << "][INFO] destination_path:" << destination_path << std::endl;

    copyFile(source_path.c_str(), destination_path.c_str());
 
    if (PRINT_DEBUG) std::cout << "[" << __func__ << "][INFO] Dmodel Revert done." << std::endl;
}

void readTXT(std::string& directory_path) {
	int str_count = 0;
#if _WIN32
    std::wstring directory_path_utf16 = utf8_to_utf16(directory_path)  + L"\\" + utf8_to_utf16(filename_txt);
    
    // Open the file
	HANDLE hFile = CreateFileW(directory_path_utf16.c_str(), GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
	if (hFile == INVALID_HANDLE_VALUE) {
		DWORD error = GetLastError();
		if (error == ERROR_FILE_NOT_FOUND) {
			std::cout << "ino_validation.txt not found in directory." << std::endl;
			if (PRINT_DEBUG) std::cout << "[" << __func__ << "][" << __LINE__ << "][INFO] JSON reset done" << std::endl;
		} else {
			std::cerr << "Failed to open ino_validation.txt: " << error << std::endl;
		}
		return;
	}

    // Get the file size
	DWORD fileSize = GetFileSize(hFile, nullptr);
	if (fileSize == INVALID_FILE_SIZE) {
		std::cerr << "Failed to get file size: " << GetLastError() << std::endl;
		CloseHandle(hFile);
		return;
	}

	// Allocate buffer for file content
	std::vector<char> fileContents(fileSize + 1); // +1 for null terminator

	// Read file content
	DWORD bytesRead;
	if (!ReadFile(hFile, &fileContents[0], fileSize, &bytesRead, nullptr)) {
		std::cerr << "Failed to read file: " << GetLastError() << std::endl;
		CloseHandle(hFile);
		return;
	}

	// Close the file handle
	CloseHandle(hFile);

	// Null-terminate the content
	fileContents[fileSize] = '\0';

    // Convert char buffer to std::string
    std::string content(fileContents.begin(), fileContents.end());

	// Print or process the file content
	if (PRINT_DEBUG) std::cout << "TXT File content:" << std::endl;
	if (PRINT_DEBUG) std::cout << &fileContents[0] << std::endl; // Assuming file contains text data
    
	//std::vector<std::string> ino_name_buf; // Vector to store lines from the file
    std::istringstream txtcontent(content);
	std::string line;
    while (std::getline(txtcontent, line)) {
        ino_name_buf.push_back(line);
    }

	// Close the file handle after reading		
	CloseHandle(hFile);

    // Assigning values to variables based on file content
    nn_model_yolotiny_name = ino_name_buf[2];
    nn_model_srcfd_name = ino_name_buf[3];
    nn_model_mobilefacenet_name = ino_name_buf[4];
    nn_model_yamnet_name = ino_name_buf[5];
    nn_model_imgclass_name = ino_name_buf[6];

    nn_default_customized_yolotiny = ino_name_buf[9];
    nn_default_customized_srcfd = ino_name_buf[10];
    nn_default_customized_mobilefacenet = ino_name_buf[11];
    nn_default_customized_yamnet = ino_name_buf[12];
    nn_default_customized_imgclass = ino_name_buf[13];

	if (PRINT_DEBUG) std::cout << "nn_model_yolotiny_name: " << nn_model_yolotiny_name << std::endl; 
	if (PRINT_DEBUG) std::cout << "nn_default_customized_yolotiny: " << nn_default_customized_yolotiny << std::endl;  
#else
    // Open directory and check for errors
    DIR* dir = opendir(directory_path.c_str());
    if (dir == nullptr) {
        std::cerr << "Failed to open directory: " << strerror(errno) << std::endl;
    }

    struct stat st;
    // Create directory if it doesn't exist
    if (stat(directory_path.c_str(), &st) == -1) {
        if (mkdir(directory_path.c_str(), 0700) == -1) {
            std::cerr << "Failed to create directory: " << strerror(errno) << std::endl;
            closedir(dir); // Ensure to close the directory if directory creation fails
        }
    }

    // Form the complete file path
    std::string file_path = directory_path + filename_txt;
    //std::cout << "file_path: " << file_path << std::endl;

    // Open file
    std::ifstream ino_validation_txt(file_path);
    if (!ino_validation_txt.is_open()) {
        std::cerr << "Failed to open file: " << file_path << std::endl;
        closedir(dir); // Close the directory if file opening fails
    }

    // Use a dynamic vector to store lines
    // std::vector<std::string> ino_name_buf;
    std::string line;

    // Read lines from file
    while (std::getline(ino_validation_txt, line)) {
        ino_name_buf.push_back(line);
    }

    // Close the file
    ino_validation_txt.close();

    // Check if there are enough lines in the vector
    
    // Access vector elements safely
    nn_model_yolotiny_name = ino_name_buf[2];
    nn_model_srcfd_name = ino_name_buf[3];
    nn_model_mobilefacenet_name = ino_name_buf[4];
    nn_model_yamnet_name = ino_name_buf[5];
    nn_model_imgclass_name = ino_name_buf[6];

    nn_default_customized_yolotiny = ino_name_buf[9];
    nn_default_customized_srcfd = ino_name_buf[10];
    nn_default_customized_mobilefacenet = ino_name_buf[11];
    nn_default_customized_yamnet = ino_name_buf[12];
    nn_default_customized_imgclass = ino_name_buf[13];
    
    // Close the directory
    closedir(dir);
#endif
}

void renameFile(const std::string& filename, const std::string& filepath, int type) {
std::string file_path;
    if (type == 1) { // Backup Dmodel
        // Original model filename
        pathModel = path_model + filename;
		if (PRINT_DEBUG) std::cout << "[" << __LINE__ << "][INFO] pathModel: " << pathModel << std::endl;
	
        // Construct the modified model filename
		if (PRINT_DEBUG) std::cout << "[" << __func__ << "][" << __LINE__ << "][INFO]  dspFileProp(pathModel) " <<  dspFileProp(pathModel) << std::endl;
		if (PRINT_DEBUG) std::cout << "[" << __func__ << "][" << __LINE__ << "][INFO]  pathModel: " <<  pathModel << std::endl;

        filenameModified = "Dbackup_" + dspFileProp(pathModel) + "_" + filename;
        sourcePath = pathModel;
        destinationPath = path_model + backspace + filenameModified;

		// Copying file from source path to dest path
        copyFile(sourcePath, destinationPath);
  		if (PRINT_DEBUG) std::cout << "[INFO] Dmodel Backup done." << std::endl;
		
    } else { // Backup Cmodel
		if (filepath.find("modified") != std::string::npos) {
			if (PRINT_DEBUG) std::cout << "[INFO] 1." << std::endl;
			file_path = filepath + filename;
			std::string filenameModified = "Cbackup_" + dspFileProp(file_path) + "_" + filename;
			sourcePath = file_path;
			destinationPath = path_model + backspace + filenameModified;
		} else {
			if (PRINT_DEBUG) std::cout << "[INFO] 2." << std::endl;
			file_path = filepath;
			if (PRINT_DEBUG) std::cout << "[INFO] file_path: " << file_path << std::endl;
			
			std::string filenameModified = "Cbackup_" + dspFileProp(file_path + backspace + filename) + "_" + filename;
			if (PRINT_DEBUG) std::cout << "[INFO] filenameModified: " << filenameModified << std::endl;
			sourcePath = file_path + backspace + filename;
			if (PRINT_DEBUG) std::cout << "[INFO] sourcePath: " << sourcePath << std::endl;
			destinationPath = path_model + backspace + filenameModified;
			if (PRINT_DEBUG) std::cout << "[INFO] destinationPath: " << destinationPath << std::endl;

			copyFile(sourcePath, destinationPath);
  			if (PRINT_DEBUG) std::cout << "[INFO] Cmodel Backup done." << std::endl;
		}

		// Copying file from source path to dest path
		//copyFile(sourcePath, destinationPath);
		if (PRINT_DEBUG) std::cout << "[" << __func__ << "][INFO] sourcePath:" << sourcePath << std::endl;
		if (PRINT_DEBUG) std::cout << "[" << __func__ << "][INFO] destinationPath:" << destinationPath << std::endl;

		// replace model
		destinationPath2 = path_model + backspace + filename;

		// // Copying file from source path to dest path
		copyFile(sourcePath, destinationPath2);

		if (PRINT_DEBUG) std::cout << "[INFO] Cmodel Copy done." << std::endl;
	} 
}

void modelRenameBackup(const std::string& nbfilename, const std::string& sketchPath) {
	std::string fname_models_txt[5] = {nn_model_yolotiny_name, nn_model_srcfd_name, nn_model_mobilefacenet_name, nn_model_yamnet_name, nn_model_imgclass_name};
	std::string filename_keyword[7] = {yolov3_model, yolov4_model, yolov7_model, scrfd_model, mobilefacenet_model, yamnet_model, cnn_model};
	int file_count = 0;

#ifdef _WIN32
	if (PRINT_DEBUG) std::cout << "[" << __LINE__ << "][INFO] path_model: \"" << path_model << "\"" << std::endl;
	if (PRINT_DEBUG) std::cout << "[" << __LINE__ << "][INFO] nbfilename: \"" << nbfilename << "\"" << std::endl;
	
	
	std::wstring path_model_utf16 = utf8_to_utf16(path_model);

	// Open dir_example path
	WIN32_FIND_DATAW findData;
	HANDLE hFind = FindFirstFileW((path_model_utf16 + L"\\*").c_str(), &findData);

	if (hFind == INVALID_HANDLE_VALUE) {
		DWORD error = GetLastError();
		std::cerr << "2 Failed to open directory: " << error << std::endl;
	}

	do {
		std::wstring fileName = findData.cFileName;
		if (PRINT_DEBUG) std::wcout << "123 fileName: " << fileName << std::endl;
		if (fileName.find(L"Dbackup_") != std::wstring::npos) {
			if (PRINT_DEBUG) std::cout << "[" << __LINE__ << "][INFO] nbfilename:  " << nbfilename << std::endl;
			if (convert_to_utf8(fileName).find(nbfilename) != std::string::npos) {
				if (PRINT_DEBUG) std::cout << "[INFO] Backup-ed " << "Dbackup_" + nbfilename << " found !!!" << std::endl;
				flag_Dbackup = true;
				file_count++;
				break;
			}
		}

	} while (FindNextFileW(hFind, &findData) != 0);
	FindClose(hFind);
	
	if (PRINT_DEBUG) std::cout << "[" << __LINE__ << "][INFO] file_count:  " << file_count << std::endl;
	// Check customized model backup status
    if (flag_Dbackup) {
		if (PRINT_DEBUG) std::cout << "[" << __LINE__ << "][INFO] flag_Dbackup  = 1" << std::endl;
		if (PRINT_DEBUG) std::cout << "[" << __LINE__ << "][INFO] nbfilename: " << nbfilename << std::endl;
		if (PRINT_DEBUG) std::cout << "[" << __LINE__ << "][INFO] sketchPath: " << sketchPath << std::endl;
        renameFile(nbfilename, sketchPath, 0); // Backup Cmodel
    } else {
		if (PRINT_DEBUG) std::cout << "[" << __LINE__ << "][INFO] flag_Dbackup  = 0" << std::endl;
		if (PRINT_DEBUG) std::cout << "[" << __LINE__ << "][INFO] nbfilename: " << nbfilename << std::endl;
		if (PRINT_DEBUG) std::cout << "[" << __LINE__ << "][INFO] sketchPath: " << sketchPath << std::endl;
        renameFile(nbfilename, sketchPath, 1); // Backup Dmodel
        renameFile(nbfilename, sketchPath, 0); // Backup Cmodel
    }

#else
	DIR* dir;
    struct dirent* entry;
 	if (PRINT_DEBUG) std::cout << "[" << __LINE__ << "][INFO] path_model: \"" << path_model << "\"" << std::endl;
	if (PRINT_DEBUG) std::cout << "[" << __LINE__ << "][INFO] nbfilename: \"" << nbfilename << "\"" << std::endl;
	flag_Dbackup = false;
	// Check default model backup status
	if ((dir = opendir(path_model.c_str())) == nullptr) {
        perror("opendir() error");
        std::cerr << "[Error] Failed to open dir at: " << path_model << std::endl;
        exit(1);
    } else {
        while ((entry = readdir(dir)) != nullptr) {
			std::string filename = entry->d_name;
			if (PRINT_DEBUG) std::cout << "[" << __LINE__ << "][INFO] filename:  " << filename << std::endl;
			
			if (filename.find("Dbackup_") != std::string::npos) {
				if (PRINT_DEBUG) std::cout << "[" << __LINE__ << "][INFO] nbfilename:  " << nbfilename << std::endl;
				if (filename.find(nbfilename) != std::string::npos) {
					if (PRINT_DEBUG) std::cout << "[INFO] Backup-ed " << "Dbackup_" + nbfilename << " found !!!" << std::endl;
					flag_Dbackup = true;
					file_count++;
					break;
				}
			}
        }
        closedir(dir);
    }

	if (PRINT_DEBUG) std::cout << "[" << __LINE__ << "][INFO] file_count:  " << file_count << std::endl;
	// Check customized model backup status
    if (flag_Dbackup) {
		if (PRINT_DEBUG) std::cout << "[" << __LINE__ << "][INFO] flag_Dbackup  = 1" << std::endl;
        renameFile(nbfilename, sketchPath, 0); // Backup Cmodel
    } else {
		if (PRINT_DEBUG) std::cout << "[" << __LINE__ << "][INFO] flag_Dbackup  = 0" << std::endl;
        renameFile(nbfilename, sketchPath, 1); // Backup Dmodel
        renameFile(nbfilename, sketchPath, 0); // Backup Cmodel
    }
#endif
}

// void backupModel(const std::string &path) {
// 	std::string model_name_od, model_name_fd, model_name_fr, model_name_ac, model_name_ic;
// 	std::string fname_models_txt[5] = {nn_model_yolotiny_name, nn_model_srcfd_name, nn_model_mobilefacenet_name, nn_model_yamnet_name, nn_model_imgclass_name};
// 	std::string models[] = {"OBJECT_DETECTION", "FACE_DETECTION", "FACE_RECOGNITION", "AUDIO_CLASSIFICATION", "IMAGE_CLASSIFICATION"};
// 	std::string model_names[NUMBER_OF_MODELS];
// 	std::string nn_task;
//     std::string voe_status = "NA";
//     std::string header_all = "";
// 	std::string line_strip_header = "NA";
// 	std::string line_strip_headerNN = "NA";
// 	std::string dir_example = "NA";
// 	std::string example_file_path;
// 	std::string ino_extension = ".ino";
// 	std::string fname_dmodel;
// 	std::string fname_dmodel_backup;
// 	std::string input, output;
	
// 	// All texts save to bufferContent
// 	std::string bufferContent;

// 	int count = 0;
// 	int count_match = 0;

// 	std::string example_name;

// 	example_file_path = getIDEFilePath(path);
// 	if (PRINT_DEBUG) std::cout << "[" << __LINE__ << "][INFO] path_example: \"" << example_file_path << "\"" << std::endl;

// #ifdef _WIN32
// 	std::wstring example_file_path_utf16 = utf8_to_utf16(example_file_path);

// 	// Open the file
//     HANDLE hFile = CreateFileW(example_file_path_utf16.c_str(), GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
//     if (hFile == INVALID_HANDLE_VALUE) {
//         DWORD error = GetLastError();
//         if (error == ERROR_FILE_NOT_FOUND) {
//             std::cout << "File not found: " << convert_to_utf8(example_file_path_utf16) << std::endl;
//         } else {
//             std::cerr << "Failed to open file: " << convert_to_utf8(example_file_path_utf16) << ". Error code: " << error << std::endl;
//         }
//         return;
//     }

// 	// Read file contents
//     const int BUFFER_SIZE_INO = 4096; // Example buffer size
//     std::vector<char> buffer(BUFFER_SIZE_INO);
//     DWORD bytesRead = 0;
//     BOOL success = FALSE;

// 	do {
//         success = ReadFile(hFile, buffer.data(), BUFFER_SIZE_INO, &bytesRead, nullptr);
//        if (success) {
//             // Process the read buffer
//             bufferContent.append(buffer.data(), bytesRead);
//         } else {
//             DWORD error = GetLastError();
//             std::cerr << "Error reading file: " << convert_to_utf8(example_file_path_utf16) << ". Error code: " << error << std::endl;
//         }
//     } while (success && bytesRead > 0);

//     // Close the file handle
//     CloseHandle(hFile);
// #else
// 	std::ifstream fmodel(example_file_path);
// 	if (fmodel.is_open()) {
//         std::string line;
		
// 		while (std::getline(fmodel, line)) {
// 			bufferContent += line + "\n"; // Append each line to bufferContent
// 		}
// 		fmodel.close();
// 	}  else {
//         std::cerr << "Unable to open file." << std::endl;
//     }
// #endif
// 	// Search for keywords and process lines containing them
// 	std::istringstream iss(bufferContent);
// 	std::string line;
	
// 	if (nn_default_customized_yolotiny == "CUSTOMIZED" || nn_default_customized_srcfd == "CUSTOMIZED" || nn_default_customized_mobilefacenet == "CUSTOMIZED" || nn_default_customized_yamnet == "CUSTOMIZED" || nn_default_customized_imgclass == "CUSTOMIZED") {
// 		if (load_nn_model_src == "LoadFromFlash") {
// 			if (PRINT_DEBUG) std::cout << "[" << __LINE__ << "] Path: " << path << std::endl;
// 			if (path == "Temp" || path.find("modified") != std::string::npos) {//path == "Temp" && path == "modified") {
// 				// IDE 1
// 				if (PRINT_DEBUG) std::cout << "[" << __LINE__ << "] IDE1" << std::endl;
// 				dir_example = extractRootDirectory(path);
// 			} else {
// 				if (PRINT_DEBUG) std::cout << "[" << __LINE__ << "] IDE2" << std::endl;
// 				// IDE 2
// 				example_name = path.substr(path.find_last_of("\\") + 1);
// 				removeChar(example_name, '\\');
// 			}
// 			std::string folder_example = listExampleDir(path_library, example_name); // return example directory path
// 			dir_example = folder_example;
// 			if (PRINT_DEBUG) std::cout << "[" << __LINE__ << "] dir_example: " << dir_example << std::endl;
		
// #ifdef _WIN32
// 			// Open dir_example path
// 			WIN32_FIND_DATAW findData;
// 			HANDLE hFind = FindFirstFileW((utf8_to_utf16(dir_example) + L"\\*").c_str(), &findData);

// 			if (hFind == INVALID_HANDLE_VALUE) {
// 				DWORD error = GetLastError();
// 				std::cerr << "3 Failed to open directory: " << error << std::endl;
// 			}

// 			do {
// 				if (!(findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
// 					std::wstring fileName = findData.cFileName;
// 					if (fileName.length() > 3 && fileName.substr(fileName.length() - 3) == L".nb") {
// 						std::string fileName_utf8 = convert_to_utf8(fileName);

// 						if (fileName_utf8 != input2nbfile(nn_model_yolotiny_name) && fileName_utf8 != input2nbfile(nn_model_srcfd_name) && fileName_utf8 !=  input2nbfile(nn_model_mobilefacenet_name) && fileName_utf8 !=  input2nbfile(nn_model_yamnet_name) && fileName_utf8 !=  input2nbfile(nn_model_imgclass_name)) {
// 							std::cerr << "Customized model mismatch. Please rename your model." << std::endl;
// 							exit(EXIT_FAILURE);
// 						} else {
// 							if (PRINT_DEBUG) std::cout << "[" << __LINE__ << "] [Info] Found customized model:  " << fileName_utf8 << " in " << dir_example << std::endl;
// 							modelRenameBackup(fileName_utf8, dir_example);
// 						}
// 						count_match++;
// 					}	
// 				}
// 			} while (FindNextFileW(hFind, &findData) != 0);
// 			FindClose(hFind);
// #else
// 			DIR* dir = opendir(dir_example.c_str());
// 			struct dirent* entry;
// 			if (dir != nullptr) {
// 				while ((entry = readdir(dir)) != nullptr) {
// 					std::string filename = entry->d_name;
// 					if (PRINT_DEBUG) std::cout << "[" << __LINE__ << "] filename: " << filename << std::endl;
					
// 					if (filename.find(".nb") != std::string::npos) {
// 						if (filename != input2nbfile(nn_model_yolotiny_name) && filename != input2nbfile(nn_model_srcfd_name) && filename !=  input2nbfile(nn_model_mobilefacenet_name) && filename !=  input2nbfile(nn_model_yamnet_name) && filename !=  input2nbfile(nn_model_imgclass_name)) {
// 							std::cerr << "Customized model mismatch. Please rename your model." << std::endl;
// 							exit(EXIT_FAILURE);
// 						} else {
// 							if (PRINT_DEBUG) std::cout << "[" << __LINE__ << "] [Info] Found customized model:  " << entry->d_name << " in " << dir_example << std::endl;
// 							modelRenameBackup(entry->d_name, dir_example); // filename, example directory
// 						}
// 						count_match++;
// 					}
// 				}
// 			}
// 			closedir(dir);
// #endif
// 			if (PRINT_DEBUG) std::cout << "count: " << count << std::endl;
// 			if (PRINT_DEBUG) std::cout << "count_match: " << count_match << std::endl;
// 			if (count_match == 0) {
// 				if (load_nn_model_src == "LoadFromFlash") { 
// 					std::cerr << "Model (.nb file) missing or customized model name mismatch. Please include your customized model in sketch folder or rename your model if it is already in sketch folder." << std::endl;
// 					exit(EXIT_FAILURE);
// 				}
// 			}
// 		}
// 	} else {
// 		if (PRINT_DEBUG) std::cout << "[" << __LINE__ << "] path_model: " << path_model << std::endl;
// 		flag_Dbackup = false;
// #ifdef _WIN32
// 	std::wstring path_model_utf16 = utf8_to_utf16(path_model);

// 	// Open dir_example path
// 	WIN32_FIND_DATAW findData;
// 	HANDLE hFind = FindFirstFileW((path_model_utf16 + L"\\*").c_str(), &findData);

// 	if (hFind == INVALID_HANDLE_VALUE) {
// 		DWORD error = GetLastError();
// 		std::cerr << "4 Failed to open directory: " << error << std::endl;
// 	}

// 	do {
// 		if (!(findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
// 			std::wstring fileName = findData.cFileName;
// 			if (PRINT_DEBUG) std::wcout << "1487 fileName: " << fileName << std::endl;

// 			if (fileName.find(L"Dbackup_") != std::string::npos) {
// 				if (PRINT_DEBUG) std::wcout << "[" << __LINE__ << "] filename: " << fileName << std::endl;
// 				flag_Dbackup = true;
// 				fname_dmodel_backup = convert_to_utf8(fileName);

// 				std::string fileName_utf8 = convert_to_utf8(fileName);

// 				if (fileName_utf8.find(yolov3_model) != std::string::npos || fileName_utf8.find(yolov4_model) != std::string::npos || fileName_utf8.find(yolov7_model) != std::string::npos ) {
// 					input = nn_model_yolotiny_name;
// 				} else if (fileName_utf8.find(scrfd_model) != std::string::npos) {
// 					input = nn_model_srcfd_name;
// 				} else if (fileName_utf8.find(mobilefacenet_model) != std::string::npos) {
// 					input = nn_model_mobilefacenet_name;
// 				} else if (fileName_utf8.find(yamnet_model) != std::string::npos) {
// 					input = nn_model_yamnet_name;
// 				}  else if (fileName_utf8.find(cnn_model) != std::string::npos) {
// 					input = nn_model_imgclass_name;
// 				} else {
// 					std::cerr << "Customized model mismatch. Please rename your model." << std::endl;
// 					exit(EXIT_FAILURE);
// 				}

// 				auto underscore = input.find('_'); // Find the first occurrence of "_"
// 				if (underscore != std::string::npos) {
// 					output = input.substr(0, underscore); // Copy the substring before "_"
// 					if (output == cnn_key) { // because the name in json does not contain cnn
// 						output = cnn_model; 
// 					}
// 				} else {
// 					output = input;
// 				}

// 				if (PRINT_DEBUG) std::cout << "[" << __LINE__ << "] output: " << output << std::endl;

// 				// To prevent wrong file used to replace default model.
// 				if (output != "NA") {						
// 					if (output.find(yolov3_model) != std::string::npos) {
// 						output = yolov3_model;
// 					} if (output.find(yolov4_model) != std::string::npos) {
// 						output = yolov4_model;
// 					} if (output.find(yolov7_model) != std::string::npos) {
// 						output = yolov7_model;
// 					} else if (output.find(scrfd_model) != std::string::npos) {
// 						output = scrfd_model;
// 					} else if (output.find(mobilefacenet_model) != std::string::npos) {
// 						output = mobilefacenet_model;
// 					} else if (output.find(yamnet_model) != std::string::npos) {
// 						output = yamnet_model;
// 					}  else if (output.find(cnn_model) != std::string::npos) {
// 						output = cnn_model;
// 					}

// 					std::string key = "_";
// 					key = key + output;
// 					auto start = fname_dmodel_backup.find(key); // Find the starting position of the substring

// 					if (start != std::string::npos) {
// 						key = key + "_";
// 						start += key.length(); // Move the pointer past the substring
// 						if (PRINT_DEBUG) std::cout << "[" << __LINE__ << "] output: " << output << std::endl;
// 						output = output + "_";
// 						if (PRINT_DEBUG) std::cout << "[" << __LINE__ << "] output: " << output << std::endl;
// 						fname_dmodel = output;
// 						fname_dmodel = fname_dmodel + fname_dmodel_backup.substr(start);
// 					}

// 					if (flag_Dbackup) {
// 						//if (PRINT_DEBUG) std::cout << "[" << __LINE__ << "] fname_dmodel: " << fname_dmodel << std::endl;
// 						revertModel(fname_dmodel, fname_dmodel_backup, path_model);
// 					}
// 				}
// 			}
// 		}
// 	} while (FindNextFileW(hFind, &findData) != 0);
// 	FindClose(hFind);

// #else
// 	if (PRINT_DEBUG) std::cout << "[" << __LINE__ << "] path_model: " << path_model << std::endl;
// 	DIR* dir = opendir(path_model.c_str());
// 	flag_Dbackup = false;
// 	if (dir) {
// 		struct dirent* ent;
// 		while ((ent = readdir(dir)) != NULL) {
// 			std::string filename = ent->d_name;
// 			if ((filename.find("Dbackup") != std::string::npos) ) {
// 				if (PRINT_DEBUG) std::cout << "[" << __LINE__ << "] filename: " << filename << std::endl;
// 				flag_Dbackup = true;
// 				fname_dmodel_backup = ent->d_name;

// 				if (filename.find(yolov3_model) != std::string::npos || filename.find(yolov4_model) != std::string::npos || filename.find(yolov7_model) != std::string::npos ) {
// 					input = nn_model_yolotiny_name;
// 				} else if (filename.find(scrfd_model) != std::string::npos) {
// 					input = nn_model_srcfd_name;
// 				} else if (filename.find(mobilefacenet_model) != std::string::npos) {
// 					input = nn_model_mobilefacenet_name;
// 				} else if (filename.find(yamnet_model) != std::string::npos) {
// 					input = nn_model_yamnet_name;
// 				}  else if (filename.find(cnn_model) != std::string::npos) {
// 					input = nn_model_imgclass_name;
// 				} else {
// 					std::cerr << "Customized model mismatch. Please rename your model." << std::endl;
// 					exit(EXIT_FAILURE);
// 				}
				
// 				auto underscore = input.find('_'); // Find the first occurrence of "_"
// 				if (underscore != std::string::npos) {
// 					output = input.substr(0, underscore); // Copy the substring before "_"
// 					if (output == cnn_key) { // because the name in json does not contain cnn
// 						output = cnn_model; 
// 					}
// 				} else {
// 					output = input;
// 				}

// 				if (PRINT_DEBUG) std::cout << "[" << __LINE__ << "] output: " << output << std::endl;

// 				// To prevent wrong file used to replace default model.
// 				if (output != "NA") {						
// 					if (output.find(yolov3_model) != std::string::npos) {
// 						output = yolov3_model;
// 					} if (output.find(yolov4_model) != std::string::npos) {
// 						output = yolov4_model;
// 					} if (output.find(yolov7_model) != std::string::npos) {
// 						output = yolov7_model;
// 					} else if (output.find(scrfd_model) != std::string::npos) {
// 						output = scrfd_model;
// 					} else if (output.find(mobilefacenet_model) != std::string::npos) {
// 						output = mobilefacenet_model;
// 					} else if (output.find(yamnet_model) != std::string::npos) {
// 						output = yamnet_model;
// 					}  else if (output.find(cnn_model) != std::string::npos) {
// 						output = cnn_model;
// 					}

// 					std::string key = "_";
// 					key = key + output;
// 					auto start = fname_dmodel_backup.find(key); // Find the starting position of the substring

// 					if (start != std::string::npos) {
// 						key = key + "_";
// 						start += key.length(); // Move the pointer past the substring
// 						if (PRINT_DEBUG) std::cout << "[" << __LINE__ << "] output: " << output << std::endl;
// 						output = output + "_";
// 						if (PRINT_DEBUG) std::cout << "[" << __LINE__ << "] output: " << output << std::endl;
// 						fname_dmodel = output;
// 						fname_dmodel = fname_dmodel + fname_dmodel_backup.substr(start);
// 					}

// 					if (flag_Dbackup) {
// 						//if (PRINT_DEBUG) std::cout << "[" << __LINE__ << "] fname_dmodel: " << fname_dmodel << std::endl;
// 						revertModel(fname_dmodel, fname_dmodel_backup, path_model);
// 					}
// 				}
// 			}
// 		}
// 		closedir(dir);
// 	}
// #endif
// 	}
// }


void backupModel(const std::string &path) {

	std::string model_name_od, model_name_fd, model_name_fr, model_name_ac, model_name_ic;
	std::string fname_models_txt[5] = {nn_model_yolotiny_name, nn_model_srcfd_name, nn_model_mobilefacenet_name, nn_model_yamnet_name, nn_model_imgclass_name};
	std::string models[] = {"OBJECT_DETECTION", "FACE_DETECTION", "FACE_RECOGNITION", "AUDIO_CLASSIFICATION", "IMAGE_CLASSIFICATION"};
	std::string model_names[NUMBER_OF_MODELS];
	std::string nn_task;
    std::string voe_status = "NA";
    std::string header_all = "";
	std::string line_strip_header = "NA";
	std::string line_strip_headerNN = "NA";
	std::string dir_example = "NA";
	std::string example_file_path;
	std::string ino_extension = ".ino";
	std::string fname_dmodel;
 	std::string fname_dmodel_backup;
 	std::string input, output;
	std::string example_name;
	
	// All texts save to bufferContent
	std::string bufferContent;
	
	int count = 0;
	int count_match = 0;

	example_file_path = getIDEFilePath(path);
	if (PRINT_DEBUG) std::cout << "[" << __LINE__ << "][INFO] path_example: \"" << example_file_path << "\"" << std::endl;

#ifdef _WIN32
	std::wstring example_file_path_utf16 = utf8_to_utf16(example_file_path);

	// Open the file
    HANDLE hFile = CreateFileW(example_file_path_utf16.c_str(), GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
    if (hFile == INVALID_HANDLE_VALUE) {
        DWORD error = GetLastError();
        if (error == ERROR_FILE_NOT_FOUND) {
            std::cout << "File not found: " << convert_to_utf8(example_file_path_utf16) << std::endl;
        } else {
            std::cerr << "Failed to open file: " << convert_to_utf8(example_file_path_utf16) << ". Error code: " << error << std::endl;
        }
        return;
    }

	// Read file contents
    const int BUFFER_SIZE_INO = 4096; // Example buffer size
    std::vector<char> buffer(BUFFER_SIZE_INO);
    DWORD bytesRead = 0;
    BOOL success = FALSE;

	do {
        success = ReadFile(hFile, buffer.data(), BUFFER_SIZE_INO, &bytesRead, nullptr);
       if (success) {
            // Process the read buffer
            bufferContent.append(buffer.data(), bytesRead);
        } else {
            DWORD error = GetLastError();
            std::cerr << "Error reading file: " << convert_to_utf8(example_file_path_utf16) << ". Error code: " << error << std::endl;
        }
    } while (success && bytesRead > 0);

    // Close the file handle
    CloseHandle(hFile);

	// Search for keywords and process lines containing them
	std::istringstream iss(bufferContent);
	std::string line;
	
	if (nn_default_customized_yolotiny == "CUSTOMIZED" || nn_default_customized_srcfd == "CUSTOMIZED" || nn_default_customized_mobilefacenet == "CUSTOMIZED" || nn_default_customized_yamnet == "CUSTOMIZED" || nn_default_customized_imgclass == "CUSTOMIZED") {
		if (load_nn_model_src == "LoadFromFlash") {
			if (PRINT_DEBUG) std::cout << "[" << __LINE__ << "] Path: " << path << std::endl;
			if (path == "Temp" || path.find("modified") != std::string::npos) {//path == "Temp" && path == "modified") {
				// IDE 1
				if (PRINT_DEBUG) std::cout << "[" << __LINE__ << "] IDE1" << std::endl;
				dir_example = extractRootDirectory(path);
			} else {
				if (PRINT_DEBUG) std::cout << "[" << __LINE__ << "] IDE2" << std::endl;
				// IDE 2
				example_name = path.substr(path.find_last_of("\\") + 1);
				removeChar(example_name, '\\');
			}
			std::string folder_example = listExampleDir(path_library, example_name); // return example directory path
			dir_example = folder_example;
			if (PRINT_DEBUG) std::cout << "[" << __LINE__ << "] dir_example: " << dir_example << std::endl;

			// Open dir_example path
			WIN32_FIND_DATAW findData;
			HANDLE hFind = FindFirstFileW((utf8_to_utf16(dir_example) + L"\\*").c_str(), &findData);

			if (hFind == INVALID_HANDLE_VALUE) {
				DWORD error = GetLastError();
				std::cerr << "3 Failed to open directory: " << error << std::endl;
			}

			do {
				if (!(findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
					std::wstring fileName = findData.cFileName;
					if (fileName.length() > 3 && fileName.substr(fileName.length() - 3) == L".nb") {
						std::string fileName_utf8 = convert_to_utf8(fileName);

						if (fileName_utf8 != input2nbfile(nn_model_yolotiny_name) && fileName_utf8 != input2nbfile(nn_model_srcfd_name) && fileName_utf8 !=  input2nbfile(nn_model_mobilefacenet_name) && fileName_utf8 !=  input2nbfile(nn_model_yamnet_name) && fileName_utf8 !=  input2nbfile(nn_model_imgclass_name)) {
							std::cerr << "Customized model mismatch. Please rename your model." << std::endl;
							exit(EXIT_FAILURE);
						} else {
							if (PRINT_DEBUG) std::cout << "[" << __LINE__ << "] [Info] Found customized model:  " << fileName_utf8 << " in " << dir_example << std::endl;
							modelRenameBackup(fileName_utf8, dir_example);
						}
						count_match++;
					}	
				}
			} while (FindNextFileW(hFind, &findData) != 0);
			FindClose(hFind);
			if (PRINT_DEBUG) std::cout << "count: " << count << std::endl;
			if (PRINT_DEBUG) std::cout << "count_match: " << count_match << std::endl;
			if (count_match == 0) {
				if (load_nn_model_src == "LoadFromFlash") { 
					std::cerr << "Model (.nb file) missing or customized model name mismatch. Please include your customized model in sketch folder or rename your model if it is already in sketch folder." << std::endl;
					exit(EXIT_FAILURE);
				}
			}
		}
	} else {
		if (PRINT_DEBUG) std::cout << "[" << __LINE__ << "] path_model: " << path_model << std::endl;
		flag_Dbackup = false;

		std::wstring path_model_utf16 = utf8_to_utf16(path_model);

		// Open dir_example path
		WIN32_FIND_DATAW findData;
		HANDLE hFind = FindFirstFileW((path_model_utf16 + L"\\*").c_str(), &findData);

		if (hFind == INVALID_HANDLE_VALUE) {
			DWORD error = GetLastError();
			std::cerr << "4 Failed to open directory: " << error << std::endl;
		}

		do {
			if (!(findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
				std::wstring fileName = findData.cFileName;

				if (fileName.find(L"Dbackup_") != std::string::npos) {
					if (PRINT_DEBUG) std::wcout << "[" << __LINE__ << "] filename: " << fileName << std::endl;
					flag_Dbackup = true;
					fname_dmodel_backup = convert_to_utf8(fileName);

					std::string fileName_utf8 = convert_to_utf8(fileName);

					if (fileName_utf8.find(yolov3_model) != std::string::npos || fileName_utf8.find(yolov4_model) != std::string::npos || fileName_utf8.find(yolov7_model) != std::string::npos ) {
						input = nn_model_yolotiny_name;
					} else if (fileName_utf8.find(scrfd_model) != std::string::npos) {
						input = nn_model_srcfd_name;
					} else if (fileName_utf8.find(mobilefacenet_model) != std::string::npos) {
						input = nn_model_mobilefacenet_name;
					} else if (fileName_utf8.find(yamnet_model) != std::string::npos) {
						input = nn_model_yamnet_name;
					}  else if (fileName_utf8.find(cnn_model) != std::string::npos) {
						input = nn_model_imgclass_name;
					} else {
						std::cerr << "Customized model mismatch. Please rename your model." << std::endl;
						exit(EXIT_FAILURE);
					}

					auto underscore = input.find('_'); // Find the first occurrence of "_"
					if (underscore != std::string::npos) {
						output = input.substr(0, underscore); // Copy the substring before "_"
						if (output == cnn_key) { // because the name in json does not contain cnn
							output = cnn_model; 
						}
					} else {
						output = input;
					}

					if (PRINT_DEBUG) std::cout << "[" << __LINE__ << "] output: " << output << std::endl;

					// To prevent wrong file used to replace default model.
					if (output != "NA") {						
						if (output.find(yolov3_model) != std::string::npos) {
							output = yolov3_model;
						} if (output.find(yolov4_model) != std::string::npos) {
							output = yolov4_model;
						} if (output.find(yolov7_model) != std::string::npos) {
							output = yolov7_model;
						} else if (output.find(scrfd_model) != std::string::npos) {
							output = scrfd_model;
						} else if (output.find(mobilefacenet_model) != std::string::npos) {
							output = mobilefacenet_model;
						} else if (output.find(yamnet_model) != std::string::npos) {
							output = yamnet_model;
						}  else if (output.find(cnn_model) != std::string::npos) {
							output = cnn_model;
						}

						std::string key = "_";
						key = key + output;
						auto start = fname_dmodel_backup.find(key); // Find the starting position of the substring

						if (start != std::string::npos) {
							key = key + "_";
							start += key.length(); // Move the pointer past the substring
							if (PRINT_DEBUG) std::cout << "[" << __LINE__ << "] output: " << output << std::endl;
							output = output + "_";
							if (PRINT_DEBUG) std::cout << "[" << __LINE__ << "] output: " << output << std::endl;
							fname_dmodel = output;
							fname_dmodel = fname_dmodel + fname_dmodel_backup.substr(start);
						}

						if (flag_Dbackup) {
							//if (PRINT_DEBUG) std::cout << "[" << __LINE__ << "] fname_dmodel: " << fname_dmodel << std::endl;
							revertModel(fname_dmodel, fname_dmodel_backup, path_model);
						}
					}
				}
			}
		} while (FindNextFileW(hFind, &findData) != 0);
		FindClose(hFind);
	}
#else
	std::ifstream fmodel(example_file_path);
	std::string param;
	std::vector<std::string> params;
	std::vector<std::string> tokens;
	
	// Check if customized model is used	
	if (nn_default_customized_yolotiny == "CUSTOMIZED" || nn_default_customized_srcfd == "CUSTOMIZED" || nn_default_customized_mobilefacenet == "CUSTOMIZED" || nn_default_customized_yamnet == "CUSTOMIZED" || nn_default_customized_imgclass == "CUSTOMIZED") {
		if (load_nn_model_src == "LoadFromFlash") {
			if (PRINT_DEBUG) std::cout << "[" << __LINE__ << "] Path: " << path << std::endl;
			if (path == "Temp" || path.find("modified") != std::string::npos) {//path == "Temp" && path == "modified") {
			// IDE 1
				if (PRINT_DEBUG) std::cout << "[" << __LINE__ << "] IDE1" << std::endl;
				dir_example = extractRootDirectory(path);
			} else {
				if (PRINT_DEBUG) std::cout << "[" << __LINE__ << "] IDE2" << std::endl;
				// IDE 2
				std::string example_name = path.substr(path.find_last_of("/") + 1);
				removeChar(example_name, '/');
				std::string file_path = listExampleDir(path_library, example_name); // return example directory path
				dir_example = folder_example;
				if (PRINT_DEBUG) std::cout << "[" << __LINE__ << "] dir_example: " << dir_example << std::endl;
			}

			DIR* dir = opendir(dir_example.c_str());
			struct dirent* entry;
			if (dir != nullptr) {
				while ((entry = readdir(dir)) != nullptr) {
					std::string filename = entry->d_name;
					if (PRINT_DEBUG) std::cout << "[" << __LINE__ << "] filename: " << filename << std::endl;
					
					if (filename.find(".nb") != std::string::npos) {
						if (filename != input2nbfile(nn_model_yolotiny_name) && filename != input2nbfile(nn_model_srcfd_name) && filename !=  input2nbfile(nn_model_mobilefacenet_name) && filename !=  input2nbfile(nn_model_yamnet_name) && filename !=  input2nbfile(nn_model_imgclass_name)) {
							std::cerr << "Customized model mismatch. Please rename your model." << std::endl;
							exit(EXIT_FAILURE);
						} else {
							if (PRINT_DEBUG) std::cout << "[" << __LINE__ << "] [Info] Found customized model:  " << entry->d_name << " in " << dir_example << std::endl;
							modelRenameBackup(entry->d_name, dir_example); // filename, example directory
						}
						count_match++;
					}
				}
				if (PRINT_DEBUG) std::cout << "[" << __LINE__ << "] count: " << count << std::endl;
				if (PRINT_DEBUG) std::cout << "[" << __LINE__ << "] countmatch: " << count_match << std::endl;

				if (count_match == 0) {
					std::cerr << "Model (.nb file) missing or customized model name mismatch. Please include your customized model in sketch folder or rename your model if it is already in sketch folder." << std::endl;
					exit(EXIT_FAILURE);
				} 
			}
			closedir(dir);
		}
	} 
	else {
		if (PRINT_DEBUG) std::cout << "[" << __LINE__ << "] path_model: " << path_model << std::endl;

		DIR* dir = opendir(path_model.c_str());
		bool flag_Dbackup = false;
		std::string fname_dmodel;
		std::string fname_dmodel_backup;
		std::string input, output;
		if (dir) {
			struct dirent* ent;
			while ((ent = readdir(dir)) != NULL) {
				std::string filename = ent->d_name;
				if ((filename.find("Dbackup") != std::string::npos) ) {
					if (PRINT_DEBUG) std::cout << "[" << __LINE__ << "] filename: " << filename << std::endl;
					flag_Dbackup = true;
					fname_dmodel_backup = ent->d_name;

					if (filename.find(yolov3_model) != std::string::npos || filename.find(yolov4_model) != std::string::npos || filename.find(yolov7_model) != std::string::npos ) {
						input = nn_model_yolotiny_name;
					} else if (filename.find(scrfd_model) != std::string::npos) {
						input = nn_model_srcfd_name;
					} else if (filename.find(mobilefacenet_model) != std::string::npos) {
						input = nn_model_mobilefacenet_name;
					} else if (filename.find(yamnet_model) != std::string::npos) {
						input = nn_model_yamnet_name;
					}  else if (filename.find(cnn_model) != std::string::npos) {
						input = nn_model_imgclass_name;
					} else {
						std::cerr << "Customized model mismatch. Please rename your model." << std::endl;
						exit(EXIT_FAILURE);
					}
					
					auto underscore = input.find('_'); // Find the first occurrence of "_"
					if (underscore != std::string::npos) {
						output = input.substr(0, underscore); // Copy the substring before "_"
						if (output == cnn_key) { // because the name in json does not contain cnn
							output = cnn_model; 
						}
					} else {
						output = input;
					}

					if (PRINT_DEBUG) std::cout << "[" << __LINE__ << "] output: " << output << std::endl;

					// To prevent wrong file used to replace default model.
					if (output != "NA") {						
						if (output.find(yolov3_model) != std::string::npos) {
							output = yolov3_model;
						} if (output.find(yolov4_model) != std::string::npos) {
							output = yolov4_model;
						} if (output.find(yolov7_model) != std::string::npos) {
							output = yolov7_model;
						} else if (output.find(scrfd_model) != std::string::npos) {
							output = scrfd_model;
						} else if (output.find(mobilefacenet_model) != std::string::npos) {
							output = mobilefacenet_model;
						} else if (output.find(yamnet_model) != std::string::npos) {
							output = yamnet_model;
						}  else if (output.find(cnn_model) != std::string::npos) {
							output = cnn_model;
						}

						std::string key = "_";
						key = key + output;
						auto start = fname_dmodel_backup.find(key); // Find the starting position of the substring

						if (start != std::string::npos) {
							key = key + "_";
							start += key.length(); // Move the pointer past the substring
							if (PRINT_DEBUG) std::cout << "[" << __LINE__ << "] output: " << output << std::endl;
							output = output + "_";
							if (PRINT_DEBUG) std::cout << "[" << __LINE__ << "] output: " << output << std::endl;
							fname_dmodel = output;
							fname_dmodel = fname_dmodel + fname_dmodel_backup.substr(start);
						}

						if (flag_Dbackup) {
							//if (PRINT_DEBUG) std::cout << "[" << __LINE__ << "] fname_dmodel: " << fname_dmodel << std::endl;
							revertModel(fname_dmodel, fname_dmodel_backup, path_model);
						}
					}
				}
			}
			closedir(dir);
		}
	}
#endif
}

// -------------------------------
//           Main
// -------------------------------
int main(int argc, char* argv[]) {
#ifdef _WIN32
	setlocale(LC_ALL, "en_US.UTF-8");
#endif 

	// Check if the number of input arguments is correct 
	if (argc != 4) {
		if (PRINT_DEBUG) std::cout <<"[Error][" << __LINE__ << "] Incorrect number of input parameters. Expected 4 parameters." << std::endl;
		exit(1);
	}

	// Retrieve the input parameters 
	std::string path_build = argv[1];
	std::string path_tools = argv[2];
	std::string model_src = argv[3];
#ifdef _WIN32
	path_build = getUsernameChecked(path_build);
	path_tools = getUsernameChecked(path_tools);
#endif

	// Retrive root path
#ifdef _WIN32
	path_root = getenv("USERPROFILE");
	path_arduino15 = getenv("USERPROFILE");
	path_root = getUsernameChecked(path_root);
#else
	path_root = getenv("HOME");
	path_arduino15 = getenv("HOME");
#endif

	size_t path_tool_find_keyword = path_tools.find(key_portable);
	if (path_tool_find_keyword != std::string::npos) {
		path_arduino15 = findKeywordPath(path_tools, key_portable);
	} else {
		path_arduino15.append(path_arduino15_add);
	}
	path_pro2 = path_arduino15;
	path_pro2 = path_pro2.append(path_ambpro2_add);
#ifdef _WIN32
	path_pro2 = getUsernameChecked(path_pro2);
	path_arduino15 = getUsernameChecked(path_arduino15);
#endif
	path_model = path_pro2;
	path_model = path_model.append(dirName(path_pro2));
	path_library = path_model;
	path_library = path_library.append(path_library_add);
	path_model = path_model.append(path_model_add);
	path_txtfile = path_tools;
	path_txtfile = path_txtfile.append(path_txtfile_add);
	load_nn_model_src = model_src;

#if PRINT_DEBUG
	// Print the input parameters 
	std::cout <<"Parameter 1      = " << path_build << std::endl;
	std::cout <<"Parameter 2      = " << path_tools << std::endl;
	std::cout <<"Parameter 3      = " << model_src << std::endl;
	// std::cout <<"USERPROFILE      = " << getenv("USERPROFILE") << std::endl;
	// std::cout <<"HOMEDRIVE        = " << getenv("HOMEDRIVE") << std::endl;
	// std::cout <<"HOMEPATH         = " << getenv("HOMEPATH") << std::endl;
	std::cout <<"path_root        = " << path_root << std::endl;
	std::cout <<"path_arduino15   = " << path_arduino15 << std::endl;
	std::cout <<"path_pro2        = " << path_pro2 << std::endl;
	std::cout <<"ver_pro2         = " << dirName(path_pro2) << std::endl;
	std::cout <<"path_model       = " << path_model << std::endl;
	std::cout <<"path_library     = " << path_library << std::endl;
	std::cout <<"path_txtfile     = " << path_txtfile << std::endl;
#endif

	path_build_options_json = pathTempJSON(path_build, ext_json, key_json);
	path_example_ino = validateINO(path_build);
	readTXT(path_txtfile);
	backupModel(path_example_ino);
	if (PRINT_DEBUG) printf("[%s]----END----\n", __func__);

	return 0;
}
