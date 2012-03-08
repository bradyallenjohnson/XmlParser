SHELL=/bin/bash
CC=/usr/bin/g++
DELETE_CMD=/bin/rm -f
COPY_CMD=/bin/cp

LIBRARY_PATH=-L. -L/home/ebrjohn/projects/CString -L/home/ebrjohn/bin/expat/lib
INCLUDE_PATH=-I. -I/home/ebrjohn/projects/CString -I/home/ebrjohn/bin/expat/include
INSTALL_DIR=/home/ebrjohn/lib

CCFLAGS=-g -fPIC
LDFLAGS=-shared
OBJ_EXTENSION=.o

LIB_NAME=libXmlParser.so
OBJS=XmlUtils$(OBJ_EXTENSION) XmlParser$(OBJ_EXTENSION) XmlParserExpatImpl$(OBJ_EXTENSION)

#
# Targets
#

all: $(LIB_NAME) $(OBJS)

$(LIB_NAME): $(OBJS)
	$(CC) $(CCFLAGS) $(LDFLAGS) $(LIBRARY_PATH) -o $(LIB_NAME) $(OBJS)

XmlUtils$(OBJ_EXTENSION): XmlUtils.cpp
	$(CC) $(CCFLAGS) $(INCLUDE_PATH) -c XmlUtils.cpp -o XmlUtils$(OBJ_EXTENSION)

XmlParser$(OBJ_EXTENSION): XmlParser.cpp
	$(CC) $(CCFLAGS) $(INCLUDE_PATH) -c XmlParser.cpp -o XmlParser$(OBJ_EXTENSION)

XmlParserExpatImpl$(OBJ_EXTENSION): XmlParserExpatImpl.cpp
	$(CC) $(CCFLAGS) $(INCLUDE_PATH) -c XmlParserExpatImpl.cpp -o XmlParserExpatImpl$(OBJ_EXTENSION)

install: all
	$(COPY_CMD) $(LIB_NAME) $(INSTALL_DIR)

clean:
	$(DELETE_CMD) $(OBJS) $(LIB_NAME)
