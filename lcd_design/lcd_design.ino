#include <U8g2lib.h>

#include <Wire.h> // library requires for IIC communication

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE); // initialization for the used OLED display

// images from https://lopaka.app/
static const unsigned char image_network_bits[] U8X8_PROGMEM = {0x00,0x70,0x00,0x50,0x00,0x50,0x00,0x50,0x00,0x57,0x00,0x55,0x00,0x55,0x00,0x55,0x70,0x55,0x50,0x55,0x50,0x55,0x50,0x55,0x57,0x55,0x55,0x55,0x77,0x77,0x00,0x00};
static const unsigned char image_network_not_connected_bits[] U8X8_PROGMEM = {0x41,0x70,0x22,0x50,0x14,0x50,0x08,0x50,0x14,0x57,0x22,0x55,0x41,0x55,0x00,0x55,0x70,0x55,0x50,0x55,0x50,0x55,0x50,0x55,0x57,0x55,0x55,0x55,0x77,0x77,0x00,0x00};
static const unsigned char image_battery_empty_bits[] U8X8_PROGMEM = {0x00,0x00,0x00,0xf0,0xff,0x7f,0x08,0x00,0x80,0x08,0x00,0x80,0x0e,0x00,0x80,0x01,0x00,0x80,0x01,0x00,0x80,0x01,0x00,0x80,0x01,0x00,0x80,0x01,0x00,0x80,0x0e,0x00,0x80,0x08,0x00,0x80,0x08,0x00,0x80,0xf0,0xff,0x7f,0x00,0x00,0x00,0x00,0x00,0x00};
static const unsigned char image_power_text_bits[] U8X8_PROGMEM = {0xc7,0x44,0x77,0x29,0x45,0x91,0x27,0x55,0x73,0x21,0x55,0x51,0xc1,0x28,0x97};

int progress = 0; // progress of the progressbar
char buffer[32]; // helper buffer to construct a string to be displayed

void setup(void) {
  u8g2.begin(); // start the u8g2 library
}

void loop(void) {
    u8g2.clearBuffer();
    u8g2.setFontMode(1);
    u8g2.setBitmapMode(1);
    
    // Wifi
    u8g2.drawXBMP(2, 1, 15, 16, image_network_not_connected_bits);

    // Batter Empty Container
    u8g2.drawXBMP(103, 1, 24, 16, image_battery_empty_bits);
    // Power Bar
    u8g2.drawBox(108, 4, 17, 9);
    // Power level
    u8g2.setFont(u8g2_font_t0_13b_tr);
    u8g2.drawStr(80, 14, "60%");

    // Top Divider
    u8g2.drawLine(1, 18, 127, 18);

    // Power bar left
    u8g2.drawBox(7, 31, 8, 28);
    u8g2.setDrawColor(2);
    u8g2.drawBox(8, 32, 6, progress);
    // u8g2.drawBox(8, 32, 6, 26);

    // Power bar right
    u8g2.drawBox(18, 31, 8, 28);
    u8g2.setDrawColor(2);
    u8g2.drawBox(19, 32, 6, 7);
    
    // Power Text
    u8g2.setDrawColor(1);
    u8g2.drawXBMP(4, 23, 24, 5, image_power_text_bits);

    // Right-Speed
    u8g2.setFont(u8g2_font_profont15_tr);
    u8g2.drawStr(37, 55, "R-SPD:");
    u8g2.drawStr(79, 55, "100");

    // Left-Speed
    u8g2.drawStr(37, 41, "L-SPD:");
    u8g2.drawStr(79, 41, "100");

    u8g2.sendBuffer();
  // u8g2.clearBuffer();					// clear the internal memory

  // // code from https://lopaka.app/
	// u8g2.setBitmapMode(1);
	// u8g2.drawFrame(12, 21, 104, 20);
	// u8g2.drawBox(14, 23, progress, 16); // draw the progressbar fill
	// u8g2.setFont(u8g2_font_helvB08_tr);
	// sprintf(buffer, "Progress: %d%%", progress); // construct a string with the progress variable
	// u8g2.drawStr(33, 53, buffer); // display the string
	// u8g2.setFont(u8g2_font_haxrcorp4089_tr);
	// u8g2.drawStr(0, 7, "Progress Bar Screen");
	// u8g2.drawLine(0, 9, 127, 9);
	// u8g2.drawXBMP( 100, 0, 7, 8, image_Lock_7x8_bits);
	// u8g2.drawXBMP( 111, 0, 5, 8, image_Bluetooth_Idle_5x8_bits);
	// u8g2.drawXBMP( 120, 1, 8, 6, image_Volup_8x6_bits);
	// u8g2.drawXBMP( 22, 45, 9, 8, image_Alert_9x8_bits);


  // u8g2.sendBuffer();					// transfer internal memory to the display
  
  // // increase the progress value to go over 0-100
	progress = progress + 1;
	if (progress > 26) {
		progress = 0;
	}
}


