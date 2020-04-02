#ifndef ZPR_TRAFFIC_SIM_DRAWING_ID_H
#define ZPR_TRAFFIC_SIM_DRAWING_ID_H

#include "../utility/ID.h"

class DrawingID: virtual public ID<DrawingID>{

    friend class Drawable;

    DrawingID(const ID<DrawingID> id)
    : ID<DrawingID>(id)
    {}

public:
};

#endif