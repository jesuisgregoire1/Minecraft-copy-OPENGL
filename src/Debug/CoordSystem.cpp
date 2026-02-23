#include "CoordSystem.hpp"
CoordSystem::CoordSystem::CoordSystem(){
    InitializePoints();
    InitializeColors();
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glGenBuffers(2, VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
                        3*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,
                        3*sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glBindVertexArray(0);
}

void CoordSystem::CoordSystem::Draw(){
    glBindVertexArray(VAO);
    glDrawArrays(GL_LINES, 0, 6);
    glBindVertexArray(0);
}


void CoordSystem::CoordSystem::InitializeColors(){
    //red -> x
    colors[0] = 1.0f;
    colors[1] = 0.0f;
    colors[2] = 0.0f;
    colors[3] = 1.0f;
    colors[4] = 0.0f;
    colors[5] = 0.0f;
    //green -> y
    colors[6] = 0.0f;
    colors[7] = 1.0f;
    colors[8] = 0.0f;
    colors[9] = 0.0f;
    colors[10] = 1.0f;
    colors[11] = 0.0f;
    //blue -> z
    colors[12] = 0.0f;
    colors[13] = 0.0f;
    colors[14] = 1.0f;
    colors[15] = 0.0f;
    colors[16] = 0.0f;
    colors[17] = 1.0f;
}

void CoordSystem::CoordSystem::InitializePoints(){
    //x
    points[6] = 0.0f;
    points[7] = 0.0f;
    points[8] = 0.0f;
    points[9] = 1.0f;
    points[10] = 0.0f;
    points[11] = 0.0f;
    //y
    points[0] = 0.0f;
    points[1] = 0.0f;
    points[2] = 0.0f;
    points[3] = 0.0f;
    points[4] = 1.0f;
    points[5] = 0.0f;
    //z
    points[12] = 0.0f;
    points[13] = 0.0f;
    points[14] = 0.0f;
    points[15] = 0.0f;
    points[16] = 0.0f;
    points[17] = 1.0f;

}

void CoordSystem::CoordSystem::SetModel(glm::vec3 scale = glm::vec3(2.0f,2.0f,2.0f),
                                        glm::vec3 translation = glm::vec3(0.0f, 0.0f, 0.0f), 
                                        float angle=0.0f, glm::vec3 axis = glm::vec3(0.0f, 0.0f, 0.0f)){
    model = glm::mat4(1.0f);
    model = glm::scale(model, scale);
    model = glm::translate(model, translation);
    model = glm::rotate(model, angle, axis);
}

void CoordSystem::CoordSystem::SetView(CameraNamespace::Camera camera){
    view = camera.ModifyViewMatrix();
}

void CoordSystem::CoordSystem::SetProjection(){
    projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
}

void CoordSystem::CoordSystem::SetMVP(ShaderNamespace::Shader shader){
    shader.use();
    int modelLoc = glGetUniformLocation(shader.ID, "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    int viewLoc = glGetUniformLocation(shader.ID, "view");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    int projectionLoc = glGetUniformLocation(shader.ID, "projection");
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
}



//Dont need this shit anymore
// void CoordSystem::CoordSystem::SetupColors(ShaderNamespace::Shader shader){
//     shader.use();
//     int useDebugLoc = glGetUniformLocation(shader.ID, "useDebugColor");
//     glUniform1i(useDebugLoc, 1);

//     int debugColorLoc = glGetUniformLocation(shader.ID, "debugColor");
//     glUniform3f(debugColorLoc, 0.0f, 1.0f, 0.0f);
// }

