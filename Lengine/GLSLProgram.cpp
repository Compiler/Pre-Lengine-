#include "GLSLProgram.h"
#include <fstream>
#include <vector>


namespace Lengine{

	GLSLProgram::GLSLProgram() : _programID(0), _vertexShaderID(0), _fragmentShaderID(0), _numAttributes(0){


	}






	void GLSLProgram::compileShaders(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath){
		_programID = glCreateProgram();


		if((_vertexShaderID = glCreateShader(GL_VERTEX_SHADER)) == 0){
			Error::throwException("Failure creating vertex shader", Error::SHADER, true);
		}

		if((_fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER)) == 0){
			Error::throwException("Failure creating fragment shader", Error::SHADER, true);
		}

		compileShader(vertexShaderFilePath, _vertexShaderID);
		compileShader(fragmentShaderFilePath, _fragmentShaderID);

	}


	void GLSLProgram::compileShader(const std::string& filePath, GLuint id){
		std::ifstream file(filePath);
		if(file.fail()){
			perror(filePath.c_str());
			Error::throwException("Failed to open " + filePath, Error::SHADER, true);
		}

		std::string fileContents = "";
		std::string line;

		while(std::getline(file, line)){
			fileContents += line + "\n";
		}
		file.close();

		const char* contentsPointer = fileContents.c_str();
		glShaderSource(id, 1, &contentsPointer, nullptr);

		glCompileShader(id);

		//check for errors
		GLint success = 0;
		glGetShaderiv(id, GL_COMPILE_STATUS, &success);

		if(success == GL_FALSE){

			GLint maxLength = 0;
			glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<char> errorLog(maxLength);
			glGetShaderInfoLog(id, maxLength, &maxLength, &errorLog[0]);


			glDeleteShader(id);

			std::printf("%s\n", &(errorLog[0]));
			Error::throwException("Shader failed to compile", Error::SHADER, true);
		}


	}

	void GLSLProgram::linkShaders(){



		glAttachShader(_programID, _vertexShaderID);
		glAttachShader(_programID, _fragmentShaderID);

		glLinkProgram(_programID);

		GLint isLinked = 0;
		glGetProgramiv(_programID, GL_LINK_STATUS, (int *)&isLinked);

		if(isLinked == GL_FALSE){
			GLint maxLength = 0;
			glGetProgramiv(_programID, GL_INFO_LOG_LENGTH, &maxLength);

			//The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(_programID, maxLength, &maxLength, &infoLog[0]);

			//We don't need the program anymore.
			glDeleteProgram(_programID);
			//Don't leak shaders either.
			glDeleteShader(_vertexShaderID);
			glDeleteShader(_fragmentShaderID);

			std::printf("%s\n", &(infoLog[0]));
			Error::throwException("Couldn't link shaders", Error::SHADER, true);
		}

		glDetachShader(_programID, _vertexShaderID);
		glDetachShader(_programID, _fragmentShaderID);
		glDeleteShader(_vertexShaderID);
		glDeleteShader(_fragmentShaderID);
	}

	void GLSLProgram::bindAttribute(const std::string& attributeName, GLuint indexOfAttribute){

		glBindAttribLocation(_programID, indexOfAttribute, attributeName.c_str());
		_numAttributes++;

	}

	GLint GLSLProgram::getUniformLocation(const std::string& uniformName){

		GLint id = glGetUniformLocation(_programID, uniformName.c_str());
		if(id == -1){
			Error::throwException("Could not find uniform: " + uniformName, -1, false);
			return -1;
		} else
			return id;

	}


	void GLSLProgram::use(){

		glUseProgram(_programID);

		for(int i = 0; i < _numAttributes; i++)
			glEnableVertexAttribArray(i);

	}

	void GLSLProgram::unuse(){

		glUseProgram(0);
		for(int i = 0; i < _numAttributes; i++)
			glDisableVertexAttribArray(i);

	}


	GLSLProgram::~GLSLProgram(){
	}

}