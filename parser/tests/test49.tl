-- Should be OK

require "ifj21"

function fc(a : integer, b : number)

end

function main() : integer, number
    local a : integer = 10
    local b : number = 5

    if a > 3 then
        fc(a, b)
        if a > 3 then
            fc(a, b)  
        elseif a < 3 then
            a = 3
        end
    end

    return 10, 10
end
