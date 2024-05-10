CC = gcc

SRCDIR = src
INCDIR = include
BUILDDIR = build

EXECUTABLE = graph

SOURCES = $(wildcard $(SRCDIR)/*.c)
OBJECTS = $(patsubst $(SRCDIR)/%.c,$(BUILDDIR)/objects/%.o,$(SOURCES))
INCLUDES = -I$(INCDIR)

CFLAGS = -Wall -Wextra -lGL -lglfw -lGLEW -lX11 -lXi -lpthread -lXrandr -ldl -lm

all: $(BUILDDIR)/$(EXECUTABLE)

$(BUILDDIR)/$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o $@

$(BUILDDIR)/objects/%.o: $(SRCDIR)/%.c | $(BUILDDIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(BUILDDIR):
	mkdir -p $(BUILDDIR); mkdir $(BUILDDIR)/objects

clean:
	rm -rf $(BUILDDIR)

.PHONY: all clean
