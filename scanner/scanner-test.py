import os
from pathlib import Path
curdir = Path(__file__).parent.absolute()
os.chdir(curdir)
os.system("make")
os.system("clear")

print_success = "typ: {} || hodnota: {}"
print_error = "Lexikalni chyba na radku: {} a sloupci: {}\n"

def test(command, expected_lines, testname):
    res = os.popen('echo "{}" | ./scanner 0'.format(command))
    #print(os.popen('echo "{}"'.format(command)).read())
    i = 0
    len_expected_lines = len(expected_lines)
    for line in res.readlines():
        line = line.strip()
        if i < len_expected_lines:  #Osetreni sahani za hranice
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
    #tests(commands, expected_lines, "test1")

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
        "global function ahoj(a : \ninteger, b : number) : number, number"]
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
        "local \ninteger \n            a            = \n            5 + 2 *  10 (       -5   +  2   -    44  +   21  )   *   \n            11",
        "\n            local \n                integer \n                    a \n                        = \n                            5\n                                +\n                                    2\
                                        \n*\n                                            10\n                                                (\n                                                    -\
                                                        \n5\
                                                            \n+\
                                                                \n2\
                                                                    \n-\
                                                                        \n44\
                                                                            \n+\
                                                                                \n21\
                                                                                    \n)\
                                                                                        \n*\
                                                                                            \n\
                                                                                            \n11",
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
        "local \n integer \na            = \n5.55 + 2 *  10e10 (       -5.2e-10   +  2   -    44  +   e2  )   *   \n11",
        "\nlocal \ninteger \na \n= \n5.55\n+\n2\n*\n10e10\n(\n-\n5.2e-10\n+\n2\n-\n44\n+\ne2\n)\n*\n\n11",
        ]
    tests(commands, expected_lines, "test4")


def test5():
    expected_lines = [
        ["1", "1", False],
        ["number int", "55", True]
    ]
    commands = [
        "$ 55",
        "$ \
            55",
        "$  --[[]] 55",
        "$  --[[\
            \
            ]] 55"]
    tests(commands, expected_lines, "test5")

def test6():
    expected_lines = [
        ["1", "9", False],
        ["number int", "55", True]
    ]
    commands = [
        "  --[[]]$ 55"
    ]
    tests(commands, expected_lines, "test6")

def test7():
    expected_lines = [
        ["5", "3", False],
        ["number int", "55", True]
    ]
    commands = [
        "  --[[[[\n\n]\n\n]]$ 55"
    ]
    tests(commands, expected_lines, "test7")


def test8():
    expected_lines = [
        ["5", "4", False],
        ["number int", "55", True]
    ]
    commands = [
        "\n\n\n\n   $ 55"
    ]
    tests(commands, expected_lines, "test8")

def test9():
    expected_lines = [
        ["5", "9", False],
        ["number int", "55", True]
    ]
    commands = [
        "  --[[[[\n\n]\n\n]]--[[]]$ 55"
    ]
    tests(commands, expected_lines, "test9")

def test10():
    expected_lines = [
        ["7", "5", False],
        ["number int", "55", True]
    ]
    commands = [
        "  --[[[[\n\n]\n\n]]--[[]]--[[\n\n  ]]$ 55"
    ]
    tests(commands, expected_lines, "test10")

def test11():
    expected_lines = [
        ["id", "a", True],
        ["8", "5", False],
        ["number int", "55", True]
    ]
    commands = [
        "a\n  --[[[[\n\n]\n\n]]--[[]]--[[\n\n  ]]$ 55"
    ]
    tests(commands, expected_lines, "test11")

def test12():
    expected_lines = [
        ["keyword", "function", True],
        ["id_f", "hlavni_program", True],
        ["end bracket", "(null)", True],
        ["id_f", "write", True],
        ["string", '"Hello from IFJ21"', True],
        ["comma", "(null)", True],
        ["string", r'"\n"', True],
        ["end bracket", "(null)", True],
        ["keyword", "end", True],
        ["id_f", "hlavni_program", True],
        ["end bracket", "(null)", True]
    ]
    commands = [
        r"function hlavni_program()\n    write(\"Hello from IFJ21\", \"\\\n\")\nend\nhlavni_program()"]
    tests(commands, expected_lines, "test12")

def test13():
    expected_lines = [
        ["id_f", "write", True],
        ["string", r'"Hello from IFJ21\n"', True],
        ["end bracket", "(null)", True]
    ]
    commands = [
        r"write(\"Hello from IFJ21\\\n\")"]
    tests(commands, expected_lines, "test13")

