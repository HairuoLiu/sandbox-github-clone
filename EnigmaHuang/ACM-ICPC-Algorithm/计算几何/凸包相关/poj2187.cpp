#include<stdio.h>
#include<math.h>

#define eps  1e-7
#define MaxN 50001

struct Point
{
    double x,y;
    Point(double a=0,double b=0){x=a;y=b;}
};

typedef Point Vector;

Vector operator + (Point a,Point b)
{
    return Vector(a.x+b.x,a.y+b.y);
}

Vector operator - (Point a,Point b)
{
    return Vector(a.x-b.x,a.y-b.y);
}

Vector operator * (Point a,double k)
{
    return Vector(a.x*k,a.y*k);
}

Vector operator / (Point a,double k)
{
    return Vector(a.x/k,a.y/k);
}


inline double dis(Point &a,Point &b)
{
    return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}

/*------Graham��͹��----*/
/*
�õ�sp-op��ep-op�Ĳ��
>0ʱep��opsp����ʱ�뷽��<0ʱ˳ʱ�룬=0ʱ����
*/
inline double Cross(Point sp,Point ep,Point op)
{
    return (sp.x-op.x)*(ep.y-op.y)-(ep.x-op.x)*(sp.y-op.y);
}

inline int cmp(Point &a,Point &b)
{
    if (a.y==b.y) return (a.x<b.x);
    return (a.y<b.y);
}

//����eps�ľ����жϴ�/С����
inline int epssgn(double x)
{
    if (fabs(x)<eps) return 0;
    else return x<0?-1:1;
}

//�����еĵ����һ������
void QSort(Point p[],int l,int r)
{
    int i=l,j=r;
    Point mid=p[(l+r)/2],swap;
    while (i<=j)
    {
	while (cmp(p[i],mid)) i++;
	while (cmp(mid,p[j])) j--;
	if (i<=j)
	{
	    swap=p[i];
	    p[i]=p[j];
	    p[j]=swap;
	    i++;j--;
	}
    }
    if (i<r) QSort(p,i,r);
    if (l<j) QSort(p,l,j);
}

//nΪԭͼ�ĵ�����p[]Ϊԭͼ�ĵ㣨0~n-1����topΪ͹�����������0~top-1����res[]Ϊ͹������±꣬��
int Graham(Point p[],int n,int res[])
{
    int i,len,top;
    top=1;
    QSort(p,0,n-1);
    for (i=0;i<3;i++) res[i]=i;
    for (i=2;i<n;i++)
    {
        while (top && epssgn(Cross(p[i],p[res[top]],p[res[top-1]]))>=0) top--;
        res[++top]=i;
    }
    len=top;
    res[++top]=n-2;
    for (i=n-3;i>=0;i--)
    {
        while (top!=len && epssgn(Cross(p[i], p[res[top]], p[res[top-1]]))>=0) top--;
        res[++top]=i;
    }
    return top;
}

//�������������������������Ҫ����2
double Cross(Vector a,Vector b)
{
    return a.x*b.y-b.x*a.y;
}

//��ת������͹��p[res[1~chnum]]��ֱ�������������appnum���洢��app[][2]�� 
double Diameter(Point p[],int res[],int chnum,int app[][2],int &appnum) //AntiPodal Point
{
    int i,j;
    double ret=0,nowlen;
    res[chnum]=res[0];
    j=1;
    appnum=0;
    for (i=0;i<chnum;i++)
    {
        //��סi������ǰ��תj�����������Ļ���һֱתһ��ȥ 
        while (Cross(p[res[i]]-p[res[i+1]],p[res[j+1]]-p[res[i+1]])
              <Cross(p[res[i]]-p[res[i+1]],p[res[j]]  -p[res[i+1]])) 
              j=(j+1)%chnum; 
        app[appnum][0]=res[i];
        app[appnum][1]=res[j];
        appnum++;
        nowlen=dis(p[res[i]],p[res[j]]);
        if (nowlen>ret) ret=nowlen;
        nowlen=dis(p[res[i+1]],p[res[j+1]]);
        if (nowlen>ret) ret=nowlen;
    }
    return ret;
}
/*------Graham��͹��----*/

Point p[MaxN];
int   res[MaxN];
int   chnum;
int   app[MaxN][2];

int main()
{
    int i,n,appnum;
    double ans;
    freopen("poj2187.txt","r",stdin);
    freopen("poj2187ans.txt","w",stdout);
    while (scanf("%d",&n)!=EOF)
    {
        for (i=0;i<n;i++) scanf("%lf%lf",&p[i].x,&p[i].y);
        if (n<3) printf("%.f\n",dis(p[0],p[1])*dis(p[0],p[1]));
        else
        {
            chnum=Graham(p,n,res);
            ans=Diameter(p,res,chnum,app,appnum);
            /*��ת�����õĵ�����Ϣ
            for (i=0;i<chnum;i++) fprintf(stderr,"%.2f %.2f\n",p[res[i]].x,p[res[i]].y);
            for (i=0;i<appnum;i++) 
            {
                fprintf(stderr,"APP : (%.2f %.2f)",p[app[i][0]].x,p[app[i][0]].y);
                fprintf(stderr,"-- (%.2f %.2f)",p[app[i][1]].x,p[app[i][1]].y);
                fprintf(stderr," \t dist=%.2f\n",dis(p[app[i][0]],p[app[i][1]]));
            }
            */
            /*����д��
            ans=0;
            for (i=0;i<chnum-1;i++)
                for (j=i+1;j<chnum;j++)
                    ans=max(ans,dis(p[res[i]],p[res[j]]));
            */
            printf("%.f\n",ans*ans);
        }
    }
    return 0;
}
