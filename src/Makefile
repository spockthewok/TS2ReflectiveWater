CC = cl
CFLAGS = /LD /EHsc /MD /Zi
LDFLAGS = /link /DEBUG
TARGET = TS2ReflectiveWater.asi

all: $(TARGET)

$(TARGET): *.obj
    $(CC) $(CFLAGS) *.obj /Fe:$(TARGET) $(LDFLAGS)

.cpp.obj:
    $(CC) $(CFLAGS) /c $<

clean:
    del /Q *.obj *.pdb *.ilk $(TARGET)