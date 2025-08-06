/*

Compile:

windows:
g++.exe -o nn_json_modify_windows.exe nn_json_modify.cpp -static
strip nn_json_modify_windows.exe

If you encounter any issue while generating exe with icon, you may refer to: https://www.rodneybeede.com/programming/compiling_a_c___windows_executable_with_a_custom_icon.html

linux:
g++ -o nn_json_modify_linux nn_json_modify.cpp -static
strip nn_json_modify_linux

macos:
g++ -std=c++11 -arch x86_64 -arch arm64 -o nn_json_modify_macos nn_json_modify.cpp
strip nn_json_modify_macos

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
#undef isnan
#undef isinf
#include "json.hpp"

#define PRINT_DEBUG         0
#define MAX_PATH_LENGTH     1024
#define NUMBER_OF_MODELS    5

using namespace std;

// Declare global variables
std::string nn_model_yolotiny_name, nn_model_srcfd_name, nn_model_mobilefacenet_name, nn_model_yamnet_name, nn_model_imgclass_name, nn_default_customized_yolotiny, nn_default_customized_srcfd, nn_default_customized_mobilefacenet, nn_default_customized_yamnet, nn_default_customized_imgclass, nn_flash_sdcard_option;
std::string path_root, path_arduino15, path_pro2, path_model, path_library, path_txtfile, load_nn_model_src, ver_pro2, path_nn_json, tool_folder_json_path, path_jsonfile;
std::vector<std::string> ino_name_buf; // Vector to store lines from the file
std::string key_portable = "portable";
std::string filename_txt = "ino_validation.txt";
std::string nnmodels_json = "nn_models.json";

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
// Read contents from JSON
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

// Function to read the content of a UTF-16 encoded file and return it as a string
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
using json = nlohmann::json;
int modelCount(const std::string& jsonFilePath) {
	int count = 0; 
#if _WIN32
	std::wstring jsonFilePath_utf16 = utf8_to_utf16(jsonFilePath);
	std::string fileContent = readUtf16File(jsonFilePath_utf16);

	if (!fileContent.empty()) {
        try {
            // Parse JSON
            json j = json::parse(fileContent);

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

	if (!fileContent.empty()) {
        try {
            // Parse JSON
            json j = json::parse(fileContent);

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
	int sdk_counter = 0;

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

// Return the path that contains amebapro2_fwfs_nn_models.json
std::string JSONpath(const std::string& input) {
#if _WIN32
    WIN32_FIND_DATAW findData;
    HANDLE hFind = FindFirstFileW((utf8_to_utf16(input) + L"\\*").c_str(), &findData);

    if (hFind == INVALID_HANDLE_VALUE) {
        DWORD error = GetLastError();
        std::cerr << "Failed to open directory: " << error << std::endl;
    }

    do {
        if (!(findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
            std::wstring fileName = findData.cFileName;
            //std::wcout << fileName << std::endl; // Print filename
            if (fileName.length() > 3 && fileName.substr(fileName.length() - 5) == L".json") {
                std::string filepath = input + convert_to_utf8(fileName);
                //std::wcout << "fileName with .json: " << fileName << std::endl; // Print filename
                //std::cout << "filepath: " << filepath << std::endl; 
                return filepath;
            }
        }
    } while (FindNextFileW(hFind, &findData) != 0);
    FindClose(hFind);
	//return "";
#else
    DIR* dir;
    struct dirent* entry;
    if ((dir = opendir(input.c_str())) == nullptr) {
        perror("Error opening directory");
        //return "";
    }
    
    while ((entry = readdir(dir)) != nullptr) {
        if (strstr(entry->d_name, ".json") != nullptr) {
            std::string filepath = input + backspace + entry->d_name;
            if (PRINT_DEBUG) std::cout << "[" << __func__ << "][" << __LINE__ << "]filepath: " << filepath << std::endl;
            return filepath;
        }
    }
    closedir(dir);
	//return "";
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
			std::cout << "amebapro2_fwfs_nn_models.json not found in directory." << std::endl;
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
            std::string filepath = input + backspace + entry->d_name;
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

// Update files with model names in amebapro2_fwfs_nn_models.json
void updateJSON(const std::string& input, const std::string& destPath) {
#if _WIN32
    std::string jsonPath = JSONpath(destPath); 
    std::wstring jsonPath_utf16 = utf8_to_utf16(jsonPath);
    // Open the JSON file
    HANDLE hFile = CreateFileW(jsonPath_utf16.c_str(), GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
    if (hFile == INVALID_HANDLE_VALUE) {
        DWORD error = GetLastError();
        if (error == ERROR_FILE_NOT_FOUND) {
            std::wcout << L"JSON file not found: " << jsonPath_utf16 << std::endl;
        } else {
            std::cerr << "Failed to open JSON file: " << error << std::endl;
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
	// if (PRINT_DEBUG) std::cout << "File content:" << std::endl;
	// if (PRINT_DEBUG) std::cout << &fileContents[0] << std::endl; // Assuming file contains text data

	// Close the file handle after reading		
	CloseHandle(hFile);

    // Parse the JSON data
    cJSON* root = cJSON_Parse(fileContents.data());
    if (root == nullptr) {
        std::cerr << "Error parsing JSON data." << std::endl;
        return;
    }

    // Access the "FWFS" object
    cJSON* fwfs = cJSON_GetObjectItemCaseSensitive(root, "FWFS");
    if (fwfs == nullptr || !cJSON_IsObject(fwfs)) {
        cJSON_Delete(root);
        std::cerr << "Invalid JSON format: missing \"FWFS\" object." << std::endl;
        return;
    }

	// Access the "files" array
	cJSON* files = cJSON_GetObjectItem(fwfs, "files");
	if (files == NULL || !cJSON_IsArray(files)) {
		std::cout << "Failed to access the \"files\" array." << std::endl;
		cJSON_Delete(root);
	}

    // Create a cJSON item for the input (example)
    cJSON* inputItem = cJSON_CreateString(input.c_str());
    if (inputItem == nullptr) {
        std::cerr << "Failed to create cJSON item for input." << std::endl;
        cJSON_Delete(root);
        return;
    }

    // Add the input item to the files array
    cJSON_AddItemToArray(files, inputItem);

    // Convert the JSON data to a formatted string
    char* updatedJsonString = cJSON_Print(root);
    if (updatedJsonString == nullptr) {
        std::cerr << "Failed to convert JSON data to string." << std::endl;
        cJSON_Delete(root);
        return;
    }

    // Reopen the file for writing (truncate existing content)
    hFile = CreateFileW(jsonPath_utf16.c_str(), GENERIC_WRITE, 0, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
    if (hFile == INVALID_HANDLE_VALUE) {
        std::cerr << "Failed to reopen file for writing: " << GetLastError() << std::endl;
        cJSON_free(updatedJsonString); // Cleanup cJSON memory
        cJSON_Delete(root);
        return;
    }

    // Write the updated JSON content to file
    DWORD bytesWritten;
    if (!WriteFile(hFile, updatedJsonString, strlen(updatedJsonString), &bytesWritten, nullptr)) {
        std::cerr << "Failed to write to file: " << GetLastError() << std::endl;
    }

    // Close the file handle
    CloseHandle(hFile);

    // Cleanup cJSON memory
    cJSON_free(updatedJsonString);
    cJSON_Delete(root);

#else
      DIR* dir;
    struct dirent* ent;
    // Open the destination directory
    dir = opendir(destPath.c_str());
    if (dir == NULL) {
        std::cout << "Failed to open the destination directory: " << destPath << std::endl;
        return;
    }
 
    while ((ent = readdir(dir)) != NULL) {
        const char* destFile = ent->d_name;
 
        // Check if the destination file is a JSON file
        if (strstr(destFile, ".json") != NULL) {
            std::string filePath = destPath + "/" + destFile;
#if PRINT_DEBUG
            std::cout << "Processing JSON file: " << destFile << std::endl;
#endif
            // Open the JSON file
            FILE* jsonFile = fopen(filePath.c_str(), "r");
            if (jsonFile == NULL) {
                std::cout << "Failed to open the JSON file: " << filePath << std::endl;
                continue;
            }
 
            // Read the contents of the JSON file
            fseek(jsonFile, 0, SEEK_END);
            long fileSize = ftell(jsonFile);
            fseek(jsonFile, 0, SEEK_SET);
            std::string jsonContent(fileSize, ' ');
            fread(&jsonContent[0], 1, fileSize, jsonFile);
            fclose(jsonFile);
 
            // Parse the JSON data
            cJSON* root = cJSON_Parse(jsonContent.c_str());
            if (root == NULL) {
                std::cout << "Failed to parse the JSON data." << std::endl;
                continue;
            }
 
            // Access the "FWFS" object
            cJSON* fwfsObject = cJSON_GetObjectItem(root, "FWFS");
            if (fwfsObject == NULL) {
                std::cout << "Failed to access the \"FWFS\" object." << std::endl;
                cJSON_Delete(root);
                continue;
            }
 
            // Access the "files" array
            cJSON* filesArray = cJSON_GetObjectItem(fwfsObject, "files");
            if (filesArray == NULL || !cJSON_IsArray(filesArray)) {
                std::cout << "Failed to access the \"files\" array." << std::endl;
                cJSON_Delete(root);
                continue;
            }
 
            // Create a cJSON item for the input
            cJSON* inputItem = cJSON_CreateString(input.c_str());
            if (inputItem == NULL) {
                std::cout << "Failed to create cJSON item for the input." << std::endl;
                cJSON_Delete(root);
                continue;
            }
 
            // Add the input item to the files array
            cJSON_AddItemToArray(filesArray, inputItem);
 
            // Convert the JSON data to a formatted string
            char* updatedJsonString = cJSON_PrintBuffered(root, 4096, cJSON_True);
 
            // Open the JSON file for writing
            jsonFile = fopen(filePath.c_str(), "w");
            if (jsonFile == NULL) {
                std::cout << "Failed to open the JSON file for writing." << std::endl;
                cJSON_Delete(root);
                continue;
            }
 
            // Write the updated JSON string to the file
            fwrite(updatedJsonString, 1, strlen(updatedJsonString), jsonFile);
 
            // Close the file
            fclose(jsonFile);
 
            // Clean up memory
            free(updatedJsonString);
            cJSON_Delete(root);
        }
    }
 
    // Close the directory
    closedir(dir);
#endif
}

std::vector<std::string> model_names;
std::vector<std::string> model_types;
void readTXT(std::string& directory_path) {
    const int model_count = modelCount(tool_folder_json_path);
    const int modelselectparams_count = modelSelectParamsCount(tool_folder_json_path);
    bool is_model_section = false;
    bool is_type_section = false;
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
	// if (PRINT_DEBUG) std::cout << "TXT File content:" << std::endl;
	// if (PRINT_DEBUG) std::cout << &fileContents[0] << std::endl; // Assuming file contains text data
    
	// std::vector<std::string> ino_name_buf; // Vector to store lines from the file
    std::istringstream txtcontent(content);
	std::string line;
    while (std::getline(txtcontent, line)) {
        // Skip empty lines or separators
        if (line.empty() || line == "----------------------------------") {
            continue;
        }

        //ino_name_buf.push_back(line);
        if (line.find("Current ino contains model(s):") != std::string::npos) {
            is_model_section = true;
            is_type_section = false; // Reset type section flag
            continue;
        }
        if (line.find("Current model(s)(Default/Customized)") != std::string::npos) {
            is_model_section = false;
            is_type_section = true;
            continue;
        }

        // Extract model names
        if (is_model_section) {
            model_names.push_back(line); // Add model name to the vector
        }

        // Extract model types (Default/Customized)
        if (is_type_section) {
            model_types.push_back(line); // Add model type to the vector
        }
    }

	// Close the file handle after reading		
	CloseHandle(hFile);

    // Check if the model names and types are extracted correctly
#if (PRINT_DEBUG)
    for (size_t i = 0; i < model_names.size(); i++) {
        std::cout << "Model " << i << ": " << model_names[i] << " | Type: " << model_types[i]  << std::endl;
    }
#endif

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
    std::string line;
    while (std::getline(ino_validation_txt, line)) {
        // Skip empty lines or separators
        if (line.empty() || line == "----------------------------------") {
            continue;
        }

        if (line.find("Current ino contains model(s):") != std::string::npos) {
            is_model_section = true;
            is_type_section = false; // Reset type section flag
            continue;
        }
        if (line.find("Current model(s)(Default/Customized)") != std::string::npos) {
            is_model_section = false;
            is_type_section = true;
            continue;
        }

        // Extract model names
        if (is_model_section) {
            model_names.push_back(line); // Add model name to the vector
        }

        // Extract model types (Default/Customized)
        if (is_type_section) {
            model_types.push_back(line); // Add model type to the vector
        }
    }

    // Close the file
    ino_validation_txt.close();

    // Check if the model names and types are extracted correctly
#if (PRINT_DEBUG)
    for (size_t i = 0; i < model_names.size(); i++) {
        std::cout << "Model " << i << ": " << model_names[i] << " | Type: " << model_types[i]  << std::endl;
    }
#endif

    // Close the directory
    closedir(dir);
#endif
}

void writeJSON(const std::string &path) {
	if (PRINT_DEBUG) std::cout << "-------------------------------------" << std::endl;
    for (size_t i = 0; i < model_names.size(); i++) {
        if (PRINT_DEBUG) std::cout << "[" << __LINE__ << "] Model Name: " << model_names[i] << std::endl;
        if (model_names[i].find("NA") == std::string::npos) {
            if (load_nn_model_src =="LoadFromFlash") {     
                updateJSON(model_names[i], path_model);
            }
        }
    }
	
	if (PRINT_DEBUG) std::cout << "-------------------------------------" << std::endl;
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
    path_jsonfile = path_txtfile;
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
    tool_folder_json_path = path_jsonfile + nnmodels_json;
	resetJSON(path_model);
    path_nn_json = JSONpath(path_model);
    readTXT(path_txtfile);
	writeJSON(path_nn_json);
	if (PRINT_DEBUG) printf("[%s]----END----\n", __func__);

	return 0;
}
