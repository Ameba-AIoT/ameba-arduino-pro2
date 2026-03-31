/******************************************************************************
*
* Copyright(c) 2007 - 2018 Realtek Corporation. All rights reserved.
*
******************************************************************************/

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <rtl8735b.h>
#include <hal_cache.h>
#include <hal_sys_ctrl.h>
#include <osdep_service.h>
#include <device_lock.h>
#include <ff.h>
#include <fatfs_sdcard_api.h>
#include <fwfs.h>
#include <nn_file_op.h>
#include <nnlite_api.h>

static int nnlite_inited = 0;

static void nnlite_get_mutex(void)
{
    device_mutex_lock(RT_DEV_LOCK_NN);
}

static void nnlite_put_mutex(void)
{
    device_mutex_unlock(RT_DEV_LOCK_NN);
}

static int nnlite_is_inited(void)
{
    return nnlite_inited;
}

extern void vipnn_hardware_init(void);
static int nnlite_init_nn(void)
{
    int ret = 0;
    nnlite_get_mutex();
    if (nnlite_inited == 1) {
        goto exit;
    }
    vipnn_hardware_init();
    vip_status_e status = vip_init();
    if (status != VIP_SUCCESS) {
        ret = -1;
        goto exit;
    }
    printf("VIPLite Drv version 0x%x\r\n", vip_get_version());
    nnlite_inited = 1;

exit:
    nnlite_put_mutex();
    return ret;
}

static void nnlite_dump_network_tensor_params(nnlite_ctx_t *ctx)
{
    printf("---------------------------------\r\n");
    printf("input count %d, output count %d\r\n", ctx->input_count, ctx->output_count);
    for (int i = 0; i < ctx->input_count; i++) {
        printf("input param %d\r\n", i);
        printf("\tdata_format  %x\r\n", ctx->vip_param_in[i].data_format);
        printf("\tmemory_type  %x\r\n", ctx->vip_param_in[i].memory_type);
        printf("\tnum_of_dims  %x\r\n", ctx->vip_param_in[i].num_of_dims);
        //printf("\tquant_data   %x\r\n", ctx->vip_param_in[i].quant_data);
        printf("\tquant_format %x\r\n", ctx->vip_param_in[i].quant_format);
        printf("\tquant_data  ");
        switch (ctx->vip_param_in[i].quant_format) {
        case VIP_BUFFER_QUANTIZE_DYNAMIC_FIXED_POINT:
            printf(", dfp=%d\r\n", ctx->vip_param_in[i].quant_data.dfp.fixed_point_pos);
            break;
        case VIP_BUFFER_QUANTIZE_TF_ASYMM:
            printf(", scale=%f, zero_point=%d\r\n", ctx->vip_param_in[i].quant_data.affine.scale,
                   ctx->vip_param_in[i].quant_data.affine.zeroPoint);
            break;
        default:
            printf(", none-quant\r\n");
        }
        //printf("\tsizes        %x\r\n", ctx->vip_param_in[i].sizes);
        printf("\tsizes        ");
        for (int x = 0; x < 6; x++) {
            printf("%d ", ctx->vip_param_in[i].sizes[x]);
        }
        printf("\r\n");
    }
    for (int i = 0; i < ctx->output_count; i++) {
        printf("output param %d\r\n", i);
        printf("\tdata_format  %x\r\n", ctx->vip_param_out[i].data_format);
        printf("\tmemory_type  %x\r\n", ctx->vip_param_out[i].memory_type);
        printf("\tnum_of_dims  %x\r\n", ctx->vip_param_out[i].num_of_dims);
        //printf("\tquant_data   %x\r\n", ctx->vip_param_out[i].quant_data);
        printf("\tquant_format %x\r\n", ctx->vip_param_out[i].quant_format);
        printf("\tquant_data  ");
        switch (ctx->vip_param_out[i].quant_format) {
        case VIP_BUFFER_QUANTIZE_DYNAMIC_FIXED_POINT:
            printf(", dfp=%d\r\n", ctx->vip_param_out[i].quant_data.dfp.fixed_point_pos);
            break;
        case VIP_BUFFER_QUANTIZE_TF_ASYMM:
            printf(", scale=%f, zero_point=%d\r\n", ctx->vip_param_out[i].quant_data.affine.scale,
                   ctx->vip_param_out[i].quant_data.affine.zeroPoint);
            break;
        default:
            printf(", none-quant\r\n");
        }
        //printf("\tsizes        %x\r\n", ctx->vip_param_out[i].sizes);
        printf("\tsizes        ");
        for (int x = 0; x < 6; x++) {
            printf("%d ", ctx->vip_param_out[i].sizes[x]);
        }
        printf("\r\n");
    }
    printf("---------------------------------\r\n");
}

