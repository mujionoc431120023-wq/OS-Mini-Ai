#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/ai_hub.h"

#define MAX_INPUT 4096
#define MAX_OUTPUT 8192

/* Color codes for terminal output */
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define BOLD    "\033[1m"

/* Print banner */
void print_banner() {
    printf(BOLD CYAN);
    printf("╔═══════════════════════════════════════════════════════════════╗\n");
    printf("║           OS-MINI AI - LINUX EDITION                        ║\n");
    printf("║           Powered by CodeAgent & Multi-Domain AI            ║\n");
    printf("╚═══════════════════════════════════════════════════════════════╝\n");
    printf(RESET);
}

/* Print main menu */
void print_menu() {
    printf(BOLD YELLOW "\n═══ PILIH DOMAIN AI ===" RESET "\n");
    printf(BLUE "  [1]" RESET " Healthcare AI     - Analisis kesehatan & diagnosis\n");
    printf(BLUE "  [2]" RESET " Education AI      - Rekomendasi materi pembelajaran\n");
    printf(BLUE "  [3]" RESET " Finance AI        - Analisis transaksi keuangan\n");
    printf(BLUE "  [4]" RESET " Manufacturing AI  - Prediksi maintenance mesin\n");
    printf(BLUE "  [5]" RESET " IoT AI            - Proses smart home & sensor\n");
    printf(BLUE "  [6]" RESET " Smart City AI     - Transportasi, energi, lingkungan\n");
    printf(BLUE "  [7]" RESET " Governance AI     - Compliance & kebijakan\n");
    printf(BLUE "  [8]" RESET " Future AI         - Quantum, Neuromorphic, Autonomous\n");
    printf(MAGENTA "  [9]" RESET " CodeAgent AI      - ANALISIS & GENERASI KODE\n");
    printf(CYAN "  [10]" RESET " Roadmap           - Evolutionary roadmap\n");
    printf(BOLD RED "  [0]" RESET " Exit\n");
    printf(YELLOW "\n>>> Pilih menu: " RESET);
}

/* Print CodeAgent menu */
void print_codeagent_menu() {
    printf(BOLD MAGENTA "\n═══ CODEAGENT - COMPLEX CODING HANDLER ===" RESET "\n");
    printf(BLUE "  [1]" RESET " Analyze Task      - Analisis tugas coding kompleks\n");
    printf(BLUE "  [2]" RESET " Generate Code     - Generate kode (C, Python, JS, etc)\n");
    printf(BLUE "  [3]" RESET " Debug & Fix       - Debug error & berikan solusi\n");
    printf(BLUE "  [4]" RESET " Code Review       - Review kode, temukan issue\n");
    printf(BLUE "  [5]" RESET " Optimize          - Optimasi performa kode\n");
    printf(BLUE "  [6]" RESET " Explain           - Jelaskan kode secara detail\n");
    printf(BOLD RED "  [0]" RESET " Back to main menu\n");
    printf(YELLOW "\n>>> Pilih menu: " RESET);
}

/* Handle Healthcare AI */
void handle_health() {
    char input[MAX_INPUT];
    char output[MAX_OUTPUT];
    
    printf(CYAN "\n=== HEALTHCARE AI ===" RESET "\n");
    printf("Masukkan gejala (例: batuk, demam, sakit kepala, sesak): ");
    fgets(input, MAX_INPUT, stdin);
    input[strcspn(input, "\n")] = 0;
    
    ai_health_analyze(input, output);
    printf(GREEN "\n📋 Diagnosis: %s\n" RESET, output);
}

/* Handle Education AI */
void handle_education() {
    char input[MAX_INPUT];
    char output[MAX_OUTPUT];
    
    printf(CYAN "\n=== EDUCATION AI ===" RESET "\n");
    printf("Masukkan topik (例: matematika, sejarah, fisika, bahasa): ");
    fgets(input, MAX_INPUT, stdin);
    input[strcspn(input, "\n")] = 0;
    
    ai_edu_recommend(input, output);
    printf(GREEN "\n📚 Materi: %s\n" RESET, output);
}

