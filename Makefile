CXX 		?= g++
CXXFLAGS 	?= -Wall -Wextra -Werror -O2
BUILDDIR	?= build

SRCDIR		:= src
PROGRAM		:= sudoku
TARGET		:= $(BUILDDIR)/$(PROGRAM)

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

debug: $(BUILDDIR)/debug

$(BUILDDIR)/debug: $(SRCS)
	$(CXX) $(CXXFLAGS) -g $^ -o $@

clean:
	$(RM) $(BUILDDIR)/*.o
	$(RM) $(TARGET)
	$(RM) $(BUILDDIR)/debug
