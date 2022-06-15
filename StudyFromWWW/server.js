// http 모듈을 http 변수에 담음
var http = require('http');

// http 모듈로 서버 생성
// 사용자로부터 http 요청이 들어오면 function 블럭내부의 코드를 실행
var server =http.createServer(function(request, response){
	response.writeHead(200,{'Content-Type':'text/html'});
	response.end('Hello node.js!!');
})

// listen 함수로 8080 포트를 가진 서버 실행
server.listen(8080, function(){
	console.log('Server is running...')
})