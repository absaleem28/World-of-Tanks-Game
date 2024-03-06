#pragma once

#include "utils/glm_utils.h"
#include "utils/math_utils.h"


namespace implemented_tema2
{
    class Camera
    {
     public:
        Camera()
        {
            position    = glm::vec3(0, 2, 5);
            forward     = glm::vec3(0, 0, -1);
            forward_view = glm::vec3(0, 0, -1);
            up          = glm::vec3(0, 1, 0);
            up_view          = glm::vec3(0, 1, 0);
            right       = glm::vec3(1, 0, 0);
            right_view       = glm::vec3(1, 0, 0);
            distanceToTarget = 2;
            cameraMode = true;
        }

        Camera(const glm::vec3 &position, const glm::vec3 &center, const glm::vec3 &up)
        {
            Set(position, center, up);
            cameraMode = true;
        }

        ~Camera()
        { }

        // Update camera
        void Set(const glm::vec3 &position, const glm::vec3 &center, const glm::vec3 &up)
        {
            this->position = position;
            forward     = glm::normalize(center - position);
            forward_view     = glm::normalize(center - position);
            right       = glm::cross(forward, up);
            right_view       = glm::cross(forward_view, up);
            this->up    = glm::cross(right, forward);
            this->up_view    = glm::cross(right_view, forward_view);
        }

        void MoveForward(float distance)
        {
            glm::vec3 dir = glm::normalize(glm::vec3(forward.x, 0, forward.z));
            position += dir * distance;
        }
        void MoveForwardM(float distance)
        {
            glm::vec3 dir = glm::normalize(glm::vec3(up_view.x, 0, up_view.z));
            position += dir * distance;
        }

        void TranslateForward(float distance)
        {
            position += glm::normalize(forward_view) * distance;

        }

        void TranslateUpward(float distance)
        {
            position += glm::normalize(up) * distance;
        }

        void TranslateRight(float distance)
        {
            position += glm::normalize(right_view) * distance;
        }

        void RotateFirstPerson_OY_view(float angle)
        {
            glm::vec4 newVecForward = glm::vec4(forward_view, 1.0);
            glm::vec4 newVecRight = glm::vec4(right_view, 1.0);

            glm::vec4 newVectorForward = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0, 1, 0)) * newVecForward;
            glm::vec4 newVectorRight = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0, 1, 0)) * newVecRight;

            forward_view = glm::normalize(glm::vec3(newVectorForward));
            right_view = glm::normalize(glm::vec3(newVectorRight));

            up_view = glm::normalize(glm::cross(right_view, forward_view));
        }

        void RotateFirstPerson_OY_position(float angle)
        {
            glm::vec4 newVecForward = glm::vec4(forward, 1.0);
            glm::vec4 newVecRight = glm::vec4(right, 1.0);

            glm::vec4 newVectorForward = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0, 1, 0)) * newVecForward;
            glm::vec4 newVectorRight = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0, 1, 0)) * newVecRight;

            forward = glm::normalize(glm::vec3(newVectorForward));
            right = glm::normalize(glm::vec3(newVectorRight));

            up = glm::normalize(glm::cross(right, forward));
        }

        void RotateThirdPerson_OY_view(float angle)
        {
            // TODO(student): Rotate the camera in third-person mode around
            // the OY axis.
            TranslateForward(distanceToTarget);
            // TranslateUpward(distanceToTarget);
            // TranslateRight(distanceToTarget);
            RotateFirstPerson_OY_view(angle);
            // TranslateRight(-distanceToTarget);
            // TranslateUpward(-distanceToTarget);
            TranslateForward(-distanceToTarget);
        }

        void RotateThirdPerson_OY_position(float angle)
        {
            // TODO(student): Rotate the camera in third-person mode around
            // the OY axis.
            TranslateForward(distanceToTarget);
            // TranslateUpward(distanceToTarget);
            // TranslateRight(distanceToTarget);
            RotateFirstPerson_OY_position(angle);
            // TranslateRight(-distanceToTarget);
            // TranslateUpward(-distanceToTarget);
            TranslateForward(-distanceToTarget);
        }

        glm::mat4 GetViewMatrix()
        {
            // Returns the view matrix
            return glm::lookAt(position, position + forward_view, up_view);
        }

        glm::vec3 GetTargetPosition()
        {
            return position + forward * distanceToTarget;
        }

     public:
        float distanceToTarget;
        glm::vec3 position;
        glm::vec3 forward;
        glm::vec3 forward_view;
        glm::vec3 right;
        glm::vec3 right_view;
        glm::vec3 up;
        glm::vec3 up_view;
        bool cameraMode;
    };
}   // namespace implemented
