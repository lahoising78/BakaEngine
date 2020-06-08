#ifndef _BAKA_APPLICATION_H_
#define _BAKA_APPLICATION_H_

#define BAKA_WINDOW_NAME_MAX_LENGTH 256

namespace baka
{

typedef struct baka_app_config_s
{
    int     initialWindowWidth;
    int     initialWindowHeight;
    char    initialWindowName[BAKA_WINDOW_NAME_MAX_LENGTH];
} BakaApplicationConfig;

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
    BakaApplicationConfig app_config;
    bool running;
};

} // namespace baka

#endif