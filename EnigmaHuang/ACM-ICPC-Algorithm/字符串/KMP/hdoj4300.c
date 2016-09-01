#include<stdio.h>
#include<string.h>
#define Max(a,b) (a)>(b)?(a):(b)
#define MaxN 100005

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

int  ANext[MaxN],BRes[MaxN];
char s1[MaxN],s2[MaxN],encode[30],decode[30];

int main()
{
    int n,t,i,len,k;
    freopen("hdoj4300.txt","r",stdin);
    freopen("hdoj4300ans.txt","w",stdout);
    scanf("%d",&t);
    while (t--)
    {
	scanf("%s%s",encode,s1);
	for (i=0;i<26;i++) decode[encode[i]-'a']='a'+i;
	len=strlen(s1);
	for (i=0;i<len;i++) s2[i]=decode[s1[i]-'a'];
	s2[i]='\0';
	ExtendedKMP(s2,s1,ANext,BRes);
	k=len;
	//���ĳ���+����ƥ������ĳ���Ҫ�����ܳ���
	//���ĳ���Ҫ���ڵ��ں���ƥ������ĳ���
	for (i=0;i<len;i++) if (i+BRes[i]==len && i>=BRes[i])
	{
	    k=i;
	    break;
	}
	for (i=0;i<k;i++) printf("%c",s1[i]);
	for (i=0;i<k;i++) printf("%c",decode[s1[i]-'a']);
	printf("\n");
    }
    return 0;
}
