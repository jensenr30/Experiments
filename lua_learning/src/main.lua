--                                                                              
local function main()
  require "polynomial"
  require "integrate"
  io.stdout:setvbuf('no')
  local a = {[0]=1, [1]=1, [2]=1}
  local start = -1
  local step = 0.001
  local stop = 1
  local x = start
  local function f(x) return poly_evaluate(a,x) end 
  local sum = integrate_1d(f, start, stop, step)
  print(sum)
end
main()
