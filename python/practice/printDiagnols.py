class Solution:
    def getDiagnol(self, A, x, y):
        ret = []
        while (x >= 0 and y < len(A)):
            print("x and y are: ",x,y)
            ret.append(A[y][x])
            x -= 1
            y += 1
        return ret
        
    # @param A : list of list of integers
    # @return a list of list of integers
    def diagonal(self, A):
        x = 0
        y = 0
        ret = []
        temp = []
        
        while (x < len(A[0]) or y < len(A)):
            if(x < len(A[0])):
                temp = self.getDiagnol(A, x, y)
                x = x + 1
            else:
                y = y + 1
                temp = self.getDiagnol(A, x-1, y)
            
            print("cur ret is: ", ret)
            ret.append(temp)
            
        return ret

A = [
  [1, 2, 3],
  [4, 5, 6],
  [7, 8, 9],

]

b = Solution()
b.diagonal(A)
