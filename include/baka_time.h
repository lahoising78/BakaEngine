#ifndef _BAKA_TIME_H_
#define _BAKA_TIME_H_

#include <baka_stopwatch.h>

namespace baka
{
    
class Time
{
friend class BakaApplication;

public:
    /** 
     * @brief get time since last frame in milliseconds
     * @return time since last frame in milliseconds
     */
    float GetDeltaTime() { return delta_time; }
    
    template<typename TimeDataType = int64_t, typename TimeUnit = millisec> 
    TimeDataType GetTime() { return game_start_time.GetTime<TimeDataType,TimeUnit>(); }

    static Time &Get()
    {
        static Time time = Time();
        return time;
    }

private:
    Time();
    void FrameStart();
    void FrameEnd();

private:
    float delta_time;                       // calculated in milli
    Stopwatch frame_stopwatch;
    float lock_frametime;

    Stopwatch game_start_time;
};

} // namespace baka


#endif