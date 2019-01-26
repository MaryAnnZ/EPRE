#pragma once

#include "..\Shader\ShaderProgram.h"
#include "..\Texture\Texture.h"

class SimpleLightingShaderProgram : public ShaderProgram
{
public:
	SimpleLightingShaderProgram(GLuint shaderProgramID);
	~SimpleLightingShaderProgram();

	virtual void loadUniformLocations();
	virtual void fillUniformLocation(MeshNode* node, std::vector<LightNode*> lights);
	virtual void fillUniformLocation(Framebuffer* framebuffer);

private:
	GLuint locationMVP;
	GLuint locationV;
	GLuint locationM;
	GLuint locationTexture;
	GLuint locationLight;
	GLuint locationCamPos;
	
	void useLights(std::vector<LightNode*> lights);
	void bindTextures(MeshNode* node);
};

