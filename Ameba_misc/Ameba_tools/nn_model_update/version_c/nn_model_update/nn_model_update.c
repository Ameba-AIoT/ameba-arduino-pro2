/*******************************************************************************************************************************************************************
*  README
*
* FOR REALTEK INTERNAL USERS
* To understand the tool overall API structure and details, please download a documentation via the Wiki link below and refer to Chapter 2:
* https://wiki.realtek.com/download/attachments/155451805/%5BWiki%5D%5BSD3%5D%20How%20to%20update%20tools%20to%20Arduino%20SDK_20230707.pdf?api=v2
*
*  COMPILATION
* Windows: VS Build Solution0
* Linux/macOS: open terminal and execute "make clean;make" command
*
*******************************************************************************************************************************************************************/
#define _GNU_SOURCE

#ifdef _WIN32
#include <io.h>
#include "dirent.h"	// https://codeyarns.com/tech/2014-06-06-how-to-use-dirent-h-with-visual-studio.html#gsc.tab=0
#define F_OK 0
#else // #elif __linux__
#include <inttypes.h>
#include <unistd.h>
#include <dirent.h>
#define __int64 int64_t
#define _close close
#define _read read
#define _lseek64 lseek64
#define _O_RDONLY O_RDONLY
#define _open open
#define _lseeki64 lseek64
#define _lseek lseek
#define _access access
#define _strdup strdup
#define stricmp strcasecmp
#endif

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>
#include "cJSON.h"
#include <locale.h>
#include <time.h>

#define PRINT_DEBUG		0
#define MAX_PATH_LENGTH 1024
#define BUFFER_SIZE		4096

/* Declear function headers */
int dirExists(const char* directory_path);
/* Return folder names under current directory */
const char* dirName(const char* directory_path);
/* Function returns nuber of content under this path */
int isDirExists(const char* path);
/* Functions below are for txt f_model manipulation */
int endsWith(const char* str, const char* suffix);
/* Returns example f_model path inside the temp JSON f_model */
const char* pathTempJSON(const char* directory_path, const char* ext, const char* key);
/* Load JSON f_model from the directory and parse into cJSON data format */
cJSON* loadJSONFile(const char* directory_path);
/* Remove char c from string str */
void removeChar(char* str, char c);
/* Validate example in directory_path and returns example path */
const char* validateINO(const char* directory_path);
/* Clear all content in the ino_validation.txt file */
void resetTXT(const char* directory_path);
/* Update content in the input to TXT f_model */
void updateTXT(const char* input);
/* Similar function as REGEX*/
void extractParam(char* line, char* param);
/* Extract header from quote symbols*/
void extractString(char* source, char* result);
/* Handler to print error message in the Arduino IDE */
void error_handler(const char* message);
/* Convert model input type to model name*/
const char* input2model(const char* input);
/* Find the dir name of input source file path*/
void extractRootDirectory(char* source, char* result);
/* Convert model input to model filename as defined in json */
const char* input2filename(const char* directory_path, const char* key);
/* Retrun the date in YYYY-MM-DD of the file creation */
char* dspFileProp(const char* f_name);
/* Add prefix Dmodel/Cmodel for backup .nb files */
void renameFile(char* filename, int type);
/* Backup files from source to destination dir, can be merged with renameFile */
void backupModel(char* input, char* sktech_path);
/* Revert Dmodel when user select Default model */
void revertModel(const char* dmodel_name, const char* dmodel_name_backup, const char* dmodel_path);
/* Copy files from source to destination dir, can be merged with renameFile */
void copyFile(const char* sourcePath, const char* destinationPath);
// -------------------------------------------------------------



void resetJSON(const char* input);

/* Update nn model json file*/
void updateJSON(const char* input, const char* destPath);
/* Function to update JSON */
int writeJSON(const char* f_path);

/* Declear global vairables */
const char* key_amb_NN					= "modelSelect";
const char* key_amb_bypassNN1			= " .modelSelect";
const char* key_amb_bypassNN2			= " modelSelect";
const char* key_amb_VOE					= "configVideoChannel";
const char* key_amb_bypassVOE1			= " .configVideoChannel";
const char* key_amb_bypassVOE2			= " configVideoChannel";
const char* key_amb_header				= "#include";
const char* key_amb_customized			= "CUSTOMIZED";
const char* key_json					= "build";
const char* key_amb						= "Arduino15";
const char* key_ino						= ".ino";
const char* ext_json					= ".json";
const char* key_amb_default				= "DEFAULT";
const char* key_amb_default_backup		= "Dbackup";
const char* key_amb_customized_backup	= "Cbackup";
const char* fname_txt					= "ino_validation.txt";
const char* dir_example					= "NA";

/* Declear common file paths */
#ifdef _WIN32
char* path_arduino15_add = "\\AppData\\Local\\Arduino15";
char* path_ambpro2_add = "\\packages\\realtek\\hardware\\AmebaPro2\\";
char* path_model_add = "\\variants\\common_nn_models";
char* path_txtfile_add = "\\misc\\";
char* backspace = "\\";
#elif __linux__
char* path_arduino15_add = "/.arduino15";
char* path_ambpro2_add = "/packages/realtek/hardware/AmebaPro2/";
char* path_model_add = "/variants/common_nn_models";
char* path_txtfile_add = "/misc/";
char* backspace = "/";
#else
char* path_arduino15_add = "/Library/Arduino15";
char* path_ambpro2_add = "/packages/realtek/hardware/AmebaPro2/";
char* path_model_add = "/variants/common_nn_models";
char* path_txtfile_add = "/misc/";
char* backspace = "/";
#endif

const char* path_build_options_json = NULL;
const char* path_example = NULL;
const char* name_example = NULL;
char path_root[MAX_PATH_LENGTH];
char path_arduino15[MAX_PATH_LENGTH];
char path_pro2[MAX_PATH_LENGTH];
char path_model[MAX_PATH_LENGTH];
char dir_model[MAX_PATH_LENGTH];
char path_txt[MAX_PATH_LENGTH];

