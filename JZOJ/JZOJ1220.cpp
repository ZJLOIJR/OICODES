#pragma GCC optimize(2)
#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>

const int N = 1000007;

int n, a, ans = 0;
int sta[N], top = 0;

inline int read()
{
	int x = 0, f = 0;
	char c = getchar();
	for (; c < '0' || c > '9'; c = getchar()) if (c == '-') f = 1;
	for (; c >= '0' && c <= '9'; c = getchar()) x = (x << 1) + (x << 3) + c - '0';
	return f ? -x : x;
}

int main()
{
	n = read();
	for (int i = 1; i <= n; i++)
	{
		a = read(), a = read();
		while (top && a < sta[top]) top--, ans++;
		while (top && a == sta[top]) top--;
		sta[++top] = a;
	}
	ans += top;
	printf("%d\n", ans);
	return 0;
}