/* Handle Finance AI */
void handle_finance() {
    char input[MAX_INPUT];
    char output[MAX_OUTPUT];
    
    printf(CYAN "\n=== FINANCE AI ===" RESET "\n");
    printf("Masukkan transaksi (例: jumlah besar, investasi, regular, foreign): ");
    fgets(input, MAX_INPUT, stdin);
    input[strcspn(input, "\n")] = 0;
    
    ai_finance_analyze(input, output);
    printf(GREEN "\n💰 Analisis: %s\n" RESET, output);
}

/* Handle Manufacturing AI */
void handle_manufacturing() {
    char input[MAX_INPUT];
    char output[MAX_OUTPUT];
    
    printf(CYAN "\n=== MANUFACTURING AI ===" RESET "\n");
    printf("Masukkan data sensor (例: vibration_high, temp_high, pressure_drop): ");
    fgets(input, MAX_INPUT, stdin);
    input[strcspn(input, "\n")] = 0;
    
    ai_manufacture_predict(input, output);
    printf(GREEN "\n🏭 Laporan: %s\n" RESET, output);
}

/* Handle IoT AI */
void handle_iot() {
    char input[MAX_INPUT];
    char output[MAX_OUTPUT];
    
    printf(CYAN "\n=== IOT AI ===" RESET "\n");
    printf("Masukkan data IoT (例: lamp_on, ac_temp_high, overheat, traffic): ");
    fgets(input, MAX_INPUT, stdin);
    input[strcspn(input, "\n")] = 0;
    
    ai_iot_process("smart_home", input, output);
    printf(GREEN "\n🏠 Status: %s\n" RESET, output);
}

/* Handle Smart City AI */
void handle_smartcity() {
    char input[MAX_INPUT];
    char output[MAX_OUTPUT];
    int submenu;
    
    printf(CYAN "\n=== SMART CITY AI ===" RESET "\n");
    printf("  [1] Transportasi\n");
    printf("  [2] Energi\n");
    printf("  [3] Lingkungan\n");
    printf("  [4] Layanan Publik\n");
    printf("Pilih: ");
    scanf("%d", &submenu);
    getchar(); // consume newline
    
    switch(submenu) {
        case 1:
            printf("Data lalu lintas (例: macet, lancar, accident): ");
            fgets(input, MAX_INPUT, stdin);
            input[strcspn(input, "\n")] = 0;
            ai_transport_analyze(input, output);
            printf(GREEN "\n🚗 Laporan: %s\n" RESET, output);
            break;
        case 2:
            printf("Data energi (例: overload, normal, peak, low): ");
            fgets(input, MAX_INPUT, stdin);
            input[strcspn(input, "\n")] = 0;
            ai_energy_monitor(input, output);
            printf(GREEN "\n⚡ Status: %s\n" RESET, output);
            break;
        case 3:
            printf("Data lingkungan (例: polusi, hujan, temp_anomaly): ");
            fgets(input, MAX_INPUT, stdin);
            input[strcspn(input, "\n")] = 0;
            ai_env_analyze(input, output);
            printf(GREEN "\n🌍 Hasil: %s\n" RESET, output);
            break;
        case 4:
            printf("Permintaan layanan (例: ambulance, pemadam, polisi): ");
            fgets(input, MAX_INPUT, stdin);
            input[strcspn(input, "\n")] = 0;
            ai_service_request(input, output);
            printf(GREEN "\n🚑 Respons: %s\n" RESET, output);
            break;
        default:
            printf(RED "Pilihan tidak valid!\n" RESET);
    }
}

/* Handle Governance AI */
void handle_governance() {
    char input[MAX_INPUT];
    char output[MAX_OUTPUT];
    
    printf(CYAN "\n=== GOVERNANCE AI ===" RESET "\n");
    printf("Masukkan kebijakan (例: privacy, security, finance): ");
    fgets(input, MAX_INPUT, stdin);
    input[strcspn(input, "\n")] = 0;
    
    ai_governance_check(input, output);
    printf(GREEN "\n⚖️ Compliance: %s\n" RESET, output);
}

