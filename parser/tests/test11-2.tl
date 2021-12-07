-- Should be OK

require "ifj21"

function foo(a : integer) : integer
    return a
end

function main()
    local a : integer = nil
    local d : integer = foo(a)

end

main()
