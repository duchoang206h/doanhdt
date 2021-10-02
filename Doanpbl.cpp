#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<iomanip>
#include<cmath>
struct Node
{
    float data;
    Node *pNext;
};
typedef struct Node NODE;
struct list
{
    NODE *pHead;
    NODE *pTail;
};
typedef struct list LIST;
void Create(LIST &l)
{
    l.pHead = NULL;
    l.pTail = NULL;
}
NODE *CreateNode(float value)
{
    NODE *p = new NODE;
    p->data = value;
    p->pNext = NULL;
    return p;
}
void insert_tail(LIST &l, NODE *p)
{
    if (l.pHead == NULL)
        l.pHead = l.pTail = p;
    else
    {
        l.pTail->pNext = p;
        l.pTail = p;
    }
}
void ShowList(LIST l)
{
    for (NODE *k = l.pHead; k != NULL; k = k->pNext)
        printf("%1.3f\t", k->data);
    printf("\n");
}
void insertPos(LIST &l, NODE *p, int index)
{
    int dem = 0;
    NODE *g = new NODE;
    for (NODE *k = l.pHead; k != NULL; k = k->pNext)
    {
        dem++;
        if (dem == index)
        {
            NODE *h = CreateNode(p->data);
            h->pNext = k;
            g->pNext = h;
            break;
        }
        g = k;
    }
}
int nhap(int &rowofmatrix, LIST l[100], int &col)
{
    FILE *f;
    int number;
    char t[200];
    printf("Nhap ten file: \n");
    fflush(stdin);
    gets(t);
    f = fopen(t, "r");
    if (f == NULL)
    {
        printf("Khong the mo file\n");
        return 0;
    }
    else
    {
        fscanf(f, "%d\n", &rowofmatrix);
        col = rowofmatrix - 1;
        int i,j ;
        for (i = 0; i < rowofmatrix; i++)
        {
            Create(l[i]);
            for (j = 0; j < rowofmatrix - 1; j++)
            {
                fscanf(f, "%d ", &number);
                NODE *p = CreateNode(number);
                insert_tail(l[i], p);
            }
        }
        fclose(f);
        for (i = 0; i < rowofmatrix; i++)
        {
            printf("Danh sach lien ket thu %d: |\t", i + 1);
            ShowList(l[i]);
        }
        printf("\nChuyen den buoc 2.\n");
    }
}
void insert(LIST l[], int rowofmatrix, int &col)
{
    int k = int(rowofmatrix + 1) / 2;
    int i;
    for (i = 0; i < rowofmatrix; i++)
    {
        printf("Them mot phan tu vao vi tri thu %d: ", k);
        int x;
        scanf("%d",&x);
        NODE *p = CreateNode(x);
        insertPos(l[i], p, k);
        col = rowofmatrix;
    }
}
int WriteFile(int rowofmatrix, LIST l[100])
{
    FILE *f;
    char t[100];
    printf("Nhap ten file de luu: \n");
    fflush(stdin);
    gets(t);
    f = fopen(t, "wb");
    int i;
    for (i = 0; i < rowofmatrix; i++)
    {
        for (NODE *k = l[i].pHead; k != NULL; k = k->pNext)
            fprintf(f, "%1.3f  ", k->data);
        fprintf(f, "\n");
    }
    fclose(f);
}
float Get(LIST l, int index)
{
    int i;
    NODE *p = l.pHead;
    for (i = 0; i < index; i++)
        p = p->pNext;
    return p->data;
}
void Set(LIST l, int index, float value)
{
    int k = 0;
    int i;
    NODE *p = l.pHead;
    for (i = 0; i < index; i++)
    {
        p = p->pNext;
    }
    p->data = value;
}
int Det(int rowofmatrix, LIST l[])
{  int i,j,k;
   LIST det[100];
    for (i = 0; i < rowofmatrix; i++)
        {
            Create(det[i]);
            for (j = 0; j < rowofmatrix; j++)
            {
                double number = Get(l[i],j);
                NODE *p = CreateNode(number);
                insert_tail(det[i], p);
            }
        } 
    double giatri;
    for (i = 0; i < rowofmatrix; i++)
        for (j = rowofmatrix; j < 2 * rowofmatrix; j++)
        {
            if (j - i == rowofmatrix)
            {
                NODE *p = CreateNode(1);
                insert_tail(det[i], p);
            }
            else
            {
                NODE *p = CreateNode(0);
                insert_tail(det[i], p);
            }
        }
    for (k = 0; k < rowofmatrix; k++)
    {
        if (Get(det[k], k) == 0)
        {
            return -1;
        }
    }
}
void Matrix(int rowofmatrix, LIST l[], LIST X, float nghiemX[])
{
    int flag = 0, count = 0;
    double eps = 0.001;
    double y;
    int n = rowofmatrix;
    int m;
    for (m = 0; m < n; m++)
    {
        int value = 0;
        NODE *p = CreateNode(value);
        insert_tail(X, p);
    }
    int i,k,j;
 
    printf("\n\n");
    printf("\tLan lap");printf("        ");
    for (i = 0; i < n; i++){
    	 printf("        x%d",i + 1);printf("            ");
	}
       
    printf("\n");
    do 
    {
        printf("\n\t %d",count + 1); printf("                  ");
        for (i = 0; i < n; i++) 
        {
            y = Get(X, i);
            Set(X, i, Get(l[i], n));
            for (int j = 0; j < n; j++)
            {
                if (j != i)
                    Set(X, i, Get(X, i) - Get(l[i], j) * Get(X, j));
            }
            Set(X, i, Get(X, i) / Get(l[i], i));
            if (abs(Get(X, i) - y) <= eps) 
                flag++;
            else{flag--;
			}    
            printf("%.4f", Get(X, i));printf("                  ");
        }
        printf("\n");
        count++;
    } while (flag <= n+1); 

    printf("\n\t Nghiem cua phuong trinh la\n");
    for (i = 0; i < n; i++){
        printf("\t\t x%d = %.4f\n",i + 1, Get(X, i)); 
		nghiemX[i]=Get(X,i);}
}
void nghiem_X(LIST l[], float nghiemX[], int rowofmatrix, float arrB[])
{
    FILE *f;
    int i,j;
    char t[100];
    printf("Nhap ten file de luu nghiem X: \n");
    fflush(stdin);
    gets(t);
    f = fopen(t, "wb");
    fprintf(f,"Giai phuong trinh AX=B\n");
    fprintf(f,"Mang A:\n");
     for (i = 0; i < rowofmatrix; i++)
    {
        for (j=0;j<rowofmatrix;j++){
        	float t = Get(l[i],j);
            fprintf(f, "%.4f  ", t);}
        fprintf(f, "\n");
    }
    fprintf(f,"Mang B:\n");
    for(i =0; i<rowofmatrix;i++){
    	fprintf(f,"%.4f\n",arrB[i]);
    	}
    fprintf(f,"\nNgiem X:\n");	
    for(i =0; i<rowofmatrix;i++){
    	fprintf(f,"%.4f\n",nghiemX[i]);
    	}
    fclose(f);
}
void Menu(LIST l[], int rowofmatrix, LIST X, float arrB[],int col, int c, float nghiemX[])
{
    int luachon;
    while (true)
    {
        system("cls");
        printf("\n =========== MENU ===========");
        printf("\n1. Doc danh sach lien ket");
        printf("\n2. Them phan tu");
        printf("\n3. Giai nghiem");
        printf("\n0. Ket thuc");
        printf("\nThu tu thuc hien cac buoc tu 1-->2-->3.");
        printf("\n =========== END ===========");
        printf("\nNhap lua chon: ");
        scanf("%d",&luachon);
        if (luachon == 1)
        {
            nhap(rowofmatrix, l, col);
            system("pause");
        }
        else if (luachon == 2)
        {
            if (col == 1)
            {
                printf("Vui long lam lai theo thu tu cac buoc.\n");
                system("pause");
            }
            else
            {   
                insert(l, rowofmatrix, col);
                int i;
                for (i = 0; i < rowofmatrix; i++)
                {
                    printf("Danh sach lien ket thu %d: |\t", i + 1);
                    ShowList(l[i]);
                }
                WriteFile(rowofmatrix, l);
                printf("\nChuyen den buoc 3.\n");
                system("pause");
                c = col;
                col = 1;
            }
        }
        else if (luachon == 3)
        {
            if ((c) != rowofmatrix)
            {
                printf("Vui long lam lai theo thu tu cac buoc.\n");
                system("pause");
            }
            else
            {
                c = 0;
                int i;
                printf("Ma tran A:\n");
                for (i = 0; i < rowofmatrix; i++)
                    ShowList(l[i]);
                if (Det(rowofmatrix, l) == -1)
                {
                    printf("DetA=0 phuong trinh vo nghiem\n");
                    printf("Vui long kiem tra lai ma tran va lam lai tu dau\n");
                    system("pause");
                }
                else
                {    int i ;
                    printf("Nhap ma tran B: \n");
                    for (i = 0; i < rowofmatrix; i++)
                    {
                        scanf("%f", &arrB[i]);
                        NODE *p = CreateNode(arrB[i]);
                        insert_tail(l[i], p);
                    }
                    Matrix(rowofmatrix, l, X,nghiemX);
                    nghiem_X(l, nghiemX, rowofmatrix,arrB);
                    system("pause");
                }
            }
        }
        else
        {
            break;
        }
    }
}
int main()
{
    system("color 3");
    int rowofmatrix, col, c;
    float arrB[100];
    LIST l[100];
    LIST X;
    float nghiemX[100];
    Menu(l, rowofmatrix, X, arrB, col, c,nghiemX);
    return 0;
}

