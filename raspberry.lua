--===INIT===--

--set ESP8266 as Station
wifi.setmode(wifi.STATIONAP);
wifi.ap.config({
    ssid = "WIFI_FLOW_SENSOR",
    pwd = "wMm2XKBgdYdeH2G2vGwM"
});
print("Server IP Address:", wifi.ap.getip())

sv = net.createServer(net.TCP) 
sv:listen(80, function(conn)
    conn:on("receive", function(conn, receivedData) 
        print("Received Data: " .. receivedData)  
        anotherConn = net.createConnection(net.TCP, false)
        anotherConn:connect(80,"127.0.0.1:3000")
        anotherConn:send("GET /" .. receivedData .."")       
    end) 
    conn:on("sent", function(conn) 
      collectgarbage()
    end)
end)