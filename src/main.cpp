// EN : Only if you use VisualStudio Code and PlatformIO
// FR : Seulement si vous utiliser VisualStudio Code et PlatformIO
#include <Arduino.h>
//--------------------------------------

/* EN :
  LVGL library. From the lvgl root directory, copy and paste the “lvgl_conf_template.h” file to the “src” folder and rename it “lvgl_conf.h”.
  When done, open the file you just pasted, modify the “if 0” to “if 1” under “ clang-format off ” at the beginning.
*/

/* FR :
  Bibliothèque LVGL. À partir du répertoire racine de lvgl, copiez et collez le fichier “lvgl_conf_template.h” dans le dossier “src” et renommez-le “lvgl_conf.h”.
  Une fois terminé, ouvrez le fichier que vous venez de coller, modifiez le “if 0” en “if 1” sous “clang-format off” au début.
*/
#include <lvgl.h>
//--------------------------------------

/* EN :
  For the TFT_eSPI library, you have to modify the User_Setup.h file to meet your screen requirement.
  My file for this project use a ST7789 screen with my pins setup.
*/

/* FR :
  Pour la bibliotheque TFT_eSPI vous devez modifier le fichier User_Setup.h pour l'adapter votre écran.
  Le fichier founi pour ce projet utilise un écran ST7789 avec ma configuration de broches.
*/
#include <TFT_eSPI.h>
//--------------------------------------

/* EN :
  Squareline Studio UI file generate with the "Export UI Files" from "Export" tab. I put my files under a folder named "squarelineui" in "[YourProject]\.pio\libdeps\esp32dev\squarelineui".
  If VS Code cannot find your folder, i find this from bobbyhadz.com : https://emanuelvigreux.fr/yourls/pathissue . "C/C++ Configurations" tabs will open, scroll down to "Include path"
  and at the end of the text area, make sure that the path to your ui.h is added (it should be the last line).
*/
/* FR :
  Inclus les fichiers UI de SquareLine Studio générer via l'option "Export UI Files" depuis l'onglet "Export". Mes fichier sont dans un dossier nommé "squarelineui" dans 
  "[YourProject]\.pio\libdeps\esp32dev\squarelineui". Si VS Code ne trouve vos fichiers, servez-vous de ceci venant du site bobbyhadz.com : https://emanuelvigreux.fr/yourls/pathissue .
  Dans l'onglet "C/C++ Configurations" qui vient de s'ouvrir, descendez un peu puis juste en dessous de "Include path" verifiez à la fin de la zone de texte que le bon chemin à été
  ajouté (le chemin devrait se trouver à la dernier ligne).
*/
#include <ui.h>
//--------------------------------------

// EN : TouchScreen library for GT911 controller
// FR : Bibliotheque pour l'écran tactile utilisant le controlleur GT911
#include <TAMC_GT911.h>
//--------------------------------------

#include <Ticker.h>

//------------------------------------English & French comments-------------------------------------------

/* EN :
The lines `#define DISP_HOR_RES 320` and `#define DISP_VER_RES 240` are defining constants for
the horizontal and vertical resolution of the screen for the LVGL library. These constants are used
to specify the dimensions of the display area that LVGL will work with. In this case, the horizontal
resolution is set to 320 pixels and the vertical resolution is set to 240 pixels. These values are
used throughout the code to configure the display driver and buffer accordingly. */

/* FR :
Les lignes #define DISP_HOR_RES 320 et #define DISP_VER_RES 240 définissent des constantes pour la résolution
horizontale et verticale de l’écran utiliser par LVGL. Ces constantes sont utilisées pour spécifier les
dimensions de la zone d’affichage avec laquelle LVGL va travailler. Dans ce cas, la résolution horizontale est
réglée sur 320 pixels et la résolution verticale sur 240 pixels. Ces valeurs sont utilisées dans tout le code
pour configurer le pilote d’affichage et le tampon en conséquence.
*/

#define DISP_HOR_RES 320
#define DISP_VER_RES 240

/* EN : These `#define` statements are used to define constants for the pins and dimensions related to the
touch screen used in the code. */

