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
--starting the wifi and connect to the server
wifi.sta.disconnect()
wifi.setmode(wifi.STATION) 
wifi.sta.config("WIFI_FLOW_SENSOR","wMm2XKBgdYdeH2G2vGwM")
wifi.sta.connect() 
print("Connecting...")

--===FLOW SENSOR===---
--set ping as interrupt
gpio.mode(pin, gpio.INT, gpio.PULLUP)

--set the function callback
gpio.trig(pin, "up", pulseUp)

--trying to connect
tmr.alarm(1, 2000, 1, function()
    if(wifi.sta.getip()~=nil) then
        tmr.stop(1)
        print("Connected!")
        cl = net.createConnection(net.TCP, 0)
        cl:connect(80, "192.168.4.1")

        --id, 1s, 1xrepeat, callback
        tmr.alarm(2, 1000, 1, function()
            flow=pulse/5.5

            if (flow~=0) then

            end

            print("\nTime from start: " .. tmr.time()-startTime)
            print("l/m: " .. flow)

            --reset the pulse
            pulse = 0
        end )
    else
        print("Connecting...")
    end
end)

--This line is set to avoid hardware problem
--More: http://www.esp8266.com/viewtopic.php?f=18&t=5624
pwm.setup(2,50,512)
pwm.start(2)