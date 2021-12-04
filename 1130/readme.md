Error List
==========

1130
-----
#### using 127.0.1.1 set the 'ServerName' directive globally to suppress this message   
vi /etc/apache2/apache2.conf   
ServerName "~~~"   
>sudo service apache2 restart   


#### Apache2를 재시작 할때는 다음의 코드를 사용하자   
어디서 오류가 났는지 알려준다.
>sudo apache2ctl restart   

#### apache2 에러로그 위치
>/var/log/apache2   

#### Memo
Content-type: text/htmla   
Content-type : text/html X   

1201
-----
#### hosts
/etc/hosts   
localhost > myhost.com   
 
1202
----
#### 한글 안나오는 문제   
\<head\> 안에 meta를 이용하여 설정해준다   

1203
----
#### 경로 지정 문제   
/cgitest에서 사진은 열리지 않아 하위 폴더 ../img를 만들고 php를 통해 사진을 저장해주었다.   
권한도 있어야하며 conf파일을 설정해줘야한다   

#### php   
php를 이용하여 multipart를 통해 파일전송을 구현하였다.   
option을 받아 이름을 지정해주어 출력이 된다.   
![Screenshot from 2021-12-03 18-41-54](https://user-images.githubusercontent.com/93642972/144580998-d8be0147-b3e4-4cd7-bc5f-d799c069bce3.png)


1203
----
#### default img 지정   
upload.php 파일에서 이미지가 선택이없을때 기본사진이 올라가도록 설정   

#### 입력에서 띄어쓰기시 +가 나타나는 현상 제거   
기존에 decode함수에서 띄어쓰기 처리가 안돼있어 추가   


