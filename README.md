
<h1 align="center">Ameba Arduino SDK</h1>
<h2 align="center">ameba-arduino-pro2</h2>

<div align="center">
  <a href="https://github.com/Ameba-AIoT/ameba-arduino-pro2/stargazers">
    <img src="https://img.shields.io/github/stars/Ameba-AIoT/ameba-arduino-pro2?style=for-the-badge&logo=github&label=Stars&logoColor=white&color=22c55e" alt="GitHub stars">
  </a>
  <a href="https://github.com/Ameba-AIoT/ameba-arduino-pro2/releases">
    <img src="https://img.shields.io/github/v/release/Ameba-AIoT/ameba-arduino-pro2?style=for-the-badge&logo=github&label=Release&logoColor=white&color=1a67af" alt="GitHub release">
  </a>
</div>

[![Build Status](https://img.shields.io/github/actions/workflow/status/Ameba-AIoT/ameba-arduino-pro2/CI_compile_examples.yml?branch=dev&event=push&label=Build%20Status)](https://github.com/Ameba-AIoT/ameba-arduino-pro2/actions/workflows/CI_compile_examples.yml)
[![Check word spell](https://img.shields.io/github/actions/workflow/status/Ameba-AIoT/ameba-arduino-pro2/spell_check.yml?branch=dev&event=schedule&label=Word%20Spell%20Check)](https://github.com/Ameba-AIoT/ameba-arduino-pro2/actions/workflows/spell_check.yml)
[![MBED Coding Style](https://img.shields.io/github/actions/workflow/status/Ameba-AIoT/ameba-arduino-pro2/coding_style_check.yml?branch=dev&event=schedule&label=MBED%20Coding%20Style%20Check)](https://github.com/Ameba-AIoT/ameba-arduino-pro2/actions/workflows/coding_style_check.yml)

#### Early Release
[![Release Version](https://img.shields.io/github/release/Ameba-AIoT/ameba-arduino-pro2/all.svg)](https://github.com/Ameba-AIoT/ameba-arduino-pro2/releases/)
[![Release Date](https://img.shields.io/github/release-date-pre/Ameba-AIoT/ameba-arduino-pro2.svg)](https://github.com/Ameba-AIoT/ameba-arduino-pro2/releases/)

#### Latest Release
[![Release Version](https://img.shields.io/github/release/Ameba-AIoT/ameba-arduino-pro2.svg)](https://github.com/Ameba-AIoT/ameba-arduino-pro2/releases/latest/)
[![Release Date](https://img.shields.io/github/release-date/Ameba-AIoT/ameba-arduino-pro2.svg)](https://github.com/Ameba-AIoT/ameba-arduino-pro2/releases/latest/)

## 1. About `dev` & `main` branch

|Branch|Usage|Remarks|
|:-----|:-----|:-----|
|`main` | stable release| https://github.com/Ameba-AIoT/ameba-arduino-pro2/raw/main/Arduino_package/package_realtek_amebapro2_index.json|
|`dev`| merge `Pull Request` & early release| https://github.com/Ameba-AIoT/ameba-arduino-pro2/raw/dev/Arduino_package/package_realtek_amebapro2_early_index.json|


For all `release` information, please visit this [link](https://github.com/Ameba-AIoT/ameba-arduino-pro2/releases).

</br>

## 2. How to add Realtek Ameba Arduino package to `Arduino IDE`:

> You can refer to this link to get started: [https://ameba-doc-arduino-sdk.readthedocs-hosted.com/en/latest/ameba_pro2/amb82-mini/index.html](https://ameba-doc-arduino-sdk.readthedocs-hosted.com/en/latest/ameba_pro2/amb82-mini/index.html)
> , or follow the steps below.

1. **Add Ameba Arduino SDK link to *Arduino IDE Additional Boards Manager***

    > Arduino IDE 1.6.5 and above versions support third party hardware so please make sure to use the latest Arduino IDE for better experience.

    Therefore, you need to add Ameba Arduino SDK link in 
    
    **"File" -> "Preferences" -> "Additional Boards Manager URLs:"**

    Copy and paste the following link into the field and click "OK",

    https://github.com/Ameba-AIoT/ameba-arduino-pro2/raw/main/Arduino_package/package_realtek_amebapro2_early_index.json

    > We also suggest to enable "Show verbose output" options on "compilation" and "upload" in Preference for easier debugging.
    
    </br>

2. **Install Ameba board in *"Board Manager"***

    Open **"Tools" -> "Board" -> "Board Manager"**, wait for it to update additional hardware configurations, then type **"ameba"** in the search bar, you will see Realtek Ameba in the list.

    Press **"Install"** to start the installation.
    
    </br>

3. **Select your Ameba model in *"Tools" -> "Board" -> "AmebaPro2 ARM (32-bits) Boards"***

    > Make sure you select the correct model for your board, otherwise your program might not work properly 

    Now you are **ready** to develop and upload firmware onto Ameba.

    For more information, please refer to https://www.amebaiot.com/en/ameba-arduino-summary/
    
    </br>

## 3. License and thirdparty licenses

> The overall project is licensed under the MIT License. See the [LICENSE](https://github.com/Ameba-AIoT/ameba-arduino-pro2?tab=MIT-1-ov-file) file for details.
> This project uses executables for tools from [CMake v3.29.6](https://github.com/Kitware/CMake/releases/tag/v3.29.6) which is licensed under the BSD 3-clause License. See the [LICENSE](https://github.com/Kitware/CMake?tab=License-1-ov-file) or "/third_party_licenses/" file for details.

</br>
