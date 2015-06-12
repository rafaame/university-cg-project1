#include "Shader.h"	

using namespace std;

Shader::Shader()
{



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

GLuint Shader::createShader(GLenum type, string code)
{

	GLuint shaderId = glCreateShader(type);
	const char *tmpCode = code.c_str();

	glShaderSource(shaderId, 1, &tmpCode, nullptr);
	
	cout << "Compiling " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment")  << " shader... ";
	glCompileShader(shaderId);

	GLint success, maxLength;
	glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);

	if(success != GL_NO_ERROR)
	{

		cout << "error" << endl;

		glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &maxLength);
	 
		vector<GLchar> errorLog(maxLength);
		glGetShaderInfoLog(shaderId, maxLength, &maxLength, &errorLog[0]);

		for(auto it = errorLog.begin(); it != errorLog.end(); it++)
			cout << (*it);

		cout << endl;

	}
	else
		cout << "compiled" << endl;

	return shaderId;

}

bool Shader::init(string vertexShaderFilename, string fragmentShaderFilename)
{
		
	if(!vertexShaderFilename.length() || !fragmentShaderFilename.length())
		return false;

	if(vertexShaderId || fragmentShaderId || programId)
		release();
	
	string vertexShaderCode = readFromFile(vertexShaderFilename);
	string fragmentShaderCode = readFromFile(fragmentShaderFilename);
	
	vertexShaderId = createShader(GL_VERTEX_SHADER, vertexShaderCode);
	fragmentShaderId = createShader(GL_FRAGMENT_SHADER, fragmentShaderCode);
	
	programId = glCreateProgram();
	glAttachShader(programId, vertexShaderId);
	glAttachShader(programId, fragmentShaderId);
	glLinkProgram(programId);
	
	GLenum error = glGetError();
	
	if(error != GL_NO_ERROR)
	{
		
		cout << "Could not create the shader program (errorId: " << error << ")" << endl;
		
		return false;

	}

	return true;

}

GLint Shader::getUniformLocation(string name)
{

	if(!programId)
		return -1;
	
	return glGetUniformLocation(programId, name.c_str());

}

void Shader::setActive(bool active)
{

	glUseProgram(active ? programId : 0);

}

void Shader::release()
{
	
	if(vertexShaderId)
	{

		glDetachShader(programId, vertexShaderId);
		glDeleteShader(vertexShaderId);
		vertexShaderId = 0;

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