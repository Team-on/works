# Func test
def separator(sym="_"):
    print(sym * 10)


# separator("##")
# print("Hi!")
# separator("#")
# print("Here")


def f(x):
    return 2*x - 4


def sqr(x):
    return x ** 3


def moduls(x):
    return 0 if x < 0 else x
    #if x < 0:
    #    return 0
    #return x


def max(x, y):
    return x if x >= y else y


def avg(l):
    if not isinstance(l, list):
        return "l not a list"
    sum = 0
    for i in l:
        sum += i
    return sum / len(l)


def geom(l):
    if not isinstance(l, list):
        return "l not a list"
    sum = 0
    for i in l:
        sum += i**2
    return sum / len(l)

	
# n = input("Max x: ")
# for i in range(n+1):
#     print(i, f(i))
#     print(i, sqr(i))

# print(moduls(-5))
# print(moduls(0))
# print(moduls(124))

# print(max(7, 4))
# print(max(1, 5))
# print(max(1, -5))

# print(avg(range(1, 6)))
# print(avg(range(100, 601)))
# print(avg(5))

# print(geom(range(1, 6)))
# print(geom(range(100, 601)))
# print(geom(5))
