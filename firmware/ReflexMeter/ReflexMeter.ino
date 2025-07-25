/* =============================================================
   REFLEKS 8×8 – TAM ASCII + Türkçe harf + emoji + 2-haneli sayaç
   ============================================================= */
#include <LedControl.h>

#define DIN 11
#define CS  10
#define CLK 13
LedControl lc(DIN, CLK, CS, 1);

/* Paneli 180° ters asılıysa aç */
//#define FLIP_180

const byte BTN = 2;      // buton (INPUT_PULLUP)
const byte LED = 3;      // refleks LED’i

/* ---------------- 5×7 FONT (ASCII 32-126 + TR 127-132) ----------------
 *  • Her karakter 7 byte = 7 sütun   • bit0 üst, bit6 alt piksel
 *  • Karakter genişliği 5, 6. ve 7. sütun boş/geçiş            */
const PROGMEM byte font5x7[][7] = {
/* 32 ' ' */{0,0,0,0,0,0,0},
/* 33 '!' */{0,0,0,0x5f,0,0,0},
/* 34 '"' */{0,0x03,0,0x03,0,0,0},
/* 35 '#' */{0x14,0x7f,0x14,0x7f,0x14,0,0},
/* 36 '$' */{0x24,0x2a,0x7f,0x2a,0x12,0,0},
/* 37 '%' */{0x23,0x13,0x08,0x64,0x62,0,0},
/* 38 '&' */{0x36,0x49,0x55,0x22,0x50,0,0},
/* 39 ''' */{0,0x05,0x03,0,0,0,0},
/* 40 '(' */{0,0x1c,0x22,0x41,0,0,0},
/* 41 ')' */{0,0x41,0x22,0x1c,0,0,0},
/* 42 '*' */{0x14,0x08,0x3e,0x08,0x14,0,0},
/* 43 '+' */{0x08,0x08,0x3e,0x08,0x08,0,0},
/* 44 ',' */{0,0x50,0x30,0,0,0,0},
/* 45 '-' */{0x08,0x08,0x08,0x08,0x08,0,0},
/* 46 '.' */{0,0x60,0x60,0,0,0,0},
/* 47 '/' */{0x20,0x10,0x08,0x04,0x02,0,0},
/* 48 '0' */{0x3e,0x51,0x49,0x45,0x3e,0,0},
/* 49 '1' */{0,0x42,0x7f,0x40,0,0,0},
/* 50 '2' */{0x62,0x51,0x49,0x49,0x46,0,0},
/* 51 '3' */{0x22,0x41,0x49,0x49,0x36,0,0},
/* 52 '4' */{0x18,0x14,0x12,0x7f,0x10,0,0},
/* 53 '5' */{0x27,0x45,0x45,0x45,0x39,0,0},
/* 54 '6' */{0x3c,0x4a,0x49,0x49,0x30,0,0},
/* 55 '7' */{0x01,0x71,0x09,0x05,0x03,0,0},
/* 56 '8' */{0x36,0x49,0x49,0x49,0x36,0,0},
/* 57 '9' */{0x06,0x49,0x49,0x29,0x1e,0,0},
/* 58 ':' */{0,0x36,0x36,0,0,0,0},
/* 59 ';' */{0,0x56,0x36,0,0,0,0},
/* 60 '<' */{0x08,0x14,0x22,0x41,0,0,0},
/* 61 '=' */{0x14,0x14,0x14,0x14,0x14,0,0},
/* 62 '>' */{0x41,0x22,0x14,0x08,0,0,0},
/* 63 '?' */{0x02,0x01,0x51,0x09,0x06,0,0},
/* 64 '@' */{0x32,0x49,0x79,0x41,0x3e,0,0},
/* 65 'A' */{0x7e,0x11,0x11,0x11,0x7e,0,0},
/* 66 'B' */{0x7f,0x49,0x49,0x49,0x36,0,0},
/* 67 'C' */{0x3e,0x41,0x41,0x41,0x22,0,0},
/* 68 'D' */{0x7f,0x41,0x41,0x22,0x1c,0,0},
/* 69 'E' */{0x7f,0x49,0x49,0x49,0x41,0,0},
/* 70 'F' */{0x7f,0x09,0x09,0x09,0x01,0,0},
/* 71 'G' */{0x3e,0x41,0x49,0x49,0x7a,0,0},
/* 72 'H' */{0x7f,0x08,0x08,0x08,0x7f,0,0},
/* 73 'I' */{0,0x41,0x7f,0x41,0,0,0},
/* 74 'J' */{0x20,0x40,0x41,0x3f,0x01,0,0},
/* 75 'K' */{0x7f,0x08,0x14,0x22,0x41,0,0},
/* 76 'L' */{0x7f,0x40,0x40,0x40,0x40,0,0},
/* 77 'M' */{0x7f,0x02,0x04,0x02,0x7f,0,0},
/* 78 'N' */{0x7f,0x04,0x08,0x10,0x7f,0,0},
/* 79 'O' */{0x3e,0x41,0x41,0x41,0x3e,0,0},
/* 80 'P' */{0x7f,0x09,0x09,0x09,0x06,0,0},
/* 81 'Q' */{0x3e,0x41,0x51,0x21,0x5e,0,0},
/* 82 'R' */{0x7f,0x09,0x19,0x29,0x46,0,0},
/* 83 'S' */{0x46,0x49,0x49,0x49,0x31,0,0},
/* 84 'T' */{0x01,0x01,0x7f,0x01,0x01,0,0},
/* 85 'U' */{0x3f,0x40,0x40,0x40,0x3f,0,0},
/* 86 'V' */{0x1f,0x20,0x40,0x20,0x1f,0,0},
/* 87 'W' */{0x7f,0x20,0x18,0x20,0x7f,0,0},
/* 88 'X' */{0x63,0x14,0x08,0x14,0x63,0,0},
/* 89 'Y' */{0x03,0x04,0x78,0x04,0x03,0,0},
/* 90 'Z' */{0x61,0x51,0x49,0x45,0x43,0,0},
/* 91 '[' */{0,0x7f,0x41,0x41,0,0,0},
/* 92 '\'*/{0x02,0x04,0x08,0x10,0x20,0,0},
/* 93 ']' */{0,0x41,0x41,0x7f,0,0,0},
/* 94 '^' */{0x04,0x02,0x01,0x02,0x04,0,0},
/* 95 '_' */{0x40,0x40,0x40,0x40,0x40,0,0},
/* 96 '`' */{0,0x03,0x07,0,0,0,0},
/* 97 'a' */{0x20,0x54,0x54,0x54,0x78,0,0},
/* 98 'b' */{0x7f,0x48,0x44,0x44,0x38,0,0},
/* 99 'c' */{0x38,0x44,0x44,0x44,0x20,0,0},
/*100 'd' */{0x38,0x44,0x44,0x48,0x7f,0,0},
/*101 'e' */{0x38,0x54,0x54,0x54,0x18,0,0},
/*102 'f' */{0x08,0x7e,0x09,0x01,0x02,0,0},
/*103 'g' */{0x0c,0x52,0x52,0x52,0x3e,0,0},
/*104 'h' */{0x7f,0x08,0x04,0x04,0x78,0,0},
/*105 'i' */{0,0x44,0x7d,0x40,0,0,0},
/*106 'j' */{0x20,0x40,0x44,0x3d,0,0,0},
/*107 'k' */{0x7f,0x10,0x28,0x44,0,0,0},
/*108 'l' */{0,0x41,0x7f,0x40,0,0,0},
/*109 'm' */{0x7c,0x04,0x18,0x04,0x78,0,0},
/*110 'n' */{0x7c,0x08,0x04,0x04,0x78,0,0},
/*111 'o' */{0x38,0x44,0x44,0x44,0x38,0,0},
/*112 'p' */{0x7c,0x14,0x14,0x14,0x08,0,0},
/*113 'q' */{0x08,0x14,0x14,0x18,0x7c,0,0},
/*114 'r' */{0x7c,0x08,0x04,0x04,0x08,0,0},
/*115 's' */{0x48,0x54,0x54,0x54,0x20,0,0},
/*116 't' */{0x04,0x3f,0x44,0x40,0x20,0,0},
/*117 'u' */{0x3c,0x40,0x40,0x20,0x7c,0,0},
/*118 'v' */{0x1c,0x20,0x40,0x20,0x1c,0,0},
/*119 'w' */{0x3c,0x40,0x30,0x40,0x3c,0,0},
/*120 'x' */{0x44,0x28,0x10,0x28,0x44,0,0},
/*121 'y' */{0x0c,0x50,0x50,0x50,0x3c,0,0},
/*122 'z' */{0x44,0x64,0x54,0x4c,0x44,0,0},
/*123 '{' */{0,0x08,0x36,0x41,0,0,0},
/*124 '|' */{0,0,0x7f,0,0,0,0},
/*125 '}' */{0,0x41,0x36,0x08,0,0,0},
/*126 '~' */{0x02,0x01,0x02,0x04,0x02,0,0},
/*127 'Ç' */{0x3e,0x49,0x49,0x49,0x22,0,0},
/*128 'Ş' */{0x06,0x49,0x49,0x49,0x31,0,0},
/*129 'Ğ' */{0x3e,0x41,0x49,0x49,0x7a,0,0},
/*130 'Ü' */{0x3f,0x40,0x40,0x40,0x3f,0,0},
/*131 'Ö' */{0x3e,0x41,0x41,0x41,0x3e,0,0},
/*132 'İ' */{0,0x41,0x7f,0x41,0,0,0}
};

