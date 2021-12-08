import os
from pathlib import Path
curdir = Path(__file__).parent.absolute()
os.chdir(curdir)
os.system("make")
os.system("clear")

res = os.popen('cat ./tests/test-positions.txt | ./scanner 1')
expect = ["3, 1",
          "3, 9",
          "5, 1",
          "5, 10",
          "5, 13",
          "5, 15",
          "5, 17",
          "5, 24",
          "5, 26",
          "5, 28",
          "5, 30",
          "5, 36",
          "7, 1",
          "9, 1",
          "9, 10",
          "9, 15",
          "9, 17",
          "9, 19",
          "9, 26",
          "9, 28",
          "10, 5",
          "10, 11",
          "10, 13",
          "10, 15",
          "10, 23",
          "10, 25",
          "11, 5",
          "11, 11",
          "11, 13",
          "11, 15",
          "11, 22",
          "11, 24",
          "12, 1",
          "12, 10",
          "12, 13",
          "12, 17",#ERROR
          "13, 5",
          "13, 8",
          "13, 10",
          "13, 12",
          "13, 14",
          "14, 9",
          "14, 12",
          "14, 14", 
          "14, 15",
          "15, 5",
          "17, 5",
          "17, 12",
          "17, 14",
          "17, 16",
          "18, 1",
          "19, 1"#EOF
        ]
i = 0
for line in res.readlines():
    line = line.strip()
    if i >= len(expect):
        print("err")
        break
    if(line != expect[i]):
        print("ERROR! Vypsalo se: {}".format(line))
        print("Ocekavalo se: {}".format(expect[i]))
        print("-------------")
    i += 1