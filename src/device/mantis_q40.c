#include <stdlib.h>
#include <hidapi/hidapi.h>
#include <string.h>
#include <stdbool.h>

#include "mantis_q40.h"
#include "braille_device.h"
#include "braille/ascii.h"

struct braille_device {
    const braille_device_driver_t* driver;
    hid_device* handle;
};

static braille_device_t* mantis_open(void* raw_device_info)
{
    struct hid_device_info* device_info = (struct hid_device_info*) raw_device_info;
    hid_device* handle = hid_open_path(device_info->path);
    if (!handle) {
        fprintf(stderr, "❌ Failed to open device at %s\n", device_info->path);
        return NULL;
    }

    struct braille_device* device = calloc(1, sizeof(struct braille_device));
    if (!device) {
        fprintf(stderr, "Failed to create matin device");
        hid_close(handle);
        return NULL;
    }

    device->handle = handle;
    device->driver = &mantis_driver;

    return device;
}

bool mantis_match(void* raw_device)
{
    struct hid_device_info* device = (struct hid_device_info*) raw_device;

    return device->product_string &&
        wcsncmp(device->product_string, L"APH Mantis Q40", 14) == 0 &&
        device->interface_number == 1 &&
        device->usage_page == 0x0041;
}

static void mantis_write(braille_device_t* raw_device, const char* msg)
{
    struct braille_device* device = (struct braille_device *) raw_device;

    unsigned char buf[64];
    memset(buf, 0x00, sizeof(buf));
    ascii_to_braille(buf, msg, strlen(msg));

    int res = hid_write(device->handle, buf, sizeof(buf));
    if (res < 0) {
        fprintf(stderr, "❌ Write failed: %ls\n", hid_error(device->handle));
    } else {
          printf("✅ Sent: '%s'\n", msg);
    }
}

const braille_device_driver_t mantis_driver = {
    .name = "APH Mantis Q40",
    .open = mantis_open,
    .match = mantis_match,
    .write = mantis_write
};
