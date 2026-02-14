/* ============================================================
   MULTI-LANGUAGE DETECTION
   Detects language from input using keyword patterns
   ============================================================ */
#include <string.h>
#include <ctype.h>
#include "../include/ai_hub.h"

/* Language patterns - common words in each language */
typedef struct {
    const char *code;
    const char *name;
    const char *patterns[5];
} language_map_t;

static language_map_t languages[] = {
    {"id", "Indonesian", {"yang", "dan", "dengan", "untuk", "adalah"}},
    {"en", "English", {"the", "and", "with", "for", "is"}},
    {"ms", "Malaysian", {"yang", "dan", "dengan", "untuk", "adalah"}},
    {"de", "German", {"und", "der", "die", "das", "mit"}},
    {"fr", "French", {"le", "la", "les", "et", "dans"}},
    {"es", "Spanish", {"el", "la", "los", "y", "para"}},
    {"jp", "Japanese", {"watashi", "desu", "anata", "no", "ka"}},
    {"zh", "Chinese", {"de", "shi", "wo", "ni", "he"}},
    {"ar", "Arabic", {"wa", "al", "il", "bi", "la"}},
    {"pt", "Portuguese", {"o", "a", "de", "e", "para"}},
    {"ru", "Russian", {"i", "v", "na", "po", "dlya"}},
    {"ko", "Korean", {"ne", "eun", "reul", "wa", "ge"}},
    {"th", "Thai", {"khong", "lae", "with", "nai", "th"}},
    {"vi", "Vietnamese", {"va", "la", "cua", "trong", "khong"}},
    {"tl", "Tagalog", {"ang", "ng", "sa", "at", "ang"}}
};

#define NUM_LANGUAGES (sizeof(languages) / sizeof(languages[0]))

int ai_detect_language(const char *input, char *lang_name) {
    if (!input || !lang_name) return -1;
    
    char lower_input[512];
    strncpy(lower_input, input, 511);
    lower_input[511] = '\0';
    
    /* Convert to lowercase */
    for (int i = 0; lower_input[i]; i++) {
        lower_input[i] = (char)tolower(lower_input[i]);
    }
    
    int max_hits = 0;
    int detected_idx = 1; /* Default to English */
    
    for (int i = 0; i < NUM_LANGUAGES; i++) {
        int hits = 0;
        for (int j = 0; j < 5; j++) {
            if (strstr(lower_input, languages[i].patterns[j])) {
                hits++;
            }
        }
        if (hits > max_hits) {
            max_hits = hits;
            detected_idx = i;
        }
    }
    
    strcpy(lang_name, languages[detected_idx].name);
    return detected_idx;
}

