CC = gcc
CFLAGS = -Wall -Wextra -g -Iinclude

TARGET = exec

SRCDIR = src
OBJDIR = obj

# searches all .c files
SRCS = $(wildcard $(SRCDIR)/*.c)

# makes the .o files in the obj/ directory
OBJS = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCS))


# compiles to executable

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -lncurses -o $(TARGET) $(OBJS)

# Kompilieren: Erstellt die .o-Dateien im "obj"-Ordner aus den .c-Dateien
$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Erstellt den "obj"-Ordner, falls er nicht existiert
$(OBJDIR):
	mkdir -p $(OBJDIR)

# Ausführen
run: all
	./$(TARGET)

# Aufräumen (löscht das Programm und den gesamten "obj"-Ordner)
clean:
	rm -rf $(OBJDIR) $(TARGET)

.PHONY: all run clean
