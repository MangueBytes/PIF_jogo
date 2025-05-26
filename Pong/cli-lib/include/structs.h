#ifndef STRUCTS_H
#define STRUCTS_H

typedef struct {
    int x, y;
    int lastX, lastY;
    int incX, incY;
} Ball;

typedef struct {
    int y;
    const int height;
} Paddle;

typedef struct {
    int left;
    int right;
} Score;

typedef struct {
    int y;
    int height;
    int dir;
    int active;
    long timer;
} Portal;

#endif