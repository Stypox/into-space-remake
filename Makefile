# source code paths
SRC = ./into-space-remake/src/
LIBS_PATH = libs/
STYPOX_GL := $(STYPOX)gl-abstractions/
APP := $(SRC)app/
GAME := $(SRC)game/
REND := $(SRC)rend/
MISC := $(SRC)misc/

# compiler options and settings
CXX = g++
CXXINCLUDE = \
	-I$(LIBS_PATH)arg-parser/include \
	-I$(LIBS_PATH)event-notifier/include \
	-I$(LIBS_PATH)file-management/include \
	-I$(LIBS_PATH)glad/include \
	-I$(LIBS_PATH)gl-abstractions/include \
	-I$(LIBS_PATH)stock-container/include \
	-I$(LIBS_PATH)imgui -I$(LIBS_PATH)imgui/examples
CXXFLAGS := -Wall -std=c++17 $(CXXINCLUDE)
CXXLIBS = -lstdc++fs -lGL -lGLU -lglfw3 -lX11 -lXxf86vm -lXrandr -lpthread -lXi -ldl -lXinerama -lXcursor -lSOIL


# generated files
EXECUTABLE_NAME := IntoSpaceRemake$(if $(filter $(OS),Windows_NT), .exe,)
OBJECT_FILES = \
	$(SRC)main.o \
	$(APP)application.o $(APP)arguments.o $(APP)debug.o \
		$(APP)input/keys.o $(APP)input/scroll.o $(APP)input/mousemove.o \
	$(GAME)game.o \
		$(GAME)ent/entity.o $(GAME)ent/item.o $(GAME)ent/cloud.o \
			$(GAME)ent/mov/rocket.o \
		$(GAME)world/world.o $(GAME)world/chunk.o \
	$(REND)renderer.o $(REND)items.o $(REND)rectangles.o \
	$(MISC)random.o $(MISC)frequency.o $(MISC)acceleration.o $(MISC)get_current_monitor.o \
	$(LIBS_PATH)glad/src/glad.o \
	$(LIBS_PATH)imgui/imgui.o $(LIBS_PATH)imgui/imgui_demo.o $(LIBS_PATH)imgui/imgui_draw.o $(LIBS_PATH)imgui/imgui_widgets.o \
		$(LIBS_PATH)imgui/examples/imgui_impl_glfw.o $(LIBS_PATH)imgui/examples/imgui_impl_opengl3.o
OBJECT_FILES_GENERATED_BY_LIBS = $(LIBS_PATH)file-management/file_management.o $(LIBS_PATH)gl-abstractions/gl_abstractions.o

# Let corresponding Makefiles decide which files should be recompiled, if any. 
.PHONY: $(OBJECT_FILES_GENERATED_BY_LIBS)


# targets
release: release_print $(EXECUTABLE_NAME)
release_print:
	$(info Compiling release version)

debug: CXXFLAGS += -g -DDEBUG
debug: debug_print $(EXECUTABLE_NAME)	
debug_print:
	$(info Compiling debug version)

# arguments
VERBOSE := $(VERBOSE)
ifneq (,$(filter $(VERBOSE), true 1))
$(info Running $(CXX) with -v flag (verbose))
CXXFLAGS += -v
else
ifneq ($(VERBOSE),)
$(error Invalid VERBOSE value: "$(VERBOSE)" (valid values: "true" "1"))
endif
endif


# executable
$(EXECUTABLE_NAME): $(OBJECT_FILES) $(OBJECT_FILES_GENERATED_BY_LIBS)
	$(CXX) $(CXXFLAGS) -o $(EXECUTABLE_NAME) $(OBJECT_FILES) $(OBJECT_FILES_GENERATED_BY_LIBS) $(CXXLIBS)

# src/
$(SRC)main.o: $(SRC)main.cpp $(APP)application.o
	$(CXX) $(CXXFLAGS) -c $(SRC)main.cpp -o $(SRC)main.o

# src/app/
$(APP)application.hpp: $(MISC)frequency.hpp $(APP)input/keys.hpp $(APP)input/mousemove.hpp $(APP)input/scroll.hpp $(GAME)game.hpp
$(APP)application.o: $(APP)application.hpp $(APP)application.cpp $(APP)arguments.hpp $(APP)debug.hpp $(REND)renderer.hpp $(MISC)get_current_monitor.hpp
	$(CXX) $(CXXFLAGS) -c $(APP)application.cpp -o $(APP)application.o
