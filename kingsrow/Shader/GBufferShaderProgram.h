#pragma once

#include "..\Shader\ShaderProgram.h"

class GBufferShaderProgram : public ShaderProgram
{
public:
	GBufferShaderProgram(GLuint shaderProgramID);
	~GBufferShaderProgram();

	virtual void loadUniformLocations();
	virtual void fillUniformLocation(Framebuffer* framebuffer);
	virtual void fillUniformLocation(MeshNode* node, std::vector<LightNode*> lights);

private:

	void bindTextures(MeshNode* node);

	GLuint locationModel;
	GLuint locationView;
	GLuint locationProjection;
	GLuint locationDiffuseTexture;
	GLuint locationSpecularTexture;
};

