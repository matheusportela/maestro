var http = require('http');
var express = require('express');
var router = express.Router();
var Camera = require('gopro').Camera;
var cam = new Camera('10.5.5.9', 'goprohero');
var fs = require('fs');



/* GET home page. */
router.get('/', function(req, res) {


    //io.on('connection', function(socket) {
    //    socket.emit('gopro', {hello: 'world'});
    //});


    cam.directory(function(data, err){
        dirData = fs.readdirSync(directoryData);
        console.log(dirData);
        console.log('jh');
    });

    res.render('index', { title: 'data' });
});


module.exports = router;
