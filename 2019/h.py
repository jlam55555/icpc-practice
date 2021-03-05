import math

def primeFac(n):
    for i in range(2,int(math.sqrt(n)+1)):
        if n%i==0:
            return i

P = int(input())
primes = set()
for i in range(P):

    n = int(input())
    fac = primeFac(n)
    primes.add( fac )
    primes.add( n/fac )

primes = list(primes)
primes.sort()
count = 0
for i in primes:
    count += 1
    print(int(i), end=" ")
    if count % 5 == 0:
        print()

if count % 5 != 0:
    print()