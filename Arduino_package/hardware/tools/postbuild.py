import os
import subprocess
import shutil
import sys
from pathlib import Path

def main():
    """
    Prebuild tool for Ameba toolchain management and NN model synchronization.
    Arguments expected from platform.txt:
    1. TOOLS_PATH (Base tools directory)
    2. TC_P1      (Primary toolchain destination)
    3. TC_P2      (Secondary toolchain source to merge)
    4. MODEL_SRC  (Directory containing .nb models)
    5. HW_PATH    (Hardware variants directory)
    """
    
    if len(sys.argv) < 6:
        print("[Error] Missing arguments. Expected 5, got", len(sys.argv) - 1)
        return
        
    # Using Path objects for better cross-platform handling
    TOOLS_PATH = Path(sys.argv[1])
    TC_P1      = Path(sys.argv[2])
    TC_P2      = Path(sys.argv[3])
    MODEL_SRC  = Path(sys.argv[4])
    HW_PATH    = Path(sys.argv[5])

    # 1. PERMISSION FIX (Unix-like systems only)
    if os.name != 'nt':  # Skip on Windows
        FLAG_FILE = TOOLS_PATH / ".perm_fixed_flag"
        if not FLAG_FILE.exists():
            print(f"[Ameba Manager] Fixing permissions on {TOOLS_PATH}...")
            try:
                # 775: rwxrwxr-x
                subprocess.run(["chmod", "-R", "775", str(TOOLS_PATH)], check=True)
                FLAG_FILE.write_text("fixed")
            except Exception as e:
                print(f"[Warning] Permission fix failed: {e}")

    # 2. TOOLCHAIN MERGE
    if TC_P2.exists() and any(TC_P2.iterdir()):
        print(f"[Ameba Manager] Merging toolchain: {TC_P2.name} -> {TC_P1.name}")
        try:
            for item in TC_P2.iterdir():
                dest = TC_P1 / item.name
                if item.is_dir():
                    if dest.exists():
                        shutil.rmtree(dest)
                    shutil.copytree(item, dest)
                else:
                    shutil.copy2(item, dest)
            
            # Clean up the source TC_P2 parent directory after successful merge
            shutil.rmtree(TC_P2.parent, ignore_errors=True)
            print("[Ameba Manager] Toolchain merge complete.")
        except Exception as e:
            print(f"[Error] Toolchain merge failed: {e}")

    # 3. NN MODEL SYNC
    MODEL_DEST = HW_PATH / "variants" / "common_nn_models"
    if MODEL_SRC.exists():
        try:
            MODEL_DEST.mkdir(parents=True, exist_ok=True)
            model_files = list(MODEL_SRC.glob("*.nb"))
            if model_files:
                print(f"[Ameba Manager] Syncing {len(model_files)} NN models...")
                for model_file in model_files:
                    shutil.copy2(model_file, MODEL_DEST / model_file.name)
        except Exception as e:
            print(f"[Error] NN Model sync failed: {e}")

if __name__ == "__main__":
    main()
