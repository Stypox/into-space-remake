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
OBJECT_FILES = $(SRC)main.o \
	$(APP)application.o $(APP)arguments.o $(APP)debug.o \
		$(APP)event/event.o $(APP)event/handler.o \
		$(APP)input/keys.o $(APP)input/scroll.o $(APP)input/mousemove.o \
	$(GAME)game.o \
		$(GAME)ent/entity.o $(GAME)ent/item.o \
			$(GAME)ent/mov/movable.o $(GAME)ent/mov/rocket.o \
		$(GAME)world/world.o $(GAME)world/chunk.o \
	$(REND)renderer.o $(REND)items.o $(REND)movables.o \
	$(MISC)random.o $(MISC)frequency.o $(MISC)acceleration.o \
	glad_glad.o \
	stypox_fileManagement.o \
	stypox_gl_ebo.o stypox_gl_shader.o stypox_gl_texture.o stypox_gl_vao.o stypox_gl_vbo.o

# executable
$(EXECUTABLE_NAME): $(OBJECT_FILES)
	$(CXX) $(CXXFLAGS) -o $(EXECUTABLE_NAME) $(OBJECT_FILES) $(CXXLIBS)

# src/

# src/main.cpp
$(SRC)main.o: $(SRC)main.cpp $(APP)application.o
	$(CXX) $(CXXFLAGS) -c $(SRC)main.cpp -o $(SRC)main.o

# src/app/

# src/app/application.cpp
$(APP)application.o: $(APP)application.h $(APP)application.cpp $(APP)arguments.o $(APP)event/handler.o $(APP)input/keys.o $(APP)input/scroll.o $(APP)input/mousemove.o $(REND)renderer.o $(APP)debug.o
	$(CXX) $(CXXFLAGS) -c $(APP)application.cpp -o $(APP)application.o

# src/app/arguments.cpp
$(APP)arguments.o: $(APP)arguments.h $(APP)arguments.cpp $(APP)debug.o
	$(CXX) $(CXXFLAGS) -c $(APP)arguments.cpp -o $(APP)arguments.o

# src/app/debug.cpp
$(APP)debug.o: $(APP)debug.h $(APP)debug.cpp
	$(CXX) $(CXXFLAGS) -c $(APP)debug.cpp -o $(APP)debug.o

# src/app/event/

# src/app/event/event.cpp
$(APP)event/event.o: $(APP)event/event.h $(APP)event/event.cpp
	$(CXX) $(CXXFLAGS) -c $(APP)event/event.cpp -o $(APP)event/event.o

# src/app/event/key.h
$(APP)event/key.h: $(APP)event/event.o

# src/app/event/scroll.h
$(APP)event/scroll.h: $(APP)event/event.o

# src/app/event/mousemove.h
$(APP)event/mousemove.h: $(APP)event/event.o

# src/app/event/handler.cpp
$(APP)event/handler.o: $(APP)event/handler.h $(APP)event/handler.cpp $(APP)event/event.o
	$(CXX) $(CXXFLAGS) -c $(APP)event/handler.cpp -o $(APP)event/handler.o

# src/app/input/

# src/app/input/keys.cpp
$(APP)input/keys.o: $(APP)input/keys.h $(APP)input/keys.cpp $(APP)event/key.h $(APP)event/event.o $(APP)event/handler.o
	$(CXX) $(CXXFLAGS) -c $(APP)input/keys.cpp -o $(APP)input/keys.o

# src/app/input/scroll.cpp
$(APP)input/scroll.o: $(APP)input/scroll.h $(APP)input/scroll.cpp $(APP)event/scroll.h $(APP)event/event.o $(APP)event/handler.o
	$(CXX) $(CXXFLAGS) -c $(APP)input/scroll.cpp -o $(APP)input/scroll.o

# src/app/input/mousemove.cpp
$(APP)input/mousemove.o: $(APP)input/mousemove.h $(APP)input/mousemove.cpp $(APP)event/mousemove.h $(APP)event/event.o $(APP)event/handler.o
	$(CXX) $(CXXFLAGS) -c $(APP)input/mousemove.cpp -o $(APP)input/mousemove.o

# src/game

# src/game/game.cpp
$(GAME)game.o: $(GAME)game.h $(GAME)game.cpp $(GAME)entitiescontainer.h $(REND)items.o $(REND)movables.o $(GAME)world/world.o
	$(CXX) $(CXXFLAGS) -c $(GAME)game.cpp -o $(GAME)game.o

