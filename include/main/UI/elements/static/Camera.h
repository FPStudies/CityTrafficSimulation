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

    /**
     * @brief camera object for registering positions of observed dynamic elements
     * 
     */
    class Camera : public StaticElement {

    /**
     * @brief type of noise error added to registered positions
     * 
     */
    using Noise = std::normal_distribution<double>;

    public:

        Camera(sf::Window& window, const Texture_ptr& texture);
        ~Camera();

    };

}

#endif
