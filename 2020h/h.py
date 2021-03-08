from collections import defaultdict

teams = defaultdict( lambda:defaultdict( int ) )
penalty = defaultdict( list ) # Number of incorrect submissions
num = defaultdict( int )    # Number Solved
time = defaultdict( int )   # Total time taken
probs = defaultdict( list ) # Time taken to solve a problem incl. penalty

def tieBreak( myList ):

    if len(myList) <= 1:
        return myList

    tempList = [ x for x in myList ]
    same=[ tempList.pop(0) ]
    final = []

    while len(tempList) >= 1:
        if same[-1][1] == tempList[0][1]:
            tempList[0] = ( tempList[0][0], tempList[0][1], same[-1][2] )    
            same.append( tempList.pop(0) )
            if len(tempList) != 0:
                continue
        else:
            tempList[0] = ( tempList[0][0], tempList[0][1], same[-1][2]+1 )      

        if len(probs[same[0][0]]) >= 1:
            same = [ ( x[0], probs[x[0]].pop(-1), x[2] ) for x in same ]
        
        same = sorted( same, key=lambda x:x[1] )
        if same != myList:
            same = tieBreak( same )

        final += same
        
        if len(tempList) >= 1:
            same = [ tempList.pop(0) ]
        else:
            same = []

    final += same
    for i in range( len(final)-1 ):
        if final[i][1] != final[i+1][1]:
            final[i+1] = (final[i+1][0],final[i+1][1],final[i][2]+1)

    return final



########## START ##########
NT,NP,NS,NR = [ int(x) for x in input().split() ]

for i in range(NS):

    T,P,t,D = [ int(x) for x in input().split() ]
    
    if t >= 300:
        continue

    # Only apply penalty if problem not solved yet
    if D == 0 and teams[T][P] == 0:
        penalty[T].append(P)
    else:
        if teams[T][P] == 0:
            # Add penalty for the problem
            curPenalty = len( [x for x in penalty[T] if x==P] ) * 20
            probs[T].append( curPenalty + t + ( 0 if len(probs[T]) == 0 else probs[T][-1] ) )
            teams[T][P] = 1
            num[T] += 1
            time[T] += t

for T in penalty.keys():
    time[T] = probs[T][-1]

# print(probs)

# Sort by problems solved
numSort = sorted( num.items(), key=lambda x:x[1], reverse=True )

curRank = 1
while curRank <= NR and len( numSort ) >= 1:
    curBest = numSort.pop(0)
    listProbs = [curBest]

    # Get teams w/ same # of problems
    while len( numSort ) >= 1:
        if curBest[1] == numSort[0][1]:
            listProbs.append( numSort.pop(0) )
        else:
            break

    times = [ ( x[0], time[x[0]] ) for x in listProbs ]
    timeSort = sorted( times, key=lambda x:x[1] )

    # Get teams w/ same times
    while len(timeSort) >= 1:
        tempListTimes = [ timeSort.pop(0) ]
        while len( timeSort ) >= 1:
            if tempListTimes[0][1] == timeSort[0][1]:
                tempListTimes.append( timeSort.pop(0) )
            else:
                break
        
        # Break tie by last prob solved
        # Get team #s
        tms = [ x[0] for x in tempListTimes ]

        listTimes = []
        while len(tms) >= 1:

            # NEED TO DEAL WITH TIES HERE
            # SAME TIME FOR LAST PROBLEM SOLVED
            #   E.G. Team 1, Solved 3, [1,3,249]
            #        Team 2, Solved 3, [2,2,249]
            #        Team 3, Solved 3, [1,2,250]
            # Should be Team 1,2,3
            lastSolved = [ ( x, probs[x].pop(-1), curRank ) for x in tms if len(probs[x]) >= 1 ]
            lastSolved = sorted( lastSolved, key=lambda x:x[1], reverse=True )

            #####################
            lastSolved = tieBreak(lastSolved)
            # print(lastSolved)

            # print(lastSolved)
            # print("Done")
            # print(lastSolved, tms)

            # If there are no more tiebreakers, append the tied teams
            if len(lastSolved) == 0:
                listTimes += [ x for x in tempListTimes if x[0] in tms ]
                break

            # Sort by team name
            lastSolved = sorted(lastSolved,key=lambda x: (x[2],x[0]))

            tempCount = 0
            while( len(lastSolved) >= 1 ):
                temp = lastSolved.pop(0)
                tms.remove( temp[0] )
                print( str(temp[2]).ljust(4), str(temp[0]).ljust(4), str(num[temp[0]]).rjust(3), str(time[temp[0]]).rjust(5), sep="" )
                tempCount += 1

        curRank += tempCount
        if curRank > NR:
            break

        # Sort by team number
        listTimes = sorted(listTimes, key=lambda x:x[0])

        tempCount = 0
        while len(listTimes) >= 1:
            temp = listTimes.pop(0)
            print( str(curRank).ljust(4), str(temp[0]).ljust(4), str(num[temp[0]]).rjust(3), str(time[temp[0]]).rjust(5), sep="" )
            tempCount += 1
            
        curRank += tempCount