/* Handle Future AI */
void handle_future() {
    char input[MAX_INPUT];
    char output[MAX_OUTPUT];
    int submenu;
    
    printf(CYAN "\n=== FUTURE AI ===" RESET "\n");
    printf("  [1] Quantum Optimization\n");
    printf("  [2] Neuromorphic Processing\n");
    printf("  [3] Autonomous Control\n");
    printf("  [4] Self-Learning\n");
    printf("  [5] Adaptive Context\n");
    printf("Pilih: ");
    scanf("%d", &submenu);
    getchar(); // consume newline
    
    switch(submenu) {
        case 1:
            printf("Problem (例: routing, finance, optimization): ");
            fgets(input, MAX_INPUT, stdin);
            input[strcspn(input, "\n")] = 0;
            ai_quantum_optimize(input, output);
            break;
        case 2:
            printf("Signal (例: pattern, sensor, learning): ");
            fgets(input, MAX_INPUT, stdin);
            input[strcspn(input, "\n")] = 0;
            ai_neuro_process(input, output);
            break;
        case 3:
            printf("Command (例: drive, fly, operate): ");
            fgets(input, MAX_INPUT, stdin);
            input[strcspn(input, "\n")] = 0;
            ai_autonomous_control(input, output);
            break;
        case 4:
            printf("Feedback (例: positif, negatif): ");
            fgets(input, MAX_INPUT, stdin);
            input[strcspn(input, "\n")] = 0;
            ai_self_learn(input, "domain_default", output);
            break;
        case 5:
            printf("Context (例: malam, kerja, relaksasi): ");
            fgets(input, MAX_INPUT, stdin);
            input[strcspn(input, "\n")] = 0;
            ai_adapt_context(input, output);
            break;
        default:
            printf(RED "Pilihan tidak valid!\n" RESET);
            return;
    }
    printf(GREEN "\n🔮 Result: %s\n" RESET, output);
}

/* Handle CodeAgent - Complex Coding Tasks */
void handle_codeagent() {
    char input[MAX_INPUT];
    char output[MAX_OUTPUT];
    char code_input[MAX_INPUT * 4];
    int submenu;
    
    while (1) {
        print_codeagent_menu();
        scanf("%d", &submenu);
        getchar(); // consume newline
        
        if (submenu == 0) break;
        
        switch(submenu) {
            case 1: // Analyze
                printf(CYAN "\n=== CODEAGENT ANALYZE ===" RESET "\n");
                printf("Masukkan tugas coding (algorithm, data structure, performance, security, architecture, database, api, testing): ");
                fgets(input, MAX_INPUT, stdin);
                input[strcspn(input, "\n")] = 0;
                ai_codeagent_analyze(input, output);
                printf(GREEN "\n📊 Analysis:\n%s\n" RESET, output);
                break;
                
            case 2: // Generate
                printf(CYAN "\n=== CODEAGENT CODE GENERATION ===" RESET "\n");
                printf("Pilih bahasa: [1] C [2] Python [3] JavaScript: ");
                int lang_choice;
                scanf("%d", &lang_choice);
                getchar();
                
                char language[32];
                if (lang_choice == 1) strcpy(language, "c");
                else if (lang_choice == 2) strcpy(language, "python");
                else if (lang_choice == 3) strcpy(language, "javascript");
                else { printf(RED "Pilihan tidak valid!\n" RESET); break; }
                
                printf("Requirements (linked list, api server, web server, machine learning, async): ");
                fgets(input, MAX_INPUT, stdin);
                input[strcspn(input, "\n")] = 0;
                
                ai_codeagent_generate(language, input, output);
                printf(GREEN "\n💻 Generated Code:\n\n%s\n" RESET, output);
                break;
                
            case 3: // Debug
                printf(CYAN "\n=== CODEAGENT DEBUG ===" RESET "\n");
                printf("Masukkan deskripsi error (null pointer, segmentation fault, memory leak, infinite loop, race condition, sql injection, deadlock): ");
                fgets(input, MAX_INPUT, stdin);
                input[strcspn(input, "\n")] = 0;
                
                ai_codeagent_debug("", input, output);
                printf(GREEN "\n🔧 Debug & Fix:\n%s\n" RESET, output);
                break;
                
            case 4: // Review
                printf(CYAN "\n=== CODEAGENT CODE REVIEW ===" RESET "\n");
                printf("Masukkan kode untuk direview (atau keyword: goto, malloc, eval, SELECT, printf): ");
                fgets(code_input, MAX_INPUT * 4, stdin);
                code_input[strcspn(code_input, "\n")] = 0;
                
                ai_codeagent_review(code_input, output);
                printf(GREEN "\n📝 Code Review:\n%s\n" RESET, output);
                break;
                
            case 5: // Optimize
                printf(CYAN "\n=== CODEAGENT OPTIMIZE ===" RESET "\n");
                printf("Masukkan kode atau pattern (ArrayList, SELECT *, String+, == String): ");
                fgets(code_input, MAX_INPUT * 4, stdin);
                code_input[strcspn(code_input, "\n")] = 0;
                
                ai_codeagent_optimize(code_input, output);
                printf(GREEN "\n⚡ Optimization:\n%s\n" RESET, output);
                break;
                
            case 6: // Explain
                printf(CYAN "\n=== CODEAGENT EXPLAIN ===" RESET "\n");
                printf("Masukkan kode untuk dijelaskan (struct, pthread, SELECT, def, class, async): ");
                fgets(code_input, MAX_INPUT * 4, stdin);
                code_input[strcspn(code_input, "\n")] = 0;
                
                ai_codeagent_explain(code_input, output);
                printf(GREEN "\n📖 Explanation:\n%s\n" RESET, output);
                break;
                
            default:
                printf(RED "Pilihan tidak valid!\n" RESET);
        }
        
        printf(YELLOW "\nTekan Enter untuk lanjut..." RESET);
        getchar();
    }
}

