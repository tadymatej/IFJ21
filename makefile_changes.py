import os
import re
from pathlib import Path
curdir = Path(__file__).parent.absolute()
os.chdir(curdir)

res = os.popen('cat ./Makefile')
for line in res.readlines():
    line = line.rstrip()
    if "-I" in line:
        line = line.replace("-I", "")
    if "PATH=" in line:
        line = re.sub(r"PATH=[A-Za-z_]*/", "PATH=", line)
    if ".PHONY" in line:
        print(line + " main")
        print("\nmain: parser_final")
        print("\nparser_final: $(PARSER_DEPS)")
        print("\t $(CC) $(CFLAGS) -o parser $^")
    else:
        print(line)
