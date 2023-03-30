# ------------------------------------------------------
# README
# This tool is to check whether correct model has being selected in Arduino IDE Tools menu while running dedicated NN example
# For Example: whether scrfd and mobilefacenet models have been selected while running NNFaceRecognition Example
# ------------------------------------------------------
# To generate executable
# python -m PyInstaller  --onefile --name ino_validation_windows.exe .\ino_validation.py 
# python3 -m PyInstaller --onefile ./ino_validation.py
#                        -w: no terminal required 
# ------------------------------------------------------
# Linux Permission Denied: chmod +x myapp ls -l myapp

import os
import re
import sys
import json
from sys import platform

DEBUG = 0
def debug_print(message):
    if DEBUG:
        print(message)

keywordNN = "modelSelect"
keywordVOE = "configVideoChannel"
keyword_header = "#include"
keyword_customized = "CUSTOMIZED"
keyword_default = "DEFAULT"
keyword_default_backup = "Dbackup"
keyword_customized_backup = "Cbackup"
keyword_bypassNN1 = " .modelSelect"
keyword_bypassNN2 = " modelSelect"
keyword_bypassVOE1 = " .configVideoChannel"
keyword_bypassVOE2 = " configVideoChannel"

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

def resetTXT():    
    directory = os.path.dirname(filepath_txt)
    if not os.path.exists(directory):
        os.makedirs(directory)
    with open(filepath_txt, 'w') as file:
        pass
    debug_print(f"[INFO] {filename_txt} has been reset")

def updateTXT(input):
    directory = os.path.dirname(filepath_txt)
    if not os.path.exists(directory):
        os.makedirs(directory)
    with open(filepath_txt, 'a') as file:
        file.write(input + "\n")

def updateNATXT(filepath, start_line, end_line):
    with open(filepath, 'r') as file:
        lines = file.readlines()
    start_line_index = None
    end_line_index = None

    for index, line in enumerate(lines):
        if start_line in line:
            start_line_index = index
        if end_line in line:
            end_line_index = index
        if start_line_index is not None and end_line_index is not None:
            break

    if start_line_index is not None and end_line_index is not None:
        content_between_lines = lines[start_line_index + 1:end_line_index]
        is_empty = all(line.strip() == '' for line in content_between_lines)
        if is_empty:
            lines.insert(start_line_index + 1, "NA\nNA\nNA\n")
        with open(filepath, 'w') as file:
            file.writelines(lines)
    else:
        raise ValueError("Start or end line not found in the file")

def dupCheckTXT(input):
    if input == "NA":
        return 1
    with open(filepath_txt,'r') as file:
        if input2model(input) not in file.read():
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

def input2header(input):
    header_mapping = {
        "yolov3_tiny"               : "NNObjectDetection.h",
        "yolov4_tiny"               : "NNObjectDetection.h",
        "yolov7_tiny"               : "NNObjectDetection.h",
        "mobilefacenet_i16"         : "NNFaceDetectionRecognition.h",
        "scrfd640"                  : "NNFaceDetection.h",
        "yolov3_tiny"               : "NNObjectDetection.h",
        "yolov4_tiny"               : "NNObjectDetection.h",
        "yolov7_tiny"               : "NNObjectDetection.h",
        "mobilefacenet_i8"          : "NNFaceDetectionRecognition.h",
        "scrfd320p"                 : "NNFaceDetection.h",
        "None"                      : "NA"
    }
    header = header_mapping.get(input)
    return header

def input2filename(input):
    if os.path.isdir(dest_path):
        for file_json in os.listdir(dest_path):
            if file_json.endswith(".json"):
                with open(os.path.join(dest_path, file_json), "r+") as file:
                    data = json.load(file)
                    value_file = data[input]["file"]
        return value_file