static int nnlite_parse_tensor_params(nnlite_ctx_t *ctx)
{
    vip_network network = ctx->network;

    int i = 0;

    vip_query_network(network, VIP_NETWORK_PROP_INPUT_COUNT, &ctx->input_count);
    if (ctx->input_count > MAX_TENSOR_NUM) {
        return -1;
    }

    vip_query_network(network, VIP_NETWORK_PROP_OUTPUT_COUNT, &ctx->output_count);
    if (ctx->output_count > MAX_TENSOR_NUM) {
        return -1;
    }

    for (i = 0; i < ctx->input_count; i++) {
        vip_buffer_create_params_t *param = &ctx->vip_param_in[i];
        memset(param, 0, sizeof(vip_buffer_create_params_t));
        param->memory_type = VIP_BUFFER_MEMORY_TYPE_DEFAULT;
        vip_query_input(network, i, VIP_BUFFER_PROP_DATA_FORMAT, &param->data_format);
        vip_query_input(network, i, VIP_BUFFER_PROP_NUM_OF_DIMENSION, &param->num_of_dims);
        vip_query_input(network, i, VIP_BUFFER_PROP_SIZES_OF_DIMENSION, param->sizes);
        vip_query_input(network, i, VIP_BUFFER_PROP_QUANT_FORMAT, &param->quant_format);
        switch (param->quant_format) {
        case VIP_BUFFER_QUANTIZE_DYNAMIC_FIXED_POINT:
            vip_query_input(network, i, VIP_BUFFER_PROP_FIXED_POINT_POS,
                            &param->quant_data.dfp.fixed_point_pos);
            break;
        case VIP_BUFFER_QUANTIZE_TF_ASYMM:
            vip_query_input(network, i, VIP_BUFFER_PROP_TF_SCALE,
                            &param->quant_data.affine.scale);
            vip_query_input(network, i, VIP_BUFFER_PROP_TF_ZERO_POINT,
                            &param->quant_data.affine.zeroPoint);
        default:
            break;
        }
    }

    for (i = 0; i < ctx->output_count; i++) {
        vip_buffer_create_params_t *param = &ctx->vip_param_out[i];
        memset(param, 0, sizeof(vip_buffer_create_params_t));
        param->memory_type = VIP_BUFFER_MEMORY_TYPE_DEFAULT;
        vip_query_output(network, i, VIP_BUFFER_PROP_DATA_FORMAT, &param->data_format);
        vip_query_output(network, i, VIP_BUFFER_PROP_NUM_OF_DIMENSION, &param->num_of_dims);
        vip_query_output(network, i, VIP_BUFFER_PROP_SIZES_OF_DIMENSION, param->sizes);
        vip_query_output(network, i, VIP_BUFFER_PROP_QUANT_FORMAT, &param->quant_format);
        switch (param->quant_format) {
        case VIP_BUFFER_QUANTIZE_DYNAMIC_FIXED_POINT:
            vip_query_output(network, i, VIP_BUFFER_PROP_FIXED_POINT_POS,
                             &param->quant_data.dfp.fixed_point_pos);
            break;
        case VIP_BUFFER_QUANTIZE_TF_ASYMM:
            vip_query_output(network, i, VIP_BUFFER_PROP_TF_SCALE,
                             &param->quant_data.affine.scale);
            vip_query_output(network, i, VIP_BUFFER_PROP_TF_ZERO_POINT,
                             &param->quant_data.affine.zeroPoint);
            break;
        default:
            break;
        }
    }

    nnlite_dump_network_tensor_params(ctx);
    return 0;
}

