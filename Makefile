CC ?= clang
CXX ?= clang++
LD ?= ld

BUILD_DIR ?= build

EXE_PATH ?= $(BUILD_DIR)/game

SOURCES = main.cpp
C_INCLUDES = $(wildcard include/*.cpp) $(wildcard include/*.c)
INCLUDE = -I./dependencies/GLEW/include -I./dependencies/GLFW/include -I./dependencies/GLM -I./dependencies/IMGUI -I./dependencies/STB/include
CFLAGS = 
LDFLAGS = -lGLEW -lglfw
ifeq ($(shell uname -s),Darwin)
LDFLAGS += -framework OpenGL
else
LDFLAGS += -lGL -lGLU -lglm
endif

IMGUI_SRC = dependencies/IMGUI/imgui/imgui_impl_glfw_gl3.cpp dependencies/IMGUI/imgui/imgui_draw.cpp dependencies/IMGUI/imgui/imgui.cpp
IMGUI_OBJ = $(patsubst dependencies/IMGUI/imgui/%,$(BUILD_DIR)/imgui/%, $(patsubst %.cpp,%.o,$(IMGUI_SRC)))

.PHONY: all clean

all: $(EXE_PATH)
clean:
	rm -rf $(BUILD_DIR)

test:
	@echo $(IMGUI_OBJ)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)/imgui

build/imgui/%.o: dependencies/IMGUI/imgui/%.cpp | $(BUILD_DIR)
	$(CXX) $(CFLAGS) $(INCLUDE) -c -o $@ $<

$(EXE_PATH): $(SOURCES) $(IMGUI_OBJ) $(C_INCLUDES) | $(BUILD_DIR)
	$(CXX) $(CFLAGS) $(INCLUDE) $(SOURCES) $(IMGUI_OBJ) $(LDFLAGS) -o $(EXE_PATH)