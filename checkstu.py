stu = []
with open('stu.txt','r') as f:
    lines = f.readlines()
    for line in lines:
        stu.append(line.strip())
    print(f'\033[32m\033[1mLOADED\33[0m')

while 1:
    new = input().strip()
    if not new:
        break
    if new in stu:
        print(f'\033[31m\033[1mWarning:{new}\33[0m')
        continue
    stu.append(new)
    print(f'\033[32m\033[1mPASS\33[0m')

with open('stu.txt','w',encoding='utf-8') as f:
    stu.sort()
    f.write('\n'.join(stu))
    print(f'\033[32m\033[1mSAVED\33[0m')

