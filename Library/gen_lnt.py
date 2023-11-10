# Lint option file generator
#  Usage: python gen_lnt.py <file_name> <compiler_path>

import os
import sys
import yaml

# Open file
def openFile(name, mode):
    try:
        file = open(name, mode)
        return file
    except Exception as e:
        print(f"Error in openFile({name}): {e}")
        sys.exit(1)

# Main function
def main():

    cmsis_pack_root = os.getenv("CMSIS_PACK_ROOT")

    if len(sys.argv) != 3:
        print("Error: Invalid number of arguments")
        sys.exit(1)

    compiler_path = sys.argv[2]
    file_name = sys.argv[1]
    library = file_name.split('.')[0]
    target  = file_name.split('+')[1]

    yml_file = openFile(file_name + ".cbuild.yml", "r")
    yml_data = yaml.load(yml_file, Loader=yaml.FullLoader)["build"]
    yml_file.close()

    lnt_file = openFile(file_name + ".lnt", "w")

    lnt_file.write("// PC-Lint invocation file (auto generated)\n\n")

    lnt_file.write("-i./lnt\n\n")

    lnt_file.write("// Generated ARM Compiler Preprocessor Symbols:\n")
    lnt_file.write("+libh(armclang_" + target + ".h)\n")
    lnt_file.write("-header(armclang_" + target + ".h)\n")
    lnt_file.write("\n")

    lnt_file.write("// Compiler Include paths:\n")
    lnt_file.write("-i" + compiler_path + "/include\n")
    lnt_file.write("-i" + compiler_path + "/include/libcxx\n")
    lnt_file.write("\n")

    lnt_file.write("// Project defines:\n")
    list = yml_data["define"]
    for item in list:
         lnt_file.write("-d" + item + "\n")
    lnt_file.write("\n")

    lnt_file.write("// Project Include paths:\n")
    list = yml_data["add-path"]
    for item in list:
         item_path = str(item).replace("${CMSIS_PACK_ROOT}", cmsis_pack_root)
         lnt_file.write("-i" + item_path + "\n")
    lnt_file.write("\n")

    lnt_file.write("// Project configuration\n")
    lnt_file.write(library + ".lnt\n\n")

    lnt_file.write("// Source file(s) for verification:\n")
    groups = yml_data["groups"]
    for group in groups:
        if "Core" in group["group"]:
            files = group["files"]
            for file in files:
                lnt_file.write(file["file"] + "\n")

    lnt_file.close()

if __name__ == "__main__":
    main()
