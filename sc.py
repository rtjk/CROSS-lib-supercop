import datetime
import fileinput
import itertools
import os
import re
import shutil
import sys

###############################################################################
################################# functions ###################################
###############################################################################

def replace_in_file(path, text_to_search, replacement_text):
  with fileinput.FileInput(path, inplace=True) as file:
    for line in file:
        print(re.sub(text_to_search, replacement_text, line), end='')

def replace_in_dir(dir, text_to_search, replacement_text):
    for root, dirs, files in os.walk(dir):
        for file in files:
            file_path = os.path.join(root, file)
            if os.path.isfile(file_path):
                replace_in_file(file_path, text_to_search, replacement_text)

def add_line_in_file(path, new_line, keyword):
    with open(path, 'r', encoding='utf-8') as file:
        lines = file.readlines()
    # insert the new line after the keyword
    for i, line in enumerate(lines):
        if keyword in line:
            lines.insert(i + 1, new_line + '\n')
            break
    with open(path, 'w', encoding='utf-8') as file:
        file.writelines(lines)

def add_line_in_dir(dir, new_line, keyword):
    for root, dirs, files in os.walk(dir):
        for file in files:
            file_path = os.path.join(root, file)
            if os.path.isfile(file_path):
                add_line_in_file(file_path, new_line, keyword)

def generate_namespace(variant, category, target, implementation):
    return f"SUPERCOP_CROSS{variant}{category}{target}_{implementation}_".upper()

def generate_dir_name(variant, category, target, implementation):
    return f"cross{variant}{category}{target}/{implementation}".lower()

###############################################################################
#################################### data #####################################
###############################################################################

TARGET_DIR = './crypto_sign'            # output
UNZIP_DIR = './unzip'                   # unzipped files (temporary)
TEMPLATES_DIR = './templates'           # files to add

PROBLEMS = {"RSDP", "RSDPG"}

CATEGORIES = {128: 1,
              192: 3,
              256: 5}

TARGETS = {"small": "SIG_SIZE",
           "balanced": "BALANCED",
           "fast": "SPEED"}

IMPLEMENTATIONS = {"clean", "avx2"}

###############################################################################
#################################### main #####################################
###############################################################################

# move to the directory where the script is located
base_dir = os.path.dirname(os.path.realpath(__file__))
os.chdir(base_dir)

# delete output directories if they already exists
if os.path.exists(TARGET_DIR):
    shutil.rmtree(TARGET_DIR)
if os.path.exists(UNZIP_DIR):
    shutil.rmtree(UNZIP_DIR)

# unzip the CROSS submission package, provided as input
nist_zip = sys.argv[1]
shutil.unpack_archive(nist_zip, UNZIP_DIR)

# generate all parameter sets
combinations = itertools.product(PROBLEMS, CATEGORIES, TARGETS, IMPLEMENTATIONS)
for p,c,t,i in combinations:
    print('.', end='', flush=True)
    # create the directory
    ps_dir = generate_dir_name(p,c,t,i)
    ps_dir = os.path.join(TARGET_DIR, ps_dir)
    os.makedirs(ps_dir)
    # copy the implementation
    for impl_dir in ["lib", "include"]:
        source_dir = os.path.join(UNZIP_DIR, "Reference_Implementation", impl_dir)
        shutil.copytree(source_dir, ps_dir, dirs_exist_ok=True)
    if(i == "avx2"):
        for impl_dir in ["lib", "include"]:
            source_dir = os.path.join(UNZIP_DIR, "Optimized_Implementation", impl_dir)
            shutil.copytree(source_dir, ps_dir, dirs_exist_ok=True)
    # copy the template files and #include them after the header comment
    keyword = "*/"
    add_line_in_dir(ps_dir, '#include "set.h"', keyword)
    add_line_in_dir(ps_dir, '#include "namespace.h"', keyword)
    add_line_in_dir(ps_dir, '#include "crypto_sign.h"', keyword)
    shutil.copytree(TEMPLATES_DIR, ps_dir, dirs_exist_ok=True)
    # replace the placeholders with the actual parameters
    ps_namespace = generate_namespace(p,c,t,i)
    replace_in_dir(ps_dir, '__namespace__', ps_namespace)
    replace_in_dir(ps_dir, '__problem__', p)
    replace_in_dir(ps_dir, '__implementation__', i)
    replace_in_dir(ps_dir, '__nist-level__', str(CATEGORIES[c]) )
    replace_in_dir(ps_dir, '__target__', TARGETS[t])

current_time = datetime.datetime.now().strftime("%H:%M")
print("\nImplementations placed in", TARGET_DIR, "@", current_time)