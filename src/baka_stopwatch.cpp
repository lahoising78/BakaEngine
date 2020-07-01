#include <baka_stopwatch.h>

namespace baka
{
    
Stopwatch::Stopwatch()
{
    start_time = std::chrono::high_resolution_clock::now();
    pause_time = std::chrono::high_resolution_clock::now();
    paused = false;
    started = false;
}

void Stopwatch::Start()
{
    start_time = std::chrono::high_resolution_clock::now();
    started = true;
}

} // namespace baka