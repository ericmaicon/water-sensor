var fs = require("fs");
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
        '   "time" FLOAT NOT NULL,'+
        '   "date" DATETIME NOT NULL'+
        ')');
    }
});