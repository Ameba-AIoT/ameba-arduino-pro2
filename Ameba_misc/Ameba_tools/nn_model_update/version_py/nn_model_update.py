# ------------------------------------------------------
# README
# This tool is to check whether correct model has being selected in Arduino IDE Tools menu while running dedicated NN example
# For Example: whether scrfd and mobilefacenet models have been selected while running NNFaceRecognition Example
# ------------------------------------------------------
# To generate executable
# run.bat
# python -m PyInstaller  --onefile --name nn_model_update_windows.exe .\nn_model_update.py
# python3 -m PyInstaller --onefile --name nn_model_update_linux ./nn_model_update.py
# python3 -m PyInstaller --onefile --name nn_model_update_macos ./nn_model_update.py
#                        -w: no terminal required 
# ------------------------------------------------------
# Linux Permission Denied: chmod +x myapp ls -l myapp

import os
import re
import sys
import shutil
import json
from datetime import datetime, timezone
from sys import platform

DEBUG = 0
def debug_print(message):
    if DEBUG:
        print(message)

keyword = "modelSelect"
keyword_header = "#include"
keyword_customized = "CUSTOMIZED"
keyword_default = "DEFAULT"
keyword_default_backup = "Dbackup"
keyword_customized_backup = "Cbackup"
keyword_bypass1 = " .modelSelect"
keyword_bypass2 = " modelSelect"

filename_txt = "ino_validation.txt"

# declear common file paths
usrmodel_path = os.path.abspath(os.path.dirname(sys.argv[0]))
for file_user_model in os.listdir(usrmodel_path):
    if file_user_model.endswith(".nb"):
        # debug_print(os.path.join(usrmodel_path, file_user_model))
        file_user_model_no_ext = os.path.splitext(os.path.basename(file_user_model))[0]
        # debug_print(file_user_model_no_ext)

if platform == "win32":
    # Windows...
    arduino15_path = os.path.expanduser("~\AppData\Local\Arduino15")
    ambpro2_path = arduino15_path + "\packages\\realtek\hardware\AmebaPro2"
    sdk_version = os.listdir(ambpro2_path)[0]
    dest_path = ambpro2_path + "\\" + sdk_version + "\\variants\common_nn_models\\"
    filepath_txt = sys.argv[2] + '\\misc\\' + filename_txt
elif platform == "linux" or platform == "linux2":
    # linux
    arduino15_path = os.path.expanduser("/home/" + os.getlogin() + "/.arduino15")
    ambpro2_path = arduino15_path + "/packages/realtek/hardware/AmebaPro2/"
    sdk_version = os.listdir(ambpro2_path)[0]
    dest_path = ambpro2_path + "/" + sdk_version + "/variants/common_nn_models/"
    filepath_txt = sys.argv[2] + '/misc/' + filename_txt
elif platform == "darwin":
    # OS X
    arduino15_path = os.path.expanduser(os.path.expanduser('~') + "/Library/Arduino15")
    ambpro2_path = arduino15_path + "/packages/realtek/hardware/AmebaPro2/"
    sdk_version = os.listdir(ambpro2_path)[1]
    dest_path = ambpro2_path + "/" + sdk_version + "/variants/common_nn_models/"
    filepath_txt = sys.argv[2] + '/misc/' + filename_txt


def resetJSON(input):
    for file_json in os.listdir(input):
        if file_json.endswith(".json"):
            with open(os.path.join(input, file_json), "r", encoding='utf-8') as file:
                data = json.load(file)
                data["FWFS"]["files"] = []
            with open(os.path.join(input, file_json), "w", encoding='utf-8') as file:
                json.dump(data, file, indent=4)
            debug_print(f"[INFO] {file_json} has been reset")

def updateJSON(input):
    for file_json in os.listdir(dest_path):
        if file_json.endswith(".json"):
            with open(os.path.join(dest_path, file_json), "r", encoding='utf-8') as file:
                data = json.load(file)
                if input == "null":
                    sys.stderr.write(f"[Error] Model input in json is null. Please check again!\n")
                    sys.exit(1)   
                if input == 'RESET':
                    break
                data["FWFS"]["files"].append(input)
            with open(os.path.join(dest_path, file_json), "w", encoding='utf-8') as file:
                json.dump(data, file, indent=4)
    # validateJSON()

def validateJSON():
    total_size = 0
    limit_size = 0
    counter = 0
    for file_json in os.listdir(dest_path):
        if file_json.endswith(".json"):
            with open(os.path.join(dest_path, file_json), "r", encoding='utf-8') as file:
                data = json.load(file)
                files_dict = data["FWFS"]["files"]
                for value in files_dict:
                    value_file_path = dest_path + data[value]["file"]
                    debug_print(value_file_path)
                    total_size += os.stat(value_file_path).st_size
                    limit_size += 4194304
                    counter += 1
                debug_print("---------")
                debug_print(total_size)
                debug_print(limit_size)
    if total_size > limit_size and counter > 1:
        sys.stderr.write(f"[Error] Model size is too big! Please check your input again.\n")
        sys.exit(1)

