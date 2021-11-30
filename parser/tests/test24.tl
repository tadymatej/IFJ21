-- Should be OK - Semantic fix

require "ifj21"

global foo : function( integer, string, number)

function fc(a : integer, b : number, c : string)

end

function main() : integer, number
    local a : integer = 10
    local b : number = 5

    a = 456
    
    if a > b then
        fc(a, b, c)
    end

    return 0, 0
end
