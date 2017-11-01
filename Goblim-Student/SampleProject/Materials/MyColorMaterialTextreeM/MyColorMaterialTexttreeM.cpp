#include "MyColorMaterialTexttreeM.h"
#include "Engine/Base/Node.h"
#include "Engine/Base/Scene.h"


MyColorMaterialTexttreeM::MyColorMaterialTexttreeM(std::string name, glm::vec4 & c) :
	MaterialGL(name,"MyColorMaterialTexttreeM")
{
	text = new GPUTexture2D("./Textures/Leaves0120_35_S.png",true);
	text2 = new GPUTexture2D("./Textures/Bunny2.png", true);
	textn = new GPUTexture2D("./Textures/leaf_nrm3.png", true);

	modelViewProj = vp->uniforms()->getGPUmat4("MVP");
	poscam = fp->uniforms()->getGPUvec3("poscam");
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
MyColorMaterialTexttreeM::~MyColorMaterialTexttreeM()
{
}
void MyColorMaterialTexttreeM::setCam(glm::vec3  c) {
	poscam->Set(c);
}
void MyColorMaterialTexttreeM::setColor(glm::vec4 & c)
{
	color->Set(c);
}

void MyColorMaterialTexttreeM::render(Node *o)
{
	if (m_ProgramPipeline)
	{		
		m_ProgramPipeline->bind();
		o->drawGeometry(GL_TRIANGLES);
		m_ProgramPipeline->release();
	}
}

void MyColorMaterialTexttreeM::update(Node* o,const int elapsedTime)
{
	//t+=0.1;
	//temps->Set(t);
	modelViewProj->Set(o->frame()->getTransformMatrix());
	
}