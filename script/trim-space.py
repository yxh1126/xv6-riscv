#!/usr/bin/env python3
"""
Script: trim_space.py
Description: Removes trailing whitespace from lines and ensures each file
             ends with exactly one newline.
Target: xv6-riscv source files (.c, .h, .S, .s, .pl, .py, .ld, Makefile)
"""

import os

# Added .ld for Linker Scripts
EXTENSIONS = {'.c', '.h', '.S', '.s', '.pl', '.py', '.md', '.ld', 'Makefile'}
IGNORE_DIRS = {'.git', '__pycache__', 'target', '.vscode'}

def trim_files(directory):
    for root, dirs, files in os.walk(directory):
        # Skip hidden/system directories
        dirs[:] = [d for d in dirs if d not in IGNORE_DIRS]

        for file in files:
            # Match extensions or specific filenames like 'Makefile'
            if any(file.endswith(ext) or file == ext for ext in EXTENSIONS):
                file_path = os.path.join(root, file)

                try:
                    # 'errors=ignore' handles potential non-utf8 characters in comments
                    with open(file_path, 'r', encoding='utf-8', errors='ignore') as f:
                        content = f.read()

                    if not content.strip():
                        # If file is empty or only whitespace, make it truly empty
                        new_content = ""
                    else:
                        # 1. Split into lines
                        # 2. Trim trailing whitespace from every line
                        # 3. Strip all trailing newlines from the end of the file
                        # 4. Add exactly ONE newline back
                        lines = content.splitlines()
                        new_content = "\n".join(line.rstrip() for line in lines).rstrip('\n') + "\n"

                    if content != new_content:
                        with open(file_path, 'w', encoding='utf-8') as f:
                            f.write(new_content)
                        print(f"Cleaned: {file_path}")

                except Exception as e:
                    print(f"Skipping {file_path}: {e}")

if __name__ == "__main__":
    trim_files('.')
    print("\nProcess complete.")
    print("Files updated: Trailing spaces removed & exactly one newline at EOF.")
