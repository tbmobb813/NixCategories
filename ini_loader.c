#include <pspiofilemgr.h>
#include <string.h>
#include <stdlib.h>
#include "psppaf.h"
#include "logger.h"

#define MAX_CATEGORY_ENTRIES 1024

typedef struct {
    char game_id[16];
    char category[32];
} CategoryEntry;

CategoryEntry g_category_map[MAX_CATEGORY_ENTRIES];
int g_category_count = 0;

/**
 * Load game ID to category mapping from an INI-style file.
 * Format: <GAMEID>=<CATEGORY>
 */
int load_ini_categories(const char* path) {
    SceUID fd = sceIoOpen(path, PSP_O_RDONLY, 0777);
    if (fd < 0) {
        kprintf("Failed to open INI file: %s\n", path);
        return -1;
    }

    SceOff size = sceIoLseek(fd, 0, PSP_SEEK_END);
    sceIoLseek(fd, 0, PSP_SEEK_SET);

    char* buffer = sce_paf_private_malloc(size + 1);
    if (!buffer) {
        sceIoClose(fd);
        kprintf("Memory allocation failed\n");
        return -2;
    }

    sceIoRead(fd, buffer, size);
    buffer[size] = '\0';
    sceIoClose(fd);

    char* line = strtok(buffer, "\n");
    while (line && g_category_count < MAX_CATEGORY_ENTRIES) {
        // Skip comments and empty lines
        if (line[0] == '#' || line[0] == '\0') {
            line = strtok(NULL, "\n");
            continue;
        }

        char* sep = strchr(line, '=');
        if (sep) {
            *sep = '\0';

            sce_paf_private_strncpy(
                g_category_map[g_category_count].game_id,
                line,
                sizeof(g_category_map[g_category_count].game_id) - 1
            );

            sce_paf_private_strncpy(
                g_category_map[g_category_count].category,
                sep + 1,
                sizeof(g_category_map[g_category_count].category) - 1
            );

            g_category_count++;
        }

        line = strtok(NULL, "\n");
    }

    sce_paf_private_free(buffer);

    kprintf("Loaded %d entries from %s\n", g_category_count, path);
    return 0;
}

/**
 * Lookup the category for a given GAMEID.
 * Returns "Uncategorized" if not found.
 */
const char* lookup_category(const char* game_id) {
    for (int i = 0; i < g_category_count; i++) {
        if (sce_paf_private_strcmp(g_category_map[i].game_id, game_id) == 0) {
            return g_category_map[i].category;
        }
    }
    return "Uncategorized";  // Change to NULL if you'd rather handle it externally
}
