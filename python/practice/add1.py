def plusOne(A):
    start = 0
    for elemNum,num in enumerate(A):
        if (num != 0):
            start = elemNum
            break
            
    inA = A[start:]
    out = [0] * (len(inA))
    remainder = 1
    

    for elemNum in reversed(range(len(out))):
        curNum = inA[elemNum]
        if(remainder and curNum != 9):
            out[elemNum] = curNum + 1
            remainder = 0
        elif(remainder and curNum == 9):
            out[elemNum] = 0
        else:
            out[elemNum] = curNum
            
    return out if not remainder else [1] + out


print (plusOne([9,9,9]))
