#include<stdio.h>
#include<string.h>
#include<algorithm>

using namespace std;

/*
  ������SG����ģ�壬Ҫ�����ǰSG��ʼ��Ϊ-1��������Ҫÿ��һ�ξͳ�ʼ��һ��
  kΪ״̬ת�Ƽ���S�Ĵ�С��S[i]��ʾ״̬ת�Ƽ�������
*/
#define MaxN    10001
#define MaxRule 101

int SG[MaxN],*S,k;

void InitSG(int rulenum,int *rules)  //rules��0��ʼ��
{
    k=rulenum;
    memset(SG,-1,sizeof(SG));
    sort(rules,rules+k);  //S��Ҫ��С��������
    S=rules;
}

int SpragueGrundy(int x)
{
    int i,res;
    bool vis[MaxRule+2];  //�������е�״̬����ת�ƣ���SGֵ����һ����������ǰ1��ת����
    if (SG[x]!=-1) return SG[x];
    memset(vis,0,sizeof(vis));
    for (i=0;i<k;i++) if (x>=S[i])
    {
        SpragueGrundy(x-S[i]);
        vis[SG[x-S[i]]]=1;
    }
    for (i=0;i<MaxN;i++) if (!vis[i])
    {
        res=i;
        break;
    }
    SG[x]=res;
    return res;
}

/*----------SG Template Over----------*/

int s[MaxRule];

int main()
{
    int i,cases,t,k,sum,num;
    freopen("hdoj1536.txt","r",stdin);
    freopen("hdoj1536ans.txt","w",stdout);
    while (scanf("%d",&k)!=EOF && k)
    {
        for (i=0;i<k;i++) scanf("%d",&s[i]);
        InitSG(k,s);
        scanf("%d",&cases);
        while (cases--)
        {
            sum=0;
            scanf("%d",&t);
            while (t--)
            {
                scanf("%d",&num);
                sum^=SpragueGrundy(num);
            }
            if (sum==0) printf("L"); else printf("W");
        }
        printf("\n");
    }
    return 0;
}
