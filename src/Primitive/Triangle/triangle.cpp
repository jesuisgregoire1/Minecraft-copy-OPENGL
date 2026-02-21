#include "triangle.hpp"

void TriangleNamespace::Triangle::CreateTriangle(){
    //Used to bind the Vertex Array Object
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

    
    // Final part to tell the shader how to read this data
    
}
void TriangleNamespace::Triangle::Draw(){
    glBindVertexArray(VAO);
    // glDrawArrays(GL_TRIANGLES, 0, 3);
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}