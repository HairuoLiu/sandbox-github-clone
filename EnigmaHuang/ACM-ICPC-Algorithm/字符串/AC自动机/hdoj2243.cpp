#include<stdio.h>
#include<string.h>

#define CharsetBase 'a'
#define CharsetSize 26       //�ַ�����С

#define MaxN 30

using namespace std;

typedef unsigned __int64 ULL;

struct TTrieNode
{
    int flag;
    int next[CharsetSize];
    int fail;
}mem[MaxN];

int root,q[MaxN];

int memtop;

int NewNode()
{
    mem[memtop].flag=0;
    mem[memtop].fail=-1;
    memset(mem[memtop].next,0,sizeof(mem[memtop].next));
    memtop++;
    return memtop-1;
}

void InitACMem()
{
    memtop=0;
    memset(mem,0,sizeof(mem));
    root=NewNode();
}

int CharPos(char c)
{
    return c-CharsetBase;
}

void Insert(char *str)
{
    int i,len,pos,p=root;
    len=strlen(str);
    for (i=0;i<len;i++)
    {
        pos=CharPos(str[i]);
        if (mem[p].next[pos]==0) mem[p].next[pos]=NewNode();
        p=mem[p].next[pos];
    }
    mem[p].flag=1;
}

void BuildAC()  //BFS��ʼ��failָ��
{
    int p,pos;
    int i,head,tail;
    head=tail=0;
    q[tail++]=root;
    while (head!=tail)
    {
        p=q[head++];
        pos=0;
        for (i=0;i<CharsetSize;i++)
        {
            if (mem[p].next[i]!=0)
            {
                if (p==root) mem[mem[p].next[i]].fail=root;  //root��ʧ��ָ��ָ��root
                else
                {
                    pos=mem[p].fail;       //ʧ��ָ��
                    while (pos!=-1)  //�������������ƥ��Ϊ�� or �ҵ�ƥ��
                    {
                        if (mem[p].next[i]!=0) //�ҵ�ƥ��
                        {
                             mem[mem[p].next[i]].fail=mem[pos].next[i];
                             mem[mem[p].next[i]].flag|=mem[mem[pos].next[i]].flag;
                             break;
                        }
                        pos=mem[pos].fail;
                    }
                    //Ϊ�գ���ͷƥ��
                    if (pos==-1) mem[mem[p].next[i]].fail=root;
                }
                q[tail++]=mem[p].next[i];
            }
            else
            {
                if (p==root) mem[p].next[i]=root;
                else mem[p].next[i]=mem[mem[p].fail].next[i];
            }
        }
    }
}

struct Matrix
{
    ULL v[MaxN*2][MaxN*2];
    int size;
    Matrix()
    {
        memset(v,0,sizeof(v));
    }
};

inline Matrix Mul(Matrix &A,Matrix &B)
{
    int i,j,k;
    Matrix C;
    C.size=A.size;
    for (i=0;i<A.size;i++)
        for (j=0;j<A.size;j++)
            for (k=0;k<A.size;k++)
                C.v[i][j]+=A.v[i][k]*B.v[k][j];
    return C;
}

Matrix Pow(Matrix A,ULL exp)
{
    int i;
    Matrix B;
    B.size=A.size;
    for (i=0;i<memtop;i++) B.v[i][i]=1;
    while (exp)
    {
        if (exp&1) B=Mul(B,A);
        A=Mul(A,A);
        exp>>=1;
    }
    return B;
}

int n,m;
Matrix Trie,res;

void TrieToMatrix()
{
    int i,j,pos;
    memset(Trie.v,0,sizeof(Trie.v));
    Trie.size=2*memtop;
    for (i=0;i<memtop;i++) if (mem[i].flag!=1)
    {
        for (j=0;j<CharsetSize;j++)
        {
            pos=mem[i].next[j];
            if (mem[pos].flag) continue;
            Trie.v[i][pos]++;
        }
    }
    //�Ҳ�����²��������λ��
    for (i=0;i<memtop;i++)
    {
	Trie.v[i][i+memtop]=1;
	Trie.v[i+memtop][i+memtop]=1;
    }
}

int main()
{
    int i;
    char word[6];
    ULL ans,exp;
    freopen("hdoj2243.txt","r",stdin);
    freopen("hdoj2243ans.txt","w",stdout);
    while (scanf("%d%d",&m,&n)!=EOF)
    {
        InitACMem();
        while (m--)
        {
            scanf("%s",word);
            Insert(word);
        }
        BuildAC();
        TrieToMatrix();
        //n+1���ݲ���A^n+...+A+I
        exp=0;
        exp=n+1LL;
        res=Pow(Trie,exp);
        //��ȥһ����λ��
        for (i=0;i<memtop;i++) res.v[i][i+memtop]-=1LL;
	ans=0;
        for (i=0;i<memtop;i++) ans+=res.v[0][i+memtop];

        //�þ���ķ�����26+26^2+...+26^n
        Trie.size=2;
        memset(Trie.v,0,sizeof(Trie.v));
        Trie.v[0][0]=26;
        Trie.v[0][1]=1;
        Trie.v[1][1]=1;
        res=Pow(Trie,exp);
	res.v[0][1]-=1;
	ans-=res.v[0][1];
	
	ans=-ans;
	
        printf("%I64u\n",ans);
    }
    return 0;
}
