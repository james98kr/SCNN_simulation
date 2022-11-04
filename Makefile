TOP_EXE := scnn
CC := g++
CPP_SUFFIX := cpp
CPP_PROTO_SUFFIX := pb.cpp
SRC_DIR := ./src
CFLAGS := -std=c++11 -Wno-unused-value
# CFLAGS := -W -Wall -g -std=c++11

SRC	= $(wildcard $(SRC_DIR)/*.$(CPP_SUFFIX))
SRC += $(wildcard $(SRC_DIR)/**/*.$(CPP_SUFFIX))

.SILENT: all

all:
	$(CC) $(CFLAGS) $(SRC) -o $(TOP_EXE)