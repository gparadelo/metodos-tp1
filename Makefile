CXXFLAGS= -std=c++11 -pedantic -Wall -O3

all: pagerank

pagerank: main.cpp matrix.cpp matrix.h
	g++ -o $@ $^ $(CXXFLAGS)