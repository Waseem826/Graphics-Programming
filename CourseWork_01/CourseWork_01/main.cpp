#pragma comment(lib, "GLFWDLL")
#pragma comment(lib, "OpenGL32")
#pragma comment(lib, "glew32")
#pragma comment(lib, "DevIL")
#pragma comment(lib, "ILU")
#pragma comment(lib, "ILUT")

#define GLFW_DLL

#include <glew.h>
#include <GL\glfw.h>
#include <IL\ilut.h>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <glm\gtc\quaternion.hpp>
#include <glm\gtx\constants.hpp>
#include <cstdlib>
#include <iostream>
#include <time.h>
#include "render_object.h"
#include "effect.h"
#include "light.h"
#include "scene.h"
#include "camera.h"
#include "util.h"
#include "skybox.h"
#include "Point_sprite.h"
#include "frame_buffer.h"
#include "post_process.h"
#include "fireworks.h"

bool running = true;

effect eff;

scene_data* scene;
scene_data* scene1;
scene_data* scene2;
scene_data* scene3;

skybox* sb;
skybox* sb1;
skybox* sb2;

const int FIREWORKS = 3;
int frameCount = 0;
Firework fw[FIREWORKS];
char lastKeyPress;
char selectedPostProc;

target_camera* cam1;
target_camera* introCam;
first_person_camera* cam;
camera* currentCam;

post_process* post_proc;
post_process* post_proc1;
post_process* post_proc2;
post_process* post_proc3;

float screenHeight = 600.0f;
float screenWidth = 800.0f;

