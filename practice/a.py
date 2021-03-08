

P = int(input())

a = 2
b = 1

if P >= 1:
    print(a, end=" ")
if P >= 2:
    print(b, end=" ")

count=2

for i in range(2,P):
    a,b=b,a+b
    count+=1
    print(b, end=" ")
    if count%7 == 0:
        print()

if count%7 != 0:
    print()


#     stuff = [ int(x) for x in input().split() ]


#     # Print result
#     print( str(i+1), end=" " )

# Truncate to 3 decimals
# print( '%.3f'%(sum) )