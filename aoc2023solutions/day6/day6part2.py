f = open("input.txt", "r")
file = f.read().splitlines()
times = [int("".join([file[0].split()[1:]][0]))]
recorddistances = [int("".join(file[1].split()[1:]))]
product = 1

#print(times)
#print(recorddistances)

#inefficient but completes in ~10 seconds so idrc
for time in enumerate(times):
    ways = 0
    for timeheld in range(time[1] + 1):
        distance = timeheld * (time[1] - timeheld)
        if distance > recorddistances[time[0]]:
            ways += 1
    product *= ways

print(product)
