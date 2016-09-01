#include <stdio.h>
#include <string.h>

#define MaxN 50005
#define Max(a,b) (a)>(b)?(a):(b)
int flag;

struct TNode
{
    int l,r;
    int lma,rma,ma;
    int cover;
}node[MaxN*3];

void BuildTree(int l,int r,int u)
{
    int mid;
    node[u].l=l;
    node[u].r=r;
    node[u].cover=-1;    //��ʼ��Ϊ��
    node[u].lma=node[u].rma=node[u].ma=r-l+1;
    if (l==r) return;
    mid=(l+r)/2;
    BuildTree(l,mid,u*2);
    BuildTree(mid+1,r,u*2+1);
}

void PushDown(int u)  //����״̬
{
    node[u*2].cover=node[u*2+1].cover=node[u].cover;
    if (node[u].cover==1)      //ȫ��
    {
        node[u*2].lma=node[u*2].rma=node[u*2].ma=0;
        node[u*2+1].lma=node[u*2+1].rma=node[u*2+1].ma=0;
    }
    else if (node[u].cover==-1) //ȫ��
    {
        node[u*2].lma=node[u*2].rma=node[u*2].ma=node[u*2].r-node[u*2].l+1;
        node[u*2+1].lma=node[u*2+1].rma=node[u*2+1].ma=node[u*2+1].r-node[u*2+1].l+1;
    }
    node[u].cover=0;   //��������Ϊ��������
}

int Query(int num,int u)
{
    if (node[u].lma==num && node[u].r-node[u].l+1==num) return node[u].l;  //���������������ȣ�ֱ�ӷ���

    if (node[u].ma>=num)
    {
            //��ǰ����ȫ����ȫ�գ�����״̬
        if (node[u].cover!=0) PushDown(u);
        //�������������Ŀ�������裬�ݹ�������
        if (node[u*2].ma >= num) return Query(num,u*2);
        //�м�����������Ŀ�������裬�����������ұ����������
        if (node[u*2].rma+node[u*2+1].lma>=num) return node[u*2].r-node[u*2].rma+1;
        //�ұ������շ�����Ŀ�������裬�ݹ�������
        if (node[u*2+1].ma>=num) return Query(num,u*2+1);
    }
    return 0;
}


void SegmentUpdate(int l, int r,int u)//����[l,r]����
{
    int mid,a,b,c;

    if (node[u].l==l && node[u].r==r) //ǡ����Ҫ�������䣬ֱ���޸ĸ�����״̬
    {
        if (flag==-1) node[u].lma=node[u].rma=node[u].ma=r-l+1;
        else node[u].lma=node[u].rma=node[u].ma=0;
        node[u].cover=flag;
        return;
    }

    mid=(node[u].l+node[u].r)/2;

    //��ǰ�ڵ�ȫ������ȫ�գ�����״̬
    if (node[u].cover!=0) PushDown(u);

    //����������
    if (r<=mid) SegmentUpdate(l,r,u*2);
    else if (l>mid) SegmentUpdate(l,r,u*2+1);
    else
    {
        SegmentUpdate(l,mid,u*2);
        SegmentUpdate(mid+1,r,u*2+1);
    }

    //������ȫ�գ���˽ڵ������������������������+����������������
    //����ڵ����������=����������������
    if (node[u*2].cover==-1)
         node[u].lma=node[u*2].ma+node[u*2+1].lma;
    else node[u].lma=node[u*2].lma;

    //��������������ԭ��ͬ��������
    if (node[u*2+1].cover==-1)
         node[u].rma=node[u*2+1].ma+node[u*2].rma;
    else node[u].rma=node[u*2+1].rma;

    a=node[u*2].rma+node[u*2+1].lma;    //����������Ӵ���������
    b=Max(node[u*2].ma,node[u*2+1].ma); //�������������ڲ��������Ľϴ���
    c=Max(node[u].lma,node[u].rma);     //�˽ڵ������������Ľϴ���
    node[u].ma=Max(Max(a,b),c);

    //���������������Ժ�����һ������Ҫ���ݸ��´˽ڵ�����
    if (node[u*2].cover==node[u*2+1].cover) node[u].cover=node[u*2].cover;
}

int main()
{
    int n,m,a,b,op;
    freopen("poj1823.txt","r",stdin);
    freopen("poj1823ans.txt","w",stdout);
    scanf("%d%d",&n,&m);
    BuildTree(1,n,1);
    node[1].cover=-1;
    node[1].ma=n;
    while (m--)
    {
        scanf("%d",&op);
        if(op==1)
        {
            scanf("%d%d",&a,&b);
            flag=1;
            SegmentUpdate(a,a+b-1,1);
        }
        else if(op==2)
        {
            scanf("%d%d",&a,&b);
            flag=-1;
            SegmentUpdate(a,a+b-1,1);
        }
        else printf("%d\n",node[1].ma);
    }
    return 0;
}
