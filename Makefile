CC = gcc
CFLAGS = -Wall -Wextra
TARGET = rmsf

all: $(TARGET)

$(TARGET): $(TARGET).c
	$(CC) $(CFLAGS) -o $@ $^

run: $(TARGET)
	./$(TARGET)

test: $(TARGET)
	bash test.sh

install: $(TARGET)
	ln -s $(PWD)/$(TARGET) /usr/local/bin/$(TARGET)

uninstall:
	rm /usr/local/bin/$(TARGET)
