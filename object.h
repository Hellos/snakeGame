#ifndef OBJECT_H
#define OBJECT_H

#include "consts.h"

class Obj
{
protected:
    struct { float x = GRID_WIDTH / 2, y = GRID_HEIGHT / 2; } pos;

public:
    Obj();
};

#endif // OBJECT_H
