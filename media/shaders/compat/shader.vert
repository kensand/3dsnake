#version 130
//precision mediump float;
//layout( location = 0 )
in vec4 vPosition;
//layout( location = 1 )
in vec4 vColor;
out vec4 Color;
uniform mat4 ModelViewProjectionMatrix;

void main(){
    gl_Position = ModelViewProjectionMatrix * vPosition;
    Color = vColor;
}
