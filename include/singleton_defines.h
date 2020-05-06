#ifndef _SINGLETON_DEFINES_H_
#define _SINGLETON_DEFINES_H_

/** 
 * @brief define the basic properties of a singleton
 * @param T the class we are defining a singleton for
 */
#define SINGLETON_CLASS_PROPERTIES(T) \
private: \
    static T *instance; \
    T(); \
    void Close(); \
\
public: \
    static T *Get() \
    { \
        if(!instance) \
            instance = new T(); \
        return instance; \
    } \
    ~T();

#define SINGLETON_COMMON_IMPLEMENTATION(T)  \
T *T::instance;                             \
                                            \
static void T##Close()                      \
{                                           \
    T *instance = T::Get();                 \
    if(instance) delete instance;           \
}

#endif