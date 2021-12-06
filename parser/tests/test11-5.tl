-- Should be OK

require "ifj21"

function foo(a : string, b : string) : string
    return a .. b
end

function main()
    
    local d : string = foo("We wish you Merry Christmas", "and Happy New Year")

end

main()
