/*
EngineGL overloaded for custom rendering
*/
#include "SampleEngine.h"
#include "Engine/OpenGL/v4/GLProgram.h"
#include "Engine/OpenGL/SceneLoaderGL.h"
#include "Engine/Base/NodeCollectors/MeshNodeCollector.h"
#include "Engine/Base/NodeCollectors/FCCollector.h"

#include <Math.h>
#include <AntTweakBar/AntTweakBar.h>

#include "Materials/MyColorMaterial/MyColorMaterial.h"
#include "Materials/MyColorMaterialText/MyColorMaterialText.h"
#include "Materials/MyColorMaterialPWater/MyColorMaterialPWater.h"
#include "Materials/MyColorMaterialCWater/MyColorMaterialCWater.h"
#include "Materials/MyColorMaterialTextRock/MyColorMaterialTextRock.h"
#include "Materials/MyColorMaterialTextStone/MyColorMaterialTextStone.h"
#include "Materials/MyColorMaterialTextTreeb/MyColorMaterialTextTreeB.h"
#include "Materials/MyColorMaterialTextreeM/MyColorMaterialTexttreeM.h"
#include "Materials/MyColorMaterialTextfountain/MyColorMaterialTextfountain.h"
#include "Materials/MyColorMaterialTextSkye/MyColorMaterialTextSkye.h"
#include "Materials/MyColorMaterialTextIle/MyColorMaterialTextIle.h"
#include "Materials/MyColorMaterialTextGrass/MyColorMaterialTextGrass.h"

#include "Effects\Reflet\Reflet.h"
#include "GPUResources/GPUInfo.h"
#define PI 3.14
SampleEngine::SampleEngine (int width, int height) :
EngineGL (width, height)
{
	
}

SampleEngine::~SampleEngine ()
{
}



