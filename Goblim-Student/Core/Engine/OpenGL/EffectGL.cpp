#include "Engine/OpenGL/EffectGL.h"
#include "Engine/Base/Scene.h"

EffectGL::EffectGL(string name,string className):
	Effect(name,className),m_ProgramPipeline(NULL)
{

	controlBar = NULL;
	GLProgram::prgMgr.addPath(ressourceEffectPath + this->m_ClassName,this->m_ClassName);
	m_ProgramPipeline = new GLProgramPipeline(this->m_ClassName);
	quad = Scene::getInstance()->getModel<ModelGL>(ressourceObjPath+"Quad.obj");
}
EffectGL::~EffectGL()
{
	Scene::getInstance()->releaseModel(quad);
	if (m_ProgramPipeline != NULL)
		delete m_ProgramPipeline;


	if (controlBar != NULL)
		delete controlBar;
}
void EffectGL::apply(GPUFBO *fbo)
{
	
}
void EffectGL::drawQuad()
{
	m_ProgramPipeline->bind();
	quad->drawGeometry(GL_TRIANGLES);
	m_ProgramPipeline->release();
}
void EffectGL::createControlBar()
{

}