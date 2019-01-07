#include<iostream>

const int MAX_N = 4000, MAX_K = 4000, SECS_IN_DAY = 86400;
int n,k, t[MAX_N+10],d[MAX_N+10], dp[MAX_N+10][MAX_K+10], res;

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);

    std::cin>>n>>k;
    for (int j = 0; j <= k; ++j)
        dp[0][j] = 1;
    for (int i = 1; i <= n; ++i)
    {
        std::cin>>t[i]>>d[i];

        for (int j = 0; j <= k; ++j)
            dp[i][j] = std::min( j>0?dp[i-1][j-1]:999999,
                                 std::max(dp[i-1][j], t[i])+d[i] );
    }

    res = SECS_IN_DAY+1-dp[n][k];
    for (int i = 1; i <= n; ++i)
        if (res < t[i]-dp[i-1][k])
            res = t[i]-dp[i-1][k];

    std::cout<<res;
}
