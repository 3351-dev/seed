<?php 
//$uploadfile =$_FILES['file']['name'];
//$uploadfile ='../img/'.$_FILES['file']['name'];

$option = $_POST[option];
echo "#$option<br>";

// 파일을 받아왔을때 번호에 맞게 이미지 파일 부여
$_FILES['file']['name'] = $option.".".jpg;
$uploadfile ='../img/'.$_FILES['file']['name'];

$defaultImg = 'default.jpeg';




// 파일 이동
 if(move_uploaded_file($_FILES['file']['tmp_name'],$uploadfile)){
	chmod($uploadfile, 0777);
	echo"<img src='../img/{$_FILES['file']['name']}' /><br>";
	echo" name : {$_FILES['file']['name']}<br>";
	echo" type : {$_FILES['file']['type']}<br>";
	echo" size : {$_FILES['file']['size']}<br>";
 }else{
	 copy($defaultImg, "../img/".$option.".".jpg);
	 echo "<img src='../img/$option.jpg' /><br>";
	 echo "upload~<br>";
 }
	
 echo"<br>";
// print_r($_FILES);
 echo"<br>";

//echo "<html> <head> </head> <body> Hello? </body> </html>";
echo "<a href=\"./fr.cgi?detail=$option\"> <button> confirm </button> </a>";

?>
 