def dupCheckJSON(input):
    for file_json in os.listdir(dest_path):
        if file_json.endswith(".json"):
            with open(os.path.join(dest_path, file_json), "r", encoding='utf-8') as file:
                data = json.load(file)
                if input2model(input) not in data["FWFS"]["files"]:
                    return 1
    return 0

def input2model(input):
    model_mapping = {
        "CUSTOMIZED_YOLOV3TINY"     : "yolov3_tiny",
        "CUSTOMIZED_YOLOV4TINY"     : "yolov4_tiny",
        "CUSTOMIZED_YOLOV7TINY"     : "yolov7_tiny",
        "CUSTOMIZED_MOBILEFACENET"  : "mobilefacenet_i16",
        "CUSTOMIZED_SCRFD"          : "scrfd640",
        "DEFAULT_YOLOV3TINY"        : "yolov3_tiny",
        "DEFAULT_YOLOV4TINY"        : "yolov4_tiny",
        "DEFAULT_YOLOV7TINY"        : "yolov7_tiny",
        "DEFAULT_MOBILEFACENET"     : "mobilefacenet_i8",
        "DEFAULT_SCRFD"             : "scrfd320p"
    }
    model = model_mapping.get(input)
    return model

def input2filename(input):
    if os.path.isdir(dest_path):
        for file_json in os.listdir(dest_path):
            if file_json.endswith(".json"):
                with open(os.path.join(dest_path, file_json), "r", encoding='utf-8') as file:
                    data = json.load(file)
                    value_file = data[input]["file"]
        return value_file

def dspFileProp(filename):
    if os.path.isfile(dest_path + filename):
        file_model_stats = os.stat(dest_path + filename)
        file_model_datetime = datetime.fromtimestamp(file_model_stats.st_mtime, tz = timezone.utc).strftime('%Y-%m-%d %H:%M:%S')
        file_model_date = datetime.fromtimestamp(file_model_stats.st_mtime, tz = timezone.utc).strftime('%Y-%m-%d')
        file_model_mode = oct(file_model_stats.st_mode)
        # debug_print("              FILE INFO")
        # debug_print("------------------------------------------")
        # debug_print(f"Size:          {file_model_stats.st_size}")
        # debug_print(f"Last modified: {file_model_datetime}")
        # debug_print(f"Mode:          {file_model_mode}")
        # debug_print("------------------------------------------")
        return file_model_date
    else:
        sys.stderr.write(f"[Error] Default model {filename} does not exist. Please check {dest_path} again.\n")
        sys.exit(1)

def renameFile(filename, type):
    if type == 1:
        # Backup Dmodel
        filename_modified = "Dbackup_" + dspFileProp(filename) + "_" + filename
        if os.path.isfile(os.path.join(dest_path, filename_modified)) == False:
            debug_print(os.path.join(dest_path, filename_modified))
            os.rename(os.path.join(dest_path, filename), os.path.join(dest_path, filename_modified))
        debug_print("[INFO] Dmodel Backup done.")
    else:
        # Backup Cmodel
        filename_modified = "Cbackup_" + dspFileProp(filename) + "_" + filename
        if os.path.isfile(os.path.join(dest_path, filename_modified)) == False:
            os.rename(os.path.join(dest_path, filename), os.path.join(dest_path, filename_modified))
        debug_print("[INFO] Cmodel Backup done.")

def backupModel(input, sktech_path):
    for dest_file in os.listdir(dest_path):
        if "Dbackup" in dest_file:
            debug_print(f"[INFO] Backup-ed {input} found !!!")
            break
    renameFile(input, 1)
    # backup Cmodel
    shutil.copy(sktech_path + os.path.sep + input, dest_path)
    renameFile(input, 0)
    # copy Cmodel
    shutil.copy(sktech_path + os.path.sep + input, dest_path)
    debug_print("[INFO] Cmodel copied.")

def revertModel(input):
    for dest_file in os.listdir(dest_path):
        if keyword_default_backup in dest_file and input in dest_file:
            debug_print(f"[INFO] Defaut backup model {dest_file} found")
            file_model_reverted = dest_file.split("_", 2)[2]
            os.remove(dest_path + os.path.sep + file_model_reverted)
            debug_print(f"[INFO] User Model {file_model_reverted} has been removed")
            # revert Dbackup
            os.rename(os.path.join(dest_path, dest_file), os.path.join(dest_path, file_model_reverted))
            debug_print(f"[INFO] Revert {input} done.")

