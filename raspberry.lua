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
        print(receivedData)  
        
        anotherConn = net.createConnection(net.TCP, false)
        anotherConn:connect(3000, "192.168.25.4")
        anotherConn:send("GET /?" .. receivedData .."")       
    end) 
    conn:on("sent", function(conn) 
        print("Data sent")
        collectgarbage()
    end)
end)
