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
g++ -arch x86_64 -arch arm64 -o nn_json_modify_macos nn_json_modify.cpp
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
#endif
#include <dirent.h>  // Include necessary headers for Linux/macOS
#include <sys/stat.h>
#include <sys/types.h>
#include "cJSON.h" // Assuming cJSON library is used
#include "cJSON.c" // Assuming cJSON library is used
#include <algorithm>
#include <unordered_map>

#define PRINT_DEBUG         0
#define MAX_PATH_LENGTH     1024
#define NUMBER_OF_MODELS    5

using namespace std;

// Declare global variables
std::string nn_model_yolotiny_name, nn_model_srcfd_name, nn_model_mobilefacenet_name, nn_model_yamnet_name, nn_model_imgclass_name, nn_default_customized_yolotiny, nn_default_customized_srcfd, nn_default_customized_mobilefacenet, nn_default_customized_yamnet, nn_default_customized_imgclass, nn_flash_sdcard_option;
std::string path_root, path_arduino15, path_pro2, path_model, path_library, path_txtfile, load_nn_model_src, ver_pro2, path_nn_json;
string ino_name_buf[100];
std::string key_portable = "portable";
std::string filename_txt = "ino_validation.txt";

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
std::string dirName(const std::string& directory_path) {
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
    DIR* dir;
    struct dirent* entry;
    if ((dir = opendir(input.c_str())) == nullptr) {
        perror("Error opening directory");
        return "";
    }
    
    while ((entry = readdir(dir)) != nullptr) {
        if (strstr(entry->d_name, ".json") != nullptr) {
            std::string filepath = input + backspace + entry->d_name;
            if (PRINT_DEBUG) std::cout << "[" << __func__ << "][" << __LINE__ << "]filepath: " << filepath << std::endl;
            return filepath;

        }
       
    }
     closedir(dir);
}

// Reset files in amebapro2_fwfs_nn_models.json
void resetJSON(const std::string& input) {
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
}

// Update files with model names in amebapro2_fwfs_nn_models.json
void updateJSON(const std::string& input, const std::string& destPath) {
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
}

// Read ino_validation.txt to get the model used names.  
void readTXT(std::string& directory_path) {
int str_count = 0;

#ifndef _WIN32
    DIR* dir = opendir(directory_path.c_str());
    struct stat st;
    // create directory if not exists
    if (stat(directory_path.c_str(), &st) == -1) {
        mkdir(directory_path.c_str(), 0700);
    }
    directory_path += filename_txt;
#else
    struct stat st;
    // create directory if not exists
    if (stat(directory_path.c_str(), &st) == -1) {
        mkdir(directory_path.c_str());
    }
    directory_path += filename_txt;
#endif
    
    std::ifstream ino_validation_txt(directory_path);
    if (ino_validation_txt.is_open()) {
        std::string line;
		while (std::getline(ino_validation_txt, line)) {
            ino_name_buf[str_count] = line;
            str_count++;
        }
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
    }
}

void writeJSON(const std::string &path) {
	if (PRINT_DEBUG) std::cout << "-------------------------------------" << std::endl;
	if (PRINT_DEBUG) std::cout << "[" << __LINE__ << "] Model Name OD: " <<  nn_model_yolotiny_name << std::endl;
	if (PRINT_DEBUG) std::cout << "[" << __LINE__ << "] Model Name FD: " <<  nn_model_srcfd_name << std::endl;
	if (PRINT_DEBUG) std::cout << "[" << __LINE__ << "] Model Name FR: " <<  nn_model_mobilefacenet_name << std::endl;
	if (PRINT_DEBUG) std::cout << "[" << __LINE__ << "] Model Name AC: " <<  nn_model_yamnet_name << std::endl;
	if (PRINT_DEBUG) std::cout << "[" << __LINE__ << "] Model Name IC: " <<  nn_model_imgclass_name << std::endl;
	if (PRINT_DEBUG) std::cout << "-------------------------------------" << std::endl;

	if (nn_model_yolotiny_name.find("NA") == std::string::npos) {    
		if (load_nn_model_src =="LoadFromFlash") {        
			updateJSON(nn_model_yolotiny_name, path_model);
		} 
	}

	if (nn_model_srcfd_name.find("NA") == std::string::npos) {    
		if (load_nn_model_src =="LoadFromFlash") {        
			updateJSON(nn_model_srcfd_name, path_model);
		} 
	}

	if (nn_model_mobilefacenet_name.find("NA") == std::string::npos) {    
		if (load_nn_model_src =="LoadFromFlash") {        
			updateJSON(nn_model_mobilefacenet_name, path_model);
		} 
	}

	if (nn_model_yamnet_name.find("NA") == std::string::npos) {    
		if (load_nn_model_src =="LoadFromFlash") {        
			updateJSON(nn_model_yamnet_name, path_model);
		} 
	}

	if (nn_model_imgclass_name.find("NA") == std::string::npos) {    
		if (load_nn_model_src =="LoadFromFlash") {        
			updateJSON(nn_model_imgclass_name, path_model);
		} 
	}
}

// -------------------------------
//           Main
// -------------------------------
int main(int argc, char* argv[]) {
	setlocale(LC_ALL, "en_US.UTF-8");
	// Check if the number of input arguments is correct 
	if (argc != 4) {
		if (PRINT_DEBUG) std::cout <<"[Error][" << __LINE__ << "] Incorrect number of input parameters. Expected 2 parameters." << std::endl;
		exit(1);
	}

	// Retrieve the input parameters 
	std::string path_build = argv[1];
	std::string path_tools = argv[2];
	std::string model_src = argv[3];

	// Retrive root path
#ifdef _WIN32
	path_root = getenv("USERPROFILE");
	path_arduino15 = getenv("USERPROFILE");
#else
	path_root = getenv("HOME");
	path_arduino15 = getenv("HOME");
#endif
	size_t path_tool_find_keyword = path_tools.find(key_portable);
	if (path_tool_find_keyword != std::string::npos) {
		path_arduino15 = path_arduino15.append(findKeywordPath(path_tools, key_portable));
	} else {
		path_arduino15.append(path_arduino15_add);
	}
	path_pro2 = path_arduino15;
	path_pro2 = path_pro2.append(path_ambpro2_add);
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
	resetJSON(path_model);
    path_nn_json = JSONpath(path_model);
    readTXT(path_txtfile);
	writeJSON(path_nn_json);
	if (PRINT_DEBUG) printf("[%s]----END----\n", __func__);

	return 0;
}
