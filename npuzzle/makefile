SRCS = $(shell find . -name "*.cpp") 

OBJS = $(addsuffix .o, $(basename $(SRCS)))

EXEC = npuzzle

CXXFLAGS = -O3

$(EXEC): $(OBJS)
	$(CXX) -o $@ $^ $(CXXFLAGS) $(LIBS)

%.o: %.cpp
	$(CXX) -c $< -o $@ $(CXXFLAGS) $(LIBS)

clean:
	rm -f $(OBJS) $(EXEC)