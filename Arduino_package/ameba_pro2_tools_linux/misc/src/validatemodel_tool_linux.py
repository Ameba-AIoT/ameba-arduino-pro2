# Readme
# This tool is to check whether correct model has being selected in Arduino IDE Tools menu while running dedicated NN example
# For Example: whether scrfd and mobilefacenet models have been selected while running NNFaceRecognition Example
# ------------------------------------------------------
# To generate executable
# python -m PyInstaller  --onefile .\updatemodel_tool.py 
# python3 -m PyInstaller --onefile ./validatemodel_tool.py
#                        -w: no terminal required 
# ------------------------------------------------------
# To run 
# updatemodel_tool.exe EMPTY/DYV4
# ------------------------------------------------------
# Linux Permission Denied: chmod +x myapp ls -l myapp

import os
import sys
import json
from sys import platform

DEBUG = 0
def debug_print(message):
    if DEBUG:
        print(message)

# declear common file paths
usrmodel_path = os.path.abspath(os.path.dirname(sys.argv[0]))
for file_user_model in os.listdir(usrmodel_path):
    if file_user_model.endswith(".nb"):
        # debug_print(os.path.join(usrmodel_path, file_user_model))
        file_user_model_no_ext = os.path.splitext(os.path.basename(file_user_model))[0]
        # debug_print(file_user_model_no_ext)

if platform == "win32":
    # Windows...
    desktop = os.path.join(os.path.join(os.environ['USERPROFILE']), 'Desktop')
    ameba_model_path = os.path.join(desktop, 'AmebaModel\\')
    debug_print(desktop)
    arduino15_path = os.path.expanduser("~\AppData\Local\Arduino15")
    ambpro2_path = arduino15_path + "\packages\\realtek\hardware\AmebaPro2"
    sdk_version = os.listdir(ambpro2_path)[0]
    dest_path = ambpro2_path + "\\" + sdk_version + "\\variants\common_nn_models\\"
elif platform == "linux" or platform == "linux2":
    # linux
    desktop = os.path.join(os.path.join(os.path.expanduser('~')), 'Desktop')
    ameba_model_path = os.path.join(desktop, 'AmebaModel/')
    debug_print(desktop)
    arduino15_path = os.path.expanduser("/home/" + os.getlogin() + "/.arduino15")
    ambpro2_path = arduino15_path + "/packages/realtek/hardware/AmebaPro2/"
    sdk_version = os.listdir(ambpro2_path)[0]
    dest_path = ambpro2_path + "/" + sdk_version + "/variants/common_nn_models/"
elif platform == "darwin":
    # OS X
    desktop = os.path.join(os.path.join(os.path.expanduser('~')), 'Desktop')
    ameba_model_path = os.path.join(desktop, 'AmebaModel/')
    debug_print(desktop)
    arduino15_path = os.path.expanduser("/Users/" + os.getlogin() + "/Library/Arduino15")
    ambpro2_path = arduino15_path + "/packages/realtek/hardware/AmebaPro2/"
    sdk_version = os.listdir(ambpro2_path)[1]
    dest_path = ambpro2_path + "/" + sdk_version + "/variants/common_nn_models/"

def validateModel(input):
    for file_json2 in os.listdir(dest_path):
        if file_json2.endswith(".json"):
            with open(os.path.join(dest_path, file_json2), "r+") as file:
                data = json.load(file)
                debug_print(data["FWFS"]["files"])
                if input not in "".join(data["FWFS"]["files"]):
                    sys.stderr.write(f"[Error] {input} model not selected. Please check your input selection.\n")
                    sys.exit(1)

if __name__ == '__main__':
    user_input_flag = False
    while user_input_flag == False:
        if len(sys.argv) > 1:
            user_input_sub1 = sys.argv[1]
            debug_print(f"User input: {user_input_sub1}")
        else:
            user_input_sub1 = input("Please provide a valid input > ")
            debug_print(f"User input: {user_input_sub1}")
        user_input_flag = True
        
        for file_json in os.listdir(user_input_sub1):
            if file_json.endswith(".json"):
                with open(os.path.join(user_input_sub1, file_json), "r+") as file:
                    data = json.load(file)

        with open(data["sketchLocation"], 'r+') as file:
            lines = file.readlines()
            for line in lines:
                if line.startswith("#include \"NN") :
                    debug_print(line)
                    if "ObjectDetection" in line[12:]:
                        keyword = "yolo"
                    if "FaceDetection" in line[12:]:
                        keyword = "scrfd"
                    if "FaceRecognition" in line[12:]:
                        keyword = "mobilefacenet"
                    validateModel(keyword)
 
