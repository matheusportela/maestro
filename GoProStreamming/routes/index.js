var http = require('http');
var express = require('express');
var router = express.Router();
var Camera = require('gopro').Camera;
var cam = new Camera('10.5.5.9', 'goprohero');
var fs = require('fs');
var FILE = "public/arquivo.txt";

/* GET home page. */
router.get('/', function(req, res) {


	fs.readFile(FILE, 'utf8', function (err,data) {
	  if (err) {
	    return console.log(err);
	  }
	  
	  console.log(data);
		if(data=='start')
			cam.startCapture();
		else if(data=='stop')
			cam.stopCapture();

	});
	
	fs.unlink(FILE, function (err) {
  	if (err) throw err;
  		console.log('Não foi possível deletar arquivo.');
	});
	
	

    res.render('index', { title: 'Maestro' });
});


module.exports = router;
