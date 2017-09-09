#version 450 core
in vec4 Color;
out vec4 fColor;

uniform vec4 Ambient;

void main()
{
   
    vec4 scatteredLight = Ambient;
    fColor = Color; //min(Color * scatteredLight, vec4(1.0));
}
