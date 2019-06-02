def word_count(i):
    d ={}
    for word in i.split(" "):
        word = word.lower()
        if word in d:
            d[word]+=1
        else:
            d[word]=1

    return d

def most_courses(dic):
    name=None
    curMax=0
    
    for teacher in dic:
        if (curMax < len(dic[teacher]):
            curMax=len(dic[teacher])
            name = teacher
            
    return name



dic = {'Andrew Chalkley': ['jQuery Basics', 'Node.js Basics','hello'],
       'Kenneth Love': ['Python Basics', 'Python Collections']}

my_string = "I do not like it Sam I Am"
print(most_courses(dic))
