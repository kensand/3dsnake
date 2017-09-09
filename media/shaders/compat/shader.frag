#version 130
precision mediump float;
in vec4 Color;

out vec4 fColor;

uniform vec4 Ambient;

void main()
{
	gl_FragColor = vec4(0.4,0.4,0.8,1.0);
}