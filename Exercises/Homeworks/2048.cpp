#include <iostream>
#include <vector>
#include <random>
#include <iomanip>
#include <algorithm>

using namespace std;

vector<vector<int>> matix(4, vector<int>(4, 0)); //初始化生成一个二维列表
int score = 0; //score记录游戏分数

void display() {
    cout << " \033[1;31;42m 欢迎进入 2048 小游戏  \033[0m" << endl;
    cout << "\r"
        "┌────┬────┬────┬────┐\n"
        "|" << setw(4) << (matix[0][0] == 0 ? "" : to_string(matix[0][0])) << "|"
        << setw(4) << (matix[0][1] == 0 ? "" : to_string(matix[0][1])) << "|"
        << setw(4) << (matix[0][2] == 0 ? "" : to_string(matix[0][2])) << "|"
        << setw(4) << (matix[0][3] == 0 ? "" : to_string(matix[0][3])) << "|\n"
        "├────┬────┬────┬────┤\n"
        "|" << setw(4) << (matix[1][0] == 0 ? "" : to_string(matix[1][0])) << "|"
        << setw(4) << (matix[1][1] == 0 ? "" : to_string(matix[1][1])) << "|"
        << setw(4) << (matix[1][2] == 0 ? "" : to_string(matix[1][2])) << "|"
        << setw(4) << (matix[1][3] == 0 ? "" : to_string(matix[1][3])) << "|\n"
        "├────┬────┬────┬────┤\n"
        "|" << setw(4) << (matix[2][0] == 0 ? "" : to_string(matix[2][0])) << "|"
        << setw(4) << (matix[2][1] == 0 ? "" : to_string(matix[2][1])) << "|"
        << setw(4) << (matix[2][2] == 0 ? "" : to_string(matix[2][2])) << "|"
        << setw(4) << (matix[2][3] == 0 ? "" : to_string(matix[2][3])) << "|\n"
        "├────┬────┬────┬────┤\n"
        "|" << setw(4) << (matix[3][0] == 0 ? "" : to_string(matix[3][0])) << "|"
        << setw(4) << (matix[3][1] == 0 ? "" : to_string(matix[3][1])) << "|"
        << setw(4) << (matix[3][2] == 0 ? "" : to_string(matix[3][2])) << "|"
        << setw(4) << (matix[3][3] == 0 ? "" : to_string(matix[3][3])) << "|\n"
        "└────┴────┴────┴────┘" << endl;
    cout << "\033[1;31;47m 得分:" << score << "  \033[0m" << endl;
}

void init() {
    int initNumFlag = 0;
    while (true) {
        int k = (rand() % 10 > 1) ? 2 : 4;  //随机生成2或4
        int s = rand() % 16;  //生成矩阵初始化的下标
        int i = s / 4, j = s % 4;
        if (matix[i][j] == 0) {  //只有当其值不为 0 时才赋值,避免第二个值重复
            matix[i][j] = k;
            initNumFlag += 1;
            if (initNumFlag == 2) {
                break;
            }
        }
    }
    display();
}

void moveRight() {
    for (int i = 0; i < 4; i++) {
        for (int j = 3; j > 0; j--) {
            for (int k = j - 1; k >= 0; k--) {
                if (matix[i][k] > 0) {
                    if (matix[i][j] == 0) {
                        if (k > 0 && matix[i][k] == matix[i][k - 1]) {
                            matix[i][k] *= 2;
                            score += matix[i][k];  //将当前数作为 score 加上
                            matix[i][k - 1] = 0;
                        }
                        if (k == 2 && matix[i][k - 1] == 0 &&
                            matix[i][k] == matix[i][k - 2]) {
                            matix[i][k] *= 2;
                            score += matix[i][k];
                            matix[i][k - 2] = 0;
                        }
                        matix[i][j] = matix[i][k];
                        matix[i][k] = 0;
                    }
                    else if (matix[i][j] == matix[i][k]) {
                        matix[i][j] *= 2;
                        score += matix[i][j];
                        matix[i][k] = 0;
                    }
                    break;
                }
            }
        }
    }
}