def validationINO():
    for file_json in os.listdir(sys.argv[1]):
        if file_json.endswith(".json") and "build" in file_json:
            with open(os.path.join(sys.argv[1], file_json), "r", encoding='utf-8') as file:
                # get path and file name for further process
                data = json.load(file)
                # Arduino IDE1.0 
                example_path = data["sketchLocation"]
                # Arduino IDE2.0 
                if "Arduino15" not in example_path: 
                    example_name = example_path.split(os.path.sep)[-1]
                    
                    # check whether keyword in file content
                    if ".ino" not in example_path and ".ino" not in example_name:
                        for file in os.listdir(example_path):
                            if ".ino" in file:
                                example_name = example_name + ".ino"
                                example_path = example_path + os.path.sep + example_name
                    
                    for file_cache in os.listdir(sys.argv[1]):
                        if file_cache.endswith(".cache") and "libraries" in file_cache:
                            with open(os.path.join(sys.argv[1], file_cache), "r", encoding='utf-8') as file:
                                for library_path in json.loads(file.read()):
                                    if "libraries" in library_path:
                                        library_path = library_path + os.path.sep + ".." + os.path.sep + "examples" + os.path.sep
                                        debug_print(f"[INFO] Current library_path: {library_path}")
                                        if example_name in os.listdir(library_path):
                                            example_path = library_path + example_name + os.path.sep + example_name + ".ino"
                                            debug_print(f"[INFO] Current example_path: {example_path}")
                    debug_print(f"[INFO] Current example {example_name} running in: {example_path}")
    return example_path

def writeJSON(example_path):
    for file_json in os.listdir(sys.argv[1]):
        if file_json.endswith(".json") and "build" in file_json:
            with open(os.path.join(sys.argv[1], file_json), "r", encoding='utf-8') as file:
                with open(example_path, 'r', encoding='utf-8') as file:
                    sktech_path  = example_path + os.path.sep + ".."
                    lines = file.readlines()
                    for line in lines:
                         if "//" not in line and keyword in line and not keyword_bypass1 in line and not keyword_bypass2 in line:
                            input_param = re.search(r'\((.*?)\)', line).group(1)
                            if input_param != "":
                                debug_print(f"Current input using: {input_param.split(',')}")
                                params = input_param.split(',') # params
                                model_type = input_param.split(',')[0]
                                model = input_param.split(',')[1:]
                                # update params
                                if model_type == "OBJECT_DETECTION" and not model:
                                    params.extend(['DEFAULT_YOLOV4TINY', 'NA_MODEL', 'NA_MODEL'])
                                if model_type == "FACE_DETECTION" and not model:
                                    params.extend(['NA_MODEL', 'DEFAULT_SCRFD', 'NA_MODEL'])
                                if model_type == "FACE_RECOGNITION" and not model:
                                    params.extend(['NA_MODEL', 'DEFAULT_SCRFD', 'DEFAULT_MOBILEFACENET'])
                                model_type = params[0]
                                model = params[1:]

                                if not (model_type != "" and not model):
                                    # check whether input parameters are in correct sequence
                                    if model_type == "OBJECT_DETECTION" and "NA_MODEL" in model[0] or model_type == "OBJECT_DETECTION" and "YOLO" not in model[0] or model_type == "FACE_DETECTION" and "NA_MODEL" in model[1] or model_type == "FACE_DETECTION" and "SCRFD" not in model[1] or model_type == "FACE_RECOGNITION" and "NA_MODEL" in model[1] or model_type == "FACE_RECOGNITION" and "NA_MODEL" in model[2] or model_type == "FACE_RECOGNITION" and "SCRFD" not in model[1] or model_type == "FACE_RECOGNITION" and "MOBILEFACENET" not in model[2]:
                                        sys.stderr.write(f"[Error] Model mismatch. Please check modelSelect() again.\n")
                                        sys.exit(1)

                                    for model_item in model:
                                        if model_item != "":
                                            debug_print(f"Current model using: {input2model(model_item.strip())}")
                                            
                                            if keyword_customized in model_item.strip():
                                                files = os.listdir(sktech_path)
                                                nb_files = [file for file in files if file.endswith('nb')]
                                                # check whether customized model exists
                                                if len(nb_files) == 0:
                                                    sys.stderr.write(f"[Error] Model not found. Please check your sketch folder again.\n")
                                                    sys.exit(1)
                                                else:
                                                    # check model naming convension
                                                    if input2filename(input2model(model_item.strip())) not in nb_files:
                                                        resetJSON(dest_path)
                                                        sys.stderr.write(f"[Error] Customized model {input2filename(input2model(model_item.strip()))} not found. Please check your sketch folder again.\n")
                                                        sys.exit(1)
                                                backupModel(input2filename(input2model(model_item.strip())), sktech_path)
                                            else:
                                                if model_item.strip() != "NA_MODEL":
                                                    revertModel(input2filename(input2model(model_item.strip())))
                                        # default add in at least one model for NN examples
                                        if input2model(model_item.strip()) != None:
                                            if dupCheckJSON(model_item.strip()):
                                                updateJSON(input2model(model_item.strip()))

def main(param1, param2):
    debug_print(f'Parameter 1: {param1}')
    debug_print(f'Parameter 2: {param2}')
    user_input_flag = False
    while user_input_flag == False:
        if len(sys.argv) > 1:
            user_input1 = sys.argv[1]
        else:
            user_input1 = input("Please provide a valid input > ")
        user_input_flag = True
        resetJSON(dest_path)
        writeJSON(validationINO())

if __name__ == '__main__':
    if len(sys.argv) == 3:
        main(sys.argv[1], sys.argv[2])
    else:
        sys.stderr.write('[Error] Usage: python updatemodel_tool.py {build.path} {ameba.tools_path}')
        sys.exit() 