#ifndef _BAKA_CAMERA_H_
#define _BAKA_CAMERA_H_

#include "baka_camera_base.h"

namespace baka
{
    class OrthographicsCamera : public CameraBase<float>
    {
    public:
        OrthographicsCamera();
    
    private:
        void RecalculateMatrix();
    };
} // namespace baka

#endif