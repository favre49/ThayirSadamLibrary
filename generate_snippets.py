#!/usr/bin/env python3
import os
import sys
import argparse
import re

CUTOFF_LINE = 'using namespace std;\n'

def parse_arguments():
    parser = argparse.ArgumentParser()
    parser.add_argument('-s','--source', default = os.getcwd(), help = 'Source directory for code files')
    parser.add_argument('-d', '--dest', default = os.path.join(os.getcwd(), 'snippets'), help = 'Destination directory for snippets')
    return parser.parse_args()

def get_base_filename(path):
    return os.path.basename(path).split('.')[0]

# Get the list of code files
def get_code_files(path):
    code_file_list = []
    for root, dirs, files in os.walk(path):
        # Don't go into hidden folders
        files = [f for f in files if not f[0] == '.']
        dirs[:] = [d for d in dirs if not d[0] == '.']
        for filename in files:
            if filename.endswith(".hpp"):
                code_file_list.append(os.path.join(root, filename))
    return code_file_list

def generate_snippet(code_filename):
    with open(code_filename, 'r') as code_file:
        code_file_content = code_file.read()
    snippet_content = ''

    # Get snippet from file
    cutoff_occ = code_file_content.find(CUTOFF_LINE)
    if cutoff_occ == -1:
        print('Code file ' + filename + ' does not contain the cutoff line')
    snippet_content += code_file_content[cutoff_occ + len(CUTOFF_LINE):]
    snippet_content.strip()
    return snippet_content

def write_snippet_file(dest_file, snippet_name, snippet_content):
    prefix = 'snippet ' + snippet_name + '\n'
    suffix = 'endsnippet'
    snippet_content = prefix + snippet_content + suffix
    with open(dest_file, 'w+') as snippet_file:
        snippet_file.write(snippet_content)

def main():
    args = parse_arguments()
    source_dir = args.source
    dest_dir = args.dest
    os.makedirs(dest_dir, exist_ok = True)
    code_file_list = get_code_files(source_dir)
    for code_filename in code_file_list:
        snippet_content = generate_snippet(code_filename)
        snippet_file_path = os.path.join(dest_dir, get_base_filename(code_filename) + '.snippets')
        write_snippet_file(snippet_file_path, get_base_filename(code_filename).lower(), snippet_content)

if __name__ == '__main__':
    main()
