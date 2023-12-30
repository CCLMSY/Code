#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <stdbool.h>

// �������ʽ�Ľṹ��
typedef struct Polynomial{
    int k;  // ϵ��
    int exp;     // ָ��
    Polynomial *next;  // ָ����һ���ڵ��ָ��
} Polynomial;

const int N=1000;
Polynomial *F[N];  // ���ڴ洢����ʽ������
//�洢�ṹ��ͷָ��->ͷ�ڵ㣨�����ݣ�->�ڵ�1->�ڵ�2->...->�ڵ�n����ָ���Ӵ�С����
int n=0;  // ����ʽ�ĸ���

// ��������
void Print_Msg(); // �����ʾ��Ϣ
void Print_Poly(Polynomial *poly); // �������ʽ��������ʽ����
    void Print_Poly_i(int i); // �����i������ʽ
    void Print_All_Poly(); // �����ǰ���ж���ʽ
void Insert_Node(Polynomial *poly, int k, int exp); // �ڶ���ʽpoly�в�����
    void Create_Poly(); // �½�����ʽ
void Delete_Poly(Polynomial *poly); // ɾ������ʽ
    void Delete_Ploy_i(int i); // ɾ����i������ʽ
void Add_Polys(int i,int j); // ��������ʽ���
void Sub_Polys(int i,int j); // ��������ʽ���
void Mul_Polys(int i,int j); // ��������ʽ���

// �����ʾ��Ϣ
void Print_Msg() {
    printf("�����������\n");
    printf("1. �������ʽ\n");
    printf("2. ��ѯ��i������ʽ\n");
    printf("3. ��ѯ��ǰ���ж���ʽ\n");
    printf("4. ɾ����i������ʽ\n");
    printf("5. ��������ʽ���\n");
    printf("6. ��������ʽ���\n");
    printf("7. ��������ʽ���\n");
    printf("8. �˳�\n");
}

// �������ʽ��������ʽ����
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
// �����i������ʽ
void Print_Poly_i(int i) {
    if(i<=0 || i>n) {
        printf("��%d������ʽ�����ڣ�\n",i);
        return;
    }
    printf("��%d������ʽ��\t", i);
    Print_Poly(F[i]);
    printf("\n");
}
// �����ǰ���ж���ʽ
void Print_All_Poly() { for(int i=1; i<=n; i++) Print_Poly_i(i);}

// ������
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
// �½�����ʽ
void Create_Poly() {
    n++;
    printf("���������ʽ��ϵ����ָ�����Կո�ָ�������0 0������\n");
    F[n] = (Polynomial *)malloc(sizeof(Polynomial));
    F[n]->next = NULL;
    int tk, texp;
    while (1) {
        scanf("%d %d", &tk, &texp);
        if(tk==0 && texp==0) break;
        Insert_Node(F[n], tk, texp);
    }
    printf("�ѱ����%d������ʽ��\t", n);
    Print_Poly(F[n]);
    printf("\n");
}

// ɾ������ʽ
void Delete_Poly(Polynomial *poly) {
    Polynomial  *t;
    while (poly != NULL) {
        t = poly->next;
        free(poly);
        poly = t;
    }
}
// ɾ����i������ʽ
void Delete_Ploy_i(int i) {
    if(i<=0 || i>n) {
        printf("��%d������ʽ�����ڣ�\n",i);
        return;
    }
    Delete_Poly(F[i]);
    for(int j=i; j<n; j++) F[j]=F[j+1];
    n--;
}

// ��������ʽ���
void Add_Polys(int i, int j) {
    if(i<=0 || i>n) {
        printf("��i=%d������ʽ�����ڣ�\n",i);
        return;
    }else if(j<=0 || j>n) {
        printf("��j=%d������ʽ�����ڣ�\n",j);
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
    printf("��%d������ʽ���%d������ʽ��ӵĽ��Ϊ��\t", i, j);
    Print_Poly(t);printf("\n");

    char c;getchar();
    while(c!='y'&&c!='n'&&c!='Y'&&c!='N'){
        printf("�Ƿ񱣴�ý����(y/n)");
        scanf("%c", &c);
    }
    if(c=='y'||c=='Y') {
        n++;F[n]=t;
        printf("�ѱ����%d������ʽ��\t", n);
        Print_Poly(t);printf("\n");
        return ;
    }Delete_Poly(t);
}

// ��������ʽ���
void Sub_Polys(int i,int j) {
    if(i<=0 || i>n) {
        printf("��i=%d������ʽ�����ڣ�\n",i);
        return;
    }else if(j<=0 || j>n) {
        printf("��j=%d������ʽ�����ڣ�\n",j);
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
    printf("��%d������ʽ���%d������ʽ����Ľ��Ϊ��\t", i, j);
    Print_Poly(t);printf("\n");
    char c;getchar();
    while(c!='y'&&c!='n'&&c!='Y'&&c!='N'){
        printf("�Ƿ񱣴�ý����(y/n)");
        scanf("%c", &c);
    }
    if(c=='y'||c=='Y') {
        n++;F[n]=t;
        printf("�ѱ����%d������ʽ��\t", n);
        Print_Poly(t);printf("\n");
        return  ;
    }
    Delete_Poly(t);
}

// ��������ʽ���
void Mul_Polys(int i,int j) {
    if(i<=0 || i>n) {
        printf("��i=%d������ʽ�����ڣ�\n",i);
        return;
    }else if(j<=0 || j>n) {
        printf("��j=%d������ʽ�����ڣ�\n",j);
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
    printf("��%d������ʽ���%d������ʽ��˵Ľ��Ϊ��\t", i, j);
    Print_Poly(t);printf("\n");
    char c;getchar();
    while(c!='y'&&c!='n'&&c!='Y'&&c!='N'){
        printf("�Ƿ񱣴�ý����(y/n)");
        scanf("%c", &c);
    }
    if(c=='y'||c=='Y') {
        n++;F[n]=t;
        printf("�ѱ����%d������ʽ��\t", n);
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
                printf("������Ҫ��ѯ�Ķ���ʽ�ı�ţ�\n");
                scanf("%d", &i);
                Print_Poly_i(i);
                break;
            case 3:
                Print_All_Poly();
                break;
            case 4:
                Print_All_Poly();
                printf("������Ҫɾ���Ķ���ʽ�ı�ţ�\n");
                scanf("%d", &i);
                Delete_Ploy_i(i);
                break;
            case 5:
                Print_All_Poly();
                printf("������Ҫ��ӵ���������ʽ�ı�ţ�\n");
                scanf("%d %d", &i, &j);
                Add_Polys(i, j);
                break;
            case 6:
                Print_All_Poly();
                printf("������Ҫ�������������ʽ�ı�ţ�\n");
                scanf("%d %d", &i, &j);
                Sub_Polys(i, j);
                break;
            case 7:
                Print_All_Poly();
                printf("������Ҫ��˵���������ʽ�ı�ţ�\n");
                scanf("%d %d", &i, &j);
                Mul_Polys(i, j);
                break;
            case 8:
                return 0;
            default:
                printf("�������\n");
                break;
        }
        printf("\n");
    }
}