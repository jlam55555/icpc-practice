

P = int(input())

a=2
b=1
if P >= 1:
    print(a, end=" ")
if P >= 2:
    print(b, end=" ")

count=2
for _ in range(2,P):

    c=a+b

    # Print result
    print( c, end=" " )
    count+=1
    if count%7 == 0:
        print()

    a=b
    b=c

if (count % 7 != 0):
    print()