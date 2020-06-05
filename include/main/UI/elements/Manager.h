/*
 * Manager.h
 *
 *      Author: Przybysz Filip
 */

#ifndef TRAFFIC_SIM_MAIN_UI_ELEMENTS_MANAGER_H
#define TRAFFIC_SIM_MAIN_UI_ELEMENTS_MANAGER_H

#include <map>

#include "AllElements.h"

namespace Element {

    class Manager {
        std::map<Draw::DrawID, Element::Element> elements_;
        
    public:
        
        Manager ();
        virtual ~Manager();

    };

};

#endif