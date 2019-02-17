
# include make configuration

CROSS=
STRIP	=$(CROSS)strip
CC=$(CROSS)gcc -fPIC
LINK=$(CROSS)ar

EXEC=

#CFLAGS=  -I./ -DMDC_MDIO_OPERATION -D_LITTLE_ENDIAN -Wall -O2  
CFLAGS=  -I./ -Wall -O2  

%.o: %.c
	$(CC) $(CFLAGS) -c $<

SRC = util.c ip_codec.c ipc.c
OBJ = $(SRC:.c=.o)
TARGET = com_util

all:com

com:$(OBJS)
	$(CC) $(CFLAGS) -c $(SRC) 
	$(CC) -shared $(CFLAGS) $(OBJ) -o lib$(TARGET).so
#	$(LINK) rcs lib$(TARGET).a $(OBJ)
#	sudo cp -f lib$(TARGET).a ..

clean:
	-rm -f $(TARGET) $(OBJ) lib$(TARGET).so
