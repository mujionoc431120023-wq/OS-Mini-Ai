/* ============================================================
   IoT CONTROLLER - Smart Home Control
   Controls smart devices via network commands
   ============================================================ */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/ai_hub.h"

#define MAX_DEVICES 10

/* Smart device structure */
typedef struct {
    char name[30];
    int state; /* 0: OFF, 1: ON */
    char ip_address[16];
} smart_device_t;

/* Device database (simulated) */
static smart_device_t home_devices[MAX_DEVICES] = {
    {"Lampu Ruang Tamu", 0, "192.168.1.101"},
    {"Lampu Kamar Tidur", 0, "192.168.1.102"},
    {"AC Ruang Tamu", 0, "192.168.1.103"},
    {"AC Kamar", 0, "192.168.1.104"},
    {"Kamera Depan", 0, "192.168.1.105"},
    {"Door Lock", 0, "192.168.1.106"},
    {"Speaker", 0, "192.168.1.107"},
    {"TV", 0, "192.168.1.108"},
    {"Water Heater", 0, "192.168.1.109"},
    {"Robot Vacuum", 0, "192.168.1.110"}
};

static int device_count = 10;

/* Control a specific device */
int ai_iot_control(const char *target, int action) {
    if (!target) return 0;
    
    char log_buf[256];
    char target_lower[50];
    strncpy(target_lower, target, 49);
    target_lower[49] = '\0';
    
    /* Convert to lowercase */
    for (int i = 0; target_lower[i]; i++) {
        target_lower[i] = (char)tolower(target_lower[i]);
    }
    
    /* Search for matching device */
    for (int i = 0; i < device_count; i++) {
        char device_lower[50];
        strncpy(device_lower, home_devices[i].name, 49);
        device_lower[49] = '\0';
        
        for (int j = 0; device_lower[j]; j++) {
            device_lower[j] = (char)tolower(device_lower[j]);
        }
        
        /* Check if target matches device name */
        if (strstr(device_lower, target_lower) || 
            (strstr(target_lower, "lampu") && strstr(device_lower, "lampu")) ||
            (strstr(target_lower, "ac") && strstr(device_lower, "ac")) ||
            (strstr(target_lower, "kamera") && strstr(device_lower, "kamera"))) {
            
            home_devices[i].state = action;
            
            snprintf(log_buf, sizeof(log_buf), 
                    "IOT: %s changed to %s", 
                    home_devices[i].name, 
                    action ? "ON" : "OFF");
            ai_log_blackbox("INFO", "IOT_CONTROLLER", log_buf);
            
            /* In real implementation, would send HTTP/UDP command to device */
            return 1; /* Success */
        }
    }
    
    ai_log_blackbox("WARN", "IOT_CONTROLLER", "Device not found");
    return 0;
}

/* Get status of all devices */
const char* ai_iot_get_status(void) {
    static char status_report[512];
    int offset = 0;
    
    offset += snprintf(status_report + offset, 512 - offset, "=== Device Status ===\n");
    
    for (int i = 0; i < device_count; i++) {
        offset += snprintf(status_report + offset, 512 - offset,
                         "%s: %s\n", 
                         home_devices[i].name,
                         home_devices[i].state ? "ON" : "OFF");
    }
    
    return status_report;
}

/* Process IoT commands from user input */
int ai_iot_process(const char *device, const char *data, char *resp) {
    if (!data || !resp) return 0;
    
    char data_lower[256];
    strncpy(data_lower, data, 255);
    data_lower[255] = '\0';
    
    for (int i = 0; data_lower[i]; i++) {
        data_lower[i] = (char)tolower(data_lower[i]);
    }
    
    /* Determine action from command */
    int action = -1;
    if (strstr(data_lower, "nyalakan") || strstr(data_lower, "hidupkan") || 
        strstr(data_lower, "on") || strstr(data_lower, "enable")) {
        action = 1;
    } else if (strstr(data_lower, "matikan") || strstr(data_lower, "nonaktifkan") || 
               strstr(data_lower, "off") || strstr(data_lower, "disable")) {
        action = 0;
    }
    
    if (action == -1) {
        /* Just query status */
        strcpy(resp, ai_iot_get_status());
        return 0;
    }
    
    /* Try to control device */
    if (device) {
        if (ai_iot_control(device, action)) {
            snprintf(resp, MAX_OUTPUT, 
                    "Siap, saya telah %s perangkat %s.", 
                    action ? "menyalakan" : "mematikan",
                    device);
            return 1;
        }
    }
    
    /* Try to find device from data */
    if (ai_iot_control(data, action)) {
        snprintf(resp, MAX_OUTPUT, 
                "Siap, saya telah %s perangkat.", 
                action ? "menyalakan" : "mematikan");
        return 1;
    }
    
    strcpy(resp, "Maaf, saya tidak menemukan perangkat yang Anda maksud.");
    return 0;
}

