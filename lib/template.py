

P = int(input())

for i in range(P):

    stuff = [ int(x) for x in input().split() ]


    # Print result
    print( str(i+1), end=" " )

# Truncate to 3 decimals
# print( '%.3f'%(sum) )