CC := g++

SRCDIR = src
BUILDDIR = build
BINDIR = bin
INCLUDEDIR = include
TESTDIR = tests
TARGET = bin/main
SRCEXT := cpp

CFLAGS = -g -Wall -Wextra -pedantic -Weffc++
LIB = -L lib
INC = -I include

SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))


$(TARGET): $(OBJECTS)
	@mkdir -p $(BINDIR)
	@echo " Linking..."
	@echo $(SOURCES)
	@echo $(OBJECTS)
	@echo " $(CC) $^ -o $(TARGET) $(LIB)"; $(CC) $^ -o $(TARGET) $(LIB)


$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(BUILDDIR)
	@echo " $(CC) $(CFLAGS) $(INC) -c -o $@ $<"; $(CC) $(CFLAGS) $(INC) -c -o $@ $<


clean:
	@echo "Cleaning."
	$(RM) -r $(BUILDDIR) $(BINDIR) $(TARGET)


tests: $(filter-out build/main.o, $(OBJECTS))
	@mkdir -p $(BINDIR)
	@echo " $(CC) $(CFLAGS) $(INC) $(LIB) -c -o $(BUILDDIR)/test.o $(TESTDIR)/tester.cpp"; $(CC) $(CFLAGS) $(INC) $(LIB) -c -o $(BUILDDIR)/test.o $(TESTDIR)/tester.cpp
	@echo " $(CC) $^ $(BUILDDIR)/test.o -o $(BINDIR)/test"; $(CC) $^ $(BUILDDIR)/test.o -o $(BINDIR)/test

.PHONY: clean