/*******************************************************************************************************************************************************************
*  README
*
*  COMPILATION
* Windows:          VS Build Solution
*                   MINGW64 git bash
*                       $gcc.exe -o nn_model_update_windows.exe nn_model_update.c cJSON.c ../../../../Ameba_Icon/ico-out.o
*                       $strip nn_model_update_windows.exe
* Linux/macOS:      open terminal and execute "make clean;make" command
*
*******************************************************************************************************************************************************************/
#define _GNU_SOURCE

#ifdef _WIN32
#include <io.h>
#include "dirent.h"     // https://codeyarns.com/tech/2014-06-06-how-to-use-dirent-h-with-visual-studio.html#gsc.tab=0
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

#define PRINT_DEBUG         0
#define MAX_PATH_LENGTH     1024
#define BUFFER_SIZE         4096

// -------------------------------
//           Headers
// -------------------------------
// File operations
/* Copy files from source to destination dir, can be merged with renameFile */
void copyFile(const char* sourcePath, const char* destinationPath);
/* Declear function headers */
int dirExists(const char* directory_path);
/* Return folder names under current directory */
const char* dirName(const char* directory_path);
/* Function returns nuber of content under this path */
int isDirExists(const char* path);
/* Recursively list out all files under given basePath */
void listExampleDir(char* basePath, char* examplePath);
/* Find the dir name of input source file path*/
void extractRootDirectory(char* source, char* result);
/* Add prefix Dmodel/Cmodel for backup .nb files */
void renameFile(char* filename, char* filepath, int type);
/* Retrun the date in YYYY-MM-DD of the file creation */
char* dspFileProp(const char* f_name);

// String operation
/* Functions below are for txt f_model manipulation */
int endsWith(const char* str, const char* suffix);
/* convert \\ in file path to \ */
const char* pathTidy(const char* input);
/* Remove char c from string str */
void removeChar(char* str, char c);
/* Similar function as REGEX*/
void extractParam(char* line, char* param);
/* Convert model input type to model name*/
const char* input2model(const char* input);
/* Convert model input to model filename as defined in json */
const char* input2filename(const char* directory_path, const char* key);

// Model operations
/* Backup files from source to destination dir, can be merged with renameFile */
void backupModel(char* input, char* sktech_path);
/* Revert Dmodel when user select Default model */
void revertModel(const char* dmodel_name, const char* dmodel_name_backup, const char* dmodel_path);

// Others
/* Handler to print error message in the Arduino IDE */
void error_handler(const char* message);
/* Validate example in directory_path and returns example path */
const char* validateINO(const char* directory_path);

// JSON operations
/* Clear nn model json file*/
void resetJSON(const char* input);
/* Update nn model json file*/
void updateJSON(const char* input, const char* destPath);
/* Returns example f_model path inside the temp JSON f_model */
const char* pathTempJSON(const char* directory_path, const char* ext, const char* key);
/* Load JSON f_model from the directory and parse into cJSON data format */
cJSON* loadJSONFile(const char* directory_path);
/* Function to update JSON */
int writeJSON(const char* f_path);


/* Declear global vairables */
const char* key_amb_NN = "modelSelect";
const char* key_amb_bypassNN1 = " .modelSelect";
const char* key_amb_bypassNN2 = " modelSelect";
const char* key_amb_VOE = "configVideoChannel";
const char* key_amb_bypassVOE1 = " .configVideoChannel";
const char* key_amb_bypassVOE2 = " configVideoChannel";
const char* key_amb_header = "#include";
const char* key_amb_customized = "CUSTOMIZED";
const char* key_json = "build";
const char* key_amb = "Arduino15";
const char* key_ino = ".ino";
const char* ext_json = ".json";
const char* key_amb_default = "DEFAULT";
const char* key_amb_default_backup = "Dbackup";
const char* key_amb_customized_backup = "Cbackup";
const char* fname_txt = "ino_validation.txt";
const char* dir_example = "NA";

/* Declear common file paths */
#ifdef _WIN32
char* path_arduino15_add = "\\AppData\\Local\\Arduino15";
char* path_ambpro2_add = "\\packages\\realtek\\hardware\\AmebaPro2\\";
char* path_model_add = "\\variants\\common_nn_models";
char* path_library_add = "\\libraries\\";
char* path_txtfile_add = "\\misc\\";
char* backspace = "\\";
#elif __linux__
char* path_arduino15_add = "/.arduino15";
char* path_ambpro2_add = "/packages/realtek/hardware/AmebaPro2/";
char* path_model_add = "/variants/common_nn_models";
char* path_library_add = "/libraries/";
char* path_txtfile_add = "/misc/";
char* backspace = "/";
#else
char* path_arduino15_add = "/Library/Arduino15";
char* path_ambpro2_add = "/packages/realtek/hardware/AmebaPro2/";
char* path_model_add = "/variants/common_nn_models";
char* path_library_add = "/libraries/";
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
char path_library[MAX_PATH_LENGTH];
char path_txtfile[MAX_PATH_LENGTH];
char folder_example[MAX_PATH_LENGTH];

