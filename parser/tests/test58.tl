-- Should be OK

require "ifj21"

function main()
    local a : integer = 10
    local b : number = 5

    if a > 3 then
        if a == 4 then
            a = a + 1
            
        else
            return
        end
    end 
    
    return
end
