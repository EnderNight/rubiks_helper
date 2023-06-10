
# Project structure
SRCDIR = src
INCDIR = src/include
OBJDIR = obj
BINDIR = bin


# Compiler flags
CXX = g++
CXXFLAGS = -MMD
CFLAGS = -Wall -Wextra -pedantic -std=c++20 -I$(INCDIR)
LDFLAGS = -fsanitize=address -ggdb
LDLIBS =



# Source files
SRC = $(shell find $(SRCDIR) -maxdepth 1 -type f -name "*.cpp")
HDR = $(shell find $(INCDIR) -maxdepth 1 -type f -name "*.h")

# Object files
OBJ = $(patsubst $(SRCDIR)/%, $(OBJDIR)/%, $(SRC:.cpp=.o))

# Targets
TARGET = rubiks_helper



# Rules

all: $(TARGET)

$(TARGET): $(OBJ)
	@mkdir -p $(BINDIR)
	$(CXX) $(CXXFLAGS) $(CFLAGS) $(LDFLAGS) $(LDLIBS) $^ -o $(BINDIR)/$(TARGET)


$(OBJDIR)/%.o: $(SRCDIR)/%.cpp $(HDR)
	@mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) $(CFLAGS) $(LDFLAGS) $(LDLIBS) $< -c -o $@


.PHONY: clean all

clean:
	$(RM) -r $(OBJDIR) $(BINDIR)
