#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;

const int N = 1e5 + 7, M = 7e6 + 3;

int n, m, q, u, v, t;
long long a[N], now = 0;

struct queue
{
	int head, tail;
	long long val[M];
	void init() { head = 1, tail = 0; }
	void push(long long x) { val[++tail] = x; }
	long long front() { return head <= tail ? val[head] : -0x7f7f7f7f7f7f; }
	long long pop() { return head <= tail ? val[head++] : -0x7f7f7f7f7f7f; }
} que1, que2, que3;

inline long long read()
{
	long long x = 0, f = 0;
	char c = getchar();
	for (; c < '0' || c > '9'; c = getchar()) if (c == '-') f = 1;
	for (; c >= '0' && c <= '9'; c = getchar()) x = (x << 1) + (x << 3) + c - '0';
	return f ? -x : x;
}
inline long long max(long long a, long long b) { return a > b ? a : b; }

void init()
{
	que1.init(), que2.init(), que3.init();
	n = read(), m = read(), q = read(), u = read(), v = read(), t = read();
	for (int i = 1; i <= n; i++) *(a + i) = read();
	sort(a + 1, a + n + 1, [](long long x, long long y){ return x > y; });
	for (int i = 1; i <= n; i++) que1.push(a[i]);
}

void solve()
{
	for (int i = 1; i <= m; now += q, i++)
	{
		long long a = que1.front(), b = que2.front(), c = que3.front();
		long long mxlen = max(a, max(b, c));
		if (mxlen == a) que1.pop();
		else if (mxlen == b) que2.pop();
		else if (mxlen == c) que3.pop();
		long long len1 = (mxlen + now) * u / v, len2 = mxlen + now - len1;
		que2.push(len1 - now - q);
		que3.push(len2 - now - q);
		if (i % t == 0) printf("%lld ", mxlen + now);
	}
	printf("\n");
	for (int i = 1; i <= n + m; i++)
	{
		long long a = que1.front(), b = que2.front(), c = que3.front();
		long long mxlen = max(a, max(b, c));
		if (mxlen == a) que1.pop();
		else if (mxlen == b) que2.pop();
		else if (mxlen == c) que3.pop();
		if (i % t == 0) printf("%lld ", mxlen + now);
	}
	printf("\n");
}

int main()
{
	freopen("earthworm.in", "r", stdin);
	freopen("earthworm.out", "w", stdout);

	init();
	solve();
	
	fclose(stdin);
	fclose(stdout);
	return 0;
}