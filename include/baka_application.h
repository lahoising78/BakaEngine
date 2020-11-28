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
    void Run();

private:
    bool Init();
    void Loop();

    virtual void Update() = 0;
    virtual void Start() = 0;
    virtual void OnRender() = 0;

protected:
    BakaAppConfig app_config;
    bool running;
};

} // namespace baka

#endif