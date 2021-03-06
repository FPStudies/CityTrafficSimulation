/*
 * Basic.h
 *
 *      Author: Kordowski Mateusz
 */

#ifndef TRAFFIC_SIM_MAIN_EVENT_BASIC_H
#define TRAFFIC_SIM_MAIN_EVENT_BASIC_H

#include <memory>

#include "../screen/ScreenInterface.h"
#include "Interface.h"

namespace Event{

    /**
     * @brief Basic functionality.
     * @details
     * - closing application with esc key.
     * 
     */
    class Basic: virtual public Interface{

        virtual Basic* clone_impl() const override;

    public:
        Basic();
        virtual ~Basic();
        Basic(const Basic& event);

        virtual void run(sf::RenderWindow& window, const sf::Event& event) override;
        std::unique_ptr<Basic> clone() const;
        virtual bool equals(const Interface& other) const override;

    };

}

#endif
