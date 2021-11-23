function factorial(a : integer) : integer
    local fakt : integer = 1
    while a > 1 do
        fakt = fakt * a
        a = a - 1
    end 
    return fakt
end

function main()
    -- Vypíše prvních faktoriál čísel <0, 10>
    local a : integer = 0
    while a < 11 do
        local fact = factorial(a)
        print(fact)
        a = a + 1
    end
end

main()