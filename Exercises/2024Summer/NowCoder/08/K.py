pat1 = 'ava'
pat2 = 'avava'

T = int(input())
for _ in range(T):
    s = input()
    i = 0
    while i < len(s):
        if i+5<=len(s) and s[i:i+5] == pat2:
            i += 5
        elif i+3<=len(s) and s[i:i+3] == pat1:
            i += 3
        else:
            print('No')
            break
    else:
        print('Yes')