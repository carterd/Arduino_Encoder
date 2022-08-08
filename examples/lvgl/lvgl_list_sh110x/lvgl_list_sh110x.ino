// Minimal "Hello" example for LittlevGL on Adafruit TFT FeatherWings.
// Requires LittlevGL, Adafruit_LvGL_Glue, Adafruit_STMPE610, Adafruit_GFX
// and Adafruit_ILI9341 (2.4" TFT) or Adafruit_HX8357 (3.5") libraries.
// This example doesn't use any touchscreen input, but it's declared anyway
// so this sketch can be copied-and-pasted to serve as a starting point for
// other projects. If display is scrambled, check that correct FeatherWing
// type is selected below (set BIG_FEATHERWING to 0 or 1 as needed).

// Prior Adafruit_LvGL_Glue users: see hello_changes example for updates!

#define BIG_FEATHERWING 0 // Set this to 1 for 3.5" (480x320) FeatherWing!
#define USE_ADAFRUIT_FONT 1 // Use adafruit converted font

#include <ButtonEncoder.h>
#include <Adafruit_LvGL_Glue.h> // Always include this BEFORE lvgl.h!
#include <lvgl.h>
#include <Adafruit_SH110X.h>
#include <DisplayCallbacks/DisplayCallback_SH110X.h> // Display-specific callback
#include <InputCallbacks/InputCallback_ButtonEncoder.h> // Button-encoder

#if USE_ADAFRUIT_FONT
#include <Fonts/PixelOperator8pt7b.h>
#include <LvglFonts/lv_font_symbols_8.h>
#include <LvglThemes/lv_theme_binary.h>
#include <Utilities/Adafruit_To_LvGL_Font.h>
#endif

#ifdef ESP32
   #define TFT_CS   15
   #define TFT_DC   33
   #define STMPE_CS 32
#else
   #define TFT_CS    9
   #define TFT_DC   10
   #define STMPE_CS  6
#endif
#define TFT_ROTATION LV_DISP_ROT_180 // Landscape orientation on FeatherWing
#define TFT_RST     8
#define BUTTON_LEFT   16
#define BUTTON_RIGHT  14
#define BUTTON_ENTER  15

#if BIG_FEATHERWING
  #include <Adafruit_HX8357.h>
  Adafruit_HX8357  tft(TFT_CS, TFT_DC, TFT_RST);
#else
  #include <Adafruit_ILI9341.h>
  #define TFT_WIDTH    64
  #define TFT_HEIGHT   128

  Adafruit_SH1107 tft(TFT_WIDTH, TFT_HEIGHT, &Wire, TFT_RST);
  ButtonEncoder encoder(BUTTON_LEFT, BUTTON_RIGHT, BUTTON_ENTER);
#endif

lv_font_t myAdaFont = {};
Adafruit_LvGL_Glue glue;
lv_group_t *group;

lv_obj_t *main_list_screen;
lv_obj_t *new_list_screen;

// Handler for the list events
// This is used for both lists to flip between them
//
static void event_handler(lv_event_t* event) {
  lv_event_code_t code = lv_event_get_code(event);
  lv_obj_t * obj = lv_event_get_target(event);
  lv_obj_t * list = lv_obj_get_parent(obj);

  if(code == LV_EVENT_CLICKED) {
      printf("Clicked: %s\n", lv_list_get_btn_text(list, obj));
      int index = lv_obj_get_child_id(obj);
      printf("List item clicked: %d\n", index);

      if (main_list_screen != NULL) {
        lvgl_destroy();
        lvgl_setup_new_list();       
      } else {
        lvgl_destroy();
        lvgl_setup_main_list();
      }
  }
}

// This is a function to simply remove all the active gui components from the screen
// Giving a fresh start to build a different screen of gui components not the use
// of del_async allowing for use in event handlers of objects that will be deleted.
void lvgl_destroy(void) {
  if (group != NULL) {
    lv_group_remove_all_objs(group);
    lv_group_del(group);
  }
  if (main_list_screen != NULL) {
    lv_obj_del_async(main_list_screen);
    main_list_screen = NULL;
  }
  if (new_list_screen != NULL) {
    lv_obj_del_async(new_list_screen);
    new_list_screen = NULL;
  }
}

// This example sketch's LittlevGL UI-building calls are all in this
// function rather than in setup(), so simple programs can just 
// copy-and-paste this sketch as a starting point, then embellish here:
void lvgl_setup_new_list(void) {
  // Create the group for navigation, connect to our button input encoder
  group = lv_group_create();
  lv_group_set_wrap(group, false);
  lv_indev_set_group(glue.getLvInputDevice(), group);
  lv_group_set_default(group);

  new_list_screen = lv_obj_create(lv_scr_act());
  lv_obj_set_size(new_list_screen, 64, 128);

  // Create simple label centered on screen
  lv_obj_t *label = lv_label_create(new_list_screen);
  lv_label_set_text(label, "New");
  lv_obj_align(label, LV_ALIGN_TOP_MID, 0, 0);

  // List
  lv_obj_t *list = lv_list_create(new_list_screen);
  lv_obj_set_size(list, 64, 98);
  lv_obj_align(list, LV_ALIGN_TOP_MID, 0, 16);

  // Some list buttons
  lv_obj_t * list_btn;


  list_btn = lv_list_add_btn(list, NULL, "One");
  lv_obj_add_event_cb(list_btn, event_handler, LV_EVENT_ALL, NULL);
  lv_group_add_obj(group, list_btn);

  list_btn = lv_list_add_btn(list, NULL, "Two");
  lv_obj_add_event_cb(list_btn, event_handler, LV_EVENT_ALL, NULL);
  lv_group_add_obj(group, list_btn);

  list_btn = lv_list_add_btn(list, NULL, "Three");
  lv_obj_add_event_cb(list_btn, event_handler, LV_EVENT_ALL, NULL);
  lv_group_add_obj(group, list_btn);
}

