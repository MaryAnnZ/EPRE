#pragma once


#include "MeshNode.h"
#include "../Shader/ShaderProgram.h"
#include "../Framebuffer.h"

class LightBox : public MeshNode
{
public:
	LightBox(int id, glm::vec3 color);
	~LightBox();

	void prepareForRendering();
	void draw(glm::mat4 viewMatrix, glm::mat4 projectionMatrix);

};

