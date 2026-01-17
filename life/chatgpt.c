#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

static int in_bounds(int x, int y, int w, int h)
{
    return (x >= 0 && x < w && y >= 0 && y < h);
}

static int count_neighbors(int *grid, int x, int y, int w, int h)
{
    int dx, dy, count = 0;

    dy = -1;
    while (dy <= 1)
    {
        dx = -1;
        while (dx <= 1)
        {
            if (!(dx == 0 && dy == 0))
            {
                if (in_bounds(x + dx, y + dy, w, h))
                    count += grid[(y + dy) * w + (x + dx)];
            }
            dx++;
        }
        dy++;
    }
    return count;
}

static void simulate(int *grid, int w, int h, int iterations)
{
    int *next;
    int x, y, n;

    while (iterations-- > 0)
    {
        next = calloc(w * h, sizeof(int));
        if (!next)
            return;

        y = 0;
        while (y < h)
        {
            x = 0;
            while (x < w)
            {
                n = count_neighbors(grid, x, y, w, h);
                if (grid[y * w + x])
                {
                    if (n == 2 || n == 3)
                        next[y * w + x] = 1;
                }
                else
                {
                    if (n == 3)
                        next[y * w + x] = 1;
                }
                x++;
            }
            y++;
        }
        free(grid);
        grid = next;
    }

    y = 0;
    while (y < h)
    {
        x = 0;
        while (x < w)
        {
            if (grid[y * w + x])
                putchar('O');
            else
                putchar(' ');
            x++;
        }
        putchar('\n');
        y++;
    }
    free(grid);
}

int main(int argc, char **argv)
{
    int w, h, iterations;
    int *grid;
    char buf;
    int x = 0, y = 0;
    int pen = 0;

    if (argc != 4)
        return 1;

    w = atoi(argv[1]);
    h = atoi(argv[2]);
    iterations = atoi(argv[3]);

    if (w <= 0 || h <= 0 || iterations < 0)
        return 1;

    grid = calloc(w * h, sizeof(int));
    if (!grid)
        return 1;

    while (read(0, &buf, 1) > 0)
    {
        if (buf == 'x')
            pen = !pen;
        else if (buf == 'w')
            y--;
        else if (buf == 's')
            y++;
        else if (buf == 'a')
            x--;
        else if (buf == 'd')
            x++;

        if (pen && in_bounds(x, y, w, h))
            grid[y * w + x] = 1;
    }

    simulate(grid, w, h, iterations);
    return 0;
}

