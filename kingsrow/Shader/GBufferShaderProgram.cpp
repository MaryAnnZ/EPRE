#include "GBufferShaderProgram.h"


GBufferShaderProgram::GBufferShaderProgram(GLuint shaderProgramID) : ShaderProgram(shaderProgramID)
{
}

GBufferShaderProgram::~GBufferShaderProgram()
{
}

void GBufferShaderProgram::loadUniformLocations()
{
	locationModel = glGetUniformLocation(programId, "M");
	locationView = glGetUniformLocation(programId, "V");
	locationProjection = glGetUniformLocation(programId, "P");
	locationDiffuseTexture = glGetUniformLocation(programId, "myTextureSamplerDiff");
	locationSpecularTexture = glGetUniformLocation(programId, "myTextureSamplerSpec");
}

void GBufferShaderProgram::fillUniformLocation(Framebuffer * framebuffer)
{
}

void GBufferShaderProgram::fillUniformLocation(MeshNode * node, std::vector<LightNode*> lights)
{
	bindTextures(node);
	glm::mat4 M = node->getModelMatrix();
	glUniformMatrix4fv(locationModel, 1, GL_FALSE, &M[0][0]);
	glm::mat4 V = node->getViewMatrix();
	glUniformMatrix4fv(locationView, 1, GL_FALSE, &V[0][0]);
	glm::mat4 P = node->getProjectionMatrix();
	glUniformMatrix4fv(locationProjection, 1, GL_FALSE, &P[0][0]);
}

void GBufferShaderProgram::bindTextures(MeshNode * node)
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, node->getTexture()->getTextureID());
	glUniform1i(locationDiffuseTexture, 0);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, node->getTexture()->getTextureID());
	glUniform1i(locationSpecularTexture, 1);
}

