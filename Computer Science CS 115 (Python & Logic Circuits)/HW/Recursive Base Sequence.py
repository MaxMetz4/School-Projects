def LCS(S1, S2):
    '''return longest common substring'''
    if 0 == len(S1) or 0 == len(S2):
        return 0
    elif S1[0] == S2[0]:
        '''a common first character adds to LCS'''
        return 1 + LCS(S1[1:], S2[1:])
    else:
        '''drop either frst character and recurse'''
        return max(LCS(S1[1:], S2), LCS(S1, S2[1:]))
