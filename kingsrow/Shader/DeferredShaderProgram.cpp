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
	locationPosition = glGetUniformLocation(programId, "pos");
	locationNormal = glGetUniformLocation(programId, "normal");
	locationAlbedo = glGetUniformLocation(programId, "texture");
	locationViewPos = glGetUniformLocation(programId, "viewPos");
	locationAttenuation = glGetUniformLocation(programId, "attenuationOn");
}

void DeferredShaderProgram::fillUniformLocation(MeshNode* node, std::vector<LightNode*> lights)
{
	useLights(lights);
	//set invalid lights
	for (unsigned int i = lights.size(); i < 100; i++) {
		std::stringstream valid;
		valid << "lights[";
		valid << i;
		valid << "].valid";
		glUniform1i(glGetUniformLocation(programId, valid.str().c_str()), false);
	}
	glm::vec3 pos = node->getPlayerPosition();
	glUniform3f(locationViewPos, pos.x, pos.y, pos.z);
	glUniform1i(locationAttenuation, node->getAttenuation());
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
		position << "].position";
		GLuint positionLoc = glGetUniformLocation(programId, position.str().c_str());
		glUniform3f(positionLoc, lights.at(i)->getPosition().x, lights.at(i)->getPosition().y, lights.at(i)->getPosition().z);
		std::stringstream color;
		color << "lights[";
		color << i;
		color << "].color";
		GLuint colorLoc = glGetUniformLocation(programId, color.str().c_str());
		glUniform3f(colorLoc, lights.at(i)->getColor().x, lights.at(i)->getColor().y, lights.at(i)->getColor().z);
		std::stringstream intensity;
		intensity << "lights[";
		intensity << i;
		intensity << "].intensity";
		GLuint intensityLoc = glGetUniformLocation(programId, intensity.str().c_str());
		glUniform1f(intensityLoc, lights.at(i)->getIntensity());
		std::stringstream valid;
		valid << "lights[";
		valid << i;
		valid << "].valid";
		glUniform1i(glGetUniformLocation(programId, valid.str().c_str()), true);
	}
}

void DeferredShaderProgram::bindTextures(MeshNode * node)
{
}
