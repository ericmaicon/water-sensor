--===VAR===--
--GPIO Pin
--3 = GPIO 0
pin = 3
pulse = 0
flow = 0
startTime = tmr.time()

--===FUNCTIONS===--
--Function to count pulse
function pulseUp(level)
    pulse = pulse + 1  
end


--===INIT===--
--set ping as interrupt
gpio.mode(pin, gpio.INT, gpio.PULLUP)

--set the function callback
gpio.trig(pin, "up", pulseUp)

--id, 1s, 1xrepeat, callback
tmr.alarm(0, 1000, 1, function()
    flow=pulse/5.5

    print("\nTime from start: " .. tmr.time()-startTime)
    print("l/m: " .. flow)

    --reset the pulse
    pulse = 0
end )

--This line is set to avoid hardware problem
--More: http://www.esp8266.com/viewtopic.php?f=18&t=5624
pwm.setup(2,50,512)
pwm.start(2)