# src/game/entitiescontainer.h
$(GAME)entitiescontainer.h: $(GAME)ent/item.o $(GAME)ent/mov/rocket.o

# src/game/ent

# src/game/ent/entity.cpp
$(GAME)ent/entity.o: $(GAME)ent/entity.h $(GAME)ent/entity.cpp $(REND)shared.h
	$(CXX) $(CXXFLAGS) -c $(GAME)ent/entity.cpp -o $(GAME)ent/entity.o

# src/game/ent/item.cpp
$(GAME)ent/item.o: $(GAME)ent/item.h $(GAME)ent/item.cpp $(GAME)ent/entity.o
	$(CXX) $(CXXFLAGS) -c $(GAME)ent/item.cpp -o $(GAME)ent/item.o

# src/game/ent/mov

# src/game/ent/mov/movable.cpp
$(GAME)ent/mov/movable.o: $(GAME)ent/mov/movable.h $(GAME)ent/mov/movable.cpp $(GAME)ent/entity.o
	$(CXX) $(CXXFLAGS) -c $(GAME)ent/mov/movable.cpp -o $(GAME)ent/mov/movable.o

# src/game/ent/mov/rocket.cpp
$(GAME)ent/mov/rocket.o: $(GAME)ent/mov/rocket.h $(GAME)ent/mov/rocket.cpp $(GAME)ent/mov/movable.o $(MISC)acceleration.o
	$(CXX) $(CXXFLAGS) -c $(GAME)ent/mov/rocket.cpp -o $(GAME)ent/mov/rocket.o

# src/game/world

# src/game/world/chunk.cpp
$(GAME)world/chunk.o: $(GAME)world/chunk.h $(GAME)world/chunk.cpp $(GAME)ent/entity.o $(GAME)ent/item.o $(APP)arguments.o $(MISC)random.o
	$(CXX) $(CXXFLAGS) -c $(GAME)world/chunk.cpp -o $(GAME)world/chunk.o

# src/game/world/world.cpp
$(GAME)world/world.o: $(GAME)world/world.h $(GAME)world/world.cpp $(GAME)world/chunk.o
	$(CXX) $(CXXFLAGS) -c $(GAME)world/world.cpp -o $(GAME)world/world.o

# src/rend

# src/rend/renderer.cpp
$(REND)renderer.o: $(REND)renderer.h $(REND)renderer.cpp
	$(CXX) $(CXXFLAGS) -c $(REND)renderer.cpp -o $(REND)renderer.o

# src/rend/items.cpp
$(REND)items.o: $(REND)items.h $(REND)items.cpp $(REND)shared.h $(REND)renderer.o $(GAME)ent/item.o stypox_gl_ebo.o stypox_gl_shader.o stypox_gl_texture.o stypox_gl_vao.o stypox_gl_vbo.o $(APP)arguments.o
	$(CXX) $(CXXFLAGS) -c $(REND)items.cpp -o $(REND)items.o

# src/rend/movables.cpp
$(REND)movables.o: $(REND)movables.h $(REND)movables.cpp $(REND)shared.h $(REND)renderer.o $(GAME)ent/mov/movable.o stypox_gl_ebo.o stypox_gl_shader.o stypox_gl_texture.o stypox_gl_vao.o stypox_gl_vbo.o $(APP)arguments.o
	$(CXX) $(CXXFLAGS) -c $(REND)movables.cpp -o $(REND)movables.o

# src/misc

# src/misc/random.h
$(MISC)random.o: $(MISC)random.h $(MISC)random.cpp
	$(CXX) $(CXXFLAGS) -c $(MISC)random.cpp -o $(MISC)random.o

# src/misc/random.h
$(MISC)frequency.o: $(MISC)frequency.h $(MISC)frequency.cpp $(MISC)clock.h
	$(CXX) $(CXXFLAGS) -c $(MISC)frequency.cpp -o $(MISC)frequency.o

# src/misc/acceleration.h
$(MISC)acceleration.o: $(MISC)acceleration.h $(MISC)acceleration.cpp $(MISC)clock.h
	$(CXX) $(CXXFLAGS) -c $(MISC)acceleration.cpp -o $(MISC)acceleration.o



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
	rm $(OBJECT_FILES)
	