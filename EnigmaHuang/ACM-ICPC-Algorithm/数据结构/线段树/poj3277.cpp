#include <stdio.h>
#include <algorithm>
#define MaxN 40005

using namespace std;

struct TNode
{
    int l,r,h;
}node[8*MaxN];  //����ע�⣬��Ϊ�����2*MaxN���㣬������Ҫ4*2*MaxN���ڵ�ű���

int segpos[2*MaxN],height[MaxN],lpos[MaxN],rpos[MaxN];

void BuildTree(int left,int right,int u)
{
    int mid;
    node[u].l=left;
    node[u].r=right;
    node[u].h=0;
    if (left+1==right) return;
    mid=(left+right)/2;
    BuildTree(left,mid,u*2);
    BuildTree(mid,right,u*2+1);
}

void SegmentUpdate(int left,int right,int &i,int u)
{
    int mid;
    if (segpos[node[u].l]==left && segpos[node[u].r]==right) //�ҵ���Ŀ�곤����ȵ�
    {
        if (node[u].h<height[i]) node[u].h=height[i];  //�����еĸ߶ȸߣ�����֮
        return;
    }
    mid=segpos[(node[u].l+node[u].r)/2];
    if (right<=mid) SegmentUpdate(left,right,i,u*2);
    else if (left>=mid) SegmentUpdate(left,right,i,u*2+1);
    else
    {
        SegmentUpdate(left,mid,i,u*2);
        SegmentUpdate(mid,right,i,u*2+1);
    }
}

long long count(int h,int u)    //��ÿ���ӽ��������
{
    long long a,b;
    //�ӳٸ��ǲ�����������ڵ���ߣ�
    //���ӽڵ���游�ڵ�ĸ߶�
    if (node[u].h<h) node[u].h=h; 
    //�����м�û�зָ����ˣ�ֱ�ӷ������
    if (node[u].l+1==node[u].r) return 1LL*(segpos[node[u].r]-segpos[node[u].l] )*node[u].h;
    a=count(node[u].h,u*2);
    b=count(node[u].h,u*2+1);
    return a+b;
}

int main()
{
    int n,m,a,b,i,k;
    long long ans;
    freopen("poj3277.txt","r",stdin);
    freopen("poj3277ans-2.txt","w",stdout);
    while (scanf("%d",&n)!=EOF)
    {
        k=0;
        for (i=1;i<=n;i++)  //��ɢ��
        {
            scanf("%d%d%d",&lpos[i],&rpos[i],&height[i]);
            segpos[++k]=lpos[i];
            segpos[++k]=rpos[i];
        }
        //uniqueҪ��������
        sort(segpos+1,segpos+k+1);
        //Ȼ��Ὣ��ͬ�ļ��е�ǰ�棬�������һ����ͬԪ�غ�һλ��ָ��
        //��˼�ȥ����Ԫ�ص�ָ����-1�͵õ���ͬ��Ԫ�صĸ���
        m=unique(segpos+1,segpos+k+1)-segpos-1;

        BuildTree(1,m,1);
        for (i=1;i<=n;i++) SegmentUpdate(lpos[i],rpos[i],i,1);
        ans=count(0,1);
        printf("%lld\n",ans);
    }
  return 0;
}
