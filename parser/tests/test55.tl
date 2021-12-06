-- Should be OK

require "ifj21"

function main()
    local a : integer = 10
    local b : number = 5

    if a > 3 then
        if a == 4 then
            a = a + 1
        elseif a == 5 then
            a = 3
        end
    end

    return 
    
    a, b = 10, 0.555555555e10256655

end
