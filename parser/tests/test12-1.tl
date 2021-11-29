-- Should be OK

require "ifj21"

function main()
    local a : integer = 3

    while a < 5 do
        a = a + 1
        if a == 4 then
            a = a + 2
        else
            a = a - 1
        end
    end

    local b : integer = 5
end

main()