/* Handle Roadmap */
void handle_roadmap() {
    char output[MAX_OUTPUT];
    
    printf(CYAN "\n=== OS-MINI AI EVOLUTION ROADMAP ===" RESET "\n\n");
    ai_show_roadmap(output);
    printf(GREEN "%s\n" RESET, output);
}

/* Main function */
int main(int argc, char *argv[]) {
    int choice;
    
    // Check for command-line mode
    if (argc > 1) {
        char output[MAX_OUTPUT];
        
        if (strcmp(argv[1], "--health") == 0) {
            ai_health_analyze(argv[2] ? argv[2] : "", output);
        } else if (strcmp(argv[1], "--edu") == 0) {
            ai_edu_recommend(argv[2] ? argv[2] : "", output);
        } else if (strcmp(argv[1], "--codeagent") == 0) {
            ai_codeagent_analyze(argv[2] ? argv[2] : "", output);
        } else if (strcmp(argv[1], "--codegen") == 0) {
            ai_codeagent_generate(argv[2] ? argv[2] : "c", argv[3] ? argv[3] : "", output);
        } else if (strcmp(argv[1], "--debug") == 0) {
            ai_codeagent_debug("", argv[2] ? argv[2] : "", output);
        } else if (strcmp(argv[1], "--review") == 0) {
            ai_codeagent_review(argv[2] ? argv[2] : "", output);
        } else {
            printf("Usage: %s [--domain] [input]\n", argv[0]);
            printf("Domains: --health, --edu, --codeagent, --codegen, --debug, --review\n");
            return 1;
        }
        
        printf("%s\n", output);
        return 0;
    }
    
    // Interactive mode
    print_banner();
    
    while (1) {
        print_menu();
        
        if (scanf("%d", &choice) != 1) {
            printf(RED "Error: Invalid input!\n" RESET);
            break;
        }
        getchar(); // consume newline
        
        switch(choice) {
            case 1:
                handle_health();
                break;
            case 2:
                handle_education();
                break;
            case 3:
                handle_finance();
                break;
            case 4:
                handle_manufacturing();
                break;
            case 5:
                handle_iot();
                break;
            case 6:
                handle_smartcity();
                break;
            case 7:
                handle_governance();
                break;
            case 8:
                handle_future();
                break;
            case 9:
                handle_codeagent();
                break;
            case 10:
                handle_roadmap();
                break;
            case 0:
                printf(GREEN "\nTerima kasih telah menggunakan OS-Mini AI!\n" RESET);
                printf(CYAN "Keep Learning, Keep Innovating! 🚀\n" RESET);
                return 0;
            default:
                printf(RED "Pilihan tidak valid!\n" RESET);
        }
        
        printf(YELLOW "\nTekan Enter untuk lanjut..." RESET);
        getchar();
    }
    
    return 0;
}

