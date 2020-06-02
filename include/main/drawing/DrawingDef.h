/*
 * DrawingDef.h
 *
 *      Author: Kordowski Mateusz
 */

#ifndef TRAFFIC_SIM_MAIN_DRAWING_DRAWING_DEF_H
#define TRAFFIC_SIM_MAIN_DRAWING_DRAWING_DEF_H

#include <SFML/Graphics.hpp>
#include <memory>

#include "DrawingID.h"

namespace Drawing{

class DrawingDef{
    std::shared_ptr<>;

public:
    DrawingDef();
    ~DrawingDef();
    DrawingDef(const DrawingDef&);
    DrawingDef(DrawingDef&& DrawingDef);
    DrawingDef& operator=(DrawingDef&& other);
};
}

#endif
