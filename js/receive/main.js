//sqlite
var sqlite3 = require("sqlite3").verbose();
var dbFile = "../db/sync.db";
var db = new sqlite3.Database(dbFile);

//serial
var serialPort = require("serialport");
var SerialPort = serialPort.SerialPort;
var sp = new SerialPort("/dev/ttyAMA0", {
    baudrate: 9600,
    parser: serialPort.parsers.readline("\n")
});

sp.on("open", function () {
    console.log('Serial opened');
    sp.on('data', function(data) {
	console.log(data);
	var params = data.split(';');
	var time = params[0];
	var flow = params[1];
        var device_id = params[2];

        if (device_id && flow && time) {
            var stmt = db.prepare("INSERT INTO 'flow' (device_id, flow, time, date) VALUES (?, ?, ?, (DATETIME('now')))");
            stmt.run({
                1: device_id,
                2: flow,
                3: time
            });
            stmt.finalize();
            console.log("Device: " + device_id + ", Flow: " + flow + ", Time: " + time + " saved.");
        }
    });
});
