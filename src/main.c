#include <hidapi/hidapi.h>
#include <stdint.h>
#include <string.h>

#include "braille_device.h"

void ascii_to_braille(unsigned char*, char*, size_t);

int main() {
    if (hid_init()) {
        fprintf(stderr, "Failed to initialize HIDAPI\n");
        return 1;
    }

    struct hid_device_info *devs = hid_enumerate(0x0, 0x0);

    braille_device_t* bd = braille_device_open_any(devs);
    braille_device_write(bd, "hello david");

    hid_free_enumeration(devs);
    hid_exit();
    return 0;
}

