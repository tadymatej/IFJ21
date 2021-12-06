-- Should be OK

require "ifj21"

function foo(a : number) : number
    return a
end

function main()
    
    local d : number = foo(0.999e1256)

end

main()
