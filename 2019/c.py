from collections import defaultdict

N, P = [ int(x) for x in input().split() ]

neighbors = {}
for i in range(N):

    stuff = [ int(x) for x in input().split() ][1:]
    neighbors[i+1] = stuff

counts = { k:len(v)+1 for k,v in neighbors.items() }
out = []


for i in range(P):
    win = defaultdict(int)
    probs = { k:0 for k,_ in neighbors.items() }

    _, start, target = [ int(x) for x in input().split() ]
    probs[start] = 1

    for _ in range(100):
        
        temp = defaultdict(int)
        for guy in probs.keys():
            win[guy] += probs[guy]/counts[guy]
            for nei in neighbors[guy]:
                temp[nei] += probs[guy]/counts[guy]
        probs = temp
    out.append( str(i+1) + " " + str('%.5f'%(win[target])) )

# Print result
for x in out:
    print(x)
