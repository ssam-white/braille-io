#include <stddef.h>
#include <hidapi/hidapi.h>

#include "braille_device.h"
#include "device/mantis_q40.h"
struct braille_device {
    const braille_device_driver_t* driver;
};


static const braille_device_driver_t* drivers[] = {
  &mantis_driver,
  NULL
};



braille_device_t* braille_device_open_any(void* raw_devices)
{
    struct hid_device_info* devices = (struct hid_device_info *) raw_devices;
    struct hid_device_info* current = devices;
    while (current)
    {
        braille_device_t* device = braille_device_open(current);
        if (device) {
          return device;
        }
        current = current->next;
    }
    return NULL;
}

braille_device_t* braille_device_open(void* device_info)
{
    for (int i = 0; drivers[i]; i++) {
        if (drivers[i]->match(device_info)) {
            return drivers[i]->open(device_info);
        }
    }
    return NULL;
}


void braille_device_write(braille_device_t* device, const char* msg)
{
    device->driver->write(device, msg);
}