// This example sketch's LittlevGL UI-building calls are all in this
// function rather than in setup(), so simple programs can just 
// copy-and-paste this sketch as a starting point, then embellish here:
void lvgl_setup_main_list(void) {
  // Create the group for navigation, connect to our button input encoder
  group = lv_group_create();
  lv_group_set_wrap(group, false);
  lv_indev_set_group(glue.getLvInputDevice(), group);
  lv_group_set_default(group);

  main_list_screen = lv_obj_create(lv_scr_act());
  lv_obj_set_size(main_list_screen, 64, 128);

  // Create simple label centered on screen
  lv_obj_t *label = lv_label_create(main_list_screen);
  lv_label_set_text(label, "Main List");
  lv_obj_align(label, LV_ALIGN_TOP_MID, 0, 0);

  // List
  lv_obj_t *list = lv_list_create(main_list_screen);
  lv_obj_set_size(list, 64, 98);
  lv_obj_align(list, LV_ALIGN_TOP_MID, 0, 16);

  // Some list buttons
  lv_obj_t * list_btn;

  list_btn = lv_list_add_btn(list, LV_SYMBOL_FILE, "New");
  lv_obj_add_event_cb(list_btn, event_handler, LV_EVENT_ALL, NULL);
  lv_group_add_obj(group, list_btn);

  list_btn = lv_list_add_btn(list, LV_SYMBOL_DIRECTORY, "Open");
  lv_obj_add_event_cb(list_btn, event_handler, LV_EVENT_ALL, NULL);
  lv_group_add_obj(group, list_btn);

  list_btn = lv_list_add_btn(list, LV_SYMBOL_CLOSE, "Delete");
  lv_obj_add_event_cb(list_btn, event_handler, LV_EVENT_ALL, NULL);
  lv_group_add_obj(group, list_btn);

  list_btn = lv_list_add_btn(list, LV_SYMBOL_EDIT, "Edit");
  lv_obj_add_event_cb(list_btn, event_handler, LV_EVENT_ALL, NULL);
  lv_group_add_obj(group, list_btn);

  list_btn = lv_list_add_btn(list, LV_SYMBOL_SAVE, "Save");
  lv_obj_add_event_cb(list_btn, event_handler, LV_EVENT_ALL, NULL);
  lv_group_add_obj(group, list_btn);

  list_btn = lv_list_add_btn(list, LV_SYMBOL_BELL, "Notify");
  lv_obj_add_event_cb(list_btn, event_handler, LV_EVENT_ALL, NULL);
  lv_group_add_obj(group, list_btn);

  list_btn = lv_list_add_btn(list, LV_SYMBOL_BATTERY_FULL, "Battery");
  lv_obj_add_event_cb(list_btn, event_handler, LV_EVENT_ALL, NULL);
  lv_group_add_obj(group, list_btn);
}

// ----------------------------------------------------------------------------
// Arduino setup function
// ----------------------------------------------------------------------------
void setup(void) {
  Serial.begin(115200);
  while(!Serial);

  // Initialize display and touchscreen BEFORE glue setup
  tft.begin(0x3C, true);

  
  // Initialize glue, passing in address of display & touchscreen
  LvGLStatus status = glue.begin(&tft, displayCallback_SH110X, (INPUT_TYPE *) &encoder, inputCallback_ButtonEncoder, LV_INDEV_TYPE_ENCODER, true);
  if(status != LVGL_OK) {
    Serial.print("Glue error ");
    Serial.println((int)status);
    for(;;);
  }

#if USE_ADAFRUIT_FONT
  // Ensure that fonts are static otherwise, there will be problems, also use lv_font_symbols as fallback font to capture symbols
  static lv_font_t myAdaFont = {};
  adafruitToLvGLFont(&PixelOperator8pt7b, &myAdaFont, &lv_font_symbols_8);
  // Ensure using the mono theme
  lv_theme_t* binary_theme = lv_theme_binary_init(glue.getLvDisplay(), true, &myAdaFont);
#else
  lv_theme_t* binary_theme = lv_theme_binary_init(glue.getLvDisplay(), true, lv_font_default());
#endif

  lv_disp_set_rotation(NULL, LV_DISP_ROT_180);
  lv_disp_set_theme(NULL, binary_theme);

  lvgl_setup_main_list(); // Call UI-building function above
}

// ----------------------------------------------------------------------------
// Arduino loop function
// ----------------------------------------------------------------------------
void loop(void) {
  lv_task_handler(); // Call LittleVGL task handler periodically
  delay(5);
}