/* FR : Ces instructions #define servent à définir des constantes pour les broches et les dimensions liées
à l’écran tactile utilisé dans le code. */

#define TOUCH_SDA 33
#define TOUCH_SCL 32
#define TOUCH_INT 21
#define TOUCH_RST 25
#define TOUCH_WIDTH 320
#define TOUCH_HEIGHT 240

//------------------------------------Object initializing-------------------------------------------
/* EN : The lines `TFT_eSPI tft = TFT_eSPI();` and `TAMC_GT911 tp = TAMC_GT911(TOUCH_SDA, TOUCH_SCL,
TOUCH_INT, TOUCH_RST, TOUCH_WIDTH, TOUCH_HEIGHT);` are initializing objects `tft` and `tp` of
classes `TFT_eSPI` and `TAMC_GT911` respectively. */

/* FR : Les lignes `TFT_eSPI tft = TFT_eSPI();` et `TAMC_GT911 tp = TAMC_GT911(TOUCH_SDA, TOUCH_SCL,
TOUCH_INT, TOUCH_RST, TOUCH_WIDTH, TOUCH_HEIGHT);` sont des objets d'initialisation `tft` et `tp`
des classes `TFT_eSPI` et `TAMC_GT911 ` respectivement. */
TFT_eSPI tft = TFT_eSPI();
TAMC_GT911 tp = TAMC_GT911(TOUCH_SDA, TOUCH_SCL, TOUCH_INT, TOUCH_RST, TOUCH_WIDTH, TOUCH_HEIGHT);

//------------------------------------Buffer creation-------------------------------------------
/* EN : The line `static lv_disp_draw_buf_t draw_buf;` is declaring a static variable named `draw_buf` of
type `lv_disp_draw_buf_t`. This variable is used to store information related to the drawing buffer
used by the LVGL library for displaying graphics on the screen. */

/* FR : La ligne `static lv_disp_draw_buf_t draw_buf;` déclare une variable statique nommée `draw_buf` de
type `lv_disp_draw_buf_t`. Cette variable est utilisée pour définir un tampon de dessin pour stocker
les informations de couleur utilisées par la bibliothèque LVGL (LitlevGL). */

static lv_disp_draw_buf_t draw_buf;

/* EN : The line `static lv_color_t buf1[DISP_HOR_RES * DISP_VER_RES / 10];` is defining a buffer named
`buf1` for storing color information used by the LVGL library. */

/* FR : La ligne `static lv_color_t buf1[DISP_HOR_RES * DISP_VER_RES / 10];` définit un tampon nommé `buf1`
qui est utilisé pour stocker les informations de couleur pour la bibliothèque LVGL. */

static lv_color_t buf1[DISP_HOR_RES * DISP_VER_RES / 10];

//------------------------------------Display flushing function-------------------------------------------
/** EN :
 * The function `my_disp_flush` updates a display with the specified area and color data using the TFT
 * library in C++.
 *
 * @param disp The `disp` parameter is a pointer to a display driver structure `lv_disp_drv_t`. This
 * structure contains information and functions related to the display driver used in the LittlevGL
 * graphics library.
 * @param area The `area` parameter in the `my_disp_flush` function represents the area on the display
 * that needs to be updated with the new colors. It is defined by the `lv_area_t` structure which
 * typically contains the coordinates of the top-left corner (x1, y1) and the bottom
 * @param color_p The `color_p` parameter is a pointer to an array of `lv_color_t` elements
 * representing the colors to be displayed on the screen. Each `lv_color_t` element typically contains
 * information about the red, green, and blue components of a color.
 */

