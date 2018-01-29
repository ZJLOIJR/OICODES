#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>

const int N = 200007;

int n, ans = 2333333, tmp, top = 0;
int t[N], vis[N], sta[N], rd[N];

inline int read()
{
	int x = 0, f = 0;
	char c = getchar();
	for (; c < '0' || c > '9'; c = getchar()) if (c == '-') f = 1;
	for (; c >= '0' && c <= '9'; c = getchar()) x = (x << 1) + (x << 3) + c - '0';
	return f ? -x : x;
}

inline int min(int a, int b) { return a < b ? a : b; }

void dfs(int x, int len, int fir)
{
	if (x == fir && len > 1) ans = min(ans, len);
	if (vis[x]) return;
	vis[x] = 1;
	dfs(t[x], len + 1, fir);
}

int main()
{
	freopen("message.in", "r", stdin);
	freopen("message.out", "w", stdout);

	n = read();
	for (int i = 1; i <= n; i++) *(t + i) = read(), rd[t[i]]++;
	for (int i = 1; i <= n; i++) if (rd[i] == 0) sta[++top] = i, vis[i] = 1;
	while (top > 0)
	{
		int x = sta[top--];
		rd[t[x]]--;
		if (rd[t[x]] == 0) vis[t[x]] = 1, sta[++top] = t[x];
	}
	for (int i = 1; i <= n; i++) if (!vis[i]) dfs(i, 0, i);
	printf("%d\n", ans);

	fclose(stdin);
	fclose(stdout);
	return 0;
}