extern void *vipnn_allocate_videomemory(size_t size);
static int nnlite_load_model_from_fwfs(nnlite_model_t *model)
{
    void *fd = nn_f_open((char*)model->filename, M_NORMAL);
    if (fd == NULL) {
        printf("nn_f_open %s failed\r\n", model->filename);
        return -1;
    }
    nn_f_seek(fd, 0, SEEK_END);
    model->size = nn_f_tell(fd);
    nn_f_seek(fd, 0, SEEK_SET);
    model->data = vipnn_allocate_videomemory(model->size);
    if (model->data == NULL) {
        printf("malloc %lu bytes failed\r\n", model->size);
        nn_f_close(fd);
        return -1;
    }
    nn_f_read(fd, model->data, model->size);
    nn_f_close(fd);
    dcache_clean_invalidate_by_addr((uint32_t *)model->data, model->size);
    return 0;
}

static int nnlite_load_model_from_sdcard(nnlite_model_t *model)
{
#if 0
    FILE *fp = fopen_with_folder(get_ai_demo_root(), (char*) model->filename, "rb");
    if (fp == NULL) {
        printf("fopen %s failed\r\n", model->filename);
        return -1;
    }
    fseek(fp, 0, SEEK_END);
    model->size = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    model->data = vipnn_allocate_videomemory(model->size);
    if (model->data == NULL) {
        printf("malloc %lu bytes failed\r\n", model->size);
        fclose(fp);
        return -1;
    }
    fread(model->data, 1, model->size, fp);
    fclose(fp);
    return 0;
#else
    printf("%s is unsupported!\r\n", __func__);
    return -1;
#endif
}

static int nnlite_create_network(nnlite_ctx_t *ctx)
{
    int status = 0;
    if (ctx->model->type == NNLITE_CREATE_NETWORK_TYPE_FWFS) {
        nnlite_load_model_from_fwfs(ctx->model);
    } else if (ctx->model->type == NNLITE_CREATE_NETWORK_TYPE_SDCARD) {
        nnlite_load_model_from_sdcard(ctx->model);
    } else {
        printf("error: invalid model type\r\n");
        return -1;
    }

    status = vip_create_network(&(ctx->model->data), ctx->model->size, VIP_CREATE_NETWORK_FROM_FLASH, &ctx->network);
    if (status != VIP_SUCCESS) {
        printf("vip_create_network failed\r\n");
        return -1;
    }
    status = vip_query_network(ctx->network, VIP_NETWORK_PROP_NETWORK_NAME, ctx->model->network_name);
    if (status != VIP_SUCCESS) {
        printf("vip_query_network failed\r\n");
        return -1;
    }
    if (nnlite_parse_tensor_params(ctx) < 0) {
        printf("nnlite_parse_tensor_params failed\r\n");
        return -1;
    }
    status = vip_prepare_network(ctx->network);
    // status = nnlite_parse_network_params(ctx);
    
    return status;
}

nnlite_ctx_t* nnlite_deploy_model(nnlite_model_t *model)
{
    if (model == NULL) {
        printf("model is NULL\r\n");
        return NULL;
    }
    
    if (nnlite_is_inited() == 0) {
        int status = nnlite_init_nn();
        if (status != 0) {
            printf("nnlite_init_nn failed\r\n");
            return NULL;
        }
    }
    nnlite_ctx_t *ctx = (nnlite_ctx_t *)malloc(sizeof(nnlite_ctx_t));
    if (!ctx) {
        printf("malloc nnlite_ctx_t failed\r\n");
        return NULL;
    }
    memset(ctx, 0, sizeof(nnlite_ctx_t));
    ctx->model = model;
    nnlite_get_mutex();
    int status = nnlite_create_network(ctx);
    nnlite_put_mutex();
    if (status != 0) {
        printf("nnlite_create_network failed\r\n");
        free(ctx); ctx = NULL;
        return NULL;
    }
    printf("Deploy %s (%s)\r\n", ctx->model->modelname, ctx->model->network_name);
    return ctx;
}

