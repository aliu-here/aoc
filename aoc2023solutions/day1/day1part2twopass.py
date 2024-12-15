f = open("input.txt", "r")
file = f.read().split('\n')
#file = ["oneight7sevenine"]
digits = [str(x) for x in range(10)]
sum = 0
letterdigits = ['zero', 'one', 'two', 'three', 'four', 'five', 'six', 'seven', 'eight', 'nine']
newfile = []

def screen_poss_digits(string, rev=False):
    possresults = []
    if (rev):
        string = string[::-1]
    threelen = ["one", "two", "six"]
    if (rev):
        threelen = [i[::-1] for i in threelen]
    for i in range(len(string) - 2):
        if string[i:i+3] in threelen:
            possresults.append([i, i+3])
    fourlen = ["zero", "four", "five", "nine"]
    if (rev):
        fourlen = [i[::-1] for i in fourlen]
    for i in range(len(string) - 3):
        if string[i:i+4] in fourlen:
            possresults.append([i, i+4])
    fivelen = ["three", "eight", "seven"]
    if (rev):
        fivelen = [i[::-1] for i in fivelen]
    for i in range(len(string) - 4):
         if string[i:i+5] in fivelen:
            possresults.append([i, i+5])
    min = [len(string), len(string)]
    for i in possresults:
        if i[0] < min[0]:
            min = i
    return min


for i in file:
    out = []
#    print(i)
    forward = screen_poss_digits(i)
    backward = screen_poss_digits(i, True)
    backward = [len(i) - x for x in backward]
    backward = [backward[1], backward[0]]
    out.append(i[:forward[0]])
    if forward[0] != forward[1]:
        out.append(str(letterdigits.index(i[forward[0]:forward[1]])))
#        print(out)
    out.append(i[forward[1]:backward[0]])
    if backward[0] != backward[1]:
#        print(backward[0])
#        print(backward[1])
#        print(i[backward[0]:backward[1]])
        out.append(str(letterdigits.index(i[backward[0]:backward[1]])))
    out.append(i[backward[1]:])
    newfile.append("".join(out))
    #print(string)
    #print(out)
#    print(newfile)
file = newfile

for i in file:
    for j in i:
        if j in digits:
            sum += int(j) * 10
#            print(j, end='')
            break
    for j in i[::-1]:
        if j in digits:
            sum += int(j)
#            print(j)
            break
print(sum)
