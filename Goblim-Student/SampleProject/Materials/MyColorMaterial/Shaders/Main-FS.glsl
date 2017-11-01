#version 430

uniform sampler2D samplerText;

layout(std140) uniform CPU
{
	vec4 CPU_color;


};



layout(location = 0) out vec4 Color;

//in vec4 gl_FragCoord;

in vec3 v_Color;
in vec3 pos;
in vec3 N;
in vec3 texcoord;
in int t;

void main()
{
	vec4 col = texture(samplerText, texcoord.xy);
	vec3 p_Color = v_Color;
	vec3 Light_pos2 = vec3(-10.0, -20.0, 0.0);
	vec3 Light_pos = vec3(10.0, 20.0, 0.0);
	vec3 Cam_pos = vec3(10.5, 20.0, 0.0);
	vec3 V = normalize(pos - Cam_pos);
	//Color=normalize(vec4(v_Color,1.0)*vec4(gl_FragCoord.xyz/0.1,0.0));
	vec3 Normale = normalize(N);
	vec3 diffuse;
	vec3 ambiante;
	vec3 specular;
	p_Color =col.xyz;
	vec3 L;
	vec3 R;
	vec3 E;
	Light_pos.xy = (Light_pos.xy*t);
	L2 = normalize(Light_pos2 - V);
	L = normalize(Light_pos - V);
	R = reflect(L, N);
	R2 = reflect(L2, N);
	E = normalize(-Cam_pos);
	diffuse = (p_Color.xyz*max(dot(N, L), 0.0));
	ambiante = p_Color.xyz;
	specular = p_Color.xyz*pow(max(dot(R, normalize(V)), 0.0), 20);
	Color = vec4(ambiante*0.4 + diffuse*0.2 + specular*0.8, 1.0);

	Color =vec4( texcoord,1.0);
}