extern void vipnn_free_videomemory(void *ptr);
void nnlite_destroy_model(nnlite_ctx_t *ctx)
{
    if (ctx == NULL) {
        printf("ctx is NULL\r\n");
        return;
    }

    vip_finish_network(ctx->network);
    vip_destroy_network(ctx->network);
    nnlite_destroy_in_tensor(ctx);
    nnlite_destroy_out_tensor(ctx);

    if (ctx->model->data) {
        vipnn_free_videomemory(ctx->model->data);
        ctx->model->data = NULL;
    }
    free(ctx);
}

int nnlite_run_model(nnlite_ctx_t *ctx)
{
    if (ctx == NULL) {
        printf("ctx is NULL\r\n");
        return -1;
    }

    vip_status_e status;
    uint32_t t1 = xTaskGetTickCount();
    nnlite_get_mutex();
    status = vip_run_network(ctx->network);
    nnlite_put_mutex();
    //printf("vip_run_network time: %d\r\n", xTaskGetTickCount() - t1);
    if (status != VIP_SUCCESS) {
        printf("vip_run_network failed\r\n");
        return -1;
    }

#if 0
    //vip_flush_buffer() doesn't work for viplite 1.8.0
    for (int i = 0; i < ctx->output_count; i++) {
        status = vip_flush_buffer(ctx->output_buffers[i], VIP_BUFFER_OPER_TYPE_INVALIDATE);
        if (status != VIP_SUCCESS)
            printf("error: vip_flush_buffer fail. %d %d\r\n", i, status);
    }
#endif

    return 0;
}

int nnlite_deploy_in_tensor(nnlite_ctx_t *ctx, int tensor_idx, void *data, uint32_t size, int zero_copy)
{
    if (ctx == NULL || data == NULL || size == 0 || tensor_idx >= ctx->input_count) {
        printf("%s error: Invalid params\r\n", __func__);
        return -1;
    }

    vip_status_e status;

    if (zero_copy) {
        if (size % 64 != 0) {
            printf("To use zero copy, the size should be aligned to 64 bytes\r\n");
            return -1;
        }
        nnlite_get_mutex();
        status = vip_create_buffer_from_handle(&ctx->vip_param_in[tensor_idx], data, size, &ctx->input_buffers[tensor_idx]);
        nnlite_put_mutex();
        dcache_clean_invalidate_by_addr((uint32_t *)data, size);
    } else {
        status = vip_create_buffer(&ctx->vip_param_in[tensor_idx], sizeof(vip_buffer_create_params_t), &ctx->input_buffers[tensor_idx]);
        if (status == VIP_SUCCESS) {
            void *ptr = vip_map_buffer(ctx->input_buffers[tensor_idx]);
            if (ptr != NULL) {
                memcpy(ptr, data, size);
                dcache_clean_by_addr((uint32_t *)ptr, size);
                vip_unmap_buffer(ctx->input_buffers[tensor_idx]);
            } else {
                printf("vip_map_buffer failed\r\n");
                return -1;
            }
        } else {
            printf("vip_create_buffer failed\r\n");
            return -1;
        }
    }
    if (status != VIP_SUCCESS) {
        printf("nnlite_deploy_in_tensor failed %d %d %d\r\n", tensor_idx, status, zero_copy);
        return -1;
    }

    vip_set_input(ctx->network, tensor_idx, ctx->input_buffers[tensor_idx]);
    return 0;
}

int nnlite_destroy_in_tensor(nnlite_ctx_t *ctx)
{
    if (ctx == NULL) {
        printf("%s error: Invalid params\r\n", __func__);
        return -1;
    }

    vip_status_e status;

    nnlite_get_mutex();
    for (int i = 0; i < ctx->input_count; i++) {
        if (ctx->input_buffers[i]) {
            status = vip_destroy_buffer(ctx->input_buffers[i]);
            if (status != VIP_SUCCESS)
                printf("error: vip_destroy_buffer fail. %d %d\r\n", i, status);
            ctx->input_buffers[i] = NULL;
        }
    }
    nnlite_put_mutex();

    return 0;
}

