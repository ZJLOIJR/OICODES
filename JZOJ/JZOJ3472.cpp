#include <cstdio>
#include <cstring>
#include <cstdlib>

const int N = 1e2 + 7, K = 10, L = 37, P = 1000000007;

int n, m, k;
char str[40];

int tot, root;
int son[N * L][26], fail[N * L], data[N * L], dp[N * L][K];
void insert(char* s)
{
	if (!root) root = ++tot;
	int now = root;
	while (*s != '\0')
	{
		if (!son[now][*s - 'a']) son[now][*s - 'a'] = ++tot;
		now = son[now][*s - 'a'];
	}
	data[now]++;
}
int head, tail, que[N * L];
void getfail()
{
	head = 1, que[tail = 1] = root;
	while (head <= tail)
	{
		int x = que[head++];
		for (int i = 0; i < 26; i++)
			if (son[x][i])
			{
				if (x == root) fail[son[x][i]] = root;
				else
				{
					int tmp = fail[x];
					while (tmp)
					{
						if (son[tmp][i]) { fail[son[x][i]] = son[tmp][i]; break; }
						tmp = fail[tmp];
					}
					if (!tmp) fail[son[x][i]] = root;
				}
				que[++tail] = son[x][i];
			}
	}
}
void getans()
{
	head = 1, que[tail = 1] = root;
	dp[root][0] = 1;
	while (head <= tail)
	{
		int x = que[head++];
		for (int i = data[x]; i <= k; i++) dp[x][i] = (dp[x][i] + )
		for (int i = 0; i < m; i++)
			
	}
}

int main()
{
	scanf("%d%d", &n, &k);
	for (int i = 1; i <= k; i++) scanf("%s", str), insert(str);
	scanf("%s", str);
	getfail();
	return 0;
}
