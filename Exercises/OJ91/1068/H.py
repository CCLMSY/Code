import re
pat = [
    r'^(\d+)$', # C True
    r'^(\d+)/x$', # C/x True
    r'^(\d+)sinx$', # Csinx False
    r'^(\d+)cosx$', # Ccosx False
    r'^(\d+)/sinx$', # C/sinx False
    r'^(\d+)/cosx$', # C/cosx False
    r'^(\d+)x$', # Cx False
    r'^(\d+)\^x$', # C^x C?
]

n = int(input())
while n:
    n -= 1
    s = input()
    s = s.split(sep='+')
    cnt = [0, 0, 0, 0, 0, 0, 0, 0]
    fl = 1
    for i in s:
        for j in range(8):
            m = re.match(pat[j], i)
            if m:
                cnt[j]+=int(m.group(1))
    for k in range(8):
        if cnt[k]:
            fl=0
    print('YES' if fl else 'NO')

