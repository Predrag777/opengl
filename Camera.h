#ifndef CAMERA_H_INCLUDED
#define CAMERA_H_INCLUDED

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <string>

class Camera{
    public:
        Camera(const glm::vec3& pos, float fov, float aspect, float zNear, float zFar){//fov->field-of-view
            m_perspective=glm::perspective(fov, aspect, zNear, zFar);
            m_position=pos;

            m_forward=glm::vec3(0,0,1);//Z direction
            m_up     =glm::vec3(0,1,0);//Y direction
        }

        inline glm::mat4 GetViewProjection() const{
            //std::cout << "Camera Position: " << glm::to_string(m_position) << std::endl;

            return m_perspective*glm::lookAt(m_position, m_position+m_forward, m_up);
        }
    protected:
    private:
        glm::mat4 m_perspective;
        glm::vec3 m_position;
        glm::vec3 m_forward; //Forward looking
        glm::vec3 m_up;      //Up looking       
};

#endif //