#include<stdio.h>
#include<string.h>

#define Max(a,b) (a)>(b)?(a):(b)
#define Min(a,b) (a)<(b)?(a):(b)
#define MaxN     210000

/*----------BKDR Hash Table Template----------*/
#define MOD      100007
#define BKDRSeed 131
#define INSERT   0
#define QUERY    1

struct TNode
{
    struct TNode* next;
    char s[255];
}mem[MaxN],*hash[MOD],*memtop;
int n;

int BKDRHash(const char* str)
{
    register int hash=0;
    while (*str) hash=hash*BKDRSeed+(*str++);
    return (hash&0x7fffffff)%MOD;
}

int Find(const char* s,int mode)  /*��ѯһ���ַ������ڴ��λ�ã�û�������*/
{
    int code=BKDRHash(s);
    struct TNode* p=hash[code];
    while (p)
    {
        if (!strcmp(p->s,s)) return p-mem;
        else p=p->next;
    }
    if (mode==INSERT)
    {
        strcpy(memtop->s,s);
        memtop->next=hash[code];   /*ͷ�巨*/
        hash[code]=memtop++;
        return memtop-mem-1;
    }
    else if (mode==QUERY) return -1;
}

void InitHash()
{
    memset(hash,0,sizeof(hash));
    memtop=mem;
}
/*----------BKDR Hash Table Template----------*/

int main()
{
    char s[100],*p;
    int id;
    freopen("hdu1880.txt","r",stdin);
    freopen("hdu1880ans.txt","w",stdout);
    InitHash();
    while(scanf("%s",s)&&s[0]!='@')
    {
        Find(s,INSERT);
        getchar();
        gets(s);
        Find(s,INSERT);
    }
    scanf("%d",&n);
    getchar();
    while (n--)
    {
        gets(s);
        id=Find(s,QUERY);
        if (id==-1)
        {
            puts("what?");
            continue;
        }
        p=mem[id^1].s; /*��Ϊ����͹����Ǹ�1�ģ�����ֱ��������һλ����*/
        if(p[0]!='[') puts(p);
        else
        {
            while (*(++p)!=']') putchar(*p);
            printf("\n");
        }
    }
    return 0;
}
