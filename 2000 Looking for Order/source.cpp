#include<iostream>
#include<iomanip>
#include<cmath>

const int MAX_N = 24, NEUTRAL_VALUE = -1;
int N, dp[1<<MAX_N],prev[1<<MAX_N], dist[MAX_N+10][MAX_N+10],x[MAX_N+10],y[MAX_N+10];

void pathTo(int mask)
{
    if (mask==0)
    {
        std::cout<<"0 ";
        return;
    }

    pathTo(prev[mask]);
    int diff = prev[mask] ^ mask;
    int first = diff & diff-1;
    int second = diff ^ first;

    if (first)
        std::cout<<int(log2(second)+1)<<" "<<int(log2(first)+1)<<" 0 ";
    else
        std::cout<<int(log2(second)+1)<<" 0 ";
}
std::string bin(int x)
{
    std::string res(MAX_N, '0');
    for (int i = res.length()-1; x; --i,x/=2)
        if (x%2)
            res[i] = '1';
    return res;
}

void showDist()
{
    std::cout<<"        ";
    for (int i = 0; i <= N; ++i)
        std::cout<< std::setw(5)<<"["<< std::setw(2)<<i<<"]";
    std::cout<<"\n";
    for (int i = 0; i <= N; ++i)
    {
        std::cout<< std::setw(5)<<"["<< std::setw(2)<<i<<"]";
        for (int j = 0; j <= N; ++j)
            std::cout<< std::setw(8)<<dist[i][j];
        std::cout<<"\n";
    }
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);

    std::cin>>x[0]>>y[0]>>N;
    for (int i = 1; i <= N; ++i)
        std::cin>>x[i]>>y[i];


    for (int i = 0; i <= N; ++i)
        for (int j = 0; j <= N; ++j)
            dist[i][j] = (x[i]-x[j])*(x[i]-x[j]) + (y[i]-y[j])*(y[i]-y[j]);

    //showDist();

    dp[0] = 0;
    for (int mask = 1; mask < 1<<N; ++mask)
        dp[mask] = NEUTRAL_VALUE;

    for (int mask = 0; mask < 1<<N; ++mask)
    {
        if (dp[mask] != NEUTRAL_VALUE)
        {
            int first;
            for (first = 1; (first<=N) && (mask & 1<<first-1); ++first);
            for (int j = first; j <= N; ++j)
                if (~mask & 1<<j-1)
                {
                    int newMask = mask|1<<first-1|1<<j-1;
                    if (dp[newMask] > dp[mask]+dist[0][first]+dist[first][j]+dist[j][0] || dp[newMask]==NEUTRAL_VALUE)
                    {
                        dp[newMask] = dp[mask]+dist[0][first]+dist[first][j]+dist[j][0];
                        prev[newMask] = mask;
                    }
                }
        }

        //std::cout<<"["<<bin(mask)<<"] = "<<std::setw(5)<<dp[mask]<<" "<<bin(prev[mask])<<" ";
        //pathTo(mask);
        //std::cout<<"\n";
    }

    std::cout<<dp[(1<<N)-1]<<"\n";
    pathTo((1<<N)-1);
}