$(APP)arguments.hpp: $(APP)debug.hpp
$(APP)arguments.o: $(APP)arguments.hpp $(APP)arguments.cpp
	$(CXX) $(CXXFLAGS) -c $(APP)arguments.cpp -o $(APP)arguments.o
$(APP)debug.hpp: $(APP)arguments.hpp
$(APP)debug.o: $(APP)debug.hpp $(APP)debug.cpp
	$(CXX) $(CXXFLAGS) -c $(APP)debug.cpp -o $(APP)debug.o

# src/app/event/
$(APP)event/key.hpp: $(APP)input/key.hpp
$(APP)event/scroll.hpp:
$(APP)event/mousemove.hpp:

# src/app/input/
$(APP)input/key.hpp:
$(APP)input/keys.hpp: $(APP)input/key.hpp $(APP)event/key.hpp
$(APP)input/keys.o: $(APP)input/keys.hpp $(APP)input/keys.cpp
	$(CXX) $(CXXFLAGS) -c $(APP)input/keys.cpp -o $(APP)input/keys.o
$(APP)input/scroll.hpp:
$(APP)input/scroll.o: $(APP)input/scroll.hpp $(APP)input/scroll.cpp $(APP)event/scroll.hpp
	$(CXX) $(CXXFLAGS) -c $(APP)input/scroll.cpp -o $(APP)input/scroll.o
$(APP)input/mousemove.hpp:
$(APP)input/mousemove.o: $(APP)input/mousemove.hpp $(APP)input/mousemove.cpp $(APP)event/mousemove.hpp
	$(CXX) $(CXXFLAGS) -c $(APP)input/mousemove.cpp -o $(APP)input/mousemove.o

# src/game
$(GAME)game.hpp: $(GAME)world/world.hpp $(MISC)clock.hpp
$(GAME)game.o: $(GAME)game.hpp $(GAME)game.cpp $(APP)event/key.hpp $(APP)debug.hpp 
	$(CXX) $(CXXFLAGS) -c $(GAME)game.cpp -o $(GAME)game.o
$(GAME)entitiescontainer.hpp: $(GAME)ent/item.hpp $(GAME)ent/mov/rocket.hpp $(GAME)ent/cloud.hpp

# src/game/ent
$(GAME)ent/entity.hpp:
$(GAME)ent/entity.o: $(GAME)ent/entity.hpp $(GAME)ent/entity.cpp
	$(CXX) $(CXXFLAGS) -c $(GAME)ent/entity.cpp -o $(GAME)ent/entity.o
$(GAME)ent/item.hpp: $(GAME)ent/entity.hpp $(REND)items.hpp
$(GAME)ent/item.o: $(GAME)ent/item.hpp $(GAME)ent/item.cpp
	$(CXX) $(CXXFLAGS) -c $(GAME)ent/item.cpp -o $(GAME)ent/item.o
$(GAME)ent/cloud.hpp: $(GAME)ent/entity.hpp $(REND)rectangles.hpp
$(GAME)ent/cloud.o: $(GAME)ent/cloud.hpp $(GAME)ent/cloud.cpp $(MISC)random.hpp
	$(CXX) $(CXXFLAGS) -c $(GAME)ent/cloud.cpp -o $(GAME)ent/cloud.o

# src/game/ent/mov
$(GAME)ent/mov/movable.hpp: $(GAME)ent/entity.hpp
$(GAME)ent/mov/rocket.hpp: $(GAME)ent/mov/movable.hpp $(GAME)ent/item.hpp $(GAME)ent/cloud.hpp $(MISC)acceleration.hpp
$(GAME)ent/mov/rocket.o: $(GAME)ent/mov/rocket.hpp $(GAME)ent/mov/rocket.cpp $(APP)event/key.hpp
	$(CXX) $(CXXFLAGS) -c $(GAME)ent/mov/rocket.cpp -o $(GAME)ent/mov/rocket.o

# src/game/world
$(GAME)world/chunk.hpp:
$(GAME)world/chunk.o: $(GAME)world/chunk.hpp $(GAME)world/chunk.cpp $(MISC)random.hpp $(APP)arguments.hpp
	$(CXX) $(CXXFLAGS) -c $(GAME)world/chunk.cpp -o $(GAME)world/chunk.o
$(GAME)world/world.hpp: $(GAME)world/chunk.hpp $(GAME)ent/mov/rocket.hpp
$(GAME)world/world.o: $(GAME)world/world.hpp $(GAME)world/world.cpp
	$(CXX) $(CXXFLAGS) -c $(GAME)world/world.cpp -o $(GAME)world/world.o