void moveLeft() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 3; j++) {
            for (int k = j + 1; k < 4; k++) {
                if (matix[i][k] > 0) {
                    if (matix[i][j] == 0) {
                        if (k < 3 && matix[i][k] == matix[i][k + 1]) {
                            matix[i][k] *= 2;
                            score += matix[i][k];
                            matix[i][k + 1] = 0;
                        }
                        if (k == 1 && matix[i][k + 1] == 0 &&
                            matix[i][k] == matix[i][k + 2]) {
                            matix[i][k] *= 2;
                            score += matix[i][k];
                            matix[i][k + 2] = 0;
                        }
                        matix[i][j] = matix[i][k];
                        matix[i][k] = 0;
                    }
                    else if (matix[i][j] == matix[i][k]) {
                        matix[i][j] *= 2;
                        score += matix[i][j];
                        matix[i][k] = 0;
                    }
                    break;
                }
            }
        }
    }
}

void moveUp() {
    for (int j = 0; j < 4; j++) {
        for (int i = 0; i < 3; i++) {
            for (int k = i + 1; k < 4; k++) {
                if (matix[k][j] > 0) {
                    if (matix[i][j] == 0) {
                        if (k < 3 && matix[k][j] == matix[k + 1][j]) {
                            matix[k][j] *= 2;
                            score += matix[k][j];
                            matix[k + 1][j] = 0;
                        }
                        if (k == 1 && matix[k + 1][j] == 0 &&
                            matix[k][j] == matix[k + 2][j]) {
                            matix[k][j] *= 2;
                            score += matix[k][j];
                            matix[k + 2][j] = 0;
                        }
                        matix[i][j] = matix[k][j];
                        matix[k][j] = 0;
                    }
                    else if (matix[i][j] == matix[k][j]) {
                        matix[i][j] *= 2;
                        score += matix[i][j];
                        matix[k][j] = 0;
                    }
                    break;
                }
            }
        }
    }
}

void moveDown() {
    for (int j = 0; j < 4; j++) {
        for (int i = 3; i >= 0; i--) {
            for (int k = i - 1; k >= 0; k--) {
                if (matix[k][j] > 0) {
                    if (matix[i][j] == 0) {
                        if (k > 0 && matix[k][j] == matix[k - 1][j]) {
                            matix[k][j] *= 2;
                            score += matix[k][j];
                            matix[k - 1][j] = 0;
                        }
                        if (k == 2 && matix[k - 1][j] == 0 &&
                            matix[k][j] == matix[k - 2][j]) {
                            matix[k][j] *= 2;
                            score += matix[k][j];
                            matix[k - 2][j] = 0;
                        }
                        matix[i][j] = matix[k][j];
                        matix[k][j] = 0;
                    }
                    else if (matix[i][j] == matix[k][j]) {
                        matix[i][j] *= 2;
                        score += matix[i][j];
                        matix[k][j] = 0;
                    }
                    break;
                }
            }
        }
    }
}

void addRandomNum() {
    // 检查矩阵是否已满
    if (all_of(matix.begin(), matix.end(), [](vector<int>& row) {
        return all_of(row.begin(), row.end(), [](int& num) {
            return num != 0;
        });
    })) {
        display();
        return;
    }

    while (true) {
        int k = (rand() % 10 > 1) ? 2 : 4;
        int s = rand() % 16;
        int i = s / 4, j = s % 4;
        if (matix[i][j] == 0) {
            matix[i][j] = k;
            break;
        }
    }
    display();
}

bool checkOver() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 3; j++) {
            if (matix[i][j] == 0 || (j + 1 < 4 && (matix[i][j] == matix[i][j + 1] ||
                matix[j][i] == matix[j + 1][i]))) {
                return true;
            }
        }
    }
    return false;
}

void _main() {
    bool flag = true;
    init();
    while (flag) {  //循环标志
        char d;
        cout << "\033[1;36;1m W:上 S:下 A:左 D:右 Q:退出 :\033[0m";
        cin >> d;
        if (d == 'A') {  // 左移
            moveLeft();
        }
        else if (d == 'S') {  // 下移
            moveDown();
        }
        else if (d == 'W') {  // 上移
            moveUp();
        }
        else if (d == 'D') {  // 右移
            moveRight();
        }
        else if (d == 'Q') {  // 退出
            break;
        }
        else {  // 对用户的其他输入不处理
            continue;
        }
        addRandomNum();
        if (!checkOver()) {
            cout << "游戏结束" << endl;
            flag = false;
        }
    }
}

int main() {
    srand(time(nullptr));
    ::_main();
    return 0;
}
