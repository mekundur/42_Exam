#include <stdio.h>
#include <malloc.h>
#include <ctype.h>

typedef struct node {
	enum {
		ADD,
		MULTI,
		VAL
	}	type;
	int	val;
	struct node	*l;
	struct node	*r;
}		node;

node	*new_node(node n) {
	node *ret = calloc(1, sizeof(node));
	if (!ret)
		return NULL;
	*ret = n;
	return ret;
}

void	destroy_tree(node *n) {
	if (!n)
		return;
	if (n->type != VAL) {
		destroy_tree(n->l);
		destroy_tree(n->r);
	}
	free(n);
}

void	unexpected(char c)
{
	if (c)
		printf("Unexpected token '%c'\n", c);
	else
		printf("Unexpected end of input\n");
}

int		accept(char **s, char c) {
	if (**s == c) {
		(*s)++;
		return 1;
	}
	return 0;
}

int expect(char **s, char c) {
	if (accept(s, c))
		return 1;
	unexpected(**s);
	return 0;
}

// YOUR CODE

node    *parse_expr(char *s);

node	*parse_val(char **s) 
{
	if (accept(s, '(')) {
		node *n = parse_expr(*s);
		if (!n || !expect(s, ')')) {
			destroy_tree(n);
			return NULL;
		}
		return n;
	} else if (isdigit(**s)) {
		node n = {.type = VAL, .val = **s - '0', .l = NULL, .r = NULL};
		(*s)++;
		return new_node(n);
	}
	unexpected(**s);
	return NULL;
}

node	*parse_term(char **s)
{
	node *left = parse_val(s);
	if (!left)
		return NULL;
	while (accept(s, '*')) {
		node *right = parse_val(s);
		if (!right) {
			destroy_tree(left);
			return NULL;
		}
		node n = {.type = MULTI, .l = left, .r = right};
		left = new_node(n);
		if (!left) {
			destroy_tree(n.l);
			destroy_tree(n.r);
			return NULL;
		}
	}
	return left;
}

node	*parse_expr(char *s) 
{
	node *tree;

	// YOUR CODE
	char *p = s;
	tree = parse_term(&p);
	if (!tree)
		return NULL;
	while (accept(&p, '+')) {
		node *right = parse_term(&p);
		if (!right) {
			destroy_tree(tree);
			return NULL;
		}
		node n = {.type = ADD, .l = tree, .r = right};
		tree = new_node(n);
		if (!tree) {
			destroy_tree(n.l);
			destroy_tree(n.r);
			return NULL;
		}
	}
	if (*p) {
		unexpected(*p);
		destroy_tree(tree);
		return NULL;
	}
	return tree;
}

int	eval_tree(node *tree) {
	switch (tree->type) {
		case ADD:
			return (eval_tree(tree->l) + eval_tree(tree->r));
		case MULTI:
			return (eval_tree(tree->l) * eval_tree(tree->r));
		case VAL:
			return tree->val;
	}
	return 0;
}

int main(int argc, char **argv) {
	if (argc != 2)
		return 1;
	node *tree = parse_expr(argv[1]);
	if (!tree)
		return 1;
	printf("%d\n", eval_tree(tree));
	destroy_tree(tree);
}

