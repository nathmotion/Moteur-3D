#include <sstream>
#include "GPUFBO.h"
#include "Engine/Base/Engine.h"
#include "Engine/OpenGL/MaterialGL.h"
#include "Effects/DisplayResource/DisplayResource.h"
#include "Effects/DisplayLayer/DisplayLayer.h"
#include "GPUResources/Textures/GPUTexture2D.h"
#include "Utils/GLError.h"

#include "GPUResources/GPUInfo.h"

#include <cmath>

static GLenum buffers[8] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2, GL_COLOR_ATTACHMENT3, GL_COLOR_ATTACHMENT4, GL_COLOR_ATTACHMENT5, GL_COLOR_ATTACHMENT6, GL_COLOR_ATTACHMENT7 };


std::string toStr(int a)
{
	std::ostringstream oss;
	oss << a;
	return(oss.str());
}



GPUFBO::GPUFBO(std::string name):
	Resource(name)
{
	width = 0;
	height = 0;
	depthBuffer = NULL;
	initialized = false;
	layer_bound = 0;
	oldFB = 0;
	scene = Scene::getInstance();
	HUD = new DisplayResource("HUD FBO");
	HUDArray = new DisplayLayer("HUD ARRAY FBO");


}


GPUFBO::~GPUFBO()
{
	delete HUD;

	destroy();
}


int GPUFBO::getWidth()
{
	return width;
}
int GPUFBO::getHeight()
{
	return height;
}
bool GPUFBO::isInitialized()
{
	return initialized;
}

void GPUFBO::destroy()
{
	for (unsigned int i =0;i < colorBuffers.size();i++)
		delete colorBuffers[i];
	if (use_depth)
		delete depthBuffer;
	glDeleteFramebuffers(1,&FBOId);

}

bool GPUFBO::create(int w,int h,int numberOfTarget,bool useDepth,GLint format,GLint typeOfTarget,int layerDepth)
{

	width = w;
	height = h;
	use_depth = useDepth;

	m_Target = typeOfTarget;
	glGenFramebuffers(1,&FBOId);

	bufferIsBound = new bool[numberOfTarget];
	glBindFramebuffer(GL_FRAMEBUFFER,FBOId);
	for(int i=0;i<numberOfTarget;i++)
	{		
		switch (typeOfTarget)
		{
		case GL_TEXTURE_3D :
		case GL_TEXTURE_2D_ARRAY :
			colorBuffers.push_back(new GPUTexture2DArray(m_Name+"ColoRArray"+toStr(i),width,height,layerDepth,format));
			//glFramebufferTextureLayer(GL_FRAMEBUFFER, buffers[i], colorBuffers[i]->getId(),0, 0);
			for (int k = 0; k < layerDepth; k++)
				glFramebufferTextureLayer(GL_FRAMEBUFFER, buffers[k], colorBuffers[0]->getId(), 0, k);
			
			// modif perso -- texture de depth buffer personnalis� sur le dernier buffer --- NOTE : fait planter ma HD 7950 ...
			//colorBuffers.push_back(new GPUTexture2D(m_Name + "Color" + toStr(i+1), width, height, format));
			//glFramebufferTexture2D(GL_FRAMEBUFFER, buffers[6], GL_TEXTURE_2D, colorBuffers[i+1]->getId(), 0);
			
			
			break;

		case GL_TEXTURE_2D :
			colorBuffers.push_back(new GPUTexture2D(m_Name+"Color"+toStr(i),width,height,format));
			glFramebufferTexture2D(GL_FRAMEBUFFER,buffers[i],typeOfTarget,colorBuffers[i]->getId(),0);
			
			break;

		default:
			LOG(WARNING)  << this->name() + " Error : unrecognized type of target " << endl;
			return false;
			break;
		}

		bufferIsBound[i] = false;

	}

	
	if (use_depth)
	{
		depthBuffer = new GPUTexture2D(m_Name + "-Depth", width, height, GL_DEPTH_COMPONENT24, GL_DEPTH_COMPONENT, GL_UNSIGNED_INT);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthBuffer->getId(), 0);
	}
	glBindFramebuffer(GL_FRAMEBUFFER, 0);    //  unbind

	initialized = CheckFramebufferStatus();
	return(initialized);

}
bool  GPUFBO::CheckFramebufferStatus()
{
	GLenum status;
	status = (GLenum) glCheckFramebufferStatus(GL_FRAMEBUFFER);
	bool evryok = false;
	switch(status) {
	case GL_FRAMEBUFFER_COMPLETE:
		evryok = true;
		break;
	case GL_FRAMEBUFFER_UNSUPPORTED:
		info_text += "Unsupported framebuffer format\n";
		break;
	case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:
		info_text += "Framebuffer incomplete, missing attachment\n";
		break;
	case GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS_EXT:
		info_text += "Framebuffer incomplete, attached images must have same dimensions\n";
		break;
	case GL_FRAMEBUFFER_INCOMPLETE_FORMATS_EXT:
		info_text += "Framebuffer incomplete, attached images must have same format\n";
		break;
	case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER_EXT:
		info_text += "Framebuffer incomplete, missing draw buffer\n";
		break;
	case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER_EXT:
		info_text += "Framebuffer incomplete, missing read buffer\n";
		break;
	default:
		info_text += "Unknown Framebuffer Error";
	}
	return(evryok);
}

