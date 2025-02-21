# take as input a zip file containg the NIST submission package for CROSS
# and generate the required directory structure for SUPERCOP

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
    # find the keyword and insert the new line after it
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

# the directory where the script is located
base_dir = os.path.dirname(os.path.realpath(__file__))

TEMPLATES_DIR = base_dir + '/templates'            # files to add
TARGET_DIR =    base_dir + '/crypto_sign'          # output
UNZIP_DIR =     base_dir + '/unzip'                # unzipped files (temporary)
IMPL_DIR =      base_dir + '/impl'                 # CROSS implementation (temporary)

PROBLEMS = ["RSDP", "RSDPG"]

CATEGORIES = {128: 1,
              192: 3,
              256: 5}

TARGETS = {"balanced": "BALANCED",
           "fast": "SPEED",
           "small": "SIG_SIZE"}

IMPLEMENTATIONS = ["clean", "avx2"]

INCLUDE = ["set.h",                                 # specifies the parameter set
           "namespace.h",                           # namespaces functions
           "crypto_sign.h"]                         # SUPERCOP API

###############################################################################
#################################### main #####################################
###############################################################################

# delete output directories if they already exists
if os.path.exists(TARGET_DIR):
    shutil.rmtree(TARGET_DIR)
if os.path.exists(UNZIP_DIR):
    shutil.rmtree(UNZIP_DIR)
if os.path.exists(IMPL_DIR):
    shutil.rmtree(IMPL_DIR)

# unzip the CROSS submission package, provided as input
nist_zip = sys.argv[1]
shutil.unpack_archive(nist_zip, UNZIP_DIR)

# copy the 'clean' and 'avx2' implementations into temporary directories
for source_dir in ["lib", "include"]:
    source_dir = os.path.join(UNZIP_DIR, "Reference_Implementation", source_dir)
    shutil.copytree(source_dir, IMPL_DIR + '/clean', dirs_exist_ok=True)
    shutil.copytree(source_dir, IMPL_DIR + '/avx2', dirs_exist_ok=True)
for source_dir in ["lib", "include"]:
    source_dir = os.path.join(UNZIP_DIR, "Optimized_Implementation", source_dir)
    shutil.copytree(source_dir, IMPL_DIR + '/avx2', dirs_exist_ok=True)
symlink_variant = ''

# include new files afer the header comment
keyword = "*/"
for file in INCLUDE:
    add_line_in_dir(IMPL_DIR, f"#include \"{file}\"", keyword)

# generate all parameter sets
combinations = itertools.product(PROBLEMS, sorted(CATEGORIES), sorted(TARGETS), IMPLEMENTATIONS)
for ps, (p,c,t,i) in enumerate(combinations):
    print('.', end='', flush=True)
    # create the directory
    ps_name = generate_dir_name(p,c,t,i)
    ps_dir = os.path.join(TARGET_DIR, ps_name)
    os.makedirs(ps_dir)
    # copy the template files
    shutil.copytree(TEMPLATES_DIR, ps_dir, dirs_exist_ok=True)
    # replace the placeholders with the actual parameters
    ps_namespace = generate_namespace(p,c,t,i)
    replace_in_dir(ps_dir, '__namespace__', ps_namespace)
    replace_in_dir(ps_dir, '__problem__', p)
    replace_in_dir(ps_dir, '__implementation__', i)
    replace_in_dir(ps_dir, '__nist-level__', str(CATEGORIES[c]) )
    replace_in_dir(ps_dir, '__target__', TARGETS[t])
    # for the first parameter set hard copy the implementation files
    if ps <= 1:
        copy_from = os.path.join(IMPL_DIR, i)
        shutil.copytree(copy_from, ps_dir, dirs_exist_ok=True)
        symlink_variant = os.path.dirname(ps_name)
    # for the rest create symlinks
    else:
        copy_from = os.path.join(TARGET_DIR, symlink_variant, i)
        for file in os.listdir(copy_from):
            if file not in INCLUDE:
                origin = os.path.join('../..', symlink_variant, i, file)
                destination = os.path.join(ps_dir, file)
                os.symlink(origin, destination)

shutil.rmtree(UNZIP_DIR)
shutil.rmtree(IMPL_DIR)

current_time = datetime.datetime.now().strftime("%H:%M")
print("\nImplementations placed in:")
print(TARGET_DIR)
print("Symbolic links point to:", symlink_variant)
print("@", current_time)
