CXX      := g++
CXXFLAGS := -std=c++17 -O2 -Wall -Wextra -Wpedantic

TARGETS  := fixed_rate_loop jitter_measure

.PHONY: all clean

all: $(TARGETS)

fixed_rate_loop: fixed_rate_loop.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^

jitter_measure: jitter_measure.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -f $(TARGETS)