int main(int argc, char* argv[]) {

	setlocale(LC_ALL, "en_US.UTF-8");
	// Check if the number of input arguments is correct 
	if (argc != 3) {
#if PRINT_DEBUG
		printf("[Error] Incorrect number of input parameters. Expected 2 parameters.\r\n");
#endif
		exit(1);
	}

	// Retrieve the input parameters 
	const char* path_build = argv[1];
	const char* path_tools = argv[2];

	// Retrive root path
#ifdef _WIN32
	strcpy(path_root, getenv("USERPROFILE"));
	strcpy(path_arduino15, getenv("USERPROFILE"));
#else
	strcpy(path_root, getenv("HOME"));
	strcpy(path_arduino15, getenv("HOME"));
#endif

	strcat(path_arduino15, path_arduino15_add);
	strcpy(path_pro2, path_arduino15);
	strcat(path_pro2, path_ambpro2_add);
	strcpy(path_model, path_pro2);
	strcat(path_model, dirName(path_pro2));
	strcat(path_model, path_model_add);
	strcpy(path_txt, argv[2]);
	strcat(path_txt, path_txtfile_add);

#if PRINT_DEBUG
	// Print the input parameters 
	printf("Parameter 1      = %s\n", path_build);
	printf("Parameter 2      = %s\n", path_tools);
	//printf("USERPROFILE      = %s\n", getenv("USERPROFILE"));
	//printf("HOMEDRIVE        = %s\n", getenv("HOMEDRIVE"));
	//printf("HOMEPATH         = %s\n", getenv("HOMEPATH"));
	printf("path_root        = %s\n", path_root);
	printf("path_arduino15   = %s\n", path_arduino15);
	printf("path_pro2        = %s\n", path_pro2);
	printf("ver_pro2         = %s\n", dirName(path_pro2));
	printf("path_model       = %s\n", path_model);
	printf("path_txt         = %s\n", path_txt);
#endif

	resetJSON(path_model);		//resetTXT(path_txt);
	//printf("[%s][INFO] resetJSON done\n", __func__);
	path_build_options_json = pathTempJSON(path_build, ext_json, key_json);
	path_example = validateINO(path_build);
	//printf("[%s][INFO] path_example            = %s\n", __func__, path_example);
	writeJSON(path_example);	//writeTXT(path_example);

	return 0;
}

const char* input2filename(const char* directory_path, const char* key) {
#if PRINT_DEBUG
	printf("[%s] open the file %s \n", __func__, directory_path);
#endif
	FILE* file = fopen(directory_path, "rb");
	if (file == NULL) {
		printf("[%s][Error] Failed to open the file.\n", __func__);
		perror("Error opening file");
		printf("Error code: %d\n", errno);
		return 1;
	}

	// Get the file size
	fseek(file, 0, SEEK_END);
	size_t file_size = ftell(file);
	fseek(file, 0, SEEK_SET);
	rewind(file);

	// Allocate memory to hold the JSON data
	char* json_data = (char*)malloc(file_size + 1);
	if (json_data == NULL) {
		printf("[%s][Error] Failed to allocate memory.\n", __func__);
		fclose(file);
		return 1;
	}

	// Read the JSON data from the file
	size_t read_size = fread(json_data, 1, file_size, file);
#if PRINT_DEBUG
	printf("[%s][Info] read_size %d\n", __func__, read_size);
	printf("[%s][Info] file_size %d\n", __func__, file_size);
#endif
	if (read_size != file_size) {
		printf("[%s][Error] Failed to read the file.\n", __func__);
		fclose(file);
		free(json_data);
		return 1;
	}
	json_data[file_size] = '\0';  // Null-terminate the string

	// Close the file
	fclose(file);

	// Parse the JSON data
	cJSON* data = cJSON_Parse(json_data);
	if (data == NULL) {
		printf("[%s][Error] Failed to parse JSON data.\n", __func__);
		return NULL;
	}
	// Print JSON data 
#if PRINT_DEBUG
	printf("[%s] json_data %s.\n", __func__, json_data);
#endif

	//const char* key = "yolov4_tiny";

	cJSON* yolov4_tiny_obj = cJSON_GetObjectItemCaseSensitive(data, key);
	if (yolov4_tiny_obj == NULL) {
		printf("Key '%s' not found.\n", key);
		cJSON_Delete(data);
		return NULL;
	}

	cJSON* file_obj = cJSON_GetObjectItemCaseSensitive(yolov4_tiny_obj, "file");
	if (file_obj == NULL) {
		printf("Attribute \"file\" not found！\n");
		cJSON_Delete(data);
		return 1;
	}

	const char* value = file_obj->valuestring;

	printf("[%s][Info] Output: %s\n", __func__, value);

	// Clean up cJSON object and allocated memory
	cJSON_Delete(data);
	free(json_data);

	return value;
}

int isDirExists(const char* path) {
	DIR* dir;
	struct dirent* ent;
	int count = 0;

	// check weather dir is valid
	if ((dir = opendir(path)) != NULL) {
		/* print all the files and directories within directory */
		while ((ent = readdir(dir)) != NULL) {
			if (ent->d_type == DT_DIR) {
				count++;
#if PRINT_DEBUG
				printf("[%s] Folder:%s\n", __func__, ent->d_name);
#endif
			}
			if (ent->d_type == DT_REG) {
				count++;
#if PRINT_DEBUG
				printf("[%s] File:%s\n", __func__, ent->d_name);
#endif
			}
		}
		if (count == 2) {
			/* Empty directory that contains "." and ".." only */
#if PRINT_DEBUG
			printf("[%s][Error] Empty directory found\n", __func__);
#endif
			return 0;
		}
		closedir(dir);
		return count;
	}
	else if (ENOENT == errno) {
#if PRINT_DEBUG
		printf("[%s][Error] Directory does not exist\n", __func__);
#endif
		return 0;
	}
	else {
		/* opendir() failed for some other reason. */
		return 0;
	}
}