# src/rend
$(REND)shared.hpp:
$(REND)renderer.hpp:
$(REND)renderer.o: $(REND)renderer.hpp $(REND)renderer.cpp $(REND)items.hpp $(REND)rectangles.hpp
	$(CXX) $(CXXFLAGS) -c $(REND)renderer.cpp -o $(REND)renderer.o
$(REND)items.hpp:
$(REND)items.o: $(REND)items.hpp $(REND)items.cpp $(REND)shared.hpp $(REND)renderer.hpp $(APP)arguments.hpp $(GAME)ent/item.hpp
	$(CXX) $(CXXFLAGS) -c $(REND)items.cpp -o $(REND)items.o
$(REND)rectangles.hpp:
$(REND)rectangles.o: $(REND)rectangles.hpp $(REND)rectangles.cpp $(REND)shared.hpp $(REND)renderer.hpp $(APP)arguments.hpp
	$(CXX) $(CXXFLAGS) -c $(REND)rectangles.cpp -o $(REND)rectangles.o

# src/misc
$(MISC)random.hpp:
$(MISC)random.o: $(MISC)random.hpp $(MISC)random.cpp
	$(CXX) $(CXXFLAGS) -c $(MISC)random.cpp -o $(MISC)random.o
$(MISC)clock.hpp:
$(MISC)frequency.hpp: $(MISC)clock.hpp
$(MISC)frequency.o: $(MISC)frequency.hpp $(MISC)frequency.cpp
	$(CXX) $(CXXFLAGS) -c $(MISC)frequency.cpp -o $(MISC)frequency.o
$(MISC)acceleration.hpp:
$(MISC)acceleration.o: $(MISC)acceleration.hpp $(MISC)acceleration.cpp
	$(CXX) $(CXXFLAGS) -c $(MISC)acceleration.cpp -o $(MISC)acceleration.o
$(MISC)get_current_monitor.hpp:
$(MISC)get_current_monitor.o: $(MISC)get_current_monitor.hpp $(MISC)get_current_monitor.cpp
	$(CXX) $(CXXFLAGS) -c $(MISC)get_current_monitor.cpp -o $(MISC)get_current_monitor.o


# libs/glad
$(LIBS_PATH)glad/src/glad.o: $(LIBS_PATH)glad/include/glad/glad.h $(LIBS_PATH)glad/src/glad.c
	$(CXX) $(CXXFLAGS) -c $(LIBS_PATH)glad/src/glad.c -o $(LIBS_PATH)glad/src/glad.o

# libs/gl-abstractions
$(LIBS_PATH)gl-abstractions/gl_abstractions.o:
	cd $(LIBS_PATH)gl-abstractions/ && make GLAD_PATH=../glad

# libs/file-management
$(LIBS_PATH)file-management/file_management.o:
	cd $(LIBS_PATH)file-management/ && make

# libs/imgui
$(LIBS_PATH)imgui/imgui.o:
	$(CXX) $(CXXFLAGS) -c $(LIBS_PATH)imgui/imgui.cpp -o $(LIBS_PATH)imgui/imgui.o
$(LIBS_PATH)imgui/imgui_demo.o:
	$(CXX) $(CXXFLAGS) -c $(LIBS_PATH)imgui/imgui_demo.cpp -o $(LIBS_PATH)imgui/imgui_demo.o
$(LIBS_PATH)imgui/imgui_draw.o:
	$(CXX) $(CXXFLAGS) -c $(LIBS_PATH)imgui/imgui_draw.cpp -o $(LIBS_PATH)imgui/imgui_draw.o
$(LIBS_PATH)imgui/imgui_widgets.o:
	$(CXX) $(CXXFLAGS) -c $(LIBS_PATH)imgui/imgui_widgets.cpp -o $(LIBS_PATH)imgui/imgui_widgets.o

# libs/imgui/examples
$(LIBS_PATH)imgui/examples/imgui_impl_glfw.o:
	$(CXX) $(CXXFLAGS) -c $(LIBS_PATH)imgui/examples/imgui_impl_glfw.cpp -o $(LIBS_PATH)imgui/examples/imgui_impl_glfw.o
$(LIBS_PATH)imgui/examples/imgui_impl_opengl3.o:
	$(CXX) $(CXXFLAGS) -DIMGUI_IMPL_OPENGL_LOADER_GLAD -c $(LIBS_PATH)imgui/examples/imgui_impl_opengl3.cpp -o $(LIBS_PATH)imgui/examples/imgui_impl_opengl3.o


clean:
	rm $(OBJECT_FILES)
	cd $(LIBS_PATH)gl-abstractions/ && make clean
	cd $(LIBS_PATH)file-management/ && make clean
	