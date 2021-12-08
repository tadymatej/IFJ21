import os
from pathlib import Path
curdir = Path(__file__).parent.absolute()
os.chdir(curdir)
os.system("make")
os.system("clear")

def insertCommentsToFile(dirPath, fileName):
    file = open(dirPath + "/" + fileName, 'r')
    fileWrite = open(dirPath + "/comments/" + fileName, "w")
    lines = file.readlines()
    for line in lines:
        if "--" not in line:
            for c in line:
                print(c, file=fileWrite, end="")
                if c is '\n' or c is ' ' or c is ',' or c is ':':
                    print("--[[]]", file=fileWrite, end="")
                    print("--[[ahojkyneee a da das d\n\ndasdas]]", file=fileWrite, end="")
        else:
            print(line, file=fileWrite)


files = os.listdir(curdir)
for file in files:
    if ".tl" in file:
        insertCommentsToFile(str(curdir), file)