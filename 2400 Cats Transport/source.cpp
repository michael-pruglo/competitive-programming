#include<cstdio>
#include<algorithm>

struct ConvexHull
{
    struct Line
    {
        long long a,b;
        long long valueAt(long long x) { return a*x+b; }
        Line(long long aa=0, long long bb=0) : a(aa), b(bb) {}
        friend double intersectX(Line l1, Line l2) { return 1.0*(l2.b-l1.b)/(l1.a-l2.a); }
    };
    std::vector<Line> hull;
    void addLine(long long a, long long b)
    {
        Line l3(a,b);
        while (hull.size()>1)
        {
            Line l2 = hull.back();
            Line l1 = *(hull.end()-2);

            if (intersectX(l1,l3) <= intersectX(l1,l2))
                hull.pop_back();
            else
                break;
        }
        hull.push_back(l3);
    }
    long long proceed(int& i, long long x)
    {
        while (i+1<hull.size() && intersectX(hull[i], hull[i+1]) < double(x)) ++i;
        return hull[i].valueAt(x);
    }
};

const int MAX_N = 1e5, MAX_M = 1e5, MAX_P = 100;
int N,M,P, a[MAX_M+10], dist[MAX_N+10], bufH,bufT;
long long s[MAX_M+10], dp[MAX_P+10][MAX_M+10];

char ss[999], *temp=ss;

int main()
{
#ifndef ONLINE_JUDGE
    freopen("C:\\Users\\Micklepru\\ClionProjects\\Competitions\\test.txt", "r", stdin);
#endif
    scanf("%d%d%d",&N,&M,&P);
    for (int i = 2; i <= N; ++i)
    {
        scanf("%d",&dist[i]);
        dist[i] += dist[i-1];
    }
    getchar();
    for (int i = 1; i <= M; ++i)
    {
        gets(temp=ss);
        bufH = strtol(temp, &temp, 10);
        bufT = strtol(temp, &temp, 10);
        a[i] = bufT - dist[bufH];
    }
    std::sort(a+1, a+M+1);
    for (int i = 1; i <= M; ++i)
        s[i] = s[i-1]+a[i];


    for (int j = 1; j <= M; ++j)
        dp[1][j] = 1ll*a[j]*j-s[j];
    for (int i = 2; i <= P; ++i)
    {
        ConvexHull optim;
        int k = 0;
        for (int j = 2; j <= M; ++j)
        {
            optim.addLine(-(j-1), s[j-1]+dp[i-1][j-1]);
            dp[i][j] = 1ll*j*a[j]-s[j] + optim.proceed(k, a[j]);
        }
    }

    printf("%I64d", dp[P][M]);
}
