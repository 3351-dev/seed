<?php
	$text=$_POST['text'];
	// echo $text."<br>";
	// echo exec("pwd");
	// echo "<br>";
	exec("sudo python3 TTS/test.py '$text' 2>errMsg");
	// echo "done<br>";

	echo json_encode($text, JSON_PRETTY_PRINT|JSON_UNESCAPED_UNICODE);

?>