TARGET = bin/cpplox
SRCDIR = src
OBJDIR = obj
INCDIR = include
BINDIR = bin

CC = g++
CPPFLAGS = -g -Wall -I $(INCDIR)

# List of .cpp and .hpp sources
SOURCES = $(wildcard $(SRCDIR)/*.cpp)
HEADERS = $(wildcard $(INCDIR)/*.hpp)
OBJECTS = $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

$(TARGET): $(OBJECTS) | $(BINDIR)
	@$(CC) $(CPPFLAGS) $(OBJECTS) -o $@

$(OBJDIR)/%.o : $(SRCDIR)/%.cpp | $(OBJDIR)
	@$(CC) $(CPPFLAGS) -c $< -o $@

$(OBJDIR):
	@mkdir $@

$(BINDIR):
	@mkdir $@

ifeq ($(OS),Windows_NT)
run: $(TARGET)
	@$(TARGET)

clean:
	@RMDIR /s /q ${OBJDIR}
	@RMDIR /s /q ${BINDIR}
else
run: $(TARGET)
	@./$(TARGET)

clean:
	@rm -rf $(OBJDIR) $(BINDIR)
endif