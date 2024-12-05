#include "mp3dec.h"
#include "audio_api.h"
#include "helix_mp3_drv.h"
#define MP3_MAX_FRAME_SIZE        (1600)
#define BUFFER_SIZE               (1500)
#define AUDIO_DMA_PAGE_SIZE       (2304)
#define I2S_DMA_PAGE_SIZE         2304
#define MP3_DATA_CACHE_SIZE       (BUFFER_SIZE + 2 * MP3_MAX_FRAME_SIZE)
#define TX_PAGE_SIZE              AUDIO_DMA_PAGE_SIZE    // 64*N bytes, max: 4095. 128, 4032
#define TX_PAGE_NUM               AUDIO_DMA_PAGE_NUM
#define RX_PAGE_SIZE              AUDIO_DMA_PAGE_SIZE    // 64*N bytes, max: 4095. 128, 4032
#define RX_PAGE_NUM               AUDIO_DMA_PAGE_NUM
#define AUDIO_DMA_PAGE_NUM        4
#define AUDIO_PKT_QUEUE_LENGTH    (50)
#define AUDIO_TX_PCM_QUEUE_LENGTH (10)
static uint32_t audio_tx_pcm_cache_len = 0;
static int16_t audio_tx_pcm_cache[AUDIO_DMA_PAGE_SIZE * 3 / 4];

#ifndef SDRAM_BSS_SECTION
#define SDRAM_BSS_SECTION
SECTION(".sdram.bss")
#endif
static xQueueHandle audio_tx_pcm_queue = NULL;
SDRAM_BSS_SECTION static uint8_t decodebuf[8192];
static audio_t g_taudio;
static uint8_t dma_txdata[TX_PAGE_SIZE * TX_PAGE_NUM] __attribute__((aligned(0x20)));
static uint8_t dma_rxdata[RX_PAGE_SIZE * RX_PAGE_NUM] __attribute__((aligned(0x20)));


void audio_play_binary_array(uint8_t *srcbuf, uint32_t len)
{
    uint8_t *inbuf;
    int bytesLeft;

    int ret;
    HMP3Decoder hMP3Decoder;
    MP3FrameInfo frameInfo;

    uint8_t first_frame = 1;
    int ch_sel = 0;
    short *wTemp;
    audio_tx_pcm_queue = xQueueCreate(AUDIO_TX_PCM_QUEUE_LENGTH, AUDIO_DMA_PAGE_SIZE);
    hMP3Decoder = MP3InitDecoder();
    MP3DecodeSetChannel(ch_sel);

    inbuf = srcbuf;
    bytesLeft = len;
    while (bytesLeft > 0) {
        if (bytesLeft > 6) {
            ret = MP3Decode(hMP3Decoder, &inbuf, &bytesLeft, (short *)decodebuf, 0);
            wTemp = (short *)decodebuf;
        } else {
            ret = ERR_MP3_INDATA_UNDERFLOW;
        }
        if (!ret) {
            MP3GetLastFrameInfo(hMP3Decoder, &frameInfo);
            wTemp = (short *)decodebuf;
            if (frameInfo.nChans == 2) {
                for (int i = 0; i < 2048; i++) {
                    wTemp[i] = wTemp[2 * i + ch_sel % 2];
                }
                frameInfo.outputSamps /= 2;
            }

            if (first_frame) {
                initialize_audio(frameInfo.samprate);
                first_frame = 0;
            }
            audio_play_pcm((int16_t *)decodebuf, frameInfo.outputSamps);
        } else {
            if (ret != ERR_MP3_INDATA_UNDERFLOW) {
                printf("[ERROR] %d\r\n", ret);
            }
            break;
        }
    }

    audio_deinit(&g_taudio);
    printf("audio deinitialized\r\n");
    printf("decoding finished\r\n");
}

void initialize_audio(int sample_rate)
{
    uint8_t smpl_rate_idx = ASR_16KHZ;
    // audio_sr smpl_rate_idx = ASR_16KHZ;

    switch (sample_rate) {
        case 8000:
            smpl_rate_idx = ASR_8KHZ;
            break;
        case 16000:
            smpl_rate_idx = ASR_16KHZ;
            break;
        case 32000:
            smpl_rate_idx = ASR_32KHZ;
            break;
        case 44100:
            smpl_rate_idx = ASR_44p1KHZ;
            break;
        case 48000:
            smpl_rate_idx = ASR_48KHZ;
            break;
        case 88200:
            smpl_rate_idx = ASR_88p2KHZ;
            break;
        case 96000:
            smpl_rate_idx = ASR_96KHZ;
            break;
        default:
            break;
    }

    audio_init(&g_taudio, OUTPUT_SINGLE_EDNED, MIC_SINGLE_EDNED, AUDIO_CODEC_2p8V);
    audio_dac_digital_vol(&g_taudio, 0xAF / 2);

    // Init TX dma

    audio_set_dma_buffer(&g_taudio, dma_txdata, dma_rxdata, AUDIO_DMA_PAGE_SIZE, AUDIO_DMA_PAGE_NUM);


    audio_rx_irq_handler(&g_taudio, (audio_irq_handler)audio_rx_complete, (uint32_t *)&g_taudio);

    // Init TX dma
    audio_tx_irq_handler(&g_taudio, (audio_irq_handler)audio_tx_complete, (uint32_t *)&g_taudio);

    audio_set_param(&g_taudio, smpl_rate_idx, WL_16BIT);    // ASR_8KHZ, ASR_16KHZ //ASR_48KHZ
    // audio_mic_analog_gain(&g_taudio, 1, AUDIO_MIC_40DB); // default 0DB


    /* Use (DMA page count -1) because occur RX interrupt in first */
    for (int i = 0; i < (AUDIO_DMA_PAGE_NUM - 1); i++) {
        uint8_t *ptx_buf = audio_get_tx_page_adr(&g_taudio);
        if (ptx_buf) {
            memset(ptx_buf, 0x0, AUDIO_DMA_PAGE_SIZE);
            audio_set_tx_page(&g_taudio, ptx_buf);
        }
        audio_set_rx_page(&g_taudio);
    }


    audio_trx_start(&g_taudio);
}

void audio_tx_complete(uint32_t arg, uint8_t *pbuf)
{
    uint8_t *ptx_buf;

    ptx_buf = (uint8_t *)audio_get_tx_page_adr(&g_taudio);
    if (xQueueReceiveFromISR(audio_tx_pcm_queue, ptx_buf, NULL) != pdPASS) {
        memset(ptx_buf, 0, AUDIO_DMA_PAGE_SIZE);
    }
    audio_set_tx_page(&g_taudio, (uint8_t *)ptx_buf);
}

void audio_rx_complete(uint32_t arg, uint8_t *pbuf)
{
    audio_t *obj = (audio_t *)arg;
    audio_set_rx_page(obj);
}

void audio_play_pcm(int16_t *buf, uint32_t len)
{
    for (int i = 0; i < len; i++) {
        audio_tx_pcm_cache[audio_tx_pcm_cache_len++] = buf[i];
        if (audio_tx_pcm_cache_len == AUDIO_DMA_PAGE_SIZE / 2) {
            xQueueSend(audio_tx_pcm_queue, audio_tx_pcm_cache, portMAX_DELAY);
            audio_tx_pcm_cache_len = 0;
        }
    }
}
