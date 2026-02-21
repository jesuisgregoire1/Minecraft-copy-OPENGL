#ifndef __INPUT_HANDLER__H
#define __INPUT_HANDLER__H
#include "../Camera/camera.hpp"
#include <GLFW/glfw3.h>
namespace InputHandlerNamespace{
    class InputHandler{
        public:
            void ProcessInput(GLFWwindow* window, CameraNamespace::Camera& camera, float dt);
    };
}
#endif