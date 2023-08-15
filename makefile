NAME=gassets
TARGET := lib$(NAME).a
BUILDDIR := build
SOURCEDIR := src
HEADERS_INSTALL_DIR := include
CC := g++

ifeq ($(PREFIX),)
	PREFIX := /usr/local
endif

SOURCES := $(shell find $(SOURCEDIR) -name "*.cpp")
OBJECTS := $(patsubst $(SOURCEDIR)/%, $(BUILDDIR)/%, $(SOURCES:.cpp=.o))
HEADERS_INSTALL := $(shell find $(HEADERS_INSTALL_DIR) -name "*.h")

# compiler flags
COMPILER_FLAGS := -std=gnu++20

all: $(TARGET)

$(TARGET): $(OBJECTS)
	@mkdir -p $(dir $@)
	ar rcs $@ $^

$(BUILDDIR)/%.o: $(SOURCEDIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CC) $(COMPILER_FLAGS) -c $< -o $@

install: $(TARGET)
	install -d $(DESTDIR)$(PREFIX)/lib/
	install -m 644 $(TARGET) $(DESTDIR)$(PREFIX)/lib/
	install -d $(DESTDIR)$(PREFIX)/include/$(NAME)/
	install -m 644 $(HEADERS_INSTALL) $(DESTDIR)$(PREFIX)/include/$(NAME)/

.PHONY: clean
clean:
	rm -rf $(BUILDDIR) $(TARGET)


