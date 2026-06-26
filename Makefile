CXX 		?= g++
CXXFLAGS 	?= -Wall -Wextra -Werror -O2
BUILDDIR	?= build

ifeq ($(OS),Windows_NT)
	EXE_EXT := .exe
else
	EXE_EXT :=
endif

SRCDIR		:= src
PROGRAM		:= sudoku$(EXE_EXT)
TARGET		:= $(BUILDDIR)/$(PROGRAM)

DEBUGTARGET := $(BUILDDIR)/debug$(EXE_EXT)

SRCS := $(wildcard $(SRCDIR)/*.cpp)
OBJS := $(SRCS:$(SRCDIR)/%.cpp=$(BUILDDIR)/%.o)

.PHONY: all clean debug $(PROGRAM)

$(PROGRAM): $(TARGET)

all: $(PROGRAM) debug

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -s $^ -o $@

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp | $(BUILDDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILDDIR):
	@mkdir -p $(BUILDDIR)

debug: $(DEBUGTARGET)

$(DEBUGTARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) -g $^ -o $@

clean:
	$(RM) $(BUILDDIR)/*.o
	$(RM) $(TARGET)
	$(RM) $(BUILDDIR)/debug
