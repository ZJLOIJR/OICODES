#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>

const int LEN = 1000007, MAX = 150 * 70 + 7;

int n;
char s[LEN];

int tot = 0;
struct node
{
	int data, fail, fa;
	int son[26];
	char ch;
} nodes[MAX];
int que[MAX];

struct DictionaryTree
{
	void init() { tot = 1, nodes[1].data = nodes[1].fa = 0, nodes[1].ch = '\0', memset(nodes[1].son, 0, sizeof(nodes[1].son)); }

	void print(int x)
	{
		if (x == 1) return;
		print(nodes[x].fa);
		printf("%c", nodes[x].ch);
	}

	void insert(char *s)
	{
		int now = 1;
		while (*s != '\0')
		{
			int num = *s - 'a';
			if (!nodes[now].son[num])
			{
				nodes[now].son[num] = ++tot;
				nodes[tot].data = 0, nodes[tot].fa = now, nodes[tot].ch = *s;
				memset(nodes[tot].son, 0, sizeof(nodes[tot].son));
			}
			now = nodes[now].son[num];
			s++;
		}
		nodes[now].data++;
	}

	void getfail()
	{
		int head = 1, tail = 0;
		que[++tail] = 1;
		while (head <= tail)
		{
			int x = que[head++];
			for (int i = 0; i < 26; i++)
				if (nodes[x].son[i])
				{
					if (x == 1) nodes[nodes[x].son[i]].fail = 1;
					else
					{
						int tmp = nodes[x].fail;
						while (tmp)
						{
							if (tmp.son[i])
							{
								nodes[nodes[x].son[i]].fail = tmp.son[i];
								break;
							}
							tmp = nodes[tmp].fail;
						}
					}
				}
			que[++tail] = nodes[x].son[i];
		}
	}

	int matchmax(char *s)
	{
		int x = 1, ret = 0;
		while (*s != '\0')
		{
			int num = *s - 'a';
			while (!nodes[x].son[num] && x != 1) x = nodes[x].fail;
			x = nodes[x].son[num];
			if (!x) x = 1;
			int tmp = x;
			while (tmp != 1)
			{
				if (nodes[tmp].data > ret)
					ret = nodes[tmp].data;
				else break;
				tmp = nodes[tmp].fail;
			}
			s++;
		}
		return ret;
	}

	void printres(int value)
	{
		int x = 1;
		while (*s != '\0')
		{
			int num = *s - 'a';
			while (!nodes[x].son[num] && x != 1) x = nodes[x].fail;
			x = nodes[x].son[num];
			if (!x) x = 1;
			int tmp = x;
			while (tmp != 1)
			{
				if (nodes[tmp].data > ret)
					ret = nodes[tmp].data;
				else break;
				tmp = nodes[tmp].fail;
			}
			s++;
		}
	}
} tree;

int main()
{
	scanf("%d", &n);
	while (n)
	{
		for (int i = 1; i <= n; i++)
		{
			scanf("%s", s);
			tree.insert(s);
		}
	}
	return 0;
}
