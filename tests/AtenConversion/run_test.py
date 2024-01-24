import os
import subprocess

if __name__ == "__main__":
    testFiles = []
    for root, dirs, files in os.walk("."):
        for item in files:
            if item[-5:] == ".aten":
                testFiles.append(item)
    print("[ info ] Run Aten-lang Grammar Parse Test")
    for item in testFiles:
        completed = subprocess.run(
            ['../../build/bin/nncv-c', '-aten-ir', item, '-o', item[:-5] + '_aten_ir.air'])
        boolStr = "success" if completed.returncode == 0 else "failure"
        print("[ info ] running on file: ", item, boolStr)
        completed = subprocess.run(
            ['../../build/bin/nncv-c', '-built-in-mlir', item, '-o', item[:-5] + '_mlir.mlir'])
        boolStr = "success" if completed.returncode == 0 else "failure"
        print("[ info ] running on file: ", item, boolStr)
