var http = require('http');
var express = require('express');
var router = express.Router();
var Camera = require('gopro').Camera;
var cam = new Camera('10.5.5.9', 'goprohero');
var fs = require('fs');
var com = require("serialport");



/* GET home page. */
router.get('/', function(req, res) {


    //io.on('connection', function(socket) {
    //    socket.emit('gopro', {hello: 'world'});
    //});

  
    /*cam.directory(function(data, err){
        dirData = fs.readdirSync(directoryData);
        console.log(dirData);
        console.log('jh');
    });*/

	
	var serialPort = new com.SerialPort("PORTA", {
	    baudrate: 9600,
	    parser: com.parsers.readline('\r\n')
	  });

	serialPort.on('open',function() {
	  console.log('Port open');
	});

	serialPort.on('data', function(data) {
	  console.log(data);
	  if(data=='start')
	  	cam.startCapture();
	  else if(data=='stop')
	  	cam.stopCapture();
	});


	
	

    res.render('index', { title: 'Maestro' });
});


module.exports = router;
