from random import randint

s=0
for _ in range(100000):
    temp = randint(1, 1000000)
    s += temp
    print(temp)

print("---", s)