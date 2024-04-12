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
g++ -arch x86_64 -arch arm64 -o ino_validation_macos ino_validation.cpp
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

#if __APPLE__
#include <cctype> // For std::isspace
#endif

#define PRINT_DEBUG         1
#define MAX_PATH_LENGTH     1024

#define NUMBER_OF_MODELS 5
#define NUMBER_OF_MODELSELECT_PARAMS 6
#define NUMBER_OF_NN_TASKS 5
using namespace std;

// Declare global variables
std::string path_root, path_arduino15, path_pro2, path_model, path_library, path_txtfile, load_nn_model_src, ver_pro2, folder_example;
std::string model_customized_default[NUMBER_OF_MODELS];
std::string path_build_options_json;
std::string path_example, path_example_ino;
std::string rootDir;
std::string key_portable = "portable";
std::string filename_txt = "ino_validation.txt";
std::string key_json = "build";
std::string ext_json = ".json";
std::string header_od = "NA", header_fd = "NA", header_fr = "NA", header_ac = "NA", header_ic = "NA";

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
#else
    struct stat st;
    // create directory if not exists
    if (stat(directory_path.c_str(), &st) == -1) {
        mkdir(directory_path.c_str());
    }
    directory_path += filename_txt;
#endif
    // open txt file and clear everything
    FILE* file = fopen(directory_path.c_str(), "w");
    if (file != NULL) {
        // File opened successfully
        fclose(file);
    }
    if (PRINT_DEBUG) std::cout << "[" << __func__ << "][" << __LINE__ << "][INFO] resetTXT done" << std::endl;
}

void resetJSON(const std::string& input) {
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
}

// Return the file path that can be found in  build.options.json, where build.options.json can be found in Temp folder of Arduino
// The path returned is the sketchLocation in build.options.json
std::string pathTempJSON(const std::string& directory_path, const std::string& ext, const std::string& key) {
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
                return file_path;
            }
        }
        closedir(dir);
    }
    return ""; // Return empty string if not found
}

cJSON* loadTempJSONFile(const std::string& file_path) {
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
    // Open the JSON file and retrieve the data
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
}

// check IDE version and get the file path for example
std::string getIDEFilePath (const std::string &path) {
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
#ifdef _WIN32
			std::string example_name = path.substr(path.find_last_of("\\") + 1);
			removeChar(example_name, '\\');	
#else
			std::string example_name = path.substr(path.find_last_of("/") + 1);
			removeChar(example_name, '/');	
#endif
			//file_path = listExampleDir(path_library, example_name); // return example directory path
			if (PRINT_DEBUG) std::cout << "[" << __LINE__ << "] 123" << std::endl;
			if (PRINT_DEBUG) std::cout << "[" << __LINE__ << "] file_path: " << file_path << std::endl;
			return file_path;
		}
		return file_path;
    }
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
    std::unordered_map<std::string, std::string> model_mapping;
    std::string input_no_spaces = input;
    input_no_spaces.erase(std::remove_if(input_no_spaces.begin(), input_no_spaces.end(), ::isspace), input_no_spaces.end());
    input_new = input_no_spaces;
    
    // Insert each key-value pair manually
    model_mapping.insert(std::make_pair("CUSTOMIZED_YOLOV3TINY", "yolov3_tiny"));
    model_mapping.insert(std::make_pair("CUSTOMIZED_YOLOV4TINY", "yolov4_tiny"));
    model_mapping.insert(std::make_pair("CUSTOMIZED_YOLOV7TINY", "yolov7_tiny"));
    model_mapping.insert(std::make_pair("CUSTOMIZED_MOBILEFACENET", "mobilefacenet_i16"));
    model_mapping.insert(std::make_pair("CUSTOMIZED_SCRFD", "scrfd640"));
    model_mapping.insert(std::make_pair("CUSTOMIZED_YAMNET", "yamnet_fp16"));
    model_mapping.insert(std::make_pair("CUSTOMIZED_IMGCLASS", "img_class"));
    model_mapping.insert(std::make_pair("DEFAULT_YOLOV3TINY", "yolov3_tiny"));
    model_mapping.insert(std::make_pair("DEFAULT_YOLOV4TINY", "yolov4_tiny"));
    model_mapping.insert(std::make_pair("DEFAULT_YOLOV7TINY", "yolov7_tiny"));
    model_mapping.insert(std::make_pair("DEFAULT_MOBILEFACENET", "mobilefacenet_i8"));
    model_mapping.insert(std::make_pair("DEFAULT_SCRFD", "scrfd320p"));
    model_mapping.insert(std::make_pair("DEFAULT_YAMNET", "yamnet_fp16"));
    model_mapping.insert(std::make_pair("DEFAULT_IMGCLASS", "img_class"));
