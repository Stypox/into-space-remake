# command to read file
READFILE := $(if $(filter $(OS),Windows_NT),type,cat)

# stypox libraries include path
STYPOX_INCLUDE_PATH_FILE = stypoxincludepath.txt
# if this doesn't work just replace the following line with: STYPOX = path/to/include/stypox/
STYPOX := $(shell $(READFILE) $(STYPOX_INCLUDE_PATH_FILE))
$(info Using stypox include path: $(STYPOX))

# glad include path
GLAD_INCLUDE_PATH_FILE = gladpath.txt
# if this doesn't work just replace the following line with: GLAD = path/to/glad/
GLAD := $(shell $(READFILE) $(GLAD_INCLUDE_PATH_FILE))
$(info Using glad include path: $(GLAD))

# compiler options and settings
CXX = g++
CXXFLAGS := -Wall -g -std=c++17 -I$(STYPOX) -I$(GLAD)include/
CXXLIBS = -lstdc++fs -lGL -lGLU -lglfw3 -lX11 -lXxf86vm -lXrandr -lpthread -lXi -ldl -lXinerama -lXcursor -lSOIL

# source code paths
SRC = ./into-space-remake/src/
STYPOX_GL := $(STYPOX)gl-abstractions/
APP := $(SRC)app/
GAME := $(SRC)game/
RENDER := $(SRC)render/

EXECUTABLE_NAME := IntoSpaceRemake$(if $(filter $(OS),Windows_NT), .exe,)
OBJECT_FILES = main.o \
	app_application.o app_arguments.o \
		app_event_event.o app_event_handler.o \
		app_input_keys.o app_input_scroll.o app_input_mousemove.o \
	\
		game_entity_entity.o game_entity_item.o \
	render_renderer.o render_items.o \
	glad_glad.o \
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
app_application.o: $(APP)application.h $(APP)application.cpp app_arguments.o app_event_handler.o app_input_keys.o app_input_scroll.o app_input_mousemove.o render_items.o
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
app_input_keys.o: $(APP)input/keys.h $(APP)input/keys.cpp $(APP)event/key.h app_event_event.o app_event_handler.o
	$(CXX) $(CXXFLAGS) -c $(APP)input/keys.cpp -o app_input_keys.o

# src/app/input/scroll.cpp
app_input_scroll.o: $(APP)input/scroll.h $(APP)input/scroll.cpp $(APP)event/scroll.h app_event_event.o app_event_handler.o
	$(CXX) $(CXXFLAGS) -c $(APP)input/scroll.cpp -o app_input_scroll.o

# src/app/input/mousemove.cpp
app_input_mousemove.o: $(APP)input/mousemove.h $(APP)input/mousemove.cpp $(APP)event/mousemove.h app_event_event.o app_event_handler.o
	$(CXX) $(CXXFLAGS) -c $(APP)input/mousemove.cpp -o app_input_mousemove.o

# src/game

# src/game/entity

# src/game/entity/entity.cpp
game_entity_entity.o: $(GAME)entity/entity.h $(GAME)entity/entity.cpp $(RENDER)shared.h
	$(CXX) $(CXXFLAGS) -c $(GAME)entity/entity.cpp -o game_entity_entity.o

# src/game/entity/item.cpp
game_entity_item.o: $(GAME)entity/item.h $(GAME)entity/item.cpp game_entity_entity.o
	$(CXX) $(CXXFLAGS) -c $(GAME)entity/item.cpp -o game_entity_item.o

# src/render

# src/render/renderer.cpp
render_renderer.o: $(RENDER)renderer.h $(RENDER)renderer.cpp
	$(CXX) $(CXXFLAGS) -c $(RENDER)renderer.cpp -o render_renderer.o

# src/render/items.cpp
render_items.o: $(RENDER)items.h $(RENDER)items.cpp $(RENDER)shared.h game_entity_item.o stypox_gl_ebo.o stypox_gl_shader.o stypox_gl_texture.o stypox_gl_vao.o stypox_gl_vbo.o
	$(CXX) $(CXXFLAGS) -c $(RENDER)items.cpp -o render_items.o



# glad_path/src/glad/
glad_glad.o: $(GLAD)include/glad/glad.h $(GLAD)src/glad.c
	$(CXX) $(CXXFLAGS) -c $(GLAD)src/glad.c -o glad_glad.o




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
	