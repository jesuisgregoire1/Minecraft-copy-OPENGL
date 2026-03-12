#include "cube.hpp"

void CubeNamespace::Cube::CreateCube(){
    //Used to bind the Vertex Array Object                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                      
    // point = new PointNamespace::Point();
    // coordSystem = new CoordSystem::CoordSystem();
    obb.SetPointers();
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
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void CubeNamespace::Cube::CreatingTextures(){
    uint8_t counter = 0;
    std :: cout << "posX_first = " << posX_first << std::endl;
    std :: cout << "posX_second = " << posX_second << std::endl;
    std :: cout << "posX_third = " << posX_third << std::endl;
    std :: cout << "posY = " << posY << std::endl;
    // 368.0f, 80.0f, 96.0f, 112.0f
    // 368.0f, 80.0f, 64.0f, 48.0f
    if(initialized){
        uint16_t posX_per_face[6] = {
            posX_third, posX_third,
            posX_third, posX_third,    
            posX_first, posX_second
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
    else{
        std :: cout << "The cube is not initialized with the texture Data" << std :: endl;
    }
}

void CubeNamespace::Cube::SetModel(){

}

void CubeNamespace::Cube::SetPosition(float x, float y, float z){
    point.x = x;
    point.y = y;
    point.z = z;
    // std :: cout << "x1=" << point.x << "||" << "y1=" << point.y << "||" << "z1=" << point.z << std :: endl;
    boundingBox.max = glm::vec3(0.0f);
    boundingBox.min = glm::vec3(0.0f);
    boundingBox.max = glm::vec3(0.5f, 0.5f, 0.5f)+ glm::vec3(point.x, point.y, point.z);
    boundingBox.min = glm::vec3(-0.5f,-0.5f,-0.5f)+ glm::vec3(point.x, point.y, point.z);
    obb.center = glm::vec3(point.x, point.y, point.z);
}

void CubeNamespace::Cube::SetRotation(float angle, float x_axis, float y_axis, float z_axis){
    rotation.angle = angle;
    rotation.axis.x = x_axis;
    rotation.axis.y = y_axis;
    rotation.axis.z = z_axis;
    glm::mat3 rot = glm::mat3(glm::rotate(glm::mat4(1.0f), angle, glm::vec3(x_axis,y_axis,z_axis)));
    obb.axis[0] = rot[0];
    obb.axis[1] = rot[1];
    obb.axis[2] = rot[2];
}

void CubeNamespace::Cube::SetMVP(CameraNamespace::Camera camera){
    ////////////////////////////////////////////////////////////////////////////////////////
    //TRANSLATION ROTATION AND SCALING
    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(point.x, point.y, point.z));
    model = glm::rotate(model, glm::radians(rotation.angle), glm::vec3(rotation.axis.x, rotation.axis.y, rotation.axis.z));
    // model = glm::rotate(model, glm::radians(rotation.angle), 
    //                 glm::vec3(rotation.axis.x, rotation.axis.y, rotation.axis.z));
    ////////////////////////////////////////////////////////////////////////////////////////
    //VIEW
    view = camera.ModifyViewMatrix();
    ////////////////////////////////////////////////////////////////////////////////////////
    //PROJECTION
    projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
    ////////////////////////////////////////////////////////////////////////////////////////
    //Bounding BOX
    boundingBox.SetMVP(camera, glm::vec3(point.x, point.y, point.z), rotation.angle, rotation.axis);
}

void CubeNamespace::Cube::MVP(CameraNamespace::Camera camera, ShaderNamespace::Shader shader){
    shader.use();
    int modelLoc = glGetUniformLocation(shader.ID, "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

    int viewLoc = glGetUniformLocation(shader.ID, "view");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

    int projectionLoc = glGetUniformLocation(shader.ID, "projection");
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
}

void CubeNamespace::Cube::SetCoordSystem(CameraNamespace::Camera camera, ShaderNamespace::Shader shader){
    coordSystem.SetModel(glm::vec3(1.0f,1.0f,1.0f),
                   glm::vec3(point.x, point.y, point.z), 
                   glm::radians(rotation.angle), glm::vec3(rotation.axis.x, rotation.axis.y, rotation.axis.z));
    coordSystem.SetView(camera);
    coordSystem.SetProjection();
    coordSystem.SetMVP(shader);
}

CubeNamespace::Cube::Cube(float posY, float posX_first, float posX_second, float posX_third){
    this->posY = posY;
    this->posX_first = posX_first;
    this->posX_second = posX_second;
    this->posX_third = posX_third;
    initialized=true;
}

void BoundingBox::BoundingBox::CreateBoundingBoxPoints(){
    //Here we want to create the bounding box for a cube
    vertices[0] = max; // top-left-front
    vertices[1] = glm::vec3(min.x, max.y, max.z); // top-right-front
    vertices[2] = glm::vec3(min.x, min.y, max.z); // bottom-right-front
    vertices[3] = glm::vec3(max.x, min.y, max.z); // bottom-left-front
    vertices[4] = glm::vec3(max.x, max.y, min.z); // top-left-back
    vertices[5] = glm::vec3(min.x, max.y, min.z); // top-right-back
    vertices[6] = min;                            // bottom-right-back
    vertices[7] = glm::vec3(max.x, min.y, min.z); // bottom-left-back
}

void BoundingBox::BoundingBox::CreateBoundingBoxColor(){
    for(uint8_t i=0 ; i<8; ++i){
        colors[i] = glm::vec3(0.0f, 1.0f, 0.0f);
    }
    // //Here we want to create the bounding box for a cube
    // colors[0] = glm::vec3(1.0f, 0.0f, 0.0f); // top-left-front
    // colors[1] = glm::vec3(1.0f, 0.0f, 0.0f); // top-right-front
    // colors[2] = glm::vec3(1.0f, 0.0f, 0.0f); // bottom-right-front
    // colors[3] = glm::vec3(1.0f, 0.0f, 0.0f); // bottom-left-front
    // colors[4] = glm::vec3(1.0f, 0.0f, 0.0f); // top-left-back
    // colors[5] = glm::vec3(1.0f, 0.0f, 0.0f); // top-right-back
    // colors[6] = glm::vec3(1.0f, 0.0f, 0.0f); // bottom-right-back
    // colors[7] = glm::vec3(1.0f, 0.0f, 0.0f); // bottom-left-back
}
void BoundingBox::BoundingBox::ChangeColor(){
    // for(uint8_t i=0 ; i<8; ++i){
    //     // colors[i] = glm::vec3(0.0f, 1.0f, 0.0f);
    //     // std :: cout << "colors[i] = " << i << " " << colors[i].x <<" "<< colors[i].y <<" "<< colors[i].z << std :: endl; 
    // }
    if(!isColliding){
        for(uint8_t i=0 ; i<8; ++i){
            colors[i] = glm::vec3(1.0f, 0.0f, 0.0f);
        }
    }else{
        for(uint8_t i=0 ; i<8; ++i){
            colors[i] = glm::vec3(0.0f, 1.0f, 0.0f);
        }
    }
    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(colors), colors);
}
BoundingBox::BoundingBox::BoundingBox(){
    CreateBoundingBoxPoints();
    CreateBoundingBoxColor();
    
    glGenVertexArrays(1, VAO);
    glGenBuffers(2, VBO);
    glGenBuffers(1, EBO);
    glBindVertexArray(*VAO);
    ////////////////////////////////////////////////////////////////////////////////////////
    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    ////////////////////////////////////////////////////////////////////////////////////////
    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    ////////////////////////////////////////////////////////////////////////////////////////
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
}

void BoundingBox::BoundingBox::Draw(){
    glBindVertexArray(*VAO);
    glLineWidth(1.5f);
    glDrawElements(GL_LINES, 24, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void BoundingBox::BoundingBox::SetMVP(CameraNamespace::Camera camera,
                                    glm::vec3 position,
                                    float angle, glm::vec3 rotation, 
                                    glm::vec3 scale){
    ////////////////////////////////////////////////////////////////////////////////////////
    //TRANSLATION ROTATION AND SCALING
    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(position.x, position.y, position.z));
    model = glm::rotate(model, glm::radians(angle), glm::vec3(rotation.x, rotation.y, rotation.z));
    model = glm::scale(model, glm::vec3(scale.x, scale.y, scale.z));

    ////////////////////////////////////////////////////////////////////////////////////////
    //VIEW
    view = camera.ModifyViewMatrix();
    ////////////////////////////////////////////////////////////////////////////////////////
    //PROJECTION
    projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
    ////////////////////////////////////////////////////////////////////////////////////////
}
void BoundingBox::BoundingBox::MVP(CameraNamespace::Camera camera, ShaderNamespace::Shader shader){
    shader.use();
    int modelLoc = glGetUniformLocation(shader.ID, "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

    int viewLoc = glGetUniformLocation(shader.ID, "view");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

    int projectionLoc = glGetUniformLocation(shader.ID, "projection");
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
}

///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
////////////////////////OBJECT ORIENTED BOX////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
ObjectBoundingBox::ObjectBoundingBox::ObjectBoundingBox(){}

ObjectBoundingBox::ObjectBoundingBox::~ObjectBoundingBox(){}

void ObjectBoundingBox::ObjectBoundingBox::SetPointers(){
    axis[0] = glm::vec3(1.0f, 0.0f, 0.0f);
    axis[1] = glm::vec3(0.0f, 1.0f, 0.0f);
    axis[2] = glm::vec3(0.0f, 0.0f, 1.0f);
}
