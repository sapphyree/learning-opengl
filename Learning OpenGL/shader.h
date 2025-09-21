#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader {
public:
	unsigned int programID;

	Shader(const char* pathToVertexShader, const char* pathtoFragmentShader) {
		// 1. retrieve source for shaders from filePath
		std::string vertexShaderCode;
		std::string fragmentShaderCode;
		std::ifstream vShaderFile;
		std::ifstream fShaderFile;

		// ifstream object exceptions
		vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		try {
			// open files
			vShaderFile.open(pathToVertexShader);
			fShaderFile.open(pathtoFragmentShader);
			std::stringstream vShaderStream, fShaderStream;
			// read file contents to stream
			vShaderStream << vShaderFile.rdbuf();
			fShaderStream << fShaderFile.rdbuf();
			// close file handlers
			vShaderFile.close();
			fShaderFile.close();
			// convert stream to string
			vertexShaderCode	= vShaderStream.str();
			fragmentShaderCode = fShaderStream.str();
		}
		catch (std::ifstream::failure error) {
			std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ\n" << std::endl;
		}
		const char* vShaderCode = vertexShaderCode.c_str();
		const char* fShaderCode = fragmentShaderCode.c_str();

		// 2. compile shaders
		unsigned int compiledVertexShader, compiledFragmentShader;
		int success;
		char infolog[512];

		// vertex shader
		compiledVertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(compiledVertexShader, 1, &vShaderCode, NULL);
		glCompileShader(compiledVertexShader);

		// compile error check
		glGetShaderiv(compiledVertexShader, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(compiledVertexShader, 512, NULL, infolog);
			std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infolog << std::endl;
		}

		// vertex shader
		compiledFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(compiledFragmentShader, 1, &fShaderCode, NULL);
		glCompileShader(compiledFragmentShader);

		// compile error check
		glGetShaderiv(compiledFragmentShader, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(compiledFragmentShader, 512, NULL, infolog);
			std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infolog << std::endl;
		}

		// shader program
		programID = glCreateProgram();
		glAttachShader(programID, compiledVertexShader);
		glAttachShader(programID, compiledFragmentShader);
		glLinkProgram(programID);

		// link error check
		glGetProgramiv(programID, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(programID, 512, NULL, infolog);
			std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infolog << std::endl;
		}

		// cleanup shaders
		glDeleteShader(compiledVertexShader);
		glDeleteShader(compiledFragmentShader);
	};
	
	void use() {
		glUseProgram(programID);
	};

	// uniform functions
	void setBool(const std::string& name, bool value) const {
		glUniform1i(glGetUniformLocation(programID, name.c_str()), (int)value);
	};

	void setInt(const std::string& name, int value) const {
		glUniform1i(glGetUniformLocation(programID, name.c_str()), value);
	};

	void setFloat(const std::string& name, float value) const {
		glUniform1f(glGetUniformLocation(programID, name.c_str()), value);
	};
};

#endif