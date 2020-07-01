#include <baka_logger.h>
#include <baka_time.h>

namespace baka
{
    
Time::Time()
{
    delta_time = 1.0f / 30.0f;
    frame_stopwatch = Stopwatch();
    lock_frametime = 0.0f;

    game_start_time = Stopwatch();
}

void Time::FrameStart()
{
    frame_stopwatch.Start();
}

void Time::FrameEnd()
{
    delta_time = frame_stopwatch.GetTime<float, std::milli>();
    /*  if frame time is more than a second, this was probably caused
        by debugging or something like that, so assume an ideal frame time instead */
    if(delta_time > 1000.0f) delta_time = 1.0f / 60.0f;

    bakalog("frame time: %fms", delta_time);
}


} // namespace baka