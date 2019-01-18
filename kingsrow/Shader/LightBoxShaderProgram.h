#pragma once
#include "..\Shader\ShaderProgram.h"
class LightBoxShaderProgram : public ShaderProgram
{
public:
	LightBoxShaderProgram(GLuint shaderProgramID);
	~LightBoxShaderProgram();

	virtual void loadUniformLocations();
	virtual void fillUniformLocation(Framebuffer* framebuffer);
	virtual void fillUniformLocation(MeshNode* node, std::vector<LightNode*> lights);

private:

	void bindTextures(MeshNode* node);

	GLuint locationModel;
	GLuint locationView;
	GLuint locationProjection;
	GLuint locationLightColor;
};

