#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>
using namespace std;

typedef long long ll;
const int N = 3e5 + 3;

int n;
ll mx, mi, ansmx, ansmi, a[N];
int top, sta[N];

inline ll read()
{
	ll x = 0, f = 0;
	char c = getchar();
	for (; c < '0' || c > '9'; c = getchar()) if (c == '-') f = 1;
	for (; c >= '0' && c <= '9'; c = getchar()) x = (x << 1) + (x << 3) + (c ^ '0');
	return f ? -x : x;
}

int main()
{
	n = read();
	for (int i = 1; i <= n; i++) a[i] = read();
	top = mx = ansmx = 0;
	for (int i = 1; i <= n; i++)
	{
		while (top && a[i] > a[sta[top]])
		{
			mx -= a[sta[top]] * (sta[top] - sta[top - 1]);
			top--;
		}
		mx += a[i] * (i - sta[top]);
		sta[++top] = i;
		ansmx += mx;
	}
	top = mi = ansmi = 0;
	for (int i = 1; i <= n; i++)
	{
		while (top && a[i] < a[sta[top]])
		{
			mi -= a[sta[top]] * (sta[top] - sta[top - 1]);
			top--;
		}
		mi += a[i] * (i - sta[top]);
		sta[++top] = i;
		ansmi += mi;
	}
	printf("%lld\n", ansmx - ansmi);
	return 0;
}
