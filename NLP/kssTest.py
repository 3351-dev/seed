import kss

text = '''안녕하세요 테스트중입니다. 온점을 찍을때와 안찍을때 어떻게 나뉘는지 궁금합니다.
어떻게. 나뉠까요? 결과가 기대됩니다 기대됩니다.
'''

print('tokenizer : ',kss.split_sentences(text))