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
out float t;
out vec3 v_Color;

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
		 *A* cos(theta *frenquence  + time * phase) ( sur les axe x et y )
		 **/
		 float A = 0.01;
		 vec2 direction = vec2(-1.0, 0.0);
		 vec2 direction2 = vec2(0.5, 0.8);
		 float S = 10;
		 float L = 5;
		 float frequence = 2 * M_PI / L;
		 float phase = 2 * S;
		 float  theta = dot(vec2(-1.0, 0.0), vec2(5, 5));
		 float k = A * direction.y*frequence;
		 
		 //



		 // modification en fonction du temps
		
		 // **						vague sinuaosidale ***

		//float wave =  amplitude * cos/sin (frequence *(vec2) direction * position + vitesse * temps ) ;
		vec3 wave = vec3( A*sin((temps/ 800)+pos.x*2)*Normal);
		pos += wave;
		// vec3 tmp = 0.002*sin((temps / 800) + pos.x * 3)*Normal;
		 N = normalize(N +wave);
		 offset = wave.x+temps/10000;

			

		 // modification en fonction de la postion des vertex
	/*	if(Position.y>0.0 && Position.y<0.2){
			///pos.x=pos.x+0.2;
			v_Color=vec3(0.5,0.5,0.5);
			
		}
		else{
			v_Color=vec3(0.5,0.5,0.5);
		}*/

		texcoord = Texture;
		//t=temps;
		
		gl_Position= MVP * vec4(pos,1.0);

}
