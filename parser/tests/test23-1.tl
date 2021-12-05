-- Should not be OK
-- Error on 14:11

require "ifj21"

function fc(a : integer, b : number, c : string)

end

function main() : integer, number
    local a : integer = 10
    local b : number = 5

    a, b, c = 456, 45, "Santa"

    if a > 0 then
        fc(a, b, c)
    end

    return 10, 5
end
