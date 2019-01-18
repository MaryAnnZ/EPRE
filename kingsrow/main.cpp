#include <glad/glad.h>

#include <GLFW/glfw3.h>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>


#include <stdio.h>
#include <stdlib.h>
#include <GLFW\glfw3.h>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <map>
#include <sstream>

#include "InputHandler.h"
#include "Render\Renderer.h"
#include "Util\UuidHelper.h"
#include "Importers\MeshImporter.h"
#include "SceneGraph\TransformNode.h"
#include "SceneGraph\LightNode\LightsEnum.h"
#include "SceneGraph\CameraNode.h"
#include "SceneGraph\PlayerNode.h"
#include "SceneGraph\LightNode\PointLightNode.h"
#include "SceneGraph\LightNode\DirectionalLightNode.h"
#include "SceneGraph\LightNode\SpotLightNode.h"
#include "SceneGraph\LightBox.h"
#include "Texture\SamplerStateEnum.h"
#include "Texture\MipmapStateEnum.h"
#include "Framebuffer.h"


int main() {
	int viewPortResX = 1024;
	int viewPortResY = 756;
	Renderer* renderer = Renderer::getInstance();
	if (renderer->init(viewPortResX, viewPortResY) == -1) {
		return -1;
	}

	InputHandler* input = new InputHandler();


	//Texture* rainbowTexture = new Texture("../kingsrow/Assets/Models/duck_textures/rainbow.jpg");

	std::map<std::string, CameraNode*> cameraList;

	//start of part that should be in a scene loader
	CameraNode* activeCamera = new CameraNode(generateUuid(), viewPortResX, viewPortResY);


	//this way we have a list of cameras and can switch between them as we want just by doing activeCamera = cameraList.find("whichever camera we want")->second;
	cameraList.insert(std::pair<std::string, CameraNode*>(std::string("player camera"), activeCamera));

	SceneNode* sceneGraph = new SceneNode(generateUuid(), NodeType::ROOT_NODE);
	sceneGraph->setParent(nullptr);


	std::vector<LightNode*> lights;
	const unsigned int NR_LIGHTS = 32;
	srand(13);
	std::vector<LightBox*> lightBoxes;
	for (unsigned int i = 0; i < NR_LIGHTS; i++)
	{
		
		// calculate slightly random offsets
		float xPos = ((rand() % 100) / 100.0) * 6.0 - 3.0;
		float yPos = ((rand() % 100) / 100.0) * 6.0 - 4.0;
		float zPos = ((rand() % 100) / 100.0) * 6.0 - 3.0;
		// also calculate random color
		float rColor = ((rand() % 100) / 200.0f) + 0.5; // between 0.5 and 1.0
		float gColor = ((rand() % 100) / 200.0f) + 0.5; // between 0.5 and 1.0
		float bColor = ((rand() % 100) / 200.0f) + 0.5; // between 0.5 and 1.0

		lights.push_back(new PointLightNode(generateUuid(), glm::vec3(xPos, 1, zPos), 0.10f, glm::vec3(rColor, gColor, bColor), LightType::POINT_LIGHT));
		LightBox* lightBox = new LightBox(generateUuid(), glm::vec3(rColor, gColor, bColor));
		lightBox->prepareForRendering();
		lightBoxes.push_back(lightBox);
		SceneNode* transformNode = new TransformNode(generateUuid(), glm::mat4(
			0.1, 0, 0, 0,
			0, 0.1, 0, 0,
			0, 0, 0.1, 0,
			xPos, 1, zPos, 1));
		transformNode->attachChild(lightBox);
		sceneGraph->attachChild(transformNode);

	}
	////room 1
	//LightNode* firstLight = new PointLightNode(generateUuid(), glm::vec3(2.0, 2, -3), 1.0f, glm::vec3(1, 1, 1), LightType::POINT_LIGHT);
	//LightNode* secondLight = new SpotLightNode(generateUuid(), glm::vec3(2.0, 1.0, -1), 1.0f, glm::vec3(1, 1, 1), glm::vec3(0, -1, 0), glm::vec2(0.5, 0.8), LightType::SPOT_LIGHT);
	//LightNode* secondLight2 = new SpotLightNode(generateUuid(), glm::vec3(2.0, 1.0, -1), 0.0f, glm::vec3(1, 0, 1), glm::vec3(0, -1, 0), glm::vec2(0.5, 0.8), LightType::SPOT_LIGHT);
	//LightNode* secondLight3 = new SpotLightNode(generateUuid(), glm::vec3(2.0, 1.0, -1), 0.0f, glm::vec3(1, 0, 1), glm::vec3(0, -1, 0), glm::vec2(0.5, 0.8), LightType::SPOT_LIGHT);

	//lights.push_back(firstLight);
	//lights.push_back(secondLight);
	//lights.push_back(secondLight2);
	//lights.push_back(secondLight3);

	std::map<int, std::vector<LightNode*>> lightMap;
	lightMap.insert(std::pair<int, std::vector<LightNode*>>(0, lights));

	renderer->setLights(lightMap.find(0)->second);

	Quad* quad = new Quad(generateUuid());
	quad->prepareForRendering();	
	

	

	std::vector<MeshNode*> drawArray;
	for (unsigned int i = 0; i < NR_LIGHTS; i++) {
		MeshNode* mesh = MeshImporter::getInstance()->getMesh(MeshLoadInfo::NANO);
		mesh->prepareForRendering();
		drawArray.push_back(mesh);

		// calculate slightly random offsets
		float xPos = ((rand() % 100) / 100.0) * 6.0 - 3.0;
		float yPos = ((rand() % 100) / 100.0) * 6.0 - 4.0;
		float zPos = ((rand() % 100) / 100.0) * 6.0 - 3.0;

		// also calculate random color
		float xScale = ((rand() % 100) / 200.0f); // between 0.5 and 1.0
		float yScale = ((rand() % 100) / 200.0f); // between 0.5 and 1.0
		float zScale = ((rand() % 100) / 200.0f); // between 0.5 and 1.0

		SceneNode* transformNode = new TransformNode(generateUuid(), glm::mat4(
			xScale, 0, 0, 0,
			0, yScale, 0, 0,
			0, 0, zScale, 0,
			xPos, 0.8, zPos, 1));

		transformNode->attachChild(mesh);
		sceneGraph->attachChild(transformNode);

	}

	SceneNode* playerTransform = new TransformNode(generateUuid(), glm::mat4(
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, -2, 1));

	PlayerNode* player = new PlayerNode(generateUuid());
	player->setCamera(activeCamera);
	playerTransform->attachChild(activeCamera);
	playerTransform->attachChild(player);
	sceneGraph->attachChild(playerTransform);

	//should probably done recursively in sceneNode		

	Framebuffer* framebuffer = new Framebuffer(viewPortResX, viewPortResY);

	//end of part that should be in a scene loader

	double time = glfwGetTime();
	double oldTime = glfwGetTime();
	double timeStep = 1.0 / 60.0;
	double timeOld = 0;

	//gameloop
	while (!input->esc && glfwWindowShouldClose(renderer->getWindow()) == 0) {
		input->update(renderer->getWindow());

		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

		time = glfwGetTime();
		double deltaTime = time - oldTime;
		while (deltaTime > timeStep)
		{
			deltaTime -= timeStep;
			sceneGraph->update(timeStep, input);
		}
		oldTime = time - deltaTime;

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		


		glm::mat4 projectionMatrix = activeCamera->getProjectionMatrix();
		glm::mat4 viewMatrix = activeCamera->getViewMatrix();
		glm::mat4 viewProjectionMatrix = projectionMatrix * viewMatrix;
		glm::vec3 playerPosition = glm::vec3(glm::inverse(viewMatrix)[0][3], glm::inverse(viewMatrix)[1][3], glm::inverse(viewMatrix)[2][3]);

		//geometry pass
		framebuffer->renderGeometryPass();
		for (MeshNode* node : drawArray) {
			//-------------draw-------------------
			node->draw(viewMatrix, projectionMatrix, viewProjectionMatrix, player->getPosition());
		}
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		//lighting pass
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		quad->draw(player->getPosition(), framebuffer);

		framebuffer->bindDepthBuffer();

		for (LightBox* lightBox : lightBoxes) {
			lightBox->draw(viewMatrix, projectionMatrix);
		}

		glfwSwapBuffers(renderer->getWindow());
		glfwPollEvents();
	}

	glfwTerminate();

	return 0;
}


