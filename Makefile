CXX := g++
CPPFLAGS := -Wall
LIBS := -lsfml-graphics -lsfml-window -lsfml-system
LDFLAGS := $(LIBS)
SRCEXT := cpp
HEADEREXT := h
OBJDIR := obj
SRCDIR := src
TARGET := life

SOURCES := $(shell find  $(SRCDIR) -type f -name '*.$(SRCEXT)')
HEADERS := $(shell find  $(SRCDIR) -type f -name '*.$(HEADEREXT)')
OBJECTS := $(patsubst $(SRCDIR)/%, $(OBJDIR)/%, $(SOURCES:.$(SRCEXT)=.o))


all: $(TARGET)

clean:
	@echo "Cleaning..."
	rm -rf $(OBJDIR) $(TARGET)

$(TARGET): $(OBJECTS)
	@echo "Linking" $(TARGET) "..."
	$(CXX) $(CPPFLAGS) $^ -o $(TARGET) $(LDFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.$(SRCEXT) $(HEADERS)
	@echo "Compiling" $@ "..."
	@mkdir -p $(OBJDIR)
	$(CXX) $(CPPFLAGS) -c -o $@ $<

.PHONY: all, clean
