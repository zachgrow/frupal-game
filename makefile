# 2020/01/16
# Authors: Josiah Baldwin, Zach Grow

# Automatic variables
# These are not defined by the user; they are automatic substitutions
#	VAR		NOTES
#	=======	======
#	$@		The filename of the rule's target (everything before the :)
#	$<		The name of the first prerequisite
#	$^		The names of all prerequisites
#	$?		The names of all prerequisites newer than the target

# Common flags for C++
# -std=		Compile for specified C++ standard
# -Wall		Display all warnings
# -g		Activate debugging symbols for use in GDB
# -c		Compile the source into objects but do not link them
# -I		Specify additional directories to be searched when including files

# Custom variables
# Note that variables can be recursively defined by using $(foo) in the def:
# 	ALPHA = foo
#	BETA  = $(ALPHA)

TARGET=frupalGame
SRCDIR=src
OBJDIR=src
# All files named src/*.hpp are headers
HEDS=$(wildcard src/*.hpp)
# All files names src/*.cpp are source files
SRCS=$(wildcard src/*.cpp)
# The object files live next to the source files, with a different extension
OBJS=$(SRCS:.cpp=.o)
# Specifies the path to any external libraries we will include when compiling
INCLUDE=./include

# ! Allow the user's environment to specify the value of CXX! If make says it cannot be found, check your environment variables to ensure it is set correctly.
CXXFLAGS=-I$(INCLUDE) -std=c++11 -Wall -g
# WARNING
# These linker flags are HIGHLY OS dependent! Proper OS detection should be
# implemented so that the program will compile under either system.
# These linker flags are meant for Linux x64:
LDFLAGS=-lBearLibTerminal -L lib/BearLibTerminal/Linux64 -Wl,-rpath="lib/BearLibTerminal/Linux64"
#LDFLAGS=-lBearLibTerminal -L. -Wl,-rpath=.
# End of Linux_x64 flags

# Make targets
# If all the objects are up to date, recompile the binary
$(TARGET):	$(OBJS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $^ -o $@

# If any of the objects are out of date, recompile them
$(OBJDIR)/%.o:	$(SRCDIR)/%.cpp
	$(CXX) $< -c $(CXXFLAGS) -o $@

# Force an explicit (re)compilation of the entire project
all: 
	$(CXX) $(SRCS) $(CXXFLAGS) $(LDFLAGS) -o $(TARGET)

# the .PHONY rule specifies a 'fake' target, ie for tasks other than compiles,
# or for situations where there is no actual file to connect to the rule
# any phony rule should continue despite errors, such as with rm
.PHONY: clean

# this rule should NEVER be first, or else make will invoke it by default!
# also note: if this rule were not phony, then it would work correctly UNTIL
# a file named 'clean' existed in the working directory!
clean:	#cleans up the working dir
	rm -rf $(OBJDIR)/*.o $(NAME)
