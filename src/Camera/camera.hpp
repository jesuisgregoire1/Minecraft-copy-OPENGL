#ifndef __CAMERA_H__
#define __CAMERA_H__
#include <iostream>
#include "../Window/window.hpp"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
namespace CameraNamespace{
    class Camera{
        private:
            float cameraSpeed = 5.25f;
            glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 10.0f);
            glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
            glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
            bool firstMovement = true;
            float sensitivity = 0.1f;
            double yaw=-90, pitch=0;
            double lastX;
            double lastY;
        public:
            glm::mat4 view;
            Camera();    
            float GetCameraSpeed() const;
            void SetCameraSpeed(float);
            glm::vec3 GetcameraPos() const;
            // void SetCameraPos(float);
            void MoveForwardCamera(float);
            void MoveBackwardCamera(float);
            void MoveRightCamera(float);
            void MoveLeftCamera(float);
            glm::mat4 ModifyViewMatrix();
            void ProcessData(double xPos, double yPos);
            static void MouseCallback(GLFWwindow* window, double xPos, double yPos);
    };
}
#endif