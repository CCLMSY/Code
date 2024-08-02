import re

def solve():
    n = int(input())
    s = input()
    s = re.sub('0+','0',s)
    # print(s)
    pat = '101'
    while re.search(pat,s):
        s = re.sub(pat,'1',s)
    while re.search('011',s):
        s = re.sub('011','1',s)
    while re.search('110',s):
        s = re.sub('110','1',s)
    if '0' in s:
        print('No')
    else :
        print('Yes')

if __name__ == '__main__':
    T = int(input())
    for _ in range(T):
        solve()