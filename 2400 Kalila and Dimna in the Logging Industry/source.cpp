#include<iostream>
#include<cstdlib>
#include<vector>
#include<cmath>
#include<cstdio>

/*
 * Data structure
 * to be used in dynamic programming optimisation
 * called "Convex Hull trick"
 * Has restriction on adding lines order
 */
class ConvexHull
{
    typedef long long coef_t;
    typedef long long coord_t;
    typedef long long val_t;

    /*
     * Line 'y=a*x+b' represented by 2 coefficients 'a' and 'b'
     */
private:
    struct Line
    {
        coef_t  a, b;

        Line(coef_t aa=0, coef_t bb=0) : a(aa), b(bb) {}
        val_t   valueAt(coord_t x) const { return a*x+b; }
        friend  bool    areParallel(const Line& l1, const Line& l2) { return l1.a==l2.a; }
        friend  double  intersectX(const Line& l1, const Line& l2) { return areParallel(l1,l2)?INFINITY:1.0*(l2.b-l1.b)/(l1.a-l2.a); }
    };

private:
    bool                isMax; //whether or not saved envelope is top(search of max value)
    std::vector<Line>   hull;  //envelope itself

public:
    explicit ConvexHull(bool isMax): isMax(isMax) {}

    /*
     * INFO:        Adding line to the envelope
     *              Line is of type 'y=a*x+b' represented by 2 coefficients 'a' and 'b'
     * NOTE:        Lines must be added in specific order:
     *                  top    envelope(max value) - non-descending by 'a'
     *                  bottom envelope(min value) - non-ascending  by 'a'
     *              If order is wrong, shows message to std::cerr and terminates the program.
     * COMPLEXITY:  Adding N lines(N calls of function) takes O(N) time
     */
    void addLine(coef_t a, coef_t b)
    {
        Line l3(a,b);
        if (hull.size()==1 && areParallel(hull[0], l3))
        {
            if (isMax && l3.b>hull[0].b || !isMax && l3.b<hull[0].b)
                hull[0] = l3;
            return;
        }

        while (hull.size()>1)
        {
            Line l2 = hull.back();
            Line l1 = *(hull.end()-2);

            if (isMax&&!(l3.a>l2.a && l2.a>l1.a) || !isMax&&!(l3.a<l2.a && l2.a<l1.a))
            {
                std::cerr<<"\n\nCONVEX HULL FATAL ERROR! Wrong adding sequence!\n";
                exit(1);
            }

            if (intersectX(l1,l3) <= intersectX(l1,l2))
                hull.pop_back();
            else
                break;
        }
        hull.push_back(l3);
    }

    /*
     * INFO:        Query, which returns max/min(depends on hull type - see more info above) value in point with abscissa 'x'
     *              Uses pointer walk technique - see notes below
     * NOTE:        Queries must be called in non-decreasing order by 'x'
     *              'i' is index(0-based) of line with left-intersection point lesser than 'x'
     *              at first call 'i' should be 0
     * COMPLEXITY:  Processing N queries(N calls of function) takes O(N) time
     */
    val_t proceed(int& i, coord_t x) const
    {
        if (i > hull.size()-1)
            i = hull.size()-1;
        while (i+1<hull.size() && intersectX(hull[i], hull[i+1]) < double(x)) ++i;
        return hull[i].valueAt(x);
    }

    /*
     * INFO:        Query, which returns max/min(depends on hull type - see more info above) value in point with abscissa 'x'
     *              Uses binary search technique
     * NOTE:        No restrictions on calling order
     * COMPLEXITY:  O(log N), N-amount of lines in hull
     */
    val_t getBest(coord_t x) const
    {
        int l = 0, r = hull.size();
        for ( ; r-l>1 ; )
        {
            int mid = (l+r)/2;
            double  leftIntersection = mid-1>=0          ? intersectX(hull[mid-1], hull[mid])   : -INFINITY;
            double rightIntersection = mid+1<hull.size() ? intersectX(hull[mid],   hull[mid+1]) :  INFINITY;
            if (leftIntersection > x)
                r = mid;
            else if (rightIntersection < x)
                l = mid+1;
            else
            {
                l = mid;
                break;
            }
        }

        return hull[l].valueAt(x);
    }
};

const int MAX_N = 1e5;
int N,a[MAX_N+10],b[MAX_N+10];
unsigned long long dp[MAX_N+10];

int main()
{
#ifndef ONLINE_JUDGE
    freopen("C:\\Users\\Micklepru\\ClionProjects\\Competitions\\test.txt", "r", stdin);
#endif
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);

    std::cin>>N;
    for (int i = 0; i < N; ++i) std::cin>>a[i];
    for (int i = 0; i < N; ++i) std::cin>>b[i];

    ConvexHull optim(0);
    int k = 0;
    for (int i = 1; i < N; ++i)
    {
        optim.addLine(b[i-1], dp[i-1]);
        auto one = optim.proceed(k, a[i]);
        auto two = optim.getBest(a[i]);
        if (one!=two)
            throw "BUGS EVERYWHERE!";

        dp[i] = two;
    }

    std::cout<<dp[N-1];
}
