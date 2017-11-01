#version 430

#extension GL_ARB_shading_language_include : enable
#extension GL_ARB_bindless_texture : enable
#include "/Materials/Common/Common"
#line 6 
#define M_PI 3.1415926535897932384626433832795


layout(std140) uniform CPU
{
	mat4 MVP;
	float temps;
};

layout (location = 0) in vec3 Position;
layout (location= 2 ) in vec3 Normal;
layout (location=3) in vec3 Texture;


 out gl_PerVertex {
        vec4 gl_Position;
        float gl_PointSize;
        float gl_ClipDistance[];
    };


out vec3 texcoord;

out vec3 v_Color;
out float t;
out vec3 pos;
out vec3 N;
out float offset;

void main()
{
		
		 N= Normal;
		 t = temps;
		 pos =Position;
		 /**					G E R S T N E R   W A V E S						**/
		 /**
		 *	A = Amplitude de la vague ( float )
		 *	W= nombre de vague (vector )
		 *	D= direction (Vector)
		 *	S = Speed
		 *	L= longueur de la vague
		 * frequence= 2 *pi/L;
		 * phase = 2* s;
		 * theta =dot( direction, vec2(x,y)));
		 *
		 * amplitude * sin ( theta * frequence + temps *phase); (simple vague sinu ) 
		 *
		 *	k=amplitude  * direction.y *frequence
		 *k* cos(theta *frenquence  + time * phase) ( sur les axe x et y )
		 **/
		 float A =0.006;
		 float A2 = 0.007;
		 float A3= 0.02;
		 float A4 = 0.003;
		 vec2 direction = vec2(1,0.5);
		 vec2 direction2 = vec2(0.5,1);
		 vec2 direction3 = vec2(0.4, 0.4);
		 vec2 direction4 = vec2(0.7,1);
		 float S = 0.0006;
		 float L = 1.5;
		 float L2 = 0.5;
		 float L3 = 0.9;
		 float L4 = 1.8;
		 float frequence = 2 * M_PI / L;
		 float frequence2 = 2 * M_PI / L2;
		 float frequence3= 2 * M_PI / L3;
		 float frequence4= 2 * M_PI / L4;
		 float phase = 2 * S;
		 float  theta = dot(direction, pos.xy);
		 float theta2 = dot(direction2, pos.xy);
		 float  theta3 = dot(direction3, vec2(pos.y,pos.x));
		 float theta4 = dot(direction4, vec2(pos.y,pos.x));
		 float k = A * direction.y*frequence;
		 float k2 = A2 * direction2.y*frequence2;
		 float k3= A3* direction3.y*frequence;
		 float k4 = A4 * direction4.y*frequence2;


		 
			 float waveX2 = k2*cos(theta2*frequence2 + temps * phase);
			 offset = waveX2;
			 float waveY2 = k2*cos(theta2*frequence2 + temps *phase);
			 float waveZ2 = 1 - (k2*cos(theta2*frequence2 + temps *phase));
			 pos.x = pos.x + waveX2;
			 N.x = N.x + waveX2;
			 pos.y = pos.y + waveY2;
			 N.y = N.y + waveY2;
			 //		pos.z = pos.z + waveZ2;
		
		
			 float waveX = k* cos(theta*frequence + temps *phase);
			 float waveY = k *cos(theta*frequence + temps *phase);
			 float waveZ = 1 - (k*sin(theta*frequence + temps *phase));

			 pos.x = pos.x - waveX;
			 N.x = N.x - waveX;
			 pos.y = pos.y + waveY;
			 N.y = N.y + waveY;
			 //	pos.z = pos.z - waveZ;
			 

			 float waveX3 = k3*cos(theta3*frequence3 + temps * phase);
			 float waveY3 = k3*cos(theta3*frequence3 + temps *phase);
			 float waveZ3 = 1 - (k3*cos(theta2*frequence3 + temps *phase));
			 pos.x = pos.x - waveX3;
			 N.x = N.x - waveX3;
			 pos.y = pos.y - waveY3;
			 N.y = N.y + waveY3;
			 
		//pos.z = pos.z + waveZ3;
			
				 float waveX4 = k4* cos(theta4*frequence4 + temps *phase);
				 float waveY4 = k4*cos(theta4*frequence4 + temps *phase);
				 float waveZ4 = 1 - (k4*sin(theta*frequence4 + temps *phase));

				 pos.x = pos.x - waveX4;
				 N.x = N.x - waveX4;
				 pos.y = pos.y - waveY4;
				 N.y = N.y + waveY4;
				 
			 


		texcoord = Texture;
		//t=temps;
		
		gl_Position= MVP * vec4(pos,1.0);

}
