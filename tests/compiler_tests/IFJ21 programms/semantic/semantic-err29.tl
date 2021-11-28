require "ifj21"

global foo : function(integer)

function foo(a:integer)
	local a : integer = 10
end

function main()
    local a : integer = 10
    local b : integer
    local c : integer
    a,b = foo(a)
end

main()
