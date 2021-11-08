import os
from pathlib import Path
curdir = Path(__file__).parent.absolute()
os.chdir(curdir)
os.system("make")
os.system("clear")

print_success = "typ: {} || hodnota: {}"
print_error = "Lexikalni chyba na radku: %d a sloupci: %d\n"

def test(command, expected_lines, testname):
    res = os.popen('echo "{}" | ./scanner'.format(command))
    i = 0
    for line in res.readlines():
        line = line.strip()
        try:
            if expected_lines[i][2]:
                expected_line = print_success.format(*expected_lines[i]).strip()
            else:
                expected_line = print_error.format(*expected_lines[i]).strip()
            j = 0
            for c in line:
                if c is not expected_line[j]:
                    print("---------------------")
                    print("Chyba uvnitr testu: {}, vystupem bylo: \n{}\nocekavalo se: \n{}".format(testname, line, expected_line))
                    break
                j += 1
            i += 1
        except:
            return

def tests(commands, expected_lines, testname):
    i = 0
    for command in commands:
        i += 1
        test(command, expected_lines, testname + "-" + str(i))

def test_template():
    expected_lines = [
        ["", "", True]
    ]
    commands = [
        "",]
    tests(commands, expected_lines, "test")

def test1():
    expected_lines = [
        ["id", "ahoj", True],
        ["id", "nazdar", True],
        ["number int", "5", True],
        ["mul", "(null)", True],
        ["number int", "10", True]
    ]
    commands = [
        "ahoj nazdar 5 * 10",
        "ahoj nazdar 5*10",
        "ahoj     --[[]]nazdar  5   *   10",
        "ahoj     nazdar  5   *   10",
        "ahoj     --[[komentar]]nazdar  5   *   10"
    ]
    tests(commands, expected_lines, "test1")

def test2():
    expected_lines = [
        ["keyword", "global", True],
        ["keyword", "function", True],
        ["id_f", "ahoj", True],
        #["start bracket", "(null)"],
        ["id", "a", True],
        ["colon - dvojtecka", "(null)", True],
        ["keyword", "integer", True],
        ["comma", "(null)", True],
        ["id", "b", True],
        ["colon - dvojtecka", "(null)", True],
        ["keyword", "number", True],
        ["end bracket","(null)", True],
        ["colon - dvojtecka","(null)", True],
        ["keyword","number", True],
        ["comma","(null)", True],
        ["keyword","number", True]
    ]
    commands = [
        "global function ahoj(a : integer, b : number) : number, number",
        "     global function ahoj(a : integer,        b : number) :      number,     number",
        "global     function ahoj(a    : integer, b : number) : number, number",
        "global function ahoj(a : \
        integer, b : number) : number, number"]
    tests(commands, expected_lines, "test2")

def test3():
    expected_lines = [
        ["keyword", "local", True],
        ["keyword", "integer", True],
        ["id", "a", True],
        ["set", "(null)", True],
        ["number int", "5", True],
        ["add", "(null)", True],
        ["number int", "2", True],
        ["mul", "(null)", True],
        ["number int", "10", True],
        ["start bracket", "(null)", True],
        ["sub", "(null)", True],
        ["number int", "5", True],
        ["add", "(null)", True],
        ["number int", "2", True],
        ["sub", "(null)", True],
        ["number int", "44", True],
        ["add", "(null)", True],
        ["number int", "21", True],
        ["end bracket", "(null)", True],
        ["mul", "(null)", True],
        ["number int", "11", True]
    ]
    commands = [
        "local integer a = 5+2*10(-5+2-44+21)*11",
        "       local       integer       a         =      5        +       2      *     10       (      -     5        +   2      -     44       +      21        )       *      11",
        "local   integer   a    =   5   +   2   *   10  ( - 5 + 2 - 44   +  21 )  * 11",
        "local \
            integer \
            a            = \
            5 + 2 *  10 (       -5   +  2   -    44  +   21  )   *   \
            11",
        "\
            local \
                integer \
                    a \
                        = \
                            5\
                                +\
                                    2\
                                        *\
                                            10\
                                                (\
                                                    -\
                                                        5\
                                                            +\
                                                                2\
                                                                    -\
                                                                        44\
                                                                            +\
                                                                                21\
                                                                                    )\
                                                                                        *\
                                                                                            \
                                                                                            11",
        ]
    tests(commands, expected_lines, "test3")

def test4():
    expected_lines = [
        ["keyword", "local", True],
        ["keyword", "integer", True],
        ["id", "a", True],
        ["set", "(null)", True],
        ["number", "5.55", True],
        ["add", "(null)", True],
        ["number int", "2", True],
        ["mul", "(null)", True],
        ["number", "10e10", True],
        ["start bracket", "(null)", True],
        ["sub", "(null)", True],
        ["number", "5.2e-10", True],
        ["add", "(null)", True],
        ["number int", "2", True],
        ["sub", "(null)", True],
        ["number int", "44", True],
        ["add", "(null)", True],
        ["id", "e2", True],
        ["end bracket", "(null)", True],
        ["mul", "(null)", True],
        ["number int", "11", True]
    ]
    commands = [
        "local integer a = 5.55+2*10e10(-5.2e-10+2-44+e2)*11",
        "       local       integer       a         =      5.55        +       2      *     10e10       (      -     5.2e-10        +   2      -     44       +      e2        )       *      11",
        "local   integer   a    =   5.55   +   2   *   10e10  ( - 5.2e-10 + 2 - 44   +  e2 )  * 11",
        "local \
            integer \
            a            = \
            5.55 + 2 *  10e10 (       -5.2e-10   +  2   -    44  +   e2  )   *   \
            11",
        "\
            local \
                integer \
                    a \
                        = \
                            5.55\
                                +\
                                    2\
                                        *\
                                            10e10\
                                                (\
                                                    -\
                                                        5.2e-10\
                                                            +\
                                                                2\
                                                                    -\
                                                                        44\
                                                                            +\
                                                                                e2\
                                                                                    )\
                                                                                        *\
                                                                                            \
                                                                                            11",
        ]
    tests(commands, expected_lines, "test4")


test1()
test2()
test3()
test4()