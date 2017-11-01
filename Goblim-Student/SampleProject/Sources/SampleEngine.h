/*
 *	(c) XLim, UMR-CNRS
 *	Authors: G.Gilet
 *
 */

#ifndef _SAMPLE_ENGINE_H
#define _SAMPLE_ENGINE_H

#include <map>
#include <string>
#include "Engine/OpenGL/EngineGL.h"
#include "Materials/BoundingBoxMaterial/BoundingBoxMaterial.h"

#include "Materials/MyColorMaterial/MyColorMaterial.h"

class SampleEngine : public EngineGL
{
	public:
		SampleEngine(int width, int height);
		~SampleEngine();

		virtual bool init();
		virtual void render();
		virtual void animate(const int elapsedTime);
		virtual void onWindowResize(int width, int height);



protected:
	GPUFBO *postProcess;
		

};
#endif
