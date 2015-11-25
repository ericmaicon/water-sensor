var fs = require("fs");
var express = require('express');
var sqlite3 = require("sqlite3").verbose();

//express
var app = express();

//sqlite
var dbFile = "../db/sync.db";
var dbExists = fs.existsSync(dbFile);

if(!dbExists) {
    console.log("Creating DB file.");
    fs.openSync(dbFile, "w");
}

var db = new sqlite3.Database(dbFile);

// Database initialization
db.serialize(function() {
    if(!dbExists) {
        db.run('CREATE TABLE "flow" ('+
        '   "id" INTEGER PRIMARY KEY AUTOINCREMENT,'+
        '   "device_id" INTEGER NOT NULL,'+
        '   "flow" FLOAT NOT NULL,'+
        '   "time" FLOAT NOT NULL'+
        ')');
    }
});

//Route
app.get('/', function (req, res) {
    var params = req.query;
    var device_id = params.device_id;
    var flow = params.flow;
    var time = params.time;

    if (device_id && flow && time) {
        var stmt = db.prepare("INSERT INTO 'flow' (device_id, flow, time) VALUES (?, ?, ?)");
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