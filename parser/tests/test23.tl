-- Hello World example in IFJ21
-- run it on Merlin by: tl run hello.tl

require "ifj21"

function fc(a : integer, b : number, c : string)

end

function main() : integer, number
    local a : integer = 10
    local b : number = 5
    local c : string = "Ho Ho Ho!"

    a, b, c = 456, 45, "Santa"
    
    if a > b then
        fc(a, b, c)
    end

    return a, b
end
