-- Should be OK

require "ifj21"

function main()
    local a : integer
    local b : integer
    local c : integer

    a, b, c = 0, 1, 2

    if a > 5 then
        b = 6
    elseif a < 4 then
        c = 7
    else
        a = 0
    end

    a = 0

end

main()
