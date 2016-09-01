#include <stdio.h>
#include <string.h>
#include <stack>

using namespace std;

#define MaxN 50005
#define Max(a,b) (a)>(b)?(a):(b)

struct TNode
{
    int l,r;
    int lma,rma,ma;
}node[MaxN*3];

void BuildTree(int left,int right,int u)
{
    int mid;
    node[u].l=left;
    node[u].r=right;
    node[u].lma=node[u].rma=node[u].ma=right-left+1;
    if (left==right) return;
    mid=(left+right)/2;
    BuildTree(left,mid,u*2);
    BuildTree(mid+1,right,u*2+1);
}

void PointUpdate(int pos,int u,int flag)
{
    int mid,a,b,c;
    if (node[u].l==node[u].r)  //��Ҷ�ӽڵ��ˣ�ֱ�Ӹ���֮
    {
        node[u].lma=node[u].ma=node[u].rma=flag;
        return;
    }

    mid=(node[u].l+node[u].r)/2;

    if (pos<=mid) PointUpdate(pos,u*2,flag);
    else PointUpdate(pos,u*2+1,flag);

    //������ȫ�գ���˽ڵ������������������������+����������������
    //����ڵ����������=����������������
    if (node[u*2].ma==node[u*2].r-node[u*2].l+1)
         node[u].lma=node[u*2].ma+node[u*2+1].lma;
    else node[u].lma=node[u*2].lma;

    //��������������ԭ��ͬ��������
    if (node[u*2+1].ma==node[u*2+1].r-node[u*2+1].l+1)
         node[u].rma=node[u*2+1].ma+node[u*2].rma;
    else node[u].rma=node[u*2+1].rma;

    a=node[u*2].rma+node[u*2+1].lma;    //����������Ӵ���������
    b=Max(node[u*2].ma,node[u*2+1].ma); //�������������ڲ��������Ľϴ���
    //c=Max(node[u].lma,node[u].rma);     //�˽ڵ������������Ľϴ���
    node[u].ma=Max(a,b);
}

int PointQuery(int pos,int u)
{
    int mid;
    //����ýڵ������ȫ������ȫ�գ�ֱ�ӷ���
    if (node[u].l==node[u].r || node[u].ma==0
     || node[u].ma==node[u].r-node[u].l+1) return node[u].ma;

    mid=(node[u].l+node[u].r)/2;
    if (pos<=mid)  //Ŀ��ڵ��ڵ�ǰ�ڵ��������
    {
            //Ŀ��ڵ����������ĵ��Ҳ�����������
            //�����������ĵ��Ҳ��������䳤��+�������Ĵ������俪ʼ��������
            //���������������
            if (pos>=node[u*2].r-node[u*2].rma+1)
             return node[u*2].rma+node[u*2+1].lma;
            else return PointQuery(pos,u*2);
    }
    else           //��������
    {
            //Ŀ��ڵ����������Ĵ������俪ʼ������������
        //����ͬ�ϣ����������������
            if (pos<=node[u*2+1].l+node[u*2+1].lma-1)
             return node[u*2].rma+node[u*2+1].lma;
            else return PointQuery(pos,u*2+1);
    }
}

int main()
{
    int n,m,x;
    char s[15];
    stack<int> st;
    
    freopen("poj2892.txt","r",stdin);
    freopen("poj2892ans.txt","w",stdout);
    scanf("%d %d",&n,&m);
    
    BuildTree(1,n,1);
    while(!st.empty()) st.pop();

    while(m--)
    {
        scanf("%s",s);
        if (s[0]=='D')
        {
            scanf("%d",&x);
            st.push(x);
            PointUpdate(x,1,0);
        }
        else if (s[0]=='R')
        {
            x=st.top();
            st.pop();
            PointUpdate(x,1,1);
        }
        else
        {
            scanf("%d",&x);
            printf("%d\n",PointQuery(x,1));
        }
    }
    return 0;
}
