#ifndef __WINDOW_H__
#define __WINDOW_H__
#include <glad/glad.h>
#include "GLFW/glfw3.h"

#define MINOR_VERSION 3
#define MAJOR_VERSION 3
#define WINDOW_NAME "minecraft_copy"
#define WINDOW_HEIGHT 600
#define WINDOW_WIDHT 800
namespace WindowNamespace{
    class Window{
        private:
            GLFWwindow *window;
            const uint16_t windowHeight = 600;
            const uint16_t windowWidth = 800;
            const uint8_t x_init = 0;
            const uint8_t y_init = 0;
        public:
            static void frameBuffer_size_callback(GLFWwindow*, uint16_t, uint16_t);
            GLFWwindow* getWindow() const;
            void initWindowSetup();
            void swapBuffers();
            void pollEvents();
            void setCurrentContext();
            void createWindow();
            void setViewPort();
            bool checkWindow();

            ~Window();
    };
}
#endif