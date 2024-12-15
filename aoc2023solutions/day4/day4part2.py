f = open("input.txt", 'r')
file = f.read().strip().split('\n')

new = []
for i in file:
    new.append(i.split(':')[1])
file = new
cards = []
for i in file:
    cards.append(i.split('|'))

cardsforeach = []
cardnumforeach = [1] * len(cards)
for i in cards:
    winningnums = i[0].split()
    yournums = i[1].split()
    count = 0
    for j in yournums:
        if j in winningnums:
            count += 1
    cardsforeach.append(count)

for i in range(len(cards)):
    for j in range(i + 1, cardsforeach[i] + i + 1):
        cardnumforeach[j] += 1 * cardnumforeach[i]


print(sum(cardnumforeach))
