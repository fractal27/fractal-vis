CC=gcc
LIBS=-lm -lraylib
INCLUDE=-I ./include

SRC=vis-fractal.c
OBJS=vis-fractal.o
BIN=vis-fractal

all: $(OBJS) $(BIN)

$(OBJS): $(SRC)
	$(CC) -c $(CFLAGS) $(INCLUDE) vis-fractal.c -o vis-fractal.o ${LIBS}


$(BIN): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDE) $(OBJS) -o $(BIN) ${LIBS}

clean:
	rm -f ${OBJS} ${BIN}

.PHONY: all clean
