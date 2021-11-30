-- Should be OK

require "ifj21"

function fc(a : integer, b : number, c : string)

end

function main() : integer, number
    local a : integer = 1001
    local b : number = 5
    local c : string = "Ho Ho Ho!"

    -- chyba zde
    a = 456
    
    if a > 1000 then
        fc( a, b, c)
    end

    return 10, 10
    
end
