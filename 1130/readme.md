Error List
==========

1130
-----
##Err
~~~using 127.0.1.1 set the 'ServerName' directive globally to suppress this message
vi /etc/apache2/apache2.conf
ServerName "~~~"
sudo service apache2 restart


##Info
Apache2를 재시작 할때는 다음의 코드를 사용하자
어디서 오류가 났는지 알려준다.
>sudo apache2ctl restart

##Info
apache2 에러로그 위치
>/var/log/apache2

##Memo
Content-type: text/html
Content-type : text/html X

1201
-----
##hosts
/etc/hosts
localhost > myhost.com
 
1202
----
##한글 안나오는 문제
\<head\> 안에 meta를 이용하여 설정해준다


