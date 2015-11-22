--incrementa o pulso
function pulseUp(level)
    print("Pulse Up!")
    pulse = pulse +1
end

function init(pin)
    pulse = 0
    flow = 0

    --define pin as interrupt
    gpio.mode(pin, gpio.INT,gpio.PULLUP)

    --trigger to dispatch when there is something on the pulse
    gpio.trig(pin, "up", pulseUp)
end

--init function
init(3)

--avoid crashes
pwm.setup(2,50,512)
pwm.start(2)