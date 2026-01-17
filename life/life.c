#include "stdlib.h"
#include "stdio.h"
#include "unistd.h"
#include "stdbool.h"

void printBoard(int w, int h, bool board[h][w]) {
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			putchar(board[i][j] ? 'O' : ' ');
		}
		putchar('\n');
	}
	putchar('\n');
}

int count(int w, int h, bool board[h][w], int x, int y) {
	int n = 0;
	for (int i = -1; i <= 1; i++) {
		for (int j = -1; j <= 1; j++) {
			if(!(i == 0 && j == 0) &&
				(y + j) >= 0 && (y + j) < h &&
			       	(x + i) > 0 && (x + i) < w)
				n += board[y+j][x+i];
		}
	}	
	return n;
}

void simulate(int w, int h, bool board[h][w]) {
	bool tmp[h][w];
	
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			int n = count(w, h, board, j, i);
			if (board[i][j] == 1 && (n == 2 || n == 3))
				tmp[i][j] = 1;
			else if (board[i][j] == 0 && n == 3)
				tmp[i][j] = 1;
			else
				tmp[i][j] = 0;
		}
	}
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			board[i][j] = tmp[i][j];
		}
	}
}

int main (int argc, char **argv) {
	if (argc != 4)
		return 0;

	char buf;
       	int w = 0, h= 0 , iter = 0;
	w = atoi(argv[1]);
	h = atoi(argv[2]);
	iter = atoi(argv[3]);
	bool board[h][w];
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			board[i][j] = 0;
		}
	}
	int x = 0, y = 0;
	bool pen = 0;
	while (read(0,&buf, 1) > 0) { 
		if (buf == 'x')
			pen = !pen;
		else if (buf == 'w' && y > 0)
			y--;
		else if (buf == 's' && y < h - 1)
			y++;
		else if (buf == 'a' && x > 0)
			x--;
		else if (buf == 'd' && x < w - 1)
			x++;
		if (pen)
			board[y][x] = 1;
	}
	while (iter-- > 0)
		simulate(w, h, board);
	printBoard(w, h, board);
}
