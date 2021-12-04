-- Should be ERR [5, 14]

require "ifj21"

global foo :: function(integer, string, number) : number, string, integer
function fc (a : integer, b : number, c : string)
end

function foo(k : integer, l : string, m : number) : number, string, integer
    k = 99
    l = "ninety-nine"
    m = 0
    
    return m, l, k
end

function main() : integer, number
    local a : integer = 10
    local b : number = 5
    local c : string = "Ho Ho Ho!"

    a = 456
    
    if a > b then local
        fc( a, b, c)
    elseif a == 5 then
        a, b, c = 5, 5, "five"
    else
        a = b
    end

    local d : integer
    
    a, b, c = fc(a, b, c)

    if if a > b then
        fc( a, b, c)
    elseif a == 5 then
        a, b, c = 5, 5, "five"
    else
        a = b
    end

    local k : integer
    local l : string
    local m : number
    
    m, l, k = foo(k, l, m)

    return a, b
end