def test14():
    expected_lines = [
        ["keyword", "function", True],
        ["id_f", "main", True],
        ["end bracket", "(null)", True],
        ["keyword", "local", True],
        ["id", "a", True],
        ["colon - dvojtecka", "(null)", True],
        ["keyword", "integer", True],
        ["set", "(null)", True],
        ["null", "nil", True],
        ["keyword", "local", True],
        ["id", "vysl", True],
        ["colon - dvojtecka", "(null)", True],
        ["keyword", "integer", True],
        ["id_f", "write", True],
        ["string", r'"Zadejte cislo pro vypocet faktorialu\n"', True],
        ["end bracket", "(null)", True],
        ["id", "a", True],
        ["set", "(null)", True],
        ["id_f", "readi", True],
        ["end bracket", "(null)", True],
        ["keyword", "if", True],
        ["id", "a", True],
        ["equal", "(null)", True],
        ["null", "nil", True],
        ["keyword", "then", True],
        ["id_f", "write", True],
        ["string", r'"a je nil\n"', True],
        ["end bracket", "(null)", True],
        ["keyword", "return", True],
        ["keyword", "else", True],
        ["keyword", "end", True],
        ["keyword", "if", True],
        ["id", "a", True],
        ["less", "(null)", True],
        ["number int", "0", True],
        ["keyword", "then", True],
        ["id_f", "write", True],
        ["string", r'"Faktorial nelze spocitat\n"', True],
        ["end bracket", "(null)", True],
        ["keyword", "else", True],
        ["id", "vysl", True],
        ["set", "(null)", True],
        ["number int", "1", True],
        ["keyword", "while", True],
        ["id", "a", True],
        ["greater", "(null)", True],
        ["number int", "0", True],
        ["keyword", "do", True],
        ["id", "vysl", True],
        ["set", "(null)", True],
        ["id", "vysl", True],
        ["mul", "(null)", True],
        ["id", "a", True],
        ["id", "a", True],
        ["set", "(null)", True],
        ["id", "a", True],
        ["sub", "(null)", True],
        ["number int", "1", True],
        ["keyword", "end", True],
        ["id_f", "write", True],
        ["string", r'"Vysledek je: "', True],
        ["comma", "(null)", True],
        ["id", "vysl", True],
        ["comma", "(null)", True],
        ["string", r'"\n"', True],
        ["end bracket", "(null)", True],
        ["keyword", "end", True],
        ["keyword", "end", True],
        ["id_f", "main", True],
        ["end bracket", "(null)", True],
    ]
    commands = [
        r"""function main()
            local a : integer = nil
            local vysl : integer
            write(\"Zadejte cislo pro vypocet faktorialu\\\n\")
            a = readi()
            if a == nil then
                write(\"a je nil\\\n\")
                return else end
            if a < 0 then
                write(\"Faktorial nelze spocitat\\\n\")
            else 
                vysl = 1
                while a > 0 do
                    vysl = vysl * a
                    a = a - 1
                end
                write(\"Vysledek je: \", vysl, \"\\\n\")
            end
        end

        main()
        """]
    tests(commands, expected_lines, "test14")

def test15():
    expected_lines = [
        ["keyword", "function", True],
        ["id_f", "whitespaces", True],
        ["end bracket", "(null)", True],
        ["keyword", "local", True],
        ["id", "s", True],
        ["colon - dvojtecka", "(null)", True],
        ["keyword", "string", True],
        ["set", "(null)", True],
        ["string", r'"\t"', True],   ##Blbě se zotavuji z chyby pokud escape je špatně (\x35A)
        ["id_f", "write", True],
        ["id", "s", True],
        ["comma", "(null)", True],
        ["string", r'"\n"', True],
        ["end bracket", "(null)", True],
        ["id", "s", True],
        ["set", "(null)", True],
        ["string", r'"a\255b"', True],
        ["id_f", "write", True],
        ["id", "s", True],
        ["comma", "(null)", True],
        ["string", r'"\n"', True],
        ["end bracket", "(null)", True],
        ["keyword", "local", True],
        ["id", "x", True],
        ["colon - dvojtecka", "(null)", True],
        ["keyword", "integer", True],
        ["set", "(null)", True],
        ["number int", "0", True],
        ["sub", "(null)", True],
        ["number int", "1", True],
        ["id_f", "write", True],
        ["id", "x", True],
        ["end bracket", "(null)", True],
        ["keyword", "end", True],
        ["id_f", "whitespaces", True],
        ["end bracket", "(null)", True],
    ]
    commands = [
        r"""

            function whitespaces
            ()
            local
            s
            :
            string
            =
            \"\\\t\"write(s, \"\\\n\")

            s = \"a\\\255b\"
            write(s
            ,
            \"\\\n\")local x:integer=0
            -
            1write(x)
            end whitespaces()
        """
    ]
    #print(os.system('echo "{}"'.format(commands[0])))
    tests(commands, expected_lines, "test15")

def test16():
    expected_lines = [
        ["keyword", "require", True],
        ["string", r'"ifj21"', True],
        ["keyword", "function", True],
        ["id_f", "main", True],
        ["end bracket", "(null)", True],
        ["keyword", "end", True]
    ]
    commands = [
        r"""
        -- Hello World example in IFJ21
        -- run it on Merlin by: tl run hello.tl

        require \"ifj21\"

        function main()
        end
        """,]
    tests(commands, expected_lines, "test16")



test1()

test2()
test3()
test4()

test5()
test6()
test7()
test8()
test9()
test10()
test11()
test12()
test13()

test14()

test15()
test16()

