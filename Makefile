# Nama output
TARGET = penjadwal_rumah_sakit

# Compiler dan flags
CC = gcc
CFLAGS = -Wall -Wextra -g

# File sumber
SRCS = main.c dokter.c jadwal.c file_io.c random_id.c

# File objek
OBJS = $(SRCS:.c=.o)

# Build dan jalankan
all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS)

run: $(TARGET)
	./$(TARGET)

# Bersih-bersih
clean:
	rm -f $(TARGET) $(OBJS)
