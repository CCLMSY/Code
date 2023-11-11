# -*- coding: utf-8 -*-

import random

matix = [[0 for i in range(4)] for i in range(4)] #初始化生成一个二维列表
score = 0 #score记录游戏分数

#print(matix)

def display():
    print(' \033[1;31;42m 欢迎进入 2048 小游戏  \033[0m')
    print('\r'
          '┌────┬────┬────┬────┐\n'
          '|%4s|%4s|%4s|%4s|\n'
          '├────┬────┬────┬────┤\n'
          '|%4s|%4s|%4s|%4s|\n'
          '├────┬────┬────┬────┤\n'
          '|%4s|%4s|%4s|%4s|\n'
          '├────┬────┬────┬────┤\n'
          '|%4s|%4s|%4s|%4s|\n'
          '└────┴────┴────┴────┘'
    
        % (ifzero (matix[0][0]), ifzero(matix[0][1]),
           ifzero (matix[0][2]), ifzero(matix[0][3]),
           ifzero (matix[1][0]), ifzero(matix[1][1]),
           ifzero (matix[1][2]), ifzero(matix[1][3]),
           ifzero (matix[2][0]), ifzero(matix[2][1]),
           ifzero (matix[2][2]), ifzero(matix[2][3]),
           ifzero (matix[3][0]), ifzero(matix[3][1]),
           ifzero (matix[3][2]), ifzero(matix[3][3]),)
        )
    print('\033[1;31;47m 得分:%s  \033[0m' %  (score))

def ifzero(s):
    return str(s) if s != 0 else ''

def init():
    initNumFlag = 0
    while True:
        k = 2 if random.randrange(0,10) > 1 else 4  #随机生成2或4
        s = divmod(random.randrange(0,16),4)  #生成矩阵初始化的下标
        if matix[s[0]][s[1]] == 0:  #只有当其值不为 0 时才赋值,避免第二个值重复
            matix[s[0]][s[1]] = k
            initNumFlag += 1
            if initNumFlag == 2:
                break
    display()

    
def moveRight():
    global score
    for i in range(4):
        for j in range(3,0,-1):
            for k in range(j - 1,-1,-1):
                if matix[i][k] > 0:
                    if matix[i][j] == 0:
                        if k > 0 and matix[i][k] == matix[i][k - 1]:
                            matix[i][k] *= 2
                            score += matix[i][k]  #将当前数作为 score 加上
                            matix[i][k - 1] = 0
                        if k == 2 and matix[i][k - 1] == 0 and \
                            matix[i][k] == matix[i][k - 2]:
                            matix[i][k] *= 2
                            score += matix[i][k]
                            matix[i][k - 2] = 0
                        matix[i][j] = matix[i][k]
                        matix[i][k] = 0
                    elif matix[i][j] == matix[i][k]:
                        matix[i][j] *= 2
                        score += matix[i][j]
                        matix[i][k] = 0
                    break

def moveLeft():
    global score
    for i in range(4):
        for j in range(3):
            for k in range(j + 1, 4):
                if matix[i][k] > 0:
                    if matix[i][j] == 0:
                        if k < 3 and matix[i][k] == matix[i][k + 1]:
                            matix[i][k] *= 2
                            score += matix[i][k]
                            matix[i][k + 1] = 0
                        if k == 1 and matix[i][k + 1] == 0 and \
                            matix[i][k] == matix[i][k + 2]:
                            matix[i][k] *= 2
                            score += matix[i][k]
                            matix[i][k + 2] = 0
                        matix[i][j] = matix[i][k]
                        matix[i][k] = 0
                    elif matix[i][j] == matix[i][k]:
                        matix[i][j] *= 2
                        score += matix[i][j]
                        matix[i][k] = 0
                    break

def moveUp():
    global score
    for j in range(4):
        for i in range(3):
            for k in range(i + 1, 4):
                if matix[k][j] > 0:
                    if matix[i][j] == 0:
                        if k < 3 and matix[k][j] == matix[k + 1][j]:
                            matix[k][j] *= 2
                            score += matix[k][j]
                            matix[k + 1][j] = 0
                        if k == 1 and matix[k + 1][j] == 0 and \
                            matix[k][j] == matix[k + 2][j]:
                            matix[k][j] *= 2
                            score += matix[k][j]
                            matix[k + 2][j] = 0
                        matix[i][j] = matix[k][j]
                        matix[k][j] = 0
                    elif matix[i][j] == matix[k][j]:
                        matix[i][j] *= 2
                        score += matix[i][j]
                        matix[k][j] = 0
                    break

def moveDown():
    global score
    for j in range(4):
        for i in range(3, -1, -1):
            for k in range(i - 1, -1, -1):
                if matix[k][j] > 0:
                    if matix[i][j] == 0:
                        if k > 0 and matix[k][j] == matix[k - 1][j]:
                            matix[k][j] *= 2
                            score += matix[k][j]
                            matix[k - 1][j] = 0
                        if k == 2 and matix[k - 1][j] == 0 and \
                            matix[k][j] == matix[k - 2][j]:
                            matix[k][j] *= 2
                            score += matix[k][j]
                            matix[k - 2][j] = 0
                        matix[i][j] = matix[k][j]
                        matix[k][j] = 0
                    elif matix[i][j]==matix[k][j]:
                        matix[i][j]*=2
                        score+=matix[i][j]
                        matix[k][j]=0
                    break


def addRandomNum() :
    
    # 检查矩阵是否已满
    if all(matix[i][j] != 0 for i in range(4) for j in range(4)):
        display()
        return
    
    while True :
        k = 2 if random.randrange(0, 10) > 1 else 4
        s = divmod(random.randrange(0, 16), 4)
        if matix[s[0]][s[1]] == 0:
            matix[s[0]][s[1]] = k
            break
    display()
    
def checkOver():
    for i in range(4) :
        for j in range(3):
            if matix[i][j] == 0 or (j+1<4 and (matix[i][j] == matix[i][j + 1] or \
                matix[j][i] == matix[j + 1][i])):
                    return True
    return False

def main():
    flag = True
    init()
    while flag:  #循环标志
        d = input('\033[1;36;1m W:上 S:下 A:左 D:右 Q:退出 :\033[0m')
        if d == 'A':  # 左移
            moveLeft()
        elif d == 'S':  # 下移
            moveDown()
        elif d == 'W':  # 上移
            moveUp()
        elif d == 'D':  # 右移
            moveRight()
        elif d == 'Q':  # 退出
            break
        else:  # 对用户的其他输入不处理
            continue
        addRandomNum()
        if not checkOver():
            print('游戏结束')
            flag = False

if __name__ == '__main__':
    main()

