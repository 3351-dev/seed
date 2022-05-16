<?php
	$user = $_GET["username"];
	echo "ID : ",$user;
?>

<!DOCTYPE html>
<html lang="ko">
	<head>
		<meta charset="utf-8">
		<meta name="viewport" content="width=device-width, initial-scale=1.0">
	</head>


	<body>
		<div>

			<b><text id="alert"> 👇아래의 문장을 읽어주세요.👇</text></b>
			<br>
			<text id='script'> "이제 본격적으로 시작해 볼까요? 첫번째 문제 보여주세요!" </text>

			<!-- 로그인시 몇번째 script인지 확인해야함 (recordingServer.py의 count 부분 확인할 것 -->
			<!-- 완료 -->

			<br><br>
		</div>
		<div>
			<button id="rec_btn"> Rec </button>
				<audio id="rec_audio"></audio>
			<button id="play_btn"> Play </button>
			<button id="next_btn"> Next </button>
		</div>

		<script src="jquery-3.6.0.min.js"></script>
		<script type="text/javascript">
			// Recording, Play
			const $audioEl = document.getElementById("rec_audio");
			const $rec_btn = document.getElementById("rec_btn");
			const $play_btn = document.getElementById("play_btn");
			const $next_btn = document.getElementById("next_btn");


			// const $user_name = "rainbow22";
			const $user_name = '<?php echo $user=$_GET[username] ?>'
			// console.log($user_name)
			readScenario($user_name)

			let isRecording = false;
			let mediaRecorder = null;
			const audioArray = [];
			var a = document.createElement('a');
			let fd_data = new FormData();




			$rec_btn.onclick = async function(event){
				if(!isRecording){
					$('#alert').text("🚨 Recording 🚨");
					const mediaStream = await navigator.mediaDevices.getUserMedia({
						audio:true
					});

					var option={
						audioBitsPerSecond : 128000,
						mimeType : 'audio/webm; codecs=pcm'
					};

					mediaRecorder = new MediaRecorder(mediaStream, option);
					mediaRecorder.ondataavailable = (event)=>{
						audioArray.push(event.data);
					}

					mediaRecorder.onstop=(event)=>{
						const blob = new Blob(audioArray);
						const blobURL = window.URL.createObjectURL(blob);

						$audioEl.src = blobURL;
						// autoplay
						// $audioEl.play();
						
						a.href = blobURL;
						fileName = blobURL.split("127.0.0.1/");

						a.download = fileName[1]+'_'+$user_name+'.wav';
						console.log(a.download)
						audioArray.splice(0);

						const blobFile = new File([blob], a.download);
						
						fd_data.append("fd_name", a.download);
						fd_data.append("fd_audio", blobFile);

						
					}
					mediaRecorder.start();
					isRecording = true;
				}else{
					mediaRecorder.stop();
					isRecording = false;
					$('#alert').text("Play를 눌러 확인하시고 Rec로 다시녹음하거나 Next로 이동해주세요");

				}
			}

			$play_btn.onclick = async function(event){
				$audioEl.play();
			}

			$next_btn.onclick = async function (event) {
				var isEnd = document.getElementById('script');
				// var isEnd = $("#script");
				// console.log('isEnd.value : ' + isEnd.value);
				// console.log(document.getElementById("script"))
				if (isEnd.value == '"Next를 눌러 학습을 요청하세요."'){
					// console.log('next_btn end');
					$.ajax({
						type:'post',
						url:'http://127.0.0.1:8000/merge',
						dataType:'text',
						data:{
							'id' : $user_name,
						},
						success: function(text){
							console.log('success')
							console.log(text)
							$('#script').text("학습이 끝난 후 이메일로 알려드릴게요😆");
							$rec_btn.disabled = true;
							$play_btn.disabled = true;
							$next_btn.disabled = true;
							$('#alert').text("고생하셨습니다!\n");
						},
						error: function(text){
							console.log('err')
							console.log(text)
						},
					})
					/*
						merge
						filelists폴더 생성 이 안에 wavs폴더 생성 후 음성파일 이동
						metadata.csv의 형태로 "audioFile|script" 로 만들어줌
						glowtts, hifigan 학습 시작.

					*/

				}

				else{
					$.ajax({
						type:'post',
						url:'http://127.0.0.1:8000/Recording',
						processData: false,
						contentType: false,
						dataType: 'json',
						data:
							fd_data,
						success: function(text){
							console.log("📥")
							// console.log(text)
							readScenario(text)
						},
					})
				}

			}

			function readScenario(count){
				// console.log(count)	// good
				$.ajax({
					type:'post',
					url:'http://127.0.0.1:8000/scenario',
					dataType: 'text',
					data:{
						"scenarioCount": count
					},
					// success 왜 안되지?? 
					// try catch문으로 잡아두고 된다고생각함? ㅋㅋ
					susccess: function(text){
						// console.log('sucess')
						console.log(text)
					},
					error:function(text){
						// console.log('error')
						console.log(text);
					},
					complete: function(text){
						// console.log('complete')
						// console.log(text.responseText)
						nextScript = document.getElementById('script');
						nextScript.value = text.responseText;
						console.log('nextScript : '+nextScript.value);
						$('#script').text(text.responseText);
						// nextScript.text(text.responseText);
					}
				})
			}

		</script>
	</body>
</html>