/** FR :
 * La fonction `my_disp_flush` met à jour un affichage avec la zone spécifiée et les données de couleur
 * à l'aide du pilote d'affichage fourni.
 *
 * @param disp Le paramètre `disp` est un pointeur vers une structure de type `lv_disp_drv_t`, qui
 * contient probablement des informations sur le pilote d'affichage et des configurations pour la
 * bibliothèque graphique LittlevGL (LVGL).
 * @param area Le paramètre `area` dans la fonction `my_disp_flush` représente la zone de l'écran qui
 * doit être mise à jour avec les nouvelles couleurs. Il est défini par la structure `lv_area_t` qui
 * contient généralement les coordonnées du coin supérieur gauche (x1, y1) et du coin inférieur
 * @param color_p Le paramètre `color_p` est un pointeur vers un tableau d'éléments `lv_color_t`
 * représentant les couleurs à afficher à l'écran. Chaque élément `lv_color_t` contient généralement
 * des informations sur les composants rouge, vert et bleu d'une couleur.
 */

void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p)
{
  uint32_t w = (area->x2 - area->x1 + 1);
  uint32_t h = (area->y2 - area->y1 + 1);

  tft.startWrite();
  tft.setAddrWindow(area->x1, area->y1, w, h);
  tft.pushColors((uint16_t *)&color_p->full, w * h, true);
  tft.endWrite();

  lv_disp_flush_ready(disp);
}

//------------------------------------Touchpad to LVGL function-------------------------------------------
/** EN :
 * The function `my_touchpad_read` reads touchpad input and updates the state and coordinates
 * accordingly in the LVGL input device data structure.
 *
 * @param indev_drv The `indev_drv` parameter in the `my_touchpad_read` function is a pointer to a
 * structure of type `lv_indev_drv_t`. This structure likely contains driver-specific settings and
 * configurations for the input device being used, such as a touchpad or touchscreen. It is used to
 * read
 * @param data The `data` parameter in the `my_touchpad_read` function is a pointer to a structure of
 * type `lv_indev_data_t`. This structure likely contains information about the state of the input
 * device, such as whether it is pressed or released, and the coordinates of the touch point.
 */

/** FR :
 * La fonction `my_touchpad_read` lit les entrées du pavé tactile et met à jour l'état et les
 * coordonnées en conséquence.
 *
 * @param indev_drv Le paramètre `indev_drv` dans la fonction `my_touchpad_read` est un pointeur vers
 * une structure de type `lv_indev_drv_t`. Cette structure contient probablement des paramètres et des
 * configurations spécifiques au pilote pour le périphérique d'entrée.
 * @param data Le paramètre `data` dans la fonction `my_touchpad_read` est un pointeur vers une
 * structure de type `lv_indev_data_t`. Cette structure contient probablement des informations sur
 * l'état du périphérique d'entrée, par exemple s'il est enfoncé ou relâché, ainsi que les coordonnées
 * du point tactile.
 */

void my_touchpad_read(lv_indev_drv_t *indev_drv, lv_indev_data_t *data)
{
  /* EN : This code snippet is checking if the touchpad (represented by `tp`) is currently being touched. If
  the touchpad is touched, it sets the state of the input device data structure (`data`) to
  `LV_INDEV_STATE_PRESSED`, indicating that the touchpad is being pressed. */

  /* FR : L'extrait de code ci-dessus vérifie si un pavé tactile (`tp`) est touché. S'il est touché, il
  définit l'état de la structure de données sur `LV_INDEV_STATE_PRESSED`. */

  if (tp.isTouched)
  {
    data->state = LV_INDEV_STATE_PRESSED;

    /* EN : The code snippet `for (int i = 0; i < tp.touches; i++)` is iterating over the touch points detected
    by the touchpad. Inside the loop, it is assigning the x and y coordinates of each touch point to the
    `data` structure. */

    /* FR : L'extrait de code `for (int i = 0; i < tp.touches; i++)` parcourt les points de contact détectés par
    le pavé tactile. À l'intérieur de la boucle, il attribue les coordonnées x et y de chaque point de
    contact à la structure « data ». Cela signifie que pour chaque point tactile détecté par le pavé
    tactile, les coordonnées x et y de ce point tactile sont stockées dans la structure « data ».
    Cela permet au programme de suivre plusieurs points de contact si le pavé tactile prend en charge la
    fonctionnalité multi-touch. */

    for (int i = 0; i < tp.touches; i++)
    {
      data->point.x = tp.points[i].x;
      data->point.y = tp.points[i].y;
    }
  }
  else
  {
    data->state = LV_INDEV_STATE_RELEASED;
  }
}