def validationINO():
    for file_json in os.listdir(sys.argv[1]):
        if file_json.endswith(".json") and "build" in file_json:
            with open(os.path.join(sys.argv[1], file_json), "r+") as file:
                # get path and file name for further process
                data = json.load(file)
                # Arduino IDE1.0 
                example_path = data["sketchLocation"]
                # Arduino IDE2.0 
                if "Arduino15" not in example_path: 
                    example_name = example_path.split(os.path.sep)[-1]
                    if ".ino" not in example_path and ".ino" not in example_name:
                        for file in os.listdir(example_path):
                            if ".ino" in file:
                                example_name = example_name + ".ino"
                                example_path = example_path + os.path.sep + example_name
                    
                    for file_cache in os.listdir(sys.argv[1]):
                        if file_cache.endswith(".cache") and "libraries" in file_cache:
                            with open(os.path.join(sys.argv[1], file_cache), "r+") as file:
                                for library_path in json.loads(file.read()):
                                    if "libraries" in library_path:
                                        library_path = library_path + os.path.sep + ".." + os.path.sep + "examples" + os.path.sep
                                        debug_print(f"[INFO] Current library_path: {library_path}")
                                        if example_name in os.listdir(library_path):
                                            example_path = library_path + example_name + os.path.sep + example_name + ".ino"
                                            debug_print(f"[INFO] Current example_path: {example_path}")
                    debug_print(f"[INFO] Current example {example_name} running in: {example_path}")
    return example_path

model_list = []

def writeTXT(example_path):
    for file_json in os.listdir(sys.argv[1]):
        if file_json.endswith(".json") and "build" in file_json:
            with open(os.path.join(sys.argv[1], file_json), "r+") as file:
                with open(example_path, 'r') as file:
                    sktech_path  = example_path + os.path.sep + ".."
                    lines = file.readlines()
                    updateTXT("----------------------------------")
                    updateTXT("Current ino contains model(s):")
                    for line in lines:
                        # check whether keywordNN in file content
                        if "//" not in line and keywordNN in line and not keyword_bypassNN1 in line and not keyword_bypassNN2 in line:
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
                                            model_list.append(input2model(model_item.strip()))
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
                                                        resetTXT()
                                                        sys.stderr.write(f"[Error] Customized model {input2filename(input2model(model_item.strip()))} not found. Please check your sketch folder again.\n")
                                                        sys.exit(1)
                    if not model_list:
                        for i in range(3):
                            updateTXT("NA")
                    else:
                        for i in range(int(len(model_list)/3 - 1)):
                            n = 3 * (i + 1)
                            for j in range(3):
                                if model_list[j] is None and model_list[j + n] is not None:
                                    model_list[j] = model_list[j + n] 
                        for i in range(3):
                            if model_list[i] is not None:
                                updateTXT(model_list[i])
                            else:
                                updateTXT("NA")

                    updateTXT("-----------------------------------")
                    updateTXT("Current NN header file(s): ")
                    line_list = []
                    for line in lines:
                        if line.startswith(keyword_header) and "NN" in line:
                            line_list.append(line.replace('"','').split()[-1])
                    if not model_list:
                        for i in range(3):
                            updateTXT("NA")
                    else:
                        for i in range(3):
                            if model_list[i] is not None:
                                if input2header(model_list[i]) in line_list:
                                    updateTXT(input2header(model_list[i]))
                                else:
                                    updateTXT("NA")
                            else:
                                updateTXT("NA")

                    updateTXT("----------------------------------")
                    updateTXT("Current ino video status:")
                    textVOE = "NA"
                    for line in lines:
                        # check whether keywordVOE in file content
                        if "//" not in line and keywordVOE in line and not keyword_bypassVOE1 in line and not keyword_bypassVOE2 in line:
                            textVOE = "ON"
                    updateTXT(textVOE)
                    
                    updateTXT("-------------------------------------")
                    updateTXT("Current ino contains header file(s): ")
                    for line in lines:
                        if line.startswith(keyword_header):
                            updateTXT(line.replace('"','').split()[-1])
                    updateTXT("--------------------------------------")
                    
                    start_line1 = "Current ino contains model(s):"
                    end_line1 = "-----------------------------------"
                    updateNATXT(filepath_txt, start_line1, end_line1)
                    start_line2 = "Current NN header file(s):"
                    end_line2 = "-------------------------------------"
                    updateNATXT(filepath_txt, start_line2, end_line2)
                    start_line3 = "Current ino contains header file(s):"
                    end_line3 = "--------------------------------------"
                    updateNATXT(filepath_txt, start_line3, end_line3)

def main(param1, param2):
    debug_print(f'Parameter 1: {param1}')
    debug_print(f'Parameter 2: {param2}')
    user_input_flag = False
    while user_input_flag == False:
        user_input_flag = True
        resetTXT()
        writeTXT(validationINO())

if __name__ == '__main__':
    if len(sys.argv) == 3:
        main(sys.argv[1], sys.argv[2])
    else:
        sys.stderr.write('[Error] Usage: python updatemodel_tool.py {build.path} {ameba.tools_path}')
        sys.exit() 