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

//////// YOUR CODE
node *parse_expr_internal(char **s);

node *parse_val(char **s) {
	if (isdigit(**s)) {
		node n = {VAL, **s - '0', NULL, NULL};
		(*s)++;
		return new_node(n);
	} else if (accept(s, '(')) {
		node *e = parse_expr_internal(s);
		if (!e || !expect(s, ')')) {
			destroy_tree(e);
			return NULL;
		}
		return e;
	} else {
		unexpected(**s);
		return NULL;
	}
}

node *parse_term(char **s) {
	node *left = parse_val(s);
	if (!left) return NULL;
	while (accept(s, '*')) {
		node *right = parse_val(s);
		if (!right) {
			destroy_tree(left);
			return NULL;
		}
		node n = {MULTI, 0, left, right};
		left = new_node(n);
		if (!left) {
			destroy_tree(n.l);
			destroy_tree(n.r);
			return NULL;
		}
	}
	return left;
}

node *parse_expr_internal(char **s) {
	node *left = parse_term(s);
	if (!left) return NULL;
	while (accept(s, '+')) {
		node *right = parse_term(s);
		if (!right) {
			destroy_tree(left);
			return NULL;
		}
		node n = {ADD, 0, left, right};
		left = new_node(n);
		if (!left) {
			destroy_tree(n.l);
			destroy_tree(n.r);
			return NULL;
		}
	}
	return left;
}

node *parse_expr(char *s) {
	node *tree = parse_expr_internal(&s);
	if (*s) {
		unexpected(*s);
		destroy_tree(tree);
		return NULL;
	}
	return tree;
}

// node	*parse_expr(char *s) {
// 	node *tree;

// 	// YOUR CODE
// 	if (*s) {
// 		destroy_tree(tree);
// 		return NULL;
// 	}
// 	return tree;
// }
//////////////////////////////////////////

int	eval_tree(node *tree) {
	switch (tree->type) {
		case ADD:
			return (eval_tree(tree->l) + eval_tree(tree->r));
		case MULTI:
			return (eval_tree(tree->l) * eval_tree(tree->r));
		case VAL:
			return tree->val;
	}
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

