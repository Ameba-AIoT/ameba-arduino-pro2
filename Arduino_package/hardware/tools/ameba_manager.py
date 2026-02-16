import os
import subprocess
import shutil
import sys

def main():
    # 1. PATH DEFINITIONS (Passed from platform.txt)
    # Args: tools_path, tc_p1, tc_p2, model_src, hw_path
    if len(sys.argv) < 6:
        return
        
    TOOLS_PATH = sys.argv[1]
    TC_P1      = sys.argv[2]
    TC_P2      = sys.argv[3]
    MODEL_SRC  = sys.argv[4]
    HW_PATH    = sys.argv[5]
    
    # 2. PERMISSION FIX (Run Once Logic)
    FLAG_FILE = os.path.join(TOOLS_PATH, ".perm_fixed_flag")
    if not os.path.exists(FLAG_FILE):
        print(f"[Ameba Manager] First run detected. Fixing permissions on {TOOLS_PATH}...")
        try:
            subprocess.run(["chmod", "-R", "777", TOOLS_PATH], check=True)
            with open(FLAG_FILE, "w") as f: f.write("fixed")
        except Exception as e:
            print(f"[Error] Permission fix failed: {e}")

    # 3. TOOLCHAIN MERGE
    if os.path.exists(TC_P2):
        print("[Ameba Manager] Merging toolchain parts...")
        for item in os.listdir(TC_P2):
            s, d = os.path.join(TC_P2, item), os.path.join(TC_P1, item)
            if os.path.isdir(s):
                if os.path.exists(d): shutil.rmtree(d)
                shutil.copytree(s, d)
        shutil.rmtree(os.path.dirname(TC_P2), ignore_errors=True)

    # 4. NN MODEL SYNC
    model_dest = os.path.join(HW_PATH, "variants/common_nn_models")
    if os.path.exists(MODEL_SRC):
        os.makedirs(model_dest, exist_ok=True)
        for f in os.listdir(MODEL_SRC):
            if f.endswith(".nb"):
                shutil.copy2(os.path.join(MODEL_SRC, f), model_dest)

if __name__ == "__main__":
    main()

