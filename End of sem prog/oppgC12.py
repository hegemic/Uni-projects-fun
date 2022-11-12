def printNonZero(dictionary):   #Exercise 3
    for num in dictionary:
        if dictionary[num] != 0:
            print(num,':',dictionary[num])

def getConstituencies(filename):    #Exercise 6
    voteFile = open(filename)
    cString = '_Constituency:'
    constituencies = set()
    for p in voteFile:
        if cString in p:
            p = p.replace(cString, '')
            p = p.replace('\n', '')
            constituencies.add(p)
    return constituencies

def getParties(filename):   #Exercise 7
    voteFile = open(filename)
    checkString = '_'
    parties = set()
    for l in voteFile:
        if checkString not in l and l.strip():
            lSplit = l.split(':')
            party = lSplit[0].strip()
            parties.add(party)
    return parties
    
def getVotesForConstituency(filename, constituency):    #Exercise 8
    voteFile = open(filename, 'r')
    votes = {}
    while 1:
        newLine = voteFile.readline()
        if constituency in newLine:
            for v in range(2):
                newLine = voteFile.readline()
            while newLine.strip():
                newSplit = newLine.split(':')
                party = newSplit[0].strip()
                vote = int(newSplit[1])
                votes[party] = vote
                newLine = voteFile.readline()
            break
    return votes

def getTotalSeats(filename, method):
    seats = {}
    tempSeats = {}
    constituencies = getConstituencies(filename)
    parties = getParties(filename)
    for p in parties:
        seats[p] = 0
        tempSeats[p] = 0
    for c in constituencies:
        votes = getVotesForConstituency(filename, c)
        quot = {}
        for v in votes:
            if method == 'D':
                mp = 1;
            else:
                mp = 2;
            quot[v] = votes.get(v)/(mp*tempSeats[v]+1)
            voteFile = open(filename, 'r')
        while 1:
            newLine = voteFile.readline()
            if c in newLine:
                cSeats = voteFile.readline().split(':')[1].strip()
                break
        for i in range(int(cSeats)):
            max = 0
            for k in quot:
                if quot[k] > max:
                    max = quot[k]
                    maxKey = k
            seats[maxKey] += 1
            tempSeats[maxKey] += 1
            quot[maxKey] = votes.get(maxKey)/(mp*tempSeats[maxKey]+1)
        for p in parties:
            tempSeats[p] = 0
        quot = {}
    return seats

seatsD = getTotalSeats('ukeu2019.txt','D')
seatsS = getTotalSeats('ukeu2019.txt','S')
printNonZero(seatsD)
print('------')
printNonZero(seatsS)

