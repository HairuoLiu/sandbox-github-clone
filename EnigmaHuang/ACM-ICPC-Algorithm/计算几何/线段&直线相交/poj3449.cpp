#include<cstdio>
#include<cmath>

using namespace std;

#define eps 1e-8
#define MaxN 32 

struct Point
{
    double x,y;
    Point(double a=0,double b=0){x=a;y=b;} 
};

typedef Point Vector;

struct Polygon //��ģ���������ͣ�ע�� 
{
    int sides,itsnum;         //�������ཻ�� 
    char name,itsname[MaxN];  //��ţ��ཻ������ 
    Point p[MaxN];
};


Vector operator - (Point a,Point b)    
{
    return Vector(a.x-b.x,a.y-b.y);
}

/* 2��������*/
double Cross(Vector a,Vector b)
{
    return a.x*b.y-b.x*a.y;
}

//����eps�ľ����жϴ�/С���� 
int epssgn(double x)    
{
    if (fabs(x)<eps) return 0;
    else return x<0?-1:1;
}

int IsSegmentIntersect(Point &a1,Point &a2,Point &b1,Point &b2)
{
    double c1=Cross(a2-a1,b1-a1);
    double c2=Cross(a2-a1,b2-a1);
    double c3=Cross(b2-b1,a1-b1);
    double c4=Cross(b2-b1,a2-b1);
    //�������<=��Ϊ<�Ϳ��Ա�ɲ����˵����� 
    return (epssgn(c1)*epssgn(c2)<=0 && epssgn(c3)*epssgn(c4)<=0);
}

Polygon a[MaxN];

//��֪�����ζԽ����꣬���������� 
void FinishSqu(Polygon &src)
{
    src.sides=4;
    src.p[2]=src.p[1]; //���ƿ�
    src.p[1].x=(src.p[0].x+src.p[2].x+src.p[2].y-src.p[0].y)/2;
    src.p[1].y=(src.p[0].y+src.p[2].y+src.p[0].x-src.p[2].x)/2;
    src.p[3].x=(src.p[0].x+src.p[2].x-src.p[2].y+src.p[0].y)/2;
    src.p[3].y=(src.p[0].y+src.p[2].y-src.p[0].x+src.p[2].x)/2; 
}

//��֪�������������꣬���곤���� 
void FinishRect(Polygon &src)
{
    src.sides=4;
    src.p[3].x=src.p[2].x-src.p[1].x+src.p[0].x;
    src.p[3].y=src.p[2].y-src.p[1].y+src.p[0].y;    
}

void QSort(int l,int r)
{
    int i=l,j=r;
    char mid=a[(i+j)/2].name;
    Polygon swap;
    while (i<=j)
    {
        while (a[i].name<mid) i++;
        while (a[j].name>mid) j--;
        if (i<=j)
        {
                   swap=a[i];
                   a[i]=a[j];
                   a[j]=swap;
                   i++;j--;
        }
    }
    if (i<r) QSort(i,r);
    if (l<j) QSort(l,j);
}

int PolygonIntersect(Polygon &a,Polygon &b)
{
    int i,j;
    for (i=0;i<a.sides;i++) //����ö�ٱ��ж��ཻ 
        for (j=0;j<b.sides;j++)
            if (IsSegmentIntersect
                (a.p[i],a.p[(i+1)%a.sides],
                 b.p[j],b.p[(j+1)%b.sides])
               ) return 1;
    return 0;
}

int main()
{
    int n,i,j;
    char s[255];
    freopen("poj3449.txt","r",stdin);
    freopen("poj3449ans.txt","w",stdout);
    while (1)
    {
        n=0;
        while (1)
        {
                   scanf("%s",s);
                   if (s[0]=='.' || s[0]=='-') break;
                   a[n].name=s[0];
                   scanf("%s",s);
                   if (s[0]=='l' || s[0]=='s') a[n].sides=2;
                   else if (s[0]=='r' || s[0]=='t') a[n].sides=3;
                   else scanf("%d",&a[n].sides);
                   for (j=0;j<a[n].sides;j++) scanf(" (%lf,%lf)", &a[n].p[j].x,&a[n].p[j].y);
                   if (s[0]=='s') FinishSqu(a[n]);
            else if (s[0]=='r') FinishRect(a[n]);
            a[n].itsnum=0;
            n++;
        }
        if (s[0]=='.') break;
        
        QSort(0,n-1);     //���������һ�·������ 
        for (i=0;i<n;i++) //����ö�ٶ�����ж��ཻ 
            for (j=i+1;j<n;j++)
            {
                       if (!PolygonIntersect(a[i],a[j])) continue;
                       a[i].itsname[a[i].itsnum++]=a[j].name;
                       a[j].itsname[a[j].itsnum++]=a[i].name;
            }
        
         for (i=0;i<n;i++)
        {
            printf("%c ",a[i].name);
            if (a[i].itsnum==0) 
            {
                printf("has no intersections\n"); 
                continue;
            }
            printf("intersects with ");
            if (a[i].itsnum==1) printf("%c\n",a[i].itsname[0]);
            else if (a[i].itsnum==2) printf("%c and %c\n",a[i].itsname[0],a[i].itsname[1]);
            else 
            {
                for (j=0;j<a[i].itsnum-1;j++) printf("%c, ",a[i].itsname[j]);
                printf("and %c\n",a[i].itsname[j]);
            }
        }
        printf("\n");
    }
    return 0;
}