/* ---------------- 3×5 sayı ------------- */
const PROGMEM byte font3x5[10][3] = {
  {0x1f,0x11,0x1f},{0x00,0x1f,0x00},{0x1d,0x15,0x17},
  {0x15,0x15,0x1f},{0x07,0x04,0x1f},{0x17,0x15,0x1d},
  {0x1f,0x15,0x1d},{0x01,0x01,0x1f},{0x1f,0x15,0x1f},
  {0x17,0x15,0x1f}
};

/* --------- 8×8 ikon maskeleri -------- */
const PROGMEM byte emoji[][8]={
{0x04,0x0c,0x18,0x30,0x18,0x0c,0x08,0}, /*⚡*/
{0x1c,0x22,0x5d,0x22,0x1c,0,0,0},       /*🐆*/
{0x02,0x06,0x1e,0x3e,0x1e,0x06,0x02,0}, /*🚀*/
{0x0c,0x12,0x3f,0x21,0x12,0x0c,0,0},    /*🐢*/
{0x1c,0x22,0x55,0x41,0x22,0x1c,0,0},    /*👵*/
{0,0x0e,0x11,0x15,0x11,0x0e,0,0}         /*🙂*/
};

/* ---------- yardımcı çizimler ---------- */
inline void P(byte x,byte y,bool on=1){
#ifdef FLIP_180
  lc.setLed(0,7-y,7-x,on);
#else
  lc.setLed(0,y,x,on);
#endif
}
void drawChar(char ch,int x0){
  if(ch<32 || ch>132) return;
  const byte *p=font5x7[ch-32];
  for(byte c=0;c<5;c++){
    byte b=pgm_read_byte(p+c);
    for(byte r=0;r<7;r++) if(b&(1<<r)) P(x0+c,r+1);
  }
}
void drawNum(byte v){
  lc.clearDisplay(0);
  for(byte c=0;c<3;c++){
    byte l=pgm_read_byte(&(font3x5[v/10][c]));
    byte r=pgm_read_byte(&(font3x5[v%10][c]));
    for(byte rr=0;rr<5;rr++){
      if(l&(1<<rr)) P(c,    rr+1);
      if(r&(1<<rr)) P(c+4,  rr+1);
    }
  }
}
void drawEmoji(byte idx){
  lc.clearDisplay(0);
  for(byte r=0;r<8;r++){
    byte bits=pgm_read_byte(&(emoji[idx][r]));
    for(byte c=0;c<8;c++) if(bits&(1<<(7-c))) P(c,r);
  }
}
void scroll(const String &s,uint16_t d=85){
  int len=s.length()*6+8;
  for(int sh=0;sh<len;sh++){
    lc.clearDisplay(0);
    int x=7-sh;
    for(char ch:s){ drawChar(ch,x); x+=6; }
    delay(d);
  }
}