// -------------------------------
//           Main
// -------------------------------
int main(int argc, char* argv[]) {
	setlocale(LC_ALL, "en_US.UTF-8");
	// Check if the number of input arguments is correct 
	if (argc != 3) {
		if (PRINT_DEBUG) printf("[Error] [%d] Incorrect number of input parameters. Expected 2 parameters.\r\n", __LINE__);
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
	strcpy(path_library, path_model);
	strcat(path_model, path_model_add);
	strcat(path_library, path_library_add);
	strcpy(path_txtfile, argv[2]);
	strcat(path_txtfile, path_txtfile_add);

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
	printf("path_library     = %s\n", path_library);
	printf("path_txtfile     = %s\n", path_txtfile);
#endif

	resetJSON(path_model);
	path_build_options_json = pathTempJSON(path_build, ext_json, key_json);
	path_example = validateINO(path_build);
	writeJSON(path_example);

	if (PRINT_DEBUG) printf("[%s]----END----\n", __func__);
	return 0;
}

// -------------------------------
//           Functions
// -------------------------------
#ifndef __MINGW64__
//extern int mkdir(char* filename);
#endif

void copyFile(const char* sourcePath, const char* destinationPath) {
	FILE* sourceFile;
	FILE* destinationFile;
	char buffer[BUFFER_SIZE];
	size_t bytesRead;

	// Open the source file for reading
	sourceFile = fopen(sourcePath, "rb");
	if (sourceFile == NULL) {
		if (PRINT_DEBUG) printf("[Wrn][%d] Failed to open the source file: %s\n", __LINE__, sourcePath);
		return;
	}

	// Open the destination file for writing
	destinationFile = fopen(destinationPath, "wb");
	if (destinationFile == NULL) {
		if (PRINT_DEBUG) printf("[Wrn][%d] Failed to create the destination file: %s\n", __LINE__, destinationPath);
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

	if (PRINT_DEBUG) printf("[%s][%d][INFO] File copied successfully: %s\n", __func__, __LINE__, destinationPath);
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
	struct dirent* ent;
	DIR* directory = opendir(directory_path);
	const char* sdk_name = "";
	// check dir validation
	if (directory) {
		while ((ent = readdir(directory)) != NULL) {
#ifdef __APPLE__
			if (strcmp(ent->d_name, ".") == 0 || strcmp(ent->d_name, "..") == 0 || strcmp(ent->d_name, ".DS_Store") == 0) {
#else
			if (strcmp(ent->d_name, ".") == 0 || strcmp(ent->d_name, "..") == 0) {
#endif
				continue;
			}
			else {
				sdk_counter++;
				sdk_name = ent->d_name;
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

void listExampleDir(char* basePath, char* exampleName)
{
	char path[1000];
	struct dirent* dp;
	DIR* dir = opendir(basePath);

	// Unable to open directory stream
	if (!dir)
		return;
	while ((dp = readdir(dir)) != NULL)
	{
		if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0)
		{
			if (strstr(path, exampleName) != NULL && (!strcmp(&path[strlen(path) - strlen(exampleName)], exampleName))) {
				//printf("%s\n", path);  
				strcpy(folder_example, path);
			}
			// Construct new path from base path
			strcpy(path, basePath);
			strcat(path, backspace);
			strcat(path, dp->d_name);
			listExampleDir(path, exampleName);
		}
	}
	closedir(dir);
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

void renameFile(char* filename, char* filepath, int type) {
	char dest_path[MAX_PATH_LENGTH] = "";       // Replace with the desired destination path

	if (type == 1) {				// Backup Dmodel
		char filename_modified[MAX_PATH_LENGTH] = "";

		// original model filename
		strcat(path_model, backspace);
		strcat(path_model, filename);

		// Construct the modified model filename
		strcat(filename_modified, "Dbackup_");
		strcat(filename_modified, dspFileProp(path_model));
		strcat(filename_modified, "_");
		strcat(filename_modified, filename);

		extractRootDirectory(path_model, dir_model);
		char source_path[MAX_PATH_LENGTH] = "";
		strcat(source_path, path_model);
		strcat(source_path, backspace);
		strcat(source_path, filename);

		char destination_path[MAX_PATH_LENGTH] = "";
		strcat(destination_path, path_model);
		strcat(destination_path, backspace);
		strcat(destination_path, filename_modified);

		// copying file from source path -> dest path
		copyFile(source_path, destination_path);
		if (PRINT_DEBUG) printf("[%s][%d][INFO] Dmodel Backup done.\n", __func__, __LINE__);
	}
	else {							// Backup Cmodel
		char filename_modified[MAX_PATH_LENGTH] = "";

		// Construct the modified filename
		strcat(filename_modified, "Cbackup_");
		strcat(filename_modified, dspFileProp(path_model));
		strcat(filename_modified, "_");
		strcat(filename_modified, filename);

		char source_path[MAX_PATH_LENGTH] = "";
		strcat(source_path, filepath);
		strcat(source_path, backspace);
		strcat(source_path, filename);

		char destination_path[MAX_PATH_LENGTH] = "";
		strcat(destination_path, path_model);
		strcat(destination_path, backspace);
		strcat(destination_path, filename_modified);
		copyFile(source_path, destination_path);
		if (PRINT_DEBUG) printf("[%s][%d][INFO] Cmodel Backup done.\n", __func__, __LINE__);

		char destination_path2[MAX_PATH_LENGTH] = "";
		strcat(destination_path2, path_model);
		strcat(destination_path2, backspace);
		strcat(destination_path2, filename);
		copyFile(source_path, destination_path2);
		if (PRINT_DEBUG) printf("[%s][%d][INFO] Cmodel Copy done.\n", __func__, __LINE__);
	}
}

char* dspFileProp(const char* filename) {
	struct stat file_model_stats;

	if (stat(filename, &file_model_stats) == -1) {
		fprintf(stderr, "[Error][%d] Default model %s does not exist. Please check %s again.\n", __LINE__, filename, filename);
		exit(1);
	}

	time_t fileCreationTime = file_model_stats.st_mtime;	// Get the file creation time
	char fileCreationDate[11];								// Format the file creation time
	strftime(fileCreationDate, sizeof(fileCreationDate), "%Y-%m-%d", localtime(&fileCreationTime));
	if (PRINT_DEBUG) printf("[%s][%d][INFO] File creation date: %s\n", __func__, __LINE__, fileCreationDate);


//#ifndef _WIN32
//	return fileCreationDate;
//#else
	char* fileCreationDate_addr = fileCreationDate;

	return fileCreationDate_addr;
//#endif
}


int endsWith(const char* str, const char* suffix) {
	size_t str_len = strlen(str);
	size_t suffix_len = strlen(suffix);
	if (suffix_len > str_len) {
		return 0;
	}
	return (strncmp(str + str_len - suffix_len, suffix, suffix_len) == 0);
}

const char* pathTidy(const char* input) {
	size_t input_length = strlen(input);
	size_t output_length = 0;
	for (size_t i = 0; i < input_length; i++) {
		if (input[i] == '\\') {
			output_length += 2;
		}
		output_length++; // for the character itself
	}

	char* output = (char*)malloc(output_length + 1); // +1 for null-terminator
	if (!output) {
		perror("Memory allocation failed");
		exit(EXIT_FAILURE);
	}

	size_t j = 0;
	for (size_t i = 0; i < input_length; i++) {
		if (input[i] == '\\') {
			output[j++] = '\\';
			output[j++] = '\\';
		}
		else {
			output[j++] = input[i];
		}
	}
	output[j] = '\0'; // Null-terminator

	return output;
}

void removeChar(char* str, char c) {
	int i, j;
	size_t len = strlen(str);
	for (i = j = 0; i < len; i++) {
		if (str[i] != c) {
			str[j++] = str[i];
		}
	}
	str[j] = '\0';
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

const char* input2model(const char* input) {
	const char* model_mapping[][2] = {
		{"CUSTOMIZED_YOLOV3TINY",    "yolov3_tiny"},
		{"CUSTOMIZED_YOLOV4TINY",    "yolov4_tiny"},
		{"CUSTOMIZED_YOLOV7TINY",    "yolov7_tiny"},
		{"CUSTOMIZED_MOBILEFACENET", "mobilefacenet_i16"},
		{"CUSTOMIZED_SCRFD",         "scrfd640"},
		{"CUSTOMIZED_YAMNET",        "yamnet_fp16"},
		{"DEFAULT_YOLOV3TINY",       "yolov3_tiny"},
		{"DEFAULT_YOLOV4TINY",       "yolov4_tiny"},
		{"DEFAULT_YOLOV7TINY",       "yolov7_tiny"},
		{"DEFAULT_MOBILEFACENET",    "mobilefacenet_i8"},
		{"DEFAULT_SCRFD",            "scrfd320p"},
		{"DEFAULT_YAMNET",			 "yamnet_fp16"},
	};

	int mapping_size = sizeof(model_mapping) / sizeof(model_mapping[0]);

	for (int i = 0; i < mapping_size; i++) {
		if (strcmp(input, model_mapping[i][0]) == 0) {
			return model_mapping[i][1];
		}
	}

	return "NA";
}

const char* input2filename(const char* directory_path, const char* key) {
	const char* value = NULL;
	if (PRINT_DEBUG) printf("[%s] open the file %s \n", __func__, directory_path);
	FILE* file = fopen(directory_path, "rb");
	if (file == NULL) {
		printf("[%s][Error] Failed to open the file.\n", __func__);
		perror("Error opening file");
		printf("Error code: %d\n", errno);
		return value;
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
		return value;
	}

	// Read the JSON data from the file
	size_t read_size = fread(json_data, 1, file_size, file);
	if (PRINT_DEBUG) printf("[%s][Info] read_size %zu\n", __func__, read_size);
	if (PRINT_DEBUG) printf("[%s][Info] file_size %zu\n", __func__, file_size);

	if (read_size != file_size) {
		printf("[%s][Error] Failed to read the file.\n", __func__);
		fclose(file);
		free(json_data);
		return value;
	}
	json_data[file_size] = '\0';  // Null-terminate the string

	// Close the file
	fclose(file);

	// Parse the JSON data
	cJSON* data = cJSON_Parse(json_data);
	if (data == NULL) {
		printf("[%s][Error] Failed to parse JSON data.\n", __func__);
		return value;
	}
	// Print JSON data 
	if (PRINT_DEBUG) printf("[%s] json_data %s.\n", __func__, json_data);

	//const char* key = "yolov4_tiny";
	cJSON* yolov4_tiny_obj = cJSON_GetObjectItemCaseSensitive(data, key);
	if (yolov4_tiny_obj == NULL) {
		printf("Key '%s' not found.\n", key);
		cJSON_Delete(data);
		return value;
	}

	cJSON* file_obj = cJSON_GetObjectItemCaseSensitive(yolov4_tiny_obj, "file");
	if (file_obj == NULL) {
		printf("Attribute \"file\" not found!\n");
		cJSON_Delete(data);
		return value;
	}
	value = file_obj->valuestring;
	if (PRINT_DEBUG) printf("[%s][Info] Output: %s\n", __func__, value);

	// Clean up cJSON object and allocated memory
	cJSON_Delete(data);
	free(json_data);

	return value;
}


void backupModel(char* input, char* sktech_path) {
	DIR* dir;
	struct dirent* entry;
	bool flag_Dbackup = 0;

	// check default model back up status
	if ((dir = opendir(path_model)) == NULL) {
		perror("opendir() error");
		if (PRINT_DEBUG) printf("[%s][%d][Error] Failed to open dir at: %s\n", __func__, __LINE__, path_model);
		exit(1);
	}
	else {
		while ((entry = readdir(dir)) != NULL) {
			if (strstr(entry->d_name, "Dbackup") != NULL) {     // customized model has been used
				if (PRINT_DEBUG) printf("[%s][%d][INFO] Backup-ed %s found !!!\n", __func__, __LINE__, input);
				flag_Dbackup = 1;
				break;
			}
		}
		closedir(dir);
	}
	if (PRINT_DEBUG) printf("[%s][%d][INFO] flag_Dbackup %d \n", __func__, __LINE__, flag_Dbackup);

	// check customized model back up status
	if (flag_Dbackup) {
		renameFile(input, sktech_path, 0);       // back up Cmodel
	}
	else {
		renameFile(input, sktech_path, 1);       // back up Dmodel
		renameFile(input, sktech_path, 0);       // back up Cmodel
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
	if (PRINT_DEBUG) printf("[%s][INFO] Dmodel Revert done.\n", __func__);
}


void error_handler(const char* message) {
	fprintf(stderr, "[Error] %s\n", message);
	exit(1);
}

const char* validateINO(const char* directory_path) {
	// Open the JSON file and retrive the data
	cJSON* data = loadJSONFile(path_build_options_json);
	cJSON* path_example = cJSON_GetObjectItem(data, "sketchLocation");
	if (PRINT_DEBUG) printf("[%s][INFO] Current example path2: %s \n", __func__, pathTidy(path_example->valuestring));

	return pathTidy(path_example->valuestring);
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
			char filepath[MAX_PATH_LENGTH];
			
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
	if (PRINT_DEBUG) printf("[%s][%d][INFO] resetJSON done\n", __func__, __LINE__);
}

void updateJSON(const char* input, const char* destPath) {
	DIR* dir;
	struct dirent* ent;
	// Open the destination directory
	dir = opendir(destPath);
	if (dir == NULL) {
		printf("Failed to open the destination directory: %s\n", destPath);
		return;
	}

	while ((ent = readdir(dir)) != NULL) {
		const char* destFile = ent->d_name;

		// Check if the destination file is a JSON file
		if (strstr(destFile, ".json") != NULL) {
#if PRINT_DEBUG
			printf("Processing JSON file: %s\n", destFile);
#endif
			// Open the JSON file
			char filePath[MAX_PATH_LENGTH];
			
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

const char* pathTempJSON(const char* directory_path, const char* ext, const char* key) {
	DIR* dir;
	struct dirent* entry;

	if ((dir = opendir(directory_path)) == NULL) {
		perror("opendir() error");
		if (PRINT_DEBUG) printf("[%s][%d][Error] Failed to open dir at: %s\n", __func__, __LINE__, directory_path);
		exit(1);
	}
	else {
		while ((entry = readdir(dir)) != NULL) {
			if (entry->d_type == DT_REG && strstr(entry->d_name, ext_json) != NULL && strstr(entry->d_name, key_json) != NULL) {
				if (PRINT_DEBUG) printf("[%s][%d][INFO] File: %s\n", __func__, __LINE__, entry->d_name);
//#ifndef _WIN32
//				strcat(directory_path, backspace);
//				strcat(directory_path, entry->d_name);
//#else
				strcat((char*)directory_path, backspace);
				strcat((char*)directory_path, entry->d_name);
//#endif
				break;
			}
		}
		closedir(dir);
	}

	return directory_path;
}

cJSON* loadJSONFile(const char* directory_path) {
	cJSON* data = NULL;
	FILE* file = fopen(directory_path, "rb");
	if (file == NULL) {
		printf("[%s][Error] Failed to open the file.\n", __func__);
		perror("Error opening file");
		printf("Error code: %d\n", errno);
		return data;
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
		return data;
	}

	// Read the JSON data from the file
	size_t read_size = fread(json_data, 1, file_size, file);
	if (PRINT_DEBUG) printf("[%s][Info] read_size %zu\n", __func__, read_size);
	if (PRINT_DEBUG) printf("[%s][Info] file_size %zu\n", __func__, file_size);

	if (read_size != file_size) {
		printf("[%s][Error] Failed to read the file.\n", __func__);
		fclose(file);
		free(json_data);
		return data;
	}
	json_data[file_size] = '\0';  // Null-terminate the string

	// Close the file
	fclose(file);

	// Parse the JSON data
	data = cJSON_Parse(json_data);
	if (data == NULL) {
		printf("[%s][Error] Failed to parse JSON data.\n", __func__);
		return NULL;
	}
	// print JSON data 
	if (PRINT_DEBUG) printf("[%s] json_data %s.\n", __func__, json_data);

	// Clean up cJSON object and allocated memory
	free(json_data);

	return data;
}

int writeJSON(const char* f_path) {
	const char buf[MAX_PATH_LENGTH] = "";
	char line[MAX_PATH_LENGTH] = { 0 };
	char voe_status[MAX_PATH_LENGTH] = "NA";
	char model_type[MAX_PATH_LENGTH] = "";
	char model_name_od[MAX_PATH_LENGTH] = "";
	char model_name_fd[MAX_PATH_LENGTH] = "";
	char model_name_fr[MAX_PATH_LENGTH] = "";
	char model_name_ac[MAX_PATH_LENGTH] = "";
	char header_od[MAX_PATH_LENGTH] = "NA";
	char header_fd[MAX_PATH_LENGTH] = "NA";
	char header_fr[MAX_PATH_LENGTH] = "NA";
	char header_ac[MAX_PATH_LENGTH] = "NA";
	char header_all[MAX_PATH_LENGTH] = "";
	char fname_od[MAX_PATH_LENGTH] = "NA";
	char fname_fd[MAX_PATH_LENGTH] = "NA";
	char fname_fr[MAX_PATH_LENGTH] = "NA";
	char fname_ac[MAX_PATH_LENGTH] = "NA";
	char line_strip_header[MAX_PATH_LENGTH] = "NA";
	char line_strip_headerNN[MAX_PATH_LENGTH] = "NA";
	char dir_example[MAX_PATH_LENGTH] = "NA";

	char* file_path = NULL;
	const char* ino_extension = ".ino";

	if (PRINT_DEBUG) printf("[%s][%d][INFO] Load example: \"%s\"\n", __func__, __LINE__, f_path);

	// check IDE Version
	if (strstr(f_path, ".ino") == NULL) {
		// IDE2 creates temp dir
		if (PRINT_DEBUG) printf("[%d] IDE2\n", __LINE__);

		DIR* dir;
		struct dirent* ent;
		dir = opendir(f_path);

		if (dir == NULL) {
			printf("Unable to open directory: %s\n", f_path);
			return 0;
		}

		// find .ino file in IDE2 TEMP folder
		while ((ent = readdir(dir)) != NULL) {
			if (ent->d_type == DT_REG) {
				if (strstr(ent->d_name, ".ino") != NULL) {
					size_t path_len = strlen(f_path);
					size_t file_name_len = strlen(ent->d_name);

					file_path = malloc(path_len + file_name_len + 2);
					if (file_path == NULL) {
						printf("Memory allocation error.\n");
					} else{
#ifndef _WIN32
						sprintf(file_path, "%s//%s", f_path, ent->d_name);
#else
						sprintf(file_path, "%s\\%s", f_path, ent->d_name);
#endif	
					}
					if (PRINT_DEBUG) printf("[%d] file_path: %s\n", __LINE__, file_path);
					//free(file_path);
					break;
				}
			}
		}
		closedir(dir);
	}
	else {
		// IDE1 creates temp file
		if (PRINT_DEBUG) printf("[%d] IDE1\n", __LINE__);
		// unmodified example
		size_t path_len = strlen(f_path);
		file_path = malloc(path_len + 2);
		file_path = (char*)f_path;
		if (PRINT_DEBUG) printf("[%d] file_path %s\n", __LINE__, file_path);

		if (file_path == NULL) {
			printf("Memory allocation error.\n");
		}

		// modified example
		if (strstr(path_example, "modified") != NULL) {
			char* example_name = strrchr(path_example, '\\');   // find the last "\"
			removeChar(example_name, '\\');
			listExampleDir(path_library, example_name);
			strcpy(file_path, folder_example);                // update example directory name
		}
	}
	f_path = (const char*)file_path;
	if (PRINT_DEBUG) printf("[%d]------------qqz file_path %s\r\n", __LINE__, f_path);

	FILE* f_model = fopen(f_path, "r");
	char param[100];

	if (f_model) {
		char line[MAX_PATH_LENGTH];
		char* token = "";

		while (fgets(line, sizeof(line), f_model)) {
			// check whether keywordNN in f_model content 
			if (strstr(line, key_amb_NN) != NULL && strstr(line, "//") == NULL && strstr(line, key_amb_bypassNN1) == NULL && strstr(line, key_amb_bypassNN2) == NULL) {
				extractParam(line, param);
				if (PRINT_DEBUG) printf("[%d] Extracted parameter: %s\n", __LINE__, param);
				token = strtok(param, ", ");
				if (token != NULL) {
					strcpy(model_type, token);
					if (PRINT_DEBUG) printf("[%d] Model Type: %s\n", __LINE__, model_type);

				}

				/* ------------------ object detection ------------------*/
				token = strtok(NULL, ", ");
				if (PRINT_DEBUG) printf("[%d] Param 1: %s\n", __LINE__, token);
				if (token != NULL) {
					// OBJECT_DETECTION example: check model combination rules
					if (strcmp(model_type, "OBJECT_DETECTION") == 0) {
						if (strcmp(token, "NA_MODEL") == 0 || strstr(token, "YOLO") == NULL) {
							goto error_combination;
						}
					}

					// check customized OD model
					if (strstr(token, key_amb_customized) != NULL) {
						if (PRINT_DEBUG) printf("[%d] od key_amb_customized\n", __LINE__);
						if (PRINT_DEBUG) printf("[%d] customized od: %s\n", __LINE__, input2model(token));
						if (PRINT_DEBUG) printf("[%d] path example %s\r\n", __LINE__, path_example);

						// goto path_model and open the file ends with .json
						if (dirExists(path_model)) {
							DIR* dir = opendir(path_model);
							struct dirent* ent;

							while ((ent = readdir(dir)) != NULL) {
								if (endsWith(ent->d_name, ".json")) {
									char fpath_nn_json[BUFFER_SIZE];
									char dir_nn_json[MAX_PATH_LENGTH] = "";
									
#ifndef _WIN32
									sprintf(fpath_nn_json, "%s//%s", path_model, ent->d_name);
									cJSON* fname_model = (cJSON*)input2filename(fpath_nn_json, input2model(token));
#else
									sprintf(fpath_nn_json, "%s\\%s", path_model, ent->d_name);
									char* fname_model = (char*)(input2filename(fpath_nn_json, input2model(token)));
#endif
									strcpy(fname_od, (char*)fname_model);
								}
							}
							closedir(dir);
						}

						if (strcmp(path_example, "Temp") == 0) {	// IDE1
							printf("[%d] ------------qqz IDE1\r\n", __LINE__);
//#ifndef _WIN32
//							extractRootDirectory(path_example, dir_example);
//#else
							extractRootDirectory((char*)path_example, dir_example);
//#endif
						}
						else {										// IDE2
							printf("[%d] ------------qqz IDE2\r\n", __LINE__);

							char* example_name = strrchr(path_example, '\\');   // find the last "\"
							removeChar(example_name, '\\');
							printf("[%d] ------------qqz example_name %s\r\n", __LINE__, example_name);
							listExampleDir(path_library, example_name);
							strcpy(dir_example, folder_example);                // update example directory name
						}
						if (PRINT_DEBUG) printf("[%d] ------------qqz dir example %s\r\n", __LINE__, dir_example);

						DIR* dir;
						struct dirent* entry;
						int count = 0;
						int count_match = 0;

						// check weather dir is valid
						if ((dir = opendir(dir_example)) != NULL) {
							// print all the files and directories within directory 
							while ((entry = readdir(dir)) != NULL) {
								if (entry->d_type == DT_REG) {
									count++;
								}
								if (strstr(entry->d_name, ".nb") != NULL) {
									if (strstr(entry->d_name, input2model(token))) {		// 1. check model file (.nb) within example directory 
										if (strcmp(entry->d_name, fname_od) != 0) {       // 2. check model file (.nb) name matches in json
											goto error_customized_mismatch;
										}
										else {
#if PRINT_DEBUG
											printf("[%s][%d][Info] Found customized model %s in %s\n", __func__, __LINE__, entry->d_name, dir_example);
#endif
#ifndef _WIN32
											backupModel(entry->d_name, dir_example);
#else
											backupModel(entry->d_name, (char*)dir_example);
#endif
										}
										count_match++;
									}
								}
							}
							if (count <= 1) {
								goto error_customized_missing;
							}
							if (count_match == 0) {
								goto error_customized_mismatch;
							}
						}
						printf("[%d] ------------qqz dir example %s\r\n", __LINE__, dir_example);
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
							struct dirent* ent;
							while ((ent = readdir(dir)) != NULL) {
								if (strstr(ent->d_name, "Dbackup") != NULL) {     // customized model has been used
									flag_Dbackup = 1;
									strcpy(fname_dmodel_backup, ent->d_name);
									strcpy(model_name_od, token);
									char* input = "";
//#ifndef _WIN32
//									input = input2model(model_name_od);
//#else
									input = (char*)(input2model(model_name_od));
//#endif
									char output[100];
									char* underscore = strchr(input, '_');      // Find the first occurrence of "_"
									if (underscore != NULL) {
										size_t length = underscore - input;     // Calculate the length of the substring before "_"
										strncpy(output, input, length);     // Copy the substring before "_" to the output variable
										output[length] = '\0';      // Add the null terminator at the end of the substring
									}
									char key[100] = "_";
									strcat(key, output);
									char* start = strstr(fname_dmodel_backup, key);     // Find the starting position of the substring
									if (start != NULL) {
										strcat(key, "_");
										start += strlen(key);       // Move the pointer past the substring
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

					strcpy(model_name_od, token);

					/* ----------------- face detection -----------------*/
					token = strtok(NULL, ", ");
					if (PRINT_DEBUG) printf("[%d] Param 2: %s\n", __LINE__, token);

					if (token != NULL) {
						// check model combination rules
						if (strcmp(model_type, "FACE_DETECTION") == 0) {
							if (strcmp(token, "NA_MODEL") == 0 || strstr(token, "SCRFD") == NULL) {
								goto error_combination;
							}
						}
						// check customized FD model
						if (strstr(token, key_amb_customized) != NULL) {
#if PRINT_DEBUG
							printf("[%d] fd key_amb_customized\n", __LINE__);
							printf("[%d] customized fd: %s\n", __LINE__, input2model(token));
							printf("[%d] path example %s\r\n", __LINE__, path_example);
#endif
							// goto path_model and open the file ends with .json
							if (dirExists(path_model)) {
								DIR* dir = opendir(path_model);
								struct dirent* ent;

								while ((ent = readdir(dir)) != NULL) {
									if (endsWith(ent->d_name, ".json")) {
										char fpath_nn_json[BUFFER_SIZE];
										char dir_nn_json[MAX_PATH_LENGTH] = "";

										
#ifndef _WIN32
										sprintf(fpath_nn_json, "%s//%s", path_model, ent->d_name);
										cJSON* fname_model = (cJSON*)input2filename(fpath_nn_json, input2model(token));
#else
										sprintf(fpath_nn_json, "%s\\%s", path_model, ent->d_name);
										char* fname_model = (char*)(input2filename(fpath_nn_json, input2model(token)));
#endif
										strcpy(fname_fd, (char*)fname_model);
									}
								}
								closedir(dir);
							}
							if (strcmp(path_example, "Temp") == 0) {
								// IDE1
								printf("[%d] ------------qqz IDE1\r\n", __LINE__);
//#ifndef _WIN32
//								extractRootDirectory(path_example, dir_example);
//#else
								extractRootDirectory((char*)path_example, dir_example);
//#endif
							}
							else {
								// IDE2
								printf("[%d] ------------qqz IDE2\r\n", __LINE__);

								char* example_name = strrchr(path_example, '\\');   // find the last "\"
								removeChar(example_name, '\\');
								printf("[%d] ------------qqz example_name %s\r\n", __LINE__, example_name);
								listExampleDir(path_library, example_name);
								strcpy(dir_example, folder_example);                // update example directory name
							}
							if (PRINT_DEBUG) printf("[%d] ------------qqz dir example %s\r\n", __LINE__, dir_example);

							DIR* dir;
							struct dirent* ent;
							int count = 0;
							int count_match = 0;

							// check weather dir is valid
							if ((dir = opendir(dir_example)) != NULL) {
								// print all the files and directories within directory 
								while ((ent = readdir(dir)) != NULL) {
									if (ent->d_type == DT_REG) {
										count++;
									}
									if (strstr(ent->d_name, ".nb") != NULL) {
										//count_nb++;
										if (strstr(ent->d_name, "scrfd")) {				// 1. check model file (.nb) within example directory 
											if (strcmp(ent->d_name, fname_fd) != 0) {	// 2. check model file (.nb) name matches in json
												goto error_customized_mismatch;
											}
											else {
#if PRINT_DEBUG
												printf("[%s][%d][Info] Found customized model %s in %s\n", __func__, __LINE__, ent->d_name, dir_example);
#endif
#ifndef _WIN32
												backupModel(ent->d_name, dir_example);
#else
												backupModel(ent->d_name, (char*)dir_example);
#endif
											}
											count_match++;
										}
									}
								}
								if (count <= 1) {
									goto error_customized_missing;
								}
								if (count_match == 0) {
									goto error_customized_mismatch;
								}
							}
							printf("[%d] ------------qqz dir example %s\r\n", __LINE__, dir_example);
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
								struct dirent* ent;
								while ((ent = readdir(dir)) != NULL) {
									if (strstr(ent->d_name, "Dbackup") != NULL) {     // customized model has been used
										flag_Dbackup = 1;
										strcpy(fname_dmodel_backup, ent->d_name);
										char* start = strstr(fname_dmodel_backup, "_scrfd");        // Find the starting position of the substring
										if (start != NULL) {
											start += strlen("_scrfd_");     // Move the pointer past the substring
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

						strcpy(model_name_fd, token);

						/*-------------- face recognition --------------*/
						token = strtok(NULL, ", ");
						if (PRINT_DEBUG) printf("[%d] Param 3: %s\n", __LINE__, token);

						if (token != NULL) {
							// FACE_RECOGNITION example: check model combination rules
							if (strcmp(model_type, "FACE_RECOGNITION") == 0) {
								if (strcmp(model_name_fd, "NA_MODEL") == 0 || strstr(model_name_fd, "SCRFD") == NULL || strcmp(token, "NA_MODEL") == 0 || strstr(token, "MOBILEFACENET") == NULL) {
									goto error_combination;
								}
							}

							// check customized FR model
							if (strstr(token, key_amb_customized) != NULL) {
								if (PRINT_DEBUG) printf("[%d]fr key_amb_customized\n", __LINE__);
								if (PRINT_DEBUG) printf("[%d]customized fr: %s\n", __LINE__, input2model(token));
								if (PRINT_DEBUG) printf("[%d]path_example: %s\n", __LINE__, path_example);

								// goto path_model and open the file ends with .json
								if (dirExists(path_model)) {
									DIR* dir = opendir(path_model);
									struct dirent* ent;

									while ((ent = readdir(dir)) != NULL) {
										if (endsWith(ent->d_name, ".json")) {
											char fpath_nn_json[BUFFER_SIZE];
											char dir_nn_json[MAX_PATH_LENGTH] = "";
								
#ifndef _WIN32						
											sprintf(fpath_nn_json, "%s//%s", path_model, ent->d_name);
											cJSON* fname_model = (cJSON*)input2filename(fpath_nn_json, input2model(token));
#else
											sprintf(fpath_nn_json, "%s\\%s", path_model, ent->d_name);
											char* fname_model = (char*)(input2filename(fpath_nn_json, input2model(token)));
#endif
											strcpy(fname_fr, (char*)fname_model);
										}
									}
									closedir(dir);
								}
								if (strcmp(path_example, "Temp") == 0) {
#if PRINT_DEBUG
									// IDE1
									printf("[%d] ------------qqz IDE1\r\n", __LINE__);
#endif
//#ifndef _WIN32
//									extractRootDirectory(path_example, dir_example);
//#else
									extractRootDirectory((char*)path_example, dir_example);
//#endif
								}
								else {
#if PRINT_DEBUG
									// IDE2
									printf("[%d] ------------qqz IDE2\r\n", __LINE__);
#endif
									char* example_name = strrchr(path_example, '\\');   // find the last "\"
									removeChar(example_name, '\\');
									listExampleDir(path_library, example_name);
									strcpy(dir_example, folder_example);                // update example directory name
								}
#if PRINT_DEBUG
								printf("[%d] ------------qqz dir example %s\r\n", __LINE__, dir_example);
#endif

								DIR* dir;
								struct dirent* ent;
								int count = 0;
								int count_match = 0;

								// check weather dir is valid
								if ((dir = opendir(dir_example)) != NULL) {
									// print all the files and directories within directory 
									while ((ent = readdir(dir)) != NULL) {
										if (ent->d_type == DT_REG) {
											count++;
										}
										if (strstr(ent->d_name, ".nb") != NULL) {
											if (strstr(ent->d_name, "mobilefacenet") != NULL) {     // 1. check model file (.nb) within example directory 
												if (strcmp(ent->d_name, fname_fr) != 0) {			// 2. check exampel file name whether matches in json
													goto error_customized_mismatch;
												}
												else {
#if PRINT_DEBUG
													printf("[%s][%d][Info] Found customized model %s in %s\n", __func__, __LINE__, ent->d_name, dir_example);
#endif
#ifndef _WIN32
													backupModel(ent->d_name, dir_example);
#else
													backupModel(ent->d_name, (char*)dir_example);
#endif
													count_match++;
												}
											}
										}
									}
									if (count <= 1) {
										goto error_customized_missing;
									}
									if (count_match == 0) {
										goto error_customized_mismatch;
									}
								}
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
									struct dirent* ent;
									while ((ent = readdir(dir)) != NULL) {
										if (strstr(ent->d_name, "Dbackup") != NULL) {     // customized model has been used
											flag_Dbackup = 1;
											strcpy(fname_dmodel_backup, ent->d_name);
											char* start = strstr(fname_dmodel_backup, "_mobilefacenet");		// Find the starting position of the substring
											if (start != NULL) {
												start += strlen("_mobilefacenet_");     // Move the pointer past the substring
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
							strcpy(model_name_fr, token);

							/*-------------- audio classification --------------*/
							token = strtok(NULL, ", ");
							if (PRINT_DEBUG) printf("[%d] Param 4: %s\n", __LINE__, token);

							if (token != NULL) {
								// AUDIO_CLASSIFICATION example: check model combination rules
								if (strcmp(model_type, "AUDIO_CLASSIFICATION") == 0) {
									if (strcmp(model_name_od, "NA_MODEL") == 0 && strstr(model_name_fd, "NA_MODEL") == NULL && strcmp(model_name_fr, "NA_MODEL") == 0) {
										goto error_exceed;
									}
								}

								// check customized AC model
								if (strstr(token, key_amb_customized) != NULL) {
									if (PRINT_DEBUG) printf("[%d] ac key_amb_customized\n", __LINE__);
									if (PRINT_DEBUG) printf("[%d] customized ac: %s\n", __LINE__, input2model(token));
									if (PRINT_DEBUG) printf("[%d] path_example: %s\n", __LINE__, path_example);

									// goto path_model and open the file ends with .json
									if (dirExists(path_model)) {
										DIR* dir = opendir(path_model);
										struct dirent* ent;

										while ((ent = readdir(dir)) != NULL) {
											if (endsWith(ent->d_name, ".json")) {
												char fpath_nn_json[BUFFER_SIZE];
												char dir_nn_json[MAX_PATH_LENGTH] = "";;

												
#ifndef _WIN32
												sprintf(fpath_nn_json, "%s//%s", path_model, ent->d_name);
												cJSON* fname_model = (cJSON*)input2filename(fpath_nn_json, input2model(token));
#else
												sprintf(fpath_nn_json, "%s\\%s", path_model, ent->d_name);
												char* fname_model = (char*)(input2filename(fpath_nn_json, input2model(token)));
#endif
												strcpy(fname_ac, (char*)fname_model);
											}
										}
										closedir(dir);
									}
									if (strcmp(path_example, "Temp") == 0) {	// IDE1
										printf("[%d] ------------qqz IDE1\r\n", __LINE__);
//#ifndef _WIN32
//										extractRootDirectory(path_example, dir_example);
//#else
										extractRootDirectory((char*)path_example, dir_example);
//#endif
									}
									else {										// IDE2
										printf("[%d] ------------qqz IDE2\r\n", __LINE__);
										char* example_name = strrchr(path_example, '\\');   // find the last "\"
										removeChar(example_name, '\\');
										printf("[%d] ------------qqz example_name %s\r\n", __LINE__, example_name);
										listExampleDir(path_library, example_name);
										strcpy(dir_example, folder_example);                // update example directory name
									}
									if (PRINT_DEBUG) printf("[%d] ------------qqz dir example %s\r\n", __LINE__, dir_example);

									DIR* dir;
									struct dirent* entry;
									int count = 0;
									int count_match = 0;

									// check weather dir is valid
									if ((dir = opendir(dir_example)) != NULL) {
										// print all the files and directories within directory 
										while ((entry = readdir(dir)) != NULL) {
											if (entry->d_type == DT_REG) {
												count++;
											}
											printf("[%d][%s] %s\n", __LINE__, __func__, entry->d_name);
											if (strstr(entry->d_name, ".nb") != NULL) {
												if (strstr(entry->d_name, input2model(token))) {		// 1. check model file (.nb) within example directory 

													printf("[%d][%s] %s\n", __LINE__, __func__, fname_ac);
													if (strcmp(entry->d_name, fname_ac) != 0) {			// 2. check model file (.nb) name matches in json
														goto error_customized_mismatch;
													}
													else {
														if (PRINT_DEBUG) printf("[%s][%d][Info] Found customized model %s in %s\n", __func__, __LINE__, entry->d_name, dir_example);
#ifndef _WIN32
														backupModel(entry->d_name, dir_example);
#else
														backupModel(entry->d_name, (char*)dir_example);
#endif
													}
													count_match++;
												}
											}
										}
										if (count <= 1) {
											goto error_customized_missing;
										}

										if (count_match == 0) {
											goto error_customized_mismatch;
										}
									}
									printf("[%d] ------------qqz dir example %s\r\n", __LINE__, dir_example);
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
										struct dirent* ent;
										while ((ent = readdir(dir)) != NULL) {
											if (strstr(ent->d_name, "Dbackup") != NULL) {     // customized model has been used
												flag_Dbackup = 1;
												strcpy(fname_dmodel_backup, ent->d_name);
												char* start = strstr(fname_dmodel_backup, "_scrfd");        // Find the starting position of the substring
												if (start != NULL) {
													start += strlen("_scrfd_");     // Move the pointer past the substring
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
								strcpy(model_name_ac, token);
								}



							}
						}
					}
				else {
					// provide default settings for all models if user never provide any selections
					if (strcmp(model_type, "OBJECT_DETECTION") == 0) {
						//if (strcmp(model_type, "OBJECT_DETECTION") == 0 && strcmp(input2model(model_name_od), "NA") == 0) {
						strcpy(model_name_od, "DEFAULT_YOLOV4TINY");
						strcpy(model_name_fd, "NA_MODEL");
						strcpy(model_name_fr, "NA_MODEL");
						strcpy(model_name_ac, "NA_MODEL");
					}
					if (strcmp(model_type, "FACE_DETECTION") == 0) {
						//if (strcmp(model_type, "FACE_DETECTION") == 0 && strcmp(input2model(model_name_fd), "NA") == 0) {
						strcpy(model_name_od, "NA_MODEL");
						strcpy(model_name_fd, "DEFAULT_SCRFD");
						strcpy(model_name_fr, "NA_MODEL");
						strcpy(model_name_ac, "NA_MODEL");
					}
					if (strcmp(model_type, "FACE_RECOGNITION") == 0) {
						//if (strcmp(model_type, "FACE_RECOGNITION") == 0 && strcmp(input2model(model_name_fr), "NA") == 0) {
						strcpy(model_name_od, "NA_MODEL");
						strcpy(model_name_fd, "DEFAULT_SCRFD");
						strcpy(model_name_fr, "DEFAULT_MOBILEFACENET");
						strcpy(model_name_ac, "NA_MODEL");
					}
					// TODO: add AUDIO_CLASSIFICATION
					if (strcmp(model_type, "AUDIO_CLASSIFICATION") == 0) {
						strcpy(model_name_od, "NA_MODEL");
						strcpy(model_name_fd, "NA_MODEL");
						strcpy(model_name_fr, "NA_MODEL");
						strcpy(model_name_ac, "DEFAULT_YAMNET");
					}
				}
				}
			}
		fclose(f_model);
		}
	else {
		printf("[%s][%d][Error] Failed to open the file.\n", __func__, __LINE__);
		perror(file_path);
		fprintf(stderr, "Failed to open the file.\n");
		exit(1);
	}

	if (PRINT_DEBUG) printf("-------------------------------------\n");
	if (PRINT_DEBUG) printf("[%d] Model Name OD: %s\n", __LINE__, input2model(model_name_od));
	if (PRINT_DEBUG) printf("[%d] Model Name FD: %s\n", __LINE__, input2model(model_name_fd));
	if (PRINT_DEBUG) printf("[%d] Model Name FR: %s\n", __LINE__, input2model(model_name_fr));
	if (PRINT_DEBUG) printf("[%d] Model Name AC: %s\n", __LINE__, input2model(model_name_ac));
	if (PRINT_DEBUG) printf("-------------------------------------\n");

	if (strstr(input2model(model_name_od), "NA") == NULL) {
		updateJSON(input2model(model_name_od), path_model);
	}
	if (strstr(input2model(model_name_fd), "NA") == NULL) {
		updateJSON(input2model(model_name_fd), path_model);
	}
	if (strstr(input2model(model_name_fr), "NA") == NULL) {
		updateJSON(input2model(model_name_fr), path_model);
	}
	if (strstr(input2model(model_name_ac), "NA") == NULL) {
		updateJSON(input2model(model_name_ac), path_model);
	}

	return 0;

error_combination:
	error_handler("Model combination mismatch. Please check modelSelect() again.");

error_customized_missing:
	error_handler("Model missing. Please check your sketch folder again.");

error_customized_mismatch:
	error_handler("Customized model mismatch. Please rename your model.");

error_exceed:
	error_handler("Exceeds model size limitation. Please remove unwanted model(s).");
	}
