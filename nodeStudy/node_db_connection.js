// node_db_connection.js

const mysql = require('mysql')

const conn = {
	host : 'localhost',
	// port : '3306',
	user : 'testuser',
	password : '12341234',
	database : 'test'
}


var connection = mysql.createConnection(conn)
connection.connect()

// var testQuery = "INSERT INTO 'student'('name','password') VALUES ('test','test')"
var testQuery = "INSERT INTO student(name) VALUES ('park')"
// var testQuery = "select * from student"

connection.query(testQuery, function(err, results, fields){
	if(err){
		console.log(err);
	}
	console.log(results)
})

testQuery = "select * from student"

connection.query(testQuery, function(err, results, fields){
	if(err){
		console.log(err)
	}
	console.log(results)
})

connection.end()