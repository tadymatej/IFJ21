require "ifj21"

global foo : function(integer)

function foo(a:integer)
	local b : integer = 10
	local c : integer = b
	local d : string = "aaa"
	return b,c,d
end

function main()
    local a : integer = 10
    local b : integer
    local c : integer
    a,b = foo(a)
end

main()
