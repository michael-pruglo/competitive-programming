#include<iostream>
#include<algorithm>

//types:
//1 - '0'
//2 - '1' and prev == '*'
//3 - '1' and prev != '*'
//4 - '2'
//5 - '*'

const int MAX_LEN = 1e6, P = 1e9+7, TYPES = 5;
std::string s;
int slen, dp[MAX_LEN+10][TYPES+10], res;

int main()
{
    std::cin>>s;
    slen = s.length();

    dp[1][1] = s[0]=='0' || s[0]=='?';
    dp[1][3] = s[0]=='1' || s[0]=='?';
    dp[1][5] = s[0]=='*' || s[0]=='?';
    for (int i = 1; i < slen; ++i)
    {
        if (s[i]=='0' || s[i]=='?')
            dp[i+1][1] = (0LL + dp[i][1] + dp[i][2])%P;
        if (s[i]=='1' || s[i]=='?')
        {
            if (i>0)
                dp[i+1][2] = dp[i][5];
            dp[i+1][3] = (0LL + dp[i][1] + dp[i][2])%P;
        }
        if ((s[i]=='2' || s[i]=='?') && i>0)
            dp[i+1][4] = dp[i][5];
        if (s[i]=='*' || s[i]=='?')
            dp[i+1][5] = (0LL + dp[i][3] + dp[i][4] + dp[i][5])%P;
    }

    res = (0LL + dp[slen][1] + dp[slen][2] + dp[slen][5])%P;
    std::cout<<res;
}
