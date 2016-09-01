#include<stdio.h>
#include<math.h>

int main()
{
    int limit,p,q,ansp,ansq;
    double a,min,dx;
    freopen("poj1650.txt","r",stdin);
    freopen("poj1650ans.txt","w",stdout);
    while (scanf("%lf%d",&a,&limit)!=EOF)
    {
        ansp=ansq=p=q=1; //ע�⣬һ��ʼӦ����ansp/ansq��С 
        min=10;          //���ҿ�����A=10��L<10�����������min��ΧҪע�� 
        while (p<=limit && q<=limit)
        {
            dx=a-1.0*p/q;
            if (fabs(dx)<min)
            {
                min=fabs(dx);
                ansp=p;
                ansq=q;
                //fprintf(stderr,"now ans: %d/%d , eps=%.10f\n",p,q,dx);
            }
            if (dx<=0) q++; else p++;
        }
        printf("%d %d\n",ansp,ansq);
        //fprintf(stderr,"final ans: %d/%d\n",ansp,ansq); 
    }
    return 0;
}
