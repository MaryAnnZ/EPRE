#include "DeferredShaderProgram.h"
#include <sstream>



DeferredShaderProgram::DeferredShaderProgram(GLuint shaderProgramID) : ShaderProgram(shaderProgramID)
{
}


DeferredShaderProgram::~DeferredShaderProgram()
{
}

void DeferredShaderProgram::loadUniformLocations()
{
	locationPosition = glGetUniformLocation(programId, "gPosition");
	locationNormal = glGetUniformLocation(programId, "gNormal");
	locationAlbedo = glGetUniformLocation(programId, "gAlbedoSpec");
	locationViewPos = glGetUniformLocation(programId, "viewPos");
}

void DeferredShaderProgram::fillUniformLocation(MeshNode* node, std::vector<LightNode*> lights)
{
	useLights(lights);

	glm::vec3 pos = node->getPlayerPosition();
	glUniform3f(locationViewPos, pos.x, pos.y, pos.z);
}

void DeferredShaderProgram::fillUniformLocation(Framebuffer* framebuffer)
{
	glUniform1i(locationPosition, 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, framebuffer->getPosition());
	
	glUniform1i(locationNormal, 1);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, framebuffer->getNormal());
	
	glUniform1i(locationAlbedo, 2);
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, framebuffer->getAlbedoSpec());
	
}

void DeferredShaderProgram::useLights(std::vector<LightNode*> lights)
{
	for (unsigned int i = 0; i < lights.size(); ++i) {
		std::stringstream position;
		position << "lights[";
		position << i;
		position << "].Position";
		glUniform3f(glGetUniformLocation(programId, position.str().c_str()), lights.at(i)->getPosition().x, lights.at(i)->getPosition().y, lights.at(i)->getPosition().z);
		std::stringstream color;
		color << "lights[";
		color << i;
		color << "].Color";
		glUniform3f(glGetUniformLocation(programId, color.str().c_str()), lights.at(i)->getColor().x, lights.at(i)->getColor().y, lights.at(i)->getColor().z);
		std::stringstream linear;
		linear << "lights[";
		linear << i;
		linear << "].Linear";
		glUniform1f(glGetUniformLocation(programId, linear.str().c_str()), 0.7);
		std::stringstream quadratic;
		linear << "lights[";
		linear << i;
		linear << "].Quadratic";
		glUniform1f(glGetUniformLocation(programId, quadratic.str().c_str()), 0.1);
	}
}

void DeferredShaderProgram::bindTextures(MeshNode * node)
{
}
