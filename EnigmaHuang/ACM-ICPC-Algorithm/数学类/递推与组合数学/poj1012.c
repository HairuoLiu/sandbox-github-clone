#include<stdio.h>

int main()
{
    int Joseph[15]={0},k,n,m,i,ans[30];
    freopen("poj1012.txt","r",stdin);
    freopen("poj1012ans.txt","w",stdout);
    while (scanf("%d",&k) && k)
    {
        if (Joseph[k])  //�Ѿ��н���ˣ�ֱ����� 
        {
       	    printf("%d\n",Joseph[k]);
       	    continue;
        }
        n=2*k;
        for (i=0;i<30;i++) ans[i]=0;  //��ʼ����ɱ�б� 
        m=1;
        for (i=1;i<=k;i++)
        {
       	    ans[i]=(ans[i-1]+m-1)%(n-i+1);  //���ƹ�ϵ 
       	    if (ans[i]<k) //���ɱ������һ�����ˣ���ôm++ 
       	    {
   	        i=0;
   	        m++;
       	    }
        }
        Joseph[k]=m;
        printf("%d\n",Joseph[k]);
    }
    return 0;
}
