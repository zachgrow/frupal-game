# 2020/01/16

TARGET=frupal
CCXX=g++
CXXFLAGS=-g
LDFLAGS=

all: $(TARGET)

clean:
	rm .*.o $(TARGET)


$(TARGET): # args go here
	$(CCXX) $(CXXFLAGS) $(LDFLAGS) $^ -o $@

# .objects.o: file.cpp headers...
#	$(CXX) $(CXXFLAGS) -c $< -o $@
