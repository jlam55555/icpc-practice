import math

stuff = [ int(x) for x in input().split() ]

sums=0
for i in stuff:
    sums+=i

mean=sums/10
dev=0
for i in range(10):
    dev+=sums[i]-mean

dev /= 9
dev = math.sqrt(dev)
    


# Print result
if dev <= 1:    
    print( "NOT COMFY" )
else:
    print( "COMFY" )

# Truncate to 3 decimals
# print( '%.3f'%(sum) )