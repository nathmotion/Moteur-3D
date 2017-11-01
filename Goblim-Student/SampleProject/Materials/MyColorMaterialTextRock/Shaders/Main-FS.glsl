#version 430
#extension GL_ARB_shading_language_include : enable
#extension GL_ARB_bindless_texture : enable
#include "/Materials/Common/Common"
#line 6 
//uniform sampler2D samplerText;

layout(std140) uniform CPU
{	
	vec4 CPU_color;
	sampler2D samplerText;
	sampler2D samplerText2;
	sampler2D samplerTextn;
	vec3 poscam;
};



layout (location = 0) out vec4 Color;

//in vec4 gl_FragCoord;

in vec3 v_Color;
in vec3 pos;
in vec3 N;
in vec3 texcoord;
//in int t;

void main()
{
	///					  ** T E X T U R  E  **
	vec4 col = texture(samplerText, 2.0*texcoord.xy);
	vec4 col2 = texture(samplerText2, texcoord.xy);
	vec4 colmix =col;
	
	
	//	L2= normalize(Light_pos2-V);

	//R2 =normalize( reflect(-L2,Normalmap));

	//Color=normalize(vec4(v_Color,1.0)*vec4(gl_FragCoord.xyz/0.1,0.0));
	//Color = vec4(texcoord, 1.0); teste de la position des texture recupere

	vec3 Normale=normalize(N);
	
	//				**  N O R M A L  M A P P I N G **
	vec3 Normalmap = ((texture(samplerTextn, texcoord.xy).xyz) * 2) - 1;
		
	//				**    P H O N G **

	vec3 Light_pos2 = vec3(-10.0, -20.0, 0.0);
	vec3 Light_pos = vec3(10.0, 200.0, 0.0);
	vec3 Cam_pos = vec3(10.5, 20.0, 0.0);
	vec3 V = normalize(pos - poscam);
	vec3 diffuse;
	vec3 ambiante;
	vec3 specular;
	
	vec3 L;
	vec3 L2;
	vec3 R2;
	vec3 R;
	vec3 E;
	Light_pos.xy=(Light_pos.xy);

	L = normalize(Light_pos.xyz -V);
	R =  normalize(reflect(-L,Normalmap));

	diffuse= (colmix.xyz*max(dot(Normalmap,L),0.0));
	ambiante=colmix.xyz;
	specular=colmix.xyz*pow(max(dot(R,normalize(V)),0.0),32);
	Color=vec4(ambiante*0.2+diffuse*0.8+specular*0.8,1.0);
	//Color = vec4(texcoord, 1.0);
}