
# Project structure
SRCDIR = src
INCDIR = src/include
OBJDIR = obj
BINDIR = bin


# Compiler flags
CC = gcc
CPPFLAGS = -MMD
CFLAGS = -Wall -Wextra -pedantic -std=gnu2x -I$(INCDIR)
LDFLAGS = -fsanitize=address -ggdb
LDLIBS =



# Source files
SRC = $(shell find $(SRCDIR) -maxdepth 1 -type f -name "*.c")
HDR = $(shell find $(INCDIR) -maxdepth 1 -type f -name "*.h")

# Object files
OBJ = $(patsubst $(SRCDIR)/%, $(OBJDIR)/%, $(SRC:.c=.o))

# Prerequisities
DEP = $(OBJ:.o=.d)

# Targets
TARGET = rubiks_helper



# Rules

all: $(TARGET)

-include $(DEP)

$(TARGET): $(OBJ)
	@mkdir -p $(BINDIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) $(LDFLAGS) $(LDLIBS) $^ -o $(BINDIR)/$(TARGET)


$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) $(LDFLAGS) $(LDLIBS) $< -c -o $@


.PHONY: clean all

clean:
	$(RM) -r $(OBJDIR) $(BINDIR)
