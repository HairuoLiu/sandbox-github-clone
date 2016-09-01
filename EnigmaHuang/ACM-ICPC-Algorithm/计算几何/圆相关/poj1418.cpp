#include <stdio.h>
#include <math.h>

#define eps 1e-12  //1e-11����ҵ�
#define pi  acos(-1.0)
#define MaxN 130


//��ά����
struct Point
{
    double x,y;
    Point(double a=0,double b=0){x=a;y=b;}
};

struct Circle
{
    Point center;
    double r;
}c[MaxN];

typedef Point Vector;

int  n,ans;
double its[2*MaxN];  //radian of every intersection-center line with the x-axis
int  visible[MaxN];  //Բ�Ŀɼ���


//������֮���ֱ�߾���
double dis(Point a,Point b)
{
    return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}

//���Ƕȵ�����2pi��
double MainAngle(double a)
{
   while (a>2*pi) a-=2*pi;
   while (a<0) a+=2*pi;
   return a;
}

void QSort(double a[],int l,int r)
{
    int i=l,j=r;
    double mid=a[(l+r)/2],swap;
    while (i<=j)
    {
        while (a[i]<mid) i++;
        while (a[j]>mid) j--;
        if (i<=j)
        {
            swap=a[i];
            a[i]=a[j];
            a[j]=swap;
            i++;j--;
        }
    }
    if (i<r) QSort(a,i,r);
    if (l<j) QSort(a,l,j);
}

int main()
{
    int i,j,k,t,itsnum;
    Point mid1,mid2;
    double a,b,d;
    freopen("poj1418.txt","r",stdin);
    freopen("poj1418ans.txt","w",stdout);
    while (scanf("%d",&n) && n)
    {
        for (i=0;i<n;i++)
        {
            scanf("%lf%lf%lf", &c[i].center.x, &c[i].center.y, &c[i].r);
            visible[i]=0;
        }
        for (i=0;i<n;i++)
        {
            itsnum=0;
            its[itsnum++]=0;
            its[itsnum++]=2*pi;
            for (j=0;j<n;j++) if (j!=i)
            {
                d=dis(c[i].center,c[j].center);
                //�������߲��ཻ������
                if (c[i].r+c[j].r<d || c[i].r+d<c[j].r || c[j].r+d<c[i].r) continue;
                //����������ļ�������
                a=atan2(c[j].center.y-c[i].center.y,c[j].center.x-c[i].center.x);
                b=acos((c[i].r*c[i].r+d*d-c[j].r*c[j].r)/(2*c[i].r*d));
                its[itsnum++]=MainAngle(a+b);
                its[itsnum++]=MainAngle(a-b);
            }
            QSort(its,0,itsnum-1);
            for (j=0;j<itsnum-1;j++)
            {
                a=(its[j]+its[j+1])/2;
                //��֪��ΪʲôҪ+-eps����һ������
                //�������ϲ���һ��Ҳû��������

                mid1.x=c[i].center.x+(c[i].r+eps)*cos(a);
                mid1.y=c[i].center.y+(c[i].r+eps)*sin(a);
                //c[k]������c[i]��һ��Բ������c[k]������
                for (k=n-1;k>=0;k--) if (dis(mid1,c[k].center)<c[k].r) break;
                if (k>=0) visible[k]=1;

                mid2.x=c[i].center.x+(c[i].r-eps)*cos(a);
                mid2.y=c[i].center.y+(c[i].r-eps)*sin(a);
                //c[k]������c[i]��һ��Բ������c[k]������
                for (k=n-1;k>=0;k--) if (dis(mid2,c[k].center)<c[k].r) break;
                if (k>=0) visible[k]=1;
            }
        }
        ans=0;
        for (i=0;i<n;i++) if (visible[i]) ans++;
        printf("%d\n",ans);
    }
    return 0;
}