int endsWith(const char* str, const char* suffix) {
	size_t str_len = strlen(str);
	size_t suffix_len = strlen(suffix);
	if (suffix_len > str_len) {
		return 0;
	}
	return strncmp(str + str_len - suffix_len, suffix, suffix_len) == 0;
}

const char* input2model(const char* input) {
	const char* model_mapping[][2] = {
		{"CUSTOMIZED_YOLOV3TINY",    "yolov3_tiny"},
		{"CUSTOMIZED_YOLOV4TINY",    "yolov4_tiny"},
		{"CUSTOMIZED_YOLOV7TINY",    "yolov7_tiny"},
		{"CUSTOMIZED_MOBILEFACENET", "mobilefacenet_i16"},
		{"CUSTOMIZED_SCRFD",         "scrfd640"},
		{"DEFAULT_YOLOV3TINY",       "yolov3_tiny"},
		{"DEFAULT_YOLOV4TINY",       "yolov4_tiny"},
		{"DEFAULT_YOLOV7TINY",       "yolov7_tiny"},
		{"DEFAULT_MOBILEFACENET",    "mobilefacenet_i8"},
		{"DEFAULT_SCRFD",            "scrfd320p"}
	};

	int mapping_size = sizeof(model_mapping) / sizeof(model_mapping[0]);

	for (int i = 0; i < mapping_size; i++) {
		if (strcmp(input, model_mapping[i][0]) == 0) {
			return model_mapping[i][1];
		}
	}

	return "NA";
}

int dirExists(const char* directory_path) {
	DIR* directory = opendir(directory_path);
	// check weather dir is valid
	if (directory) {
		closedir(directory);
		return 1;
	}
	else {
		printf("[%s][Error] Failed to open directory.\n", __func__);
		return 0;
	}
}

