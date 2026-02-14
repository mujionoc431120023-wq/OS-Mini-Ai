/* ============================================================
   CONTEXT-AWARE SWITCHING
   Tracks conversation topics and auto-switches between domains
   ============================================================ */
#include <string.h>
#include <stdlib.h>
#include "../include/ai_hub.h"

#define MAX_CONTEXT_HISTORY 5
#define CONTEXT_STR_LEN 256

/* Context history storage */
static struct {
    char history[MAX_CONTEXT_HISTORY][CONTEXT_STR_LEN];
    int current_idx;
    char current_intent[50];
} context_mem = { .current_idx = 0, .current_intent = "general" };

/* Update context based on input keywords */
void ai_context_update(const char *input) {
    if (!input) return;
    
    char lower_input[CONTEXT_STR_LEN];
    strncpy(lower_input, input, CONTEXT_STR_LEN - 1);
    lower_input[CONTEXT_STR_LEN - 1] = '\0';
    
    /* Convert to lowercase for matching */
    for (int i = 0; lower_input[i]; i++) {
        lower_input[i] = (char)tolower(lower_input[i]);
    }
    
    /* Detect topic based on keywords */
    if (strstr(lower_input, "sakit") || strstr(lower_input, "obat") || 
        strstr(lower_input, "diagnosa") || strstr(lower_input, "demam") ||
        strstr(lower_input, "batuk") || strstr(lower_input, "pusing")) {
        strcpy(context_mem.current_intent, "health");
    }
    else if (strstr(lower_input, "masa depan") || strstr(lower_input, "ramalan") || 
             strstr(lower_input, "takdir") || strstr(lower_input, "destiny")) {
        strcpy(context_mem.current_intent, "destiny");
    }
    else if (strstr(lower_input, "investasi") || strstr(lower_input, "uang") || 
             strstr(lower_input, "dana") || strstr(lower_input, "saham")) {
        strcpy(context_mem.current_intent, "finance");
    }
    else if (strstr(lower_input, "alam semesta") || strstr(lower_input, "quantum") || 
             strstr(lower_input, "kosmik") || strstr(lower_input, "cosmic")) {
        strcpy(context_mem.current_intent, "cosmic");
    }
    else if (strstr(lower_input, "belajar") || strstr(lower_input, "sekolah") || 
             strstr(lower_input, "kampus") || strstr(lower_input, "ajar")) {
        strcpy(context_mem.current_intent, "education");
    }
    else if (strstr(lower_input, "iot") || strstr(lower_input, "smart home") || 
             strstr(lower_input, "lampu") || strstr(lower_input, "ac")) {
        strcpy(context_mem.current_intent, "iot");
    }
    else if (strstr(lower_input, "kota") || strstr(lower_input, "lalu lintas") || 
             strstr(lower_input, "energi") || strstr(lower_input, "transport")) {
        strcpy(context_mem.current_intent, "smartcity");
    }
    else if (strstr(lower_input, "kode") || strstr(lower_input, "coding") || 
             strstr(lower_input, "program") || strstr(lower_input, "debug")) {
        strcpy(context_mem.current_intent, "codeagent");
    }
    
    /* Save to history (FIFO) */
    if (context_mem.current_idx >= MAX_CONTEXT_HISTORY) {
        for (int i = 0; i < MAX_CONTEXT_HISTORY - 1; i++) {
            strcpy(context_mem.history[i], context_mem.history[i + 1]);
        }
        context_mem.current_idx = MAX_CONTEXT_HISTORY - 1;
    }
    
    strncpy(context_mem.history[context_mem.current_idx], input, CONTEXT_STR_LEN - 1);
    context_mem.history[context_mem.current_idx][CONTEXT_STR_LEN - 1] = '\0';
    context_mem.current_idx++;
}

/* Get current context intent */
const char* ai_context_get_current(void) {
    return context_mem.current_intent;
}

/* Reset context */
void ai_context_reset(void) {
    context_mem.current_idx = 0;
    strcpy(context_mem.current_intent, "general");
}

/* Check if current context is about a specific topic */
int ai_context_is_about(const char *keyword) {
    if (!keyword) return 0;
    
    for (int i = 0; i < context_mem.current_idx; i++) {
        if (strstr(context_mem.history[i], keyword)) {
            return 1;
        }
    }
    return 0;
}

