#ifndef SHADER_INCLUDED_H
#define SHADER_INCLUDED_H

#include <string>
#include <GL/glew.h>
#include "transform.h"
#include "Camera.h"


class Shader
{
public:
	Shader(const std::string& fileName);
	void Update(const Transform& transform, const Camera& camera);
	void Bind();

	virtual ~Shader();
protected:
private:
	static const unsigned int NUM_SHADERS = 2;
	static const unsigned int NUM_UNIFORMS = 3;
	void operator=(const Shader& shader) {}
	Shader(const Shader& shader) {}

	enum{
		TRANSFORM_U
		//,NUM_UNIFORMS
	};

	std::string LoadShader(const std::string& fileName);
	void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);
	GLuint CreateShader(const std::string& text, unsigned int type);

	GLuint m_program;
	GLuint m_shaders[NUM_SHADERS];
	GLuint m_uniforms[NUM_UNIFORMS];
};

#endif