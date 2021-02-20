from cs50 import get_string

text = get_string('Text: ')
sentances = words = letters = 0

for char in text:
    if char.isalpha():
        letters += 1
    if char.isspace():
        words += 1
    if char in ['?', '.', '!']:
        sentances += 1

words += 1

L = (letters * 100) / words
S = (sentances * 100) / words
index = int((0.0588 * L - 0.296 * S - 15.8) + 0.5)
if index < 1:
    print('Before Grade 1')
elif index >= 16:
    print('Grade 16+')
else:
    print(f'Grade {index}')
