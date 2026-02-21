#version 330 core
out vec4 FragColor;
in vec2 TexCoord;
uniform sampler2D ourTexture;
uniform bool useDebugColor;
uniform vec3 debugColor;
void main(){
    if (useDebugColor){
        FragColor = vec4(debugColor, 1.0f);
    }
    else{
        FragColor = texture(ourTexture, TexCoord);
    }
}