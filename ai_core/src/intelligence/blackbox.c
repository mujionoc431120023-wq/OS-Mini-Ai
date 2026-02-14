/* ============================================================
   BLACKBOX LOGGER - System Audit Trail
   Records all AI decisions and system events
   ============================================================ */
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include "../include/ai_hub.h"

#define LOG_FILE "data/blackbox.log"

void ai_log_blackbox(const char *level, const char *module, const char *message) {
    FILE *file = fopen(LOG_FILE, "a");
    if (!file) return;

    time_t now = time(NULL);
    char *ts = ctime(&now);
    ts[strlen(ts) - 1] = '\0';

    fprintf(file, "[%s] [%s] [%s]: %s\n", ts, level, module, message);
    fclose(file);
}

void ai_log_session_start(void) {
    ai_log_blackbox("INFO", "SYSTEM", "=== NEW AI SESSION STARTED ===");
}

