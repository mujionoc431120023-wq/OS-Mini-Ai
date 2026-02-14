/* ============================================================
   AI HUB - Central AI Dispatcher Header (ENHANCED VERSION)
   OS-Mini AI for Linux - Multi-Domain Intelligence System
   
   Features:
   - Fuzzy Logic (Anti-typo)
   - Context-Aware Switching
   - Multi-language Detection
   - Sentiment Analysis
   - Long-term Memory (Persistence)
   - Security & Encryption
   - IoT Smart Home Control
   - Cloud Sync (Dormant)
   - OTA Updates (Dormant)
   - Self-Repair System (NEW)
   ============================================================ */

#ifndef AI_HUB_H
#define AI_HUB_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>

/* ============================================================
   SYSTEM CONFIGURATION
   ============================================================ */
#define VERSION "1.0.0"
#define MAX_INPUT 4096
#define MAX_OUTPUT 8192
#define FEATURE_MONETIZATION_ACTIVE 0  /* 0: Non-aktif, 1: Aktif */

/* Forward declaration for ncurses WINDOW */
struct _win_st;
typedef struct _win_st WINDOW;

/* ============================================================
   CORE INTELLIGENCE MODULES
   ============================================================ */

/* Blackbox Logger - System Audit Trail */
void ai_log_blackbox(const char *level, const char *module, const char *message);
void ai_log_session_start(void);

/* Fuzzy Logic - Anti Typo System */
int ai_fuzzy_match(const char *input, const char *target);
int ai_fuzzy_distance(const char *s1, const char *s2);

/* Context-Aware Switching */
void ai_context_update(const char *input);
const char* ai_context_get_current(void);
void ai_context_reset(void);
int ai_context_is_about(const char *keyword);

/* Multi-language Detection */
int ai_detect_language(const char *input, char *lang_name);

/* Sentiment Analysis */
int ai_analyze_sentiment(const char *input, char *emotion);
int ai_predict_next_step(const char *input, const char *emotion, char *prediction);

/* Long-term Memory (Persistence) */
void ai_persistence_load(void);
void ai_persistence_save(void);
void ai_persistence_update(const char *key, const char *value);
char* ai_get_user_name(void);

/* Encryption Engine */
void ai_crypto_process(char *data, size_t len);

/* Cloud Sync (Dormant) */
int ai_cloud_push(void);
int ai_cloud_pull(void);

/* OTA Updates (Dormant) */
int ai_ota_check_update(void);
void ai_ota_apply_update(void);

/* Security Module */
int ai_security_verify(void);
void ai_self_destruct_check(int attempts);

/* IoT Controller */
int ai_iot_control(const char *target, int action);
const char* ai_iot_get_status(void);

/* Face Recognition (Dormant - Hardware Dependent) */
int ai_face_init(void);
int ai_face_verify(void);
int ai_is_camera_active(void);

/* Billing/Monetization (Dormant) */
int ai_billing_check_access(const char *feature_name);
void ai_billing_init_session(void);

/* UI Components */
void draw_ai_bubble(WINDOW *win, int active);
void display_typing_effect(WINDOW *win, int y, int x, const char *text, int speed);
int is_bubble_clicked(int mx, int my, int wy, int wx);

/* ============================================================
   DOMAIN AI MODULES (Original Features)
   ============================================================ */

/* Healthcare AI */
int ai_health_analyze(const char *symptom, char *diagnosis);

/* Education AI */
int ai_edu_recommend(const char *topic, char *material);

/* Manufacturing AI */
int ai_manufacture_predict(const char *sensor, char *report);

/* Finance AI */
int ai_finance_analyze(const char *transaction, char *result);

/* IoT AI */
int ai_iot_process(const char *device, const char *data, char *resp);

/* Smart City AI */
int ai_transport_analyze(const char *traffic, char *report);
int ai_energy_monitor(const char *usage, char *status);
int ai_env_analyze(const char *sensor, char *result);
int ai_service_request(const char *req, char *resp);

/* Governance AI */
int ai_governance_check(const char *policy, char *compliance);

/* Future AI */
int ai_quantum_optimize(const char *problem, char *solution);
int ai_neuro_process(const char *signal, char *resp);
int ai_autonomous_control(const char *command, char *status);
int ai_self_learn(const char *feedback, const char *domain, char *update);
int ai_adapt_context(const char *context, char *resp);
int ai_show_roadmap(char *buf);

/* Community & Evolution AI */
int ai_patch_submit(const char *user, const char *patch);
int ai_symbiosis_collab(const char *input, const char *context, char *output);
int ai_bio_interface(const char *data, char *output);
int ai_cosmic_nav(const char *coordinates, char *response);
int ai_singularity_merge(const char *input, char *output);
int ai_infinity_expand(const char *input, char *output);
int ai_meta_integrate(const char *input, char *output);
int ai_destiny_core(const char *input, char *output);

/* ============================================================
   CODEAGENT - Complex Coding Task Handler
   ============================================================ */
int ai_codeagent_analyze(const char *task, char *response);
int ai_codeagent_generate(const char *language, const char *requirements, char *code);
int ai_codeagent_debug(const char *code, const char *error, char *fix);
int ai_codeagent_review(const char *code, char *review);
int ai_codeagent_optimize(const char *code, char *optimized);
int ai_codeagent_explain(const char *code, char *explanation);

/* ============================================================
   SELF-REPAIR SYSTEM - Automatic Bug Fixing
   ============================================================ */

/* Error severity levels */
#define SELF_REPAIR_INFO      1
#define SELF_REPAIR_WARNING   2
#define SELF_REPAIR_ERROR     3
#define SELF_REPAIR_CRITICAL  4

/* Health report structure */
typedef struct {
    int memory_ok;
    int disk_ok;
    int ai_modules_ok;
    int persistence_ok;
    int blackbox_ok;
    int last_error_count;
    int last_repair_count;
    float health_score;
} health_report_t;

/* Initialize self-repair system */
void ai_self_repair_init(void);

/* Log an error */
void ai_self_repair_log_error(const char *category, const char *error_msg, 
                               const char *context, int severity);

/* Analyze error using AI */
void ai_self_repair_analyze_error(int error_id, char *analysis, size_t len);

/* Auto-fix an error */
int ai_self_repair_auto_fix(int error_id);

/* Manual fix */
int ai_self_repair_manual_fix(int error_id, const char *custom_fix);

/* Health check */
void ai_self_repair_health_check(health_report_t *report);

/* Get health status */
void ai_self_repair_get_health_status(char *status, size_t len);

/* Run diagnostics */
void ai_self_repair_run_diagnostics(char *output, size_t len);

/* Restore from backup */
int ai_self_repair_restore_backup(void);

/* Clear error log */
void ai_self_repair_clear_errors(void);

/* Get error count */
int ai_self_repair_get_error_count(void);

/* Get unfixed count */
int ai_self_repair_get_unfixed_count(void);

/* Simulate error for testing */
void ai_self_repair_simulate_error(const char *category, const char *msg);

/* ============================================================
   MAIN HUB FUNCTION
   ============================================================ */
int ai_hub_request(const char *domain, const char *input, char *output);

#endif /* AI_HUB_H */

