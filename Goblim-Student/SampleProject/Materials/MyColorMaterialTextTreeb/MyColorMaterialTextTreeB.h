#ifndef _COLORMATERIALTEXTTREEB_H
#define _COLORMATERIALTEXTTREEB_H


#include "Engine/OpenGL/MaterialGL.h"
#include "Engine/OpenGL/Lighting/LightingModelGL.h"
#include <memory.h>

class MyColorMaterialTextTreeB : public MaterialGL
{
	public:
		MyColorMaterialTextTreeB(std::string name,glm::vec4 & c = glm::vec4(0.5,0.5,0.5,1.0));
		~MyColorMaterialTextTreeB();
		void setColor(glm::vec4 & c);
		void setCam(glm::vec3 c);
		virtual void render(Node *o);
		virtual void update(Node* o,const int elapsedTime);
		

	private:
		GPUvec4* color;
		GPUmat4* modelViewProj;
		GPUfloat* temps; 
		GPUTexture2D* text;
		GPUsampler* samplerText;
		GPUTexture2D* text2;
		GPUsampler* samplerText2;
		GPUTexture2D* textn;
		GPUsampler* samplerTextn;
		GPUvec3* poscam;
		float t;
};

#endif