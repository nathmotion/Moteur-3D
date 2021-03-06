#ifndef _COLORMATERIALTEXTFOUNTAIN_H
#define _COLORMATERIALTEXTFOUNTAIN_H


#include "Engine/OpenGL/MaterialGL.h"
#include "Engine/OpenGL/Lighting/LightingModelGL.h"
#include <memory.h>

class MyColorMaterialTextfountain : public MaterialGL
{
	public:
		MyColorMaterialTextfountain(std::string name,glm::vec4 & c = glm::vec4(0.5,0.5,0.5,1.0));
		~MyColorMaterialTextfountain();
		void setColor(glm::vec4 & c);
		void setCam(glm::vec3 pos);
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