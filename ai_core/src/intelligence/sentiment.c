/* ============================================================
   SENTIMENT ANALYSIS
   Analyzes user emotion from text input
   ============================================================ */
#include <string.h>
#include <ctype.h>
#include "../include/ai_hub.h"

/* Positive and negative word lists (multi-language) */
static const char *positive_words[] = {
    "senang", "bagus", "hebat", "suka", "happy", "good", "love", "excellent",
    "awesome", "amazing", "wonderful", "fantastic", "great", "best", "perfect",
    "beautiful", "nice", "terbaik", "syukur", "alhamdulillah", "merdeka"
};

static const char *negative_words[] = {
    "marah", "sedih", "buruk", "jelek", "angry", "sad", "bad", "hate",
    "terrible", "awful", "horrible", "worst", "sucks", "gagal", "kecewa",
    "bingung", "kesal", "stress", "strees", "panik", "takut", "ngeri"
};

#define NUM_POSITIVE (sizeof(positive_words) / sizeof(positive_words[0]))
#define NUM_NEGATIVE (sizeof(negative_words) / sizeof(negative_words[0]))

int ai_analyze_sentiment(const char *input, char *emotion) {
    if (!input || !emotion) return 0;
    
    char lower_input[512];
    strncpy(lower_input, input, 511);
    lower_input[511] = '\0';
    
    /* Convert to lowercase */
    for (int i = 0; lower_input[i]; i++) {
        lower_input[i] = (char)tolower(lower_input[i]);
    }
    
    int score = 0;
    
    /* Check for positive words */
    for (int i = 0; i < NUM_POSITIVE; i++) {
        if (strstr(lower_input, positive_words[i])) {
            score++;
        }
    }
    
    /* Check for negative words */
    for (int i = 0; i < NUM_NEGATIVE; i++) {
        if (strstr(lower_input, negative_words[i])) {
            score--;
        }
    }
    
    /* Determine emotion label */
    if (score > 0) {
        strcpy(emotion, "POSITIVE");
    } else if (score < 0) {
        strcpy(emotion, "NEGATIVE");
    } else {
        strcpy(emotion, "NEUTRAL");
    }
    
    return score;
}

/* Predict next step based on sentiment and input */
int ai_predict_next_step(const char *input, const char *emotion, char *prediction) {
    if (!input || !emotion || !prediction) return 0;
    
    char lower_input[512];
    strncpy(lower_input, input, 511);
    lower_input[511] = '\0';
    
    for (int i = 0; lower_input[i]; i++) {
        lower_input[i] = (char)tolower(lower_input[i]);
    }
    
    /* Health-related predictions */
    if (strstr(lower_input, "sakit") || strstr(lower_input, "demam")) {
        strcpy(prediction, "Saran: Mencari informasi obat atau jadwal dokter terdekat.");
    }
    /* Finance-related predictions */
    else if (strstr(lower_input, "investasi") || strstr(lower_input, "saham")) {
        strcpy(prediction, "Saran: Menampilkan ringkasan pasar modal hari ini.");
    }
    /* Negative emotion handling */
    else if (strcmp(emotion, "NEGATIVE") == 0) {
        strcpy(prediction, "Saran: Mengaktifkan mode relaksasi atau musik tenang.");
    }
    /* Default prediction */
    else {
        strcpy(prediction, "Saran: Menunggu instruksi spesifik selanjutnya.");
    }
    
    return 0;
}

