-- Should be OK

require "ifj21"

global foo : function( integer, string, number)

function fc(a : integer, b : number, c : string) : string
    c = "Hello World!"

    return c
end

function main() : integer, number
    local a : integer = 10
    local b : number = 5
    local c : string

    a = 456
    
    if a > b then
        c = fc(a, b, c)
    end

    return 0, 0
end
