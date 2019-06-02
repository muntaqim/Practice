a = None

class Node:
    def __init__(self, value=None, n=None):
        print ("here: {} {}".format(value,n))
        if (isinstance(value,Node)):
            self.n = value.n
            self.value = value.value
        else:
            self.n = n
            self.value = value


def create():
    b = Node(1)
    print ("new node is ",b)
    a = b


if __name__=="__main__":
    create()
    print ("a is ",a)
