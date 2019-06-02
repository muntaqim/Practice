class Node:
    def __init__(self, value=0):
        self.value = value
        self.next = None
    def printList(self):
        cur = self
        while (cur != None):
            printString = str(cur.value) + "->"
            print(printString, end='')
            cur = cur.next
        print()

def numToLinkedList(num):
    head = None
    #so we can return the actual head
    returnHead = None
    while (num):
        curNode = Node(num%10)
        if head == None:
            head = curNode
            returnHead = curNode
        else:
            head.next = curNode
            head = head.next
        num = num//10
    return returnHead

if __name__=="__main__":
    firstNum = int(input("Enter first num: "))
    secondNum = int(input("Enter second num: "))

    l1 = numToLinkedList(firstNum)
    l2 = numToLinkedList(secondNum)
    l1.printList()
    l2.printList()

