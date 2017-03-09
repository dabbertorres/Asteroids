CXX    := g++
CFLAGS := --std=c++14 -Wall -Wextra

LIBS := -lsfml-system -lsfml-graphics -lsfml-window

RLS_FLAGS := -O2
DBG_FLAGS := -DDEBUG -O0 -g

OUT       := Asteroids
BUILD_DIR := build

SRC := $(wildcard *.cpp)
OBJ := $(SRC:%.cpp=%.o)
DEP := $(OBJ:%.o=%.d)

release: $(OUT_DIR)/release/$(OUT)
debug: $(OUT_DIR)/debug/$(OUT)

$(OUT_DIR)/release/$(OUT): $(addprefix $(BUILD_DIR)/release/,$(OBJ))
	$(CXX) $(CFLAGS) $(RLS_FLAGS) $(LIBS) $^ -o $@

$(OUT_DIR)/debug/$(OUT): $(addprefix $(BUILD_DIR)/debug/,$(OBJ))
	$(CXX) $(CFLAGS) $(DBG_FLAGS) $(LIBS) $^ -o $@

# generate dependencies
-include $(BUILD_DIR)$(DEP)

# object files rule
# each object file should have a corresponding .cpp file
# "-MMD" tells the compiler to generate a dependency file for the input
$(BUILD_DIR)/release/%.o : %.cpp
	@mkdir -p $(@D)
	$(CXX) $(CFLAGS) $(RLS_FLAGS) -MMD -c $^ -o $@

$(BUILD_DIR)/debug/%.o : %.cpp
	@mkdir -p $(@D)
	$(CXX) $(CFLAGS) $(DBG_FLAGS) -MMD -c $^ -o $@

.PHONY clean:
	@rm -rf $(BUILD_DIR)

