#ifndef SHADER_H
#define SHADER_H

#include "common.h"		

using namespace std;							

class Shader
{

public:

	Shader();
	~Shader();

	string readFromFile(string filename);
	void compileShader(GLuint shaderId, GLenum type, string code);
	bool init(string vertexShaderFilename, string fragmentShaderFilename );

	GLint getUniformLocation(string name);
	
	void setInt(GLint id, int newValue) { glUniform1i(id, newValue); }
	void setFloat(GLint id, GLfloat newValue) { glUniform1f(id, newValue); }
	void setFloat2(GLint id, GLfloat v0, GLfloat v1) { glUniform2f(id, v0, v1); }
	void setFloat3(GLint id, GLfloat v0, GLfloat v1, GLfloat v2) { glUniform3f(id, v0, v1, v2); }
	void setFloat4(GLint id, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3) { glUniform4f(id, v0, v1, v2, v3);	}
	void setMatrix4(GLint id, GLsizei count, GLboolean transpose, const GLfloat *value) { glUniformMatrix4fv(id, count, transpose, value); }
	
	void setActive(bool active);
	
	void release();

private:

	GLuint vertexShaderId;
	GLuint fragmentShaderId;
	GLuint programId;

};

#endif











