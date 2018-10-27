# Знаходить всі варіанти коли числа з List l дають суму int num
# 
# Дописати щоб мыж числами могло не бути знаку. Тобто 1,2 => 1+2, 1-2, 12
def solve(l, num):
    sym = []
    for _ in l:
        sym.append(0)

    while sym.count(0) != 0:
        sum = 0
        for i in range(len(sym)):
          sum += l[i] if sym[i] == 0 else -l[i]

        if sum == num:
            s = ""
            for i in range(len(sym)):
                s += ("+" + (str)(l[i])) if sym[i] == 0 else (str)(-l[i])
            print(sym)
            print(s)

        sym[0] += 1
        for i in range(1, len(sym)):
            if sym[i - 1] == 2:
                sym[i - 1] = 0
                sym[i] += 1

solve([1, 2, 3, 4, 5, 6, 7, 8, 9] ,13)я 