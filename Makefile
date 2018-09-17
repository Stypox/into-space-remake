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
REND := $(SRC)rend/
MISC := $(SRC)misc/

EXECUTABLE_NAME := IntoSpaceRemake$(if $(filter $(OS),Windows_NT), .exe,)
OBJECT_FILES = main.o \
	app_application.o app_arguments.o app_debug.o \
		app_event_event.o app_event_handler.o \
		app_input_keys.o app_input_scroll.o app_input_mousemove.o \
	game_game.o \
		game_ent_entity.o game_ent_item.o \
			game_ent_mov_movable.o game_ent_mov_rocket.o \
		game_world_chunk.o \
	rend_renderer.o rend_items.o rend_movables.o \
	misc_random.o misc_frequency.o \
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
app_application.o: $(APP)application.h $(APP)application.cpp app_arguments.o app_event_handler.o app_input_keys.o app_input_scroll.o app_input_mousemove.o rend_renderer.o app_debug.o
	$(CXX) $(CXXFLAGS) -c $(APP)application.cpp -o app_application.o

# src/app/arguments.cpp
app_arguments.o: $(APP)arguments.h $(APP)arguments.cpp app_debug.o
	$(CXX) $(CXXFLAGS) -c $(APP)arguments.cpp -o app_arguments.o

# src/app/debug.cpp
app_debug.o: $(APP)debug.h $(APP)debug.cpp
	$(CXX) $(CXXFLAGS) -c $(APP)debug.cpp -o app_debug.o

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

# src/game/game.cpp
game_game.o: $(GAME)game.h $(GAME)game.cpp $(GAME)entitiescontainer.h rend_items.o rend_movables.o
	$(CXX) $(CXXFLAGS) -c $(GAME)game.cpp -o game_game.o

# src/game/ent

# src/game/ent/entity.cpp
game_ent_entity.o: $(GAME)ent/entity.h $(GAME)ent/entity.cpp $(REND)shared.h
	$(CXX) $(CXXFLAGS) -c $(GAME)ent/entity.cpp -o game_ent_entity.o

# src/game/ent/item.cpp
game_ent_item.o: $(GAME)ent/item.h $(GAME)ent/item.cpp game_ent_entity.o
	$(CXX) $(CXXFLAGS) -c $(GAME)ent/item.cpp -o game_ent_item.o

# src/game/ent/mov

# src/game/ent/mov/movable.cpp
game_ent_mov_movable.o: $(GAME)ent/mov/movable.h $(GAME)ent/mov/movable.cpp game_ent_entity.o
	$(CXX) $(CXXFLAGS) -c $(GAME)ent/mov/movable.cpp -o game_ent_mov_movable.o

# src/game/ent/mov/rocket.cpp
game_ent_mov_rocket.o: $(GAME)ent/mov/rocket.h $(GAME)ent/mov/rocket.cpp game_ent_mov_movable.o
	$(CXX) $(CXXFLAGS) -c $(GAME)ent/mov/rocket.cpp -o game_ent_mov_rocket.o

# src/game/world

# src/game/world/chunk.cpp
game_world_chunk.o: $(GAME)world/chunk.h $(GAME)world/chunk.cpp game_ent_entity.o game_ent_item.o app_arguments.o misc_random.o
	$(CXX) $(CXXFLAGS) -c $(GAME)world/chunk.cpp -o game_world_chunk.o

# src/rend

# src/rend/renderer.cpp
rend_renderer.o: $(REND)renderer.h $(REND)renderer.cpp
	$(CXX) $(CXXFLAGS) -c $(REND)renderer.cpp -o rend_renderer.o

# src/rend/items.cpp
rend_items.o: $(REND)items.h $(REND)items.cpp $(REND)shared.h rend_renderer.o game_ent_item.o stypox_gl_ebo.o stypox_gl_shader.o stypox_gl_texture.o stypox_gl_vao.o stypox_gl_vbo.o app_arguments.o
	$(CXX) $(CXXFLAGS) -c $(REND)items.cpp -o rend_items.o

# src/rend/movables.cpp
rend_movables.o: $(REND)movables.h $(REND)movables.cpp $(REND)shared.h rend_renderer.o game_ent_mov_movable.o stypox_gl_ebo.o stypox_gl_shader.o stypox_gl_texture.o stypox_gl_vao.o stypox_gl_vbo.o app_arguments.o
	$(CXX) $(CXXFLAGS) -c $(REND)movables.cpp -o rend_movables.o

# src/misc

# src/misc/random.h
misc_random.o: $(MISC)random.h $(MISC)random.cpp
	$(CXX) $(CXXFLAGS) -c $(MISC)random.cpp -o misc_random.o

# src/misc/random.h
misc_frequency.o: $(MISC)frequency.h $(MISC)frequency.cpp $(MISC)clock.h
	$(CXX) $(CXXFLAGS) -c $(MISC)frequency.cpp -o misc_frequency.o



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
	