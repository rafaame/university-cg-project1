#ifndef _Shader_H
#define _Shader_H

#include <string>										
#include <fstream>										
#include "GL/glew.h"									



class Shader
{
public:

	
	Shader()	{ }
	~Shader()	{ Destroy(); }

	
	std::string LoadShaderFile(std::string strFile);

	
	void Initialize(std::string strVertexFile, std::string strFragmentFile );
	
	
	GLint GetVariable(std::string strVariable);

	
	void SetInt(GLint id, int newValue)											{ glUniform1i(id, newValue);		}
	void SetFloat(GLint id, GLfloat newValue)									{ glUniform1f(id, newValue);		}
	void SetFloat2(GLint id, GLfloat v0, GLfloat v1)							{ glUniform2f(id, v0, v1);			}
	void SetFloat3(GLint id, GLfloat v0, GLfloat v1, GLfloat v2)				{ glUniform3f(id, v0, v1, v2);		}
	void SetFloat4(GLint id, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3)	{ glUniform4f(id, v0, v1, v2, v3);	}
	
	
	void SetMatrix4(GLint id, GLsizei count, GLboolean transpose, const GLfloat *value)
	{ 
		glUniformMatrix4fv(id, count, transpose, value);
	}

	
	void TurnOn()		{	glUseProgram(ShaderProgramId);  }
	void TurnOff()		{	glUseProgram(0);				}
	
	
	void Destroy();

private:

	
	GLuint VertexShaderId;

	
	GLuint FragmentShaderId;

	
	GLuint ShaderProgramId;
};

#endif











