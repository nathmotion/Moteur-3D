#version 430


layout(std140) uniform CPU
{	
	vec4 CPU_color;
};



layout (location = 0) out vec4 Color;

void main()
{
	Color = CPU_color;
}