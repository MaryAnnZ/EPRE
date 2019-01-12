#include "Quad.h"
#include "../Render/Renderer.h"
#include "../Importers/ShaderImporter.h"



Quad::Quad(int id) : MeshNode(id)
{
}


Quad::~Quad()
{
}

void Quad::prepareForRendering()
{
	float quadVertices[] = {
		// positions        // texture Coords
		-1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
		-1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
		1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
		1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
	};

	Renderer* renderer = Renderer::getInstance();
	renderer->generateVertexArray(&vao);
	renderer->generateBufferObject(&vertexBuffer);


	renderer->bindVertexArray(vao);
	renderer->fillBuffer(vertexBuffer, GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
	
	renderer->setVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	renderer->setVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	
	/**/
	shaderProgram = ShaderImporter::getInstance()->loadShaderProgram(MeshLoadInfo::DEFERRED_SHADER);
	shaderProgram->loadUniformLocations();
	/**/

	renderer->bindVertexArray(0);
	renderer->bindBuffer(GL_ARRAY_BUFFER, 0);
	renderer->bindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}

void Quad::draw(glm::vec3 playerPosition, Framebuffer * framebuffer)
{
	this->playerPosition = playerPosition;
	Renderer::getInstance()->draw(this, framebuffer);
}
