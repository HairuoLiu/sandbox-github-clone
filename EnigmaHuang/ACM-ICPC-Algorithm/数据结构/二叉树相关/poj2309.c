#include<stdio.h>

int main()
{
    int n,t,i,min,max;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d",&n);
        i=n&-n;      //�����õ���״��������������λ1�ķ���
        max=n|(i-1); //�����һ��1��������0���1
        min=n-i+1;   //�����һ��1����ƶ���ĩβ
        printf("%d %d\n",min,max);
    }
    return 0;
}
