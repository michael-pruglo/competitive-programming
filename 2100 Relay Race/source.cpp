#include<iostream>

const int MAX_N = 300, BIG = 1e9;
int N, a[MAX_N+10][MAX_N+10], dp[MAX_N+10][MAX_N+10][2];

int max4(int a, int b, int c, int d) { return std::max(std::max(a,b), std::max(c,d)); }

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);

    std::cin>>N;
    for (int i = 1; i <= N; ++i)
        for (int j = 1; j <= N; ++j)
            std::cin>>a[i][j];

    for (int i = 0; i <= N; ++i)
        for (int j = 0; j <= N; ++j)
            dp[i][j][0] = dp[i][j][1] = -BIG;
    dp[1][1][0] = a[1][1];

    for (int d = 3; d <= N+N; ++d)
        for (int i1 = std::max(1, d-N); i1 <= std::min(d-1, N) ; ++i1)
        for (int i2 = i1;               i2 <= std::min(d-1, N) ; ++i2)
        {
            int j1 = d-i1, j2 = d-i2;
            dp[i1][i2][d&1] = a[i1][j1] + (i1!=i2?a[i2][j2]:0) + max4(dp[i1  ][i2  ][~d&1],
                                                                      dp[i1-1][i2  ][~d&1],
                                                                      dp[i1  ][i2-1][~d&1],
                                                                      dp[i1-1][i2-1][~d&1]);
        }

    std::cout<<dp[N][N][0];
}
