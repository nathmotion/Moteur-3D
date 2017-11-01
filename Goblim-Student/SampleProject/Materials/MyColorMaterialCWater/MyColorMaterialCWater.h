#ifndef _COLORMATERIALCWATER_H
#define _COLORMATERIALCWATER_H


#include "Engine/OpenGL/MaterialGL.h"
#include "Engine/OpenGL/Lighting/LightingModelGL.h"
#include <memory.h>

class MyColorMaterialCWater: public MaterialGL
{
	public:
		MyColorMaterialCWater(std::string name, glm::vec4 & c = glm::vec4(0.5, 0.5, 0.5, 1.0));
		~MyColorMaterialCWater();
		void setColor(glm::vec4 & c);
		void setCam(glm::vec3 & c);
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
		GPUTexture2D* text3;
		GPUsampler* samplerText3;
		GPUTexture2D* text4;
		GPUsampler* samplerText4;
		GPUTexture2D* textn2;
		GPUsampler* samplerTextn2;
		GPUvec3* poscam;
		float t;
};

#endif