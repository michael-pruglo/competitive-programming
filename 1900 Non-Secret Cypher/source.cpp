#import<bits/stdc++.h>
__int64 R,N,K,l,r,i;
std::map<int,int> m,a;
main()
{
    for (std::cin>>N>>K; i < N; std::cin>>a[i++]);

    for (++m[a[0]]; l < N; --m[a[l++]], R+=N-r)
        while (r<N & m[a[r]]<K) ++m[a[++r]];

    std::cout<<R;
}
