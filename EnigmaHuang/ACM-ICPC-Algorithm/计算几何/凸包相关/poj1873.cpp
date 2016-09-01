#include<stdio.h>
#include<math.h>
#include<string.h>

#define eps  1e-7
#define MaxN 16
#define pi   3.1415926535

struct Point
{
    double x,y;
    int v,l;
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
/*------Graham��͹��----*/

Point  tree[MaxN],p[MaxN];
int    res[MaxN],cut[MaxN],ansp[MaxN];
int    chnum,ansn,n;
double minv,ansl;

void DFS(int depth,int CutNum)
{
    int i,j,ExistNum;
    double need,sumv,suml;
    if (depth==n)
    {
        if (CutNum==0 || CutNum==n) return;//û��������ȫ�����ˣ�ֱ�ӷ���
        ExistNum=n-CutNum;
        sumv=suml=0;
        for (i=0;i<n;i++) if (cut[i])
        {
	    sumv+=tree[i].v;
	    suml+=tree[i].l;
        }
        if (sumv>minv) return ; //���ڵ�ǰ���Ž�
        for (i=j=0;i<n;i++) if (!cut[i]) p[j++]=tree[i];
	if (ExistNum==1) need=0;
	else if (ExistNum==2) need=2*dis(p[0],p[1]);
	else
	{
	    chnum=Graham(p,ExistNum,res);
	    need=0;
	    for (i=0;i<chnum;i++) need+=dis(p[res[i]],p[res[(i+1)%chnum]]);
	}
	if (suml>=need)
	{
	    minv=sumv;
	    ansl=suml-need;
	    ansn=CutNum;
	    for (i=j=0;i<n;i++) if (cut[i]) ansp[j++]=i;
	}
    }
    else
    {
        cut[depth]=0;
        DFS(depth+1,CutNum);
        cut[depth]=1;
        DFS(depth+1,CutNum+1);
    }
}

int main()
{
    int i,t=0;
    freopen("poj1873.txt","r",stdin);
    freopen("poj1873ans.txt","w",stdout);
    while (scanf("%d",&n) && n)
    {
        minv=99999999;
        for (i=0;i<n;i++) scanf("%lf%lf%d%d", &tree[i].x,&tree[i].y,&tree[i].v,&tree[i].l);
        memset(cut,0,sizeof(cut));
        DFS(0,0);
        printf("Forest %d\nCut these trees: ",++t);
        for (i=0;i<ansn;i++) printf("%d ",ansp[i]+1);
        printf("\nExtra wood: %.2f\n\n",ansl);
    }
}
