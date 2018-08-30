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
STYPOX_GL := $(STYPOX)gl-abstractions/
APP := $(SRC)app/

EXECUTABLE_NAME := IntoSpaceRemake$(if $(filter $(OS),Windows_NT), .exe,)
OBJECT_FILES = main.o \
	app_application.o app_arguments.o \
		app_event_event.o app_event_handler.o \
		app_input_keys.o \
	stypox_fileManagement.o \
	stypox_gl_ebo.o stypox_gl_shader.o stypox_gl_texture.o stypox_gl_vao.o stypox_gl_vbo.o

# executable
$(EXECUTABLE_NAME): $(OBJECT_FILES)
	$(CXX) $(CXXFLAGS) -o $(EXECUTABLE_NAME) $(OBJECT_FILES) $(CXXLIBS)

# src/

# src/main.cpp
main.o: $(SRC)main.cpp app_application.o
	$(CXX) $(CXXFLAGS) -c $(SRC)main.cpp -o main.o

# src/app/

# src/app/application.cpp
app_application.o: $(APP)application.h $(APP)application.cpp app_arguments.o
	$(CXX) $(CXXFLAGS) -c $(APP)application.cpp -o app_application.o

# src/app/arguments.cpp
app_arguments.o: $(APP)arguments.h $(APP)arguments.cpp
	$(CXX) $(CXXFLAGS) -c $(APP)arguments.cpp -o app_arguments.o

# src/app/event/

# src/app/event/event.cpp
app_event_event.o: $(APP)event/event.h $(APP)event/event.cpp
	$(CXX) $(CXXFLAGS) -c $(APP)event/event.cpp -o app_event_event.o

# src/app/event/handler.cpp
app_event_handler.o: $(APP)event/handler.h $(APP)event/handler.cpp app_event_event.o
	$(CXX) $(CXXFLAGS) -c $(APP)event/handler.cpp -o app_event_handler.o

# src/app/input/

# src/app/input/keys.cpp
app_input_keys.o: $(APP)input/keys.h $(APP)input/keys.cpp app_event_event.o app_event_handler.o $(APP)event/key.h $(APP)event/mouse.h
	$(CXX) $(CXXFLAGS) -c $(APP)input/keys.cpp -o app_input_keys.o


# stypox_libraries_path/

# stypox_libraries_path/fileManagement.cpp
stypox_fileManagement.o: $(STYPOX)fileManagement.h $(STYPOX)fileManagement.cpp
	$(CXX) $(CXXFLAGS) -c $(STYPOX)fileManagement.cpp -o stypox_fileManagement.o

# stypox_libraries_path/gl-abstractions/

# stypox_libraries_path/gl-abstractions/ebo.cpp
stypox_gl_ebo.o: $(STYPOX_GL)ebo.h $(STYPOX_GL)ebo.cpp
	$(CXX) $(CXXFLAGS) -c $(STYPOX_GL)ebo.cpp -o stypox_gl_ebo.o

# stypox_libraries_path/gl-abstractions/shader.cpp
stypox_gl_shader.o: $(STYPOX_GL)shader.h $(STYPOX_GL)shader.cpp
	$(CXX) $(CXXFLAGS) -c $(STYPOX_GL)shader.cpp -o stypox_gl_shader.o

# stypox_libraries_path/gl-abstractions/texture.cpp
stypox_gl_texture.o: $(STYPOX_GL)texture.h $(STYPOX_GL)texture.cpp
	$(CXX) $(CXXFLAGS) -c $(STYPOX_GL)texture.cpp -o stypox_gl_texture.o

# stypox_libraries_path/gl-abstractions/vao.cpp
stypox_gl_vao.o: $(STYPOX_GL)vao.h $(STYPOX_GL)vao.cpp
	$(CXX) $(CXXFLAGS) -c $(STYPOX_GL)vao.cpp -o stypox_gl_vao.o

# stypox_libraries_path/gl-abstractions/vbo.cpp
stypox_gl_vbo.o: $(STYPOX_GL)vbo.h $(STYPOX_GL)vbo.cpp
	$(CXX) $(CXXFLAGS) -c $(STYPOX_GL)vbo.cpp -o stypox_gl_vbo.o


# remove all .o files
clean:
	rm ./*.o
	