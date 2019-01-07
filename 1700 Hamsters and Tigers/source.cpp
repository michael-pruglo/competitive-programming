#include<iostream>
#include<cstdio>
#include<algorithm>

int N, h, sum,l,r, ans=int(1e9);
std::string s;

int main()
{
#ifndef ONLINE_JUDGE
    freopen("C:\\Users\\Micklepru\\ClionProjects\\Competitions\\test.txt", "r", stdin);
#endif

    std::cin>>N>>s;
    h = std::count(s.begin(), s.end(), 'H');
    for (r = 0; r < h; ++r)
        sum += s[r]=='T';
    //std::cout<<sum<<"\n";
    for (l = 0; l < N; ++l)
    {
        ans = std::min(ans, sum);
        sum -= s[l]=='T';
        sum += s[r]=='T';
        //std::cout<<l<<"-"<<r<<" s="<<sum<<"\n";
        r = r<N-1? r+1 : 0;
    }
    std::cout<<std::min(ans, sum);
}
