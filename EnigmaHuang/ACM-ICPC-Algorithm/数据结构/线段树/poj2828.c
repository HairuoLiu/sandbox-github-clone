#include<stdio.h>

#define MaxN 200005

struct
{
    int l,r,val;
}node[3*MaxN];
int id,pos[MaxN],val[MaxN],ans[MaxN];

void BuildTree(int left,int right,int u)
{
    int mid;
    node[u].l=left;
    node[u].r=right;
    node[u].val=right-left+1; //�˴���¼��������ж��ٵĿ�λ��һ��ʼȫ���ǿյ�
    if (left==right) return;
    mid=(left+right)/2;
    BuildTree(left,mid,u*2);
    BuildTree(mid+1,right,u*2+1);
}

int PointUpdata(int emptynum,int u) //������²���λu�������е�empty����λ�ı��
{
    node[u].val--;  //��������һ�ˣ������λ-1
    if (node[u].l==node[u].r) return node[u].l;
    if (node[u*2].val>=emptynum) return PointUpdata(emptynum,u*2);
    else
    {
        emptynum-=node[u*2].val;
        return PointUpdata(pos,u*2+1);
    }
}

int main()
{
    int n,i,id;
    freopen("poj2828.txt","r",stdin);
    freopen("poj2828ans.txt","w",stdout);
    while (scanf("%d", &n)!=EOF)
    {
        BuildTree(1,n,1);
        for (i=1;i<=n;i++) scanf("%d%d",&pos[i],&val[i]);
        //������pos[i]���˺��棬����Ҫ�ҵ�pos[i]+1����λ
        for (i=n;i>=1;i--) ans[PointUpdata(pos[i]+1,1)]=val[i];
        for (i=1;i<=n;i++) printf("%d ",ans[i]);
        printf("\n");
    }
    return 0;
}
