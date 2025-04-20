#ifndef BRAILLE_DEVICE_H
#define BRAILLE_DEVICE_H

#include <stdbool.h>

typedef struct braille_device braille_device_t;

typedef struct braille_device_driver {
  const char* name;
  braille_device_t* (*open)(void*);
  bool (*match)(void*);
  void (*write)(braille_device_t*, const char*);
} braille_device_driver_t;

braille_device_t* braille_device_open_any(void*);
braille_device_t* braille_device_open(void*);
void braille_device_write(braille_device_t*, const char* msg);

#endif
