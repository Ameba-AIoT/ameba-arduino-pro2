#pragma once

extern const int PORT;
extern const char *server;
extern const char *resource;

extern const char *OtaState[];
extern const char *g_otaState;

void ota_http(void);
