#include "manager.h"

#include "controller.h"

namespace Animation{

Manager::Manager()
    : controllerList()
{

}

Manager::~Manager()
{

}

void Manager::update( unsigned int stepSize )
{
    for(auto iter = controllerList.begin(); iter < controllerList.end(); ){

        if( iter->update(stepSize)){
            iter++;
        } else{
            // Remove the controller from the list if the object under control
            // doesn't exist anymore.
            controllerList.erase(iter++);
        }
    }
}

} // End namespace Animation
