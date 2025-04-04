CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic
LDFLAGS =

SRC_DIR = src
EXTERNAL_DIR = external
BUILD_DIR = build
BIN_DIR = bin

IMGUI_DIR = $(EXTERNAL_DIR)/imgui
IMGUI_SRCS = $(wildcard $(IMGUI_DIR)/*.cpp) $(wildcard $(IMGUI_DIR)/backends/*.cpp)
IMGUI_OBJS = $(patsubst $(EXTERNAL_DIR)/%.cpp,$(BUILD_DIR)/external/%.o,$(IMGUI_SRCS))

TARGET = $(BIN_DIR)/engine_simulator

SRCS = $(shell find $(SRC_DIR) -name "*.cpp")
OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRCS))

INCLUDES = -I$(SRC_DIR) -I$(EXTERNAL_DIR) -I$(IMGUI_DIR)

LIBS = -lglfw -lvulkan -ldl -lpthread -lX11 -lXxf86vm -lXrandr -lXi

.PHONY: all clean debug release

all: debug

debug: CXXFLAGS += -g -DDEBUG
debug: prepare $(TARGET)

release: CXXFLAGS += -O3 -DNDEBUG
release: prepare $(TARGET)

prepare:
	@mkdir -p $(BIN_DIR)
	@mkdir -p $(dir $(OBJS))
	@mkdir -p $(BUILD_DIR)/external/imgui/backends

$(TARGET): $(OBJS) $(IMGUI_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS) $(LIBS)
	@echo "Build successful! Executable is at $(TARGET)"

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c -o $@ $<

$(BUILD_DIR)/external/%.o: $(EXTERNAL_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c -o $@ $<

clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)

-include $(OBJS:.o=.d)
-include $(IMGUI_OBJS:.o=.d)

$(BUILD_DIR)/%.d: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	@set -e; rm -f $@; \
	$(CXX) -MM $(CXXFLAGS) $(INCLUDES) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,$(BUILD_DIR)/\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$