bool SampleEngine::init ()
{

	//postProcess = new GPUFBO("PostProcess");
	//postProcess->create(FBO_WIDTH, FBO_HEIGHT, 1, true, GL_RGBA32F, GL_TEXTURE_2D, 1); //FBO_WIDTH, FBO_HEIGHT, GL_RGBA32F et GL_TEXTURE_2D sont déjà déclarés)

	LOG (INFO) << "Initializing Scene";
	timeQuery->create ();

	LOG(INFO) << GPUInfo::Instance()->getOpenGLVersion() << std::endl;

	// Load shaders in "\common" into graphic cards
	GLProgram::prgMgr.addPath (ressourceMaterialPath + "Common", "");

	// Create Lighting Model GL and collect all light nodes of the scene 
	lightingModel = new LightingModelGL("LightingModel", scene->getRoot());
	// Bind the light buffer for rendering
	lightingModel->bind();

	// ***						S K Y B O X
	//Node* skye = scene->getNode("sky");
	//skye->setModel(scene->m_Models.get<ModelGL>(ressourceObjPath +"cube2.obj"));
	//glm::vec3 posCam = scene->camera()->convertPtTo(glm::vec3(0.0), scene->getNode("sky")->frame());
	//glm::vec3 posCam = scene->camera()->convertPtTo(glm::vec3(0.0), scene->getNode("sky")->frame());
	//skye->setMaterial(new MyColorMaterialTextSkye("MyColorMaterielTextSkye", glm::vec4(0.2, 0.8, 0.5, 1.0)));
	//scene->getSceneNode()->adopt(skye);
	//skye->frame()->scale(glm::vec3(1000.0));
	/**

	Dans Core/GPUResources/Textures/GPUTexture2D.cpp dans la première méthode create(),
	j'ai remplacé 10 par 1 glTexStorage2D(m_Target, 10, internalformat, width, height)
	pronfondeur 

	glEnable(GL_DEPTH_TEST);
	*/
	Node* fond = scene->getNode("fond");
	fond->setModel(scene->m_Models.get<ModelGL>(ressourceObjPath + "cube2.obj"));
	//glm::vec3 posCam = scene->camera()->convertPtTo(glm::vec3(0.0), scene->getNode("sky")->frame());
	glm::vec3 posCam = scene->camera()->convertPtTo(glm::vec3(0.0), scene->getNode("fond")->frame());
	fond->setMaterial(new MyColorMaterialTextSkye("MyColorMaterielTextSkye", glm::vec4(0.2, 0.8, 0.5, 1.0)));
	scene->getSceneNode()->adopt(fond);
	fond->frame()->scale(glm::vec3(20.0, 1.0, 20.0));
	fond->frame()->translate(glm::vec3(0.0, -5.0, 0.0));


	// ***							  O B J E T   S C E N E         ***

	Node* rock = scene->getNode("rock");
	rock->setModel(scene->m_Models.get<ModelGL>(ressourceObjPath + "Rock1.obj"));
	posCam = scene->camera()->convertPtTo(glm::vec3(0.0), scene->getNode("rock")->frame());
	rock->setMaterial(new MyColorMaterialTextRock("MyColorMaterialTextRock", glm::vec4(0.2, 0.5, 0.8, 1.0)));
	(dynamic_cast<MyColorMaterialTextRock*>(scene->getNode("rock")->getMaterial())->setCam(posCam));
	scene->getSceneNode()->adopt(rock);
	rock->frame()->scale(glm::vec3(1.5));
	rock->frame()->rotate(glm::vec3(0.0, 0.0, 1.0),PI/7);
	rock->frame()->rotate(glm::vec3(0.0, 0.5, 0.0), -PI /9);
	rock->frame()->rotate(glm::vec3(1.0, 0.0, 0.0), -PI / 9);
	rock->frame()->translate(glm::vec3(5.0, -3.0, -1.5));


	Node* grass = scene->getNode("grass");
	grass->setModel(scene->m_Models.get<ModelGL>(ressourceObjPath + "Grass_01.obj"));
	posCam = scene->camera()->convertPtTo(glm::vec3(0.0), scene->getNode("grass")->frame());
	grass->setMaterial(new MyColorMaterialTextGrass("MyColorMaterialTextGrass", glm::vec4(0.2, 0.5, 0.8, 1.0)));
	(dynamic_cast<MyColorMaterialTextGrass*>(scene->getNode("grass")->getMaterial())->setCam(posCam));
	scene->getSceneNode()->adopt(grass);
	
	grass->frame()->translate(glm::vec3(6.5, -0.6,3.5));
	grass->frame()->rotate(glm::vec3(0.2, -0.8, 1.9), PI / 8);

	Node* grass2 = scene->getNode("grass2");
	grass2->setModel(scene->m_Models.get<ModelGL>(ressourceObjPath + "Grass_02.obj"));
	posCam = scene->camera()->convertPtTo(glm::vec3(0.0), scene->getNode("grass2")->frame());
	grass2->setMaterial(new MyColorMaterialTextGrass("MyColorMaterialTextGrass", glm::vec4(0.2, 0.5, 0.8, 1.0)));
	(dynamic_cast<MyColorMaterialTextGrass*>(scene->getNode("grass2")->getMaterial())->setCam(posCam));
	scene->getSceneNode()->adopt(grass2);
	grass2->frame()->scale(glm::vec3(0.9));

	grass2->frame()->translate(glm::vec3(10.0, -0.8, 7.5));

	Node* tree = scene->getNode("tree");
	tree->setModel(scene->m_Models.get<ModelGL>(ressourceObjPath + "treeb.obj"));
	posCam = scene->camera()->convertPtTo(glm::vec3(0.0), scene->getNode("tree")->frame());
	tree->setMaterial(new MyColorMaterialTextTreeB("MyColorMaterialTextTreeB", glm::vec4(0.2, 0.5, 0.8, 1.0)));
	(dynamic_cast<MyColorMaterialTextTreeB*>(scene->getNode("tree")->getMaterial())->setCam(posCam));
	scene->getSceneNode()->adopt(tree);
	tree->frame()->scale(glm::vec3(0.9));
	tree->frame()->translate(glm::vec3(10.0, -0.8, 7.5));


	/**Node* mesh = scene->getNode("mesh");
	mesh->setModel(scene->m_Models.get<ModelGL>(ressourceObjPath + "treem.obj"));
	posCam = scene->camera()->convertPtTo(glm::vec3(0.0), scene->getNode("mesh")->frame());
	mesh->setMaterial(new MyColorMaterialTexttreeM("MyColorMaterialTexttreeM", glm::vec4(0.2, 0.5, 0.8, 1.0)));
	(dynamic_cast<MyColorMaterialTexttreeM*>(scene->getNode("mesh")->getMaterial())->setCam(posCam));
	scene->getSceneNode()->adopt(mesh);
	mesh->frame()->scale(glm::vec3(0.9));
	mesh->frame()->translate(glm::vec3(10.0, -0.8, 7.5));
	*/

	Node* stone = scene->getNode("stone");
	stone->setModel(scene->m_Models.get<ModelGL>(ressourceObjPath + "stone_2.obj"));
	posCam = scene->camera()->convertPtTo(glm::vec3(0.0), scene->getNode("stone")->frame());
	stone->setMaterial(new MyColorMaterialTextIle("MyColorMaterialTextIle", glm::vec4(0.2, 0.5, 0.8, 1.0)));
	(dynamic_cast<MyColorMaterialTextIle*>(scene->getNode("stone")->getMaterial())->setCam(posCam));
	scene->getSceneNode()->adopt(stone);
	stone->frame()->rotate(glm::vec3(0.0, 0.0, 1.0), 2*PI/2);
	stone->frame()->scale(glm::vec3(1.5));
	stone->frame()->translate(glm::vec3(-5.0,0.5,3.0));


	Node* fountain = scene->getNode("fountain");
	fountain->setModel(scene->m_Models.get<ModelGL>(ressourceObjPath + "fountain.obj"));
	posCam = scene->camera()->convertPtTo(glm::vec3(0.0), scene->getNode("fountain")->frame());

	fountain->setMaterial(new MyColorMaterialTextfountain("MyColorMaterialTextfountain", glm::vec4(0.2, 0.5, 0.8, 1.0)));
	(dynamic_cast<MyColorMaterialTextfountain*>(scene->getNode("fountain")->getMaterial())->setCam(posCam));

	scene->getSceneNode()->adopt(fountain);
	fountain->frame()->scale(glm::vec3(0.002));
	fountain->frame()->translate(glm::vec3(4050.0, 0.0, 2950.0));


	//***						   E A U

	Node* water = scene->getNode("Mywater");
	water->setModel(scene->m_Models.get<ModelGL>(ressourceObjPath + "plan2.obj"));
	posCam = scene->camera()->convertPtTo(glm::vec3(0.0), scene->getNode("Mywater")->frame());
	water->setMaterial(new MyColorMaterialCWater("MyColorMaterialCWater",glm::vec4(0.2, 0.5, 0.8, 1.0)));
	(dynamic_cast<MyColorMaterialCWater*>(scene->getNode("Mywater")->getMaterial())->setCam(posCam));
	scene->getSceneNode()->adopt(water);
	water->frame()->scale(glm::vec3(10.0, 1.0, 10.0));
	water->frame()->translate(glm::vec3(0.0,-2.0,0.0));
	water->frame()->rotate(glm::vec3(0.0, 1.0,0.0),  PI);

	
	Node* plane = scene->getNode("MyPlane");
	 posCam = scene->camera()->convertPtTo(glm::vec3(0.0), scene->getNode("MyPlane")->frame());

	plane->setModel(scene->m_Models.get<ModelGL>(ressourceObjPath + "plan2.obj"));
	//bunny->setMaterial(new MyColorMaterial("ColorMaterial",glm::vec4(0.2,0.5,0.8,1.0)));
	plane->setMaterial(new MyColorMaterialPWater("MyColorMaterialPWater",glm::vec4(0.2,0.5,0.8,1.0)));
	(dynamic_cast<MyColorMaterialPWater*>(scene->getNode("MyPlane")->getMaterial())->setCam(posCam));
	scene->getSceneNode()->adopt(plane);
	plane->frame()->scale(glm::vec3(0.7));
	plane->frame()->translate(glm::vec3(11.6, 2.1, 8.4));

	// Create Bounding Box Material for bounding box rendering
	boundingBoxMat = new BoundingBoxMaterial ("BoundingBoxMat");

	// OpenGL state variable initialisation
	glClearColor (0.4, 0.4, 0.4, 1.0);
	glEnable (GL_DEPTH_TEST);

	
	// Force window Resize
	this->onWindowResize (w_Width, w_Height);

	allNodes->collect (scene->getRoot());

	renderedNodes->collect (scene->getRoot ());

	for (unsigned int i = 0; i < allNodes->nodes.size (); i++)
		allNodes->nodes[i]->animate (0);

	return(true);
}


