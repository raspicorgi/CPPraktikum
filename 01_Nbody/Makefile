# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++11 -Wall

# Source files
SRC = main.cpp \
      lib/Body.cpp \
      lib/Euler_Cromer.cpp \
      lib/Euler.cpp \
      lib/Hermite.cpp \
      lib/Integrator.cpp \
      lib/Tools.cpp \
      lib/Vector3d.cpp \
      lib/Velocity_Verlet.cpp

# Object files
OBJ = $(SRC:.cpp=.o)

# Executable name
EXEC = nbody_simulation

# Default target
all: $(EXEC)

# Link object files to create the executable
$(EXEC): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile source files into object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -f $(OBJ) $(EXEC)

.PHONY: all clean