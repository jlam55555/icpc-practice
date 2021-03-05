
N = int(input())

sum = 0
for i in range(N):
    sum += float( input() )

# Print result
print( '%.3f'%(sum/float(N)) )