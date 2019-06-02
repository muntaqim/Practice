class Letter:
    def __init__(self, pattern=None):
        self.pattern = pattern
        
    def __str__(self):
        returnString = ""
        for letter in self.pattern:
            if letter == ".":
                returnString += "dot-"
            elif letter == "_":
                returnString += "dash-"
        return returnString[:-1]    

class S(Letter):
    def __init__(self):
        pattern = ['.', '.', '.']
        super().__init__(pattern)
