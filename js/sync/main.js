var fs = require("fs");
var process = require("process");
var pg = require('pg');
var sqlite3 = require("sqlite3").verbose();

//sqlite
var dbFile = "../db/sync.db";
var dbExists = fs.existsSync(dbFile);

if(!dbExists) {
    console.log("Creating DB file.");
    fs.openSync(dbFile, "w");
}

var sqliteDb = new sqlite3.Database(dbFile);

// Database initialization
sqliteDb.serialize(function() {
  if(!dbExists) {
      sqliteDb.run('CREATE TABLE "flow" ('+
      '   "id" INTEGER PRIMARY KEY AUTOINCREMENT,'+
      '   "device_id" INTEGER NOT NULL,'+
      '   "flow" FLOAT NOT NULL,'+
      '   "time" FLOAT NOT NULL'+
      ')');
  }
});

//postgres
var config = require('../config/config.json');
var conString = "postgres://" + config.username + ":" + config.password + "@" + config.ip + "/" + config.database;
var pgClient = new pg.Client(conString);


/**
 * Create Pg SQL with all IN ids
 *
 * @param rows
 * @returns {string}
 */
function createPgSql (rows) {
    for (var i = 0; i<rows.length; i++) {
        var row = rows[i];
        pgSql = pgSql + row.id + ",";
    }
    pgSql = pgSql.substr(0,pgSql.length-1) + ")";

    return pgSql;
}

/**
 * Insert on PG
 *
 * @param rows
 * @param flowsToBeDeleted
 */
function insertOnPostgres (rows, flowsToBeDeleted) {
    console.log("Inserting on postgres...");

    for (var i = 0; i<rows.length; i++) {
        var row = rows[i];

        console.log("Insert " + row.id);
        var query = pgClient.query("INSERT INTO flow (device_id, flow, time, integration_id, date) values ($1, $2, $3, $4, NOW())", [
            row.device_id,
            row.flow,
            row.time,
            row.id
        ]);

        query.on('error', function(err) {
            console.log('Query error: ' + err);
        });
    }

    deleteFromSqlite(flowsToBeDeleted);
}

/**
 * delete from SQLite
 *
 * @param flowsToBeDeleted
 */
function deleteFromSqlite (flowsToBeDeleted) {
    console.log("Removing from sqlite...");

    for (var i = 0; i<flowsToBeDeleted.length; i++) {
        var row = flowsToBeDeleted[i];

        console.log("Removing " + row.id);
        sqliteDb.exec("DELETE FROM flow WHERE id = " + row.id);
    }

    console.log("Done.");
    closeConnections();
    process.exit();
}

/**
 * Close pg connection
 */
function closeConnections () {
    //pgClient.close();
    sqliteDb.close();
}

//LOGIC START
//fetching everything from sqllite and insert on pg
console.log("Starting...");
console.log("Connecting in: " + conString);
console.log("Connecting to PG...");

pgClient.connect();

console.log("Getting all flows from SQLITE...");
var pgSql = "SELECT * FROM flow WHERE integration_id IN (";

sqliteDb.all("SELECT * FROM flow", function(err, rows) {
    var size = rows.length;
    console.log("Collected:" + size);

    if (size < 1) {
        console.log("Done.");
        closeConnections();
        process.exit();
    }

    //flows to be deleted
    var flowsToBeDeleted = [];

    //creating the sql
    var pgSql = createPgSql(rows);

    //check on postgres
    var query = pgClient.query(pgSql);

    // Stream results back one row at a time
    query.on('row', function(pgRow, result) {
        for (var i = 0; i<rows.length; i++) {
            var sqlLiteRow = rows[i];
            if (sqlLiteRow.id == pgRow.integration_id) {
                rows.splice(i, 1);
                flowsToBeDeleted.push(sqlLiteRow);
                continue;
            }
        }
    });

    query.on('end', function () {
        insertOnPostgres(rows, flowsToBeDeleted);
    });
});