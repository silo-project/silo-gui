document.addEventListener("DOMContentLoaded", function() {
	let socket = new WebSocket("ws://localhost:7681");
	socket.onopen = function(e) {
		console.log("[open] 커넥션이 만들어졌습니다.");
		socket.send("My name is John");
		console.log("데이터를 서버에 전송했습니다.");
	};

	socket.onmessage = function(event) {
		console.log(`[message] 서버로부터 전송받은 데이터: ${event.data}`);
	};

	socket.onclose = function(event) {
		if (event.wasClean) {
			console.log(`[close] 커넥션이 정상적으로 종료되었습니다(code=${event.code} reason=${event.reason})`);
		} else {
			// 예시: 프로세스가 죽거나 네트워크에 장애가 있는 경우
			// event.code가 1006이 됩니다.
			console.log('[close] 커넥션이 죽었습니다.');
		}
	};

	socket.onerror = function(error) {
		console.log(`[error] ${error.message}`);
	};
}, false);

