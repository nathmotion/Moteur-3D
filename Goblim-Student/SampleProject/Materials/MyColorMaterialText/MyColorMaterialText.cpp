#include "MyColorMaterialText.h"
#include "Engine/Base/Node.h"
#include "Engine/Base/Scene.h"


MyColorMaterialText::MyColorMaterialText(std::string name, glm::vec4 & c) :
	MaterialGL(name,"MyColorMaterialText")
{
	text = new GPUTexture2D("./Textures/Bunny1.png",true);
	text2 = new GPUTexture2D("./Textures/Bunny2.png", true);
	textn = new GPUTexture2D("./Textures/Bunny_nm.jpg", true);

	modelViewProj = vp->uniforms()->getGPUmat4("MVP");
	//temps = vp->uniforms()->getGPUfloat("temps");
	color = fp->uniforms()->getGPUvec4("CPU_color");
	samplerText = fp->uniforms()->getGPUsampler("samplerText");
	samplerText2 = fp->uniforms()->getGPUsampler("samplerText2");
	samplerTextn = fp->uniforms()->getGPUsampler("samplerTextn");

	samplerText->Set(text->getHandle());
	samplerText2->Set(text2->getHandle());
	samplerTextn->Set(textn->getHandle());
	color->Set(c);

}
MyColorMaterialText::~MyColorMaterialText()
{

}

void MyColorMaterialText::setColor(glm::vec4 & c)
{
	color->Set(c);
}

void MyColorMaterialText::render(Node *o)
{
	if (m_ProgramPipeline)
	{		
		m_ProgramPipeline->bind();
		o->drawGeometry(GL_TRIANGLES);
		m_ProgramPipeline->release();
	}
}

void MyColorMaterialText::update(Node* o,const int elapsedTime)
{
	//t+=0.1;
	//temps->Set(t);
	modelViewProj->Set(o->frame()->getTransformMatrix());
	
}