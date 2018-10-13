# List with cubes
n = (int)(input("N: "))

list1 = [x**3 for x in range(n+1) if x % 2 == 1]

for i in range(n + 1):
    if i % 2 == 1:
        list1.append(i**3)

print(list1)

# List from n-1 to n+1
n = 0

while n < 3:
    try:
        n = int(input("n: "))
    except:
        n = 0
list2 = [i for i in range(n-1, n+1)]

print(list2)

# List average
n = 0
sum = 0.0

while n == 0:
    try:
        n = int(input("Arr length: "))
    except:
        n = 0

for i in range(n):
    while True:
        try:
            i = float(input("Arr i: "))
            sum += i
            break
        except:
            i = 0

print(sum / n)

# Is vector normalized and nornilize it if non
vecSize = 0
summ = 0.0
l = list()

while vecSize == 0:
    try:
        vecSize = int(input("vecSize: "))
    except:
        vecSize = 0

for i in range(vecSize):
    while True:
        try:
            i = float(input("coord: "))
            l.append(i)
            summ += i
            break
        except:
            i = 0

if summ == 1:
    print("Vector normalized")
else:
    print("Vector non normalized")
    summ = 0
    for i in l:
        summ += i**2
    summ = summ**0.5;
    for i in range(len(l)):
        l[i] /= summ
    print(l)