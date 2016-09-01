#include<stdio.h>

//2����
int pow2[15]={2,4,8,16,32,64,128,256,512,1024,2048,4096,8192,16384,32768};

/*
  n=��������m=�������p=ȡ��p���˵Ľ�������� 
  ���ǵ�p�������ö���Ǯ��-1��ʾһ������ 
*/
int Solve(int n,int m,int p)
{
    int i,t;
    //��ҹ���¸�����
    if (n<=2*m)
    {
        //���Ǿ����ߣ�������ż����ͬ�����ܱ���¸
        if (n!=p && (n%2==p%2)) return 1;
        //ʣ�µĶ��Ǿ�����ӵ��
        else if (n==p) return (m-(n-1)/2);
        //�����˷ֲ�����ң����ǵľ��߲�Ӱ��ȫ��
        else return 0;
    }
    //��ҹ���¸�������߲����ý��
    else if (n==2*m+1)
    {
        if (p<2*m && p&1) return 1; 
        else return 0;
    }
    t=n-2*m;
    //ʣ�µ��������Ա�������������ھ�������˵���϶�û�н��
    for (i=0;i<14;i++) if (t==pow2[i]) return 0; //2*m+2^k�ľ����߿��Ա��������ò���Ǯ 
    for (i=1;i<14;i++) if (t<pow2[i])
    {
        //����2*m+2^k�ľ����߱���
        if (p>2*m+pow2[i-1] && p<2*m+pow2[i]) return -1;
        else return 0;
    }
}

int main()
{
    int t,n,m,p,ans;
    scanf("%d",&t);
    freopen("hdoj1538.txt","r",stdin);
    freopen("hdoj1538ans.txt","w",stdout);
    while (t--)
    {
        scanf("%d%d%d",&n,&m,&p);
        ans=Solve(n,m,p);
        if (ans>=0) printf("%d\n",ans); else printf("Thrown\n");
    }
    return 0;
}   
