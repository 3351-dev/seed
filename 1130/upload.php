<?php 
//$uploadfile =$_FILES['file']['name'];
//$uploadfile ='../img/'.$_FILES['file']['name'];

$option = $_POST[option];
echo "$option<br>";

$_FILES['file']['name'] = $option.".".jpg;

$uploadfile ='../img/'.$_FILES['file']['name'];



// 파일 이동
 if(move_uploaded_file($_FILES['file']['tmp_name'],$uploadfile)){
	chmod($uploadfile, 0777);
	echo"<img src={$_FILES['file']['name']} /><br>";
	echo" name : {$_FILES['file']['name']}<br>";
	echo" type : {$_FILES['file']['type']}<br>";
	echo" size : {$_FILES['file']['size']}<br>";
 }else{
	 echo "Failed Upload<br>";
 }
	
 echo"<br>";
 print_r($_FILES);
 echo"<br>";

?>
 
