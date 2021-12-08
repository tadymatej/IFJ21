--[[
    Spočítá součet dvou čísel
    a První číslo, které se sčítá
    b Druhé číslo, které se sčítá
    Vrací výsledek
  ]]
global function add(a : number, b : number) : number
    local res : number = a + b
    return res 
end

--[[
    Spočítá rozdíl dvou čísel
    a číslo, od kterého se odčítá
    b číslo, které se odčítá
    Vrací výsledek
  ]]
global function sub(a : number, b : number) : number
    local res : number = a - b
    return res
end

-- Spočte násobení dvou čísel pomocí sčítání
global function mul(a : number, b : integer) : number
    local res : number = 0.0
    while b > 0 do
        res = add(res, a)
        b = b - 1
    end
    return res
end

global function div(a : number, b : number) : number
    if b == 0 then
        return nil
    else
        return a / b 
    end
end

function main()
    --Testovací funkce, vypisuje průběžně náhodné výsledky
    local res : number
    local a : integer
    local b : number
    a = 1
    b = 2.5
    res = add(a, b)
    print(res)
    
    res = sub(res, b)
    print(res)

    a, b = 10, 20
    res = mul(b, a)
    print(res)
    a, b = 10, 20e2
    res = div(b, a)
    print(res)

end
main()
