#include <cstdio>
#include <cstring>
#include <cstdlib>

const int MAX = 8e6 + 7;

int m, opt;
char str[MAX];

int tot, root, son[MAX][10], fa[MAX], val[MAX];
int getfa(int x) { return fa[x] == x ? x : fa[x] = getfa(fa[x]); }

int insert(int x)
{
	if (!root) root = ++tot, fa[root] = root;
	int now = root, len = strlen(str);
	for (int i = 0; i < len; i++)
	{
		now = getfa(now);
		int nx = son[now][str[i] - '0'];
		if (!nx) nx = ++tot, fa[tot] = tot;
		son[now][str[i] - '0'] = nx;
		now = nx;
	}
	val[now] += x;
	return now;
}

void find()
{
	int now = root, len = strlen(str);
	for (int i = 0; i < len; i++)
	{
		now = getfa(now);
		int nx = son[now][str[i] - '0'];
		if (!nx) { printf("0\n"); return; }
		now = son[now][str[i] - '0'];
	}
	if (val[now]) printf("1\n");
	else printf("0\n");
}

void merge(int x, int y)
{
	if (x == y) return;
	fa[getfa(x)] = getfa(y);
	for (int i = 0; i < 10; i++)
	{
		if (son[x][i] && son[y][i]) merge(son[x][i], son[y][i]);
		if (!son[y][i] && son[x][i]) son[y][i] = son[x][i];
	}
}

int main()
{
	freopen("input", "r", stdin);
	freopen("output", "w", stdout);
	//freopen("quantum.in", "r", stdin);
	//freopen("quantum.out", "w", stdout);
	
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
			fa[getfa(x)] = getfa(y);
			merge(x, y), merge(y, x);
		}
	}

	fclose(stdin);
	fclose(stdout);
	return 0;
}
