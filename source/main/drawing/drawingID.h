#ifndef DRAWING_ID_H
#define DRAWING_ID_H

#include "../utility/ID.h"

class DrawingID: public ID<DrawingID>{

    friend class Drawable;

    DrawingID(ID<DrawingID> id)
    : ID<DrawingID>(id)
    {}

public:
};

#endif