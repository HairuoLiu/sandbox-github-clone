#include<stdio.h>
#include<algorithm>

#define MaxN 25005

using namespace std;

struct
{
    int l,r;
    int val;
}node[3*MaxN];

struct TPost
{
    int pos,num;
}post[MaxN];

int flag,n,nn;

inline int cmp1(const TPost &a,const TPost &b)
{
    if (a.pos<b.pos) return 1;
    else return 0;
}

inline int cmp2(const TPost &a,const TPost &b)
{
    if (a.num>b.num) return 1;
    if (a.num==b.num && a.pos<b.pos) return 1;
    return 0;
}

void BuildTree(int left,int right,int u)
{
    int mid;
    node[u].l=left;
    node[u].r=right;
    node[u].val=0;         //��ʼʱ��û�б�ռ��
    if (left==right) return;
    mid=(left+right)/2;
    BuildTree(left,mid,u*2);
    BuildTree(mid+1,right,u*2+1);
}

void SegmentQuery(int left,int right,int u)  //��ѯ�Ƿ��пյ�����
{         
    if (node[u].val==1) return;
    if (node[u].l==left && node[u].r==right)  //�ҵ�һ����ȫû�ù�������
    {
        node[u].val=1;   //�����Ϊ����
        flag=1;          //���ź������Ա���������ǲ��Ƴ�
        return;
    }
    if (right<=node[u*2].r) SegmentQuery(left,right,u*2);
    else if(left>=node[u*2+1].l) SegmentQuery(left,right,u*2+1);
    else
    {
        SegmentQuery(left,node[u*2].r,u*2);
        SegmentQuery(node[u*2+1].l,right,u*2+1);
    }
    //������������䶼�����ˣ��������ֱ�ӱ��Ϊ���ù���
    node[u].val=node[u*2].val & node[u*2+1].val;
}

void Discrete()
{
    int i,pre;
    sort(post,post+2*n,cmp1);
    nn=0;
    pre=0;
    for (i=0;i<2*n;i++) if (post[i].pos!=pre)
    {
        pre=post[i].pos;
        post[i].pos=++nn;
    }
    else post[i].pos=nn;
}

int main()
{
    int t,i,ans;
    freopen("poj2528.txt","r",stdin);
    freopen("poj2528ans.txt","w",stdout);
    scanf("%d",&t);
    while (t--)
    {
        scanf("%d",&n);
        for (i=0;i<n;i++)
        {
            scanf("%d%d",&post[2*i].pos,&post[2*i+1].pos);
            post[2*i].num=post[2*i+1].num=i;
        }
        Discrete();
        BuildTree(1,nn,1);
        sort(post,post+2*n,cmp2);   //�������������ǰ��
        ans=0;
        for (i=0;i<2*n;i+=2)
        {
            flag=0;
            SegmentQuery(post[i].pos,post[i+1].pos,1);
            if (flag) ans++;
        }
        printf("%d\n",ans);
    }
    return 0;
}
