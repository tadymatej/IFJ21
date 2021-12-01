-- Should be ERR [9, 20] - TODO PSA vraci semantickou chybu, je to asi syntakticka chyba

require "ifj21"

function main()
    local a : integer = 88.44

    --Možná to není syntaktická chyba.. Pošetřit
    a, b, c = a, b =
end

main()
