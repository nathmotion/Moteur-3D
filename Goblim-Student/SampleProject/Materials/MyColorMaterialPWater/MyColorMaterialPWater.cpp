#include "MyColorMaterialPWater.h"
#include "Engine/Base/Node.h"
#include "Engine/Base/Scene.h"


MyColorMaterialPWater::MyColorMaterialPWater(std::string name,glm::vec4 & c) :
	MaterialGL(name,"MyColorMaterialPWater")
{

	text = new GPUTexture2D("./Textures/fond-bleu.jpg",true);
	text2 = new GPUTexture2D("./Textures/water_n1.jpg", true);
	textn = new GPUTexture2D("./Textures/water_n4.png", true);

	modelViewProj = vp->uniforms()->getGPUmat4("MVP");
	temps = vp->uniforms()->getGPUfloat("temps");
	color = fp->uniforms()->getGPUvec4("CPU_color");
	poscam = fp->uniforms()->getGPUvec3("PosCam");

	samplerText = fp->uniforms()->getGPUsampler("samplerText");
	samplerText2 = fp->uniforms()->getGPUsampler("samplerText2");
	samplerTextn = fp->uniforms()->getGPUsampler("samplerTextn");

	samplerText->Set(text->getHandle());
	samplerText2->Set(text2->getHandle());
	samplerTextn->Set(textn->getHandle());
	color->Set(c);

}
MyColorMaterialPWater::~MyColorMaterialPWater()
{

}
void MyColorMaterialPWater::setCam(glm::vec3 pos) {
	poscam->Set(pos);
}
void MyColorMaterialPWater::setColor(glm::vec4 & c)
{
	color->Set(c);
}

void MyColorMaterialPWater::render(Node *o)
{
	if (m_ProgramPipeline)
	{		
		m_ProgramPipeline->bind();
		o->drawGeometry(GL_TRIANGLES);
		m_ProgramPipeline->release();
	}
}

void MyColorMaterialPWater::update(Node* o,const int elapsedTime)
{
	t+=elapsedTime;
	temps->Set(t);
	modelViewProj->Set(o->frame()->getTransformMatrix());
	
}