import torch
from konlpy.tag import Okt
from collections import Counter


### 크롤링을 위한 모듈 
from bs4 import BeautifulSoup as bs
import requests

import pandas as pd

url = 'https://engineering.linecorp.com/ko/blog/how-line-messaging-servers-prepare-for-new-year-traffic/'

response = requests.get(url)

# print(response.encoding) # ISO-8859-1
response.encoding = 'utf-8'

html_text = response.text

soup = bs(response.text, 'html.parser')

contents = soup.select('div.content_inner') ## 외계어


# 해당 문장에서 명사만 추출
okt = Okt()

# 출력부
for i in contents:
	title = i.get_text()
	# print(okt.nouns(title))
	# pageNouns = set(okt.nouns(title))
	pageNouns = (okt.nouns(title))
	count = Counter(pageNouns)

noun_list = count.most_common(100)
for i,v in noun_list:
	# print(i, v)
	if len(i)<2 :
		# print(i, v)
		noun_list.pop(v)
	else :
		print(i, v)

# print(noun_list)

# max = 0
# for nouns in pageNouns:
# 	cnt = pageNouns.count(nouns)
# 	if max<cnt:
# 		max = cnt
# 		print(nouns, '\t:\t' ,cnt)
# 	# print(i)


