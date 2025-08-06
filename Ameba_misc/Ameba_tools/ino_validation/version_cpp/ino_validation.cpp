/*

Compile:

windows:
g++.exe -o ino_validation_windows.exe ino_validation.cpp -static
strip ino_validation_windows.exe
### g++.exe -o ino_validation_windows.exe ino_validation.cpp -static ico-out.o -static
### mingw32-g++.exe -o  ino_validation_windows.exe ino_validation.cpp -static

If you encounter any issue while generating exe with icon, you may refer to: https://www.rodneybeede.com/programming/compiling_a_c___windows_executable_with_a_custom_icon.html

linux:
g++ -o ino_validation_linux ino_validation.cpp -static
strip ino_validation_linux

macos:
g++ -std=c++11 -arch x86_64 -arch arm64 -o ino_validation_macos ino_validation.cpp
strip ino_validation_macos

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
#undef isnan
#undef isinf
#include "json.hpp"

#if __APPLE__
#include <cctype> // For std::isspace
#endif

#define PRINT_DEBUG         			0
#define MAX_PATH_LENGTH    				1024

using namespace std;

// Declare global variables
std::string path_root, path_arduino15, path_pro2, path_model, path_library, path_txtfile, path_jsonfile, load_nn_model_src, ver_pro2, folder_example;
std::string path_build_options_json;
std::string path_example, path_example_ino;
std::string tool_folder_json_path;
std::string rootDir;
std::string key_portable = "portable";
std::string filename_txt = "ino_validation.txt";
std::string nnmodels_json = "nn_models.json";
std::string key_json = "build";
std::string ext_json = ".json";
std::string header_od = "NA", header_fd = "NA", header_fr = "NA", header_ac = "NA", header_ic = "NA", header_gesture = "NA", header_line = "NA";

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

// Declare keywords
std::string key_amb_NN = "modelSelect";
std::string key_amb_bypassNN1 = " .modelSelect";
std::string key_amb_bypassNN2 = " modelSelect";
std::string key_amb_customized = "CUSTOMIZED";
std::string key_amb_default = "DEFAULT";
std::string key_amb_header = "#include";
std::string key_nn = "NN";
std::string key_amb_VOE = "configVideoChannel";
std::string key_amb_bypassVOE1 = " .configVideoChannel";
std::string key_amb_bypassVOE2 = " configVideoChannel";

// -------------------------------
//           Functions
// -------------------------------

#ifdef _WIN32
std::wstring get_username() {
    wchar_t username[MAX_PATH_LENGTH];
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

std::string readUtf16File(const std::wstring& utf16Path) {
    HANDLE hFile = CreateFileW(utf16Path.c_str(), GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
    if (hFile == INVALID_HANDLE_VALUE) {
        DWORD error = GetLastError();
        std::cerr << "Failed to open file: " << error << std::endl;
        return "";
    }

    DWORD fileSize = GetFileSize(hFile, nullptr);
    if (fileSize == INVALID_FILE_SIZE) {
        std::cerr << "Failed to get file size: " << GetLastError() << std::endl;
        CloseHandle(hFile);
        return "";
    }

    std::vector<char> fileContents(fileSize + 1);  // +1 for null terminator

    DWORD bytesRead;
    if (!ReadFile(hFile, &fileContents[0], fileSize, &bytesRead, nullptr)) {
        std::cerr << "Failed to read file: " << GetLastError() << std::endl;
        CloseHandle(hFile);
        return "";
    }

    fileContents[fileSize] = '\0';  // Null-terminate the content

    CloseHandle(hFile);

    return std::string(fileContents.begin(), fileContents.end() - 1);  // Remove null terminator
}
#endif

// Read contents from JSON
using json = nlohmann::json;
int modelCount(const std::string& jsonFilePath) {
	int count = 0; 
#if _WIN32
	std::wstring jsonFilePath_utf16 = utf8_to_utf16(jsonFilePath);
	std::string fileContent = readUtf16File(jsonFilePath_utf16);

	 // Access "modelCount" -> "COUNT"
	if (!fileContent.empty()) {
        try {
            // Parse JSON
            json j = json::parse(fileContent);

            // Access "modelCount" -> "COUNT"
            if (j.contains("modelCount") && j["modelCount"].contains("COUNT")) {
                std::string count_str = j["modelCount"]["COUNT"];

                // Ensure the string is valid for conversion to integer
                if (!count_str.empty()) {
                    try {
                        // Convert to integer
                        count = std::stoi(count_str);
                    } catch (const std::invalid_argument& e) {
                        std::cerr << "Invalid argument: could not convert to integer: " << count_str << std::endl;
                    } catch (const std::out_of_range& e) {
                        std::cerr << "Out of range: could not convert to integer: " << count_str << std::endl;
                    }
                }
            }

            // Debug output
            if (PRINT_DEBUG) {
                std::cout << "[" << __func__ << "][" << __LINE__ << "] Model count: " << count << std::endl;
            }
        } catch (const json::exception& e) {
            std::cerr << "JSON parsing error: " << e.what() << std::endl;
        }
    }
#else
	// Read the JSON file
    std::ifstream inFile(jsonFilePath);
    if (!inFile.is_open()) {
        throw std::runtime_error("Unable to open JSON file: " + jsonFilePath);
    }

    // Parse the JSON file
    json j;
    inFile >> j;

	// Access the "modelCount" key and extract the "COUNT" value as a string
    std::string count_str = j["modelCount"]["COUNT"].get<std::string>();

    // Convert the string to an integer
	count = std::stoi(count_str);  // Converts the string to an integer

	if (PRINT_DEBUG) std::cout << "[" << __func__ << "][" << __LINE__ << "] Model count :" << count << std::endl;
#endif
    return count;
}

int modelSelectParamsCount(const std::string& jsonFilePath) {
	int count = 0;
#if _WIN32
	std::wstring jsonFilePath_utf16 = utf8_to_utf16(jsonFilePath);
	std::string fileContent = readUtf16File(jsonFilePath_utf16);

	 // Access "modelCount" -> "COUNT"
	if (!fileContent.empty()) {
        try {
            // Parse JSON
            json j = json::parse(fileContent);

            // Access "modelCount" -> "COUNT"
            if (j.contains("ModelSelectParamsCount") && j["ModelSelectParamsCount"].contains("COUNT")) {
                std::string count_str = j["ModelSelectParamsCount"]["COUNT"];

                // Ensure the string is valid for conversion to integer
                if (!count_str.empty()) {
                    try {
                        // Convert to integer
                        count = std::stoi(count_str);
                    } catch (const std::invalid_argument& e) {
                        std::cerr << "Invalid argument: could not convert to integer: " << count_str << std::endl;
                    } catch (const std::out_of_range& e) {
                        std::cerr << "Out of range: could not convert to integer: " << count_str << std::endl;
                    }
                }
            }

            // Debug output
            if (PRINT_DEBUG) {
                std::cout << "[" << __func__ << "][" << __LINE__ << "] Model count: " << count << std::endl;
            }
        } catch (const json::exception& e) {
            std::cerr << "JSON parsing error: " << e.what() << std::endl;
        }
    }
#else
	// Read the JSON file
    std::ifstream inFile(jsonFilePath);
    if (!inFile.is_open()) {
        throw std::runtime_error("Unable to open JSON file: " + jsonFilePath);
    }

    // Parse the JSON file
    json j;
    inFile >> j;

	// Access the "modelCount" key and extract the "COUNT" value as a string
    std::string count_str = j["ModelSelectParamsCount"]["COUNT"].get<std::string>();

    // Convert the string to an integer
	count = std::stoi(count_str);  // Converts the string to an integer

	if (PRINT_DEBUG) std::cout << "[" << __func__ << "][" << __LINE__ << "] ModelSelectParamsCount :" << count << std::endl;
#endif

    return count;
}

std::string dirName(const std::string& directory_path) {
#ifdef _WIN32
	std::wstring sdk_name;
	std::wstring directory_path_utf16 = utf8_to_utf16(directory_path);
	// Use Windows API to open directory and list contents
	WIN32_FIND_DATAW findData;
	HANDLE hFind = FindFirstFileW((directory_path_utf16 + L"\\*").c_str(), &findData);
	if (hFind == INVALID_HANDLE_VALUE) {
		DWORD error = GetLastError();
		std::cerr << "Failed to open directory: " << error << std::endl;
		return "Failed to open directory.";
	}

	int sdk_counter = 0;
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
	int sdk_counter = 0;
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

// Clear all contents in the ino_validation.txt file
void resetTXT(std::string& directory_path) {
#ifndef _WIN32
    DIR* dir = opendir(directory_path.c_str());
    struct stat st;
    // create directory if not exists
    if (stat(directory_path.c_str(), &st) == -1) {
        mkdir(directory_path.c_str(), 0700);
    }
    directory_path += filename_txt;

	// open txt file and clear everything
    FILE* file = fopen(directory_path.c_str(), "w");
    if (file != NULL) {
        // File opened successfully
        fclose(file);
    }
    if (PRINT_DEBUG) std::cout << "[" << __func__ << "][" << __LINE__ << "][INFO] resetTXT done" << std::endl;
#else
    std::wstring directory_path_utf16 = utf8_to_utf16(directory_path);
    std::wstring txt_file_path = directory_path_utf16 + L"\\ino_validation.txt";

    // Open the file
    HANDLE hFile = CreateFileW(txt_file_path.c_str(), GENERIC_WRITE, 0, nullptr, TRUNCATE_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
    if (hFile == INVALID_HANDLE_VALUE) {
        DWORD error = GetLastError();
        if (error == ERROR_FILE_NOT_FOUND) {
            std::cout << "ino_validation.txt not found in directory." << std::endl;
			if (PRINT_DEBUG) std::cout << "[" << __func__ << "][" << __LINE__ << "][INFO] resetTXT done" << std::endl;
	    } else {
            std::cerr << "Failed to open ino_validation.txt: " << error << std::endl;
        }
        return;
    }

    // Clear the contents of the file by setting its size to zero
    SetEndOfFile(hFile);

    // Close the file handle
    CloseHandle(hFile);

#endif
}

// Reset FWFS: "File" content in amebapro2_fwfs_nn_models.json
void resetJSON(const std::string& input) {
#if _WIN32
	std::wstring directory_path_utf16 = utf8_to_utf16(input);
	std::wstring json_file_path = directory_path_utf16 + L"\\amebapro2_fwfs_nn_models.json";

	// Open the file
	HANDLE hFile = CreateFileW(json_file_path.c_str(), GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
	if (hFile == INVALID_HANDLE_VALUE) {
		DWORD error = GetLastError();
		if (error == ERROR_FILE_NOT_FOUND) {
			//std::cout << "amebapro2_fwfs_nn_models.json not found in directory." << std::endl;
			if (PRINT_DEBUG) std::cout << "[" << __func__ << "][" << __LINE__ << "][INFO] JSON reset done" << std::endl;
		} else {
			std::cerr << "Failed to open amebapro2_fwfs_nn_models.json: " << error << std::endl;
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

	// Print or process the file content
	if (PRINT_DEBUG) std::cout << "File content:" << std::endl;
	if (PRINT_DEBUG) std::cout << &fileContents[0] << std::endl; // Assuming file contains text data

	// Close the file handle after reading		
	CloseHandle(hFile);

	cJSON* root = cJSON_Parse(fileContents.data());

	if (root == nullptr) {
		//fprintf(stderr, "Error parsing JSON in file: %s\n", entry->d_name);
		//continue;
	}

	cJSON* fwfs = cJSON_GetObjectItemCaseSensitive(root, "FWFS");
	if (fwfs == nullptr || !cJSON_IsObject(fwfs)) {
		cJSON_Delete(root);
		//fprintf(stderr, "Invalid JSON format in file: %s\n", entry->d_name);
		//continue;
	}

	cJSON* files = cJSON_GetObjectItemCaseSensitive(fwfs, "files");
	if (files == nullptr || !cJSON_IsArray(files)) {
		cJSON_Delete(root);
		//fprintf(stderr, "Invalid JSON format in file: %s\n", entry->d_name);
		//continue;
	}

	cJSON_DeleteItemFromObject(fwfs, "files");
	cJSON* new_files = cJSON_CreateArray();
	cJSON_AddItemToObject(fwfs, "files", new_files);

	char* new_file_contents = cJSON_Print(root);
	cJSON_Delete(root);

	// Reopen the file for writing (truncate existing content)
	hFile = CreateFileW(json_file_path.c_str(), GENERIC_WRITE, 0, nullptr, TRUNCATE_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
	if (hFile == INVALID_HANDLE_VALUE) {
		std::cerr << "Failed to reopen file for writing: " << GetLastError() << std::endl;
		cJSON_free(new_file_contents); // Cleanup cJSON memory
		return;
	}

	// Write the updated JSON content to file
	DWORD bytesWritten;
	if (!WriteFile(hFile, new_file_contents, strlen(new_file_contents), &bytesWritten, nullptr)) {
		std::cerr << "Failed to write to file: " << GetLastError() << std::endl;
	}

	// Close the file handle
	CloseHandle(hFile);

	// Cleanup cJSON memory
	cJSON_free(new_file_contents);

	if (PRINT_DEBUG) std::cout << "Clear JSON!" << std::endl; // Assuming file contains text data
#else
	DIR* dir;
	struct dirent* entry;
	if ((dir = opendir(input.c_str())) == nullptr) {
		perror("Error opening directory");
		return;
	}
	
	while ((entry = readdir(dir)) != nullptr) {
		if (strstr(entry->d_name, ".json") != nullptr) {
			std::string filepath = input + "/" + entry->d_name;
			if (PRINT_DEBUG) std::cout << "[" << __func__ << "][" << __LINE__ << "]filepath: " << filepath << std::endl;
			FILE* file = fopen(filepath.c_str(), "rb");
			if (file == nullptr) {
				perror("Error opening file");
				continue;
			}
			
			fseek(file, 0, SEEK_END);
			long file_size = ftell(file);
			fseek(file, 0, SEEK_SET);
			
			char file_contents[file_size + 1];
			if (fread(file_contents, file_size, 1, file) != 1) {
				perror("Error reading file");
				fclose(file);
				continue;
			}
			fclose(file);
			
			file_contents[file_size] = '\0'; // Null-terminate the string
			
			cJSON* root = cJSON_Parse(file_contents);
			if (root == nullptr) {
				fprintf(stderr, "Error parsing JSON in file: %s\n", entry->d_name);
				continue;
			}
			
			cJSON* fwfs = cJSON_GetObjectItemCaseSensitive(root, "FWFS");
			if (fwfs == nullptr || !cJSON_IsObject(fwfs)) {
				cJSON_Delete(root);
				fprintf(stderr, "Invalid JSON format in file: %s\n", entry->d_name);
				continue;
			}
			
			cJSON* files = cJSON_GetObjectItemCaseSensitive(fwfs, "files");
			if (files == nullptr || !cJSON_IsArray(files)) {
				cJSON_Delete(root);
				fprintf(stderr, "Invalid JSON format in file: %s\n", entry->d_name);
				continue;
			}
			
			cJSON_DeleteItemFromObject(fwfs, "files");
			cJSON* new_files = cJSON_CreateArray();
			cJSON_AddItemToObject(fwfs, "files", new_files);
			
			char* new_file_contents = cJSON_Print(root);
			cJSON_Delete(root);
			
			std::string new_file_contents_str(new_file_contents);
			
			FILE* new_file = fopen(filepath.c_str(), "w");
			if (new_file == nullptr) {
				perror("Error opening file for writing");
				free(new_file_contents);
				continue;
			}
			
			if (fwrite(new_file_contents_str.c_str(), new_file_contents_str.size(), 1, new_file) != 1) {
				perror("Error writing to file");
			}
			fclose(new_file);
			free(new_file_contents);
		}
	}
	closedir(dir);
#endif
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

	//std::cout << "[loadTempJSONFile] file_path: " << file_path << std::endl;
	
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
        std::cerr << "Failed to open directory: " << error << std::endl;
        return "Failed to open directory.";
    }
	
    do {
		if ((findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) &&
            wcscmp(findData.cFileName, L".") != 0 && wcscmp(findData.cFileName, L"..") != 0) {
			//if (PRINT_DEBUG) std::wcout << findData.cFileName << std::endl;
			std::wstring currentFileName = findData.cFileName;
			std::wstring currentPath = basePathUtf16  + L"\\" + currentFileName;

			// Check if exampleName is part of the currentFileName
			if (currentFileName == exampleNameUtf16) {
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

			std::string example_name = path.substr(path.find_last_of("\\") + 1);
			removeChar(example_name, '\\');	

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
			if (PRINT_DEBUG) std::cout << "[" << __LINE__ << "] 123" << std::endl;
			if (PRINT_DEBUG) std::cout << "[" << __LINE__ << "] file_path: " << file_path << std::endl;
			return file_path;
		}
		return file_path;
    }
#endif
}

void extractParam(std::string& line, std::string& param) {
	size_t start = line.find('(');
	size_t end = line.find(')');
	if (start != std::string::npos && end != std::string::npos && end > start) {
		size_t length = end - start - 1;
        param = line.substr(start + 1, length);

#if __APPLE__
        // Remove leading whitespace characters
        size_t i = 0;
        while (i < param.length() && std::isspace(param[i])) {
            ++i;
        }
        param.erase(0, i);

        // Remove trailing whitespace characters
        i = param.length();
        while (i > 0 && std::isspace(param[i - 1])) {
            --i;
        }
        param.erase(i);

#else
        // Remove leading and trailing whitespace characters
        param.erase(std::remove_if(param.begin(), param.end(), [](unsigned char c) { return std::isspace(c); }), param.end());
#endif
        
    }
}

std::string input2model(const std::string& input) {
std::string input_new, input_lower;
#if __APPLE__
	// Read the JSON file
    std::ifstream inFile(tool_folder_json_path);
    if (!inFile.is_open()) {
        throw std::runtime_error("3 Unable to open JSON file: " + tool_folder_json_path);
    }

    // Parse the JSON file
    json j;
    inFile >> j;
    std::unordered_map<std::string, std::string> model_mapping;
    std::string input_no_spaces = input;
    input_no_spaces.erase(std::remove_if(input_no_spaces.begin(), input_no_spaces.end(), ::isspace), input_no_spaces.end());
    input_new = input_no_spaces;
    for (const auto& pair : j["model_mappings"].items()) {
        model_mapping.insert(std::make_pair(pair.key(), pair.value()));
    }
#elif _WIN32
    std::wstring jsonFilePath_utf16 = utf8_to_utf16(tool_folder_json_path);
	std::string fileContent = readUtf16File(jsonFilePath_utf16);
	// Parse the JSON content from the UTF-8 string
    json j = json::parse(fileContent);
	std::unordered_map<std::string, std::string> model_mapping = j["model_mappings"].get<std::unordered_map<std::string, std::string>>();
#else
	// Read the JSON file
    std::ifstream inFile(tool_folder_json_path);
    if (!inFile.is_open()) {
        throw std::runtime_error("3 Unable to open JSON file: " + tool_folder_json_path);
    }

    // Parse the JSON file
    json j;
    inFile >> j;
    std::unordered_map<std::string, std::string> model_mapping = j["model_mappings"].get<std::unordered_map<std::string, std::string>>();
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

void updateTXT(const std::string& input) {
#ifdef _WIN32
	std::wstring path_txtfile_utf16 = utf8_to_utf16(path_txtfile);
	std::wstring txt_file_path = path_txtfile_utf16 + L"\\ino_validation.txt";

	// Open the file in append mode
    HANDLE hFile = CreateFileW(txt_file_path.c_str(), GENERIC_WRITE, 0, nullptr, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
    if (hFile == INVALID_HANDLE_VALUE) {
        DWORD error = GetLastError();
        std::cerr << "Failed to open or create ino_validation.txt: " << error << std::endl;
        return;
    }

	// Move the file pointer to the end of the file
    SetFilePointer(hFile, 0, nullptr, FILE_END);
	
	// Append a newline character to separate entries
	std::string line = input + "\n"; // Append newline

	// Write to the file
    DWORD bytesWritten;
    if (!WriteFile(hFile, line.c_str(), static_cast<DWORD>(line.size()), &bytesWritten, nullptr)) {
        std::cerr << "Failed to write to ino_validation.txt: " << GetLastError() << std::endl;
    } else {
        ///if (PRINT_DEBUG) std::cout << "Successfully wrote to ino_validation.txt" << std::endl;
    }

    // Close the file handle
    CloseHandle(hFile);

#else
	std::ofstream file(path_txtfile, std::ios_base::app); // check again
    if (file.is_open()) {
        file << input << std::endl;
        file.close();
    }
    else {
#if PRINT_DEBUG
        std::cerr << "[" << __func__ << "][" << __LINE__ << "][Error] Failed to open the file." << std::endl;
#endif
        perror(path_txtfile.c_str());
    }
#endif
}

std::string extractString(const std::string& source) {
	std::string result;
    auto start = source.find("\""); // find the 1st "
    if (start == std::string::npos) {
        result = ""; // set as empty string if not found
        return "";
    }
    start++; // skip the first "
    auto end = source.find("\"", start); // find the 2nd "
    if (end == std::string::npos) {
        result = ""; // set as empty string if not found
        return "";
    }
	result = source.substr(start, end - start);
    return result;
}

std::string extractString2(const std::string& source) {
	std::string result;
    auto start = source.find('<'); // find the 1st <
    if (start == std::string::npos) {
        result = ""; // set as empty string if not found
        return result;
    }
    start++; // skip the first <
    auto end = source.find('>', start); // find the 1st >
    if (end == std::string::npos) {
        result = ""; // set as empty string if not found
        return result;
    }
    result = source.substr(start, end - start);
	return result;
}

void writeTXT(const std::string &path) {
	const int model_count = modelCount(tool_folder_json_path);
	const int modelselectparams_count = modelSelectParamsCount(tool_folder_json_path);

	std::vector<std::string> model_customized_default(model_count);
	std::vector<std::string> model_names(model_count);
	std::vector<std::string> header_names(modelselectparams_count);
	std::vector<std::string> modelSelectParams(modelselectparams_count);
	std::vector<std::string> models(model_count);
	std::vector<std::string> headers(model_count);

	std::string example_file_path;
	std::string model_name_od, model_name_fd, model_name_fr, model_name_ac, model_name_ic, model_name_pd, model_name_hlm;
	std::string nn_task;
    std::string voe_status = "NA";
    std::string header_all = "";
	std::string line_strip_header = "NA";
	std::string line_strip_headerNN = "NA";
	std::string dir_example = "NA";
	std::string ino_extension = ".ino";
	int count = 0;
	int count_match = 0;

	std::vector<std::string> tokens;
	std::vector<std::string> params;
	std::string param;

	// Read the JSON file
#if _WIN32
	std::wstring jsonFilePath_utf16 = utf8_to_utf16(tool_folder_json_path);

    // Read the content of the file as a UTF-8 string
    std::string fileContent = readUtf16File(jsonFilePath_utf16);

    // Parse the JSON content from the UTF-8 string
    json j = json::parse(fileContent);

#else
	std::ifstream inFile(tool_folder_json_path);
	if (!inFile.is_open()) {
		throw std::runtime_error("Unable to open JSON file: " + tool_folder_json_path);
	}

	// Parse the JSON file
	json j;
	inFile >> j;
#endif
	// Initialize a vector to store tasks
	std::vector<std::string> nnTasks;
	std::vector<std::string> headerName;
	std::vector<std::string> header;

	// All texts save to bufferContent
	std::string bufferContent;

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
    const int BUFFER_SIZE = 4096; // Example buffer size
    std::vector<char> buffer(BUFFER_SIZE);
    DWORD bytesRead = 0;
    BOOL success = FALSE;

    do {
        success = ReadFile(hFile, buffer.data(), BUFFER_SIZE, &bytesRead, nullptr);
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
#else
	std::ifstream fmodel(example_file_path);
	if (fmodel.is_open()) {
        std::string line;
		
		while (std::getline(fmodel, line)) {
			bufferContent += line + "\n"; // Append each line to bufferContent
		}
		fmodel.close();
	}  else {
        std::cerr << "Unable to open file." << std::endl;
    }
#endif

	// Search for keywords and process lines containing them
	std::istringstream iss(bufferContent);
	std::string line;
	while (std::getline(iss, line)) {
		if (line.find(key_amb_NN) != std::string::npos &&
			line.find(backspace) == std::string::npos &&
			line.find(key_amb_bypassNN1) == std::string::npos &&
			line.find(key_amb_bypassNN2) == std::string::npos) {
			
			// Process the line containing the keyword(s)
			// Example processing:
			if (PRINT_DEBUG) std::cout << "Found keyword(s) in line: " << line << std::endl;
			extractParam(line, param);
			if (PRINT_DEBUG) std::cout << "[" << __func__ << "][" << __LINE__ << "][INFO] Extracted parameter: " << param << std::endl;
			
			std::istringstream tokenStream(param);
			std::string token;
			std::getline(tokenStream, token, ',');
			
			if (!token.empty()) {
				nn_task = token;
				if (PRINT_DEBUG) std::cout << "[" << __LINE__ << "] nn_task " << nn_task << std::endl;
			}

			tokens.clear();
			std::istringstream iss(param);
			while (std::getline(iss, token, ',')) {
				tokens.push_back(token);	
			}

			// Copy tokens to the model_names array
			if (tokens.size() <= modelselectparams_count) {
				std::copy(tokens.begin(), tokens.end(), modelSelectParams.begin());
			}

			// Assign model name to each model variable
			for (int i = 0; i < model_count; i++) {
				model_names[i] = modelSelectParams[i + 1];
				if (PRINT_DEBUG) std::cout << "[" << __LINE__ << "] model_names[i] " << model_names[i] << std::endl;
			}

			if (PRINT_DEBUG) std::cout << "-------------------------------------" << std::endl;
			for (int m = 0; m < model_count; m++) { 
				if (PRINT_DEBUG) std::cout << "[" << __LINE__ << "] model_name: " << model_names[m] << std::endl;
			}
		}
	}

	// Error handler
	if (j.contains("nn_task") && j["nn_task"].contains("NNTASK")) {
		nnTasks = j["nn_task"]["NNTASK"].get<std::vector<std::string>>();
	} else {
		std::cerr << "Error: 'nn_task' or 'NNTASK' key not found in the JSON file." << std::endl;
	}

	if (j.contains("error_handler") && j["error_handler"].contains("tasks")) {
		auto tasks = j["error_handler"]["tasks"];
        if (tasks.contains(nn_task)) {
            std::vector<std::string> required_models = tasks[nn_task].get<std::vector<std::string>>();
   
			bool all_keywords_present = true;
            for (const auto& required_model : required_models) {
                bool model_found = false;
                for (const auto& model_name : model_names) {
                    if (model_name.find(required_model) != std::string::npos) {
                        model_found = true;
                        break;
                    }
                }

                if (!model_found) {
                    std::cerr << "Model combination mismatch for task '" << nn_task << "'. Missing model: " << required_model << std::endl;
                    all_keywords_present = false;
                }
            }

			// Exit if any required model is missing
            if (!all_keywords_present) {
                exit(EXIT_FAILURE);
            }
		} 
		// else {
        //     std::cerr << "Task '" << nn_task << "' not found in error_handler." << std::endl;
        //     exit(EXIT_FAILURE);
        // }
	} else {
        std::cerr << "Error handler configuration is invalid or missing." << std::endl;
        exit(EXIT_FAILURE);
    }
	
	for (int i = 0; i < model_count; i++) {
		if (load_nn_model_src != "LoadFromFlash" && model_names[i].find(key_amb_default) != std::string::npos) {
			std::cerr << "Model selection mismatched. Please ensure that you select a customized model when loading from SD card." << std::endl;
			exit(EXIT_FAILURE);
    	}
	}

	// Check if customized model is used
	for (int i = 0; i < model_count; i++) {
		if (model_names[i].find(key_amb_customized) != std::string::npos) {
			if (PRINT_DEBUG) std::cout << "[" << __LINE__ << "] model_names[i]: " << model_names[i] << std::endl;
			if (PRINT_DEBUG) std::cout << "[" << __LINE__ << "] key_amb_customized" << std::endl;
			if (PRINT_DEBUG) std::cout << "[" << __LINE__ << "] input model: " << input2model(model_names[i]) << std::endl;
			if (PRINT_DEBUG) std::cout << "[" << __LINE__ << "] path example: " << path << std::endl;

			if (load_nn_model_src == "LoadFromFlash") {
				if (path == "Temp" || path.find("modified") != std::string::npos) {
					// IDE 1
					if (PRINT_DEBUG) std::cout << "[" << __LINE__ << "] IDE1" << std::endl;
					dir_example = extractRootDirectory(path);
				} else {
					if (PRINT_DEBUG) std::cout << "[" << __LINE__ << "] IDE2" << std::endl;
					// IDE 2
#ifdef _WIN32
					std::string example_name = path.substr(path.find_last_of("\\") + 1);
					removeChar(example_name, '\\');
#else
					std::string example_name = path.substr(path.find_last_of("/") + 1);
					removeChar(example_name, '/');
#endif
					if (PRINT_DEBUG) std::cout << "[" << __LINE__ << "] example_name: " << example_name << std::endl;
					std::string folder_example = listExampleDir(path_library, example_name); // return example directory path
					if (PRINT_DEBUG) std::cout << "[" << __LINE__ << "] folder_example: " << folder_example << std::endl;
					dir_example = folder_example;
					if (PRINT_DEBUG) std::cout << "[" << __LINE__ << "] dir_example: " << dir_example << std::endl;
				}
#ifdef _WIN32
				WIN32_FIND_DATAW findData;
				HANDLE hFind = FindFirstFileW((utf8_to_utf16(dir_example) + L"\\*").c_str(), &findData);

				if (hFind == INVALID_HANDLE_VALUE) {
					DWORD error = GetLastError();
					std::cerr << "Failed to open directory: " << error << std::endl;
				}

				do {
					if (!(findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
						std::wstring fileName = findData.cFileName;
						count++;
						if (PRINT_DEBUG) std::wcout << fileName << std::endl; // Print filename
						if (fileName.length() > 3 && fileName.substr(fileName.length() - 3) == L".nb") {
						 	count_match++;
						}
					}
				} while (FindNextFileW(hFind, &findData) != 0);
				FindClose(hFind);
#else
				DIR* dir = opendir(dir_example.c_str());
				struct dirent* entry;
				
				// check whether directory is valid
				if (dir != nullptr) {
					while ((entry = readdir(dir)) != nullptr) {
						if (entry->d_type == DT_REG) {	
							count++;
						}

						std::string filename = entry->d_name;
						if (PRINT_DEBUG) std::cout << "[" << __LINE__ << "] filename: " << filename << std::endl;
						if (filename.find(".nb") != std::string::npos) {
							if (PRINT_DEBUG) std::cout << "[" << __LINE__ << "] filename: " << filename << std::endl;
							if (PRINT_DEBUG) std::cout << "[" << __LINE__ << "] model_names[i]: " << model_names[i] << std::endl;
							if (PRINT_DEBUG) std::cout << "[" << __LINE__ << "] input2model(model_names[i]): " << input2model(model_names[i]) << std::endl;
							//if (filename.find(input2model(model_names[i])) != std::string::npos) {
								count_match++;
							//}
						}
					}
				}
				closedir(dir);
#endif
				if (PRINT_DEBUG) std::cout << "[" << __LINE__ << "] count: " << count << std::endl;
				if (PRINT_DEBUG) std::cout << "[" << __LINE__ << "] count_match: " << count_match << std::endl;
			} 

			if (count_match == 0) {
				if (load_nn_model_src == "LoadFromFlash") { 
					std::cerr << "Model (.nb file) missing or customized model name mismatch. Please include your customized model in sketch folder or rename your model if it is already in sketch folder." << std::endl;
					exit(EXIT_FAILURE);
				}
			}
		} 
	}
	
	if (PRINT_DEBUG) std::cout << "-------------------------------------" << std::endl;
	for (int i = 0; i < model_count; i++) {
		if (PRINT_DEBUG) std::cout << "[" << __LINE__ << "] Model Name : " <<  input2model(model_names[i]) << std::endl;
	}

	if (load_nn_model_src == "LoadFromFlash") {
		if (input2model(model_name_ac) != "NA") {
			if ((input2model(model_name_od) != "NA" ||  input2model(model_name_fd) != "NA" || input2model(model_name_fr) != "NA" || input2model(model_name_ic) != "NA")) {
				std::cerr << "Exceeds model size limitation for Flash. Please consider using SD card to load NN models." << std::endl;
				exit(EXIT_FAILURE);
			}
		}
	}

	// ------------------------- update TXT -------------------------
	updateTXT("----------------------------------");
	updateTXT("Current ino contains model(s):");
	for (int i = 0; i < model_count; i++) {
		if (model_names[i].length() == 0) {
			updateTXT("NA");
		}
		else {
			updateTXT(input2model(model_names[i]));
		}
	}

	updateTXT("----------------------------------");
	updateTXT("Current model(s)(Default/Customized)");
	for (int i = 0; i < model_count; i++) {
		if (model_names[i].length() != 0 && model_names[i] != "NA_MODEL") {
			if (PRINT_DEBUG) std::cout << "[" << __LINE__ << "] model_names[i]: " << model_names[i] << std::endl;

			if (model_names[i].find(key_amb_default) != std::string::npos) {
				model_customized_default[i] = "DEFAULT";
			} else if (model_names[i].find(key_amb_customized) != std::string::npos) {
				model_customized_default[i] = "CUSTOMIZED";
			} else {
				model_customized_default[i] = "NA";
			}
			updateTXT(model_customized_default[i]);

			if (PRINT_DEBUG) std::cout << "[" << __LINE__ << "] model_customized_default[i]: " << model_customized_default[i] << std::endl;
		} else {
			updateTXT("NA");
		}
	}
	
	updateTXT("-----------------------------------");
	updateTXT("Current NN header file(s): ");

	if (PRINT_DEBUG) std::cout << "[" << __LINE__ << "] example_file_path: " << example_file_path << std::endl;
	// if (PRINT_DEBUG) std::cout << "[" << __LINE__ << "] bufferContent: " << bufferContent << std::endl;

	if (j.contains("header") && j["header"].contains("HEADERNAME")) {
        headerName = j["header"]["HEADERNAME"].get<std::vector<std::string>>();
    } else {
        std::cerr << "Error: 'HEADERNAME' not found in JSON." << std::endl;
		exit(EXIT_FAILURE);
    }

	for (int i = 0; i < model_count; i++) {
		if (PRINT_DEBUG) std::cout << "[" << __LINE__ << "]  headerName[i]: " << headerName[i] << std::endl;
	}

	std::istringstream iss_nnheader(bufferContent);
	header.resize(model_count, "NA");
	while (std::getline(iss_nnheader, line)) {
		if (line.find(key_amb_header) != std::string::npos && line.find(key_nn) != std::string::npos) {
			for (int i = 0; i < model_count; i++) {
				if (PRINT_DEBUG) std::cout << "[" << __LINE__ << "] headerName[i]: " << headerName[i] << std::endl;
				if (line.find(headerName[i]) != std::string::npos) {
					header[i] = extractString(line); // Save header_line to the vector.
					header_line = extractString(line); // Assign to array or vector.
					 if (PRINT_DEBUG) std::cout << "[" << __LINE__ << "] header[" << i << "]: " << header[i] << std::endl;
                	break; // No need to check further for this line.
				} 
			}
		} 
	}

	if (PRINT_DEBUG) std::cout << "-------------------------------------" << std::endl;
	for (int i = 0; i < model_count; i++) {
		if (PRINT_DEBUG) std::cout << "[" << __LINE__ << "] Final header[" << i << "]: " << header[i] << std::endl;
		updateTXT(header[i]);
	}

	updateTXT("----------------------------------");
	updateTXT("Current ino video status:");

	std::istringstream iss_voe(bufferContent);
	while (std::getline(iss_voe, line)) {
		if (line.find(key_amb_VOE) != std::string::npos && line.find("//") == std::string::npos &&
			line.find(key_amb_bypassVOE1) == std::string::npos && line.find(key_amb_bypassVOE2) == std::string::npos) {
			voe_status = "ON";
		}
	}	
	updateTXT(voe_status);

	updateTXT("-------------------------------------");
	updateTXT("Current NN Model(s) loaded from:");
	if (load_nn_model_src == "LoadFromFlash") {
		updateTXT("FLASH");
	} else {
		updateTXT("SDCARD");
	}

	updateTXT("-------------------------------------");
	updateTXT("Current ino contains header file(s): ");

	std::istringstream iss_headerfiles(bufferContent);
	header_all = "";
	while (std::getline(iss_headerfiles, line)) {
		if (line.find(key_amb_header) != std::string::npos) {
			line_strip_header = extractString(line);	// remove unnecessary part in the header
			if (line_strip_header.length() == 0) {
				line_strip_header = extractString2(line);
			}
			if (PRINT_DEBUG) std::cout << "line_strip_header: " << line_strip_header << std::endl;
			header_all = header_all.append(line_strip_header); // store headers into a string
		}
	}
	// update header_all to txt
	const std::string delimiter = ".h";
	if (!header_all.empty()) {
		std::string headersCopy = header_all;
		char* headersCopyCStr = const_cast<char*>(headersCopy.c_str()); 
		char* token = std::strtok(headersCopyCStr, delimiter.c_str());
		if (token != nullptr) {
			if (PRINT_DEBUG) std::cout << "Token: " << token << std::endl;
			updateTXT(token);
			while ((token = std::strtok(nullptr, delimiter.c_str())) != nullptr) {
				if (PRINT_DEBUG) std::cout << "Token: " << token << ".h" << std::endl;
				updateTXT(token);
			}
		}
	}
}

// -------------------------------
//           Main
// -------------------------------
int main(int argc, char* argv[]) {

#ifdef _WIN32
	SetConsoleOutputCP(CP_UTF8);

    // Set locale to support UTF-8
    std::locale::global(std::locale(""));
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
	path_jsonfile = path_txtfile; // they are in the same folder (misc)
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
	resetTXT(path_txtfile);
	resetJSON(path_model);
	path_build_options_json = pathTempJSON(path_build, ext_json, key_json);
	tool_folder_json_path = path_jsonfile + nnmodels_json;
	path_example_ino = validateINO(path_build);
	writeTXT(path_example_ino);
	if (PRINT_DEBUG) printf("[%s]----END----\n", __func__);

	return 0;
}