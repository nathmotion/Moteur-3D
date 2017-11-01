#include "MyColorMaterialCWater.h"
#include "Engine/Base/Node.h"
#include "Engine/Base/Scene.h"


MyColorMaterialCWater::MyColorMaterialCWater(std::string name, glm::vec4 & c) :
	MaterialGL(name,"MyColorMaterialCWater")
{
	text = new GPUTexture2D("./Textures/fond-bleu.jpg",true);
	text2 = new GPUTexture2D("./Textures/noise.png", true);
	text3= new GPUTexture2D("./Textures/irra2.jpg", true);
	text4 = new GPUTexture2D("./Textures/skyt.png", true);


	textn2 = new GPUTexture2D("./Textures/water_n1.jpg", true);
	textn = new GPUTexture2D("./Textures/water_n2.jpg", true);

	modelViewProj = vp->uniforms()->getGPUmat4("MVP");
	temps = vp->uniforms()->getGPUfloat("temps");
	color = fp->uniforms()->getGPUvec4("CPU_color");
	poscam = fp->uniforms()->getGPUvec3("PosCam");
	samplerText = fp->uniforms()->getGPUsampler("samplerText");
	samplerText2 = fp->uniforms()->getGPUsampler("samplerText2");
	samplerText3 = fp->uniforms()->getGPUsampler("samplerText3");
	samplerText4 = fp->uniforms()->getGPUsampler("samplerText4");

	samplerTextn2 = fp->uniforms()->getGPUsampler("samplerTextn2");
	samplerTextn = fp->uniforms()->getGPUsampler("samplerTextn");

	samplerText->Set(text->getHandle());
	samplerText2->Set(text2->getHandle());
	samplerText3->Set(text3->getHandle());
	samplerText4->Set(text4->getHandle());

	samplerTextn2->Set(textn2->getHandle());
	samplerTextn->Set(textn->getHandle());
	color->Set(c);

}
MyColorMaterialCWater::~MyColorMaterialCWater()
{

}

void MyColorMaterialCWater::setCam(glm::vec3 & pos) {
	poscam->Set(pos);
}
void MyColorMaterialCWater::setColor(glm::vec4 & c)
{
	color->Set(c);
}

void MyColorMaterialCWater::render(Node *o)
{
	if (m_ProgramPipeline)
	{		
		m_ProgramPipeline->bind();
		o->drawGeometry(GL_TRIANGLES);
		m_ProgramPipeline->release();
	}
}

void MyColorMaterialCWater::update(Node* o,const int elapsedTime)
{
	t+=elapsedTime;
	temps->Set(t);
	modelViewProj->Set(o->frame()->getTransformMatrix());
	
}