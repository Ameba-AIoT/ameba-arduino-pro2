# Readme
# This tool is using for prebuild stage. handling toolchain and Arduino IDE option erase flash.
# ------------------------------------------------------
# To generate executable
# windows os 
## power shell
## pyinstaller --onefile --name prebuild_windows prebuild_tool.py
# linux os 
## pyinstaller --onefile --name prebuild_linux prebuild_tool.py
# macos 
## python3 -m PyInstaller --onefile --name prebuild_macos ./prebuild_tool.py
# ------------------------------------------------------

import os
import sys
import shutil

def copy_files_recursive(src_dir, dest_dir):
    try:
        # get the name of the source directory
        ###src_name = os.path.basename(src_dir)
        # create the destination directory if it doesn't exist
        if not os.path.exists(dest_dir):
            os.makedirs(dest_dir)
        # copy all files and subdirectories recursively
        for item in os.listdir(src_dir):
            src = os.path.join(src_dir, item)
            dest = os.path.join(dest_dir, item)
            if os.path.isdir(src):
                # recursively copy subdirectories
                copy_files_recursive(src, dest)
            else:
                # overwrite existing files using shutil.copy2()
                shutil.copy2(src, dest)
    except Exception as e:
        print(f"Error copying files: {e}")


def main(toolchian_path, toolchian_p2_path, toolchain_p1, toolchain_p2):
#   current_dir = os.getcwd()
#   get the full path of the source folder
#   full_path = os.path.join(current_dir, folder_name)

    if os.path.exists(toolchian_p2_path):
        copy_files_recursive(toolchian_p2_path, toolchian_path)
        try:
            shutil.rmtree(toolchian_p2_path)
        except Exception as e:
            print(f"Error: {toolchain_p2} : {e}")

if __name__ == '__main__':
#    print('prebuild tool test ')

    main(sys.argv[1], sys.argv[2], sys.argv[3], sys.argv[4])

#    print('prebuild tool test done')
#    sys.exit(1)
