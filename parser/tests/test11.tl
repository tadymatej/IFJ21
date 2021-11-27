-- Should be OK

require "ifj21"

function main() : integer
    local a : integer
    if a > 5 then
        a = 6
    elseif a < 4 then
        a = 7
    else
        a = 0
    end

    return 10

end

main()
