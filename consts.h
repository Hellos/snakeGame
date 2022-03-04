#ifndef CONSTS_H
#define CONSTS_H

#define WHITE 148, 93, 11

static const int FRAME_RATE = 1000/60;
static const int SCREEN_WIDTH = 640;
static const int SCREEN_HEIGHT = 640;
static const int GRID_WIDTH = 32;
static const int GRID_HEIGHT = 32;

enum class Block { head, body, food, empty };
enum class Move { up, down, left, right };

#endif // CONSTS_H
