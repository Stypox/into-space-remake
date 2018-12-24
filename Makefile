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
CXXINCLUDE = -I$(LIBS_PATH)arg-parser/include \
	-I$(LIBS_PATH)file-management/include \
	-I$(LIBS_PATH)glad/include \
	-I$(LIBS_PATH)gl-abstractions/include \
	-I$(LIBS_PATH)stock-container/include \
	-I$(LIBS_PATH)imgui -I$(LIBS_PATH)imgui/examples
CXXFLAGS := -Wall -std=c++17 $(CXXINCLUDE)
CXXLIBS = -lstdc++fs -lGL -lGLU -lglfw3 -lX11 -lXxf86vm -lXrandr -lpthread -lXi -ldl -lXinerama -lXcursor -lSOIL


# generated files
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
$(APP)application.o: $(APP)application.h $(APP)application.cpp $(APP)arguments.o $(APP)event/handler.o $(APP)input/keys.o $(APP)input/scroll.o $(APP)input/mousemove.o $(REND)renderer.o $(APP)debug.o
	$(CXX) $(CXXFLAGS) -c $(APP)application.cpp -o $(APP)application.o
$(APP)arguments.o: $(APP)arguments.h $(APP)arguments.cpp $(APP)debug.o
	$(CXX) $(CXXFLAGS) -c $(APP)arguments.cpp -o $(APP)arguments.o
$(APP)debug.o: $(APP)debug.h $(APP)debug.cpp
	$(CXX) $(CXXFLAGS) -c $(APP)debug.cpp -o $(APP)debug.o

# src/app/event/
$(APP)event/event.o: $(APP)event/event.h $(APP)event/event.cpp
	$(CXX) $(CXXFLAGS) -c $(APP)event/event.cpp -o $(APP)event/event.o
$(APP)event/key.h: $(APP)event/event.o
$(APP)event/scroll.h: $(APP)event/event.o
$(APP)event/mousemove.h: $(APP)event/event.o
$(APP)event/handler.o: $(APP)event/handler.h $(APP)event/handler.cpp $(APP)event/event.o
	$(CXX) $(CXXFLAGS) -c $(APP)event/handler.cpp -o $(APP)event/handler.o

# src/app/input/
$(APP)input/keys.o: $(APP)input/keys.h $(APP)input/keys.cpp $(APP)event/key.h $(APP)event/event.o $(APP)event/handler.o
	$(CXX) $(CXXFLAGS) -c $(APP)input/keys.cpp -o $(APP)input/keys.o
$(APP)input/scroll.o: $(APP)input/scroll.h $(APP)input/scroll.cpp $(APP)event/scroll.h $(APP)event/event.o $(APP)event/handler.o
	$(CXX) $(CXXFLAGS) -c $(APP)input/scroll.cpp -o $(APP)input/scroll.o
$(APP)input/mousemove.o: $(APP)input/mousemove.h $(APP)input/mousemove.cpp $(APP)event/mousemove.h $(APP)event/event.o $(APP)event/handler.o
	$(CXX) $(CXXFLAGS) -c $(APP)input/mousemove.cpp -o $(APP)input/mousemove.o

# src/game
$(GAME)game.o: $(GAME)game.h $(GAME)game.cpp $(GAME)entitiescontainer.h $(REND)items.o $(REND)movables.o $(GAME)world/world.o
	$(CXX) $(CXXFLAGS) -c $(GAME)game.cpp -o $(GAME)game.o
$(GAME)entitiescontainer.h: $(GAME)ent/item.o $(GAME)ent/mov/rocket.o

# src/game/ent
$(GAME)ent/entity.o: $(GAME)ent/entity.h $(GAME)ent/entity.cpp $(REND)shared.h
	$(CXX) $(CXXFLAGS) -c $(GAME)ent/entity.cpp -o $(GAME)ent/entity.o
$(GAME)ent/item.o: $(GAME)ent/item.h $(GAME)ent/item.cpp $(GAME)ent/entity.o $(LIBS_PATH)stock-container/include/stypox/stock_container.h
	$(CXX) $(CXXFLAGS) -c $(GAME)ent/item.cpp -o $(GAME)ent/item.o

# src/game/ent/mov
$(GAME)ent/mov/movable.o: $(GAME)ent/mov/movable.h $(GAME)ent/mov/movable.cpp $(GAME)ent/entity.o $(LIBS_PATH)stock-container/include/stypox/stock_container.h
	$(CXX) $(CXXFLAGS) -c $(GAME)ent/mov/movable.cpp -o $(GAME)ent/mov/movable.o
$(GAME)ent/mov/rocket.o: $(GAME)ent/mov/rocket.h $(GAME)ent/mov/rocket.cpp $(GAME)ent/mov/movable.o $(MISC)acceleration.o $(LIBS_PATH)stock-container/include/stypox/stock_container.h
	$(CXX) $(CXXFLAGS) -c $(GAME)ent/mov/rocket.cpp -o $(GAME)ent/mov/rocket.o

# src/game/world
$(GAME)world/chunk.o: $(GAME)world/chunk.h $(GAME)world/chunk.cpp $(GAME)ent/entity.o $(GAME)ent/item.o $(APP)arguments.o $(MISC)random.o
	$(CXX) $(CXXFLAGS) -c $(GAME)world/chunk.cpp -o $(GAME)world/chunk.o
$(GAME)world/world.o: $(GAME)world/world.h $(GAME)world/world.cpp $(GAME)world/chunk.o
	$(CXX) $(CXXFLAGS) -c $(GAME)world/world.cpp -o $(GAME)world/world.o

# src/rend
$(REND)renderer.o: $(REND)renderer.h $(REND)renderer.cpp
	$(CXX) $(CXXFLAGS) -c $(REND)renderer.cpp -o $(REND)renderer.o
$(REND)items.o: $(REND)items.h $(REND)items.cpp $(REND)shared.h $(REND)renderer.o $(GAME)ent/item.o $(APP)arguments.o $(LIBS_PATH)stock-container/include/stypox/stock_container.h
	$(CXX) $(CXXFLAGS) -c $(REND)items.cpp -o $(REND)items.o
$(REND)movables.o: $(REND)movables.h $(REND)movables.cpp $(REND)shared.h $(REND)renderer.o $(GAME)ent/mov/movable.o $(APP)arguments.o $(LIBS_PATH)stock-container/include/stypox/stock_container.h
	$(CXX) $(CXXFLAGS) -c $(REND)movables.cpp -o $(REND)movables.o

# src/misc
$(MISC)random.o: $(MISC)random.h $(MISC)random.cpp
	$(CXX) $(CXXFLAGS) -c $(MISC)random.cpp -o $(MISC)random.o
$(MISC)frequency.o: $(MISC)frequency.h $(MISC)frequency.cpp $(MISC)clock.h
	$(CXX) $(CXXFLAGS) -c $(MISC)frequency.cpp -o $(MISC)frequency.o
$(MISC)acceleration.o: $(MISC)acceleration.h $(MISC)acceleration.cpp $(MISC)clock.h
	$(CXX) $(CXXFLAGS) -c $(MISC)acceleration.cpp -o $(MISC)acceleration.o
$(MISC)get_current_monitor.o: $(MISC)get_current_monitor.h $(MISC)get_current_monitor.cpp
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
	