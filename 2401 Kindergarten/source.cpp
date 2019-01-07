#include<iostream>
#include<cstdio>
#include<cstring>
#include<ctime>

long long res, cx,cy;
int N, curr;

int main()
{
#ifndef ONLINE_JUDGE
    freopen("C:\\Users\\Micklepru\\ClionProjects\\Competitions\\test.txt", "r", stdin);
#endif

    scanf("%d", &N);
    for (int i = 0; i < N; ++i)
    {
        scanf("%d", &curr);
        if (res-curr>cx || i==0) cx = res-curr;
        if (res+curr>cy || i==0) cy = res+curr;
        res = std::max(res,cx+curr);
        res = std::max(res,cy-curr);
    }
    printf("%I64d", res);

#ifndef ONLINE_JUDGE
    std::cout << "\n\n\nTime elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " s.\n";
#endif
}
