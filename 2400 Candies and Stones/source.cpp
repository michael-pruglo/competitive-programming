#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn=20000+10,maxh=11000;
int n,m,p;
int x[maxn],y[maxn];
int ans[maxh][maxn/32+1];
int d[2][maxn];
char out[maxn*2],*outp=out;
inline int add(int a,int b)
{
    int t=a+b;
    if(t>=p) return t-p; else return t;
}
void solve(int n,int m,bool first)
{
    //printf("solve %d %d %d\n",n,m,first);
    int *f=d[0],*g=d[1];
    memset(ans,0,sizeof(ans));
    f[0]=add(x[0],y[0]);
    for(int i=1;i<m;i++)
    {
        f[i]=f[i-1]+add(x[0],y[i]);
    }
    for(int i=1;i<n;i++)
    {
        g[0]=f[0]+add(x[i],y[0]);
        if(n-i<maxh) ans[n-i][0]=1;
        for(int j=1;j<m;j++)
        {
            int t=x[i]+y[j];
            if(t>=p) t-=p;
            int v0=g[j-1];
            int v1=f[j];
            if(v0<=v1)
            {
                g[j]=v1+t;
                if(n-i<maxh) ans[n-i][j>>5]|=1<<(j&31);
            }
            else
            {
                g[j]=v0+t;
            }
        }
        swap(f,g);
    }
    //puts("!");
    if(first)
    {
        printf("%d\n",f[m-1]);
    }
    int i=n-1,j=m-1;
    while(i>n-maxh&&(i>0||j>0))
    {
        if(ans[n-i][j>>5]&(1<<(j&31)))
        {
            i--;
            *outp++='C';
        }
        else
        {
            j--;
            *outp++='S';
        }
    }
    if(n>=maxh)
    {
        //printf("got %d %d\n",i,j);
        solve(i+1,j+1,false);
    }
}
int main()
{
    scanf("%d%d%d",&n,&m,&p);
    for(int i=0;i<n;i++)
    {
        scanf("%d",&x[i]);
        x[i]%=p;
    }
    for(int i=0;i<m;i++)
    {
        scanf("%d",&y[i]);
        y[i]%=p;
    }
    /*n=m=20000;
    p=1000000000;
    for(int i=0;i<n;i++) x[i]=y[i]=n;*/
    solve(n,m,true);
    for(int i=strlen(out)-1;i>=0;i--) putchar(out[i]);
    puts("");
    return 0;
}
