#polimorfism test

class Number:
    def __init__(self, num):
        self.num = num

    def __add__(self, o):
        return self.num - o.num

    def __sub__(self, o):
        return self.num + o.num

a = Number(2)
b = Number(2)

print(a + b)
print(a - b)


class MyList:
    def __init__(self, l):
        self.list = list.copy(l)

    def __add__(self, o):
        l = MyList(self.list)

        for i in range(0, list.__len__(self.list)):
            l.list[i] += o.list[i]

        return l

    def __sub__(self, o):
        l = MyList(self.list)

        for i in range(0, list.__len__(self.list)):
            l.list[i] -= o.list[i]

        return l

    def __mul__(self, o):
        l = MyList(self.list)

        for i in range(0, list.__len__(self.list)):
            l.list[i] *= o.list[i]

        return l

    def __truediv__(self, o):
        l = MyList(self.list)

        for i in range(0, list.__len__(self.list)):
            l.list[i] /= o.list[i]

        return l

    def __floordiv__(self, o):
        l = MyList(self.list)

        for i in range(0, list.__len__(self.list)):
            l.list[i] //= o.list[i]

        return l

    def __str__(self):
        s = ''
        for i in self.list:
            s += str(i) + ' '
        return s

    def __eq__(self, o):
        if self.list.__len__() != o.list.__len__():
            return False

        for i in range(0, list.__len__(self.list)):
            if self.list[i] != o.list[i]:
                return False

        return True


ml1 = MyList([7, 2, 6, 8, 10, 125])
ml2 = MyList([2, 2, 2, 2, 2, 2])

print("1: ", ml1)
print("2: ", ml2, '\n')

print(ml1 + ml2)
print(ml1 - ml2)
print(ml1 * ml2)
print(ml1 / ml2)
print(ml1 // ml2, '\n')

print(ml1 == ml1)
print(ml1 != ml1)
print(ml1 == ml2)
print(ml1 != ml2)