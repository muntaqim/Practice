def bubbleSort(a):
    for x in range(len(a)):
        for y in range(len(a)-x-1):
            if a[y] > a[y+1]:
                a[y],a[y+1] = a[y+1],a[y]

#returns the index with the minimum value
def findMinElement(a):
    curMinValue = a[0]
    curMinElement =  0
    for x in range(1,len(a)):
        if a[x] < curMinValue:
            curMinValue = a[x]
            curMinElement = x
    return curMinElement


def selectionSort(a):
    for x in range(len(a)-1):
        minElement = findMinElement(a[x:])
        a[x], a[minElement + x] = a[minElement + x], a[x]

a = [4,2,4,1,6,3,7,9,4,2]
selectionSort(a)
print(a)
