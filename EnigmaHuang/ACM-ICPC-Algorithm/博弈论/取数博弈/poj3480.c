#include<stdio.h>

int main()
{
    int t,a,n,i,sum1,sum2,ans;
    freopen("poj3480.txt","r",stdin);
    freopen("poj3480ans.txt","w",stdout);
    scanf("%d",&t);
    while (t--)
    {
        scanf("%d",&n);
        sum1=sum2=ans=0;
        for (i=0;i<n;i++)
        {
            scanf("%d",&a);
            if (a>=2) sum1++; else sum2++;
            ans^=a;
        }
        //�ʼ����ΪS2,�����µ���һ�����ȶ�þ���S1
        if ((ans!=0 && sum1!=0) || (ans==0 && sum1==0)) printf("John\n");
        else if ((ans==0 && sum1>=2) || (ans!=0 && sum2%2!=0 && sum1==0)) printf("Brother\n");
    }
    return 0;
}

