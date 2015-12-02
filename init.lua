--===VAR===--
--GPIO Pin
--3 = GPIO 0
pin = 3
pulse = 0
flow = 0
flowAmount = 0
flowTime = tmr.time()
startTime = tmr.time()

serverIp = "192.168.4.1"
deviceId = 1

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

tmr.alarm(0, 2000, 1, function()
    if(wifi.sta.getip() ~= nil) then
        tmr.stop(0)
        print("Connected!")
        print("Client IP Address:", wifi.sta.getip())
      else
         print("Connecting...")
      end
end)

--===FLOW SENSOR===---
--set ping as interrupt
gpio.mode(pin, gpio.INT, gpio.PULLUP)

--set the function callback
gpio.trig(pin, "up", pulseUp)

--id, 1s, 1xrepeat, callback
tmr.alarm(1, 1000, 1, function()
    flow=pulse/5.5

    if (flow~=0) then
        if (flowAmount ~= 0) then
            flowTime = tmr.time()
        end

        flowAmount = flowAmount + flow
    end

    if (flow == 0 and flowAmount ~= 0) then
        print("Sending: time=" .. flowTime .. "&flow=" .. flowAmount .. "&device_id=" .. deviceId)
        cl=net.createConnection(net.TCP, false)
        cl:connect(80, serverIp)
        cl:send("time=" .. flowTime .. "&flow=" .. flowAmount .. "&device_id=" .. deviceId) 
        flowAmount = 0
        flowTime = 0
    end

    print("\nTime from start: " .. tmr.time()-startTime)
    print("l/m: " .. flow)

    --reset the pulse
    pulse = 0
end )

--This line is set to avoid hardware problem
--More: http://www.esp8266.com/viewtopic.php?f=18&t=5624
pwm.setup(2,50,512)
pwm.start(2)
