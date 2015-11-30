var express = require('express');
var sqlite3 = require("sqlite3").verbose();

//express
var app = express();

//sqlite
var dbFile = "../db/sync.db";
var db = new sqlite3.Database(dbFile);

//Route
app.get('/', function (req, res) {
    var params = req.query;
    var device_id = params.device_id;
    var flow = params.flow;
    var time = params.time;

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
    res.send("");
});

//Server
var server = app.listen(3000, function () {
    var host = server.address().address;
    var port = server.address().port;

    console.log('App listening at http://%s:%s', host, port);
});