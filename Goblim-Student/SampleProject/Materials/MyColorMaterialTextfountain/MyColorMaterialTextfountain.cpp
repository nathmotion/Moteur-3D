#include "MyColorMaterialTextfountain.h"
#include "Engine/Base/Node.h"
#include "Engine/Base/Scene.h"


MyColorMaterialTextfountain::MyColorMaterialTextfountain(std::string name, glm::vec4 & c) :
	MaterialGL(name,"MyColorMaterialTextfountain")
{
	text = new GPUTexture2D("./Textures/Brick_D.png",true);
	text2 = new GPUTexture2D("./Textures/Bunny2.png", true);
	textn = new GPUTexture2D("./Textures/Brick_N.png", true);

	modelViewProj = vp->uniforms()->getGPUmat4("MVP");
	//temps = vp->uniforms()->getGPUfloat("temps");
	color = fp->uniforms()->getGPUvec4("CPU_color");
	poscam = fp->uniforms()->getGPUvec3("poscam");

	samplerText = fp->uniforms()->getGPUsampler("samplerText");
	samplerText2 = fp->uniforms()->getGPUsampler("samplerText2");
	samplerTextn = fp->uniforms()->getGPUsampler("samplerTextn");

	samplerText->Set(text->getHandle());
	samplerText2->Set(text2->getHandle());
	samplerTextn->Set(textn->getHandle());
	color->Set(c);

}
MyColorMaterialTextfountain::~MyColorMaterialTextfountain()
{

}
void MyColorMaterialTextfountain::setCam(glm::vec3 pos) {
	poscam->Set(pos);
}
void MyColorMaterialTextfountain::setColor(glm::vec4 & c)
{
	color->Set(c);
}

void MyColorMaterialTextfountain::render(Node *o)
{
	if (m_ProgramPipeline)
	{		
		m_ProgramPipeline->bind();
		o->drawGeometry(GL_TRIANGLES);
		m_ProgramPipeline->release();
	}
}

void MyColorMaterialTextfountain::update(Node* o,const int elapsedTime)
{
	//t+=0.1;
	//temps->Set(t);
	modelViewProj->Set(o->frame()->getTransformMatrix());
	
}