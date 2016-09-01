#include<stdio.h>
#include<string.h>
#define Max(a,b) (a)>(b)?(a):(b)
#define MaxN 200005

/*
��a��ģ�崮������b����������ÿ����׺�������ǰ׺
ANext[i]:a[i~M]��a�������ǰ׺����
BRes[i] :b[i~N]��a�������ǰ׺����
*/
void ExtendedKMP(char *a,char *b,int *ANext,int *BRes)
{
    int i,j,k,M,N,Len,L;
    M=strlen(a);
    N=strlen(b);
    for (j=0;j+1<M && a[j]==a[j+1];j++);
    ANext[1]=j;
    k=1;
    for (i=2;i<M;i++)
    {
        Len=k+ANext[k];
        L=ANext[i-k];
        if (L+i<Len) ANext[i]=L;
        else
        {
            for (j=Max(0,Len-i);i+j<M && a[j]==a[i+j];j++);
            ANext[i]=j;
            k=i;
        }
    }
    for (j=0;j<N && j<M && a[j]==b[j];j++);
    BRes[0]=j;
    k=0;
    for (i=1;i<N;i++)
    {
        Len=k+BRes[k];
        L=ANext[i-k];
        if (L<Len-i) BRes[i]=L;
        else
        {
            for (j=Max(0,Len-i);j<M && i+j<N && a[j]==b[i+j];j++);
            BRes[i]=j;
            k=i;
        }
    }
}

int  next[MaxN],extend[MaxN],sectlen,len;
char s1[MaxN],s2[MaxN];

void GetKMPNext(char *pattern)
{
    int n,i,j;
    memset(next,0,sizeof(next));
    n=strlen(pattern);
    for (i=1;i<n;i++)
    {
        j=i;
        while (j>0)
        {
            j=next[j];
            if (pattern[j]==pattern[i])
            {
                next[i+1]=j+1;
                break;
            }
        }
    }
    sectlen=n-next[n];
}

void Solve()
{
    int i,less,equ,greater;
    if (len%sectlen!=0) sectlen=len;
    less=equ=greater=0;
    /*
    extend[i]����iλ��Ϊ��ʼ�ĺ�׺��λ��Ϊi����ƥ���ԭ��ǰ׺����
    s2[i]��λ��Ϊi�õ��Ĵ��ĵ�һλ
    s2[extend[i]]��λ��Ϊi����ƥ���ԭ���ĳ��Ⱥ�һλ
    s2[extend[i]+i]��λ��Ϊi����ƥ���ԭ���ĳ��Ⱥ�һλ����Ӧ��λ�ƴ����Ⱥ�һλ
    */
    for (i=0;i<sectlen;i++)
    {
	//s2[i~i+len-1]��s1��ȫƥ�䣬�����λ�����Ľ�����
	if (extend[i]==len) equ++;
	//λ�ƴ�ʧ��λ�õ�ֵС��ԭ��ʧ��λ�õ�ֵ
	else if (s2[extend[i]]>s2[i+extend[i]]) less++;
        //λ�ƴ�ʧ��λ�õ�ֵ����ԭ��ʧ��λ�õ�ֵ
	else if (s2[extend[i]]<s2[i+extend[i]]) greater++;
    }
    printf("%d %d %d\n",less,equ,greater);
}

int main()
{
    int t,i,n;
    freopen("hdoj4333.txt","r",stdin);
    freopen("hdoj4333ans.txt","w",stdout);
    scanf("%d\n",&t);
    for (i=1;i<=t;i++)
    {
	scanf("%s",s1);
	strcpy(s2,s1);
	strcat(s2,s1);  
	len=strlen(s1);
	GetKMPNext(s1);
	ExtendedKMP(s1,s2,next,extend);
	printf("Case %d: ",i);
	Solve();
    }
    return 0;
}
