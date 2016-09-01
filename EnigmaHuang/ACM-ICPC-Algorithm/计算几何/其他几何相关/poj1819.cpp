#include<stdio.h>
#include<math.h>

#define MaxN 1001
#define eps  1e-8

struct Circle
{
    double x,y,r;//�뾶
}s[MaxN];

int main()
{
    int i,j,n,ans,p,last,k;
    int unfix[MaxN];        //�Ƿ��ȥ(1��ȥ��0����ȥ)
    int fixpos[MaxN];       //����ȥ��Բ��λ��
    double x;
    freopen("poj1819.txt","r",stdin);
    freopen("poj1819ans.txt","w",stdout);
    while (scanf("%d",&n)!=EOF)
    {
        p=ans=0;
        last=1;
        for (i=1;i<=n;i++)
        {
            unfix[i]=1;     //����Բһ��ʼ����Ϊ��ȥ
            k=0;            //���ҽ�ǰ�治��ȥԲ����Ϊ0
            scanf("%lf",&s[i].r);
            s[i].x=s[i].y=s[i].r;  //��Բiλ�ó�ʼΪ��y�����е�λ��
            for (j=1;j<=p;j++)
            {
                x=s[fixpos[j]].x+2*sqrt(s[i].r*s[fixpos[j]].r);//���㰴fixpos[j]��i�����ƶ�iʱ��i�ĺ�����λ��
                if (x-s[i].x>eps)  //����ʱ��λ�ñ����ڵ�Ҫ������ô����Բi��λ��
                {
                    s[i].x=x;      //���º�����λ��
                    k=j;           //��¼��i���е����һ��Բ�ı��
                }
            }
            p=k;  //�ڲ���ȥԲ�������i���е�Բk��i֮�������Բ����i���벻��ȥԲ
            fixpos[++p]=i;
            if (s[i].r+s[i].x-s[last].r-s[last].x>eps) last=i;  //����i�Ƿ����һ������ȥԲ
        }
        for (i=1;i<=p;i++) unfix[fixpos[i]]=0;  //������ȥԲ��Ϊ0
        for (i=last+1;i<=n;i++) unfix[i]=1;     //��last���Բ��Ϊ��ȥԲ
        for (i=1;i<=n;i++) ans+=unfix[i];       //ͳ�ƿ�ȥԲ����
        printf("%d\n",ans);
        for (i=1;i<=n;i++) if (unfix[i]) printf("%d\n",i);
    }
    return 0;
}
