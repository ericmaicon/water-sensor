//sqlite
var sqlite3 = require("sqlite3").verbose();
var dbFile = "../db/sync.db";
var db = new sqlite3.Database(dbFile);

//serial
var SerialPort = require("serialport").SerialPort;
var serialPort = new SerialPort("/dev/ttyAMA0", {
  baudrate: 59600
});

serialPort.on("open", function () {
    console.log('open');
    serialPort.on('data', function(data) {
        console.log('data received: ' + data);
        console.log('data received: ' + JSON.parse(data));
        // var params = req.query;
        // var device_id = params.device_id;
        // var flow = params.flow;
        // var time = params.time;

        // if (device_id && flow && time) {
        //     var stmt = db.prepare("INSERT INTO 'flow' (device_id, flow, time, date) VALUES (?, ?, ?, (DATETIME('now')))");
        //     stmt.run({
        //         1: device_id,
        //         2: flow,
        //         3: time
        //     });
        //     stmt.finalize();
        //     console.log("Device: " + device_id + ", Flow: " + flow + ", Time: " + time + " saved.");
        // }
    });
});
