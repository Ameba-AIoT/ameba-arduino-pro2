                  HOW TO USE TFT_ESPI LIBRARY ON AMEBAPRO2
================================================================================
1. Download tft_eSPI into your "C:\Users\USERNAME\Documents\Arduino\libraries" 


                     TO DOWNLOAD THE LATEST LIBRARY
================================================================================
1. Download tft_eSPI library from https://github.com/Bodmer/TFT_eSPI 
   (also available in library manager).
2. Modify SPI CS, Reset and DC pin configuration accordingly in "User_Setup.h".
3. Comment out all "pinMode(TFT_CS, OUTPUT)" & "ltoa();" functions in "TFT_sSPI.cpp" 
   to avoid pin conflict error.
    
