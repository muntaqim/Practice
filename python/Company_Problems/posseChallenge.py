################################################################
# Description: This app will return the password after consuming
#              JSON documents from a given URL
#
################################################################
#!/usr/bin/python3
import requests
import json

# class to represent the various attributes of a posse card
class PosseCard:
    def __init__(self, st):
        self.len = len(st)
        self.case = self.findCase(st[1])
        self.letter = self.findLetter(st[1])
        self.prefix = st[0]

    def findLetter(self, ch):
        if ch == "a" or ch == "A" or ch == "Ä":
            return "a"
        
        elif ch == "u" or ch == "U" or ch == "Ü":
            return "u"

        return "o"

    def findCase(self, ch):
        if ch == "a" or ch == "o" or ch =="u":
            return "lower"

        elif ch == "A" or ch == "O" or ch == "U":
            return "upper"

        return "umlaut"

    def __str__(self):
        return "len is {}, case is {}, letter is {}, predix is {}".format(self.len,self.case,self.letter,self.prefix)

    @staticmethod
    def compare3(first, second, third):

        #ensure lens are all either the same or they are all different
        if(not (first.len == second.len and first.len == third.len and second.len == third.len) and
            not (first.len != second.len and first.len != third.len and second.len != third.len)):
            return False

        #ensure case are all either the same or they are all different
        if(not (first.case == second.case and first.case == third.case and second.case == third.case) and
            not (first.case != second.case and first.case != third.case and second.case != third.case)):
            return False


        #ensure letters are all either the same or they are all different
        if(not (first.letter == second.letter and first.letter == third.letter and second.letter == third.letter) and
            not (first.letter != second.letter and first.letter != third.letter and second.letter != third.letter)):
            return False


        #ensure prefix are all either the same or they are all different
        if(not (first.prefix == second.prefix  and first.prefix  == third.prefix  and second.prefix  == third.prefix ) and
            not (first.prefix != second.prefix  and first.prefix  != third.prefix  and second.prefix  != third.prefix )):
            return False

        return True

    @staticmethod
    def findPosse(curCards):
        # algorithm will be n^3. basically going through all combinations untill 
        # a set is found that is compatible

        #potentially can be sped up first comparing the first two pick and then narrowing
        #down what attributes need to be in the third one to make a set.

        #Maybe a dictionary can be used to group cards based on attribute

        for i in range(len(curCards)):
            for j in range(i+1,len(curCards)):
                    for k in range(j+1,len(curCards)):
                        if(PosseCard.compare3(curCards[i], curCards[j], curCards[k])):
                            return [i, j, k]


# main function that communicates with the given endpoint
def posseChallenge():
    start = "https://enigmatic-hamlet-4927.herokuapp.com/posse"
    r = requests.post(url = start)

    start_json = json.loads(r.text)

    boardID = start_json['id']
    board = start_json['board']
    
    password = ""
    # infinite loop for simplicity
    while (1):
        #turn everything into a card
        curCards = [PosseCard(st) for st in board]
        
        # find a posse
        posse = PosseCard.findPosse(curCards)
        
        possePost = []
        for i in posse:
            possePost.append(board[i])
        
        foundPosse = {"posse": possePost}
        
        # POST the found posse
        posturl = "https://enigmatic-hamlet-4927.herokuapp.com/posse/" + boardID
        r = requests.post(url = posturl, data = json.dumps(foundPosse)) 
        j = json.loads(r.text)
        
        #if password is in the return data, stop
        if 'password' in j:
            password =  j['password']
            print(j['password'])
            break

        board = j['board']

    return password

if __name__ == "__main__":
    posseChallenge()
