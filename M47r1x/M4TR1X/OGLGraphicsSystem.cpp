#include "OGLGraphicsSystem.h"
#include "Window.h"
#include "Shader.h"
#include "Texture2D.h"
#include <initializer_list>

namespace Engine
{
	OGLGraphicsSystem::OGLGraphicsSystem(Window* window)
		: GraphicsSystem()
		, m_window(window)
		, isActive(false)
	{

		// Here specify the attributes of the desired configuration.
		// Below, we select an EGLConfig with at least 8 bits per color
		// component compatible with on-screen windows
		const EGLint attribs[] = {
			EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
			EGL_BLUE_SIZE, 8,
			EGL_GREEN_SIZE, 8,
			EGL_RED_SIZE, 8,
			EGL_ALPHA_SIZE, 8,
			EGL_DEPTH_SIZE, 16,
			EGL_NONE
		};
		EGLint w, h, format;
		EGLint numConfigs;
		EGLConfig config;
		m_eglDisplay = eglGetDisplay(EGL_DEFAULT_DISPLAY);

		eglInitialize(m_eglDisplay, 0, 0);

		// Here, the application chooses the configuration it desires.
		// find the best match if possible, otherwise use the very first one
		eglChooseConfig(m_eglDisplay, attribs, nullptr, 0, &numConfigs);
		EGLConfig* supportedConfigs = new EGLConfig[numConfigs];
		//assert(supportedConfigs);
		eglChooseConfig(m_eglDisplay, attribs, supportedConfigs, numConfigs, &numConfigs);
		//assert(numConfigs);
		int i = 0;
		for (; i < numConfigs; i++) {
			EGLConfig& cfg = supportedConfigs[i];
			EGLint r, g, b, d;
			if (eglGetConfigAttrib(m_eglDisplay, cfg, EGL_RED_SIZE, &r) &&
				eglGetConfigAttrib(m_eglDisplay, cfg, EGL_GREEN_SIZE, &g) &&
				eglGetConfigAttrib(m_eglDisplay, cfg, EGL_BLUE_SIZE, &b) &&
				eglGetConfigAttrib(m_eglDisplay, cfg, EGL_DEPTH_SIZE, &d) &&
				r == 8 && g == 8 && b == 8 && d == 0) {

				config = supportedConfigs[i];
				break;
			}
		}
		if (i == numConfigs) {
			config = supportedConfigs[0];
		}

		// EGL_NATIVE_VISUAL_ID is an attribute of the EGLConfig that is
		// guaranteed to be accepted by ANativeWindow_setBuffersGeometry().
		// As soon as we picked a EGLConfig, we can safely reconfigure the
		// ANativeWindow buffers to match, using EGL_NATIVE_VISUAL_ID.
		eglGetConfigAttrib(m_eglDisplay, config, EGL_NATIVE_VISUAL_ID, &format);
		m_eglSurface = eglCreateWindowSurface(m_eglDisplay, config, window->getNativeWindow(), NULL);
		EGLint contextAttribs[] = { EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE, EGL_NONE };
		m_eglContext = eglCreateContext(m_eglDisplay, config, NULL, contextAttribs);

		if (eglMakeCurrent(m_eglDisplay, m_eglSurface, m_eglSurface, m_eglContext) == EGL_FALSE) {
			//assert(0);//LOGW("Unable to eglMakeCurrent");
		}

		// Get size of the surface
		eglQuerySurface(m_eglDisplay, m_eglSurface, EGL_WIDTH, &w);
		eglQuerySurface(m_eglDisplay, m_eglSurface, EGL_HEIGHT, &h);
		window->setSize(w, h);

		// Check openGL on the system
		auto opengl_info = { GL_VENDOR, GL_RENDERER, GL_VERSION, GL_EXTENSIONS };
		for (auto name : opengl_info) {
			auto info = glGetString(name);
			//LOGI("OpenGL Info: %s", info);
		}

		isActive = true;
	}


	OGLGraphicsSystem::~OGLGraphicsSystem()
	{
	}


	void OGLGraphicsSystem::clearScreen(float red, float green, float blue)
	{
		// Sets wiewport and clears the screen by given color.
		glViewport(0, 0, m_window->getWidth(), m_window->getHeight());
		glClearColor(red, green, blue, 0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}


	void OGLGraphicsSystem::drawTriangles(Shader* shader, float* vertices, int numvertices)
	{
		// Bind shader
		shader->useShader();

		// Set positions attribute
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, vertices);
		glEnableVertexAttribArray(0);

		// Draw vertex arrays as triangle.
		glDrawArrays(GL_TRIANGLES, 0, numvertices);
	}

	void OGLGraphicsSystem::drawTriangles(
		Shader* shader,
		float vertices[],
		float textureCoords[],
		int numvertices)
	{
		// Bind shader
		shader->useShader();

		// Positions
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, vertices);
		glEnableVertexAttribArray(0);

		// Texture coordinates
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, textureCoords);
		glEnableVertexAttribArray(1);

		// Draw vertex arrays as triangle.
		glDrawArrays(GL_TRIANGLES, 0, numvertices);
	}

	void OGLGraphicsSystem::drawTriangles(
		Shader* shader,
		Texture2D* texture,
		float vertices[],
		float textureCoords[],
		int numvertices)
	{
		// Bind shader
		shader->useShader();

		// Set positions
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, vertices);
		glEnableVertexAttribArray(0);

		// Set texture coordinates
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, textureCoords);
		glEnableVertexAttribArray(1);

		// Bind texture
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture->getTextureId());

		// Set the sampler texture unit to 0
		glUniform1i(shader->getUniformLocation("texture"), 0);

		// Draw vertex arrays as triangle.
		glDrawArrays(GL_TRIANGLES, 0, numvertices);
	}

	void OGLGraphicsSystem::swapBuffers()
	{
		eglSwapBuffers(m_eglDisplay, m_eglSurface);
	}
	
	void OGLGraphicsSystem::drawObject(Shader* shader, float* textureCoords, float vertices[], int numvertices){
		shader->useShader();
		// Set positions
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, vertices);
		glEnableVertexAttribArray(0);

		// Set texture coordinates
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, textureCoords);
		glEnableVertexAttribArray(1);
		glActiveTexture(GL_TEXTURE0);
		glDrawArrays(GL_TRIANGLES, 0, numvertices);

	}


	void OGLGraphicsSystem::drawBitmapText(char *string, float x, float y, float z, float r, float g, float b){
		char *c;
		// http://androidblog.reindustries.com/a-real-opengl-es-2-0-2d-tutorial-part-8-rendering-text/

		

	}



}