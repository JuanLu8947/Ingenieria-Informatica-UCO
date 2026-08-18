#!/usr/bin/env python3
# -*- coding: utf-8 -*-
# Description: Script to run unit tests.
# Author: Francisco José Madrid Cuevas <fjmadrid@uco.es>
# Date: 2025-01-29

import sys
import os
import subprocess
import glob
import argparse

__version__ = "1.0.0"


def is_executable(file_path):
    if os.name == "nt":
        file_path += ".exe"
    return os.path.isfile(file_path) and os.access(file_path, os.X_OK)


def is_directory(file_path):
    return os.path.isdir(file_path)


def is_file(file_path):
    return os.path.isfile(file_path)


def eprint(*args, **kwargs):
    print(*args, file=sys.stderr, **kwargs)


if __name__ == "__main__":
    parser = argparse.ArgumentParser(
        description=f'Run unit tests ({__version__})')
    parser.add_argument('test_program', type=str, help='Test program')
    parser.add_argument(
        'test', type=str, help='Test file or folder with all the tests to run')
    args = parser.parse_args(sys.argv[1:])
    if not is_executable(args.test_program):
        eprint("Test program is not executable.")
        sys.exit(1)
    if not is_file(args.test) and not is_directory(args.test):
        eprint("Test file or folder does not exist.")
        sys.exit(1)
    tests = []
    if is_directory(args.test):
        tests = sorted(glob.glob(args.test + "/??"))
    else:
        tests.append(args.test)
    correct_count = 0
    for test in tests:
        print("Test running: " + test + " ... ", end="")
        output = subprocess.run([args.test_program, test],
                                capture_output=True,
                                text=True,
                                encoding="utf-8",
                                timeout=30)
        if output.returncode != 0:
            print(
                f"\033[31mTest finished with error code {output.returncode}\033[0m")
            print(output.stderr)
        else:
            with open(test + ".a", encoding="utf-8") as f:
                expected_output = f.read()
            if output.stdout != expected_output:                
                print("\033[31mTest failed.\033[0m")
                print("Expected output:")
                print("["+expected_output+"]")
                print("Actual output:")
                print("["+output.stdout+"]")
            else:
                print("\033[32mTest passed.\033[0m")
                correct_count += 1
    print(f"{correct_count}/{len(tests)} tests passed.")
    if correct_count == len(tests):
        sys.exit(0)
    else:
        sys.exit(1)
