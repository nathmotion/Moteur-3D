#version 430

#extension GL_ARB_shading_language_include : enable
#extension GL_ARB_bindless_texture : enable
#include "/Materials/Common/Common"
#line 6 


layout(std140) uniform CPU
{
	mat4 MVP;
int temps;
};

layout(location = 0) in vec3 Position;
layout(location = 2) in vec3 Normal;
layout(location = 4) in vec3 Texture;


out gl_PerVertex{
	vec4 gl_Position;
float gl_PointSize;
float gl_ClipDistance[];
};




out vec3 v_Color;


out vec3 N;
out vec3 pos;
out int t;
out vec3 texcoord;
/*


*/
void main()
{

	N = Normal;

	pos = Position;

	// modification en fonction du temps




	if (Position.y>0.0 && Position.y<0.2) {
		///pos.x=pos.x+0.2;
		v_Color = vec3(0.5, 0.5, 0.5);

	}
	else {
		v_Color = vec3(0.5, 0.5, 0.5);
	}

	texcoord = Texture;
	t = temps;

	gl_Position = MVP * vec4(pos, 1.0);

}
