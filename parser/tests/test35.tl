-- Should be OK - Semantic fix

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