const char* dirName(const char* directory_path) {
	int sdk_counter = 0;
	struct dirent* entry;
	DIR* directory = opendir(directory_path);
	const char* sdk_name = "";
	// check dir validation
	if (directory) {
		while ((entry = readdir(directory)) != NULL) {
#ifdef __APPLE__
            if(strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0 || strcmp(entry->d_name, ".DS_Store") == 0) {
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
		// non singular SDK validation
		if (sdk_counter > 1) {
			goto error_non_singular;
		}
		else {
			return sdk_name;
		}
	}
	else {
		printf("[%s][Error] Failed to open directory.\n", __func__);
	}
	closedir(directory);

error_non_singular:
	error_handler("AmebaPro2 directory only allow 1 SDK!!! Please check again.");
}

void resetTXT(const char* directory_path) {
	DIR* dir = opendir(directory_path);
	struct stat st;

	// create directory if not exists
	if (stat(dir, &st) == -1) {
		mkdir(dir, 0700);
	}
	strcat(directory_path, fname_txt);

	// open txt file and clear everything
	FILE* file = fopen(directory_path, "w");
	if (file != NULL) {

	}
}

void updateTXT(const char* input) {
	//strcat(path_txt, fname_txt);
	FILE* file = fopen(path_txt, "a");

	if (file) {
		fprintf(file, "%s\n", input);
		fclose(file);
	}
	else {
#if PRINT_DEBUG
		printf("[%s][Error] Failed to open the file.\n", __func__);
#endif	
		perror(path_txt);
		// qqz return EXIT_FAILURE;
	}
}

const char* pathTempJSON(const char* directory_path, const char* ext, const char* key) {
	DIR* dir;
	struct dirent* ent;

#if PRINT_DEBUG
	printf("[%s][INFO] Load json file in dir \"%s\"\n", __func__, directory_path);
#endif
	if ((dir = opendir(directory_path)) != NULL) {
		/* print all the files and directories within directory */
		while ((ent = readdir(dir)) != NULL) {
			if (ent->d_type == DT_REG && strstr(ent->d_name, ext_json) != NULL && strstr(ent->d_name, key_json) != NULL) {
#if PRINT_DEBUG
				printf("[%s][INFO] File: %s\n", __func__, ent->d_name);
#endif
				strcat(directory_path, backspace);
				strcat(directory_path, ent->d_name);
				return directory_path;
				/*

				size_t size_file = strlen(ent->d_name);
				size_t size_json = strlen(ext);
				const char* jsonfilename = strstr(ent->d_name, key);

				if (size_file >= size_json && strcmp(ent->d_name + size_file - size_json, ext) == 0) {
					if (strlen(jsonfilename) != 0 && strlen(jsonfilename) == strlen(ent->d_name)) {
#if PRINT_DEBUG
						printf("[%s][INFO] File: %s\n", __func__, ent->d_name);
#endif
						strcat(directory_path, backspace);
						strcat(directory_path, jsonfilename);

					}
					return directory_path;
				}*/
			}
		}
	}
}

cJSON* loadJSONFile(const char* directory_path) {
	FILE* file = fopen(directory_path, "rb");
	if (file == NULL) {
		printf("[%s][Error] Failed to open the file.\n", __func__);
		perror("Error opening file");
		printf("Error code: %d\n", errno);
		return 1;
	}

	// Get the file size
	fseek(file, 0, SEEK_END);
	size_t file_size = ftell(file);
	fseek(file, 0, SEEK_SET);
	rewind(file);

	// Allocate memory to hold the JSON data
	char* json_data = (char*)malloc(file_size + 1);
	if (json_data == NULL) {
		printf("[%s][Error] Failed to allocate memory.\n", __func__);
		fclose(file);
		return 1;
	}

	// Read the JSON data from the file
	size_t read_size = fread(json_data, 1, file_size, file);
#if PRINT_DEBUG
	printf("[%s][Info] read_size %d\n", __func__, read_size);
	printf("[%s][Info] file_size %d\n", __func__, file_size);
#endif
	if (read_size != file_size) {
		printf("[%s][Error] Failed to read the file.\n", __func__);
		fclose(file);
		free(json_data);
		return 1;
	}
	json_data[file_size] = '\0';  // Null-terminate the string

	// Close the file
	fclose(file);

	// Parse the JSON data
	cJSON* data = cJSON_Parse(json_data);
	if (data == NULL) {
		printf("[%s][Error] Failed to parse JSON data.\n", __func__);
		return NULL;
	}
	// print JSON data 
#if PRINT_DEBUG
	printf("[%s] json_data %s.\n", __func__, json_data);
#endif

	// Clean up cJSON object and allocated memory
	//cJSON_Delete(data);
	free(json_data);

	return data;
}

void removeChar(char* str, char c) {
	int i, j;
	int len = strlen(str);
	for (i = j = 0; i < len; i++) {
		if (str[i] != c) {
			str[j++] = str[i];
		}
	}
	str[j] = '\0';
}

const char* validateINO(const char* directory_path) {
	DIR* dir;
	struct dirent* ent;

	// Open the JSON file and retrive the data
	cJSON* data = loadJSONFile(path_build_options_json);	
	// Arduino IDE1.0 
	cJSON* path_example = cJSON_GetObjectItem(data, "sketchLocation");
#if PRINT_DEBUG
	printf("[%s][INFO] Current example path: %s \n", __func__, path_example->valuestring);
#endif	

	return path_example->valuestring;
}

void extractParam(char* line, char* param) {
	char* start = strchr(line, '(');
	char* end = strchr(line, ')');
	if (start != NULL && end != NULL && end > start) {
		size_t length = end - start - 1;
		strncpy(param, start + 1, length);
		param[length] = '\0';
	}
}

void error_handler(const char* message) {
	fprintf(stderr, "[Error] %s\n", message);
	exit(1);
}

void extractString(char* source, char* result) {
	char* start = strchr(source, '\"'); // find the 1st "
	if (start == NULL) {
		strcpy(result, ""); // set as empty string if not found
		return;
	}

	start++; // skip the first "

	char* end = strchr(start, '\"'); // find the 2nd "
	if (end == NULL) {
		strcpy(result, ""); // set as empty string if not found
		return;
	}

	int length = end - start;
	strncpy(result, start, length);
	result[length] = '\0'; // add ending param at EOL
}

void extractString2(char* source, char* result) {
	char* start = strchr(source, '<'); // find the 1st <
	if (start == NULL) {
		strcpy(result, ""); // set as empty string if not found
		return;
	}

	start++; // skip the first "

	char* end = strchr(start, '>'); // find the 1st >
	if (end == NULL) {
		strcpy(result, ""); // set as empty string if not found
		return;
	}

	int length = end - start;
	strncpy(result, start, length);
	result[length] = '\0'; // add ending param at EOL
}

void extractRootDirectory(char* filepath, char* rootDir) {
#ifdef _WIN32
	char* lastBackslash = strrchr(filepath, '\\');
#else
	char* lastBackslash = strrchr(filepath, '/');
#endif
	if (lastBackslash != NULL) {
		*lastBackslash = '\0';
	}
}

void resetJSON(const char* input) {
	DIR* dir;
	struct dirent* entry;

	dir = opendir(input);
	if (dir == NULL) {
		perror("Error opening directory");
		return;
	}

	while ((entry = readdir(dir)) != NULL) {
		if (strstr(entry->d_name, ".json") != NULL) {
			char filepath[256];
			snprintf(filepath, sizeof(filepath), "%s/%s", input, entry->d_name);

			FILE* file = fopen(filepath, "r");
			if (file == NULL) {
				perror("Error opening file");
				continue;
			}

			fseek(file, 0, SEEK_END);
			long file_size = ftell(file);
			fseek(file, 0, SEEK_SET);

			char* file_contents = (char*)malloc(file_size + 1);
			fread(file_contents, file_size, 1, file);
			fclose(file);

			cJSON* root = cJSON_Parse(file_contents);
			if (root == NULL) {
				fprintf(stderr, "Error parsing JSON in file: %s\n", entry->d_name);
				free(file_contents);
				continue;
			}

			cJSON* fwfs = cJSON_GetObjectItemCaseSensitive(root, "FWFS");
			if (fwfs == NULL || !cJSON_IsObject(fwfs)) {
				cJSON_Delete(root);
				free(file_contents);
				fprintf(stderr, "Invalid JSON format in file: %s\n", entry->d_name);
				continue;
			}

			cJSON* files = cJSON_GetObjectItemCaseSensitive(fwfs, "files");
			if (files == NULL || !cJSON_IsArray(files)) {
				cJSON_Delete(root);
				free(file_contents);
				fprintf(stderr, "Invalid JSON format in file: %s\n", entry->d_name);
				continue;
			}

			cJSON_DeleteItemFromObject(fwfs, "files");

			cJSON* new_files = cJSON_CreateArray();
			cJSON_AddItemToObject(fwfs, "files", new_files);

			char* new_file_contents = cJSON_Print(root);
			cJSON_Delete(root);
			free(file_contents);

			FILE* new_file = fopen(filepath, "w");
			if (new_file == NULL) {
				perror("Error opening file for writing");
				free(new_file_contents);
				continue;
			}

			fwrite(new_file_contents, strlen(new_file_contents), 1, new_file);
			fclose(new_file);
			free(new_file_contents);
		}
	}

	closedir(dir);
}

char* dspFileProp(const char* filename) {
	struct stat file_model_stats;
	if (stat(filename, &file_model_stats) == -1) {
		fprintf(stderr, "[Error] Default model %s does not exist. Please check %s again.\n", filename, filename);
		exit(1);
	}
	// Get the file creation time
	time_t fileCreationTime = file_model_stats.st_mtime;

	// Format the file creation time
	char fileCreationDate[11];
	strftime(fileCreationDate, sizeof(fileCreationDate), "%Y-%m-%d", localtime(&fileCreationTime));


#if PRINT_DEBUG
	printf("[%s][INFO] File creation date: %s\n",__func__, fileCreationDate);
#endif
	return fileCreationDate;
}

void copyFile(const char* sourcePath, const char* destinationPath) {
	FILE* sourceFile;
	FILE* destinationFile;
	char buffer[BUFFER_SIZE];
	size_t bytesRead;

	// Open the source file for reading
	sourceFile = fopen(sourcePath, "rb");
	if (sourceFile == NULL) {
		printf("Failed to open the source file: %s\n", sourcePath);
		return;
	}

	// Open the destination file for writing
	destinationFile = fopen(destinationPath, "wb");
	if (destinationFile == NULL) {
		printf("Failed to create the destination file: %s\n", destinationPath);
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

#if PRINT_DEBUG
	printf("File copied successfully.\n");
#endif
}

void renameFile(char* filename, int type) {
	char dest_path[100] = "";					// Replace with the desired destination path

	if (type == 1) {							// Backup Dmodel
		char filename_modified[200] = "";
		
		// original model filename
		strcat(path_model, backspace);
		strcat(path_model, filename);

		// Construct the modified model filename
		strcat(filename_modified, "Dbackup_");
		strcat(filename_modified, dspFileProp(path_model));
		strcat(filename_modified, "_");
		strcat(filename_modified, filename);

		extractRootDirectory(path_model, dir_model);
		char source_path[300] = "";
		strcat(source_path, path_model);
		strcat(source_path, backspace);
		strcat(source_path, filename);

		char destination_path[300] = "";
		strcat(destination_path, path_model);
		strcat(destination_path, backspace);
        strcat(destination_path, filename_modified);

		// copying file from source path -> dest path
		copyFile(source_path, destination_path);
#if PRINT_DEBUG
		printf("[%s][INFO] Dmodel Backup done.\n", __func__);
#endif
	}
	else {										// Backup Cmodel
		char filename_modified[200] = "";
			
		// Construct the modified filename
		strcat(filename_modified, "Cbackup_");
		strcat(filename_modified, dspFileProp(path_model));
		strcat(filename_modified, "_");
		strcat(filename_modified, filename);

		char source_path[300] = "";
		strcat(source_path, dir_example);
		strcat(source_path, backspace);
		strcat(source_path, filename);

		char destination_path[300] = "";
		//extractRootDirectory(path_model, dir_model);
		strcat(destination_path, path_model);
		strcat(destination_path, backspace);
		strcat(destination_path, filename_modified);
		copyFile(source_path, destination_path);
#if PRINT_DEBUG
		printf("[%s][INFO] Cmodel Backup done.\n", __func__);
#endif
		char destination_path2[300] = "";
		strcat(destination_path2, path_model);
		strcat(destination_path2, backspace);
		strcat(destination_path2, filename);
		copyFile(source_path, destination_path2);
#if PRINT_DEBUG
		printf("[%s][INFO] Cmodel copy done.\n", __func__);
#endif
	}
}

void backupModel(char* input, char* sktech_path) {
	DIR* dir = opendir(path_model);
	bool flag_Dbackup = 0;
	/* check whether default example has been back up */
	if (dir) {
		struct dirent* entry;
		while ((entry = readdir(dir)) != NULL) {
			if (strstr(entry->d_name, "Dbackup") != NULL) {		// customized model has been used
				//printf("[%s][INFO] Backup-ed %s found !!!\n", __func__, input);
				flag_Dbackup = 1;
				break;
			}
		}
		closedir(dir);
	}

	if (flag_Dbackup) {
		renameFile(input, 0);										// back up Cmodel
	}
	else {
		renameFile(input, 1);										// back up Dmodel
		renameFile(input, 0);										// back up Cmodel
	}
}

void revertModel(const char* dmodel_name, const char* dmodel_name_backup, const char* dmodel_path) {
	char source_path[300] = "";
	strcat(source_path, dmodel_path);
	strcat(source_path, backspace);
	strcat(source_path, dmodel_name_backup);

	char destination_path[300] = "";
	strcat(destination_path, dmodel_path);
	strcat(destination_path, backspace);
	strcat(destination_path, dmodel_name);

	copyFile(source_path, destination_path);
#if PRINT_DEBUG
	printf("[%s][INFO] Dmodel Revert done.\n", __func__);
#endif
}

int writeJSON(const char* f_path) {
	DIR* dir;
	struct dirent* ent;
	const char buf[MAX_PATH_LENGTH] = "";
	const char backslash[] = "\\";
	char line[MAX_PATH_LENGTH] = { 0 };
	unsigned int line_count = 0;
	char voe_status[100] = "NA";
	char model_type[100] = "";
	char model_name_od[100] = "";
	char model_name_fd[100] = "";
	char model_name_fr[100] = "";
	char header_od[100] = "NA";
	char header_fd[100] = "NA";
	char header_fr[100] = "NA";
	char header_all[100] = "";
	char fname_od[100] = "NA";
	char fname_fd[100] = "NA";
	char fname_fr[100] = "NA";
	char line_strip_header[100] = "NA";
	char line_strip_headerNN[100] = "NA";
	

	f_path = path_example;

#if PRINT_DEBUG
	printf("[%s][INFO] Load example: \"%s\"\n", __func__, f_path);
#endif
	
	/* check path format : IDE1 file path, IDE2 dir path */ 
	if (strstr(f_path, ".ino") == NULL) {
#if PRINT_DEBUG
		printf("IDE2\n");
#endif
		DIR* dir;
		struct dirent* ent;

		// check weather dir is valid
		if ((dir = opendir(f_path)) != NULL) {
			/* print all the files and directories within directory */
			while ((ent = readdir(dir)) != NULL) {
				if (ent->d_type == DT_REG && strstr(ent->d_name, ".ino") != NULL) {
#if PRINT_DEBUG
					printf("[%s] File:%s\n", __func__, ent->d_name);
#endif
					strcat(f_path, backspace);
					strcat(f_path, ent->d_name);
					printf("[%s] path:%s\n", __func__, f_path);
				}
			}
		}
		else {
			/* opendir() failed for some other reason. */
			printf("[%s][Error] Faield to open temp dir in IDE2.0 :%s\n", __func__, f_path);
			// qqz return EXIT_FAILURE;
		}
	}
	
	FILE* f_model = fopen(f_path, "r");
	char param[100];
	if (f_model) {
		char line[MAX_PATH_LENGTH];
		while (fgets(line, sizeof(line), f_model)) {
			/* check whether keywordNN in f_model content */
			if (strstr(line, key_amb_NN) != NULL && strstr(line, "//") == NULL && strstr(line, key_amb_bypassNN1) == NULL && strstr(line, key_amb_bypassNN2) == NULL) {
				extractParam(line, param);
				//printf("Extracted parameter: %s\n", param);
				char* token;
				token = strtok(param, ", ");
				if (token != NULL) {
					strcpy(model_type, token);
					//printf("Model Type: %s\n", model_type);
					/* ------------------ object detection ------------------*/
					token = strtok(NULL, ", ");
					// printf("1 token: %s\n", token);
					if (token != NULL) {
						// check model combination rules
						if (strcmp(model_type, "OBJECT_DETECTION") == 0) {
							if (strcmp(token, "NA_MODEL") == 0 || strstr(token, "YOLO") == NULL) {
								goto error_combination;
							}
							// check customized od model
							if (strstr(token, key_amb_customized) != NULL) {
								printf("-----------------------------------------\n");
								printf("  fd key_amb_customized\n");
								printf("  customized fd: %s\n", input2model(token));
								// goto path_model and open the file ends with .json
								if (dirExists(path_model)) {
									DIR* dir = opendir(path_model);
									struct dirent* entry;

									while ((entry = readdir(dir)) != NULL) {
										if (endsWith(entry->d_name, ".json")) {
											char fpath_nn_json[MAX_PATH_LENGTH];
											char dir_nn_json[MAX_PATH_LENGTH];

											sprintf(fpath_nn_json, "%s\\%s", path_model, entry->d_name);
											cJSON* fname_model = input2filename(fpath_nn_json, input2model(token));
											strcpy(fname_od, fname_model);
										}
									}
									closedir(dir);
								}
								extractRootDirectory(path_example, dir_example);
								dir_example = path_example;

								DIR* dir;
								struct dirent* ent;
								int count = 0;

								/* check weather example directory is valid */
								if ((dir = opendir(path_example)) != NULL) {
									/* print all the files and directories within directory */
									while ((ent = readdir(dir)) != NULL) {
										if (ent->d_type == DT_REG && strstr(ent->d_name, ".nb") != NULL) {
											count++;
										}
										if (strstr(ent->d_name, ".nb") != NULL) {
											if (strstr(ent->d_name, "yolo") != NULL) {			// 1. check model file (.nb) within example directory 
#if PRINT_DEBUG
												printf("[%s] model fname %s\n", __func__, ent->d_name);
												printf("[%s] json fname %s\n", __func__, fname_od);
#endif
												if (strcmp(ent->d_name, fname_od) != 0) {		// 2. check exampel file name whether matches in json
													goto error_customized_mismatch;
												}
												else {
#if PRINT_DEBUG
													printf("[%s][Info] Found customized model %s\n", __func__, ent->d_name);
#endif
													backupModel(ent->d_name, dir_example);
												}
											}
											else {
												goto error_customized_mismatch;					// 3. check model file (.nb) existance
											}
										}
									}
								}
								printf("[%s] %d\n", __func__, count);
								if (count < 1) {
									goto error_customized_missing;
								}
							}
							else {
								DIR* dir = opendir(path_model);
								bool flag_Dbackup = 0;
								char fname_dmodel[100];
								char fname_dmodel_backup[100];
								
								/* check whether default example has been back up */
								if (dir) {
									struct dirent* entry;
									while ((entry = readdir(dir)) != NULL) {
										if (strstr(entry->d_name, "Dbackup") != NULL) {				// customized model has been used
											flag_Dbackup = 1;
											strcpy(fname_dmodel_backup, entry->d_name);
											strcpy(model_name_od, token);
											
											char* input = "";
											input = input2model(model_name_od);
											char output[100];
											char* underscore = strchr(input, '_'); // Find the first occurrence of "_"
											if (underscore != NULL) {
												size_t length = underscore - input; // Calculate the length of the substring before "_"
												strncpy(output, input, length); // Copy the substring before "_" to the output variable
												output[length] = '\0'; // Add the null terminator at the end of the substring
											}
											char key[100] = "_";
											strcat(key,output);
											char* start = strstr(fname_dmodel_backup, key);		// Find the starting position of the substring
											if (start != NULL) {
												strcat(key, "_");
												start += strlen(key);							// Move the pointer past the substring
												strcat(output, "_");
												strcpy(fname_dmodel, output);
												strcat(fname_dmodel, start);
											}
										}
									}
									closedir(dir);
								}

								if (flag_Dbackup) {
									revertModel(fname_dmodel, fname_dmodel_backup, path_model);
								}
							}
						}
						strcpy(model_name_od, token);

						/* ----------------- face detection -----------------*/
						token = strtok(NULL, ", ");
						// printf("2 token: %s\n", token);
						if (token != NULL) {
							// check model combination rules
							if (strcmp(model_type, "FACE_DETECTION") == 0) {
								if (strcmp(token, "NA_MODEL") == 0 || strstr(token, "SCRFD") == NULL) {
									goto error_combination;
								}
								/* check customized fd model */
								if (strstr(token, key_amb_customized) != NULL) {
									printf("-----------------------------------------\n");
									printf("  fd key_amb_customized\n");
									printf("  customized fd: %s\n", input2model(token));
									// goto path_model and open the file ends with .json
									if (dirExists(path_model)) {
										DIR* dir = opendir(path_model);
										struct dirent* entry;

										while ((entry = readdir(dir)) != NULL) {
											if (endsWith(entry->d_name, ".json")) {
												char fpath_nn_json[MAX_PATH_LENGTH];
												char dir_nn_json[MAX_PATH_LENGTH];

												sprintf(fpath_nn_json, "%s\\%s", path_model, entry->d_name);
												cJSON* fname_model = input2filename(fpath_nn_json, input2model(token));
												strcpy(fname_od, fname_model);
											}
										}
										closedir(dir);
									}
									extractRootDirectory(path_example, dir_example);
									dir_example = path_example;

									DIR* dir;
									struct dirent* ent;
									int count = 0;

									/* check weather example directory is valid */
									if ((dir = opendir(path_example)) != NULL) {
										/* print all the files and directories within directory */
										while ((ent = readdir(dir)) != NULL) {
											if (ent->d_type == DT_REG && strstr(ent->d_name, ".nb") != NULL) {
												count++;
											}
											if (strstr(ent->d_name, ".nb") != NULL) {
												if (strstr(ent->d_name, "scrfd") != NULL) {		// 1. check model file (.nb) within example directory 
#if PRINT_DEBUG
													printf("[%s] model fname %s\n", __func__, ent->d_name);
													printf("[%s] json fname %s\n", __func__, fname_od);
#endif
													if (strcmp(ent->d_name, fname_od) != 0) {	// 2. check exampel file name whether matches in json
														goto error_customized_mismatch;
													}
													else {
#if PRINT_DEBUG
														printf("[%s][Info] Found customized model %s\n", __func__, ent->d_name);
#endif
														backupModel(ent->d_name, dir_example);
													}
												}
												else {
													goto error_customized_mismatch;				// 3. check model file (.nb) existance
												}
											}
										}
									}
									printf("[%s] %d\n", __func__, count);
									if (count <= 1) {
										goto error_customized_missing;
									}
								}
								else {
									DIR* dir = opendir(path_model);
									bool flag_Dbackup = 0;
									char fname_dmodel[100];
									char fname_dmodel_backup[100];
									/* check whether default example has been back up */
									if (dir) {
										struct dirent* entry;
										while ((entry = readdir(dir)) != NULL) {
											if (strstr(entry->d_name, "Dbackup") != NULL) {			// customized model has been used
												flag_Dbackup = 1;
												strcpy(fname_dmodel_backup, entry->d_name);
												char* start = strstr(fname_dmodel_backup, "_scrfd");		// Find the starting position of the substring
												if (start != NULL) {
													start += strlen("_scrfd_");						// Move the pointer past the substring
													strcpy(fname_dmodel, "scrfd_");
													strcat(fname_dmodel, start);
												}
											}
										}
										closedir(dir);
									}

									if (flag_Dbackup) {
										revertModel(fname_dmodel, fname_dmodel_backup, path_model);
									}
								}
							}
							strcpy(model_name_fd, token);

							/*-------------- face recognition --------------*/
							token = strtok(NULL, ", ");
							// printf("3 token: %s\n", token);
							// check model combination rules
							if (strcmp(model_type, "FACE_RECOGNITION") == 0) {
								if (strcmp(model_name_fd, "NA_MODEL") == 0 || strstr(model_name_fd, "SCRFD") == NULL || strcmp(token, "NA_MODEL") == 0 || strstr(token, "MOBILEFACENET") == NULL) {
									goto error_combination;
								}
								// check customized fr model
								if (strstr(token, key_amb_customized) != NULL) {
									printf("-----------------------------------------\n");
									printf("	fr key_amb_customized\n");
									printf("	customized fr: %s\n", input2model(token));
									// goto path_model and open the file ends with .json
									if (dirExists(path_model)) {
										DIR* dir = opendir(path_model);
										struct dirent* entry;

										while ((entry = readdir(dir)) != NULL) {
											if (endsWith(entry->d_name, ".json")) {
												char fpath_nn_json[MAX_PATH_LENGTH];
												char dir_nn_json[MAX_PATH_LENGTH];

												sprintf(fpath_nn_json, "%s\\%s", path_model, entry->d_name);
												cJSON* fname_model = input2filename(fpath_nn_json, input2model(token));
												strcpy(fname_od, fname_model);
											}
										}
										closedir(dir);
									}
									extractRootDirectory(path_example, dir_example);
									dir_example = path_example;

									DIR* dir;
									struct dirent* ent;
									int count = 0;

									/* check weather example directory is valid */
									if ((dir = opendir(path_example)) != NULL) {
										/* print all the files and directories within directory */
										while ((ent = readdir(dir)) != NULL) {
											if (ent->d_type == DT_REG && strstr(ent->d_name, ".nb") != NULL) {
												count++;
											}
											if (strstr(ent->d_name, ".nb") != NULL) {
												if (strstr(ent->d_name, "mobilefacenet") != NULL) {		// 1. check model file (.nb) within example directory 
#if PRINT_DEBUG
													printf("[%s] model fname %s\n", __func__, ent->d_name);
													printf("[%s] json fname %s\n", __func__, fname_od);
#endif
													if (strcmp(ent->d_name, fname_od) != 0) {			// 2. check exampel file name whether matches in json
														goto error_customized_mismatch;
													}
													else {
#if PRINT_DEBUG
														printf("[%s][Info] Found customized model %s\n", __func__, ent->d_name);
#endif
														backupModel(ent->d_name, dir_example);
													}
												}
												else {
													goto error_customized_mismatch;						// 3. check model file (.nb) existance
												}
											}
										}
									}
									printf("[%s] %d\n", __func__, count);
									if (count <= 1) {
										goto error_customized_missing;
									}
								}
								else {
									DIR* dir = opendir(path_model);
									bool flag_Dbackup = 0;
									char fname_dmodel[100];
									char fname_dmodel_backup[100];
									/* check whether default example has been back up */
									if (dir) {
										struct dirent* entry;
										while ((entry = readdir(dir)) != NULL) {
											if (strstr(entry->d_name, "Dbackup") != NULL) {			// customized model has been used
												flag_Dbackup = 1;
												strcpy(fname_dmodel_backup, entry->d_name);
												char* start = strstr(fname_dmodel_backup, "_mobilefacenet");		// Find the starting position of the substring
												if (start != NULL) {
													start += strlen("_mobilefacenet_");						// Move the pointer past the substring
													strcpy(fname_dmodel, "mobilefacenet_");
													strcat(fname_dmodel, start);
												}
											}
										}
										closedir(dir);
									}

									if (flag_Dbackup) {
										revertModel(fname_dmodel, fname_dmodel_backup, path_model);
									}
								}
							}
							if (token != NULL) {
								strcpy(model_name_fr, token);
							}
						}
					}

					/* default settings for all models */
					else {
						/* provide default settings for all models if user never provide any selections*/
						if (strcmp(model_type, "OBJECT_DETECTION") == 0 && strcmp(input2model(model_name_od), "NA") == 0) {
							strcpy(model_name_od, "DEFAULT_YOLOV4TINY");
							strcpy(model_name_fd, "NA_MODEL");
							strcpy(model_name_fr, "NA_MODEL");
						}
						if (strcmp(model_type, "FACE_DETECTION") == 0 && strcmp(input2model(model_name_od), "NA") == 0) {
							strcpy(model_name_od, "NA_MODEL");
							strcpy(model_name_fd, "DEFAULT_SCRFD");
							strcpy(model_name_fr, "NA_MODEL");
						}
						if (strcmp(model_type, "FACE_RECOGNITION") == 0 && strcmp(input2model(model_name_od), "NA") == 0) {
							strcpy(model_name_od, "NA_MODEL");
							strcpy(model_name_fd, "DEFAULT_SCRFD");
							strcpy(model_name_fr, "DEFAULT_MOBILEFACENET");
						}
					}
				}
				fclose(f_model);
#if PRINT_DEBUG
				printf("-------------------------------------\n");
				printf("Model Name OD: %s\n", input2model(model_name_od));
				printf("Model Name FD: %s\n", input2model(model_name_fd));
				printf("Model Name FR: %s\n", input2model(model_name_fr));
				printf("-------------------------------------\n");
#endif
				if (strstr(input2model(model_name_od), "NA") == NULL) {
					updateJSON(input2model(model_name_od), path_model);
				}
				if (strstr(input2model(model_name_fd), "NA") == NULL) {
					updateJSON(input2model(model_name_fd), path_model);
				}
				if (strstr(input2model(model_name_fr), "NA") == NULL) {
					updateJSON(input2model(model_name_fr), path_model);
				}
			}
		}
	}
	return 0;

error_combination:
	error_handler("Model combination mismatch. Please check modelSelect() again.");

error_customized_missing:
	error_handler("Model missing. Please check your sketch folder again.");

error_customized_mismatch:
	error_handler("Customized model mismatch. Please check your sketch folder again.");
}

void updateJSON(const char* input, const char* destPath) {
	DIR* dir;
	struct dirent* entry;
	// Open the destination directory
	dir = opendir(destPath);
	if (dir == NULL) {
		printf("Failed to open the destination directory: %s\n", destPath);
		return;
	}

	while ((entry = readdir(dir)) != NULL) {
		const char* destFile = entry->d_name;

		// Check if the destination file is a JSON file
		if (strstr(destFile, ".json") != NULL) {
#if PRINT_DEBUG
			printf("Processing JSON file: %s\n", destFile);
#endif
			// Open the JSON file
			char filePath[256];
			snprintf(filePath, sizeof(filePath), "%s/%s", destPath, destFile);
			FILE* jsonFile = fopen(filePath, "r");
			if (jsonFile == NULL) {
				printf("Failed to open the JSON file: %s\n", filePath);
				continue;
			}
			
			// Read the contents of the JSON file
			fseek(jsonFile, 0, SEEK_END);
			long fileSize = ftell(jsonFile);
			fseek(jsonFile, 0, SEEK_SET);
			char* jsonContent = malloc(fileSize + 1);
			fread(jsonContent, 1, fileSize, jsonFile);
			fclose(jsonFile);
			jsonContent[fileSize] = '\0';
					
			// Parse the JSON data
			cJSON* root = cJSON_Parse(jsonContent);
			free(jsonContent);
			if (root == NULL) {
				printf("Failed to parse the JSON data.\n");
				continue;
			}

			// Access the "FWFS" object
			cJSON* fwfsObject = cJSON_GetObjectItem(root, "FWFS");
			if (fwfsObject == NULL) {
				printf("Failed to access the \"FWFS\" object.\n");
				cJSON_Delete(root);
				continue;
			}

			// Access the "files" array
			cJSON* filesArray = cJSON_GetObjectItem(fwfsObject, "files");
			if (filesArray == NULL || !cJSON_IsArray(filesArray)) {
				printf("Failed to access the \"files\" array.\n");
				cJSON_Delete(root);
				continue;
			}

			// Create a cJSON item for the input
			cJSON* inputItem = cJSON_CreateString(input);
			if (inputItem == NULL) {
				printf("Failed to create cJSON item for the input.\n");
				cJSON_Delete(root);
				continue;
			}

			// Add the input item to the files array
			cJSON_AddItemToArray(filesArray, inputItem);

			// Convert the JSON data to a formatted string
			char* updatedJsonString = cJSON_PrintBuffered(root, 4096, cJSON_True);

			// Open the JSON file for writing
			jsonFile = fopen(filePath, "w");
			if (jsonFile == NULL) {
				printf("Failed to open the JSON file for writing.\n");
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