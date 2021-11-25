-- Hello World example in IFJ21
-- run it on Merlin by: tl run hello.tl

require "ifj21"

global fc : function() : integer

function main() : integer
    local a : integer = 5

    return fc()
end

function fc() : integer
    local b : integer = 0
    return 10
end

main()
