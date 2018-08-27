# stypox libraries include path
STYPOX_INCLUDE_PATH_FILE = stypoxincludepath.txt
READFILE := $(if $(filter $(OS),Windows_NT),type,cat)
# if this doesn't work just replace the following line with: STYPOX = path/to/include/stypox
STYPOX := $(shell $(READFILE) $(STYPOX_INCLUDE_PATH_FILE))

# compiler options and settings
CXX = g++
CXXFLAGS := -Wall -g -std=c++17 -I$(STYPOX)
CXXLIBS = -lstdc++fs -lGLEW -lGL -lGLU -lglfw3 -lX11 -lXxf86vm -lXrandr -lpthread -lXi -ldl -lXinerama -lXcursor -lSOIL

# source code paths
SRC = ./into-space-remake/src/
GL := $(STYPOX)gl-abstractions/
APP := $(SRC)app/

EXECUTABLE_NAME := IntoSpaceRemake$(if $(filter $(OS),Windows_NT), .exe,)
OBJECT_FILES = main.o application.o fileManagement.o ebo.o shader.o texture.o vao.o vbo.o

# executable
$(EXECUTABLE_NAME): $(OBJECT_FILES)
	$(CXX) $(CXXFLAGS) -o $(EXECUTABLE_NAME) $(OBJECT_FILES) $(CXXLIBS)


# main
main.o: $(SRC)main.cpp
	$(CXX) $(CXXFLAGS) -c $(SRC)main.cpp


# application
application.o: $(APP)application.h $(APP)application.cpp
	$(CXX) $(CXXFLAGS) -c $(APP)application.cpp 


# includes from stypox libraries: fileManagement
fileManagement.o: $(STYPOX)fileManagement.h $(STYPOX)fileManagement.cpp
	$(CXX) $(CXXFLAGS) -c $(STYPOX)fileManagement.cpp


# includes from stypox libraries: gl-abstractions
ebo.o: $(GL)ebo.h $(GL)ebo.cpp
	$(CXX) $(CXXFLAGS) -c $(GL)ebo.cpp

shader.o: $(GL)shader.h $(GL)shader.cpp
	$(CXX) $(CXXFLAGS) -c $(GL)shader.cpp

texture.o: $(GL)texture.h $(GL)texture.cpp
	$(CXX) $(CXXFLAGS) -c $(GL)texture.cpp

vao.o: $(GL)vao.h $(GL)vao.cpp
	$(CXX) $(CXXFLAGS) -c $(GL)vao.cpp

vbo.o: $(GL)vbo.h $(GL)vbo.cpp
	$(CXX) $(CXXFLAGS) -c $(GL)vbo.cpp


# remove all .o files
clean:
	rm ./*.o
	