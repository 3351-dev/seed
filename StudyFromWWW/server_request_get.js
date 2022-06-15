// server_request_get.js

var http = require('http')

var url = require('url')

var queryString = require('querystring')
/*
	query string
	query parameters의 url 뒤에 덧붙여 추가적인 정보를 서버측에 전달
	http://localhost:8080/?var1=newData&var2=153&var3=testdata2017
	위의 url을 입력했을때 query string은 ?var1=newData&var2=153&var3=testdata2017
*/

var server = http.createServer(function(request, response){
	console.log('--- log start ---')

	var parsedUrl = url.parse(request.url)
	console.log(parsedUrl);

	var parsedQuery = queryString.parse(parsedUrl.query, '&','=');
	console.log(parsedQuery);
	console.log('--- log end ---')

	response.writeHead(200, {'Content-Type':'text/html'})
	response.end('Hello node js')
})

server.listen(8080, function(){
	console.log('Server is running')
})