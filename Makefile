##### Variables

ifeq ($(OS),Windows_NT)
    
	SRCDIR = src
	OBJDIR = obj
	INCDIR = -Isrc -Iinclude -Ivendor/glfw-3.0.4/include -Ivendor/glew-1.10.0/include -Ivendor/glm
	LIBDIR = -Lvendor/glfw-3.0.4/src -Lvendor/glew-1.10.0/lib
	CPPFLAGS = -g -Wall $(INCDIR) -DGLM_FORCE_RADIANS -DGLFW_STATIC
	LFLAGS = -lglfw3 -lGLEW -lopengl32 -lglu32 -lgdi32
	CC = g++ -mwin32

else
    
	SRCDIR = src
	OBJDIR = obj
	INCDIR = -Isrc -Iinclude -Ivendor/glfw-3.0.4/include -I/usr/local/Cellar/glew/1.11.0/include -Ivendor/glm -Ivendor/physx/include
	LIBDIR = -Lvendor/glfw-3.0.4/src -L/usr/local/Cellar/glew/1.11.0/lib -Lvendor/physx/lib/osx64
	CPPFLAGS = -g -Wall $(INCDIR) -DGLFW_STATIC
	LFLAGS = -framework IOKit -framework Cocoa -framework OpenGL -framework QuartzCore -lglfw3 -lGLEW -lPhysX3CommonDEBUG -lPhysX3DEBUG -lPhysX3CookingDEBUG -lPhysX3ExtensionsDEBUG -lPhysXProfileSDKDEBUG -lPhysX3VehicleDEBUG -lPhysx3CharacterKinematicDEBUG -lPvdRuntimeDEBUG -lSimulationControllerDEBUG -lLowLevelClothDEBUG -lSceneQueryDEBUG -lLowLevelDEBUG -lPxTaskDEBUG -lPhysXVisualDebuggerSDKDEBUG
	CC = g++

endif

##### Files

SOURCES = $(wildcard $(SRCDIR)/*.cpp)
SRCFILES = $(patsubst $(SRCDIR)/%,%,$(SOURCES))
DEPENDENCIES = $(patsubst $(SRCDIR)/%,$(OBJDIR)/%,$(SOURCES:.cpp=.o))
OBJTEMP = $(patsubst $(SRCDIR)/%,$(OBJDIR)/%,$(SOURCES))
OBJECTS = $(patsubst %.cpp,%.o,$(OBJTEMP))
TARGET = bin/main

##### Build rules

run: all
	cd bin && ./main

all: $(DEPENDENCIES)
	$(CC) $(CPPFLAGS) $(LIBDIR) $(OBJECTS) $(LFLAGS) -o $(TARGET)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CC) $(CPPFLAGS) -c -o $(OBJDIR)/$*.o $(SRCDIR)/$*.cpp

depend:
	gcc -E -MM $(CPPFLAGS) $(SOURCES) | sed 's|[a-zA-Z0-9_-]*\.o|$(OBJDIR)/&|' > deps.d

clean:
	@rm -rf $(TARGET) $(TARGET).exe $(OBJDIR)/*.o *.bak *~ *%
	
memtest:
	valgrind --tool=memcheck --leak-check=full --show-reachable=yes ./main

include deps.d