#ifndef _BAKA_STOPWATCH_H_
#define _BAKA_STOPWATCH_H_

#include <chrono>

namespace baka
{

typedef std::micro microsec;
typedef std::milli millisec;
typedef std::ratio<1L,1L> sec;
typedef std::ratio<60L,1L> minute;
typedef std::ratio<3600L,1L> hour;
typedef std::ratio<60L * 60L * 24L, 1L> day;
typedef std::ratio<60L * 60L * 24L * 7L, 1L> week;
typedef std::ratio<60L * 60L * 24L * 365L, 1L> year;
    
class Stopwatch
{
public:
    Stopwatch();
    
    void Start();

    template<typename TimeDataType = float, typename TimeUnits = sec>
    TimeDataType GetTime();

private:
    std::chrono::high_resolution_clock::time_point start_time;
    std::chrono::high_resolution_clock::time_point pause_time;
    bool paused;
    bool started;
};

template<typename TimeDataType, typename TimeUnits>
TimeDataType Stopwatch::GetTime()
{
    if(!started) return {};
    if(paused)
    {
        return std::chrono::duration_cast<std::chrono::duration<TimeDataType, TimeUnits>>(pause_time - start_time).count();
    }

    auto currentTime = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast< std::chrono::duration<TimeDataType,TimeUnits> >( currentTime - start_time ).count();
}

} // namespace baka

#endif