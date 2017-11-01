#include "MyColorMaterialTextIle.h"
#include "Engine/Base/Node.h"
#include "Engine/Base/Scene.h"


MyColorMaterialTextIle::MyColorMaterialTextIle(std::string name, glm::vec4 & c) :
	MaterialGL(name,"MyColorMaterialTextIle")
{
	text = new GPUTexture2D("./Textures/soil.jpg", true);
	text2 = new GPUTexture2D("./Textures/Bunny2.png", true);
	textn = new GPUTexture2D("./Textures/rock_nm2.jpg", true);

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
MyColorMaterialTextIle::~MyColorMaterialTextIle()
{

}
void MyColorMaterialTextIle::setCam(glm::vec3 pos) {
	poscam->Set(pos);
}
void MyColorMaterialTextIle::setColor(glm::vec4 & c)
{
	color->Set(c);
}

void MyColorMaterialTextIle::render(Node *o)
{
	if (m_ProgramPipeline)
	{		
		m_ProgramPipeline->bind();
		o->drawGeometry(GL_TRIANGLES);
		m_ProgramPipeline->release();
	}
}

void MyColorMaterialTextIle::update(Node* o,const int elapsedTime)
{
	//t+=0.1;
	//temps->Set(t);
	modelViewProj->Set(o->frame()->getTransformMatrix());
	
}