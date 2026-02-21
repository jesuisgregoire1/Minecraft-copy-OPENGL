#include "camera.hpp"

CameraNamespace::Camera::Camera(){
    view = glm::lookAt(cameraPos, cameraPos+cameraFront, cameraUp);
    
}

float CameraNamespace::Camera::GetCameraSpeed() const{
    return cameraSpeed;
}

void CameraNamespace::Camera::SetCameraSpeed(float value){
    cameraSpeed = value;
}

glm::vec3 CameraNamespace::Camera::GetcameraPos() const{
    return cameraPos;
}

void CameraNamespace::Camera::MoveForwardCamera(float dt){
    this->cameraPos += cameraSpeed*cameraFront*dt;

    // for (int row = 0; row < 3; ++row) {
    //     std::cout << this->cameraPos[row] << " ";
    // }
    // std :: cout << std :: endl;
}

void CameraNamespace::Camera::MoveBackwardCamera(float dt){
    cameraPos -= cameraSpeed*cameraFront*dt;
}

void CameraNamespace::Camera::MoveRightCamera(float dt){
    cameraPos -= glm::normalize(glm::cross(cameraUp, cameraFront))*cameraSpeed*dt;
}

void CameraNamespace::Camera::MoveLeftCamera(float dt){
    cameraPos += glm::normalize(glm::cross(cameraUp, cameraFront))*cameraSpeed*dt;
}

glm::mat4 CameraNamespace::Camera::ModifyViewMatrix(){
    return glm::lookAt(cameraPos, cameraPos+cameraFront, cameraUp);
}

void CameraNamespace::Camera::ProcessData(double xPos, double yPos){
    // std :: cout << "xPos = " << xPos << "|| yPos = " << yPos << std :: endl;
    if (firstMovement)
    {
        lastX = xPos;
        lastY = yPos;
        firstMovement = false;
    }
  
    float xoffset = xPos - lastX;
    float yoffset = lastY - yPos; 
    lastX = xPos;
    lastY = yPos;

    float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw   += xoffset;
    pitch += yoffset;

    if(pitch > 89.0f)
        pitch = 89.0f;
    if(pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    std :: cout << "X = " << direction.x << " || " << "Y = " << direction.y << " || " << "Z = " << direction.z<< std :: endl;
    cameraFront = glm::normalize(direction);
}

void CameraNamespace::Camera::MouseCallback(GLFWwindow* window, double xPos, double yPos){
    Camera* camera = static_cast<Camera*>(glfwGetWindowUserPointer(window));
    camera->ProcessData(xPos, yPos);
}

