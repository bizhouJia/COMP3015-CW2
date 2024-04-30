#include "scenebasic_uniform.h"

#include <cstdio>
#include <cstdlib>

#include <string>
using std::string;

#include <iostream>
using std::cerr;
using std::endl;

#include "helper/glutils.h"

using glm::vec3;
using glm::mat4;

SceneBasic_Uniform::SceneBasic_Uniform() : cup(0.3f, 0.2f, 1, 20) {}

void SceneBasic_Uniform::initScene()
{
    compile();
	// Enable depth testing for 3D rendering
	glEnable(GL_DEPTH_TEST);
	// Initialize the model matrix to an identity matrix
	model = mat4(1.0f);
	// Set up the view matrix to position and locate the camera
	view = glm::lookAt(vec3(0.0f, 0.0f, 2.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));
	// Rotate the model
	model = glm::rotate(model, glm::radians(35.0f), vec3(1.0f, 0.0f, 0.0f));
	projection = mat4(1.0f);
	// Set the light position uniform in the shader
	prog.setUniform("LightPosition", view * glm::vec4(1.0f, 7.0f, 0.0f, -2.0f));
	// Set the diffuse light intensity and diffuse reflectivity
	prog.setUniform("Ld", vec3(1.0f, 1.0f, 1.0f));
	prog.setUniform("Kd", vec3(0.5f, 0.5f, 0.5f));
}

void SceneBasic_Uniform::compile()
{
	try {
		prog.compileShader("shader/basic_uniform.vert");
		prog.compileShader("shader/basic_uniform.frag");
		prog.link();
		prog.use();
	} catch (GLSLProgramException &e) {
		cerr << e.what() << endl;
		exit(EXIT_FAILURE);
	}
}

void SceneBasic_Uniform::update( float t )
{
	//update your angle here
}

void SceneBasic_Uniform::render()
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	// Set the matrices for rendering
	setMatrices();
	// Render the cup
	cup.render();
}

void SceneBasic_Uniform::resize(int w, int h)
{
	// Set the view point size to match window size
	glViewport(0,0,w,h);
    width = w;
    height = h;
	// Update the projection matrix for the new window size
	projection = glm::perspective(glm::radians(70.0f), (float)w / h, 0.3f, 100.0f);
}

void SceneBasic_Uniform::setMatrices()
{
	// Combine the view and model matrices
	mat4 modelView = view * model;
	// Set the ModelViewMatrix uniform in the shader
	prog.setUniform("ModelViewMatrix", modelView);
	// Calculate and set the NormalMatrix uniform for transforming normals
	prog.setUniform("NormalMatrix", glm::mat3(vec3(modelView[0]), vec3(modelView[1]), vec3(modelView[2])));
	// Calculate and set the model view projection matrix uniform
	prog.setUniform("MVP", projection * modelView);
}
