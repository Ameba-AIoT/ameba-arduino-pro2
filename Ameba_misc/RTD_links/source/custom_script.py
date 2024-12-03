import os
import shutil

board_list = []
common_list = []
temp_only_list = [1000, 1000]

def create_folder(folder_name):
    try:
        os.mkdir(folder_name)
        print(f"Folder '{folder_name}' created successfully.")
    except FileExistsError:
        print(f"Folder '{folder_name}' already exists.")
    except OSError as error:
        print(f"Creation of the directory '{folder_name}' failed: {error}")

def get_folder_paths(folder_path, mode):
    folder_paths = []
    if mode == 0:
        for item in os.listdir(folder_path):
            item_path = os.path.join(folder_path, item)
            if os.path.isdir(item_path):
                folder_paths.append(item_path)
    elif mode == 1:
        for item in os.listdir(folder_path):
            if os.path.isdir(os.path.join(folder_path, item)) and not item.startswith("_"):
                folder_paths.append(item)
    return folder_paths

def copy_files(o_file, c_file, mode):
    ### copytree
    if mode == 1:
        source_path = os.path.abspath(o_file)
        target_path = os.path.abspath(c_file)
        shutil.copytree(source_path, target_path)
    ### copyfile
    else:
        source_path = os.path.abspath(o_file)
        target_path = os.path.abspath(c_file)
        shutil.copyfile(source_path, target_path)

def copy_folder(src_folder, target_folder):
    """
    Copy the contents of a folder into an existing target folder.

    Args:
        src_folder (str): Path to the source folder.
        target_folder (str): Path to the target folder.

    Returns:
        None
    """
    # Check if source folder exists
    if not os.path.exists(src_folder):
        raise FileNotFoundError(f"Source folder '{src_folder}' not found.")

    # Check if target folder exists, create it if not
    if not os.path.exists(target_folder):
        os.makedirs(target_folder)

    # Iterate over all items in the source folder
    for item in os.listdir(src_folder):
        src_item = os.path.join(src_folder, item)
        target_item = os.path.join(target_folder, item)

        # If it's a directory, copy it recursively
        if os.path.isdir(src_item):
            if os.path.exists(target_item):
                # If the target subdirectory already exists, merge contents
                shutil.copytree(src_item, target_item, dirs_exist_ok=True)
            else:
                shutil.copytree(src_item, target_item)
        # If it's a file, copy it directly
        else:
            shutil.copy2(src_item, target_item)

def replace_text_in_file(file_path, text_a, text_b):
    """
    Replace all occurrences of text A with text B in the specified file.

    Parameters:
    file_path (str): The path to the file.
    text_a (str): The text to be replaced.
    text_b (str): The text to replace with.

    Returns:
    str: A message indicating the success of the operation.
    """
    try:
        # Read the content of the file
        with open(file_path, 'r', encoding='utf-8') as file:
            content = file.read()

        # Replace the text
        new_content = content.replace(text_a, text_b)

        # Write the modified content back to the file
        with open(file_path, 'w', encoding='utf-8') as file:
            file.write(new_content)

        return f"Text '{text_a}' has been replaced with '{text_b}' in the file '{file_path}'"

    except Exception as e:
        return f"An error occurred: {e}"

if __name__ == "__main__":
    # Change the current working directory
    new_directory = './Ameba_misc/RTD_links/source'
    os.chdir(new_directory)
    # Print the new current working directory
    print(os.getcwd())

    # copy json files
    copy_files('../../../Arduino_package/package_realtek_amebapro2_early_index.json', '_static/package_realtek_amebapro2_early_index_rtd.json', 0);
    ### copy_files('../../../Arduino_package/package_realtek_amebapro2_early_index.json', '_static/package_realtek_amebapro2_index_rtd.json', 0);

    # copy release files
    copy_folder('../../../Arduino_package/release', '_static/release');

    replace_text_in_file('_static/package_realtek_amebapro2_early_index_rtd.json', 'github.com/Ameba-AIoT/ameba-arduino-pro2/raw/dev/Arduino_package', 'ameba-doc-test-zzw.readthedocs-hosted.com/en/latest/_static');

    # Remove the folder '/path/to/folder' and all its contents
    ###shutil.rmtree('_static/release')






















































