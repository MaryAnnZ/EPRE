#include "LightBoxShaderProgram.h"



LightBoxShaderProgram::LightBoxShaderProgram(GLuint shaderProgramID) : ShaderProgram(shaderProgramID)
{
}


LightBoxShaderProgram::~LightBoxShaderProgram()
{
}


void LightBoxShaderProgram::loadUniformLocations()
{
	locationModel = glGetUniformLocation(programId, "model");
	locationView = glGetUniformLocation(programId, "view");
	locationProjection = glGetUniformLocation(programId, "projection");
	locationLightColor = glGetUniformLocation(programId, "lightColor");
}

void LightBoxShaderProgram::fillUniformLocation(Framebuffer * framebuffer)
{
}

void LightBoxShaderProgram::fillUniformLocation(MeshNode * node, std::vector<LightNode*> lights)
{
	glm::mat4 M = node->getModelMatrix();
	glUniformMatrix4fv(locationModel, 1, GL_FALSE, &M[0][0]);
	glm::mat4 V = node->getViewMatrix();
	glUniformMatrix4fv(locationView, 1, GL_FALSE, &V[0][0]);
	glm::mat4 P = node->getProjectionMatrix();
	glUniformMatrix4fv(locationProjection, 1, GL_FALSE, &P[0][0]);
	glm::vec3 color = node->getLightColor();
	glUniform3f(locationLightColor, color.x, color.y, color.z);
}

void LightBoxShaderProgram::bindTextures(MeshNode * node)
{
}

