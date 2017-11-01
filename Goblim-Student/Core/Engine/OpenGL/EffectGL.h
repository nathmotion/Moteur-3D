#ifndef _EFFECTGL_
#define _EFFECTGL_

#include "Engine/Base/Effect.h"
#include "Engine/OpenGL/v4/GLProgramPipeline.h"
#include "GPUResources/FBO/GPUFBO.h"
#include "Engine/OpenGL/ModelGL.h"
#include <AntTweakBar/AntTweakBar.h>


class EffectGL : public Effect
{
	public :
		EffectGL(string name,string className);
		~EffectGL();

		//virtual void apply();
		virtual void apply(GPUFBO *fbo=NULL);

		virtual void createControlBar();

	protected :
		void drawQuad();
		GLProgramPipeline* m_ProgramPipeline;
		ModelGL *quad;
		TwBar* controlBar;
};

#endif
