CXX      = g++ -std=c++17
CXXFLAGS = -c -Wall
LD       = $(CXX)
LDFLAGS  = -Wall

ROOTDIR := .
OBJDIR  := obj
BINDIR  := bin
SRCDIR  := src
INCDIR  := inc

LIBPF_DIR = /home/jonapoul/repos/libpf

LIBS := $(LIBPF_DIR)/libPF.a \
		  -lfolly -lpthread -lssl -lcrypto -llzma -lz -lsnappy -llz4 -liberty -ljemalloc -levent -ldouble-conversion -lglog -lgflags

INC  = -I. \
       -I$(INCDIR) \
       -I$(LIBPF_DIR)

SRC := $(wildcard $(SRCDIR)/*.cpp)
OBJ := $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SRC))

#g++ -std=c++11 -o echoserver EchoServer.cpp -O2 -lwangle -lfolly -lpthread -lssl -lgflags -lglog -lcrypto

EXEC = percolation

default: dir $(EXEC)

$(EXEC): $(OBJ) | dir
	$(LD) -o $(BINDIR)/$@ $(LDFLAGS) $(OBJ) $(LIBS)

dir:
	mkdir -p $(OBJDIR)
	mkdir -p $(BINDIR)

clean:
	rm -f $(OBJDIR)/*   2>/dev/null || true
	rm -f $(BINDIR)/*   2>/dev/null || true
	rm -f $(SRCDIR)/*.o 2>/dev/null || true

diff:
	git diff --stat

rebuild: clean $(EXEC)

update:
	git pull

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | dir
	$(CXX) $(CXXFLAGS) $(INC) -c $< -o $@