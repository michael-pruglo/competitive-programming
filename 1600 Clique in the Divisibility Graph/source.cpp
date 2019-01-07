#include<iostream>

const int MAX_N=1e6, MAX_VAL=1e6;
int N, val[MAX_N+10], dp[MAX_N+10], res;
int isHere[MAX_VAL+10];

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);

    std::cin>>N;
    for (int i = 1; i <= N; ++i)
    {
        std::cin>>val[i];
        isHere[val[i]] = i;
    }

    res = 1;
    dp[N] = 1;
    for (int i = N-1; i>0; --i)
    {
        dp[i] = 1;
        for (int j = 2*val[i]; j <= MAX_VAL; j+=val[i])
            if (isHere[j])
                dp[i] = std::max(dp[i], dp[isHere[j]]+1);

        res = std::max(res, dp[i]);
    }

    std::cout<<res;
}
