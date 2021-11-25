-- Hello World example in IFJ21
-- run it on Merlin by: tl run hello.tl

require "ifj21"

function fc(a : integer, b : number)

end

function main() : integer, number
    local a : integer = 10
    local b : number = 5

    if a > b then
        fc(a, b)
    end

    return 10, 10
end
