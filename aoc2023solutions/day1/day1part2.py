f = open("input.txt", "r")
file = f.read().split('\n')
digits = [str(x) for x in range(10)]
sum = 0
letterdigits = ['zero', 'one', 'two', 'three', 'four', 'five', 'six', 'seven', 'eight', 'nine']
newfile = []

def screen_poss_digits(string):
    possresults = []
    threelen = ["one", "two", "six"]
    for i in range(len(string) - 2):
        if string[i:i+3] in threelen:
            possresults.append([i, i+3])
    fourlen = ["zero", "four", "five", "nine"]
    for i in range(len(string) - 3):
        if string[i:i+4] in fourlen:
            possresults.append([i, i+4])
    fivelen = ["three", "eight", "seven"]
    for i in range(len(string) - 4):
         if string[i:i+5] in fivelen:
            possresults.append([i, i+5])
    min = [len(string), len(string)]
    for i in possresults:
        if i[0] < min[0]:
            min = i
    return min


for i in file:
    string = i 
    out = []
    previndex = 0
    while screen_poss_digits(string) != [len(string), len(string)]:
        result = screen_poss_digits(string)
        out = []
        out.append(string[:result[0]])
        out.append(str(letterdigits.index(string[result[0]:result[1]])))
        out.append(string[result[1] - 1:len(string)]) #i hate this part
        previndex = result[1]
        string = "".join(out)
    #print(string)
    #print(out)

    out.append(string[previndex:len(string)])
    string = "".join(out)
    newfile.append(string)
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
