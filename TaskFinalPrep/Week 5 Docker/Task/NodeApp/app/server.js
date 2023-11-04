let express = require('express');
let path = require('path');
let fs = require('fs');
let MongoClient = require('mongodb').MongoClient;
let bodyParser = require('body-parser');
let app = express();
const cors = require("cors");
app.use(cors());

app.use(bodyParser.urlencoded({
    extended: true
}));
app.use(bodyParser.json());

app.get('/', function (req, res) {
    console.log("Rendering html template...");
    res.sendFile(path.join(__dirname, "index.html"));
});

app.get('/profile-picture', function (req, res) {
    console.log("Getting profile picture...");
    let img = fs.readFileSync(path.join(__dirname, "images/profile-1.jpeg"));
    res.writeHead(200, {'Content-Type': 'image/jpeg' });
    res.end(img, 'binary');
});

// use when starting application locally
let mongoUrlLocal = "mongodb://admin:password@localhost:27017";

// use when starting application as docker container
let mongoUrlDocker = "mongodb://admin:password@mongodb";

// pass these options to mongo client connect request to avoid DeprecationWarning for current Server Discovery and Monitoring engine
let mongoClientOptions = { useNewUrlParser: true, useUnifiedTopology: true };

// "user-account" in demo with docker. "my-db" in demo with docker-compose
let databaseName = "user-account";

app.post('/update-profile', function (req, res) {
    console.log("Updating profile picture on database...");
    let userObj = req.body;

    MongoClient.connect(mongoUrlLocal, mongoClientOptions, function (err, client) {
    if (err) throw err;
    console.log("MongoDB connection created successfuly...");
    let db = client.db(databaseName);
    userObj['userid'] = 1;

    let myquery = { userid: 1 };
    let newvalues = { $set: userObj };

    db.collection("users").updateOne(myquery, newvalues, {upsert: true}, function(err, res) {
        if (err) throw err;
        client.close();
    });

    });
    console.log("Record updated on MongoDB sucessfuly...");
    // Send response
    res.send(userObj);
});

app.get('/get-profile', function (req, res) {
    let response = {};
    // Connect to the db
    MongoClient.connect(mongoUrlLocal, mongoClientOptions, function (err, client) {
    if (err) throw err;

    let db = client.db(databaseName);

    let myquery = { userid: 1 };

    db.collection("users").findOne(myquery, function (err, result) {
        if (err) throw err;
        response = result;
        client.close();

        // Send response
        res.send(response ? response : {});
    });
    });
});

app.listen(3000, function () {
    console.log("App is ready and running on port 3000!");
});
