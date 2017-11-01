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

class DeferredEngineGL : public EngineGL
{
	public:
		DeferredEngineGL(int width, int height);
		~DeferredEngineGL();

		virtual bool init();
		virtual void render();
		virtual void animate(const int elapsedTime);
		virtual void onWindowResize(int width, int height);
		virtual void deferredRender();



protected:

			
		GPUFBO* GeometryPassFBO;
		GPUFBO* PostProcessFBO;
		//PostProcess* PP;	

};
#endif
