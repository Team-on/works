# cracking the code interview 1.1
str = raw_input("str: ")
l = list(i for i in str)
l.sort()

findPair = False
for i in range(1, len(l)):
    if l[i] == l[i - 1]:
        findPair = True;
        break;

if findPair:
    print("Not only unique")
else:
    print("Only unique")