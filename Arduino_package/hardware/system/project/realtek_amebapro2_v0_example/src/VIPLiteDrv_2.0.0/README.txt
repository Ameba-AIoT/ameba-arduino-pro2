
1. VIPLite folder organization.

    driver/
        NBG parser in this folder, load NBG to video memory for running commands.

    hal/
        user/   viplite hal user space for linux. 
        kernel/ viplite hal kernel space for linux. 
        user and kernel just design for linux platform.In a flat system, such as FreeRTOS, the customer can simple call the kernel functions here. This is heavily dependent on how the system defines it.
        
    sdk/
        sdk/inc/ viplite header folder.
           

    
2. VIPLite driver naming rules.
    1. user space function name : 
       viphal_xxx
       viphal_os_xxxx  for system function defines
       gcvip_xxx_xxx
    2. user space structure name : gcvip_xxx_t
    3. user space variable name : gcvip_xxx
    4. kernel space function name :  vipdrv_xxx
    5. kernel space structure name: vipdrv_xxx_t
    6. enumerate name : gcvip_xxx_e
    7. Public to application name of function and structure:  vip_xxxx_xxx
    
3. Build VIPLite driver on Linux.
    1. configure toolchains and build option in build_drv.sh
    2. ./build_drv.sh install
    
    Build Option:
    export USE_LINUX_CMA=1 is allocated a memory from Linux CMA for video memory.
    export PLATFORM_NAME=xxxx is specify platform code path. is vendor company name.
    export SOC_CONFIG is board/project name.
    export USE_LINUX_PCIE_DEVICE=1 is used Linux PCIE device driver. export USE_PCIE_MSI=1, enable PCIE MSI interrupt.
    export USE_LINUX_PLATFORM_DEVICE is used Linux platform device driver.
    export FPGA_BUILD=1 is specify to build for FPGA.
    export USE_SECURE=1 is build security solution. VIPLite should be ported into TrustZone.
    export AUTO_CORRECT_CONFLICTS=1 is enabled automatically correct conflicting compilation switches in vip_lite_config.h
    
    
4. Build VIPLite driver on freesRTOS
    1. include makefile.freeRTOS into makefile of freeRTOS system.
    2. build freeRTOS system.
    3. VIPLite drvier is builded into freeRTOS together.
    
    
5. Build VIPLite driver on Android
    1. source Android build environment
    2. mm
