#pragma once

#include <string>
#include <GL\glew.h>
#include "Error.h"
namespace Lengine{
	class GLSLProgram{
	public:
		GLSLProgram();


		void compileShaders(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath);
		void linkShaders();
		void bindAttribute(const std::string& attributeName, GLuint indexOfAttribute);
		void use();
		void unuse();

		GLint getUniformLocation(const std::string& uniformName);

		~GLSLProgram();

	private:

		GLuint _programID;
		GLuint _vertexShaderID;
		GLuint _fragmentShaderID;
		GLint _numAttributes;


		void compileShader(const std::string& filePath, GLuint id);

	};

}