#pragma once

extern int _port;
extern char *_server;
extern const char *resource;

extern const char *OtaState[];
extern const char *g_otaState;

void ota_http(void);
