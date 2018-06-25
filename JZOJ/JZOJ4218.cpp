#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
inline int read()
{
	int x = 0, f = 0;
	char c = getchar();
	for (; c < '0' || c > '9'; c = getchar()) if (c == '-') f = 1;
	for (; c >= '0' && c <= '9'; c = getchar()) x = (x << 1) + (x << 3) + (c ^ '0');
	return f ? -x : x;
}

const int N = 2e5 + 7;

int n, m, x1, y1, x2, y2;
double dis1[N], dis2[N];

int main()
{
	
	return 0;
}
