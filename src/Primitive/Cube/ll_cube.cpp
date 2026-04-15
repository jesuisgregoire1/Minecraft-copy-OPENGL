#include "ll_cube.hpp"

void ll_CubeNamespace::LL_Cube::CreateCube(){
    CreatingTextures();
    glGenVertexArrays(1, &VAO);
    glGenBuffers(3, VBO);
    glGenBuffers(1, &EBO);
    glBindVertexArray(VAO);
    //Used to bind the Vertex Buffer Object
    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Final part to tell the shader how to read this data
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(aNormal), aNormal, GL_STATIC_DRAW);

    // Final part to tell the shader how to read this data
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, VBO[2]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(textures), textures, GL_STATIC_DRAW);

    // Final part to tell the shader how to read this data
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2*sizeof(float), (void*)0);
    glEnableVertexAttribArray(2);

    //Used to bind the Element Buffer object buffer
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
}

void ll_CubeNamespace::LL_Cube::Draw(){
    glBindVertexArray(VAO);
    //glDrawArrays(GL_TRIANGLES, 0, 36);
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void ll_CubeNamespace::LL_Cube::ModelViewProjection(CameraNamespace::Camera camera, ShaderNamespace::Shader shader,glm::vec3 scale){
        ////////////////////////////////////////////////////////////////////////////////////////
    //TRANSLATION ROTATION AND SCALING
    model = glm::mat4(1.0f);    
    model = glm::translate(model, glm::vec3(points.x, points.y, points.z));
    model = glm::rotate(model, glm::radians(angle), glm::vec3(rotation.x, rotation.y, rotation.z));
    model = glm::scale(model, scale);
    // model = glm::rotate(model, glm::radians(rotation.angle), 
    //                 glm::vec3(rotation.axis.x, rotation.axis.y, rotation.axis.z));
    ////////////////////////////////////////////////////////////////////////////////////////
    //VIEW
    view = camera.ModifyViewMatrix();
    ////////////////////////////////////////////////////////////////////////////////////////
    //PROJECTION
    projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
    ////////////////////////////////////////////////////////////////////////////////////////
    shader.use();
    int modelLoc = glGetUniformLocation(shader.ID, "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

    int viewLoc = glGetUniformLocation(shader.ID, "view");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

    int projectionLoc = glGetUniformLocation(shader.ID, "projection");
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

    // int objectColor = glGetUniformLocation(shader.ID, "objectColor");
    // glUniform3fv(objectColor, 1, glm::value_ptr(glm::vec3(1.0f, 0.5f, 0.31f)));

    // int material_ambient = glGetUniformLocation(shader.ID, "material.ambient");
    // glUniform3fv(material_ambient, 1, glm::value_ptr(glm::vec3(1.0f, 0.5f, 0.31f)));
    
    // int material_diffuse = glGetUniformLocation(shader.ID, "material.diffuse");
    // glUniform3fv(material_diffuse, 1, glm::value_ptr(glm::vec3(1.0f, 0.5f, 0.31f)));
    
    int material_diffuse = glGetUniformLocation(shader.ID, "material.diffuse");
    glUniform1i(material_diffuse, 0);
    
    // int material_specular = glGetUniformLocation(shader.ID, "material.specular");
    // glUniform3fv(material_specular, 1, glm::value_ptr(glm::vec3(0.5f, 0.5f, 0.5f)));
    int material_specular = glGetUniformLocation(shader.ID, "material.specular");
    glUniform1i(material_specular, 1);
    int material_shininess = glGetUniformLocation(shader.ID, "material.shininess");
    glUniform1f(material_shininess, 32.0f);
    
    glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f);
    // lightColor.x = sin(glfwGetTime() * 2.0f);
    // lightColor.y = sin(glfwGetTime() * 0.7f);
    // lightColor.z = sin(glfwGetTime() * 1.3f);
    
    glm::vec3 diffuseColor = lightColor   * glm::vec3(0.5f); 
    glm::vec3 ambientColor = diffuseColor * glm::vec3(0.2f); 

    int light_ambient = glGetUniformLocation(shader.ID, "light.ambient");
    glUniform3fv(light_ambient, 1, glm::value_ptr(ambientColor));
    
    int light_diffuse = glGetUniformLocation(shader.ID, "light.diffuse");
    glUniform3fv(light_diffuse, 1, glm::value_ptr(diffuseColor));
    
    int light_specular = glGetUniformLocation(shader.ID, "light.specular");
    glUniform3fv(light_specular, 1, glm::value_ptr(glm::vec3(1.0f, 1.0f, 1.0f)));

    // int lightColor = glGetUniformLocation(shader.ID, "lightColor");
    // glUniform3fv(lightColor, 1, glm::value_ptr(glm::vec3(1.0f, 1.0f, 1.0f)));
}

void ll_CubeNamespace::LL_Cube::SetPosition(float x, float y, float z){
    points.x = x;
    points.y = y;
    points.z = z;
}

void ll_CubeNamespace::LL_Cube::SetRotation(float angle, float x_axis, float y_axis, float z_axis){
    angle = angle;
    rotation.x = x_axis;
    rotation.y = y_axis;
    rotation.z = z_axis;
}

void ll_CubeNamespace::LL_Cube::CreatingTextures(){
    for(uint16_t i=0; i< 48; i+=8){
        textures[i] = 1.0f;
        textures[i+1] = 1.0f;
        textures[i+2] = 1.0f;
        textures[i+3] = 0.0f;
        textures[i+4] = 0.0f;
        textures[i+5] = 0.0f;
        textures[i+6] = 0.0f;
        textures[i+7] = 1.0f;  
    }
}