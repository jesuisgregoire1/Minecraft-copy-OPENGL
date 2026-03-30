#include "quad.hpp"

QuadNamespace::Quad::Quad(){
    glGenVertexArrays(1, &VAO);
    glGenBuffers(2, VBO);
    glGenBuffers(1, &EBO);
    
    glBindVertexArray(VAO);
    
    //Used to bind the Vertex Buffer Object
    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(textures), textures, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2*sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
}

void QuadNamespace::Quad::Draw(){
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}


void QuadNamespace::Quad::Rotate(CameraNamespace::Camera camera,
                                ShaderNamespace::Shader shader){
    shader.use();
    model = glm::mat4(1.0f);
    model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    // model = glm::scale(model, 10.0f*glm::vec3(1.0f, 1.0f, 0.0f));
    glm::mat4 view = camera.ModifyViewMatrix();
    projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
    int modelLoc = glGetUniformLocation(shader.ID, "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    int viewLoc = glGetUniformLocation(shader.ID, "view");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    int projectionLoc = glGetUniformLocation(shader.ID, "projection");
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
}
//DELETE IT AFTER LOL!!!!!TESTING PURPOSES

//0,1,3|| 1,2,3 || 2,1,3 || 3,0,1 ||
void QuadNamespace::Quad::CrossTesting(uint8_t ii, uint8_t jj, uint8_t kk, glm::vec3 crossVec[]){
            float v[12]   =   {0.5f,  0.5f, 0.0f,  // top right
                                0.5f, -0.5f, 0.0f,  // bottom right
                                -0.5f, -0.5f, 0.0f,  // bottom left
                                -0.5f,  0.5f, 0.0f};   // top left
    glm::vec3 normals[3];
    for(uint8_t i=0; i<4; i++){
        for(uint8_t j=i*3; j < i*3+4; j+=3){
            normals[i] = glm::vec3(v[j],v[j+1],v[j+2]);
        }
    }
    glm::vec3 p1 = normals[ii];
    glm::vec3 p2 = normals[jj];
    glm::vec3 p3 = normals[kk];
    glm::vec3 diffBetweenVectors = p2 - p1;
    glm::vec3 diffBetweenAnotherVectors = p3 - p1;
    crossVec[ii] = glm::cross(diffBetweenAnotherVectors, diffBetweenVectors);
}


void QuadNamespace::Quad::Test(){
    //0,1,3|| 1,2,3 || 2,3,1 || 3,0,1 ||
    CrossTesting(0,1,3, crossVec);
    CrossTesting(1,2,3, crossVec);
    CrossTesting(2,3,1, crossVec);
    CrossTesting(3,0,1, crossVec);
    glm::vec3 normal1[8] = {glm::vec3(0.5f, 0.5f, 0.0f), glm::vec3(0.5f,  0.5f, 0.0f) +     glm::normalize(crossVec[0]),
                            glm::vec3(0.5f, -0.5f, 0.0f), glm::vec3(0.5f, -0.5f, 0.0f) +    glm::normalize(crossVec[1]),
                            glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec3(-0.5f, -0.5f, 0.0f) +  glm::normalize(crossVec[2]),
                            glm::vec3(-0.5f, 0.5f, 0.0f), glm::vec3(-0.5f, 0.5f, 0.0f) +    glm::normalize(crossVec[3])};
    glGenVertexArrays(1, &second_VAO);
    glGenBuffers(1, &second_VBO);
    glBindVertexArray(second_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, second_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(normal1), normal1, GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);
    glEnableVertexAttribArray(0);
}
void QuadNamespace::Quad::GenerateCrossProduct(CameraNamespace::Camera camera, ShaderNamespace::Shader shader){
    shader.use();
    model = glm::mat4(1.0f);
    // model = glm::translate(model, glm::vec3(0.5f, 0.5f, 0.0f));
    model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    // model = glm::scale(model, 20.0f*glm::vec3(1.0f, 1.0f, 1.0f));
    glm::mat4 view = camera.ModifyViewMatrix();
    projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
    int modelLoc = glGetUniformLocation(shader.ID, "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    int viewLoc = glGetUniformLocation(shader.ID, "view");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    int projectionLoc = glGetUniformLocation(shader.ID, "projection");
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
}

void QuadNamespace::Quad::SecondDraw(){
    glBindVertexArray(second_VAO);
    glDrawArrays(GL_LINES, 0, 8);
    glBindVertexArray(0);
}

