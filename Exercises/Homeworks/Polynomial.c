#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <stdbool.h>

// 定义多项式的结构体
typedef struct Polynomial{
    int k;  // 系数
    int exp;     // 指数
    Polynomial *next;  // 指向下一个节点的指针
} Polynomial;

const int N=1000;
Polynomial *F[N];  // 用于存储多项式的数组
//存储结构：头指针->头节点（无数据）->节点1->节点2->...->节点n，按指数从大到小排列
int n=0;  // 多项式的个数

// 函数声明
void Print_Msg(); // 输出提示信息
void Print_Poly(Polynomial *poly); // 输出多项式（不带格式符）
    void Print_Poly_i(int i); // 输出第i个多项式
    void Print_All_Poly(); // 输出当前所有多项式
void Insert_Node(Polynomial *poly, int k, int exp); // 在多项式poly中插入项
    void Create_Poly(); // 新建多项式
void Delete_Poly(Polynomial *poly); // 删除多项式
    void Delete_Ploy_i(int i); // 删除第i个多项式
void Add_Polys(int i,int j); // 两个多项式相加
void Sub_Polys(int i,int j); // 两个多项式相减
void Mul_Polys(int i,int j); // 两个多项式相乘

// 输出提示信息
void Print_Msg() {
    printf("请输入操作：\n");
    printf("1. 输入多项式\n");
    printf("2. 查询第i个多项式\n");
    printf("3. 查询当前所有多项式\n");
    printf("4. 删除第i个多项式\n");
    printf("5. 两个多项式相加\n");
    printf("6. 两个多项式相减\n");
    printf("7. 两个多项式相乘\n");
    printf("8. 退出\n");
}

// 输出多项式（不带格式符）
void Print_Poly(Polynomial *poly) {
    poly=poly->next;
    if(poly==NULL) {
        printf("0");
        return;
    }
    bool f = false;
    while (poly != NULL) {
        if(f) printf(" + ");
        if(poly->k != 1 ) printf("%d", poly->k);
        else if(poly->exp == 0) printf("%d", poly->k);
        if(poly->exp != 0) printf("x");
        if(poly->exp != 1 && poly->exp != 0) printf("^%d", poly->exp);
        poly = poly->next;
        f = true;
    }
}
// 输出第i个多项式
void Print_Poly_i(int i) {
    if(i<=0 || i>n) {
        printf("第%d个多项式不存在！\n",i);
        return;
    }
    printf("第%d个多项式：\t", i);
    Print_Poly(F[i]);
    printf("\n");
}
// 输出当前所有多项式
void Print_All_Poly() { for(int i=1; i<=n; i++) Print_Poly_i(i);}

// 插入项
void Insert_Node(Polynomial *ploy, int k, int exp) {
    if(k==0) return;
    Polynomial *t = ploy->next;
    while (t != NULL) {
        if(t->exp == exp) {
            t->k += k;
            if(t->k == 0) {
                Polynomial *q = t->next;
                free(t);
                t = q;
            }
            return;
        }else if(t->exp < exp) {
            Polynomial *q = (Polynomial *)malloc(sizeof(Polynomial));
            q->k = k;
            q->exp = exp;
            q->next = t->next;
            t->next = q;
            return;
        }
        t = t->next;
    }
    if(t == NULL) {
        Polynomial *q = (Polynomial *)malloc(sizeof(Polynomial));
        q->k = k;
        q->exp = exp;
        q->next = NULL;
        for(t=ploy; t->next!=NULL; t=t->next);
        t->next = q;
        return;
    }
}
// 新建多项式
void Create_Poly() {
    n++;
    printf("请输入多项式的系数和指数，以空格分隔。输入0 0结束：\n");
    F[n] = (Polynomial *)malloc(sizeof(Polynomial));
    F[n]->next = NULL;
    int tk, texp;
    while (1) {
        scanf("%d %d", &tk, &texp);
        if(tk==0 && texp==0) break;
        Insert_Node(F[n], tk, texp);
    }
    printf("已保存第%d个多项式：\t", n);
    Print_Poly(F[n]);
    printf("\n");
}

// 删除多项式
void Delete_Poly(Polynomial *poly) {
    Polynomial  *t;
    while (poly != NULL) {
        t = poly->next;
        free(poly);
        poly = t;
    }
}
// 删除第i个多项式
void Delete_Ploy_i(int i) {
    if(i<=0 || i>n) {
        printf("第%d个多项式不存在！\n",i);
        return;
    }
    Delete_Poly(F[i]);
    for(int j=i; j<n; j++) F[j]=F[j+1];
    n--;
}

