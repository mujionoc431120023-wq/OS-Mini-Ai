/* ============================================================
   LONG-TERM MEMORY (PERSISTENCE)
   Stores and retrieves encrypted user data
   ============================================================ */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/ai_hub.h"

#define MEMORY_PATH "data/ai_memory.dat"

/* User memory structure */
typedef struct {
    char user_name[50];
    char last_topic[50];
    int interaction_count;
    char user_preference[256];
    char last_domain[32];
} long_term_memory_t;

static long_term_memory_t ltm;

/* Encryption key (internal to AI) */
static const char *ENCRYPTION_KEY = "OS_MINI_OMEGA_SECURE_KEY_2026";

/* Simple XOR encryption */
void ai_crypto_process(char *data, size_t len) {
    if (!data || len == 0) return;
    
    size_t key_len = strlen(ENCRYPTION_KEY);
    for (size_t i = 0; i < len; i++) {
        data[i] ^= ENCRYPTION_KEY[i % key_len];
    }
}

/* Load memory from disk */
void ai_persistence_load(void) {
    FILE *file = fopen(MEMORY_PATH, "rb");
    if (file) {
        size_t read_size = fread(&ltm, sizeof(long_term_memory_t), 1, file);
        fclose(file);
        
        if (read_size > 0) {
            /* Decrypt loaded data */
            ai_crypto_process((char *)&ltm, sizeof(long_term_memory_t));
            ai_log_blackbox("INFO", "PERSISTENCE", "Long-term memory loaded successfully.");
            return;
        }
    }
    
    /* Initialize new memory if file doesn't exist */
    memset(&ltm, 0, sizeof(long_term_memory_t));
    strcpy(ltm.user_name, "User");
    ltm.interaction_count = 0;
    ai_log_blackbox("WARN", "PERSISTENCE", "No memory file found. Initializing new memory.");
}

/* Save memory to disk */
void ai_persistence_save(void) {
    FILE *file = fopen(MEMORY_PATH, "wb");
    if (file) {
        /* Create encrypted copy */
        long_term_memory_t temp_mem = ltm;
        ai_crypto_process((char *)&temp_mem, sizeof(long_term_memory_t));
        
        fwrite(&temp_mem, sizeof(long_term_memory_t), 1, file);
        fclose(file);
        ai_log_blackbox("INFO", "PERSISTENCE", "Memory encrypted and saved to disk.");
    } else {
        ai_log_blackbox("ERROR", "PERSISTENCE", "Failed to save memory to disk.");
    }
}

/* Update memory with new data */
void ai_persistence_update(const char *key, const char *value) {
    if (!key || !value) return;
    
    if (strcmp(key, "name") == 0) {
        strncpy(ltm.user_name, value, 49);
    } else if (strcmp(key, "topic") == 0) {
        strncpy(ltm.last_topic, value, 49);
    } else if (strcmp(key, "domain") == 0) {
        strncpy(ltm.last_domain, value, 31);
    } else if (strcmp(key, "pref") == 0) {
        strncpy(ltm.user_preference, value, 255);
    }
    
    ltm.interaction_count++;
    ai_persistence_save();
}

/* Get user name */
char* ai_get_user_name(void) {
    return ltm.user_name;
}

