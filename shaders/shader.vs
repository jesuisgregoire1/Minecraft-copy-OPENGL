#version 330 core
layout (location=0) in vec3 aPos;
layout (location=1) in vec2 aTex;
out vec2 TexCoord;
//uniform vec3 color_in;
uniform mat4 transform;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;


void main(){
    gl_Position = (projection*view*model)*vec4(aPos.x, aPos.y, aPos.z, 1.0);
    TexCoord = aTex;
    //gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
}