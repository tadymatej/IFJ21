require "ifj21"

function main() : integer
    local a : integer = 5

    local b : integer = foo(a)

    a, b = 5, 88
end

main()