void GPUFBO::drawBuffer(int i)
{
		glDrawBuffer(buffers[i]);
}
void  GPUFBO::drawBuffers(int i)
{
	glDrawBuffers(i,buffers);
}

void GPUFBO::enable()
{
	glGetIntegerv(GL_FRAMEBUFFER_BINDING,&oldFB);
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	glViewport(0, 0,  width,  height);
	glBindFramebuffer(GL_FRAMEBUFFER, FBOId);
}

void GPUFBO::enable(int layer,int attachment)
{

	glGetIntegerv(GL_FRAMEBUFFER_BINDING,&oldFB);
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	glViewport(0, 0,  width,  height);
	glBindFramebuffer (GL_FRAMEBUFFER, FBOId);
	switch (m_Target)
	{
		case GL_TEXTURE_2D_ARRAY:
			glFramebufferTextureLayer(GL_FRAMEBUFFER, buffers[attachment], colorBuffers[0]->getId(), 0, layer);
			break;

		case GL_TEXTURE_2D:
		default:
			glFramebufferTexture2D(GL_FRAMEBUFFER, buffers[attachment], m_Target, colorBuffers[layer]->getId(), 0);
	}

	if (use_depth) glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, m_Target, depthBuffer->getId(), 0);
	
}

void GPUFBO::bindLayerToBuffer(int layer, int buffer){
	switch (m_Target)
	{
		case GL_TEXTURE_2D_ARRAY:
			glFramebufferTextureLayer(GL_FRAMEBUFFER, buffers[buffer], colorBuffers[0]->getId(), 0, layer);
			break;

		case GL_TEXTURE_2D:
		default:
			glFramebufferTexture2D(GL_FRAMEBUFFER, buffers[buffer], m_Target, colorBuffers[layer]->getId(), 0);
	}
	
}


void GPUFBO::disable()
{
	// rebind old framebuffer
	glBindFramebuffer (GL_FRAMEBUFFER, oldFB);
	// restore attributes
	glPopAttrib();
}
void GPUFBO::display(const glm::vec4 & box,int layer)
{
	if(m_Target == GL_TEXTURE_2D)
	{
		colorBuffers[layer]->bind();
		HUD->isUIntDepth->Set(0);
		HUD->display(box);
		colorBuffers[layer]->release();
	}
	else
	{
		colorBuffers[0]->bind();
		HUDArray->display(box,layer);
		colorBuffers[0]->release();
	}

}


void GPUFBO::displayDepth(const glm::vec4 & box)
{
	depthBuffer->bind();
	HUD->isUIntDepth->Set(1);
	HUD->display(box);
	depthBuffer->release();

}
GPUTexture* GPUFBO::getColorTexture(int i)
{
	return colorBuffers[i];
}

GPUTexture* GPUFBO::getDepthTexture()
{
	return depthBuffer;
}

void GPUFBO::bindColorTexture(int channel,int layer )
{
	if (layer < (int)colorBuffers.size())
	{
		colorBuffers[layer]->bind(channel);
		layer_bound = layer;
		bufferIsBound[layer] = true;
	}
}

void GPUFBO::releaseColorTexture()
{
//	colorBuffers[layer_bound]->release();
	for(int i = 0 ; i < (int) colorBuffers.size() ; i++)
	{
		if (bufferIsBound[i]) colorBuffers[i]->release();
	}

}

void GPUFBO::bindDepthTexture(int channel )
{
	depthBuffer->bind(channel);

}
void GPUFBO::releaseDepthTexture()
{
	depthBuffer->release();

}
void GPUFBO::setDepthBuffer(GPUTexture* de)
{
	depthBuffer = de;
	glBindFramebuffer(GL_FRAMEBUFFER,FBOId);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthBuffer->getId(), 0);
	glBindFramebuffer(GL_FRAMEBUFFER,0);
}


void GPUFBO::switchToTexture2DArray()
{
	// TODO : � partir du tableau de texture, remplacer
	
}

GLuint GPUFBO::getFBOid()
{
	return FBOId;
}

