#Extended programming exercise, Hege Michalsen 19026013

#Part A

def getTotal(dictionary):   #Exercise 1
    sum = 0
    for num in dictionary:
        sum += dictionary[num]
    return sum
    
def normalise(dictionary):  #Exercise 2
    total = getTotal(dictionary)
    for num in dictionary:
        dictionary[num] = dictionary[num]/total
    return dictionary

def printNonZero(dictionary):   #Exercise 3
    for num in dictionary:
        if dictionary[num] != 0:
            print(num,':',dictionary[num])

def analyse(votes, seats):  #Exercise 4
    normVotes = normalise(votes)
    normSeats = normalise(seats)
    votesKeys = list(votes.keys())
    seatsKeys = list(seats.keys())

    for i in range(len(seats)):
        if seats[seatsKeys[i]] > 0:
            percSeats = round(100 * normSeats[seatsKeys[i]],2)
            percVotes = round(100 * normVotes[votesKeys[i]],2)
            print(votesKeys[i],int(percVotes),'of votes vs',int(percSeats),'% seats')

def addTo(d1, d2):  #Exercise 5
    for key in d2:
        if key not in d1:
            d1[key] = d2[key]
        else:
            d1[key] += d2[key]
    return d1

#Part B

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
    voteFile = open(filename)
    votes = {}
    newLine = voteFile.readline()
    while newLine:
        if constituency in newLine:
            for v in range(2):
                newLine = voteFile.readline()
            while newLine.strip():
                newSplit = newLine.split(':')
                party = newSplit[0].strip()
                vote = int(newSplit[1])
                votes[party] = vote
                newLine = voteFile.readline()
            return votes
        newLine = voteFile.readline()
    return 0

def getTotalVotes(filename):    #Exercise 9    
    constituencies = getConstituencies(filename)
    totalVotes = {}
    for i in constituencies:
        votes = getVotesForConstituency(filename, i)
        totalVotes = addTo(totalVotes, votes)

    return totalVotes

def getTotalSeats(filename):    #Exercise 10
    seats = {}
    tempSeats = {}  #seats per constituency
    constituencies = getConstituencies(filename)
    parties = getParties(filename)
    for p in parties:
        seats[p] = 0
        tempSeats[p] = 0
    for c in constituencies:
        votes = getVotesForConstituency(filename, c)
        quot = {}
        for v in votes:
            quot[v] = votes.get(v)/(tempSeats[v]+1)
            voteFile = open(filename, 'r')
        newLine = voteFile.readline()
        while newLine:
            if c in newLine:
                cSeats = voteFile.readline().split(':')[1].strip()
                for i in range(int(cSeats)):
                    max = 0
                    for k in quot:
                        if quot[k] > max:
                            max = quot[k]
                            maxKey = k
                    seats[maxKey] += 1
                    tempSeats[maxKey] += 1
                    quot[maxKey] = votes.get(maxKey)/(tempSeats[maxKey]+1)  #v/(s+1)
            newLine = voteFile.readline()
        for p in parties:
            tempSeats[p] = 0
    return seats

"""
seats = getTotalSeats('ukeu2019.txt')
printNonZero(seats)
"""

