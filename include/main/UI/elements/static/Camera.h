/*
 * Camera.h
 *
 *      Author: Przybysz Filip
 */

#ifndef TRAFFIC_SIM_CAMERA_H
#define TRAFFIC_SIM_CAMERA_H

#include <random>

#include "StaticElement.h"

namespace Elements {

    class Camera : public StaticElement {

    using Noise = std::normal_distribution<double>;

    public:

        Camera(sf::Window& window, const Texture_ptr& texture);
        ~Camera();

    };

}

#endif
