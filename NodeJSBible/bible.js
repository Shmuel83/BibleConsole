var http = require('http');
const readline = require('readline');
var xml2js = require('./lib_XML2JS/xml2js.js').parseString;

var NodeJSBible = function (options) {
	
var myBook = "Jn";
var myChapt = 1;
var myVerseStart = 1;
var myVerseStop = 2;
var myVersion = "darby";
/*
var server = http.createServer(function(req, res) {
  res.writeHead(200);
  res.end('Salut tout le monde !');
});
server.listen(8080);
*/
process.stdin.resume();
process.stdin.setEncoding('utf8');

var rl = readline.createInterface({
    input: process.stdin,
    output: process.stdout
});

function requestVerseStop() {
		rl.question('Verse Stop? ', function(answer) {
		rl.close();
		process.stdin.destroy();
		myBook = Number(answer);
	});	
}

function requestVerseStart() {
		rl.question('Verse Start? ', function(answer) {
		myBook = Number(answer);
		rl.close();
		process.stdin.destroy();
		requestVerseStop();
	});	
}

function requestChapter() {
		process.stdin.destroy();	
		rl.question('Chapt? ', function(answer) {
		myChapt = Number(answer);
		rl.close();
		requestVerseStart();
		process.stdin.destroy();		
	});
	
}

function requestBook() {
  rl.question('Book? ', function(answer) {
  myBook = answer;
  rl.close();
  //requestChapter();
  getTestPersonaLoginCredentials();
  process.stdin.destroy();  
  });
  
}

function getTestPersonaLoginCredentials(callback) {
return http.get({
        host: "api.preachingcentral.com",
		path: "/bible.php?passage="+myBook+myChapt+":"+myVerseStart+"-"+myVerseStop+"&version="+myVersion
    }, function(response) {
        // Continuously update stream with data
        var body = '';
        response.on('data', function(d) {
            body += d;
        });
        response.on('end', function() {

            // Data reception is done, do whatever with it!
            var parsed = body;
			//console.log(parsed);
			xml2js(parsed, function (err, result) {
				for(var i=0; i<=(myVerseStop-myVerseStart); i++) {
					var myjson = result.bible.range[0].item[i].text;
					console.dir(myjson);
				}
			});
        });
    });
}
requestBook();
//getTestPersonaLoginCredentials();


}
module.exports = NodeJSBible;