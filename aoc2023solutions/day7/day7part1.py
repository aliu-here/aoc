def sorthands(hands):
    fiveoakind = []
    fouroakind = []
    fullhouse = []
    threeoakind = []
    twopair = []
    onepair = []
    highcard = []
    for i in hands:
        cards = {}
        for j in i[0]:
            try:
                cards[j] += 1
            except KeyError:
                cards[j] = 1
        if len(cards) == 1:
            fiveoakind.append(i)
        elif len(cards) == 2:
            for j in cards.keys():
                if cards[j] == 4 or cards[j] == 1:
                    fouroakind.append(i)
                    break
                if cards[j] == 3 or cards[j] == 2:
                    fullhouse.append(i)
                    break
        elif len(cards) == 3:
            for j in cards.keys():
                if cards[j] == 3:
                    threeoakind.append(i)
                    break
                if cards[j] == 2:
                    twopair.append(i)
                    break
        elif len(cards) == 4:
            onepair.append(i)
        else:
            highcard.append(i)
    allcards = [fiveoakind, fouroakind, fullhouse, threeoakind, twopair, onepair, highcard][::-1]
    mapping = {"A":"E", "K":"D", "Q":"C", "J":"B", "T":"A"}
    reversemapping = {"E":"A", "D":"K", "C":"Q", "B":"J", "A":"T"}
    out = []
    for i in allcards:
        sortablecards = []
        for card in i:
            temp = list(card[0])
            for char in enumerate(temp):
                if char[1] in "AEKQJT":
                    temp[char[0]] = mapping[char[1]]
            sortablecards.append(["".join(temp), card[1]])
        sortablecards = sorted(sortablecards, key=lambda x:x[0])
#        print(sortablecards)
        sortedoriginalcards = []
        for card in sortablecards:
            temp = list(card[0])
            for char in enumerate(temp):
                if char[1] in "ABCDE":
                    temp[char[0]] = reversemapping[char[1]]
            sortedoriginalcards.append([''.join(temp), card[1]])
#        print(sortedoriginalcards)
        out += sortedoriginalcards
    return out

f = open("input.txt", "r")
file = f.read().strip().split('\n')

file = [x.split() for x in file]
sortedcards = sorthands(file)
sum = 0

for pair in enumerate(sortedcards):
    #    print(pair[1])
    bet = int(pair[1][1])
    sum += (pair[0]+1) * bet

print(sum)