int nnlite_deploy_out_tensor(nnlite_ctx_t *ctx, int tensor_idx, void *data, uint32_t size, int zero_copy)
{
    if (ctx == NULL || data == NULL || size == 0 || tensor_idx >= ctx->output_count) {
        printf("%s error: Invalid params\r\n", __func__);
        return -1;
    }

    vip_status_e status;

    if (zero_copy) {
        if (size % 64 != 0) {
            printf("To use zero copy, the size should be aligned to 64 bytes\r\n");
            return -1;
        }
        nnlite_get_mutex();
        status = vip_create_buffer_from_handle(&ctx->vip_param_out[tensor_idx], data, size, &ctx->output_buffers[tensor_idx]);
        nnlite_put_mutex();
    } else {
        printf("%s: Only supports zero-copy mode. Please set zero_copy to 1.\r\n", __func__);
        printf("Or use nnlite_create_out_tensor() instead.\r\n");
        return -1;
    }
    if (status != VIP_SUCCESS) {
        printf("nnlite_deploy_out_tensor failed %d %d %d\r\n", tensor_idx, status, zero_copy);
        return -1;
    }

    status = vip_set_output(ctx->network, tensor_idx, ctx->output_buffers[tensor_idx]);
    if (status != VIP_SUCCESS) {
        printf("vip_set_output failed %d %d\r\n", tensor_idx, status);
        return -1;
    }

    return 0;
}

void* nnlite_create_out_tensor(nnlite_ctx_t *ctx, int tensor_idx)
{
    if (ctx == NULL || tensor_idx >= ctx->output_count) {
        printf("%s error: Invalid params\r\n", __func__);
        return NULL;
    }

    vip_status_e status;
    status = vip_create_buffer(&ctx->vip_param_out[tensor_idx], sizeof(vip_buffer_create_params_t), &ctx->output_buffers[tensor_idx]);
    if (status != VIP_SUCCESS) {
        printf("vip_create_buffer failed %d %d\r\n", tensor_idx, status);
        return NULL;
    }

    status = vip_set_output(ctx->network, tensor_idx, ctx->output_buffers[tensor_idx]);
    if (status != VIP_SUCCESS) {
        printf("vip_set_output failed %d %d\r\n", tensor_idx, status);
        return NULL;
    }

    void *ptr = vip_map_buffer(ctx->output_buffers[tensor_idx]);
    if (ptr == NULL) {
        printf("vip_map_buffer failed\r\n");
        return NULL;
    }
    
    return ptr;
}

int nnlite_flush_out_tensor(nnlite_ctx_t *ctx)
{
    vip_status_e status;
    int ret = 0;
    nnlite_get_mutex();
    for (int i = 0; i < ctx->output_count; i++) {
        status = vip_flush_buffer(ctx->output_buffers[i], VIP_BUFFER_OPER_TYPE_INVALIDATE);
        if (status != VIP_SUCCESS) {
            printf("error: vip_flush_buffer fail. %d %d\r\n", i, status);
            ret = -1;
        }
    }
    nnlite_put_mutex();
    return ret;
}

int nnlite_destroy_out_tensor(nnlite_ctx_t *ctx)
{
    if (ctx == NULL) {
        printf("%s error: Invalid params\r\n", __func__);
        return -1;
    }

    vip_status_e status;

    nnlite_get_mutex();
    for (int i = 0; i < ctx->output_count; i++) {
        if (ctx->output_buffers[i]) {
            status = vip_destroy_buffer(ctx->output_buffers[i]);
            if (status != VIP_SUCCESS)
                printf("error: vip_destroy_buffer fail. %d %d\r\n", i, status);
            ctx->output_buffers[i] = NULL;
        }
    }
    nnlite_put_mutex();

    return 0;
}

