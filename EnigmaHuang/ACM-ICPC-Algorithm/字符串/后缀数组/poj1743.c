#include<stdio.h>
#include<string.h>

#define Max(a,b) (a)>(b)?(a):(b)
#define Min(a,b) (a)<(b)?(a):(b)
#define MaxN 20005

int sa[MaxN],rank[MaxN],height[MaxN];
int wa[MaxN],wb[MaxN],wv[MaxN],wd[MaxN];

int cmp(int *r,int a,int b,int l)
{
    return (r[a]==r[b] && r[a+l]==r[b+l]);
}

/*Doubling Algorithm�����㷨��sa��rank*/
void DA(int *r,int *sa,int *rank,int n,int m)
{
    int i,j,p,*x=wa,*y=wb,*t;
    //��һ�֣��Ӵ�����Ϊ1
    for (i=0;i<m;i++) wd[i]=0;

    for (i=0;i<n;i++)
    {
        x[i]=r[i];
        wd[r[i]]++;
    }

    for (i=1;i<m;i++) wd[i]+=wd[i-1];
    for (i=n-1;i>=0;i--)
    {
        wd[x[i]]--;
        sa[wd[x[i]]]=i;
    }
    //��2~k�֣�����2^k<=n
    for (j=1,p=1;p<n;j*=2,m=p)
    {
        for (p=0,i=n-j;i<n;i++) y[p++]=i;
        for (i=0;i<n;i++) if (sa[i]>=j) y[p++]=sa[i]-j;
        for (i=0;i<n;i++) wv[i]=x[y[i]];
        for (i=0;i<m;i++) wd[i]=0;
        for (i=0;i<n;i++) wd[wv[i]]++;
        for (i=1;i<m;i++) wd[i]+=wd[i-1];
        for (i=n-1;i>=0;i--)
        {
            wd[wv[i]]--;
            sa[wd[wv[i]]]=y[i];
        }
        t=x;
        x=y;
        y=t;
        x[sa[0]]=0;
        p=1;
        for (i=1;i<n;i++)
        {
            if (cmp(y,sa[i-1],sa[i],j)) x[sa[i]]=p-1;
            else x[sa[i]]=p++;
        }
    }
    for (i=1;i<=n-1;i++) rank[sa[i]]=i;
}

void CalcHeight(int *r,int *sa,int *height,int n)
{
    int i,j,k=0;
    for (i=0;i<n;height[rank[i++]]=k)
    {
        if (k) k--;
        for (j=sa[rank[i]-1];r[i+k]==r[j+k];k++);
    }
}

int n,ans,num[MaxN];

int Check(int len)
{
    int i=2,max,min;
    while (1)
    {
	while (i<=n && height[i]<len) i++;
	if (i>n) break; 
	max=min=sa[i-1];
	while (i<=n && height[i]>=len)
	{
	    max=Max(max,sa[i]);
	    min=Min(min,sa[i]);
	    i++;
	}
	if (max-min>=len) return 1;  //����һ����������Ҫ�󼴿�
    }
    return 0;
}

void BinSearch(int startl,int startr)
{
    int l=startl,r=startr,mid;
    while (l<r)
    {
	mid=(l+r+1)/2;
	if (Check(mid)) l=mid; else r=mid-1;
    }
    if (l<4) ans=0; else ans=l+1;  //���ɵĳ�����������ĳ���+1
}

int main()
{
    int i;
    freopen("poj1743.txt","r",stdin);
    freopen("poj1743ans.txt","w",stdout);
    while (scanf("%d",&n) && n)
    {
        for (i=0;i<n;i++) scanf("%d",&num[i]);
        if (n<10)
        {
            printf("0\n");
            continue;
        }
        n--;
        for (i=0;i<n;i++) num[i]=num[i+1]-num[i]+89;  //ȡ������
        num[n]=0;
        DA(num,sa,rank,n+1,180);
        CalcHeight(num,sa,height,n);
        BinSearch(4,n/2);
        printf("%d\n",ans);
    }
}
