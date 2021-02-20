from cs50 import get_string

number = get_string('Number: ')
reversed_number = number[::-1]
odd_sum = sum([(int(x) * 2) // 10 + ((int(x) * 2) % 10)
               for x in reversed_number[1::2]])
even_sum = sum([int(x) for x in reversed_number[0::2]])
total_sum = odd_sum + even_sum

if total_sum % 10 == 0:
    if len(number) == 15 and number[0:2] in ['34', '37']:
        print('AMEX')
    elif len(number) == 16 and 51 <= int(number[0:2]) <= 55:
        print('MASTERCARD')
    elif len(number) in [13, 16] and number[0] == '4':
        print('VISA')
    else:
        print('INVALID')
else:
    print('INVALID')
