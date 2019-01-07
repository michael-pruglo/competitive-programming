#include<iostream>
#include<map>

const int MAX_N = 500;
long long N,M,MOD, columnsSum[MAX_N+10],ones,twos;
std::map<std::pair<int,int>, long long> dp[2];


int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);

    std::cin>>N>>M>>MOD;
    for (int i = 0; i < M; ++i)
        for (int j = 0; j < N; ++j)
        {
            char c;
            std::cin>>c;
            columnsSum[j] += c=='1';
        }

    for (int i = 0; i < N; ++i)
    {
        if (columnsSum[i]==1)
            ++ones;
        if (columnsSum[i]==0)
            ++twos;
    }

    dp[ N   %2][{0,0}] = 1;
    dp[(N-1)%2][{2,0}] = 1;
    for (long long i = N-2; i >= M; --i)
        for (long long one = 0; one <= N; ++one)
        {
            long long two = ((N-i)*2-one)/2;
            if (one-2>=0)             ( dp[i%2][{one,two}] += dp[(i+1)%2][{one-2,  two  }] * one*(one-1)/2 ) %= MOD;
            if (one-1>=0 && two-1>=0) ( dp[i%2][{one,two}] += dp[(i+1)%2][{one-1+1,two-1}] * one*two       ) %= MOD;
            if (two-2>=0)             ( dp[i%2][{one,two}] += dp[(i+1)%2][{one  +2,two-2}] * two*(two-1)/2 ) %= MOD;
        }

    std::cout<<dp[M%2][{ones,twos}];
}
