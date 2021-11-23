global function myVar(x: string) : string
    return "Toto je variable x: " .. x
end

global function len(x : string) : integer 
    return #x
end

function foo(x : string, a : integer) : string, integer
    a = a + 5
    return x, a
end

function main() 
    local x : string --Lokální proměnná
    x = --[[Deklarace hodnoty proměnné na "Matěj"]] "Matěj"
    print(myVar(x))
    print(x)
    print("Délka řetězce x: " .. len(x))
    x = myVar(x)
    print(x)
    local a : integer
    x, a = foo(x, 20)
    print("První return:", x, "Druhý return:", a)
    x, a = foo(x, a)
    print("První return: ", x, "Druhý return: ", a)


end
main()