#Extra programming challenge, part C

#Exercise 11

def getSeats(votes, nbrSeats, method='D'):
    seats = {}
    quot = {}
    if method == 'S':
        for party in votes:
            seats[party] = 0
        for round in range(0, nbrSeats):
            party = getWinner(votes, seats)
            seats[party] += 1

    elif method == 'D':
        for party in votes:
            seats[party] = 0
            quot[party] = votes.get(party)/(seats[party]+1)
        for i in range(nbrSeats):
            max = 0
            for k in quot:
                if quot[k] > max:
                    max = quot[k]
                    maxKey = k
            seats[maxKey] += 1
            quot[maxKey] = votes.get(maxKey) / (seats[maxKey] + 1)
    return seats


def getWinner(votes, seats):    #from week 9 code
    maxQuotient = -1
    for party in votes:
        quotient = getQuotient(party, votes, seats)
        if quotient > maxQuotient:
            winner = party
            maxQuotient = quotient
    return winner


def getQuotient(party, votes, seats):   #from week 9
    return votes[party] / (1 + 2*seats[party])


"""
votes = readVoteFile('ne_England.txt')
seatsD = getSeats(votes,3,'D')
seatsS = getSeats(votes,3,'S')
seats = getSeats(votes,3)
#print('D:',seatsD)
#print('S:',seatsS)
print(seats)
"""

#Exercise 12

def printNonZero(dictionary):   #From part A, exercise 3
    for num in dictionary:
        if dictionary[num] != 0:
            print(num,':',dictionary[num])

def getConstituencies(filename):    #From exercise 6
    voteFile = open(filename)
    cString = '_Constituency:'
    constituencies = set()
    for p in voteFile:
        if cString in p:
            p = p.replace(cString, '')
            p = p.replace('\n', '')
            constituencies.add(p)
    return constituencies

def getParties(filename):   #From exercise 7
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

def getTotalSeats(filename, method='D'):
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
                    quot[maxKey] = votes.get(maxKey)/(mp*tempSeats[maxKey]+1)
            newLine = voteFile.readline()

        for p in parties:
            tempSeats[p] = 0
        quot = {}
    return seats


seatsD = getTotalSeats('ukeu2019.txt','D')
seatsS = getTotalSeats('ukeu2019.txt','S')
printNonZero(seatsD)
print('------')
printNonZero(seatsS)