// 两个多项式相加
void Add_Polys(int i, int j) {
    if(i<=0 || i>n) {
        printf("第i=%d个多项式不存在！\n",i);
        return;
    }else if(j<=0 || j>n) {
        printf("第j=%d个多项式不存在！\n",j);
        return;
    }
    Polynomial *p = F[i]->next, *q = F[j]->next;
    Polynomial *t = (Polynomial *)malloc(sizeof(Polynomial));
    t->next = NULL;
    while (p!=NULL && q!=NULL) {
        if(p->exp == q->exp) {
            Insert_Node(t, p->k+q->k, p->exp);
            p = p->next;
            q = q->next;
        }else if(p->exp > q->exp) {
            Insert_Node(t, p->k, p->exp);
            p = p->next;
        }else {
            Insert_Node(t, q->k, q->exp);
            q = q->next;
        }
    }
    while (p != NULL) {
        Insert_Node(t, p->k, p->exp);
        p = p->next;
    }
    while (q != NULL) {
        Insert_Node(t, q->k, q->exp);
        q = q->next;
    }
    printf("第%d个多项式与第%d个多项式相加的结果为：\t", i, j);
    Print_Poly(t);printf("\n");

    char c;getchar();
    while(c!='y'&&c!='n'&&c!='Y'&&c!='N'){
        printf("是否保存该结果？(y/n)");
        scanf("%c", &c);
    }
    if(c=='y'||c=='Y') {
        n++;F[n]=t;
        printf("已保存第%d个多项式：\t", n);
        Print_Poly(t);printf("\n");
        return ;
    }Delete_Poly(t);
}

// 两个多项式相减
void Sub_Polys(int i,int j) {
    if(i<=0 || i>n) {
        printf("第i=%d个多项式不存在！\n",i);
        return;
    }else if(j<=0 || j>n) {
        printf("第j=%d个多项式不存在！\n",j);
        return;
    }
    Polynomial *p = F[i]->next, *q = F[j]->next;
    Polynomial *t = (Polynomial *)malloc(sizeof(Polynomial));
    t->next = NULL;
    while (p!=NULL && q!=NULL) {
        if(p->exp == q->exp) {
            Insert_Node(t, p->k-q->k, p->exp);
            p = p->next;
            q = q->next;
        }else if(p->exp > q->exp) {
            Insert_Node(t, p->k, p->exp);
            p = p->next;
        }else {
            Insert_Node(t, -q->k, q->exp);
            q = q->next;
        }
    }
    while (p != NULL) {
        Insert_Node(t, p->k, p->exp);
        p = p->next;
    }
    while (q != NULL) {
        Insert_Node(t, -q->k, q->exp);
        q = q->next;
    }
    printf("第%d个多项式与第%d个多项式相减的结果为：\t", i, j);
    Print_Poly(t);printf("\n");
    char c;getchar();
    while(c!='y'&&c!='n'&&c!='Y'&&c!='N'){
        printf("是否保存该结果？(y/n)");
        scanf("%c", &c);
    }
    if(c=='y'||c=='Y') {
        n++;F[n]=t;
        printf("已保存第%d个多项式：\t", n);
        Print_Poly(t);printf("\n");
        return  ;
    }
    Delete_Poly(t);
}

// 两个多项式相乘
void Mul_Polys(int i,int j) {
    if(i<=0 || i>n) {
        printf("第i=%d个多项式不存在！\n",i);
        return;
    }else if(j<=0 || j>n) {
        printf("第j=%d个多项式不存在！\n",j);
        return;
    }
    Polynomial *p = F[i]->next, *q = F[j]->next;
    Polynomial *t = (Polynomial *)malloc(sizeof(Polynomial));
    t->next = NULL;
    while (p != NULL) {
        Polynomial *tp = q;
        while (tp != NULL) {
            Insert_Node(t, p->k*tp->k, p->exp+tp->exp);
            tp = tp->next;
        }
        p = p->next;
    }
    printf("第%d个多项式与第%d个多项式相乘的结果为：\t", i, j);
    Print_Poly(t);printf("\n");
    char c;getchar();
    while(c!='y'&&c!='n'&&c!='Y'&&c!='N'){
        printf("是否保存该结果？(y/n)");
        scanf("%c", &c);
    }
    if(c=='y'||c=='Y') {
        n++;F[n]=t;
        printf("已保存第%d个多项式：\t", n);
        Print_Poly(t);printf("\n");
        return ;
    }
    Delete_Poly(t);
}

int main(){
    int x=1;
    while(x) {
        Print_Msg();
        int op,i,j;
        scanf("%d", &op);
        switch(op) {
            case 1:
                Create_Poly();
                break;
            case 2:
                printf("请输入要查询的多项式的编号：\n");
                scanf("%d", &i);
                Print_Poly_i(i);
                break;
            case 3:
                Print_All_Poly();
                break;
            case 4:
                Print_All_Poly();
                printf("请输入要删除的多项式的编号：\n");
                scanf("%d", &i);
                Delete_Ploy_i(i);
                break;
            case 5:
                Print_All_Poly();
                printf("请输入要相加的两个多项式的编号：\n");
                scanf("%d %d", &i, &j);
                Add_Polys(i, j);
                break;
            case 6:
                Print_All_Poly();
                printf("请输入要相减的两个多项式的编号：\n");
                scanf("%d %d", &i, &j);
                Sub_Polys(i, j);
                break;
            case 7:
                Print_All_Poly();
                printf("请输入要相乘的两个多项式的编号：\n");
                scanf("%d %d", &i, &j);
                Mul_Polys(i, j);
                break;
            case 8:
                return 0;
            default:
                printf("输入错误！\n");
                break;
        }
        printf("\n");
    }
}