/* ---------- Setup ---------- */
void setup(){
  lc.shutdown(0,false);
  lc.setIntensity(0,8);
  lc.clearDisplay(0);
  pinMode(BTN,INPUT_PULLUP);
  pinMode(LED,OUTPUT);
  randomSeed(analogRead(A0));
}

/* ---------- Loop ---------- */
void loop(){
  delay(random(2000,4000));
  digitalWrite(LED,HIGH);
  unsigned long t0=millis();

  while(digitalRead(BTN)){                // canlı sayaç
    byte ds=((millis()-t0)/100)%100;
    drawNum(ds);
  }
  digitalWrite(LED,LOW);
  unsigned ms=millis()-t0;

  scroll(String(ms)+"MS  ");              // sonuç
  byte idx; String msg;
  if(ms<150){idx=0;msg="SIMSEK HIZI!";}
  else if(ms<300){idx=1;msg="CITA GIBI HIZLI!";}
  else if(ms<450){idx=2;msg="ROKET MODU!";}
  else if(ms<650){idx=5;msg="FENA DEGIL!";}
  else if(ms<850){idx=3;msg="TOSBAGA MODU :)";}
  else {idx=4;msg="NINE HIZINDA!";}

  drawEmoji(idx); delay(700);
  scroll(msg);
  delay(1200);
}