void initialise()
{
	srand(time(NULL));
		
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_VERTEX_ARRAY);
	//glClearColor(0.0f, 1.0f, 1.0f, 1.0f);

	// Set the accumulation buffer clearing colour to black at 0,0f alpha
	glClearAccum(0.0f, 0.0f, 0.0f, 0.0f);
	
	glEnable(GL_POINT_SMOOTH); // Smooth the points so that they're circular and not square
	glPointSize(fw->particleSize);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//TargetCamera================================
	cam1 = new target_camera();
	cam1->setProjection(glm::degrees(glm::quarter_pi<float>()), screenWidth/screenHeight, 0.1f, 10000.0f);
	cam1->setTarget(glm::vec3(0.0f, 0.0f, 0.0f));
	cam1->setPositon(glm::vec3(5.0f, 2.0f, 5.0f));
	//===========================================================
	//IntroCamera
	introCam = new target_camera();
	introCam->setProjection(glm::degrees(glm::quarter_pi<float>()), screenWidth/screenHeight, 0.1f, 10000.0f);
	introCam->setTarget(glm::vec3(0.5f, 0.5f, 0.0f));
	introCam->setPositon(glm::vec3(0.43227, 1.21953, -6.0));

	//First personCamera=====================================
	cam = new first_person_camera();
	cam->setProjection(glm::pi<float>() / 4.0f, screenWidth/screenHeight, 0.1f, 10000.0f);
	cam->setPositon(glm::vec3(0.0f, 2.0f, -5.0f));
	//=============================================================


	if (!eff.addShader("lit_textured.vert", GL_VERTEX_SHADER))
		exit(EXIT_FAILURE);
	if (!eff.addShader("lighting.frag", GL_FRAGMENT_SHADER))
		exit(EXIT_FAILURE);
	if (!eff.addShader("point_light.frag", GL_FRAGMENT_SHADER))
		exit(EXIT_FAILURE);
	if (!eff.addShader("spot_light.frag", GL_FRAGMENT_SHADER))
		exit(EXIT_FAILURE);
	if (!eff.addShader("lit_textured.frag", GL_FRAGMENT_SHADER))
		exit(EXIT_FAILURE);
	if (!eff.create())
		exit(EXIT_FAILURE);


	effect* post_eff = new effect();
	if(!post_eff->addShader("post_process.vert", GL_VERTEX_SHADER))
		exit(EXIT_FAILURE);
	if(!post_eff->addShader("Sepia.frag", GL_FRAGMENT_SHADER))
		exit(EXIT_FAILURE);
	if (!post_eff->create())
		exit(EXIT_FAILURE);

	effect* post_eff1 = new effect();
	if(!post_eff1->addShader("post_process.vert", GL_VERTEX_SHADER))
		exit(EXIT_FAILURE);
	if(!post_eff1->addShader("Greyscale.frag", GL_FRAGMENT_SHADER))
		exit(EXIT_FAILURE);
	if (!post_eff1->create())
		exit(EXIT_FAILURE);

	effect* post_eff2 = new effect();
	if(!post_eff2->addShader("post_process.vert", GL_VERTEX_SHADER))
		exit(EXIT_FAILURE);
	if(!post_eff2->addShader("Negative.frag", GL_FRAGMENT_SHADER))
		exit(EXIT_FAILURE);
	if (!post_eff2->create())
		exit(EXIT_FAILURE);

	lastKeyPress = '3';
	selectedPostProc = 'O';
	
	scene1 = loadScene("TableAndChairs.json");
	//scene2 = loadScene("scene.json");
	scene2 = loadScene("ParkBench.json");
	scene3 = loadScene("Insturctions.json");
	
	post_proc1 = new post_process(post_eff);
	post_proc1->create(screenWidth, screenHeight);
	post_proc2 = new post_process(post_eff1);
	post_proc2->create(screenWidth, screenHeight);
	post_proc3 = new post_process(post_eff2);
	post_proc3->create(screenWidth, screenHeight);

	//post_proc = post_proc1;
	
	std::vector<std::string> cubemap_texs;
	cubemap_texs.push_back("xpos.png");
	cubemap_texs.push_back("xneg.png");
	cubemap_texs.push_back("ypos.png");
	cubemap_texs.push_back("yneg.png");
	cubemap_texs.push_back("zpos.png");
	cubemap_texs.push_back("zneg.png");

	std::vector<std::string> cubemap_texs1;
	cubemap_texs1.push_back("posx.jpg");
	cubemap_texs1.push_back("negx.jpg");
	cubemap_texs1.push_back("posy.jpg");
	cubemap_texs1.push_back("negy.jpg");
	cubemap_texs1.push_back("posz.jpg");
	cubemap_texs1.push_back("negz.jpg");

	cubemap* cm = new cubemap(cubemap_texs);
	cm->create();

	cubemap* cm1 = new cubemap(cubemap_texs1);
	cm1->create();
	
	sb1 = new skybox(cm);
	sb1->create();

	sb2 = new skybox(cm1);
	sb2->create();
	
	//sb = sb1;

}

void moveFPSCam(float deltaTime, float speed)
{
	//fps cam controls
	if (glfwGetKey('W'))
		cam->move(glm::vec3(0.0f, 0.0f, speed) * (float)deltaTime);
	if (glfwGetKey('S'))
		cam->move(-glm::vec3(0.0f, 0.0f, speed) * (float)deltaTime);
	if (glfwGetKey('A'))
		cam->move(glm::vec3(speed, 0.0f, 0.0f) * (float)deltaTime);
	if (glfwGetKey('D'))
		cam->move(-glm::vec3(speed, 0.0f, 0.0f) * (float)deltaTime);
	if (glfwGetKey('E'))
		cam->rotate(-glm::pi<float>() / 4.0f * deltaTime, 0.0f);
	if (glfwGetKey('Q'))
		cam->rotate(glm::pi<float>() / 4.0f * deltaTime, 0.0f);
	if (glfwGetKey(GLFW_KEY_LSHIFT))
		cam->move(-glm::vec3(0.0f, speed, 0.0f) * (float)deltaTime);
	if (glfwGetKey(GLFW_KEY_SPACE))
		cam->move(glm::vec3(0.0f, speed, 0.0f) * (float)deltaTime);
}

