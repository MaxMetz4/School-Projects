def deepLength(L):
    if L == []:
        return 0
    if isinstance(L[0],list):
        return deepLength(L[1:]) + deepLength(L[0])
    else:
        return 1 + deepLength(L[1:])
