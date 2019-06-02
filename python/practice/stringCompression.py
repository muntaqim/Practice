# given a string that looks like this: aabbbcddddd 
# output should be a2b3c1d5. Return original if compressed version is longer

def compress(string):
    finalString=""
    curCount = 0
    curLetter= string[0]

    for letter in string:
        if letter != curLetter:
            # write curLetter to final string along with
            # count
            finalString += (curLetter + str(curCount))
            curCount = 0
            curLetter = letter
        
        curCount+=1
    
    # for the last string need this extra condition
    finalString += (curLetter + str(curCount))
    curCount = 0
    curLetter = letter

    print(finalString)
    if len(finalString) < len(string):
        return finalString
    else:
        return string

if __name__ == "__main__":
    inp = "aabbbcddddd"
    print("final string is: {}".format(compress(inp)))
