AT = @
CC = gcc -c
LD = gcc -o
DEBUG ?= yes
USEGLIB ?= yes
USENCUR ?= yes

LIBGLIB := glib-2.0

SRCDIR = ./src
OBJDIR = ./obj
BINDIR = ./bin
INCDIR = ./include

TARGET = $(BINDIR)/main

INC = $(wildcard $(INCDIR)/*.h)
SRC = $(wildcard $(SRCDIR)/*.c)
OBJ = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRC))

CFLAGS = -I $(INCDIR) -Wall -MMD
ifeq ($(DEBUG), yes)
CFLAGS += -g
endif
ifeq ($(USEGLIB), yes)
CFLAGS += $(shell pkg-config --cflags $(LIBGLIB))
LDFLAGS += $(shell pkg-config --libs $(LIBGLIB))
endif
ifeq ($(USENCUR), yes)
LDFLAGS += -lcurses -ltinfo
endif

all: $(TARGET)

$(TARGET): $(OBJ)
	$(LD) $@ $^ $(LDFLAGS)

#check-dir:
#	$(AT)if [ ! -d $(OBJDIR) ]; then mkdir $(OBJDIR); fi
#	$(AT)if [ ! -d $(LIBDIR) ]; then mkdir $(LIBDIR); fi

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) -o $@ $< $(CFLAGS)

-include $(OBJDIR)/*.d

clean:
	rm -rf $(OBJDIR)/* $(BINDIR)/*

.PHONY: all clean
