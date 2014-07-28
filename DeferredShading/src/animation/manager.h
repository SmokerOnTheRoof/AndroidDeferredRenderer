#pragma once

#include <vector>


#include "controller.h"

namespace Animation{

/** \class Manager
 *  \brief The animation manager.
 *
 *  This class represents the animation manager.
 *  Animation::Controller which will be added to the
 *  Manager can be updated with the update() function.
 *
 */

class Manager{

public:

    Manager();
    ~Manager();

    /**
     *	\brief Updates all controllers.
     *
     *  Updates all controllers in the list for the given time step.
     *
     *	/param stepSize The time step in milliseconds.
     */
    void update(unsigned int stepSize);

    /**
     *	\brief Adds controller to the controller list.
     *
     *  Adds a new controller to the controller list.
     *  Will not take ownership. It's the callers responsibility 
     *  to free memory afterwards.
     *
     *	/param controller New controller which should be added to the list.
     */
    void addController(const Controller& controller){controllerList.push_back(controller);}

private:

    std::vector<Controller> controllerList;


};

} // End namespace Animation
