CXX = clang++
CXXFLAGS = -Wall -std=c++17 -O3 -MMD

EXES = ex1 ex2 ex3 ex4 ex5

all: $(EXES)

# Matches any target in your EXES list (e.g. ex1)
$(EXES): %:
	$(CXX) $(CXXFLAGS) -o $@ $(wildcard $**.cc)

# Auto-include headers (tracks changes to your .h files)
-include $(wildcard *.d)

# Cleanup
clean:
	rm -f $(EXES) *.d