void render(const effect* eff, const glm::mat4 view, const glm::mat4& projection, const render_object* object)
{
	glm::mat4 mvp = projection * view * object->transform.getTransformationMatrix();
	glUniformMatrix4fv(eff->getUniformIndex("modelViewProjection"), 1, GL_FALSE, glm::value_ptr(mvp));
	glm::mat4 mit = glm::inverse(glm::transpose(object->transform.getTransformationMatrix()));
	glUniformMatrix4fv(eff->getUniformIndex("modelInverseTranspose"), 1, GL_FALSE, glm::value_ptr(mit));
	glUniformMatrix4fv(eff->getUniformIndex("model"), 1, GL_FALSE, glm::value_ptr(object->transform.getTransformationMatrix()));
	CHECK_GL_ERROR
	glm::mat4 scale = glm::scale(glm::mat4(1.0f), object->transform.scale);
	glUniformMatrix4fv(eff->getUniformIndex("scale"), 1, GL_FALSE, glm::value_ptr(scale));
	CHECK_GL_ERROR
	object->material->bind(eff);

	glBindVertexArray(object->geometry->vao);
	if (object->geometry->indexBuffer)
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, object->geometry->indexBuffer);
		glDrawElements(GL_TRIANGLES, object->geometry->indices.size(), GL_UNSIGNED_INT, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		CHECK_GL_ERROR
	}
	else
		glDrawArrays(GL_TRIANGLES, 0, object->geometry->vertices.size());
	glBindVertexArray(0);
	CHECK_GL_ERROR
}



void renderScene2()
{

	post_proc->beginRender(true);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
	sb->render(currentCam);
	
	eff.begin();
	scene->light.bind(&eff);
	scene->dynamic.bind(&eff);
	
	glUniform3fv(eff.getUniformIndex("eyePos"), 1, glm::value_ptr(currentCam->getPosition()));
	CHECK_GL_ERROR
	
	std::hash_map<std::string, render_object*>::const_iterator iter = scene->objects.begin();
	for (; iter != scene->objects.end(); ++iter)
		render(&eff, currentCam->getView(), currentCam->getProjecion(), iter->second);

	post_proc->endRender();
	eff.end();
	
	post_proc->render(true);
	
	glfwSwapBuffers();
}

void drawFireworks()
{
	// Displacement trick for exact pixelisation
	glTranslatef(0.375, 0.375, 0);

	// Draw our fireworks
	for (int loop = 0; loop < FIREWORKS; loop++)
	{
		for (int particleLoop = 0; particleLoop < FIREWORK_PARTICLES; particleLoop++)
		{
 			// Set the point size of the firework particles (this needs to be called BEFORE opening the glBegin(GL_POINTS) section!)
			glPointSize(fw[loop].particleSize);
 
			glBegin(GL_POINTS);
				// Set colour to yellow on the way up, then whatever colour firework should be when exploded
				if (fw[loop].hasExploded == false)
				{
					glColor4f(1.0f, 1.0f, 0.0f, 1.0f);
				}
				else
				{
					glColor4f(fw[loop].red, fw[loop].green, fw[loop].blue, fw[loop].alpha);
				}
				// Draw the point
				glVertex3f(fw[loop].x[particleLoop], fw[loop].y[particleLoop], fw[loop].z[particleLoop]);
			glEnd();
		}
		// Move the firework appropriately depending on its explosion state
		if (fw[loop].hasExploded == false)
		{
			fw[loop].move();
		}
		else
		{
			fw[loop].explode();
		}
	}
}

void renderFireworksScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glAccum(GL_RETURN, 0.99f);
	glClear(GL_ACCUM_BUFFER_BIT);
	
	eff.begin();

	scene->dynamic.bind(&eff);
	scene->light.bind(&eff);

	glUniform3fv(eff.getUniformIndex("eyePos"), 1, glm::value_ptr(currentCam->getPosition()));

	drawFireworks();
	
	std::hash_map<std::string, render_object*>::const_iterator iter = scene->objects.begin();
	for (; iter != scene->objects.end(); ++iter)
		render(&eff, currentCam->getView(), currentCam->getProjecion(), iter->second);
		
	eff.end();
	glUseProgram(0);
	CHECK_GL_ERROR
	glfwSwapBuffers();

	glAccum(GL_ACCUM, 0.2f); //0.2f
}

