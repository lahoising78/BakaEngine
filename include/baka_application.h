#ifndef _BAKA_APPLICATION_H_
#define _BAKA_APPLICATION_H_

#include "baka_graphics.h"
#include "baka_input.h"

namespace baka
{

typedef struct
{
    WindowConfig window_config;
    InputConfig input_config;
} BakaAppConfig;

class BakaApplication
{
public:
    BakaApplication();
    ~BakaApplication();
    void Start();

private:
    bool Init();
    void Run();
    virtual void Update() = 0;

protected:
    BakaAppConfig app_config;
    bool running;
};

} // namespace baka

#endif