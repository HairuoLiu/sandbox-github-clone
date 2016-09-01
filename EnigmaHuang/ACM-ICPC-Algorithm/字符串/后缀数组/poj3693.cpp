#include<stdio.h>
#include<string.h>

#define Max(a,b) (a)>(b)?(a):(b)
#define Min(a,b) (a)<(b)?(a):(b)
#define MaxN 100005
#define MaxL 20

int sa[MaxN],rank[MaxN],height[MaxN];
int wa[MaxN],wb[MaxN],wv[MaxN],wd[50];

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
    for (i=0;i<n;i++)
    {
        if (k) k--;
        for (j=sa[rank[i]-1];r[i+k]==r[j+k];k++);
        height[rank[i]]=k;
    }
}

int min[MaxN][MaxL];

void MakeRMQ(int size,int a[])  //a��Ҫ��1��ʼ���
{
    int i,j;
    for (i=1;i<=size;i++) min[i][0]=a[i];
    for (j=1;(1<<j)<=size;j++)
        for (i=1;i+(1<<j)-1<=size;i++)
            min[i][j]=Min(min[i][j-1],min[i+(1<<(j-1))][j-1]);
}

int RangeMinQuery(int l,int r)
{
    int k=0;
    if (l>r) return 0;
    while ( (1<<(k+1)) <= (r-l+1) ) k++;
    return Min(min[l][k],min[r+1-(1<<k)][k]);
}

int LCP(int i,int j)
{
    int t;
    if (i>j)
    {
	t=i;
	i=j;
	j=t;
    }
    i++;
    return RangeMinQuery(i,j);
}

char s[MaxN];
int  num[MaxN],n,ans[MaxN];

int main()
{
    int i,j,t=0,flag;
    int sectlen,startpos,maxfit,sect,offset,offsetfit;
    int cnt,res;
    freopen("poj3693.txt","r",stdin);
    freopen("poj3693ans.txt","w",stdout);
    while (scanf("%s",s)!=EOF)
    {
        if (s[0]=='#') break;
        n=strlen(s);
        for (i=0;i<n;i++) num[i]=s[i]-'a'+2;
        num[n++]=1;

        DA(num,sa,rank,n,30);
        CalcHeight(num,sa,height,n);
        MakeRMQ(n,height);
        flag=cnt=res=0;

        for (sectlen=1;sectlen<n;sectlen++)
            for (startpos=sectlen;startpos<n-1;startpos+=sectlen)
            {
                maxfit=LCP(rank[startpos-sectlen],rank[startpos]);
                offset=sectlen-maxfit%sectlen;  //��ǰλ�ƣ����ɶ�һ��ѭ���ڵĳ���
                if (startpos>sectlen && (maxfit%sectlen)!=0)
                {
                    offsetfit=LCP(rank[startpos-offset-sectlen],rank[startpos-offset]);
                    maxfit=Max(maxfit,offsetfit);
                }
                sect=maxfit/sectlen+1;  //maxfit/sectlen=����ǰ׺���е�ѭ������=���н���-1
                if (sect>res)  //ѭ���������࣬����ѱ���ĺ�ѡ��
                {
                    res=sect;
                    cnt=0;
                    ans[cnt++]=sectlen;
                }
                //ѭ��������ͬ����ѭ���ڳ��Ȳ�ͬ�������ѡ����
                else if (sect==res && ans[cnt-1]!=sectlen) ans[cnt++]=sectlen;
            }

	//��sa[1]��ʼ�ң������ֵ�����С
        for (i=1;i<=n && !flag;i++)
            for (j=0;j<cnt && !flag;j++)
		//������׺��LCP>=ѭ���ڳ���*(ѭ������-1)������==������aaaa��aaa
                if (LCP(rank[sa[i]],rank[sa[i]+ans[j]])>=ans[j]*(res-1))
                {
                    flag=1;
                    printf("Case %d: ",++t);
                    s[sa[i]+ans[j]*res]='\0';
                    printf("%s\n",s+sa[i]);
                }
    }
    return 0;
}
