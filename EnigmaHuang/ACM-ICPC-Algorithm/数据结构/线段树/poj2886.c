#include <stdio.h>
#include <string.h>

#define MaxN 500005

struct line
{
    int l,r,val;
}node[MaxN*3];

int n,k;
int MaxID,MaxNum;   //Լ���������ı�ţ�Լ�����������ֵ
int div[MaxN];      //ÿ������Լ������

void GetDivision()  //Ԥ������������Լ������
{
    int i,j;
    memset(div,0,sizeof(div));
    for (i=1;i<=n;i++)
    {
        div[i]++;
        for (j=i*2;j<=n;j+=i) div[j]++;
    }
    MaxID=1;
    MaxNum=div[1];
    for (i=2; i <= n; i++) if (div[i]>MaxNum)
    {
        MaxNum=div[i];
        MaxID=i;
    }
}

void BuildTree(int left,int right,int u)
{
    int mid;
    node[u].l=left;
    node[u].r=right;
    node[u].val=right-left+1;
    if (left==right) return ;
    mid=(left+right)/2;
    BuildTree(left,mid,u*2);
    BuildTree(mid+1,right,u*2+1);
}

int QueryPos(int k,int u) //����uΪ���ڵ�������е�k�����������е�λ��
{
    node[u].val--;       //��λ��1
    if (node[u].l==node[u].r) return node[u].l;

    //����������
    if (k<=node[u*2].val) return QueryPos(k,u*2);
    else return QueryPos(k-node[u*2].val,u*2+1);
}

char name[MaxN][15];
int  card[MaxN];

int main()
{
    int i,pos;
    freopen("poj2886.txt","r",stdin);
    freopen("poj2886ans.txt","w",stdout);
    while(scanf("%d %d",&n,&k)!=EOF)
    {
        GetDivision();
        for (i=1;i<=n;i++) scanf("%s %d",name[i],&card[i]);

        BuildTree(1,n,1);

        for (i=0;i<MaxID;i++)   //��ȦMaxID���ɣ������ҳ���MaxID�γ�Ȧ���˵�ʵ��λ��
        {
            pos=QueryPos(k,1);  //�ҵ�ԭʼλ�ã�˳�����˳�Ȧ
            n--;                //��Ȧ�Ժ�������1
            if (n==0) break;
            //����һ�ֵĳ�Ȧλ����ʣ�������е�k����kֵ
            if (card[pos]>0) k=(k-1+card[pos]-1)%n+1;
            else k=((k-1+card[pos])%n+n)%n+1;
        }
        printf("%s %d\n",name[pos],MaxNum);
    }
    return 0;
}
