/* ============================================================
   FUZZY LOGIC - Anti-Typo System
   Uses Levenshtein Distance algorithm for fuzzy matching
   ============================================================ */
#include <string.h>
#include <stdlib.h>
#include "../include/ai_hub.h"

/* Calculate minimum of three values */
#define MIN3(a, b, c) ((a) < (b) ? ((a) < (c) ? (a) : (c)) : ((b) < (c) ? (b) : (c)))

/* Calculate Levenshtein distance between two strings */
int ai_fuzzy_distance(const char *s1, const char *s2) {
    int x, y, s1len, s2len;
    s1len = strlen(s1);
    s2len = strlen(s2);
    
    /* Allocate matrix on stack */
    int matrix[s1len + 1][s2len + 1];
    
    /* Initialize first row and column */
    matrix[0][0] = 0;
    for (x = 1; x <= s1len; x++) matrix[x][0] = matrix[x - 1][0] + 1;
    for (y = 1; y <= s2len; y++) matrix[0][y] = matrix[0][y - 1] + 1;

    /* Fill in the rest of the matrix */
    for (x = 1; x <= s1len; x++) {
        for (y = 1; y <= s2len; y++) {
            matrix[x][y] = MIN3(
                matrix[x - 1][y] + 1,           /* deletion */
                matrix[x][y - 1] + 1,           /* insertion */
                matrix[x - 1][y - 1] + (s1[x - 1] == s2[y - 1] ? 0 : 1) /* substitution */
            );
        }
    }
    return matrix[s1len][s2len];
}

/* Check if two strings are similar (within tolerance) */
int ai_fuzzy_match(const char *input, const char *target) {
    if (!input || !target) return 0;
    
    /* Exact match */
    if (strcmp(input, target) == 0) return 1;
    
    /* Case-insensitive match */
    char input_lower[256];
    char target_lower[256];
    strncpy(input_lower, input, 255);
    strncpy(target_lower, target, 255);
    input_lower[255] = '\0';
    target_lower[255] = '\0';
    
    /* Convert to lowercase */
    for (int i = 0; input_lower[i]; i++) input_lower[i] = (char)tolower(input_lower[i]);
    for (int i = 0; target_lower[i]; i++) target_lower[i] = (char)tolower(target_lower[i]);
    
    if (strcmp(input_lower, target_lower) == 0) return 1;
    
    /* Fuzzy match with tolerance */
    int distance = ai_fuzzy_distance(input_lower, target_lower);
    
    /* Allow up to 2 character differences for short words,
       proportionally more for longer words */
    int tolerance = 2;
    if (strlen(target) > 5) tolerance = 3;
    if (strlen(target) > 10) tolerance = 4;
    
    return (distance <= tolerance) ? 1 : 0;
}

