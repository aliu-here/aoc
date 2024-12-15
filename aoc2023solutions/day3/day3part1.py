f = open("input.txt", 'r')
file = f.read().strip().split('\n')

temp = []
for i in file:
    temp.append([x for x in i])
file = temp
def adjacent(data, coord):
    digitindices = []
    for i in enumerate(data):
        for j in i[1]:
            loc = j[1]
            if abs(loc[0] - coord[0]) <= 1 and abs(loc[1] - coord[1]) <= 1 and loc != coord:
                digitindices.append(i[0])
                break
    return digitindices


digitresults = []
numbers = []
sum = 0

for i in enumerate(file):
    number = []
    for j in enumerate(i[1]):
        if j[1] not in "1234567890":
            if number != []:
                numbers.append(number)
            number = []
        else:
            number.append([j[1], [i[0], j[0]]])
    if number != []:
        numbers.append(number)
for i in enumerate(file):
    for j in enumerate(i[1]):
        if j[1] not in "1234567890.":
            adjacentdigits = adjacent(numbers, [i[0], j[0]])
            for k in adjacentdigits:
                sum += int(''.join([x[0] for x in numbers[k]]))
print(sum)            
