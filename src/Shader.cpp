#include "Shader.h"

#include "RenderingManager.h"
#include "Application.h"

#include "Scene.h"
#include "Player.h"
#include "Camera.h"
#include "Model.h"

using namespace std;
using namespace glm;

Shader::Shader()
{

	vertexShaderId = 0;
	tessellationControlShaderId = 0;
	tessellationEvaluationShaderId = 0;
	fragmentShaderId = 0;
	programId = 0;

	viewProjectionMatrixId = 0;
	modelMatrixId = 0;

}

Shader::~Shader()
{

	release();

}

string Shader::readFromFile(string filename)
{

	cout << "Loading shader file (" << filename << ")... ";

	ifstream fin(filename.c_str());

	if(!fin)
		return "";

	string line = "";
	string code = "";

	while(getline(fin, line))
		code = code + "\n" + line;

	fin.close();

	cout << "loaded" << endl;

	return code;

}

void Shader::compileShader(GLuint shaderId, GLenum type, string code)
{

	const char *codePointer = code.c_str();
	glShaderSource(shaderId, 1, &codePointer, NULL);

	string typeName;

	switch(type)
	{

		case GL_VERTEX_SHADER:

			typeName = "vertex";

			break;

		case GL_TESS_CONTROL_SHADER:

			typeName = "tessellation control";

			break;

		case GL_TESS_EVALUATION_SHADER:

			typeName = "tessellation evaluation";

			break;

		case GL_FRAGMENT_SHADER:

			typeName = "fragment";

			break;

	}

	cout << "Compiling " << typeName  << " shader... ";
	glCompileShader(shaderId);

	GLint success, maxLength;
	glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);
	glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &maxLength);

	if(success == GL_FALSE)
		cout << "error" << endl;
	else
		cout << "compiled" << endl;

	if(maxLength > 0)
	{

		vector<GLchar> errorLog(maxLength + 1);
		glGetShaderInfoLog(shaderId, maxLength, NULL, &errorLog[0]);

		for(auto it = errorLog.begin(); it != errorLog.end(); it++)
			cout << (*it);

		cout << endl;

	}

}

bool Shader::init
(
	string vertexShaderFilename,
	string tessellationControlShaderFilename,
	string tessellationEvaluationShaderFilename,
	string fragmentShaderFilename
)
{

	if(!vertexShaderFilename.length() || !fragmentShaderFilename.length())
		return false;

	if(tessellationControlShaderFilename.length() && !tessellationEvaluationShaderFilename.length())
		return false;

	if(tessellationEvaluationShaderFilename.length() && !tessellationControlShaderFilename.length())
		return false;

	if(vertexShaderId || tessellationControlShaderId || tessellationEvaluationShaderId || fragmentShaderId || programId)
		release();

	string vertexShaderCode = readFromFile(vertexShaderFilename);
	string fragmentShaderCode = readFromFile(fragmentShaderFilename);

	vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
	fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);

	if(tessellationControlShaderFilename.length())
	{

		string tessellationControlShaderCode = readFromFile(tessellationControlShaderFilename);
		string tessellationEvaluationShaderCode = readFromFile(tessellationEvaluationShaderFilename);

		tessellationControlShaderId = glCreateShader(GL_TESS_CONTROL_SHADER);
		tessellationEvaluationShaderId = glCreateShader(GL_TESS_EVALUATION_SHADER);

		compileShader(tessellationControlShaderId, GL_TESS_CONTROL_SHADER, tessellationControlShaderCode);
		compileShader(tessellationEvaluationShaderId, GL_TESS_EVALUATION_SHADER, tessellationEvaluationShaderCode);

	}

	compileShader(vertexShaderId, GL_VERTEX_SHADER, vertexShaderCode);
	compileShader(fragmentShaderId, GL_FRAGMENT_SHADER, fragmentShaderCode);

	programId = glCreateProgram();

	glAttachShader(programId, vertexShaderId);
	glAttachShader(programId, fragmentShaderId);

	if(tessellationControlShaderFilename.length())
	{

		glAttachShader(programId, tessellationControlShaderId);
		glAttachShader(programId, tessellationEvaluationShaderId);

	}

	glLinkProgram(programId);

	GLint success, maxLength;
	glGetProgramiv(programId, GL_LINK_STATUS, &success);
	glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &maxLength);

	if(maxLength > 0)
	{

		vector<GLchar> errorLog(maxLength + 1);
		glGetProgramInfoLog(programId, maxLength, NULL, &errorLog[0]);

		for(auto it = errorLog.begin(); it != errorLog.end(); it++)
			cout << (*it);

		cout << endl;

	}

	if(success == GL_FALSE)
	{

		cout << "Could not create the shader program (errorId: " << success << ")" << endl;

		return false;

	}

	viewProjectionMatrixId = getUniformLocation("viewProjectionMatrix");
    modelMatrixId = getUniformLocation("modelMatrix");

	return true;

}

void Shader::update(Scene *scene)
{

	Camera *camera = scene->getPlayer()->getCamera();

    mat4 projectionMatrix = camera->getProjectionMatrix();
    mat4 viewMatrix = camera->getViewMatrix();
    mat4 viewProjectionMatrix = projectionMatrix * viewMatrix;

    setViewProjectionMatrix(viewProjectionMatrix);

}

void Shader::update(Model *model)
{

	mat4 modelMatrix = translate(mat4(), model->getPosition()) * mat4_cast(model->getRotation()) * glm::scale(mat4(), model->getScale());
	setModelMatrix(modelMatrix);

}

GLint Shader::getUniformLocation(string name)
{

	if(!programId)
		return -1;

	return glGetUniformLocation(programId, name.c_str());

}

void Shader::setViewProjectionMatrix(const mat4& viewProjectionMatrix)
{

    setMatrix4(viewProjectionMatrixId, 1, false, &viewProjectionMatrix[0][0]);

}


void Shader::setModelMatrix(const mat4& modelMatrix)
{

    setMatrix4(modelMatrixId, 1, false, &modelMatrix[0][0]);

}

void Shader::setActive(bool active)
{

	glUseProgram(active ? programId : 0);

	Application::instance()->getRenderingManager()->setActiveShader(active ? this : NULL);

}

void Shader::release()
{

	if(vertexShaderId)
	{

		glDetachShader(programId, vertexShaderId);
		glDeleteShader(vertexShaderId);
		vertexShaderId = 0;

	}

	if(tessellationControlShaderId)
	{

		glDetachShader(programId, tessellationControlShaderId);
		glDeleteShader(tessellationControlShaderId);
		tessellationControlShaderId = 0;

	}

	if(tessellationEvaluationShaderId)
	{

		glDetachShader(programId, tessellationEvaluationShaderId);
		glDeleteShader(tessellationEvaluationShaderId);
		tessellationEvaluationShaderId = 0;

	}


	if(fragmentShaderId)
	{

		glDetachShader(programId, fragmentShaderId);
		glDeleteShader(fragmentShaderId);
		fragmentShaderId = 0;

	}


	if(programId)
	{

		glDeleteShader(programId);
		programId = 0;

	}

}