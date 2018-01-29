#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>

const int L = 57;

struct node { int data; node* son[26]; void init() { data = 0; memset(son, 0, sizeof(son)); } };
node *root;

int n, m;
char str[L];

void set(char *s, int val)
{
	node *now = root;
	while (*s != '\0')
	{
		int num = *s - 'a';
		if (!now->son[num])
			now->son[num] = new node, now->son[num]->init();
		now = now->son[num];
		s++;
	}
	now->data = 1;
}

int get(char *s)
{
	node *now = root;
	while (*s != '\0')
	{
		int num = *s - 'a';
		if (!now->son[num])
			return -1;
		now = now->son[num];
		s++;
	}
	if (now->data == 1) { now->data = 0; return 1; }
	else return 0;
}

int main()
{
	root = new node, root->init();
	scanf("%d", &n);
	while (n--)
	{
		scanf("%s", str);
		set(str, 1);
	}
	scanf("%d", &m);
	while (m--)
	{
		scanf("%s", str);
		int ret = get(str);
		if (ret == -1)
			printf("WRONG\n");
		else if (ret == 0)
			printf("REPEAT\n");
		else
			printf("OK\n");
	}
	return 0;
}
