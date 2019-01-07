#include<iostream>
#include<cstdio>

const int MAX_N = 4000, MAX_K = 800, INF = int(2e9);
int N,K, u[MAX_N+10][MAX_N+10];
struct {int val,opt;} dp[MAX_N+10][MAX_K+10];

inline int cost(int l, int r) { return (u[r][r]+u[l-1][l-1]-u[l-1][r]-u[r][l-1])/2; }

int main()
{
#ifndef ONLINE_JUDGE
    freopen("C:\\Users\\Micklepru\\ClionProjects\\Competitions\\test.txt", "r", stdin);
#endif

    scanf("%d%d\n", &N, &K);
    for (int i = 1; i <= N; ++i)
        for (int j = 1; j <= N; ++j)
        {
            u[i][j] = getchar()-'0';
            u[i][j] += u[i-1][j]+u[i][j-1]-u[i-1][j-1];
            getchar();
        }

    for (int i = 1; i <= N; ++i)
    {
        dp[i][1].val = cost(1, i);
        dp[i][1].opt = 1;
    }

    for (int i = 2; i <= N; ++i)
    {
        dp[i][K+1].opt = i-1;
        for (int k = K; k > 1; --k)
        {
            dp[i][k].val = INF;
            for (int j = dp[i-1][k].opt; j <= dp[i][k+1].opt; ++j)
            {
                int val = dp[j][k-1].val + cost(j+1, i);
                if (dp[i][k].val > val)
                {
                    dp[i][k].val = val;
                    dp[i][k].opt = j;
                }
            }
        }
    }

    printf("%d", dp[N][K]);
}
