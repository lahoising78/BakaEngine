#include <glm/gtc/matrix_transform.hpp>
#include "baka_camera.h"
#include "baka_graphics.h"

namespace baka
{
    
OrthographicsCamera::OrthographicsCamera()
    : CameraBase()
{
    this->rotation = 0.0f;

    float width = (float)Graphics::GetWidth();
    float height = (float)Graphics::GetHeight();

    this->projection = glm::ortho(0.0f, width, 0.0f, height, -1.0f, 1.0f);

    RecalculateMatrix();
}

void OrthographicsCamera::RecalculateMatrix()
{
    this->view = 
        glm::translate( identity_matrix, this->position ) *
        glm::rotate( identity_matrix, glm::radians(this->rotation), glm::vec3(0, 0, 1));
    
    view = glm::inverse(view);

    this->view_projection = this->projection * this->view;
}

} // namespace baka
