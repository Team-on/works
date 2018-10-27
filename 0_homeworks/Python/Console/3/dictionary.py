'''
# Dictionary test.
sqr = {0:0, 1:1, 2:4}
print(sqr.keys()[2])
for x in sqr.keys():
    print(x)
'''


'''
a,b,c = 1,2,3
a,b=b,a
print(a)
print(b)
print(c)
'''


#Simple phonebook
phonebook = {}
for _ in range(input("Number: ")):
    n = raw_input("Abonent name: ")
    t =  input("Abonent number: ")
    phonebook[n] = t

n = raw_input("Search name: ")
if n in phonebook:
    print(phonebook[n])
else:
    print("Cant find key")
