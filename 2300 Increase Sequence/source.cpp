#include<iostream>

const int MAX_N = 2000, MODULO = 1e9+7;
int N,H,a[MAX_N+10], dp[MAX_N+10][2];

void enlarge(int& what, long long howMuch) { what = (what%MODULO + int(howMuch%MODULO))%MODULO; }

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);

    std::cin>>N>>H;
    for (int i = 1; i <= N; ++i)
        std::cin>>a[i];

    dp[0][0] = 1;
    for (int i = 1; i <= N; ++i)
    {
        for (int opened = 0; opened <= N; ++opened)
        {
            if (a[i]+opened==H)
            {
                enlarge(dp[opened  ][i&1],      dp[opened][~i&1]);
                if (opened>0)
                enlarge(dp[opened-1][i&1], 1LL* dp[opened][~i&1]*opened);
            }
            else if (a[i]+opened==H-1)
            {
                enlarge(dp[opened+1][i&1],      dp[opened][~i&1]);
                enlarge(dp[opened  ][i&1], 1LL* dp[opened][~i&1]*(opened+1));
            }
        }
        for (int opened = 0; opened <= N; ++opened)
            dp[opened][~i&1] = 0;
    }

    std::cout<<dp[0][N&1];
}
