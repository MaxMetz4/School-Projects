#I, Max Metzner pledge my honor that I have abided by the stevens honor system
#Lab assignment 9/12/19
def myLength(A): 
    x = 0
    for i in A: 
        x = x + 1
    return x
'''this function works like len()'''

def dotProduct(L,K):
    if myLength(L) == 0:
        return 0.0
        '''base case for empty list'''
    x = L[0]*K[0]
    '''dot product multiplication'''
    return x + dotProduct(L[1:],K[1:])
    '''adds them all together recursively'''
    
def expand(S):
    if myLength(S) == 0:
        return []
        '''base case for empty list'''
    else:
        return list(S[0])+ expand(S[1:])
        '''splits each letter into separate lists'''

def deepMember(e,L):
    if myLength(L) == 0:
        return False
        '''base case for when e is not in the list'''
    elif isinstance(L[0], list) == True:
        return deepMember(e,L[0])
        '''if its a list then go into the sublist'''
    elif L[0] == e:
        return True
        '''identifies the desired character "e" in the list'''
    else:
        return deepMember(e,L[1:])
        '''otherwise, keep going through list'''

def removeAll(e, L):
    if e in L:
        if e == L[0]:
            return L[1:]
            '''if there is e in the list, return the rest of the list without e'''
        else:
            return removeAll(e,L[1:])
            '''recurses the function'''
    else:            
        return L
        '''return any characters that aren't e'''

def deepReverse(L):
    if L == []:
        return L
        '''base case that returns L'''
    if isinstance(L,list) == False:
        return L
        '''makes sure object in list is not a list'''
    else:
        return deepReverse(L[1:])+[deepReverse(L[0])]
        '''returns list in backwards order'''
