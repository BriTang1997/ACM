#include<queue>
#include<set>
#include<cstdio>
#include <iostream>
#include<algorithm>
#include<cstring>
#include<cmath>
using namespace std;
/*
    ac自动机
*/
struct acnode{
    int sum;
    acnode* next[26];
    acnode* fail;
    acnode(){
        for(int i =0;i<26;i++)
            next[i]=NULL;
        fail= NULL;
        sum=0;
    }
};
acnode *root;
int cnt;
acnode* newnode(){
    acnode *p = new acnode;
    for(int i =0;i<26;i++)
        p->next[i]=NULL;
    p->fail = NULL;
    p->sum=0;
    return p;
}
//插入函数
void Insert(char *s)
{
    acnode *p = root;
    for(int i = 0; s[i]; i++)
    {
        int x = s[i] - 'a';
        if(p->next[x]==NULL)
        {
            acnode *nn=newnode();
            for(int j=0;j<26;j++)
                nn->next[j] = NULL;
            nn->sum = 0;
            nn->fail = NULL;
            p->next[x]=nn;
        }
        p = p->next[x];
    }
    p->sum++;
}
//获取fail指针，在插入结束之后使用
void getfail(){
    queue<acnode*> q;
	for(int i = 0 ; i < 26 ; i ++ )
	{
		if(root->next[i]!=NULL){
			root->next[i]->fail = root;
			q.push(root->next[i]);
		}
	}
    while(!q.empty()){
        acnode* tem = q.front();
        q.pop();
        for(int i = 0;i<26;i++){
            if(tem->next[i]!=NULL)
            {
                acnode *p;
                if(tem == root){
                    tem->next[i]->fail = root;
                }
                else
                {
                    p = tem->fail;
                    while(p!=NULL){
                        if(p->next[i]!=NULL){
                            tem->next[i]->fail = p->next[i];
                            break;
                        }
                        p=p->fail;
                    }
                    if(p==NULL)
                        tem->next[i]->fail = root;
                }
                q.push(tem->next[i]);
            }
        }
    }
}
//匹配函数
void ac_automation(char *ch)
{
    acnode *p = root;
    int len = strlen(ch);
    for(int i = 0; i < len; i++)
    {
        int x = ch[i] - 'a';
        while(p->next[x]==NULL && p != root)//没匹配到，那么就找fail指针。
            p = p->fail;
        p = p->next[x];
        if(!p)
            p = root;
        acnode *temp = p;
        while(temp != root)
        {
           if(temp->sum >= 0)
            /*
                在这里已经匹配完毕了，执行想执行的操作即可，这里是cnt++
            */
           {
               cnt += temp->sum;
               temp->sum = -1;
           }
           else break;
           temp = temp->fail;
        }
    }
}

int main()
{
    cnt = 0;
    int n;
    cin>>n;
    char c[101];
    root = newnode();
    for(int i = 0 ;i < n;i++){
        scanf("%s",c);
        Insert(c);
    }
    getfail();
    int m ;
    cin>> m;
    for(int i = 0;i<m;i++){
        scanf("%s",c);
        ac_automation(c);
    }
    cout<<cnt<<endl;
    return 0;
}
