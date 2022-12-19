If playback needs to be compliled, please change the below configuration, otherwise compile error will be occur

1. modify project/realtek_amebaLite_va0_example/GCC-RELEASE/amebalite_layout.ld
   increase KR4_BD_PSRAM DSP_BD_PSRAM address  0x60300000, for example(change 0x60300000 to 0x60500000):
   KR4_BD_PSRAM (rwx) :                    ORIGIN = 0x60180020, LENGTH = 0x60750000 - 0x60180020	/* KR4 BD PSRAM: 5951k */
   DSP_BD_PSRAM (rwx) :                    ORIGIN = 0x60750020, LENGTH = 0x60800000 - 0x60750020	/* DSP BD PSRAM: 703k */

2. modify project/realtek_amebaLite_va0_example/inc/inc_kr4/FreeRTOSConfig.h
   increase configTOTAL_HEAP_SIZE, for example(change 200 * 1024 to 2048 * 1024):
   #elif defined(CONFIG_AS_INIC_NP)
   #define configTOTAL_HEAP_SIZE           ( ( size_t ) ( 2048 * 1024 ) )
   Besides, increase configTOTAL_HEAP_SIZE to ( ( size_t ) ( 3072 * 1024 ) ) if plays two aac audio files at the same time.

3. enable playback configurations:
   cd project/realtek_amebaLite_va0_example/GCC-RELEASE/project_kr4: make menuconfig
   < Audio Config  ---> [*] Enable Media Framework, < Demux  ---> choose the extractors, < Codec  ---> choose the codecs.

4. enable https:
1). modify project/realtek_amebaLite_va0_example/GCC-RELEASE/project_kr4/vsdk/make/mbedtls/mbedtls-2.16.9/Makefile
   Add the following file to the compilation:
   ifeq ($(CONFIG_AS_INIC_AP), y)
   CSRC += $(DIR)/library/net_sockets.c
   endif

   CSRC += $(DIR)/library/arc4.c \
       $(DIR)/library/dhm.c \
       $(DIR)/library/ecdh.c \
       $(DIR)/library/ecdsa.c \
       $(DIR)/library/hmac_drbg.c \
       $(DIR)/library/pem.c \
       $(DIR)/library/pk.c \
       $(DIR)/library/pk_wrap.c \
       $(DIR)/library/pkwrite.c \
       $(DIR)/library/rsa.c \
       $(DIR)/library/oid.c \
       $(DIR)/library/base64.c \

2). modify component/ssl/mbedtls-2.16.9/include/mbedtls/config_rsa.h
   increase MBEDTLS_SSL_MAX_CONTENT_LEN to avoid mbedtls read error
   #define MBEDTLS_SSL_MAX_CONTENT_LEN 16*1024

5. modify component/lwip/api/lwipopts.h
   increase PBUF_POOL_SIZE to avoid slow downloading speed when playing two http/https audio at the same time.
   #define PBUF_POOL_SIZE 38

6. config wifi
1). cd project/realtek_amebaLite_va0_example/GCC-RELEASE/project_kr4: make menuconfig
   < CONFIG WIFI  ---> [*] Enable Wifi, [*] Enable INIC AP
   < CONFIG WIFI FW  ---> choose none
2). cd project/realtek_amebaLite_va0_example/GCC-RELEASE/project_km4: make menuconfig
   < CONFIG WIFI  ---> [*] Enable Wifi, [*] Enable INIC NP
   < CONFIG WIFI FW  ---> [*] Enable Wifi firmware, [*] Enable FW DRIVER COEXIST

7. enable playback tests
   modify project/realtek_amebaLite_va0_example/GCC-RELEASE/project_kr4/vsdk/make/audio/Makefile
   make -C frameworks/media/playback tests

8. Usage: player_test [OPTION...]
   [-m source_mode]         0: http source, 1: buffer data source; 2: sdcard source
   [-mc mix_count]          1: one playback, 2: two playbacks
   [-d delay_seconds]       delay seconds for the second playback to start, only effect when -mc is set 2
   [-F audio_path]          An audio file path to play

   for example:
   @player -m 0 -mc 1 -nt 0 -F http://192.168.31.226/1.mp3
   @player -m 1 -mc 2 -nt 1