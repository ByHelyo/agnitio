CC = gcc
CFLAGS = -std=c99 `pkg-config --cflags sdl gtk+-3.0` -D_POSIX_C_SOURCE=200809L
LDLIBS = `pkg-config --libs sdl SDL_image gtk+-3.0` -lm -rdynamic

BIN = agnitio

OBJ = src/gui/gui.o \
      src/image/image.o \
      src/image/image-binarization.o \
      src/image/image-display.o \
      src/image/image-greyscale.o \
      src/image/pixel-operations.o \
      src/neural-network/database.o \
      src/neural-network/layer.o \
      src/neural-network/layer-learn.o \
      src/neural-network/layer-save.o \
      src/neural-network/network-learn.o \
      src/neural-network/network.o \
      src/neural-network/neuron.o \
      src/neural-network/neuron-save.o \
      src/neural-network/neuron-learn.o \
      src/neural-network/network-save.o \
      src/neural-network/sigmoid.o \
      src/utils/array.o \
      src/utils/random.o \
      src/utils/string.o \
      src/main.o

ASSETS = assets/design.glade

all: release

release: CFLAGS += -O3
release: ${OBJ} ${ASSETS}
	${CC} ${LDFLAGS} ${LDLIBS} -o ${BIN} ${OBJ}

dev: CFLAGS += -pedantic -Wall -Wextra -g -fsanitize=address
dev: LDFLAGS += -fsanitize=address
dev: ${OBJ} ${ASSETS}
	${CC} ${LDFLAGS} ${LDLIBS} -o ${BIN} ${OBJ}

clean:
	${RM} ${OBJ} ${BIN}

.PHONY: all release dev clean
