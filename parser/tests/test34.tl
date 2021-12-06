--Should be OK

require "ifj21"

function foo(a : integer) : integer
    return a
end

function main() : integer
    local a : integer = 5

    local b : number = foo(a)

    a, b = 5, 88

end

main()
