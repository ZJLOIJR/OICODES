#include <cstdio>
#include <cstring>
#include <cstdlib>

const int N = 1e2 + 7, K = 9, L = 37, P = 1000000007;

int n, m, k, full, arr[20];
char str[40], ok[256];

int tot, root;
int son[K * L][26], fail[K * L], data[K * L], f[K * L][N][1 << K];
inline int bit(int x) { return (1 << (x - 1)); }
void insert(char *s, int val)
{
	if (!root) root = ++tot;
	int now = root;
	while (*s != '\0')
	{
		if (!son[now][*s - 'a']) son[now][*s - 'a'] = ++tot;
		now = son[now][*s - 'a'], s++;
	}
	data[now] |= bit(val);
}
int head, tail, que[K * L];
void getfail()
{
	head = 1, que[tail = 1] = root;
	while (head <= tail)
	{
		int x = que[head++];
		for (int p = 1; p <= arr[0]; p++)
		{
			int i = arr[p];
			if (son[x][i])
			{
				if (x == root) fail[son[x][i]] = root;
				else
				{
					fail[son[x][i]] = son[fail[x]][i];
					data[son[x][i]] |= data[fail[son[x][i]]];
				}
				que[++tail] = son[x][i];
			}
			else son[x][i] = son[fail[x]][i] ? son[fail[x]][i] : root;
		}
	}
}
int getans()
{
	f[0][root][0] = 1;
	for (int i = 0; i < n; i++)
		for (int j = 1; j <= tot; j++)
			for (int s = 0; s <= full; s++)
				if (f[i][j][s])
					for (int p = 1; p <= arr[0]; p++)
					{
						int nxj = son[j][arr[p]], nxs = s | data[nxj];
						f[i + 1][nxj][nxs] = (f[i + 1][nxj][nxs] + 0LL + f[i][j][s]) % P;
					}
	int ret = 0;
	for (int i = 1; i <= tot; i++) ret = (ret + 0LL + f[n][i][full]) % P;
	return ret;
}

int main()
{
	scanf("%d%d", &n, &k);
	full = (1 << k) - 1;
	for (int i = 1; i <= k; i++) scanf("%s", str), insert(str, i);
	scanf("%d%s", &m, str);
	for (int i = 0; i < m; i++)
	{
		if (!ok[str[i] - 'a']) arr[++arr[0]] = str[i] - 'a';
		ok[str[i] - 'a'] = 1;
	}
	if (k)
	{
		getfail();
		printf("%d\n", getans());
	}
	else
	{
		int ans = 1;
		for (int i = 1; i <= n; i++) ans = ans * 1LL * arr[0] % P;
		printf("%d\n", ans);
	}
	return 0;
}
