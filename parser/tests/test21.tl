-- Should be OK - Semantic fix

require "ifj21"

function fc(a : integer, b : number, c : string)

end

function main() : integer, number
    local a : integer = 10
    local b : number = 5
    local c : string = "Ho Ho Ho!"

    if a > b then
        fc(a, b, c)
    end

    return a, b
end
