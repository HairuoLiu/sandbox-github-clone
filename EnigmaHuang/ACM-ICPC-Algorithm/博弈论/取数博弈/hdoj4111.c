#include<stdio.h>
#include<string.h>

int SG[55][60005];

int GetSG(int i,int j)
{
    if (SG[i][j]!=-1) return SG[i][j];
    if (j==1)
    {
        SG[i][j]=GetSG(i+1,0);
        return SG[i][j];
    }     
    SG[i][j]=0;
    //ĳ��ֻ��һ����ȡ��
    if (i>=1 && !GetSG(i-1,j)) SG[i][j]=1;
    //�Ѳ���1����ȡ��һ��
    else if (j>=1 && !GetSG(i,j-1)) SG[i][j]=1;
    //��1���ĺϲ�������1����
    else if (i>=1 && j>0 && !GetSG(i-1,j+1)) SG[i][j]=1;
    //������1���ĺϲ���ע��ϲ���Ҫһ��
    else if (i>=2 && ( (j==0 && !GetSG(i-2,j+2))
                     ||(j!=0 && !GetSG(i-2,j+3)) ) )
         SG[i][j]=1;
    return SG[i][j];
}

int main()
{
    int n,t,cases=0,k,one,sum;
    freopen("hdoj4111.txt","r",stdin);
    freopen("hdoj4111ans.txt","w",stdout);
    scanf("%d",&t);
    memset(SG,-1,sizeof(SG));
    while (t--)
    {
        scanf("%d",&n);
        one=0;
        sum=0;
        while (n--)
        {
            scanf("%d",&k);
            if (k==1) one++;
            else sum+=(k+1);
        }
        if (sum) sum--;
        printf("casese #%d: ",++cases);
        if (GetSG(one,sum)) printf("Alice\n");
        else printf("Bob\n");
    }
    return 0;
}
