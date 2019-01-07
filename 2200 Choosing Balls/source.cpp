#include<iostream>

const int MAX_N=1e5;
const long long BIG=1ll<<62;
long long N,Q, c[MAX_N+10],v[MAX_N+10], a,b;
long long dp[MAX_N+10], max1, max2, tmp;

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);

    std::cin>>N>>Q;
    for (int i = 0; i < N; ++i) std::cin>>v[i];
    for (int i = 0; i < N; ++i) std::cin>>c[i];

    for (int q = 0; q < Q; ++q)
    {
        dp[0] = 0;
        for (int i = 1; i <= N; ++i) dp[i] = -BIG;
        max1 = max2 = 0;

        std::cin>>a>>b;

        for (int i = 0; i < N; ++i)
        {
            tmp = std::max(dp[c[i]]+v[i]*a, dp[max2]+v[i]*b);
            if (max1 != c[i])
            {
                tmp = std::max(tmp, dp[max1]+v[i]*b);
                if (tmp>=dp[max1])
                {
                    max2 = max1;
                    max1 = c[i];
                }
                else if (tmp>dp[max2])
                {
                    max2 = c[i];
                }
            }
            dp[c[i]] = std::max(dp[c[i]], tmp);
        }

        std::cout<<dp[max1]<<"\n";
    }
}
