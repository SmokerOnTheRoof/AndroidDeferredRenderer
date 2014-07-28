#pragma once

#include <vector>

#ifdef ANDROID

#include <stddef.h>

#endif // ANDROID

/** \class Timer
 *  \brief Simple timer.
 *
 *  The timer get the duration since the last time
 *  the get duration function was called. When first instantiated
 *  a buffer size and initial values will be required.
 *  To calculate the time since the last duration call the min and
 *  max value in the buffer are discarded and the average of the
 *  remaining values will be returned.
 * 
 *  This functionality should smooth the time values and prevent big
 *  time steps when debugging and additional logic for initialization.
 *
 */

class Timer{

public:

    Timer(size_t bufferSize = 7, unsigned int initValues = 1000/60);
    ~Timer();

    /**
     *	\brief Gets the duration since the last call to getDuration.
     *
     *	Returns the average time between the last bufferSize-2 calls to
     *  getDuration(). The maximum and minimum value are discarded.
     *
     *  /return returnValue
     */
    unsigned int getDuration();

private:

    std::vector<unsigned int> timeBuffer;

    size_t currentIndex;

    unsigned int lastTime;

};
