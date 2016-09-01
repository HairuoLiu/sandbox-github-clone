#include<stdio.h>
#include<string.h>

#define CharsetSize 26       //�ַ�����С
#define CharsetBase 'A'     //�ַ�����С�ַ�

#define MaxN 1005

using namespace std;

int dir,startr,startc;
int row,col,n;
char map[MaxN][MaxN];
int len[MaxN],ans[MaxN][3];

int dr[8]={-1,-1,0,1,1,1,0,-1};
int dc[8]={0,1,1,1,0,-1,-1,-1};

struct TTrieNode
{
    int id;
    TTrieNode *next[CharsetSize];
    TTrieNode *fail;
    TTrieNode()
    {
        fail=NULL;
        id=0;
        memset(next,NULL,sizeof(next));
    }
}mem[MaxN*100];

typedef struct TTrieNode* PTrieNode;

PTrieNode root,q[MaxN*100];

int memtop;

/*
�ֶ��ڴ�ط��䣬ע���ڴ�ش�С
����ʹ��new�ķ�ʽ���µ�һ��������û��ִ��
���ղ��������ڴ�й¶�����ڴ��ֵ��������
���Լ������ֶ��ڴ���䡣
*/
PTrieNode NewNode()
{
    mem[memtop].id=-1;
    mem[memtop].fail=NULL;
    memset(mem[memtop].next,NULL,sizeof(mem[memtop].next));
    memtop++;
    return &mem[memtop-1];
}

void InitACMem()
{
    memtop=0;
    memset(mem,0,sizeof(mem));
    root=NewNode();
}

void Insert(char *str,int id)
{
    int i,len,pos;
    PTrieNode p=root;
    len=strlen(str);
    for (i=0;i<len;i++)
    {
        pos=str[i]-CharsetBase;
        if (p->next[pos]==NULL) p->next[pos]=NewNode();//new TTrieNode();
        p=p->next[pos];
    }
    p->id=id;
}

void BuildAC()  //BFS��ʼ��failָ��
{
    PTrieNode p,pos;
    int i,head,tail;
    head=tail=0;
    q[tail++]=root;
    while (head!=tail)
    {
        p=q[head++];
        pos=NULL;
        for (i=0;i<CharsetSize;i++) if (p->next[i]!=NULL)
        {
            if (p==root) p->next[i]->fail=root;  //root��ʧ��ָ��ָ��root
            else
            {
                pos=p->fail;       //ʧ��ָ��
                while (pos!=NULL)  //�������������ƥ��Ϊ�� or �ҵ�ƥ��
                {
                    if (pos->next[i]!=NULL) //�ҵ�ƥ��
                    {
                         p->next[i]->fail=pos->next[i];
                         break;
                    }
                    pos=pos->fail;
                }
                //Ϊ�գ���ͷƥ��
                if (pos==NULL) p->next[i]->fail=root;
            }
            q[tail++]=p->next[i];
        }
    }
}

int Query(char *str)
{
    int i,pos,slen,res,id;
    PTrieNode p=root,tmp;
    res=0;
    slen=strlen(str);
    for (i=0;i<slen;i++)
    {
        pos=str[i]-CharsetBase;
        while (p->next[pos]==NULL && p!=root) p=p->fail;
        p=p->next[pos];
        if (p==NULL) p=root;
        //tmp���������׺��
        for (tmp=p;tmp!=root && tmp->id!=-1;tmp=tmp->fail)
        {
            id=tmp->id;
            ans[id][0]=startr+(i-len[id]+1)*dr[dir%8];
            ans[id][1]=startc+(i-len[id]+1)*dc[dir%8];
            ans[id][2]=dir%8;
            tmp->id=-1;
        }
    }
    return res;
}

void GetStrLineFromPosWithDir(char *str)
{
    int i=0,r=startr,c=startc;
    while (r>=0 && c>=0 && r<row && c<col)
    {
	str[i++]=map[r][c];
	r+=dr[dir%8];
	c+=dc[dir%8];
    }
    str[i]='\0';
}

int main()
{
    int i,j;
    char word[1000];
    freopen("poj1204.txt","r",stdin);
    freopen("poj1204ans.txt","w",stdout);
    while (scanf("%d%d%d",&row,&col,&n)!=EOF)
    {
        InitACMem();
        for (i=0;i<row;i++) scanf("%s",map[i]);
        for (i=0;i<n;i++)
        {
	    scanf("%s",word);
	    len[i]=strlen(word);
	    Insert(word,i);
        }
        BuildAC();
        for (i=0;i<row;i++)
        {
	    for (dir=1;dir<=3;dir++)
	    {
	    	startr=i;
	    	startc=0;
                GetStrLineFromPosWithDir(word);
		//fprintf(stderr,"startr=%d startc=%d dir=%d word=%s\n",startr,startc,dir%8,word);
		Query(word);
	    }
	    for (dir=5;dir<=7;dir++)
	    {
		startr=i;
		startc=col-1;
                GetStrLineFromPosWithDir(word);
                //fprintf(stderr,"startr=%d startc=%d dir=%d word=%s\n",startr,startc,dir%8,word);
		Query(word);
	    }
        }
        for (i=0;i<col;i++)
        {
	    for (dir=3;dir<=5;dir++)
	    {
	    	startr=0;
	    	startc=i;
                GetStrLineFromPosWithDir(word);
                //fprintf(stderr,"startr=%d startc=%d dir=%d word=%s\n",startr,startc,dir%8,word);
		Query(word);
	    }
	    for (dir=7;dir<=9;dir++)  //dir=7,0,1
	    {
	    	startr=row-1;
	    	startc=i;
                GetStrLineFromPosWithDir(word);
                //fprintf(stderr,"startr=%d startc=%d dir=%d word=%s\n",startr,startc,dir%8,word);
		Query(word);
	    }
        }
        for (i=0;i<n;i++) printf("%d %d %c\n",ans[i][0],ans[i][1],ans[i][2]+'A');
    }
    return 0;
}
