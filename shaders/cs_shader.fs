#version 330 core
out vec4 FragColor;
in vec3 f_color;
uniform bool useDebugColor;
uniform vec3 debugColor;

void main(){
    if (useDebugColor){
        FragColor = vec4(f_color, 1.0f);
    }
}