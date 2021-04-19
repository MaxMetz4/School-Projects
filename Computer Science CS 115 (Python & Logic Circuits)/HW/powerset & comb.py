def powerset(S):
    if not S:
        ans = [[]]
    else:
        loseIt = powerset(S[1:])
        useIt = list(map(lambda L: [S[0]] + L, loseIt))
        ans = useIt + loseIt
    return ans

def comb(S,k):
    if not k:
        ans = [[]]
    elif not S:
        ans = []
    else:
        loseIt = comb(S[1:],k)
        useIt = list(map(lambda T: [ S[0] ] + T, comb(S[1:], k-1)))
        ans = useIt + loseIt
    return ans
    
