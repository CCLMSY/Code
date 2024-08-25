import sys

def read():
    s = 0
    w = 1
    ch = sys.stdin.read(1)
    while ch < '0' or ch > '9':
        if ch == '-':
            w = -1
        ch = sys.stdin.read(1)
    while ch >= '0' and ch <= '9':
        s = s * 10 + ord(ch) - ord('0')
        ch = sys.stdin.read(1)
    return s * w

coef = [-20,-10,0,10,20]
complete = [0] * 6
base = [[[] for _ in range(6)] for _ in range(6)]
afriend = [0] * 13
adrive = [0] * 13
atrain = [0] * 13
ans = [0] * 6
fm = [1] * 6
mul = [0] * 6
ext = [[0] * 6 for _ in range(13)]

base[1][0] = [10, 0, 5, 0, 0, 2]
base[1][1] = [0, 9, 0, 4, 0, 2]
base[1][2] = [0, 5, 8, 0, 0, 2]
base[1][3] = [4, 0, 4, 8, 0, 2]
base[1][4] = [2, 0, 0, 0, 9, 4]

for i in range(5):
    base[2][i] = base[1][i][:]
    base[2][i][i] += 1

for i in range(5):
    base[3][i] = base[2][i][:]
    base[3][i][i] += 1

base[3][2][1] += 1
base[3][4][0] += 1

for i in range(5):
    base[4][i] = base[3][i][:]
    base[4][i][i] += 1

for i in range(5):
    base[5][i] = base[4][i][:]
    base[5][i][i] += 1

base[5][2][1] += 1
base[5][4][0] += 1
base[5][3][0] += 1
base[5][3][2] += 1

ans[5] = 120
for i in range(5):
    ans[i] = read()

for i in range(5):
    mul[i] = read()

for i in range(1, 7):
    afriend[i] = read()
    adrive[i] = read()
    atrain[i] = read()
    for j in range(5):
        ans[j] += read()
    for j in range(5):
        ext[i][j] = read()

for i in range(6):
    ans[i] = min(ans[i], 1200)

T = read()
while T > 0:
    summer = read()
    weight = read()
    drive = read()
    type = read()
    lv = 5
    spresent = 100
    sfriend = 100
    strain = 100
    sdrive = 100
    fm1=100
    fm2=100
    fm3=100
    fm4=100
    if not summer:
        lv = min(5, complete[type] // 4 + 1)
    arr = base[lv][type][:]
    fm = [1,1,1,1,1,1]
    for Z in range(read()):
        x = read()
        y = read()
        for i in range(6):
            arr[i] += ext[x][i]
        spresent += 5
        if y:
            sfriend *= 100 + afriend[x]
            fm2 *= 100
        strain += atrain[x]
        sdrive += adrive[x]

    if weight:
        arr[0] = 0

    sdrive = 100 * fm4 + coef[drive] * sdrive
    fm4*=100

    for i in range(6):
        arr[i] *= sfriend * strain * sdrive * spresent
        fm[i] *= fm1*fm2*fm3*fm4
        arr[i] *= (100 + mul[i])
        fm[i]*=100
        ans[i] = ans[i] + (arr[i]//fm[i])
        if i != 5:
            ans[i] = min(ans[i], 1200)
        print(ans[i], end=" ")
    print("")
    if not summer:
        complete[type] += 1
    T -= 1
