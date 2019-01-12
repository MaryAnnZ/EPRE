#pragma once

#include "..\Shader\ShaderProgram.h"

class DeferredShaderProgram : public ShaderProgram
{
public:
	DeferredShaderProgram(GLuint shaderProgramID);
	~DeferredShaderProgram();

	virtual void loadUniformLocations();
	virtual void fillUniformLocation(MeshNode* node, std::vector<LightNode*> lights);
	virtual void fillUniformLocation(Framebuffer* framebuffer);

private:

	void useLights(std::vector<LightNode*> lights);
	void bindTextures(MeshNode* node);

	GLuint locationPosition, locationNormal, locationAlbedo;
	GLuint locationViewPos;
};

