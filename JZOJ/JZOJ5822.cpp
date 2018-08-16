#include <cstdio>
#include <cstring>
#include <cstdlib>

const int MAX = 8e6 + 7;

int m, opt;
char str[MAX], str0[MAX];

int tot, root, son[MAX][10], fa[MAX];
int getfa(int x) { return fa[x] == x ? x : fa[x] = getfa(fa[x]); }
void link(int x, int y) { fa[getfa(x)] = getfa(y); }

int insert()
{
	if (!root) root = ++tot, fa[root] = root;
	int now = root, len = strlen(str);
	for (int i = 0; i < len; i++)
	{
		now = getfa(now);
		int nx = son[now][str[i] - '0'];
		if (!nx) nx = ++tot, fa[nx] = nx, son[now][str[i] - '0'] = nx;
		now = son[now][str[i] - '0'];
	}
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
	printf("1\n");
}

int main()
{
	freopen("input", "r", stdin);
	//freopen("quantum.in", "r", stdin);
	//freopen("quantum.out", "w", stdout);
	
	scanf("%d", &m);
	while (m--)
	{
		scanf("%d", &opt);
		if (opt == 1) scanf("%s", str), insert();
		else if (opt == 2) scanf("%s", str), find();
		else
		{
			int x, y;
			scanf("%s", str), x = insert();
			scanf("%s", str), y = insert();
			if (
		}
	}

	fclose(stdin);
	fclose(stdout);
	return 0;
}
