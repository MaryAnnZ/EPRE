#include "MeshNode.h"
#include "../Shader/ShaderProgram.h"
#include "../Framebuffer.h"


#pragma once
class Quad :
	public MeshNode
{
public:
	Quad(int id);
	~Quad();

	void prepareForRendering();
	void draw(glm::vec3 playerPosition, Framebuffer* framebuffer);


};

