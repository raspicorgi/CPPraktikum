# Compiler
CXX = g++
# Compiler flags
CXXFLAGS = -std=c++11 -Wall
# Source files
SRC = main.cpp \
      lib/Vector3d.cpp \
      lib/Body.cpp \
      lib/Euler_Cromer.cpp \
      lib/Euler.cpp \
      lib/Hermite.cpp \
      lib/Integrator.cpp \
      lib/Tools.cpp \
      lib/Velocity_Verlet.cpp
# Build directory
BUILD_DIR = build
# Object files
OBJ = $(SRC:%.cpp=$(BUILD_DIR)/%.o)
# Executable name
EXEC = nbody_simulation
# Default target
all: $(EXEC)
# Link object files to create the executable
$(EXEC): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^
# Compile source files into object files
$(BUILD_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@
# Clean up build files
clean:
	rm -rf $(BUILD_DIR) $(EXEC)
.PHONY: all clean