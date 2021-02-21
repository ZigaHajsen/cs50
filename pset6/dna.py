from sys import argv

if len(argv) != 3:
    print('There need to be 3 comand line arguments')
    exit(1)

file = open(argv[1], 'r')

strands = []
persons = {}
for index, row in enumerate(file):
    if index == 0:
        strands = [strand for strand in row.strip().split(',')][1:]
    else:
        curr_row = row.strip().split(',')
        persons[curr_row[0]] = [int(x) for x in curr_row[1:]]

dna_strand = open(argv[2], 'r').read()
final_strands = []
for strand in strands:
    index = 0
    current_max_strand = 0
    max_strand = -1
    while index < len(dna_strand):
        current_sequence = dna_strand[index:index + len(strand)]
        if current_sequence == strand:
            current_max_strand += 1
            max_strand = max(max_strand, current_max_strand)
            index += len(strand)
        else:
            current_max_strand = 0
            index += 1

    final_strands.append(max_strand)

for name, data in persons.items():
    if data == final_strands:
        print(name)
        exit(0)

print('No match')
