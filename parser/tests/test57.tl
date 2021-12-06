-- Should be OK

require "ifj21"

function main():integer, number
    local a : integer = 10
    local b : number = 5

    if a > 3 then
        if a == 4 then
            a = a + 1
            return a,b
        elseif a == 5 then
            a = 3
        end
    end 
    
    return a,b
end
