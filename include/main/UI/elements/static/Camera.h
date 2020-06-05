/*
 * Camera.h
 *
 *      Author: Przybysz Filip
 */

#ifndef TRAFFIC_SIM_CAMERA_H
#define TRAFFIC_SIM_CAMERA_H

#include "StaticElement.h"

namespace Element {

    class Camera : public StaticElement {

    public:

        Camera(sf::Window& window, const Texture_ptr& texture);
        ~Camera();

    };

}

#endif