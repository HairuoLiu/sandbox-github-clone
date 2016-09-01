#include<cstdio>
#include<cstring>
#include<string>
#include<queue>

using namespace std;

#define MaxN 51

struct TState
{
    int person_x,person_y;
    int box_x,box_y;
    string ans;
}p,q;  //p�ǵ�ǰ���ӹ��ѹ����в�����״̬�����˵Ĺ���������������ӵ�ռλ

struct TState2
{
    int x,y;
    string ans;
}P,Q;  //P�ǵ�ǰ�˵Ĺ��ѹ����в�����״̬�����ظ����ӵĹ�����Ϊ���

int  dx[4]={1,-1,0,0};
int  dy[4]={0,0,1,-1};
char PMove[4]={'s','n','e','w'};
char BMove[4]={'S','N','E','W'};
char map[MaxN][MaxN];

/*�˵ķ��ʱ�ǣ��˹��ѵ�ʱ�����ظ���*/
int  PVis[MaxN][MaxN];   
/*���ӵķ��ʱ�ǣ����ӹ��ѿ����ظ������޴Σ�ֻҪ�ǴӲ�ͬ
  ������롣�������һά��¼�����Ǵ��ĸ����������һά��*/
int  BVis[MaxN][MaxN][4]; 

int  sx,sy,ex,ey,bx,by;
int  r,c;

int Check(int x,int y)
{
    if (x>=0 && x<r && y>=0 && y<c) return 1;
    else return 0;
}

int BFSPerson(int start_x,int start_y,int end_x,int end_y)
{
    queue<TState2> p_que;
    int i,nx,ny;
    
    memset(PVis,0,sizeof(PVis));

    P.x=start_x;
    P.y=start_y;
    P.ans="";
    
    PVis[P.x][P.y]=1;
    PVis[p.box_x][p.box_y]=1;
    p_que.push(P);
    
    while (!p_que.empty())
    {
        P=p_que.front();
        p_que.pop();
        if (P.x==end_x && P.y==end_y) return 1;
        for (i=0;i<4;i++)
        {
            nx=P.x+dx[i];
            ny=P.y+dy[i];
            if (Check(nx,ny) && map[nx][ny]!='#' && !PVis[nx][ny])
            {
                PVis[nx][ny]=1;
                Q.ans=P.ans+PMove[i];
                Q.x=nx;
                Q.y=ny;
                p_que.push(Q);
            }
        }
    }
    return 0;
}

int BFSBox()
{
    queue<TState> b_que;
    int i,nx,ny,tx,ty;

    memset(BVis,0,sizeof(BVis));

    p.person_x=sx;
    p.person_y=sy;
    p.box_x=bx;
    p.box_y=by;
    p.ans="";
    
    b_que.push(p);
    
    while (!b_que.empty())
    {
        p=b_que.front();
        b_que.pop();
        for (i=0;i<4;i++)
        {
            nx=p.box_x+dx[i];  //���ӵ���һ��λ��
            ny=p.box_y+dy[i];
            tx=p.box_x-dx[i];  //��Ҫ�Ƶ�ǰλ�õ����ӣ���Ҫ�����λ��
            ty=p.box_y-dy[i];
            //��Ҫ�����λ�ú����ӵ���һ��λ�ö��Ϸ�
            //��������û�д��������������Ҫ�����λ��
            if (Check(tx,ty) && map[tx][ty]!='#' && Check(nx,ny)
            && map[nx][ny]!='#' && !BVis[nx][ny][i])
            {
                //��������ߵ��ƶ���λ�ã��������������
                if (BFSPerson(p.person_x,p.person_y,tx,ty))
                {
                    BVis[nx][ny][i]=1;
                    q.person_x=p.box_x;
                    q.person_y=p.box_y;
                    q.box_x=nx;
                    q.box_y=ny;
                    q.ans=p.ans+P.ans+BMove[i];
                    if (nx==ex && ny==ey) return 1;
                    b_que.push(q);
                }
            }
        }
    }
    return 0;
}

int main()
{
    int cas=1,i,j;
    freopen("poj1475.txt","r",stdin);
    freopen("poj1475ans.txt","w",stdout);
    while (scanf("%d%d",&r,&c)!=EOF && r && c)
    {
        for (i=0;i<r;i++)
        {
            scanf("%s",map[i]);
            for (j=0;j<c;j++)
            {
                if (map[i][j]=='S')
                {
                    sx=i;
                    sy=j;
                }
                if (map[i][j]=='T')
                {
                    ex=i;
                    ey=j;
                }
                if (map[i][j]=='B')
                {
                    bx=i;
                    by=j;
                }
            }
        }
        printf("Maze #%d\n",cas++);
        if (BFSBox()) printf("%s\n",q.ans.c_str());
        else printf("Impossible.\n");
        printf("\n");
    }
    return 0;
}
