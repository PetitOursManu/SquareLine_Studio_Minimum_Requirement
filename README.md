# SquareLine_Studio_Minimum_Requirement

![Sc980f80372d74c34a31d29b93598fac74](https://github.com/PetitOursManu/SquareLine_Studio_Minimum_Requirement/assets/7190987/99f4d31e-3106-4482-96fb-140a57b1873d)

This is a bare minimum code you will need to make your ui exported file from SquareLine Studio working with your ESP32 board. The main git branch use a ST7789 screen, a GT911 controller for touchscreen on an ALL-IN-ONE yellow board (ESP32-2432S032 capacitive variant).

My screen is a 3.2 inch capacitive TFT screen with a resolution of 320*240.

You have a lot of information in main.cpp file to help configure this file to your own needs. All comment are in **English and French**.


## Library install & configuration

I use VS Code & PlatformIO extension, but those steps will also be true if you use the Arduino IDE. You will need to install some library to your project. On arduino you can add them from the left side menu and for VS Code you can add them from Home -> Libraries in your VS Code IDE interface.

Libraries you need :
- `LVGL` : For my version of SquareLine Studio i used lvgl-8.3.6.
- `TFT_eSPI` : You can use the latest version.
- `TAMC_GT911` : You can use the latest version.

When you installed those libraries you need tomodify 2 file from them.

> [!TIP]
> To find your library folder with Arduino IDE, just go to `File` -> `Preferences...` and the path to your library will be next to `Sketchbook location :`

> [!TIP]
> To find your library folder with PlatformIO, just go to your project folder `Your_Project_Name/.pio/` -> `libdeps/esp32dev` and your in your libraries folder.

First go to the `lvgl` folder and copy/paste the `lvgl_conf_template.h` file to the `src` folder still under the lvlg folder. Now rename your freshly paste file from `lvgl_conf_template.h` to `lvgl_conf.h`. Open it, and change the `#if 0` under clang-format off comment to `#if 1`. Save and close.

Now go to your TFT_eSPI library folder. Scroll down and open `User_Setup.h`. Here you have to modify multiple things. First scroll down a bit and you will show this comment : **Only define one driver, the other ones must be commented out**. Under it is a list of driver compatible for some screen. Because mine is a ST7789 screen, i commented out the `#define ST7789_DRIVER`. Do the same but for your own screen.

Scroll down, find the **For ST7789, ST7735, ILI9163 and GC9A01 ONLY, define the pixel width and height in portrait orientation** comment. Comment out `#define TFT_WIDTH  240` and `#define TFT_HEIGHT  320` and the change the resolution according to screen resolution. There is multiple #define TFT_WIDTH and TFT_HEIGHT line, they all do the same thing because they all have the same neame, so just pick the one you want.

Scroll down again, find this comment : **EDIT THE PIN NUMBERS IN THE LINES FOLLOWING TO SUIT YOUR ESP32 SETUP**. You will find a bunch line to define your screen/GPIO pins connection. You need to define : 
- `#define TFT_MISO XX` : If you do not have a defined pin, just set -1
- `#define TFT_MOSI XX`
- `#define TFT_SCLK XX`
- `#define TFT_CS   XX`
- `#define TFT_DC   XX`
- `#define TFT_RST  XX` : If you do not have a defined pin, just set -1
- `#define TFT_BL   XX` : Backlite pin, if you not have one, let it commented

Save and close.


## Screen & Touchscreen pins

For this to work you will need to change all the defined pins in the `main.cpp` file under `YOUR_PROJECT_NAME/src` folder. This branch use the **TFT_eSPI** and **TAMC_GT911** library. 

In main.cpp file change the this define to change pins and resolution :
- `#define DISP_HOR_RES XXX` : replace XXX by your horizontal screen resolution
- `#define DISP_VER_RES XXX` : replace XXX by your vertical screen resolution
- `#define TOUCH_SDA XX` : replace XX to GPIO to screen SDA pin
- `#define TOUCH_SCL XX` : replace XX to GPIO to screen SCL pin
- `#define TOUCH_INT XX` : replace XX to GPIO to screen INT pin
- `#define TOUCH_RST XX` : replace XX to GPIO to screen RST pin
- `#define TOUCH_WIDTH XXX` : replace XXX by your horizontal screen resolution (should be the same as the screen)
- `#define TOUCH_WIDTH XXX` : replace XXX by your vertical screen resolution (should be the same as the screen)



## Authors

- Go check my other Repo :wink: : [@PetitOursManu](https://github.com/PetitOursManu)

