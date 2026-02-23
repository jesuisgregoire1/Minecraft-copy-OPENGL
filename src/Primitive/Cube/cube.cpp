#include "cube.hpp"

void CubeNamespace::Cube::CreateCube(){
    //Used to bind the Vertex Array Object
    point = new PointNamespace::Point();
    coordSystem = new CoordSystem::CoordSystem();
    CreatingTextures();
    glGenVertexArrays(1, &VAO);
    glGenBuffers(2, VBO);
    glGenBuffers(1, &EBO);
    glBindVertexArray(VAO);
    //Used to bind the Vertex Buffer Object
    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Final part to tell the shader how to read this data
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(textures), textures, GL_STATIC_DRAW);

    // Final part to tell the shader how to read this data
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2*sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);

    //Used to bind the Element Buffer object buffer
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
}

void CubeNamespace::Cube::Draw(){
    glBindVertexArray(VAO);
    //glDrawArrays(GL_TRIANGLES, 0, 36);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void CubeNamespace::Cube::CreatingTextures(){
    uint8_t counter = 0;
    uint16_t posY = 368;
    uint16_t posX_first = 80;
    uint16_t posX_second = 96;
    uint16_t posX_third = 112;
    uint16_t posX_per_face[6] = {
        posX_third,  posX_third,
        posX_third, posX_third,    
        posX_second,  posX_first
    };

    for (int f = 0; f < 6; f++) {
        int i = f * 8; // 8 floats per face (4 vertices × 2)
        uint16_t posX = posX_per_face[f];

        textures[i + 0] = ((posX) + 16)/ widthTexture; // top right
        textures[i + 1] = ((posY) - 16)/ heightTexture;

        textures[i + 2] = ((posX) + 16)/ widthTexture; // bottom right
        textures[i + 3] = posY / heightTexture;

        textures[i + 4] = posX / widthTexture;        // bottom left
        textures[i + 5] = posY / heightTexture;

        textures[i + 6] = posX / widthTexture;        // top left
        textures[i + 7] = ((posY) -16)/ heightTexture;
    }
}

void CubeNamespace::Cube::Rotate(CameraNamespace::Camera camera, 
                                ShaderNamespace::Shader shader){
    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(point->x, point->y, point->z));
    model = glm::rotate(model, glm::radians(50*(float)glfwGetTime()), glm::vec3(0.0f, 1.0f, 0.0f));

    glm::mat4 view = camera.ModifyViewMatrix();
    projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
    int modelLoc = glGetUniformLocation(shader.ID, "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    int viewLoc = glGetUniformLocation(shader.ID, "view");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    int projectionLoc = glGetUniformLocation(shader.ID, "projection");
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
}

void CubeNamespace::Cube::SetCoordSystem(CameraNamespace::Camera camera,
                                        ShaderNamespace::Shader shader){
    coordSystem->SetModel(glm::vec3(1.0f,1.0f,1.0f),
                    glm::vec3(point->x, point->y, point->z), 
                    glm::radians(50*(float)glfwGetTime()), glm::vec3(0.0f, 1.0f, 0.0f));
    coordSystem->SetView(camera);
    coordSystem->SetProjection();
    coordSystem->SetMVP(shader);
}