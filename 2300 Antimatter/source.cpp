#include<iostream>
#include<cstdio>
#include<cstring>
#include<ctime>

const int MAX_SUM = 10000, MODULO = int(1e9+7);
int N, curr;
int dp[4*MAX_SUM+10][2], res;

inline void enlarge(int& what, int howMuch)
{
    what += howMuch;
    if (what>=MODULO) what -= MODULO;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("C:\\Users\\Micklepru\\ClionProjects\\Competitions\\test.txt", "r", stdin);
#endif

    std::cin>>N;
    for (int i = 1; i <= N; ++i)
    {
        std::cin>>curr;
        enlarge(dp[MAX_SUM][~i&1], 1);
        for (int sum = 2*MAX_SUM; sum >= 0; --sum)
        {
            dp[sum][i&1] = dp[sum-curr][~i&1];
            enlarge(dp[sum][i&1], dp[sum+curr][~i&1]);
        }
        enlarge(res, dp[MAX_SUM][i&1]);
    }
    std::cout<<res;

#ifndef ONLINE_JUDGE
    std::cout << "\nTime elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " s.\n";
#endif
}
