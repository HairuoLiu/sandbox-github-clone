#include<stdio.h>
#include<string.h>
#define lowbit(x) (x&(-x))
#define MaxN 20002

struct TCow
{
    int x,w;
}cow[MaxN];

int wNum[MaxN]; //wNum[x]��һ�������xС��������ţ������
int wDis[MaxN]; //wDis[x]��һ�������xС��������ţ���˵�ľ���֮��

void add(int *tree,int x,int value)
{
    int i;
    for (i=x;i<=MaxN;i+=lowbit(i)) tree[i]+=value;
}

long long sum(int *tree,int x)
{
    long long res=0;
    int i;
    for (i=x;i;i-=lowbit(i)) res+=tree[i];
    return res;
}

void QSort(TCow p[],int l,int r)
{
    int i=l,j=r,mid=p[(l+r)/2].x;
    TCow swap;
    while (i<=j)
    {
        while (p[i].x<mid) i++;
        while (p[j].x>mid) j--;
        if (i<=j)
        {
            swap=p[i];
            p[i]=p[j];
            p[j]=swap;
            i++;j--;
        }
    }
    if (i<r) QSort(p,i,r);
    if (l<j) QSort(p,l,j);
}

int main()
{
    int i,n;
    long long PreNum,PreDis,ans;
    freopen("poj1990.txt","r",stdin);
    freopen("poj1990ans.txt","w",stdout);
    while (scanf("%d",&n)!=EOF)
    {
        for (i=0;i<n;i++) scanf("%d%d",&cow[i].w,&cow[i].x);
        QSort(cow,0,n-1);
        ans=0;
        //������������
        memset(wNum,0,sizeof(wNum));
        memset(wDis,0,sizeof(wDis));
        for (i=0;i<n;i++)
        {
            PreNum=sum(wNum,cow[i].w-1);  //���ȵ�ǰ����С��ţ������֮��
            PreDis=sum(wDis,cow[i].w-1);  //���ȵ�ǰ����С��ţ�ĵ�0�ľ���֮��
            ans+=(PreNum*cow[i].x-PreDis)*cow[i].w;
            add(wNum,cow[i].w,1);
            add(wDis,cow[i].w,cow[i].x);
        }
        //���Ҳ��������
        memset(wNum,0,sizeof(wNum));
        memset(wDis,0,sizeof(wDis));
        for (i=n-1;i>=0;i--)
        {
            //���ǵ��������û�б����浽���Ĵ�����������Ҫ����
            //ֱ��ʹ��cow[i].w������-1��������Ҳ����
            PreNum=sum(wNum,cow[i].w);  //���ȵ�ǰ����С��ţ������֮��
            PreDis=sum(wDis,cow[i].w);  //���ȵ�ǰ����С��ţ�ĵ�0�ľ���֮��
            ans+=(PreDis-PreNum*cow[i].x)*cow[i].w;
            add(wNum,cow[i].w,1);
            add(wDis,cow[i].w,cow[i].x);
        }
        printf("%lld\n",ans);
    }
    return 0;
}
