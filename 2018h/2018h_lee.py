from collections import defaultdict


def smallest(n):
    return 2

def SP(n):
    if n==1 or (n in PRIMES):
        return n
    else
        return n/smallest(n)

P = int(input())

fibDict = defaultdict( set() )
for i in range(P):
    
    K, n, a_o, a_1 = [ int(x) for x in input().split() ]

    fibDict[a_o] = {a_1}
    for i in range(n):

        a_new = SP( a_o + a_1 )
        if a_new in fibDict[a_1]:
            break
        fibDict[a_1].add(a_new)
        a_o = a_1
        a_1 = a_new

    # Print result
    print( str(i+1), end=" " )
