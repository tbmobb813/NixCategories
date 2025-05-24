#include <pspiofilemgr.h>
#include <pspkernel.h>
#include <string.h>
#include <stdlib.h>
#include "psppaf.h"
#include "logger.h"

#define MAX_ENTRIES 256
#define MAX_LINE_LENGTH 64

typedef struct {
    char game_id[16];
    char category[32];
} IniEntry;

static IniEntry entries[MAX_ENTRIES];
static int entry_count = 0;

int load_ini_config() {
    SceUID fd = sceIoOpen("ms0:/seplugins/categories.ini", PSP_O_RDONLY, 0777);
    if (fd < 0) {
        kprintf("No INI config found.\n");
        return 0;
    }

    char buffer[MAX_LINE_LENGTH];
    int bytes_read = 0;
    int line_index = 0;

    char line[MAX_LINE_LENGTH] = {0};
    int i = 0;

    while ((bytes_read = sceIoRead(fd, &buffer[i], 1)) > 0 && entry_count < MAX_ENTRIES) {
        if (buffer[i] == '\n' || i >= MAX_LINE_LENGTH - 1) {
            buffer[i] = '\0';

            char* equal = strchr(buffer, '=');
            if (equal) {
                *equal = '\0';
                const char* game_id = buffer;
                const char* category = equal + 1;

                strncpy(entries[entry_count].game_id, game_id, sizeof(entries[entry_count].game_id) - 1);
                strncpy(entries[entry_count].category, category, sizeof(entries[entry_count].category) - 1);
                entry_count++;
            }
            i = 0;
        } else {
            i++;
        }
    }

    sceIoClose(fd);
    kprintf("Loaded %d INI entries.\n", entry_count);
    return 1;
}

const char* get_category_from_ini(const char* game_id) {
    for (int i = 0; i < entry_count; i++) {
        if (strcmp(entries[i].game_id, game_id) == 0) {
            return entries[i].category;
        }
    }
    return NULL;
}
