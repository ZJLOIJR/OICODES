#include <cstdio>
#include <cstring>
#include <cstdlib>

struct node
{
	node* fail; node* son[26];
	int data;
	void init()
	{
		data = 0, fail = NULL;
		memset(son, 0, sizeof(son));
	}
};
node* root;

int n, m;
char str[2000007];
void insert(char* s)
{
	node* now = root;
	while (*s != '\0')
	{
		if (!now->son[*s - 'a']) now->son[*s - 'a'] = new node, now->son[*s - 'a']->init();
		now = now->son[*s - 'a'];
		s++;
	}
	now->data++;
}
int head, tail;
node* que[30007];
void getfail()
{
	head = 1, que[tail = 1] = root;
	while (head <= tail)
	{
		node* x = que[head++];
		for (int i = 0; i < 26; i++)
			if (x->son[i])
			{
				if (x == root) x->son[i]->fail = root;
				else
				{
					node* tmp = x->fail;
					while (tmp)
					{
						if (tmp->son[i]) { x->son[i]->fail = tmp->son[i]; break; }
						tmp = tmp->fail;
					}
					if (!tmp) x->son[i]->fail = root;
				}
				que[++tail] = x->son[i];
			}
	}
}
int match(char *s)
{
	int ret = 0;
	node* now = root;
	while (*s != '\0')
	{
		while (!now->son[*s - 'a'] && now != root) now = now->fail;
		now = now->son[*s - 'a'];
		if (!now) now = root;
		node* tmp = now;
		while (tmp != root) ret += tmp->data, tmp = tmp->fail;
		s++;
	}
	return ret;
}

int main()
{
	root = new node, root->init();
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= m; i++) scanf("%s", str), insert(str);
	getfail();
	scanf("%s", str);
	printf("%d\n", match(str));
	return 0;
}
