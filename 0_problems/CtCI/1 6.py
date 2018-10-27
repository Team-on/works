# 1.6 Given an image represented by an NxN matrix, where each pixel in the image is 4
# bytes, write a method to rotate the image by 90 degrees. Can you do this in place?
n = input("N: ")
mtx = list(range(n))
for i in mtx:
    mtx[i] = list(range(n))
    print(mtx[i])

for i in range(n):
    for j in range(n):
        mtx[i][j] = mtx[n-1-j][i]

for i in mtx:
    print(i)
