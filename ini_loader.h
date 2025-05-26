#ifndef INI_LOADER_H
#define INI_LOADER_H

#ifdef __cplusplus
extern "C" {
#endif

    // Maximum number of entries this loader can store
#define MAX_CATEGORY_ENTRIES 1024

/**
 * Structure for mapping GAMEID to category name.
 */
    typedef struct {
        char game_id[16];
        char category[32];
    } CategoryEntry;

    // Global category map and counter
    extern CategoryEntry g_category_map[MAX_CATEGORY_ENTRIES];
    extern int g_category_count;

    /**
     * Loads categories from an INI-style file.
     * Each line should be in the format: GAMEID=CATEGORY
     * Returns 0 on success, negative on error.
     */
    int load_ini_categories(const char* path);

    /**
     * Returns the category string for a given GAMEID.
     * If not found, returns "Uncategorized".
     */
    const char* lookup_category(const char* game_id);

#ifdef __cplusplus
}
#endif

#endif // INI_LOADER_H
