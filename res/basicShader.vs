#version 120

void main()
{
	gl_Position = MVP * vec4(position, 1.0);
}