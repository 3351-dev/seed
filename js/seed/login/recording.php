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

			<b><text id="alert"> ๐์๋์ ๋ฌธ์ฅ์ ์ฝ์ด์ฃผ์ธ์.๐</text></b>
			<br>
			<text id='script'> "์ด์  ๋ณธ๊ฒฉ์ ์ผ๋ก ์์ํด ๋ณผ๊น์? ์ฒซ๋ฒ์งธ ๋ฌธ์  ๋ณด์ฌ์ฃผ์ธ์!" </text>

			<!-- ๋ก๊ทธ์ธ์ ๋ช๋ฒ์งธ script์ธ์ง ํ์ธํด์ผํจ (recordingServer.py์ count ๋ถ๋ถ ํ์ธํ  ๊ฒ -->
			<!-- ์๋ฃ -->

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
					$('#alert').text("๐จ Recording ๐จ");
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
//    					fileName = blobURL.split("127.0.0.1/");
    					fileName = blobURL.split("https://aiserver.thankage.com/");
//                        console.log(a.href);
//                        console.log(fileName[0]);

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
					$('#alert').text("Play๋ฅผ ๋๋ฌ ํ์ธํ์๊ณ  Rec๋ก ๋ค์๋น์ํ๊ฑฐ๋ Next๋ก ์ด๋ํด์ฃผ์ธ์");

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
				if (isEnd.value == '"Next๋ฅผ ๋๋ฌ ํ์ต์ ์์ฒญํ์ธ์."'){
					// console.log('next_btn end');
					$.ajax({
						type:'post',
//						url:'http://127.0.0.1:8000/merge',
                        url:'https://aiserver.thankage.com:8000/merge',
						dataType:'text',
						data:{
							'id' : $user_name,
						},
						success: function(text){
							console.log('success')
							console.log(text)
							$('#script').text("ํ์ต์ด ๋๋ ํ ์ด๋ฉ์ผ๋ก ์๋ ค๋๋ฆด๊ฒ์๐");
							$rec_btn.disabled = true;
							$play_btn.disabled = true;
							$next_btn.disabled = true;
							$('#alert').text("๊ณ ์ํ์จ์ต๋๋ค!\n");
						},
						error: function(text){
							console.log('err')
							console.log(text)
						},
					})
					/*
						merge
						filelistsํด๋ ์์ฑ ์ด ์์ wavsํด๋ ์์ฑ ํ ์์ฑํ์ผ ์ด๋
						metadata.csv์ ํํ๋ก "audioFile|script" ๋ก ๋ง๋ค์ด์ค
						glowtts, hifigan ํ์ต ์์.

					*/

				}

				else{
					$.ajax({
						type:'post',
//						url:'http://127.0.0.1:8000/Recording',
						url:'https://aiserver.thankage.com:8000/Recording',
						processData: false,
						contentType: false,
						dataType: 'json',
						data:
							fd_data,
						success: function(text){
							console.log("๐ฅ")
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
//					url:'http://127.0.0.1:8000/scenario',
					url:'https://aiserver.thankage.com:8000/scenario',
					dataType: 'text',
					data:{
						"scenarioCount": count
					},
					// success ์ ์๋์ง?? 
					// try catch๋ฌธ์ผ๋ก ์ก์๋๊ณ  ๋๋ค๊ณ ์๊ฐํจ? ใใ
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

