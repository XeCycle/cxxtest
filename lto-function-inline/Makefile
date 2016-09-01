CXXFLAGS += -std=c++11 -O3 -flto -fdevirtualize-at-ltrans

main: main.cc a.o b.o
a.o: a.cc vfunction.hh
b.o: b.cc vfunction.hh
