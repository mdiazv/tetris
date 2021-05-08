
CXX := g++
CXXFLAGS := -std=c++17 -g -Wall -MMD -MP

TARGET := tetris
SRCS := $(shell find . -name "*.cpp")
OBJS := $(addsuffix .o, $(basename $(SRCS)))
DEPS := $(OBJS:.o=.d)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(OBJS) -o tetris $(LDLIBS)

.PHONY: clean
clean:
	$(RM) $(TARGET) $(OBJS) $(DEPS)

-include $(DEPS)
