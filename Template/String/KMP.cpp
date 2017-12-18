#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;
const int N=100;
char str[100],ptr[100];
int next[100];
string ans;
void getnext()
{
    int i,n,k;
    n=strlen(ptr);
    memset(next,0,sizeof(next));
    k=0;
    for(i=1;i<n;i++)
    {
        while(k>0 && ptr[k]!=ptr[i])
            k=next[k];
        if(ptr[k]==ptr[i]) k++;
        next[i+1]=k;
    }
    for(int i = 1;i<=n;i++){
        cout<<next[i]<<" ";
    }
    cout<<endl;
}
int kmp(char *a,char *b)
{
    int i=0,j=0;
    int len1=strlen(a);
    int len2=strlen(b);
    getnext();
    while(i<len1&&j<len2)
    {
        if(j==0||a[i]==b[j])
        {   i++;j++;       }
        else j=next[j+1];
    }
    if(j>=len2)
        return i-j;
    else
        return -1;
}
int main(){
	while( scanf( "%s%s", str, ptr ) )
	{
        int ans = kmp(str,ptr);
        if(ans!=-1)
            printf( "%d\n", kmp( str,ptr ));
        else
            printf("404 Not find\n");
	}
	return 0;
}
