BUILD_DIR := ./build
OBJ_DIR := $(BUILD_DIR)/obj
SRC_DIR := ./src
INC_DIR := ./inc
LIBS := -lprotobuf -lpthread #-lcpr 

PCH_FILENAME = $(SRC_DIR)/server.h
PCH = $(SRC_DIR)/$(PCH_FILENAME).gch

EXECUTABLE := server

HEADERS := $(shell find $(INC_DIR) -name '*.h')
SRCS := $(shell find $(SRC_DIR) -name '*.cpp' -or -name '*.c' -or -name '*.s')
OBJS := $(SRCS:%=$(OBJ_DIR)/%.o)
DEPS := $(OBJS:.o=.d)


CPPFLAGS := $(INC_FLAGS) -MMD -MP
CXXFLAGS += -std=c++17

$(BUILD_DIR)/$(EXECUTABLE): $(PCH) $(OBJS)
	@echo "Linking..."
	$(CXX) $(OBJS) $(LIBS) -o $@ $(LDFLAGS)

$(OBJ_DIR)/%.cpp.o: %.cpp
	@echo "Compiling sources..."
	mkdir -p $(dir $@)
	$(CXX) $(CPPFLAGS) -w $(CXXFLAGS) -I $(INC_DIR) -I $(SRC_DIR) -g -c $< -o $@

$(PCH): $(HEADERS)
	@echo "Building Precompiled Header..."
	$(CXX) $(CXXFLAGS) -w -I $(INC_DIR) -I $(SRC_DIR) -x c++-header $(PCH_FILENAME)

.PHONY: clean
clean:
	rm -r $(BUILD_DIR)
