//********************************** Banshee Engine (www.banshee3d.com) **************************************************//
//**************** Copyright (c) 2016 Marko Pintera (marko.pintera@gmail.com). All rights reserved. **********************//
#include "BsGLSupport.h"
#include "BsGLTexture.h"
#include "GL/glew.h"

GLenum glewContextInit(bs::ct::GLSupport* glSupport);

namespace bs { namespace ct
{
	void GLSupport::initializeExtensions()
	{
		glewContextInit(this);
		BS_CHECK_GL_ERROR();

		// Set version string
		const GLubyte* pcVer = glGetString(GL_VERSION);
		assert(pcVer && "Problems getting GL version string using glGetString");

		String tmpStr = (const char*)pcVer;
		mVersion = tmpStr.substr(0, tmpStr.find(" "));

		// Get vendor
		const GLubyte* pcVendor = glGetString(GL_VENDOR);
		tmpStr = (const char*)pcVendor;
		mVendor = tmpStr.substr(0, tmpStr.find(" "));

		// Set extension list
		INT32 numExtensions = 0;
		glGetIntegerv(GL_NUM_EXTENSIONS, &numExtensions);
		BS_CHECK_GL_ERROR();

		for (INT32 i = 0; i < numExtensions; i++)
			extensionList.insert(String((char*)glGetStringi(GL_EXTENSIONS, i)));
	}

	bool GLSupport::checkExtension(const String& ext) const
	{
		if(extensionList.find(ext) == extensionList.end())
			return false;

		return true;
	}
}}