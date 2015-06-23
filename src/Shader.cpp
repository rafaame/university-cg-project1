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

void Shader::compileShader(GLuint shaderId, GLenum type, string code)
{

	const char *codePointer = code.c_str();
	glShaderSource(shaderId, 1, &codePointer, NULL);
	
	cout << "Compiling " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment")  << " shader... ";
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

bool Shader::init(string vertexShaderFilename, string fragmentShaderFilename)
{
		
	if(!vertexShaderFilename.length() || !fragmentShaderFilename.length())
		return false;

	if(vertexShaderId || fragmentShaderId || programId)
		release();
	
	string vertexShaderCode = readFromFile(vertexShaderFilename);
	string fragmentShaderCode = readFromFile(fragmentShaderFilename);

	vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
	fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
	
	compileShader(vertexShaderId, GL_VERTEX_SHADER, vertexShaderCode);
	compileShader(fragmentShaderId, GL_FRAGMENT_SHADER, fragmentShaderCode);
	
	programId = glCreateProgram();
	glAttachShader(programId, vertexShaderId);
	glAttachShader(programId, fragmentShaderId);
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