#else
    std::unordered_map<std::string, std::string> model_mapping = {
        {"CUSTOMIZED_YOLOV3TINY",    "yolov3_tiny"},
        {"CUSTOMIZED_YOLOV4TINY",    "yolov4_tiny"},
        {"CUSTOMIZED_YOLOV7TINY",    "yolov7_tiny"},
        {"CUSTOMIZED_MOBILEFACENET", "mobilefacenet_i16"},
        {"CUSTOMIZED_SCRFD",         "scrfd640"},
        {"CUSTOMIZED_YAMNET",        "yamnet_fp16"},
        {"CUSTOMIZED_IMGCLASS",      "img_class"},
        {"DEFAULT_YOLOV3TINY",      "yolov3_tiny"},
        {"DEFAULT_YOLOV4TINY",      "yolov4_tiny"},
        {"DEFAULT_YOLOV7TINY",      "yolov7_tiny"},
        {"DEFAULT_MOBILEFACENET",   "mobilefacenet_i8"},
        {"DEFAULT_SCRFD",           "scrfd320p"},
        {"DEFAULT_YAMNET",          "yamnet_fp16"},
        {"DEFAULT_IMGCLASS",        "img_class"}
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

void updateTXT(const std::string& input) {
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
	std::string model_name_od, model_name_fd, model_name_fr, model_name_ac, model_name_ic;
	std::string models[] = {"OBJECT_DETECTION", "FACE_DETECTION", "FACE_RECOGNITION", "AUDIO_CLASSIFICATION", "IMAGE_CLASSIFICATION"};
	std::string modelSelectParams[NUMBER_OF_MODELSELECT_PARAMS];
	std::string model_names[NUMBER_OF_MODELS];
    std::string header_names[NUMBER_OF_MODELSELECT_PARAMS];
	std::string nn_task;
    std::string voe_status = "NA";
    std::string header_all = "";
	std::string line_strip_header = "NA";
	std::string line_strip_headerNN = "NA";
	std::string dir_example = "NA";
	std::string example_file_path;
	std::string ino_extension = ".ino";
	int count = 0;
	int count_match = 0;

	example_file_path = getIDEFilePath(path);
	if (PRINT_DEBUG) std::cout << "[" << __LINE__ << "][INFO] path_example: \"" << example_file_path << "\"" << std::endl;
	
	std::ifstream fmodel(example_file_path);
	std::string param;
	std::vector<std::string> params;
	std::vector<std::string> tokens;
	
	if (fmodel.is_open()) {
        std::string line;
		
		while (std::getline(fmodel, line)) {
			// check whether keywordNN in file
		
            if (line.find(key_amb_NN) != std::string::npos && line.find(backspace) == std::string::npos && line.find(key_amb_bypassNN1) == std::string::npos && line.find(key_amb_bypassNN2) == std::string::npos) {
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
				std::copy(tokens.begin(), tokens.end(), modelSelectParams);

				// Assign model name to each model variable
				for (int i = 0; i <= NUMBER_OF_MODELS; i++) {
					model_names[i] = modelSelectParams[i + 1];
				}
				model_name_od = model_names[0];
				model_name_fd = model_names[1];
				model_name_fr = model_names[2];
				model_name_ac = model_names[3];
				model_name_ic = model_names[4];

				if (PRINT_DEBUG) std::cout << "[" << __LINE__ << "] model_name_od " << model_name_od << std::endl;
				if (PRINT_DEBUG) std::cout << "[" << __LINE__ << "] model_name_fd " << model_name_fd << std::endl;
				if (PRINT_DEBUG) std::cout << "[" << __LINE__ << "] model_name_fr " << model_name_fr << std::endl;
				if (PRINT_DEBUG) std::cout << "[" << __LINE__ << "] model_name_ac " << model_name_ac << std::endl;
				if (PRINT_DEBUG) std::cout << "[" << __LINE__ << "] model_name_ic " << model_name_ic << std::endl;

				// check for invalid combination for modelSelect (Error Handler)
				if (load_nn_model_src != "LoadFromFlash" && (model_name_od.find(key_amb_default) != std::string::npos  || model_name_fd.find(key_amb_default) != std::string::npos || model_name_fr.find(key_amb_default) != std::string::npos || model_name_ac.find(key_amb_default) != std::string::npos || model_name_ic.find(key_amb_default) != std::string::npos)) { // If Load from SD Card and modelSelect is Default
					std::cerr << "Model selection mismatched. Please ensure that you have select customized model in modelSelect() when selecting SD card." << std::endl;
					exit(EXIT_FAILURE);
				}

				if (nn_task == "OBJECT_DETECTION") {
					if (model_name_od == "NA_MODEL" || model_name_od.find("YOLO") == std::string::npos) {
						std::cerr << "Model combination mismatch. Please check modelSelect() again." << std::endl;
						exit(EXIT_FAILURE);
					}
				} else if (nn_task == "FACE_DETECTION") {
					if (model_name_fd  == "NA_MODEL" || model_name_fd.find("SCRFD") == std::string::npos) {
						std::cerr << "Model combination mismatch. Please check modelSelect() again." << std::endl;
						exit(EXIT_FAILURE);
					}
				} else if (nn_task == "FACE_RECOGNITION") {
					if (model_name_fd  == "NA_MODEL" || model_name_fd.find("SCRFD") == std::string::npos || model_name_fd == "NA_MODEL" || model_name_fr.find("MOBILEFACENET") == std::string::npos) {
						std::cerr << "Model combination mismatch. Please check modelSelect() again." << std::endl;
						exit(EXIT_FAILURE);
					}
				} else if (nn_task == "AUDIO_CLASSIFICATION") {
					if (model_name_ac  == "NA_MODEL" || model_name_ac.find("YAMNET") == std::string::npos) {
						if (PRINT_DEBUG) std::cout << "[" << __LINE__ << "] model_name_ac: " << model_name_ac << std::endl;
						std::cerr << "Model combination mismatch. Please check modelSelect() again." << std::endl;
						exit(EXIT_FAILURE);
					}
				} else if (nn_task == "IMAGE_CLASSIFICATION") {
					if (model_name_ic == "NA_MODEL" || model_name_ic.find("IMGCLASS") == std::string::npos) {
						std::cerr << "Model combination mismatch. Please check modelSelect() again." << std::endl;
						exit(EXIT_FAILURE);
					}
				}
				
				// Check if customized model is used
				for (int i = 0; i < NUMBER_OF_MODELS; i++) {
					if (model_names[i].find(key_amb_customized) != std::string::npos) {
						if (PRINT_DEBUG) std::cout << "[" << __LINE__ << "] key_amb_customized" << std::endl;
						if (PRINT_DEBUG) std::cout << "[" << __LINE__ << "] input model: " << input2model(model_names[i]) << std::endl;
						if (PRINT_DEBUG) std::cout << "[" << __LINE__ << "] path example: " << path << std::endl;
						
						model_customized_default[i] = key_amb_customized;
						if (load_nn_model_src == "LoadFromFlash") {
							//flagCustomizedModel = 1;
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
								std::string file_path = listExampleDir(path_library, example_name); // return example directory path
								dir_example = folder_example;
								if (PRINT_DEBUG) std::cout << "[" << __LINE__ << "] dir_example: " << dir_example << std::endl;
							}

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
										if (filename.find(input2model(model_names[i])) != std::string::npos) {

											count_match++;
										}
									}
								}
							}
							closedir(dir);
							if (PRINT_DEBUG) std::cout << "[" << __LINE__ << "] count: " << count << std::endl;
							if (PRINT_DEBUG) std::cout << "[" << __LINE__ << "] countmatch: " << count_match << std::endl;
						} 

					} else if (model_names[i].find(key_amb_default) != std::string::npos) {
						model_customized_default[i] = "DEFAULT";
					} else {
						model_customized_default[i] = "NA";
					}
					if (PRINT_DEBUG) std::cout << "[" << __LINE__ << "] model_customized_default[i]: " << model_customized_default[i] << std::endl;
				}
            }
        }
        fmodel.close();
    } else {
		std::cerr << "[Error] Failed to open f_model." << std::endl;
		exit(EXIT_FAILURE);
	}

	if (PRINT_DEBUG) std::cout << "-------------------------------------" << std::endl;
	if (PRINT_DEBUG) std::cout << "[" << __LINE__ << "] Model Name OD: " <<  input2model(model_name_od) << std::endl;
	if (PRINT_DEBUG) std::cout << "[" << __LINE__ << "] Model Name FD: " <<  input2model(model_name_fd) << std::endl;
	if (PRINT_DEBUG) std::cout << "[" << __LINE__ << "] Model Name FR: " <<  input2model(model_name_fr) << std::endl;
	if (PRINT_DEBUG) std::cout << "[" << __LINE__ << "] Model Name AC: " <<  input2model(model_name_ac) << std::endl;
	if (PRINT_DEBUG) std::cout << "[" << __LINE__ << "] Model Name IC: " <<  input2model(model_name_ic) << std::endl;
	if (PRINT_DEBUG) std::cout << "-------------------------------------" << std::endl;
	
	
	if (nn_task == "AUDIO_CLASSIFICATION") {
		if (load_nn_model_src == "LoadFromFlash") {
			if ((model_name_od != "NA_MODEL" && model_name_fd != "NA_MODEL" && model_name_fr != "NA_MODEL" && model_name_ic != "NA_MODEL")) {
				std::cerr << "Exceeds model size limitation for Flash. Please consider using SD card to load NN models." << std::endl;
				exit(EXIT_FAILURE);
			}
		}
	}

	// ------------------------- update TXT -------------------------
	updateTXT("----------------------------------");
	updateTXT("Current ino contains model(s):");
	if (model_name_od.length() == 0 && model_name_fd.length() == 0 && model_name_fr.length() == 0 && model_name_ac.length() == 0 && model_name_ic.length() == 0) {
		for (int i = 0; i < NUMBER_OF_MODELS; i++) {
			updateTXT("NA");
		}
	}
	else {
		updateTXT(input2model(model_name_od));
		updateTXT(input2model(model_name_fd));
		updateTXT(input2model(model_name_fr));
		updateTXT(input2model(model_name_ac));
		updateTXT(input2model(model_name_ic));
	}

	updateTXT("----------------------------------");
	updateTXT("Current model(s)(Default/Customized)");

	if (model_name_od.length() != 0 && model_name_od != "NA_MODEL") {
		if (PRINT_DEBUG) std::cout << "[" << __LINE__ << "] Model Name OD: " << model_name_od << std::endl;
		updateTXT(model_customized_default[0]);
	} else {
		updateTXT("NA");
	}
	
	if (model_name_fd.length() != 0 && model_name_fd != "NA_MODEL") {
		if (PRINT_DEBUG) std::cout << "[" << __LINE__ << "] Model Name FD: " << model_name_fd << std::endl;
		updateTXT(model_customized_default[1]);
	} else {
		updateTXT("NA");
	}

	if (model_name_fr.length() != 0 && model_name_fd != "NA_MODEL") {
		if (PRINT_DEBUG) std::cout << "[" << __LINE__ << "] Model Name FR: " << model_name_fr << std::endl;
		updateTXT(model_customized_default[2]);
	} else {
		updateTXT("NA");
	}
	
	if (model_name_ac.length() != 0 && model_name_ac != "NA_MODEL") {
		if (PRINT_DEBUG) std::cout << "[" << __LINE__ << "] Model Name AC: " << model_name_ac << std::endl;
		updateTXT(model_customized_default[3]);
	} else {
		updateTXT("NA");
	}
	
	if (model_name_ic.length() != 0 && model_name_ic != "NA_MODEL") {
		if (PRINT_DEBUG) std::cout << "[" << __LINE__ << "] Model Name AC: " << model_name_ic << std::endl;
		updateTXT(model_customized_default[4]);
	} else {
		updateTXT("NA");
	}

	updateTXT("-----------------------------------");
	updateTXT("Current NN header file(s): ");

	if (PRINT_DEBUG) std::cout << "[" << __LINE__ << "] example_file_path: " << example_file_path << std::endl;

	// struct dirent *entry;
	//DIR *f_headerNN = opendir(example_file_path.c_str());
	std::ifstream f_headerNN(example_file_path);

	if (f_headerNN.is_open()) {
		if (PRINT_DEBUG) std::cout << "f_headerNN.is_open" << std::endl;
		std::string line;
		while (std::getline(f_headerNN, line)) {
            if (line.find(key_amb_header) != std::string::npos && line.find(key_nn) != std::string::npos) {
                if (line.find("Object") != std::string::npos) {
                    header_od = extractString(line);
                } 
		else if (line.find("FaceDetection") != std::string::npos && line.find("Recognition") == std::string::npos) {
                    header_fd = extractString(line);
                } 
		else if (line.find("FaceDetectionRecognition") != std::string::npos) {
                    header_fr = extractString(line);
                } 
		else if (line.find("Audio") != std::string::npos) {
                    header_ac = extractString(line);
                } 
		else if (line.find("Image") != std::string::npos) {
                    header_ic = extractString(line);
                }
            }
        }
		if (PRINT_DEBUG) std::cout << "[" << __LINE__ << "] Extracted OD header: " << header_od << std::endl;
		if (PRINT_DEBUG) std::cout << "[" << __LINE__ << "] Extracted FD header: " << header_fd << std::endl;
		if (PRINT_DEBUG) std::cout << "[" << __LINE__ << "] Extracted FR header: " << header_fr << std::endl;
		if (PRINT_DEBUG) std::cout << "[" << __LINE__ << "] Extracted AC header: " << header_ac << std::endl;
		if (PRINT_DEBUG) std::cout << "[" << __LINE__ << "] Extracted IC header: " << header_ic << std::endl;
		if (PRINT_DEBUG) std::cout << "-------------------------------------" << std::endl;
	} else {
		std::cerr << "[Error] Failed to open the file. " << std::endl;
		exit(EXIT_FAILURE);
	}

	updateTXT(header_od);
	updateTXT(header_fd);
	updateTXT(header_fr);
	updateTXT(header_ac);
	updateTXT(header_ic);

	updateTXT("----------------------------------");
	updateTXT("Current ino video status:");
	std::ifstream f_VOE(example_file_path); 
	if (f_VOE) {
		if (PRINT_DEBUG) std::cout << "f_VOE.is_open" << std::endl;
		std::string line;
		while (std::getline(f_VOE, line)) {
			if (line.find(key_amb_VOE) != std::string::npos && line.find("//") == std::string::npos &&
				line.find(key_amb_bypassVOE1) == std::string::npos && line.find(key_amb_bypassVOE2) == std::string::npos) {
				voe_status = "ON";
			}
		}
	} else {
		std::cerr << "[Error] Failed to open the file. " << std::endl;
		exit(EXIT_FAILURE);
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

	std::ifstream f_header(example_file_path); 	

	if (f_header.is_open()) {
		header_all = "";
		std::string line;
		while (std::getline(f_header, line)) {
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
	resetTXT(path_txtfile);
	resetJSON(path_model);
	path_build_options_json = pathTempJSON(path_build, ext_json, key_json);
	path_example_ino = validateINO(path_build);
	writeTXT(path_example_ino);
	if (PRINT_DEBUG) printf("[%s]----END----\n", __func__);

	return 0;
}
