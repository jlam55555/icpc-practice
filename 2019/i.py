
arr = [0,1,2,3,4,5,6,7,8,9,'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W',
        'X','Y','Z','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z']
P,Q,N = [ int(x) for x in input().split() ]

for i in range(40):

    skip=False
    tempN = N*(Q**i)

    coeffs = []
    for j in reversed( range(i+1) ):
        denom = ( (P**j)*(Q**(i-j)) )
        coeffs.append( int( tempN/denom ) )
        if coeffs[-1] >= P*(Q**(i-j)):
            skip=True
            break
        tempN %= denom

    # for j in reversed( range(i+1) ):
    #     denom = P**j
    #     coeffs.append( int( tempN/denom ) )
    #     if coeffs[-1] >= P:
    #         skip=True
    #         break
    #     tempN %= denom
    
    if tempN != 0:
        skip=True

    # print(len(coeffs), coeffs)

    # i=4
    #   15 * q^4 = a_o*q^4 + a_1*q^3*p + a_2*q^2*p^2 + a_3
    #   15 * q^4 = c_0 + c_1*p + c_2*p^2 ...

    # c_4=2, c_3=2
    # tempN = 24
    
    # c_2*p^2 = 9*c_2
    # for j in range( len(coeffs) ):
    #     if coeffs[j] % ( Q**j ) != 0:
    #         print(f"not divisble {coeffs[j]} {Q**j}")
    #         skip = True
    #         break
    #     else:
    #         coeffs[j] /= Q**j

    if skip:
        continue

    # Valid soln found
    break

# Print result
coeffs = [ arr[x] for x in coeffs ]
for i in coeffs:
    print( i, end="" )
print()
# Truncate to 3 decimals
# print( '%.3f'%(sum) )