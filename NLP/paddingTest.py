import numpy as np
from tensorflow.keras.preprocessing.text import Tokenizer

preprocessed_sentences = [['barber', 'person'], ['barber', 'good', 'person'],
 ['barber', 'huge', 'person'], ['knew', 'secret'], ['secret', 'kept', 'huge', 'secret'],
 ['huge', 'secret'], ['barber', 'kept', 'word'], ['barber', 'kept', 'word'], 
 ['barber', 'kept', 'secret'], ['keeping', 'keeping', 'huge', 'secret', 'driving', 'barber', 'crazy'], 
 ['barber', 'went', 'huge', 'mountain']]

tokenizer = Tokenizer()
tokenizer.fit_on_texts(preprocessed_sentences)
encoded = tokenizer.texts_to_sequences(preprocessed_sentences)
print(encoded)

max_len = max(len(item) for item in encoded) 
print("max_len : ",max_len)

for sentence in encoded:
	while len(sentence)<max_len:
		sentence.append(0)

padded_np = np.array(encoded)
print(padded_np)