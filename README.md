# SquareLine_Studio_Minimum_Requirement
This is a bare minimum code you will need to make your ui exported file from SquareLine Studio working with your ESP32 board. The main branch use a ST7789 screen, a GT911 controller for touchscreen on an ALL-IN-ONE yellow board (ESP32-2432S032 capacitive variant).

You might have to change the pins in the main.cpp file under the src folder before sending it to your board.
This code use the TFT_eSPI library to communicate with the screen and the TAMC_GT911 library to communicate with the GT911 controller.

You have a lot of information in main.cpp file to help configure this file to your own needs.
All comment are in English and French.

I might also add a link to download all PDF and schematics of the board.
