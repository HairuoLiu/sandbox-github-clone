////http://www.cnblogs.com/Booble/archive/2010/10/10/1847163.html 

#include <stdio.h>
#include <math.h>
#include <algorithm>

#define MaxN 5050
using namespace std;

struct TNode
{
    int l,r;
    int lcov,rcov;          //���Ҷ˵��Ƿ񱻸���
    int count,linecnt,len;  //�����ǵĴ�����������������������䳤��
}node[MaxN*3];

struct TScanSegment
{
    int x,y1,y2;
    int flag;     //flag��1=��ߣ�-1=����
    bool operator < (TScanSegment seg2) const //��x����xͬ�����ǰ 
    {
        if (this->x==seg2.x) return (this->flag>seg2.flag);
        else return (this->x<seg2.x);
    }
}seg[MaxN*2];

int y[MaxN*2];     //��¼y����
int flag; 

void BuildTree(int left,int right,int u)
{
    int mid; 
    node[u].l=left;
    node[u].r=right;
    node[u].len=node[u].linecnt=node[u].count=0;
    if (left+1==right) return;
    mid=(left+right)/2;
    BuildTree(left,mid,u*2);
    BuildTree(mid,right,u*2+1);
}

void UpdateNode(int u)  //���³��ȺͰ����������� 
{                   
    if (node[u].count>0) 
    {
        node[u].len=y[node[u].r]-y[node[u].l];
        node[u].linecnt=node[u].lcov=node[u].rcov=1;
    }
    else if (node[u].l+1==node[u].r)
    {
        node[u].len=0;
        node[u].linecnt=node[u].lcov=node[u].rcov=0;
    }
    else     //������������ֵȷ����ǰ���ֵ 
    {
        node[u].len=node[u*2].len+node[u*2+1].len;
        node[u].lcov=node[u*2].lcov;
        node[u].rcov=node[u*2+1].rcov;
        node[u].linecnt=node[u*2].linecnt+node[u*2+1].linecnt 
                       -node[u*2].rcov*node[u*2+1].lcov;
    }
}

void SegmentUpdate(int left,int right,int u)
{
    int mid;
    if (y[node[u].l]==left && y[node[u].r]==right)  //�ҵ�Ŀ�����䣬����֮ 
    {
        node[u].count+=flag;
        UpdateNode(u);
        return;
    }
    mid=y[(node[u].l+node[u].r)/2];
    //���������� 
    if (right<=mid) SegmentUpdate(left,right,u*2);
    else if (left>=mid) SegmentUpdate(left,right,u*2+1);
    else
    {
        SegmentUpdate(left,mid,u*2);
        SegmentUpdate(mid,right,u*2+1);
    }
    //������������Ҫ���¸��µ�ǰ�ڵ� 
    UpdateNode(u);
}

int main ()
{
    int n,m,i,j,k;
    int x1,y1,x2,y2;
    int Perimeter;   //�ܳ� 
    int PreYCover;   //��һ��ɨ����λ��Y�Ḳ�ǳ��Ⱥ�
    int NowParaXCnt; //��ǰƽ����X��ıߵ�����
    freopen("poj1177.txt","r",stdin);
    freopen("poj1177ans.txt","w",stdout);
    while (scanf("%d",&n)!=EOF)
    {
        m=0;
        for (i=0;i<n;i++)
        {
            scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
            seg[m].x =x1;
            seg[m].y1=y1;
            seg[m].y2=y2;
            seg[m].flag=1;
            y[m++]=y1;
            seg[m].x =x2;
            seg[m].y1=y1;
            seg[m].y2=y2;
            seg[m].flag=-1;
            y[m++]=y2;
        }
        sort(y,y+m);
        sort(seg,seg+m);
        //��ɢ�� 
        k=1;
        for (i=1;i<m;i++) if (y[i]!=y[i-1]) y[k++]=y[i];
        
        BuildTree(0,k-1,1);
        
        Perimeter=0;
        PreYCover=0;
        NowParaXCnt=0;         
        for (i=0;i<m;i++)
        {
            flag=seg[i].flag;
            SegmentUpdate(seg[i].y1,seg[i].y2,1);
            //����ƽ��X��ıߵĳ���=��ǰɨ������ƽ��X��ı���*x����ı�ֵ 
            if (i>0) Perimeter+=2*NowParaXCnt*(seg[i].x-seg[i-1].x);
            //����ƽ��Y��ıߵĳ���=ɨ����ǰ��λ����ɨ�踲�ǳ���֮��ľ���ֵ 
            Perimeter+=abs(node[1].len-PreYCover);   
            //����Y�Ḳɨ�踲�ǳ��Ⱥ�ƽ��X��ıߵĳ��� 
            PreYCover=node[1].len;
            NowParaXCnt=node[1].linecnt;
        }
        printf("%d\n",Perimeter);
    }
    return 0;
}

