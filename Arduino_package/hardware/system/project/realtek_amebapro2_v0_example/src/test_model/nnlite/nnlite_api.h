#ifndef _NNLITE_API_H_
#define _NNLITE_API_H_

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <vip_lite.h>

#define TENSOR_ZERO_COPY    1
#define MAX_TENSOR_NUM      20

typedef enum nnlite_create_network_type_e {
    NNLITE_CREATE_NETWORK_TYPE_FWFS,
    NNLITE_CREATE_NETWORK_TYPE_SDCARD
} nnlite_create_network_type_e;

typedef struct nnlite_model_s {
    nnlite_create_network_type_e type;
    const char *filename;
    const char *modelname;
    void *data;
    uint32_t size;

    // Initialize by vip_query_network()
    char network_name[64];
    //--------------------------------
} nnlite_model_t;

typedef struct nnlite_ctx_s {
    nnlite_model_t *model;
    vip_network network;
    vip_buffer_create_params_t vip_param_in[MAX_TENSOR_NUM];
    vip_buffer_create_params_t vip_param_out[MAX_TENSOR_NUM];

    vip_buffer input_buffers[MAX_TENSOR_NUM];
    vip_buffer output_buffers[MAX_TENSOR_NUM];

    //vipnn_params_t params;

    int input_count;
    int output_count;
} nnlite_ctx_t;

nnlite_ctx_t* nnlite_deploy_model(nnlite_model_t *model);
void nnlite_destroy_model(nnlite_ctx_t *ctx);
int nnlite_run_model(nnlite_ctx_t *ctx);
int nnlite_deploy_in_tensor(nnlite_ctx_t *ctx, int tensor_idx, void *data, uint32_t size, int zero_copy);
int nnlite_destroy_in_tensor(nnlite_ctx_t *ctx);
int nnlite_deploy_out_tensor(nnlite_ctx_t *ctx, int tensor_idx, void *data, uint32_t size, int zero_copy);
void* nnlite_create_out_tensor(nnlite_ctx_t *ctx, int tensor_idx);
int nnlite_flush_out_tensor(nnlite_ctx_t *ctx);
int nnlite_destroy_out_tensor(nnlite_ctx_t *ctx);

#endif
