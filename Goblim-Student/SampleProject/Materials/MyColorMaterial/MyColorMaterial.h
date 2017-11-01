#ifndef _COLORMATERIAL_H
#define _COLORMATERIAL_H


#include "Engine/OpenGL/MaterialGL.h"
#include "Engine/OpenGL/Lighting/LightingModelGL.h"
#include <memory.h>

class MyColorMaterial : public MaterialGL
{
	public:
		MyColorMaterial(std::string name, glm::vec4 & c = glm::vec4(0.5,0.5,0.5,1.0));
		~MyColorMaterial();
		void setColor(glm::vec4 & c);

		virtual void render(Node *o);
		virtual void update(Node* o,const int elapsedTime);
		

	private:
		GPUvec4* color;
		GPUmat4* modelViewProj;
		GPUfloat* temps; 
		GPUTexture2D* text;
		GPUsampler* samplerText;
		float t = 0;
};

#endif