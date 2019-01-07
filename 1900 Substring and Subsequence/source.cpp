#include<iostream>

const long MAX_LEN = 5000, P = 1e9+7;
long long dp[MAX_LEN+10][MAX_LEN+10], res=0;
std::string s,t;

void add(long long& to, long long howMuch)
{
    to = (to%P + howMuch%P)%P;
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);

    std::cin>>s>>t;

    int slen = s.length();
    int tlen = t.length();
    for (int i = 1; i <= slen; ++i)
        for (int j = 1; j <= tlen; ++j)
        {
            dp[i][j] = dp[i][j-1];
            if (s[i-1]==t[j-1])
                add(dp[i][j], dp[i-1][j-1]+1);
        }

    for (int i = 1; i <= slen; ++i)
        add(res, dp[i][tlen]);

    std::cout<<res;
}
