/*
EngineGL overloaded for custom rendering
*/
#include "DeferredEngineGL.h"
#include "Engine/OpenGL/v4/GLProgram.h"
#include "Engine/OpenGL/SceneLoaderGL.h"
#include "Engine/Base/NodeCollectors/MeshNodeCollector.h"
#include "Engine/Base/NodeCollectors/FCCollector.h"


#include <AntTweakBar/AntTweakBar.h>

#include "GPUResources/Textures/GPUTextureCubeMap.h"

#include "Materials/ColorMaterial/ColorMaterial.h"

#include "GPUResources/GPUInfo.h"
//#include "Effects/DepthCopy/DepthCopy.h"



DeferredEngineGL::DeferredEngineGL (int width, int height) :
EngineGL (width, height)
{
	
	GeometryPassFBO = NULL;
	PostProcessFBO = NULL;
	

}

DeferredEngineGL::~DeferredEngineGL ()
{
}


bool DeferredEngineGL::init ()
{
	LOG (INFO) << "Initializing Scene";
	timeQuery->create ();

	LOG(INFO) << GPUInfo::Instance()->getOpenGLVersion() << std::endl;

	// Load shaders in "\common" into graphic cards
	GLProgram::prgMgr.addPath (ressourceMaterialPath + "Common", "");

	GeometryPassFBO = new GPUFBO("Geometry Pass");
	GeometryPassFBO->create(FBO_WIDTH, FBO_HEIGHT, 1, true, GL_RGB16F, GL_TEXTURE_2D_ARRAY, 7);


	


	// Create Lighting Model GL and collect all light nodes of the scene 
	lightingModel = new LightingModelGL("LightingModel", scene->getRoot());
	// Bind the light buffer for rendering
	lightingModel->bind();

	// Create Bounding Box Material for bounding box rendering
	boundingBoxMat = new BoundingBoxMaterial ("BoundingBoxMat");

	// OpenGL state variable initialisation
	glClearColor (0.0, 0.0, 0.0, 1.0);
	glEnable (GL_DEPTH_TEST);



	// Force window Resize
	this->onWindowResize (w_Width, w_Height);
	allNodes->collect (scene->getRoot ());
	renderedNodes->collect (scene->getRoot ());


	for (unsigned int i = 0; i < allNodes->nodes.size (); i++)
		allNodes->nodes[i]->animate (0);

	return(true);
}

void DeferredEngineGL::deferredRender()
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// -- Deferred rendering pass
		GeometryPassFBO->enable();

			glDepthMask (GL_TRUE);
			glClearColor (0.0, 0.0, 0.0, 1.0);
			glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glEnable (GL_DEPTH_TEST);
			//
			GeometryPassFBO->drawBuffers(6);
			//
			////Rendering every collected node
			for (unsigned int i = 0; i < renderedNodes->nodes.size (); i++)
				renderedNodes->nodes[i]->render();
		
			glDisable (GL_DEPTH_TEST);
			glDepthMask (GL_FALSE);
		GeometryPassFBO->disable();



}
void DeferredEngineGL::render ()
{

	
	// Begin Time query
	timeQuery->begin ();
	
	deferredRender();
	
		
		//// Display
		//PP->apply(GeometryPassFBO, PostProcessFBO); // Application du PostProcess

		GeometryPassFBO->display (); // Affichage du FBO contenant l'image finale
			


		if (drawLights)
			lightingModel->renderLights();

		if (drawBoundingBoxes)
			for (unsigned int i = 0; i < renderedNodes->nodes.size(); i++)
				renderedNodes->nodes[i]->render(boundingBoxMat);

	// end time Query					
	timeQuery->end ();


	scene->needupdate = false;

}
float teta = 0.0f;
void DeferredEngineGL::animate (const int elapsedTime)
{
	
	// Animate each node
	for (unsigned int i = 0; i < allNodes->nodes.size (); i++)
		allNodes->nodes[i]->animate (elapsedTime);


	// force update of lighting model
	lightingModel->update (true);

}

void DeferredEngineGL::onWindowResize (int width, int height)
{

	glViewport (0, 0, width, height);
	scene->camera ()->setAspectRatio ((float)width / (float)height);
	w_Width = width;
	w_Height = height;

	if (lightingModel != NULL)
		lightingModel->setWindowSize (glm::vec2 (width, height));

}



