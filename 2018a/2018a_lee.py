P = int(input())

for i in range(P):
	cor = False
	line = input()
	K,C = [ int(x) for x in line.split()[0:2] ]
	pots = [ int(x) for x in line.split()[2:] ]

	sums = {0}
	for p in pots:
		tempSums = set()
		for s in sums:
			tempSums.add( s+p )
			if s+p == C:
				cor = True
				break
		if cor:
			break
		sums = sums.union( tempSums )

	print( str(i+1), end=" " )
	print( "YES" ) if cor else print( "NO" )

