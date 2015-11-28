var _ = require('underscore');

//sqlite
var sqliteKnex = require('knex')({
    client: 'sqlite3',
    connection: {
        filename: "../db/sync.db"
    }
});

var sqlLite = require('bookshelf')(sqliteKnex);

var Flow = sqlLite.Model.extend({
    tableName: 'flow'
});

//mysql
var connection = require('../config/config.json');
var mysqlKnex = require('knex')({
    client: 'mysql',
    connection: connection
});

var mysql = require('bookshelf')(mysqlKnex);

var MFlow = mysql.Model.extend({
    tableName: 'flow'
});


//main logic
console.log("Getting all flows from SQLITE...");
Flow.fetchAll().then(function (flows) {
    var rows = flows.toJSON();
    var size = rows.length;
    console.log("Collected:", size);

    //exiting
    if (size < 1) {
        finalize();
    }

    //check on MySQL
    var flowsToBeDeleted = [];
    var ids = _.pluck(rows, 'id');
    MFlow.query({where: ['integration_id', 'in', ids]}).fetchAll().then(function (mysqlRows) {
        mysqlRows = mysqlRows.toJSON();

        _.each(mysqlRows, function (mysqlRow) {
            for (var i = 0; i < size; i++) {
                var sqliteRow = rows[i];
                if (sqliteRow && sqliteRow.id == mysqlRow.integration_id) {
                    rows.splice(i, 1);
                    flowsToBeDeleted.push(sqliteRow);
                }
            };
        });

        insertOnMySQL(rows, flowsToBeDeleted);
    });
});

/**
 * Insert on MySQL
 *
 * @param rows
 * @param flowsToBeDeleted
 */
function insertOnMySQL (rows, flowsToBeDeleted) {
    if (rows.length < 1) {
        deleteFromSqlite(flowsToBeDeleted);
        return;
    }

    console.log("Inserting on MySQL...");
    var amountSaved = 0;

    _.each(rows, function (row) {
        var record = {
            device_id: row.device_id,
            flow: row.flow,
            time: row.time,
            integration_id: row.id,
            date: row.date
        };

        console.log("Trying to save record", row.id);
        new MFlow(record).save().then(function(model) {
            console.log(row.id, "Saved");

            flowsToBeDeleted.push(row);
            amountSaved++;

            if (amountSaved == rows.length) {
                deleteFromSqlite(flowsToBeDeleted);
            }
        });
    });
}

/**
 * delete from SQLite
 *
 * @param flowsToBeDeleted
 */
function deleteFromSqlite (flowsToBeDeleted) {
    console.log("Removing from sqlite...");

    var ids = _.pluck(flowsToBeDeleted, 'id');
    var query = sqliteKnex("flow")
        .del()
        .whereIn('id', ids);

    console.log("Query", query.toSQL());
    query.nodeify(function (err) {
        if(err) throw err;

        console.log("Records removed.");

        finalize();
    });
}

/**
 * close connections and kill the process
 */
function finalize () {
    console.log("Done.");
    process.exit();
}