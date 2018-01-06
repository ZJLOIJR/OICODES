#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;

const int N = 1000007;

int n;
char s[N];

struct node
{
	node* son[26];
	node* fail;
	int data;
	void init() { memset(son, 0, sizeof(son)); fail = NULL, data = 0; }
};

node* que[1000007];

struct DictionaryTree
{
	node* root;

	void init() { root = new node; root->init(); }

	void insert(char *s)
	{
		node* now = root;
		while (*s != '\0')
		{
			int num = *s - 'a';
			if (now->son[num] == NULL)
			{
				node* newnode = new node;
				now->son[num] = newnode;
				now->son[num]->init();
			}
			now = now->son[num];
			s++;
		}
		now->data++;
	}

	void getfail()
	{
		memset(que, 0, sizeof(que));
		int head = 1, tail = 0;
		que[++tail] = root;
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
							if (tmp->son[i])
							{
								x->son[i]->fail = tmp->son[i];
								break;
							}
							tmp = tmp->fail;
						}
						if (tmp == NULL) x->son[i]->fail = root;
					}
					que[++tail] = x->son[i];
				}
		}
	}

	int match(char *s)
	{
		int ret = 0;
		node* x = root;
		while (*s != '\0')
		{
			int num = *s - 'a';
			while (!x->son[num] && x != root) x = x->fail;
			x = x->son[num];
			if (!x) x = root;
			node* tmp = x;
			while (tmp != root)
			{
				if (tmp->data >= 0)
				{
					ret += tmp->data;
					tmp->data = -1;
				}
				else break;
				tmp = tmp->fail;
			}
			s++;
		}
		return ret;
	}
} Tree;

int main()
{
	Tree.init();
	scanf("%d", &n);
	while (n--)
	{
		scanf("%s", s);
		Tree.insert(s);
	}
	Tree.getfail();
	scanf("%s", s);
	printf("%d\n", Tree.match(s));
	return 0;
}
