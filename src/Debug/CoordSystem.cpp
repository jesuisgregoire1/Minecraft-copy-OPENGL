#include "CoordSystem.hpp"
CoordSystem::CoordSystem::CoordSystem(){
    InitializePoints_X();
    InitializePoints_Y();
    // glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    // glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(points_y), &points_y, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_TRUE,
                        2*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // glGenBuffers(1, &VBO[1]);
    // glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
    // glBufferData(GL_ARRAY_BUFFER, sizeof(points_x), &points_x, GL_STATIC_DRAW);
    // glVertexAttribPointer(0, 2, GL_FLOAT, GL_TRUE,
    //                     2*sizeof(float), (void*)0);
    // glEnableVertexAttribArray(0);
    // glGenBuffers(1, &VBO[2]);
    // glBindBuffer(GL_ARRAY_BUFFER, VBO[2]);
    // glBufferData(GL_ARRAY_BUFFER, sizeof(points_z), &points_z, GL_STATIC_DRAW);
    // glVertexAttribPointer(0, 2, GL_FLOAT, GL_TRUE,
    //                     2*sizeof(float), (void*)0);
    // glEnableVertexAttribArray(0);
}

void CoordSystem::CoordSystem::Draw(){
    //glBindVertexArray(VAO);
    glDrawArrays(GL_LINES, 0, 2);
    // glBindVertexArray(0);
}


void CoordSystem::CoordSystem::InitializePoints_X(){
    points_y[0] = 0.0f;
    points_y[1] = 0.0f;
    points_y[2] = 1.0f;
    points_y[3] = 0.0f;
}

void CoordSystem::CoordSystem::InitializePoints_Y(){
    points_y[0] = 0.0f;
    points_y[1] = 0.0f;
    points_y[2] = 0.0f;
    points_y[3] = 1.0f;
}


void CoordSystem::CoordSystem::InitializePoints_Z(){
    points_y[0] = 0.0f;
    points_y[1] = 0.0f;
    points_y[2] = 0.0f;
    points_y[3] = 1.0f;
}

void CoordSystem::CoordSystem::Rotate(CameraNamespace::Camera camera, 
                                ShaderNamespace::Shader shader){
    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
    model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
    glm::mat4 view = camera.ModifyViewMatrix();
    projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
    int modelLoc = glGetUniformLocation(shader.ID, "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    int viewLoc = glGetUniformLocation(shader.ID, "view");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    int projectionLoc = glGetUniformLocation(shader.ID, "projection");
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
}

void CoordSystem::CoordSystem::SetupColors(ShaderNamespace::Shader shader){
    shader.use();
    int useDebugLoc = glGetUniformLocation(shader.ID, "useDebugColor");
    glUniform1i(useDebugLoc, 1);

    int debugColorLoc = glGetUniformLocation(shader.ID, "debugColor");
    glUniform3f(debugColorLoc, 1.0f, 0.0f, 0.0f);

}