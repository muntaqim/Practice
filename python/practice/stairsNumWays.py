def numWaysInternal(numStairs, numSteps, remember):
    totalWays = 0
    
    if numStairs == 0:
        return 1

    #we've already seen this so just return value
    if numStairs in remember:
        return remember[numStairs]
    
    #numSteps is a list of ways to step. Loop through this
    for step in numSteps:
        if(numStairs - step >= 0):
            totalWays += numWaysInternal(numStairs - step, 
                                         numSteps,
                                         remember)
    remember[numStairs] = totalWays
    return totalWays

def numWays(numStairs, numSteps):
    remember = dict()
    return numWaysInternal(numStairs, numSteps, remember)



print "number of ways is: " + str(numWays(3, [1,2]))
