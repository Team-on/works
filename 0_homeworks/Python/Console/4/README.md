class PaperPack:
    #def __init__(self):
    #    self.shape = "rectangle"
    #    self.color = "blue"
    #    self.material = "paper"
    #    self.useCase = "notes"
    #    self.amount = "100"
    #    self.name = "stickers"

    def __init__(self, shape="DEFAULT", color="DEFAULT", mat="DEFAULT", use="DEFAULT", amo=100, name="DEFAULT"):
        self.shape = shape
        self.color = color
        self.material = mat
        self.useCase = use
        self.amount = amo
        self.name = name

    def RemoveLetter(self, note):
        self.amount -= 1
        return "I write: " + note

    def StaticMethod():
        print("QQ from static method")

    def __repr__(self):
        return "Papers-"+self.name


stickers = PaperPack(color="RED", use="Just paper", name="Paper")

#print(stickers, '\n')
#print(stickers.__dict__, '\n')

#print(stickers.RemoveLetter("SMTH Cool"), '\n')
#print(stickers.__dict__, '\n')


#print(PaperPack.RemoveLetter(stickers, "MORE"), '\n')
#print(stickers.__dict__, '\n')

#PaperPack.StaticMethod()


class Mug:
    def __init__(self, print = "Flowers", color = "White", mat = "Glass", liquid = None):
        self.print = print
        self.color = color
        self.mat = mat
        self.liquid = liquid

    def clear(self):
        self.liquid = None

    def __repr__(self):
        return "Mug-" + self.liquid.__repr__()


mug = Mug(liquid="Cola")
#print(mug.__dict__, '\n')
#mug.clear()
#print(mug.__dict__, '\n')



class Shell:
    head = -1

    def __init__(self, content = []):
        self.content = content

    def Push(self, o):
        self.head += 1
        self.content.append(o)

    def Pop(self):
        if self.head == -1:
            return  None
        rez = self.content.pop(self.head)
        self.head -= 1
        return rez


class Marker:
    amount = 100

    def __init__(self, color="Black"):
        self.color = color

    def Use(self):
        self.amount -= 1

    def Fill(self, more):
        self.amount += more
        if self.amount > 100:
            self.amount == 100

    def __repr__(self):
        return "Marker-" + self.color + "-" + self.amount.__repr__()


class Penal:
    head = -1

    def __init__(self, content=[]):
        self.content = content

    def Push(self, o):
        self.head += 1
        self.content.append(o)

    def Pop(self):
        if self.head == -1:
            return None
        rez = self.content.pop(self.head)
        self.head -= 1
        return rez

    def __repr__(self):
        return "Penal-" + self.content.__repr__()

s = Shell()

s.Push(15)
s.Push(22)
s.Push("STR")
s.Push(77.125)
s.Push(77.125)

s.Push(stickers)

mug.liquid = Marker("Blue")
s.Push(mug)

p = Penal()
p.Push(Marker())
p.Push(Marker("Red"))
p.Push(Marker("Green"))

s.Push(p)

print(s.__dict__)
print(s.Pop())
print(s.__dict__)
