########################################################################
# This app will consume data from an enpoint and print the password
# the main function of interest is readFromStream
########################################################################

import requests
import re
# -*- coding: utf-8 -*-
# used to find the letter and index hidden 
# in a chunk
def findLetterAndIndex(curChunk):
    #index is on the first line
    index = int(curChunk[0])
    letter = ""
    
    #parsing out the coordinates from the second line
    coord = list(map(int,re.findall(r'-?\d+',curChunk[1])))

    data = curChunk[2:]

    #coordinate system starts from botton so go to end
    #of array and then subtract to go up. Going right
    #is just normal index access
    letter = data[len(data) - coord[1] - 1][coord[0]]

    return letter,index

# reads from the given stream and then return the hidden
# password
def readFromStream():
    r = requests.get("https://afternoon-headland-69107.herokuapp.com", stream=True)
    
    i = 0
    
    #define a dictionary to keep track of password letters
    passwordLetters = dict()

    #chucks are seperate by new blank. This array will be used
    #to store lines for a chunk
    curChunk = []
    
    chunkCount = 0
    # read stream line by line
    for line in r.iter_lines():
        decoded_line = line.decode('utf-8')
        #blocks are seperated by newline 
        if(decoded_line == "" ):
            
            #process the chunk and return a letter
            #and the index it belongs to
            letter,index = findLetterAndIndex(curChunk)
            
            # check to see if we've seen this index before
            # the assumption is that we should see a certain
            # index at most twice since this is a rotating stream
            # if we see any index fot a third time, break out of
            # loop
            
            if index not in passwordLetters:
                passwordLetters[index] = [letter, 1]

            else:
                # do a sanity check to ensure the letters
                # that are recieved each time for a particular
                # index is the same
                if(letter != passwordLetters[index][0]):
                    raise Exception("letter doesn't match index")

                
                # keep track of how many times a index is seen
                passwordLetters[index][1]+=1

                #seeing for third time so we've already seen all
                #letters
                if(passwordLetters[index][1] == 3):
                    break;


            # reset the chunk after processing 
            # clean up
            curChunk = []
            chunkCount+=1
            continue

        curChunk.append(decoded_line)


    #find the max index value
    numElements = max(passwordLetters, key=int)
    
    #initialize array where we will store the final
    #password
    password = [0 for i in range(numElements + 1)]

    #use dict to do final mapping
    for key,val in passwordLetters.items():
        password[key] = val[0]

    password = "".join(password)

    #will just print the password
    print(password)

if __name__=="__main__":
    readFromStream()
