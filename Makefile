# stypox libraries include path
STYPOX_INCLUDE_PATH_FILE = stypoxincludepath.txt
READFILE := $(if $(filter $(OS),Windows_NT),type,cat)
# if this doesn't work just replace the following line with: STYPOX = path/to/include/stypox
STYPOX := $(shell $(READFILE) $(STYPOX_INCLUDE_PATH_FILE))

# Compiler options and settings
CXX = g++
CXXFLAGS := -Wall -g -std=c++17 -I$(STYPOX)
CXXLIBS = -lstdc++fs -lGLEW -lGL -lGLU -lglfw3 -lX11 -lXxf86vm -lXrandr -lpthread -lXi -ldl -lXinerama -lXcursor -lSOIL

SRC = ./into-space-remake/src/
GL := $(STYPOX)gl-abstractions/
OBJ = ./

EXECUTABLE_NAME := $(if $(filter $(OS),Windows_NT), IntoSpaceRemake.exe, IntoSpaceRemake)

#executable dependencies
$(EXECUTABLE_NAME): main.o fileManagement.o ebo.o shader.o texture.o vao.o vbo.o
	$(CXX) $(CXXFLAGS) -o $(EXECUTABLE_NAME) main.o fileManagement.o ebo.o shader.o texture.o vao.o vbo.o $(CXXLIBS)


#main
main.o: $(SRC)main.cpp
	$(CXX) $(CXXFLAGS) -c $(SRC)main.cpp


#includes from stypox libraries: fileManagement
fileManagement.o: $(STYPOX)fileManagement.h $(STYPOX)fileManagement.cpp
	$(CXX) $(CXXFLAGS) -c $(STYPOX)fileManagement.cpp


#includes from stypox libraries: gl-abstractions
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




#cleaning
clean:
	rm $(OBJ)*.o
	