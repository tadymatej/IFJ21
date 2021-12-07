-- Should be OK

require "ifj21"

global fc : function () : integer

function fc() : integer
    local a : integer

    a=5
    return a
end

function main() : integer, integer
    
    return 5, fc()
end