void renderSceneIntro()
{	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
	eff.begin();
	scene->light.bind(&eff);
	scene->dynamic.bind(&eff);
	
	glUniform3fv(eff.getUniformIndex("eyePos"), 1, glm::value_ptr(currentCam->getPosition()));
	CHECK_GL_ERROR
	
	std::hash_map<std::string, render_object*>::const_iterator iter = scene->objects.begin();
	for (; iter != scene->objects.end(); ++iter)
		render(&eff, currentCam->getView(), currentCam->getProjecion(), iter->second);

	eff.end();
	glUseProgram(0);
	CHECK_GL_ERROR
	glfwSwapBuffers();
}

void update(double deltaTime)
{
	cam->update(deltaTime);
	introCam->update(deltaTime);
	moveFPSCam(deltaTime, 1.0f);

	running = !glfwGetKey(GLFW_KEY_ESC) && glfwGetWindowParam(GLFW_OPENED);	

	if (lastKeyPress == '1') //render scene 1
	{
		scene = scene1;
		currentCam = cam;
		renderFireworksScene();
		
	}
	
	if (lastKeyPress == '2') // render scene 2
	{
		
		scene = scene2;
		sb = sb2;
		
		currentCam = cam;
		

		if (selectedPostProc == 'I')
			post_proc = post_proc1;
		if (selectedPostProc == 'O')
			post_proc = post_proc2;
		if (selectedPostProc == 'P')
			post_proc = post_proc3;

		renderScene2();

		if (glfwGetKey('I'))
			selectedPostProc = 'I';
		if (glfwGetKey('O'))
			selectedPostProc = 'O';
		if (glfwGetKey('P'))
			selectedPostProc = 'P';
	}
	
	if (lastKeyPress == '3') // render scene 2
	{
		sb = sb2;
		post_proc = post_proc2;
		scene = scene3;
		currentCam = introCam;
		renderSceneIntro();	
		std::cout<<cam->getPosition().x<<" , "<<cam->getPosition().y<<" , "<<cam->getPosition().z;
	}

	if (glfwGetKey('1'))
		lastKeyPress = '1';
	if (glfwGetKey('2'))
		lastKeyPress = '2';
	if (glfwGetKey('3'))
		lastKeyPress = '3';
}

void cleanup()
{
}

int main()
{
	SET_DEBUG

	if (!glfwInit())
		exit(EXIT_FAILURE);
	if (!glfwOpenWindow(screenWidth, screenHeight, 0, 0, 0, 0, 0, 0, GLFW_WINDOW))
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	GLenum error = glewInit();
	if (error != GLEW_OK)
	{
		std::cout << "Error: " << glewGetErrorString(error) <<std::endl;
		exit(EXIT_FAILURE);
	}

	const GLubyte* renderer = glGetString(GL_RENDERER);
	const GLubyte* vendor = glGetString(GL_VENDOR);
	const GLubyte* version = glGetString(GL_VERSION);
	const GLubyte* glslVersion = glGetString(GL_SHADING_LANGUAGE_VERSION);
	GLint major , minor;
	glGetIntegerv(GL_MAJOR_VERSION, &major);
	glGetIntegerv(GL_MINOR_VERSION, &minor);
	printf("GL VENDOR : %s\n", vendor);
	printf("GL Renderer : %s\n", renderer);
	printf("GL Version (string) : %s\n", version);
	printf("GL Version (integer) : %d.%d\n", major, minor);
	printf("GLSL version : %s\n", glslVersion);

	ilInit();
	iluInit();
	ilutRenderer(ILUT_OPENGL);

	initialise();

	double prevTimeStamp = glfwGetTime();
	double currentTimeStamp;
	while (running)
	{
		currentTimeStamp = glfwGetTime();
		update(currentTimeStamp - prevTimeStamp);
		
		//render();
		
		prevTimeStamp = currentTimeStamp;
	}

	cleanup();

	glfwTerminate();

	exit(EXIT_SUCCESS);

}



