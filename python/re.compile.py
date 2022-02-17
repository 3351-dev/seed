import re
p = re.compile(r'\s\s+')
print(p)

print('')

# apble, abple
text = "!abple I like apble and abple apble! ?!"
text_mod = re.sub('abple|apble', "apple", text.strip('!'))

#strip([char]) ; 인자로 전달된 문자를 String의 왼쪽, 오른쪽에서 제거
# 공백일 경우 " " 제거
print(text_mod)

