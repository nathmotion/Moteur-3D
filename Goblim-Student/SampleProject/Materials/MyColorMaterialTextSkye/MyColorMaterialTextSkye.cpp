#include "MyColorMaterialTextSkye.h"
#include "Engine/Base/Node.h"
#include "Engine/Base/Scene.h"


MyColorMaterialTextSkye::MyColorMaterialTextSkye(std::string name, glm::vec4 & c) :
	MaterialGL(name,"MyColorMaterialTextSkye")
{
	text = new GPUTexture2D("./Textures/RockS.jpg",true);
	text2 = new GPUTexture2D("./Textures/Bunny2.png", true);
	textn = new GPUTexture2D("./Textures/rock__nm3.jpg", true);

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
MyColorMaterialTextSkye::~MyColorMaterialTextSkye()
{

}
void MyColorMaterialTextSkye::setCam(glm::vec3 & c) {
	poscam->Set(c);
}
void MyColorMaterialTextSkye::setColor(glm::vec4 & c)
{
	color->Set(c);
}

void MyColorMaterialTextSkye::render(Node *o)
{
	if (m_ProgramPipeline)
	{		
		m_ProgramPipeline->bind();
		o->drawGeometry(GL_TRIANGLES);
		m_ProgramPipeline->release();
	}
}

void MyColorMaterialTextSkye::update(Node* o,const int elapsedTime)
{
	//t+=0.1;
	//temps->Set(t);
	modelViewProj->Set(o->frame()->getTransformMatrix());
	
}