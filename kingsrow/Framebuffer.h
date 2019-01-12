#pragma once

#include <glad/glad.h>

#include <GLFW/glfw3.h>
#include <glm\glm.hpp>

class Framebuffer
{
public:
	Framebuffer(int width, int height);
	~Framebuffer();

	unsigned int getGBuffer() { return gBuffer; }
	unsigned int getPosition() { return gPosition; }
	unsigned int getNormal() { return gNormal; }
	unsigned int getAlbedoSpec() { return gAlbedoSpec; }
	unsigned int getDepth() { return rboDepth; }

	void renderGeometryPass();
	void renderLightingPass();

private:

	

	unsigned int gBuffer;
	unsigned int gPosition, gNormal, gAlbedoSpec;
	unsigned int rboDepth;
};

