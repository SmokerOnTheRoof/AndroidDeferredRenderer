#include "timer.h"

#include <algorithm>
#include <numeric>

#ifdef WIN32

#include "SDL.h"
#include "SDL_timer.h"

#endif // End WIN32

#include "assert.h"

Timer::Timer(size_t bufferSize/* = 7*/, unsigned int initValues /*= 1000/60*/ )
    : timeBuffer()
    , currentIndex(0)
    , lastTime(0)
{
    assert(bufferSize >= 3); // To be honest the buffer size should be at least 5
    timeBuffer.assign(bufferSize, initValues);
}

Timer::~Timer()
{

}

unsigned int Timer::getDuration()
{
    // ToDo: Ugly hack. I don't want to check if the timer subsystem was initialized
    //       every time i call getDuration(). When i switch to boost in the future the
    //       SDL timer subsystem isn't required anymore.

#ifdef WIN32
    static int timerInit = SDL_InitSubSystem(SDL_INIT_TIMER); 
    assert(timerInit >= 0);
#endif

#ifdef WIN32
    unsigned int newTime = SDL_GetTicks();
    unsigned int newDuration = newTime - lastTime;

    lastTime = newTime;
#endif
#ifdef ANDROID
    // ToDo: Now Android that Android can't use SDL
    //          it might be better to switch to the boost timers
    unsigned int newDuration = 1000/60;
#endif

    timeBuffer[currentIndex] = newDuration;

    currentIndex = (currentIndex+1) % timeBuffer.size();

    // Get the min and max element
    unsigned int max = *std::max_element(timeBuffer.begin(), timeBuffer.end());
    unsigned int min = *std::min_element(timeBuffer.begin(), timeBuffer.end());

    // Get the sum
    unsigned int sum = std::accumulate(timeBuffer.begin(), timeBuffer.end(), 0);

    // substract the min and max
    sum = sum - max - min;

    return sum / (timeBuffer.size()-2);

}

