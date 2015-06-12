#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>										
#include <stdlib.h>	

#include <iostream>
#include <sstream>
#include <fstream>

#include <vector>

#include <chrono>
#include <thread>

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>									
#include <glm/gtc/matrix_transform.hpp>					
#include <glm/gtx/transform2.hpp>

#define FOURCC_DXT1 0x31545844 // Equivalent to "DXT1" in ASCII
#define FOURCC_DXT3 0x33545844 // Equivalent to "DXT3" in ASCII
#define FOURCC_DXT5 0x35545844 // Equivalent to "DXT5" in ASCII

#define PI 3.14159265358979323846264338327950288

#endif