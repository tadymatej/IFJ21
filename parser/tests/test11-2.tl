-- Hello World example in IFJ21
-- run it on Merlin by: tl run hello.tl

require "ifj21"

function foo(a : integer) : integer
    return a
end

function main()
    local a : integer
    local b : integer
    local c : integer

    a, b, c = 0, 1, 2

    if a > 5 then
        a = 6
    elseif a < 4 then
        a = 7
    else
        a = 0
    end

    a = 0

    local d : integer = foo(a)

end

main()
