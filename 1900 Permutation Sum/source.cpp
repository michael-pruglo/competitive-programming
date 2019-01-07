#include<iostream>

int N, r[]={0,1,18,1800,670320,734832000,890786230,695720788,150347555};

int main()
{
    std::cin>>N;
    std::cout<<r[N%2*-~N/2];
}
