import os
import sys
import shutil
from pathlib import Path

def copy_files_recursive(src_dir, dest_dir):
    """
    Recursively copies files from src_dir to dest_dir, overwriting existing files.
    """
    src_path = Path(src_dir)
    dest_path = Path(dest_dir)

    if not dest_path.exists():
        dest_path.mkdir(parents=True, exist_ok=True)

    for item in src_path.iterdir():
        dest = dest_path / item.name
        if item.is_dir():
            copy_files_recursive(item, dest)
        else:
            # shutil.copy2 preserves file metadata (timestamps, etc.)
            shutil.copy2(item, dest)

def main():
    # Validate that all 4 required arguments are provided
    if len(sys.argv) < 5:
        print("Usage: prebuild_tool.py <toolchain_path> <toolchain_p2_path> <p1_name> <p2_name>")
        sys.exit(1)

    # Assigning arguments to descriptive variables
    toolchain_path = Path(sys.argv[1])
    toolchain_p2_path = Path(sys.argv[2])
    # toolchain_p1 = sys.argv[3]  # Currently unused in original logic
    toolchain_p2_label = sys.argv[4]

    # Process only if the 'part 2' directory exists and has content
    if toolchain_p2_path.exists() and any(toolchain_p2_path.iterdir()):
        try:
            print(f"Merging {toolchain_p2_label} into {toolchain_path}...")
            copy_files_recursive(toolchain_p2_path, toolchain_path)
            
            # Safe cleanup: Only delete if the copy process didn't crash
            print(f"Cleaning up {toolchain_p2_label}...")
            shutil.rmtree(toolchain_p2_path)
            toolchain_p2_path.mkdir(parents=True, exist_ok=True)
            
            print("Prebuild process completed successfully.")
        except Exception as e:
            print(f"Critical Error during {toolchain_p2_label} processing: {e}")
            sys.exit(1)
    else:
        print(f"Source directory {toolchain_p2_path} is empty or does not exist. Skipping.")

if __name__ == '__main__':
    main()
