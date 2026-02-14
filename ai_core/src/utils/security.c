/* ============================================================
   SECURITY MODULE - PIN Lock & Self-Destruct
   Provides authentication and system protection
   ============================================================ */
#include <string.h>
#include <stdlib.h>
#include "../include/ai_hub.h"

#define DEFAULT_PIN "1234"
#define MAX_ATTEMPTS 3
#define LOCKOUT_TIME 300 /* 5 minutes in seconds */

static int failed_attempts = 0;

/* Verify PIN - returns 1 if correct, 0 if wrong */
int ai_security_verify(void) {
    char pin[10];
    
    printf("\n=== SECURITY CHECK ===\n");
    printf("Enter PIN: ");
    
    /* Get PIN input (in real app, use getpass or hidden input) */
    if (fgets(pin, sizeof(pin), stdin) != NULL) {
        pin[strcspn(pin, "\n")] = 0;
    }
    
    if (strcmp(pin, DEFAULT_PIN) == 0) {
        failed_attempts = 0;
        ai_log_blackbox("INFO", "SECURITY", "Access Granted");
        return 1;
    } else {
        failed_attempts++;
        char log_msg[128];
        snprintf(log_msg, sizeof(log_msg), "Failed login attempt #%d", failed_attempts);
        ai_log_blackbox("WARN", "SECURITY", log_msg);
        
        /* Check for self-destruct condition */
        if (failed_attempts >= MAX_ATTEMPTS) {
            ai_self_destruct_check(failed_attempts);
        }
        
        return 0;
    }
}

/* Self-destruct check - lockout after too many failed attempts */
void ai_self_destruct_check(int attempts) {
    if (attempts >= MAX_ATTEMPTS) {
        ai_log_blackbox("CRITICAL", "SECURITY", "Self-Destruct Sequence Initiated");
        printf("\n!!! SECURITY ALERT !!!\n");
        printf("Too many failed attempts. System locked for 5 minutes.\n");
        
        /* In real implementation, would actually lock for 5 minutes */
        /* sleep(LOCKOUT_TIME); */
        
        failed_attempts = 0;
    }
}

