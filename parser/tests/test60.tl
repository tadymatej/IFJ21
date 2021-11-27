-- Should be OK

require "ifj21"
function concat (x : string, y : string) : string, integer
  return x .. y, 0 end
function main()
  local x : string = "ahoj"
  local y : string = "svete"
  local ret: integer
  x, ret = concat(x, y)
end

main()
