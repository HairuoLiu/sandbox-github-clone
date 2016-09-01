#include<stdio.h>
#include<string.h>

#define inf  0x3f3f3f3f
#define MaxN 100005

using namespace std;

/*----------Splay Template Start----------*/

typedef struct SplayNode* Node;

struct SplayNode
{
    Node pre,ch[2];
    int value,lazy;   //����ֵ��lazy���
    int size,rev;     //������С����ת���
    long long sum;    //�����Ľ���ֵ��
    void init(int _value)
    {
        pre=ch[0]=ch[1]=NULL;
        value=_value;
        sum=1LL*value;
        lazy=0;
        size=1;
        rev=0;
    }
}mem[MaxN];      //�ڴ��
int memtop;      //�ڴ���ѷ��䵽�����λ��

Node stack[MaxN]; //�ڴ�ػ���ջ
int stacktop;     //ջ��ָ��

Node root;

inline int GetSize(Node &x)  //ȡ��x������С����Ҫ�ǽ��x=NULL�����
{
    return x?x->size:0;
}

void PushDown(Node &x)  //��x�������
{
    if (!x) return;
    if (x->lazy)
    {
        int w=x->lazy;
        x->value+=w;
        if (x->ch[0])
        {
            x->ch[0]->lazy+=w;
            x->ch[0]->sum+=1LL*w*GetSize(x->ch[0]);
        }
        if (x->ch[1])
        {
            x->ch[1]->lazy+=w;
            x->ch[1]->sum+=1LL*w*GetSize(x->ch[1]);
        }
        x->lazy=0;
    }
    if (x->rev)
    {
        Node t=x->ch[0];
        x->ch[0]=x->ch[1];
        x->ch[1]=t;
        x->rev=0;
        if (x->ch[0]) x->ch[0]->rev^=1;
        if (x->ch[1]) x->ch[1]->rev^=1;
    }
}

void Update(Node &x)  //����x�����Ϣ
{
    if (!x) return;
    x->size=1;
    x->sum=x->value;
    if (x->ch[0])
    {
        x->sum+=x->ch[0]->sum;
        x->size+=x->ch[0]->size;
    }
    if (x->ch[1])
    {
        x->sum+=x->ch[1]->sum;
        x->size+=x->ch[1]->size;
    }
}

void Rotate(Node &x,int d) //��ת������d=0��ʾ������d=1��ʾ����
{
    Node y=x->pre;
    PushDown(y);
    PushDown(x);
    PushDown(x->ch[d]);
    y->ch[!d]=x->ch[d];
    if (x->ch[d]!=NULL) x->ch[d]->pre=y;
    x->pre=y->pre;
    if (y->pre!=NULL)
    {
        if (y->pre->ch[0]==y) y->pre->ch[0]=x;
        else y->pre->ch[1]=x;
    }
    x->ch[d]=y;
    y->pre=x;
    Update(y);
    if (y==root) root=x;//��Ϊ��ָ�룬����root���ܱ�ת��ȥ��
}

void Splay(Node &src,Node &dst) // Splay�������ѽ��srcת�����dst���ӽڵ�
{
    PushDown(src);
    while (src!=dst)
    {
        if (src->pre==dst)
        {
            if (dst->ch[0]==src) Rotate(src,1);
            else Rotate(src,0);
            break;
        }
        else
        {
            Node y=src->pre,z=y->pre;
            if (z->ch[0]==y)
            {
                if (y->ch[0]==src)
                {
                    Rotate(y,1);
                    Rotate(src,1); //һ������ת
                }
                else
                {
                    Rotate(src,0);
                    Rotate(src,1); //֮������ת
                }
            }
            else
            {
                if (y->ch[1]==src)
                {
                    Rotate(y,0);
                    Rotate(src,0);  //һ������ת
                }
                else
                {
                    Rotate(src,1);
                    Rotate(src,0); // ֮������ת
                }
            }
            if (z==dst) break;//ת��֮��x�͵���ԭ��z��λ�ã����z����Ҫ���ĵط����Ϳ����˳���
        }
        Update(src);
    }
    Update(src);
}

void Select(int k,Node &f)  //�ѵ�k��Ԫ�ص���f���ӽڵ�
{
    int tmp;
    Node t;
    t=root;
    while (1)
    {
        PushDown(t);
        tmp=GetSize(t->ch[0]);  //�õ�t�������Ĵ�С
        if (k==tmp+1) break;    //�ó�t��Ϊ���ҽ�㣬�˳�
        if (k<=tmp) t=t->ch[0]; //��k�������t��ߣ�������
        else //�������ұߣ��������������У������㲻���ǵ�k��
        {
            k-=tmp+1;
            t=t->ch[1];
        }
    }
    PushDown(t);
    Splay(t,f);   //ִ����ת
}

inline void SelectOperateSegment(int l,int r)   //ѡ�����������
{
    Select(l,root);
    Select(r+2,root->ch[1]);
}

void Insert(int pos,int value)   //��posλ�ú������һ����ֵvalue
{
    Select(pos+1,root);
    Select(pos+2,root->ch[1]);
    //SelectOperateSegment(pos+1,pos);
    //����д���е����岻������ʹ��

    Node t;
    Node x=root->ch[1];

    PushDown(root);
    PushDown(x);

    if (stacktop>0)
    {
            t=stack[stacktop];
            stacktop--;
    }
    else
    {
            t=&mem[memtop];
            memtop++;
    }
    t->init(value);
    t->ch[1]=x;
    x->pre=t;
    root->ch[1]=t;
    t->pre=root;
    Splay(x,root);
}

void Add(int a,int b,int value)  //����[a,b]�е���������value
{
    SelectOperateSegment(a,b);
    Node x=root->ch[1]->ch[0];
    PushDown(x);
    Update(x);
    x->sum+=1LL*value*GetSize(x);
    x->lazy+=value;
    Splay(x,root);
}

long long GetSum(int a,int b)    //ȡ[a,b]����ĺ�
{
    SelectOperateSegment(a,b);
    Node x=root->ch[1];
    PushDown(x);
    x=x->ch[0];
    PushDown(x);
    Update(x);
    return x->sum;
}

void InitSplayTree(int *a=NULL,int n=0)
{
    int i;
    memtop=0;
    root=&mem[memtop];
    memtop++;
    root->init(inf);
    root->ch[1]=&mem[memtop];
    memtop++;
    root->ch[1]->init(inf);
    stacktop=0;
    if (a==0 || n==0) return;
    for (i=0;i<n;i++) Insert(i,a[i]);
}

/*----------Splay Template Over----------*/


int a[MaxN];

int main()
{
    char c;
    int n,m,i,swap;
    int x,y,val;
    freopen("poj3468.txt","r",stdin);
    freopen("poj3468ans.txt","w",stdout);
    while (scanf("%d%d\n",&n,&m)!=EOF)
    {
        for (i=0;i<n;i++) scanf("%d",&a[i]);
        scanf("\n");
        InitSplayTree(a,n);
        while (m--)
        {
            scanf("%c %d %d",&c,&x,&y);
            if (c=='Q')
            {
                scanf("\n");
                if (x>y)
                {
                    swap=x;
                    x=y;
                    y=swap;
                }
                printf("%lld\n",GetSum(x,y));
            }
            if (c=='C')
            {
                scanf("%d\n",&val);
                Add(x,y,val);
            }
        }
    }
    return 0;
}
