/*
����޿ӵ���
1��Ҫ��C++����G++���ջ�������ΪSplay�������˻���
   �˻�����ɶ�ջ������һ�Ҫ�ӱ���ָ�
2���ܺ��ڴ棡
*/

#include<stdio.h>
#include<string.h>

#define Min(a,b) (a)<(b)?(a):(b)
#define inf  0x3f3f3f3f
#define MaxN 1000050
#pragma comment(linker, "/STACK:1024000000,1024000000")

int n,m,posr,posl;

/*----------Splay Template Start----------*/

typedef struct SplayNode* Node;

struct SplayNode
{
    Node pre,ch[2];
    int value/*,lazy,min*/;   //����ֵ��lazy��ǣ�������Сֵ
    int size,rev;         //������С����ת���
    void init(int _value)
    {
        pre=ch[0]=ch[1]=NULL;
        /*min=*/value=_value;
        //lazy=0;
        size=1;
        rev=0;
    }
}mem[MaxN];      //�ڴ��
int memtop;      //�ڴ���ѷ��䵽�����λ��

/*
Node stack[MaxN]; //�ڴ�ػ���ջ
int stacktop;     //ջ��ָ��
*/

Node root;

inline int GetSize(Node &x)  //ȡ��x������С����Ҫ�ǽ��x=NULL�����
{
    return x?x->size:0;
}

void PushDown(Node &x)  //��x�������
{
    if (!x) return;
    /*if (x->lazy)
    {
        int w=x->lazy;
        x->value+=w;
        if (x->ch[0])
        {
            x->ch[0]->lazy+=w;
            x->ch[0]->min+=w;
        }
        if (x->ch[1])
        {
            x->ch[1]->lazy+=w;
            x->ch[1]->min+=w;
        }
        x->lazy=0;
    }*/
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
    //x->min=x->value;
    if (x->ch[0])
    {
        //x->min=Min(x->min,x->ch[0]->min);
        x->size+=x->ch[0]->size;
    }
    if (x->ch[1])
    {
        //x->min=Min(x->min,x->ch[1]->min);
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

    /*if (stacktop>0)
    {
        t=stack[stacktop];
        stacktop--;
    }
    else*/
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
    //x->min+=value;
    //x->lazy+=value;
    Splay(x,root);
}

void Reverse(int a,int b)        //����[a,b]�е�����ת
{
    SelectOperateSegment(a,b);
    root->ch[1]->ch[0]->rev^=1;
    Node x=root->ch[1]->ch[0];
    Splay(x,root);
}

void Erase(int pos)              //Ĩȥ��pos��Ԫ��
{
    SelectOperateSegment(pos,pos);
    PushDown(root->ch[1]);
    //stack[++stacktop]=root->ch[1]->ch[0];  //�����ڴ�
    root->ch[1]->ch[0]=NULL;
    Node x=root->ch[1];
    Splay(x,root);
}

void InOrderTraversal(Node x)
{
    if (!x) return;
    PushDown(x);
    InOrderTraversal(x->ch[0]);
    if (x->value!=inf)
    {
        printf("%d",x->value);
        n--;
        if (n) printf(" ");
    }
    InOrderTraversal(x->ch[1]);
}

void InitSplayTree()
{
    int i;
    memtop=0;
    root=&mem[memtop];
    memtop++;
    root->init(inf);
    root->ch[1]=&mem[memtop];
    memtop++;
    root->ch[1]->init(inf);
}

/*----------Splay Template Over----------*/

int main()
{
    int i,t,val;
    char cmd[255];
    freopen("hdoj4286.txt","r",stdin);
    freopen("hdoj4286ans.txt","w",stdout);
    scanf("%d",&t);
    while (t--)
    {
        scanf("%d",&n);
        InitSplayTree();
        for (i=0;i<n;i++)
        {
            scanf("%d",&val);
            Insert(i,val);
        }

        scanf("%d%d",&posl,&posr);
        posl--;

        scanf("%d\n",&m);
        for (i=0;i<m;i++)
        {
            scanf("%s",cmd);
            if (strcmp(cmd,"MoveLeft")==0)
            {
                scanf("%s",cmd);
                if (cmd[0]=='R') posr--;
                if (cmd[0]=='L') posl--;
                if (posl<0) posl=0;
                if (posr<0) posr=0;
                scanf("\n");
            }
            if (strcmp(cmd,"MoveRight")==0)
            {
                scanf("%s",cmd);
                if (cmd[0]=='R') posr++;
                if (cmd[0]=='L') posl++;
                if (posr>n) posr=n;
                if (posl>n) posl=n;
                scanf("\n");
            }
            if (strcmp(cmd,"Insert")==0)
            {
                scanf("%s %d\n",cmd,&val);
                if (cmd[0]=='L') Insert(posl,val);
                if (cmd[0]=='R') Insert(posr,val);
                posr++;
                n++;
            }
            if (strcmp(cmd,"Delete")==0)
            {
                scanf("%s",cmd);
                scanf("\n");
                if (n==0) continue;
                if (cmd[0]=='L') Erase(posl+1);
                if (cmd[0]=='R') Erase(posr);
                posr--;
                n--;
            }
            if (strcmp(cmd,"Reverse")==0)
            {
                Reverse(posl+1,posr);
                scanf("\n");
            }
        }
        InOrderTraversal(root);
        printf("\n");
    }
    return 0;
}
