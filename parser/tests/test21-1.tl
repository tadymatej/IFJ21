-- Should be OK

require "ifj21"

function fc(a : integer, b : number, c : string)

end

function main() : integer, number
    local a : integer = 10
    local b : number = 5
    local c : string = "Ho Ho Ho!"

    if a > 100 then
        fc(a, b, c)
    end

    return 5, 5
end
