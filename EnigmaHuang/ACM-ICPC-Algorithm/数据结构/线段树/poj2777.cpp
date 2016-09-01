#include<stdio.h>
#define MaxN 100005

using namespace std;

struct
{
    int l,r;
    int val;    //32λ��int��ÿһλ��Ӧһ����ɫ����λ�������bool col[32]
    int cover;  //��ʾ������䶼��Ϳ��ͬһ����ɫ���߶���Ч�ʵ����֣�����������0(n)��
}node[3*MaxN];

void swap(int &a, int &b)
{
    int tmp=a;a=b;b=tmp;
}

void BuildTree(int left,int right,int u)
{
    int mid;
    node[u].l=left;
    node[u].r=right;
    node[u].val=1;         //��ʼʱ��ΪͿ����ɫ1
    node[u].cover=1;
    if (left==right) return;
    mid=(left+right)/2;
    BuildTree(left,mid,u*2);
    BuildTree(mid+1,right,u*2+1);
}

void PushDown(int u)       //�ӳٲ���
{
    node[u].cover=0;
    node[u*2].val=node[u].val;
    node[u*2].cover=1;
    node[u*2+1].val=node[u].val;
    node[u*2+1].cover=1;
}

void SegmentUpdata(int left,int right,int newvalue,int u)
{
    if (left<=node[u].l && right>=node[u].r)
    {
        node[u].val=newvalue;
        node[u].cover=1;
        return;
    }
    if (node[u].val==newvalue) return;     //��֦
    if (node[u].cover) PushDown(u);
    //node[u].col |= val;   ���У���Ϊ�¼������ɫ���ܻ��node[u].val�е�ĳЩ��ɫ���ǵ�
    if (left<=node[u*2].r)    SegmentUpdata(left,right,newvalue,u*2);
    if (right>=node[u*2+1].l) SegmentUpdata(left,right,newvalue,u*2+1);

    //������һ�����¼ӵ�
    node[u].val=node[u*2].val | node[u*2+1].val;   //���ݹ�����ٸ��ĸ��ڵ����ɫ
}

void SegmentSum(int left,int right,int &sum,int u)
{
    if (node[u].cover)      //�������ȫ��Ϊ1����ɫ�����ڷָ�����
    {         
        //sum+=node[u].val;
        sum |= node[u].val; //��ɫ�������λ�������
        return;
    }
    if (left<=node[u].l && right>=node[u].r)
    {
        //sum+=node[u].val;
        sum |= node[u].val;
        return;
    }
    if (left<=node[u*2].r)    SegmentSum(left,right,sum,u*2);
    if (right>=node[u*2+1].l) SegmentSum(left,right,sum,u*2+1);
}

int BinSum(int sum)           //��int�͵�sum��Ӧ����ɫ����
{
    int ans=0;
    while (sum)
    {
        if (sum%2) ans++;  
        sum=sum/2;        
    }
    return ans;
}

int main()
{
    int n,t,m,sum;
    freopen("poj2777.txt","r",stdin);
    freopen("poj2777ans.txt","w",stdout);
    scanf("%d%d%d",&n,&t,&m);
    BuildTree(1,n,1);
    while (m--)
    {
        getchar();
        int a,b,c;
        char ope;
        scanf("%c", &ope);
        if(ope == 'C')
        {
            scanf("%d%d%d",&a,&b,&c);
            if (b<a) swap(a,b);            //�п���b<a
            SegmentUpdata(a,b,1<<(c-1),1); //int�͵������cλ����c����ɫ����Ϊ1
        }
        else
        {
            scanf("%d%d",&a,&b);
            if (b<a) swap(a,b);
            sum=0;
            SegmentSum(a,b,sum,1);
            printf("%d\n",BinSum(sum));
        }
    }
    return 0;
}
