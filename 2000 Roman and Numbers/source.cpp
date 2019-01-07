#include<iostream>
#include<cstring>

const int MAX_DIGITS = 18, MAX_M = 100;
char N[MAX_DIGITS+10];
long long timesRepeat, dp[1<<MAX_DIGITS][MAX_M];
int M, nlen, digAmount[10];

int main()
{
    std::cin>>N>>M;
    nlen = strlen(N);

    timesRepeat = 1;
    for (int i = 0; i < nlen; ++i)
        timesRepeat *= ++digAmount[N[i]-='0'];

    dp[0][0] = 1;
    for (int i = 0; i < 1<<nlen; ++i)
        for (int k = 0; k < nlen; ++k)
            if ( (i & 1<<k)==0 && (i||N[k]) )
                for (int j = 0; j < M; ++j)
                        dp[i | 1<<k][(j*10+N[k])%M] += dp[i][j];

    std::cout<< dp[(1<<nlen)-1][0]/timesRepeat;
}
