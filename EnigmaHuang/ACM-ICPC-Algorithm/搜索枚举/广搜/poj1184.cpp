#include<cstdio>
#include<cstring>
#include<queue>

using namespace std;

int ans,cnt;
int vis[6][6][6][6][6][6][6][10];    //0~5��λ������Ӧ��ֵ��6�������λ�ã�7������״̬

int mouse[10][6]=                    //����10�ַ������
{
    1,0,0,0,0,0,
    1,1,0,0,0,0,
    1,1,1,0,0,0,
    1,1,1,1,0,0,
    1,1,1,1,1,0,
    1,1,1,1,1,1,
    1,0,0,0,0,1,
    1,1,0,0,0,1,
    1,1,1,0,0,1,
    1,1,1,1,0,1
};

struct Node
{
    int s[6];
    int pos,step,state;
}cur,now;
int value[44000][8];     // 0~5 ��Ӧ��s��ֵ 6~state 7~step   ������״̬��¼����
queue<Node>q;

int GetState(int *st)           //��ȡ������״̬
{
    int i,j,flag;
    for (i=0;i<10;i++)
    {
        flag=1;
        for (j=0;j<6;j++) if (mouse[i][j]!=st[j]) flag=0;
        if (flag) return i;
    }
}

int Abs(int i)
{
    return i>0?i:-i;
}

void BFS()
{
    int i,j,temp;
    int now_pos,now_step,now_state;
    int s1[6],s2[6],s22[6],st[6];
    while (!q.empty()) q.pop();
    memset(vis,0,sizeof(vis));
    
    //��012345��ʼ����
    cnt=0;
    for (i=0;i<6;i++) cur.s[i]=i;
    cur.pos=0;
    cur.step=0;
    cur.state=0;
    q.push(cur);
    vis[0][1][2][3][4][5][0][0]=1;
    
    while (!q.empty())
    {
        now       = q.front();
        now_step  = now.step;
        now_pos   = now.pos;
        now_state = now.state;
        memcpy(s1,mouse[now_state],sizeof(s1));
        memcpy(s2,now.s,sizeof(s2));
        cnt++;
        for (i=0;i<6;i++) value[cnt][i]=s2[i];
        value[cnt][6]=now_state;
        value[cnt][7]=now_step;
        
        if (now_pos!=0)   //����
        {
            cur.pos=now_pos-1;
            memcpy(st,s1,sizeof(s1));
            st[now_pos-1]=1;
            cur.state=GetState(st);
            if (!vis[s2[0]][s2[1]][s2[2]][s2[3]][s2[4]][s2[5]][now_pos-1][cur.state])
            {
                vis[s2[0]][s2[1]][s2[2]][s2[3]][s2[4]][s2[5]][now_pos-1][cur.state]=1;
                memcpy(cur.s,s2,sizeof(s2));
                cur.step=now_step+1;
                q.push(cur);
            }
        }
        
        if (now_pos!=5)   //����
        {
            cur.pos=now_pos+1;
            memcpy(st,s1,sizeof(s1));
            st[now_pos+1]=1;
            cur.state=GetState(st);
            if (!vis[s2[0]][s2[1]][s2[2]][s2[3]][s2[4]][s2[5]][now_pos+1][cur.state])
            {
                vis[s2[0]][s2[1]][s2[2]][s2[3]][s2[4]][s2[5]][now_pos+1][cur.state]=1;
                memcpy(cur.s,s2,sizeof(s2));
                cur.step=now_step+1;
                q.push(cur);
            }
        }
        
        if (now_pos!=0)   //��0��λ�ý���
        {
            memcpy(st,s1,sizeof(s1));
            memcpy(s22,s2,sizeof(s2));
            temp=s22[now_pos];
            s22[now_pos]=s22[0];
            s22[0]=temp;
            st[0]=1;
            cur.state=GetState(st);
            if (!vis[s22[0]][s22[1]][s22[2]][s22[3]][s22[4]][s22[5]][now_pos][cur.state])
            {
                vis[s22[0]][s22[1]][s22[2]][s22[3]][s22[4]][s22[5]][now_pos][cur.state]=1;
                cur.step=now_step+1;
                cur.pos=now_pos;
                memcpy(cur.s,s22,sizeof(s22));
                q.push(cur);
            }
        }
        
        if (now_pos!=5)    //��5��λ�ý���
        {
            memcpy(st,s1,sizeof(s1));
            memcpy(s22,s2,sizeof(s2));
            temp=s22[now_pos];
            s22[now_pos]=s22[5];
            s22[5]=temp;
            st[5]=1;
            cur.state=GetState(st);
            if (!vis[s22[0]][s22[1]][s22[2]][s22[3]][s22[4]][s22[5]][now_pos][cur.state])
            {
                vis[s22[0]][s22[1]][s22[2]][s22[3]][s22[4]][s22[5]][now_pos][cur.state]=1;
                cur.step=now_step+1;
                cur.pos=now_pos;
                memcpy(cur.s,s22,sizeof(s22));
                q.push(cur);
            }
        }
        q.pop();
    }
}

int main()
{
    int i,j,sum,flag;
    char s1[10],s2[10];
    int start[10],end[10];
    freopen("poj1184.txt","r",stdin);
    freopen("poj1184ans.txt","w",stdout);
    BFS();                           // һ��BFS���ܹ�����ǰ���ֲ������ÿ�����ֶ�Ӧ��λ�ü�������״̬
    while(scanf("%s%s",s1,s2)!=EOF)
    {
        for (i=0;i<6;i++)
        {
            start[i]=s1[i]-'0';
            end[i]=s2[i]-'0';
        }
        ans=0x3f3f3f3f;
        for (i=1;i<=cnt;i++)                     // ÿ��ö�������������ans
        {
            sum=0;
            flag=1;
            for (j=0;j<6;j++)
            {
                //ֻ�б��������˵�λ�ò��ܸı��С
                if (mouse[value[i][6]][j]) sum+=Abs(end[j]-start[value[i][j]]);
                //���û���ʣ���ֵ��������״̬��ͬ���϶�����
                else if (end[j]!=start[value[i][j]]) flag=0;
            }
            if (flag && ans>sum+value[i][7]) ans=sum+value[i][7];
        }
        printf("%d\n",ans);
    }
}
