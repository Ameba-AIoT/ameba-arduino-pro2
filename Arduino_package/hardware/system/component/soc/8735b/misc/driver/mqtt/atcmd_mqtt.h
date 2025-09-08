#ifndef _ATCMD_MQTT_H_
#define _ATCMD_MQTT_H_

#include "MQTTClient.h"

// Initialize
void atcmd_mqtt_init(void);

// Processing received MQTT AT commands
int atcmd_mqtt_process(const char *cmd, int cmd_len, char *response, int max_resp_len);

// Set up the MQTT client to send responses
void atcmd_mqtt_set_client(MQTTClient *client, const char *response_topic);

void atcmd_mqtt_deinit(void);

#endif