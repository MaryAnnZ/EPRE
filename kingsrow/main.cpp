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
#include <fstream>

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

#define PI 3.14159265


int main() {

	int viewPortResX = 1024;
	int viewPortResY = 756;
	bool forwardRender = false;
	int NR_LIGHTS = 100;
	int NR_OBJECTS = 2;
	float intensity = 1.0;
	float renderLights = false;



	std::ifstream inputFile("../kingsrow/Assets/config.txt");
	std::string line;
	int linecount = 0;
	/*
	0 - Deferred Shading (0), Forward Shading(1)
	1 - NR_LIGHT (<= 100)
	2 - Light intensity(float)
	3 - NR_OBJECTS
	4 - Viewport width
	5 - Viewport height
	*/
	while (std::getline(inputFile, line)) {
		if (line.length() <= 0) {
			continue;
		}
		if (line.at(0) == '#') { //this is a commentar
			continue;
		}
		switch (linecount)
		{
		case 0: {
			if (line.at(0) == '0') {
				forwardRender = false;
			}
			else if (line.at(0) == '1') {
				forwardRender = true;
			}
			break;
		}
		case 1: {
			NR_LIGHTS = std::stoi(line);
			break;
		}
		case 2: {
			intensity = std::atof(line.c_str());
			break;
		}
		case 3: {
			NR_OBJECTS = std::stoi(line);
			break;
		}
		case 4: {
			viewPortResX = std::stoi(line);
			break;
		}
		case 5: {
			viewPortResY = std::stoi(line);
			break;
		}
		case 6: {
			if (line.at(0) == '0') {
				renderLights = false;
			}
			else if (line.at(0) == '1') {
				renderLights = true;
			}
			break;
		}
		default:
			break;
		}
		linecount++;
	}
	std::cout << forwardRender << std::endl;
	std::cout << NR_LIGHTS << std::endl;
	std::cout << intensity << std::endl;
	std::cout << NR_OBJECTS << std::endl;
	std::cout << viewPortResX << std::endl;
	std::cout << viewPortResY << std::endl;
	std::cout << renderLights << std::endl;

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
	srand(13);
	std::vector<LightBox*> lightBoxes;
	for (unsigned int i = 0; i < std::min(NR_LIGHTS, 100); i++)
	{
		
		// calculate slightly random offsets
		float xPos = ((rand() % 100) / 100.0) * 6.0 - 3.0;
		float yPos = ((rand() % 100) / 100.0) * 6.0 - 4.0;
		float zPos = ((rand() % 100) / 100.0) * 6.0 - 3.0;
		// also calculate random color
		float rColor = ((rand() % 100) / 200.0f) + 0.5; // between 0.5 and 1.0
		float gColor = ((rand() % 100) / 200.0f) + 0.5; // between 0.5 and 1.0
		float bColor = ((rand() % 100) / 200.0f) + 0.5; // between 0.5 and 1.0

		lights.push_back(new PointLightNode(generateUuid(), glm::vec3(xPos, std::max(yPos, 0.0f), zPos), intensity, glm::vec3(rColor, gColor, bColor), LightType::POINT_LIGHT));
		LightBox* lightBox = new LightBox(generateUuid(), glm::vec3(rColor, gColor, bColor));
		lightBox->prepareForRendering();
		lightBoxes.push_back(lightBox);
		SceneNode* transformNode = new TransformNode(generateUuid(), glm::mat4(
			0.1, 0, 0, 0,
			0, 0.1, 0, 0,
			0, 0, 0.1, 0,
			xPos, std::max(yPos, 0.0f), zPos, 1));
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
	

	

	std::vector<MeshNode*> drawArrayDeferred;
	std::vector<MeshNode*> drawArrayForward;

	MeshNode* planeDeferred = MeshImporter::getInstance()->getMesh(MeshLoadInfo::PLANE_DEFERRED);
	MeshNode* planeForward = MeshImporter::getInstance()->getMesh(MeshLoadInfo::PLANE_FORWARD);
	planeDeferred->prepareForRendering();
	planeForward->prepareForRendering();
	drawArrayDeferred.push_back(planeDeferred);
	drawArrayForward.push_back(planeForward);


	SceneNode* transformNode = new TransformNode(generateUuid(), glm::mat4(
			1, 0, 0, 0,
			0, cos(90 * PI / 180), -sin(90 * PI / 180), 0,
			0, sin(90 * PI / 180), cos(90 * PI / 180), 0,
			0, 0, 0, 1));
	SceneNode* scaleTransform = new TransformNode(generateUuid(), glm::mat4(
		10, 0, 0, 0,
		0, 10, 0, 0,
		0, 0, 10, 0,
		0, 0, 0, 1));

	transformNode->attachChild(planeDeferred);
	transformNode->attachChild(planeForward);
	scaleTransform->attachChild(transformNode);
	sceneGraph->attachChild(scaleTransform);

	for (unsigned int i = 0; i < NR_OBJECTS; i++) {
		MeshNode* meshDeferred = MeshImporter::getInstance()->getMesh(MeshLoadInfo::CUBE_DEFERRED);
		MeshNode* meshForward = MeshImporter::getInstance()->getMesh(MeshLoadInfo::CUBE_FORWARD);
		meshDeferred->prepareForRendering();
		meshForward->prepareForRendering();
		drawArrayDeferred.push_back(meshDeferred);
		drawArrayForward.push_back(meshForward);

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
			xPos, std::max(yPos, 0.0f), zPos, 1));

		transformNode->attachChild(meshDeferred);
		transformNode->attachChild(meshForward);
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

		if (input->renderLights) {
			renderLights = !renderLights;
		}
		if (input->renderMode) {
			forwardRender = !forwardRender;
		}
		if (input->intUp) {
			intensity += 0.1;
			for (LightNode* light : lights) {
				light->setIntensity(intensity);
			}
		}
		if (input->intDown) {
			intensity -= 0.1;
			for (LightNode* light : lights) {
				light->setIntensity(intensity);
			}
		}

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

		if (forwardRender) {
			for (MeshNode* node : drawArrayForward) {
				//-------------draw-------------------
				node->draw(viewMatrix, projectionMatrix, viewProjectionMatrix, player->getPosition());
			}
		}
		else {
			//geometry pass
			framebuffer->renderGeometryPass();
			for (MeshNode* node : drawArrayDeferred) {
				//-------------draw-------------------
				node->draw(viewMatrix, projectionMatrix, viewProjectionMatrix, player->getPosition());
			}
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
			//lighting pass
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			quad->draw(player->getPosition(), framebuffer);

			if (renderLights) {
				framebuffer->bindDepthBuffer();

				for (LightBox* lightBox : lightBoxes) {
					lightBox->draw(viewMatrix, projectionMatrix);
				}
			}
		}

		glfwSwapBuffers(renderer->getWindow());
		glfwPollEvents();
	}

	glfwTerminate();

	return 0;
}