void SampleEngine::render ()
{
	
	// Begin Time query
	timeQuery->begin ();
	//GPUFBO* monFbo = new GPUFBO("fFBO");
	
	glClearColor(1.0, 1.0, 1.0, 1.0);
	//postProcess->enable(); //on active le GPUFBO
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//postProcess->bindColorTexture(0); //on lie le fbo à une texture
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	////Rendering every collected node
	for (unsigned int i = 0; i < renderedNodes->nodes.size (); i++)
		renderedNodes->nodes[i]->render();
	//monEffet->apply(postProcess); //on appel la fonction de l'effet que l'on souhaite affiche et lui faisant passer en paramètre le fbo
	//postProcess->getColorTexture(0)->release(); //on libère la texture	
	if (drawLights)
		lightingModel->renderLights();

	if (drawBoundingBoxes)
		for (unsigned int i = 0; i < renderedNodes->nodes.size(); i++)
			renderedNodes->nodes[i]->render(boundingBoxMat);
	//postProcess->disable(); //on désactive le GPUFBO
	//postProcess->display(); //on affiche ce qu'il a récupéré
	// end time Query					
	timeQuery->end ();


	scene->needupdate = false;

}
void SampleEngine::animate (const int elapsedTime)
{
	
	// Animate each node
	for (unsigned int i = 0; i < allNodes->nodes.size (); i++)
		allNodes->nodes[i]->animate (elapsedTime);

}

void SampleEngine::onWindowResize (int width, int height)
{

	glViewport (0, 0, width, height);
	scene->camera ()->setAspectRatio ((float)width / (float)height);
	w_Width = width;
	w_Height = height;


}



