#include "MyColorMaterial.h"
#include "Engine/Base/Node.h"
#include "Engine/Base/Scene.h"


MyColorMaterial::MyColorMaterial(std::string name, glm::vec4 & c):
	MaterialGL(name,"MyColorMaterial")
{
	text = new GPUTexture2D("./Textures/Bunny1.png", true);
	modelViewProj = vp->uniforms()->getGPUmat4("MVP");
	temps = vp->uniforms()->getGPUfloat("temps");
	color = fp->uniforms()->getGPUvec4("CPU_color");
	samplerText = fp->uniforms()->getGPUsampler("samplerText");
	samplerText->Set(text->getHandle());
	color->Set(c);

}
MyColorMaterial::~MyColorMaterial()
{

}

void MyColorMaterial::setColor(glm::vec4 & c)
{
	color->Set(c);
}

void MyColorMaterial::render(Node *o)
{
	if (m_ProgramPipeline)
	{		
		m_ProgramPipeline->bind();
		o->drawGeometry(GL_TRIANGLES);
		m_ProgramPipeline->release();
	}
}

void MyColorMaterial::update(Node* o,const int elapsedTime)
{
	t += 0.5;
	temps->Set(t);
	modelViewProj->Set(o->frame()->getTransformMatrix());
	
}