CC = gcc
CFLAGS = -Wall -Wextra -g -Iinclude

TARGET = exec

SRCDIR = src
OBJDIR = obj

SRCS = $(wildcard $(SRCDIR)/*.c)

OBJS = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCS))

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) -lncurses -lm -lpthread

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

# Ausführen
run: all
	./$(TARGET)

# Aufräumen (löscht das Programm und den gesamten "obj"-Ordner)
clean:
	rm -rf $(OBJDIR) $(TARGET)

.PHONY: all run clean
