def maxofdict(dictionary):
    keys = dictionary.keys()
    maximum = 0
    maxkey = ""
    for i in keys:
        if i == "J":
            continue
        if dictionary[i] > maximum:
            maxkey = i
            maximum = dictionary[i]
    return maxkey

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
        jokerpresent = 0
        for j in i[0]:
            try:
                cards[j] += 1
            except KeyError:
                cards[j] = 1
        if "J" in cards.keys():
            jokerpresent = 1
#        print(cards)
        cardlen = len(cards) - jokerpresent
        if cardlen == 0:
            fiveoakind.append(i)
            continue
        if jokerpresent:
            cards[maxofdict(cards)] += cards["J"]
#        print(cards)
        if cardlen == 1:
            fiveoakind.append(i)
        elif cardlen == 2:
            for j in cards.keys():
                if j == 'J':
                    continue
                if cards[j] == 4 or cards[j] == 1:
                    fouroakind.append(i)
                    break
                if cards[j] == 3 or cards[j] == 2:
                    fullhouse.append(i)
                    break
        elif cardlen == 3:
            for j in cards.keys():
                if j == "J":
                    continue
                if cards[j] == 3:
                    threeoakind.append(i)
                    break
                if cards[j] == 2:
                    twopair.append(i)
                    break
        elif cardlen == 4:
            onepair.append(i)
        else:
            highcard.append(i)
    allcards = [fiveoakind, fouroakind, fullhouse, threeoakind, twopair, onepair, highcard][::-1]
    mapping = {"A":"E", "K":"D", "Q":"C", "T":"B", "J":"1"}
    out = []
#    print(allcards)
    for i in allcards:
        sortablecards = []
        for card in i:
            temp = list(card[0])
            for char in enumerate(temp):
                if char[1] in "AEKQTJ":
                    temp[char[0]] = mapping[char[1]]
            sortablecards.append(["".join(temp), card[1]])
        sortablecards = sorted(sortablecards, key=lambda x:x[0])
        out += sortablecards
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
