#include<iostream>
#include<algorithm>

const int MAX_N=100, MAX_M=20;
const unsigned long long LOT=-1;

struct Friend
{
    unsigned long long X,K,mask;
    friend bool operator< (Friend a, Friend b) { return a.K<b.K; }
};

unsigned long long N,M,B, Mi,c, dp[1ULL<<MAX_M], res=LOT;
Friend a[MAX_N+10];

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin>>N>>M>>B;
    for (int i = 0; i < N; ++i)
    {
        std::cin>>a[i].X>>a[i].K>>Mi;
        a[i].mask = 0;
        for (int j = 0; j < Mi; ++j)
        {
            std::cin>>c;
            a[i].mask |= 1<<c-1;
        }
    }

    std::sort(a, a+N);

    for (unsigned long long i = 1; i < 1<<M; ++i)
        dp[i] = LOT;

    for (int j = 0; j < N; ++j)
    {
        for (unsigned long long i = 0; i < 1<<M; ++i)
            if (dp[i] < LOT)
                dp[i|a[j].mask] = std::min(dp[i|a[j].mask], dp[i]+a[j].X);

        if (dp[(1<<M)-1] < LOT)
            res = std::min(res, dp[(1<<M)-1]+B*a[j].K);
    }

    if (res < LOT)
        std::cout<<res;
    else
        std::cout<<-1;
}
