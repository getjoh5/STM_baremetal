target extended-remote localhost:2331
monitor reset
monitor halt

define flash
  dont-repeat
  monitor reset
  monitor halt
  load
  monitor reset
  monitor halt
end
