SHELL := /bin/bash

USER_DIR:=
ifeq ($(shell uname),Darwin) #if using a Mac
  ifeq ($(shell hostname -s),Xudongs-MacBook-Pro)                 #if using my MBP laptop
  export PATH := /usr/local/opt/coreutils/libexec/gnubin:$(PATH)  # have to have this for shuf
  USER_DIR:=/Users/xudong
  else ifeq ($(shell hostname -s),CIS-3211-64950)                 #if using my office desktop
  export PATH := /usr/local/opt/coreutils/libexec/gnubin:$(PATH)  # have to have this for shuf
  USER_DIR:=/Users/n01237497
  endif
else ifeq ($(shell uname),Linux) #if using Ubuntu
  ifeq ($(shell hostname -s),cisvm-xudong-1) #if using CIS virtual machine 1
  USER_DIR:=/home/xudong
  else ifeq ($(shell hostname -s),cisvm-xudong-2) #if using CIS virtual machine 2
  USER_DIR:=/home/xudong
  else ifeq ($(shell hostname -s),xudong-ThinkPad-T410)    #if using my Thinkpad
  USER_DIR:=/home/xudong
  else ifeq ($(shell hostname -s),kestrel)   #if using UKY CSR machine
  USER_DIR:=/homes/liu
  endif
endif

# Determine the platform for portability.
UNAME := $(shell uname)

INSTANCES_DIR = instances

ifneq (,$(findstring CYGWIN,$(UNAME)))
OUTPUT_DIR = out/gcccygwin64
else ifeq ($(UNAME),Darwin)
OUTPUT_DIR = out/gccdarwin64
else
OUTPUT_DIR = out/gcclinux64
endif

INCLUDE_DIR = . $(USER_DIR)/pybind11/include
SRC_DIR = ./src
SRC_FILES = $(filter-out %_binder.cpp, $(wildcard $(SRC_DIR)/*.cpp))
SRCBINDER_FILES = $(filter %_binder.cpp, $(wildcard $(SRC_DIR)/*.cpp))
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp, $(OUTPUT_DIR)/%.o, $(SRC_FILES))
SO_FILES := $(patsubst $(SRC_DIR)/%_binder.cpp, $(OUTPUT_DIR)/%.so, $(SRCBINDER_FILES))

# Conventions suggest an overall INCLUDE_FLAGS.
INCLUDE_FLAGS := $(addprefix -I,$(INCLUDE_DIR))

CXXFLAGS := -O3 -shared -std=c++11 `python-config --cflags --ldflags` -fPIC

all: make_dir $(SO_FILES)

.PHONY: make_dir
make_dir:
	mkdir -p $(OUTPUT_DIR)

$(SO_FILES): $(OUTPUT_DIR)/%.so : $(SRC_DIR)/%_binder.cpp $(SRC_FILES)
	$(CXX) $(CXXFLAGS) $(INCLUDE_FLAGS) $^ -o $@