//------------------------------------Ticker for LVGL-------------------------------------------
/** EN :
 * The function `lvglTickCallback` increments the LittlevGL tick by 10 to control at what frequency the LVGL animation are loaded.
 */

/** FR :
 * La fonction lvglTickCallback incrémente le tick de LittlevGL de 10 pour contrôler à quelle fréquence les animations LVGL sont chargées.
 */

Ticker lvglTicker;

void lvglTickCallback()
{
  lv_tick_inc(10);
}

//------------------------------------Setup-------------------------------------------
void setup()
{
  Serial.begin(115200);

  // EN : LCD init
  // FR : Initialisation de l'écran
  tft.init();
  tft.setRotation(1);
  tft.begin();

  // EN : Init comunication with the touchscreen and your ESP32 and set the correct rotation of the touchscreen for landscape use
  // FR : Initialise la communication entre l’écran tactile et l'ESP32. Et régle la rotation de l’écran tactile pour une utilisation en paysage
  tp.begin();
  tp.setRotation(ROTATION_RIGHT);

  // EN : Init LVGL library
  // FR : Initialise la bibliotheque LVGL
  lv_init();

  // EN : Call lvglTickCallback every 10 milliseconds. Give LVGL the time knowledge to execute animation and more
  // FR : Appel la fonction lvglTickCallback toutes les 10 millisecondes. Permet de donner une notion de temps à LVGL pour l'execution de différentes taches.
  lvglTicker.attach_ms(10, lvglTickCallback);
  lv_disp_draw_buf_init(&draw_buf, buf1, NULL, (DISP_HOR_RES * DISP_VER_RES / 10));

  // EN : Allow LVGL to comunicate with your driver screen and to toggle display flush function and your buffer
  // FR : Permet à LVGL de communiquer avec le pilote de l'écran and d'appeler la fonction de rafraichissement de l'écran ainsi que le tampon graphique
  static lv_disp_drv_t disp_drv;     /*Descriptor of a display driver*/
  lv_disp_drv_init(&disp_drv);       /*Basic initialization*/
  disp_drv.flush_cb = my_disp_flush; /*Set your driver function*/
  disp_drv.draw_buf = &draw_buf;     /*Assign the buffer to the display*/
  disp_drv.hor_res = DISP_HOR_RES;   /*Set the horizontal resolution of the display*/
  disp_drv.ver_res = DISP_VER_RES;   /*Set the vertical resolution of the display*/
  lv_disp_drv_register(&disp_drv);   /*Finally register the driver*/

  // EN : Allow LVGL to comunicate with your driver touchscreen and to toggle your touchpad function to know what points are pressed
  // FR : Permet à LVGL de communiquer avec le pilote de l'écran tactile et d'appeler la fonction de lecture des points touché sur l'écran.
  static lv_indev_drv_t indev_drv;        /*Descriptor of a input device driver*/
  lv_indev_drv_init(&indev_drv);          /*Basic initialization*/
  indev_drv.type = LV_INDEV_TYPE_POINTER; /*Touch pad is a pointer-like device*/
  indev_drv.read_cb = my_touchpad_read;   /*Set your driver function*/
  lv_indev_drv_register(&indev_drv);      /*Finally register the driver*/

  // EN : Init ui.h file from SquareLine Studio
  // FR : Initialise le fichier ui.h créer par SquareLine Studio
  ui_init();
}

//------------------------------------Loop-------------------------------------------
void loop()
{
  // EN : Read the touch from your touchscreen
  // FR : Récupère les points touchés depuis votre écran tactile
  tp.read();

  // EN : Manage all task (animation, entry...) ready to be execute. The function is called each 30 milliseconds for reactivity
  // FR : Gére toutes les taches (animation, entrée...) prête à être executé. Cette fonction est appelé toutes les 30 millisecondes pour des raison de réactivité
  lv_timer_handler();
  delay(30);
}