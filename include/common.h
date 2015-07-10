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
#include <glm/gtx/quaternion.hpp>

#define MAGICKCORE_QUANTUM_DEPTH 16
#define MAGICKCORE_HDRI_ENABLE 0
#include "Magick++.h"

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

#define NDEBUG
#define PX_DEBUG
//#define PX_SUPPORT_VISUAL_DEBUGGER
#include "PxPhysicsAPI.h"

#define INVALID_UNIFORM_LOCATION 0xFFFFFFFF
#define ARRAY_SIZE_IN_ELEMENTS(a) (sizeof(a)/sizeof(a[0]))
#define ToRadian(x) (float)(((x) * M_PI / 180.0f))
#define ToDegree(x) (float)(((x) * 180.0f / M_PI))

#define PI 3.14159265358979323846264338327950288

#endif