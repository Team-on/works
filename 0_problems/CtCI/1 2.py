# cracking the code interview 1.2
str1 = raw_input("str1: ")
str2 = raw_input("str2: ")
l1 = list(i for i in str1)
l2 = list(i for i in str2)
l1.sort()
l2.sort()
print(l1)
print(l2)

findDiff = False
if len(l1) == len(l2):
    for i in range(len(l1)):
        if l1[i] != l2[i]:
            findDiff = True;
            break;

if findDiff:
    print("Not permutation")
else:
    print("Permutation")