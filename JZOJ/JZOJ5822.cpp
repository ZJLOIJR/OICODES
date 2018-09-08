#include <cstdio>
#include <cstring>
#include <cstdlib>

const int LEN = 8e6 + 7, MAX = 1e6 + 7;

int m, opt;
char str[LEN];

int tot, root, son[MAX][10], fa[MAX], val[MAX];
int getfa(int x) { return fa[x] == x ? x : fa[x] = getfa(fa[x]); }

int insert(int x)
{
	if (!root) root = ++tot, fa[tot] = tot;
	int now = root, len = strlen(str);
	for (int i = 0; i < len; i++)
	{
		int nx = son[now][str[i] - '0'];
		if (!nx) nx = ++tot, fa[tot] = tot;
		son[now][str[i] - '0'] = nx;
		now = getfa(nx);
	}
	val[now] += x;
	return now;
}

void find()
{
	int now = root, len = strlen(str);
	for (int i = 0; i < len; i++)
	{
		int nx = son[now][str[i] - '0'];
		if (!nx) { printf("0\n"); return; }
		now = getfa(son[now][str[i] - '0']);
	}
	if (val[now]) printf("1\n");
	else printf("0\n");
}

void merge(int x, int y)
{
	int a = getfa(x), b = getfa(y);
	if (a == b) return;
	fa[a] = b, val[b] += val[a];
	for (int i = 0; i < 10; i++)
	{
		if (!getfa(son[b][i])) son[b][i] = getfa(son[a][i]);
		else if (!getfa(son[a][i])) son[a][i] = getfa(son[b][i]);
		else merge(son[a][i], son[b][i]);
		b = getfa(b);
	}
}

int main()
{
	freopen("quantum.in", "r", stdin);
	freopen("quantum.out", "w", stdout);
	
	scanf("%d", &m);
	while (m--)
	{
		scanf("%d", &opt);
		if (opt == 1) scanf("%s", str), insert(1);
		else if (opt == 2) scanf("%s", str), find();
		else
		{
			scanf("%s", str);
			int x = insert(0);
			scanf("%s", str);
			int y = insert(0);
			merge(x, y);
		}
	}

	fclose(stdin);
	fclose(stdout);
	return 0;
}
