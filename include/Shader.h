#ifndef SHADER_H
#define SHADER_H

#include "common.h"

using namespace std;
using namespace glm;

class Scene;
class Model;

class Shader
{

public:

	Shader();
	~Shader();

	string readFromFile(string filename);
	void compileShader(GLuint shaderId, GLenum type, string code);
	virtual bool init(string vertexShaderFilename, string tessellationControlShaderFilename, string tessellationEvaluationShaderFilename, string fragmentShaderFilename);
	virtual void update(Scene *scene);
	virtual void update(Model *model);

	bool hasTessellation() { return tessellationControlShaderId && tessellationEvaluationShaderId; }
	GLint getUniformLocation(string name);

	void setInt(GLint id, int newValue) { glUniform1i(id, newValue); }
	void setFloat(GLint id, GLfloat newValue) { glUniform1f(id, newValue); }
	void setFloat2(GLint id, GLfloat v0, GLfloat v1) { glUniform2f(id, v0, v1); }
	void setFloat3(GLint id, GLfloat v0, GLfloat v1, GLfloat v2) { glUniform3f(id, v0, v1, v2); }
	void setFloat4(GLint id, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3) { glUniform4f(id, v0, v1, v2, v3);	}
	void setMatrix4(GLint id, GLsizei count, GLboolean transpose, const GLfloat *value) { glUniformMatrix4fv(id, count, transpose, value); }

	virtual void setViewProjectionMatrix(const mat4& viewProjectionMatrix);
    virtual void setModelMatrix(const mat4& modelMatrix);

	virtual void setActive(bool active);

	virtual void release();

protected:

	GLuint vertexShaderId;
	GLuint tessellationControlShaderId;
	GLuint tessellationEvaluationShaderId;
	GLuint fragmentShaderId;
	GLuint programId;

	GLuint viewProjectionMatrixId;
    GLuint modelMatrixId;

};

#endif











