-- Should be OK

require "ifj21"

global foo : function(integer, string, number) : number, string, integer
function fc (a : integer, b : number, c : string)

end

function main() : integer, number
    local a : integer = 10
    local b : number = 5
    local c : string = "Ho Ho Ho!"
    
    if a > 5 then
        fc(a, b, c)
    elseif a == 5 then
        a, b, c = 5, 5, "five"
    else
        a = 0
    end

    local d : integer
    
    fc()
    fc()
    fc()

    if a < 5 then
        fc(a, b, c)
    elseif a == 5 then
        a, b, c = 5, 5, "five"
    else
        a = 0
    end

    a = 456
    --local d : integer
    fc()
    fc()
    fc()

    return 0, 0
end
