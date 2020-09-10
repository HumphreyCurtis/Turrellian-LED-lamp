#include <M5Stack.h>

int i=0; 
int green[]={
  0x7fe0, 0x3666, 
  0x07e0, 0x2444, 0x0400, 
  0x0320, 0xafe5, 0x9e66,
  0x07ef, 0x07d3, 0x9772, 
  0x9fd3, 0x8df1, 0x3d8e, 
  0x2c4a, 0x8400, 0x5345, 
  0x6c64
}; 

int blue[]={
  0xf7fdf, 0xe73f, 0xb71c,
  0xaedc, 0x867f, 0x867d, 
  0x05ff, 0xb63b, 0x1c9f,
  0x64bd, 0x4416, 0x5cf4,
  0x435c, 0x001f, 0x0019, 
  0x0011, 0x0010
};

int blue_green[]={
  0x5cf4, 0xb71c, 0x0533,
  0x0410, 0x07ff, 0x471a, 
  0x1336, 0x2595, 0x3d93, 
  0x0dd6
};

int purple_blue[]={
  0x18ce, 0x895c, 0x4810,
  0x7b5d, 0x6ad9, 0x49f1, 
  0x5a79, 0x50df, 0x0071, 
  0x4950, 0x8bd8, 0x629b
};

int red[]={
  0xfd0f, 0xfc0e, 0xecaf, 
  0xf410, 0xcaeb,0xb104,
  0xf800, 0xc800, 0xc987, 
  0xb0a2, 0xe947, 0xc182, 
  0x8800, 0xfb08, 0xfa20
};

int purple[]={
  0xe73f, 0xddfb, 0xdd1b,
  0xec1d, 0xdb9a, 0xf81f,
  0xbaba, 0x939b, 0x895c,
  0x901a, 0x9999, 0x8811,
  0x8010
};

int red_purple[]={
  0xdb92, 0x8000, 0xd8a7,
  0x8a70, 0x89cb, 0x81eb,
  0x818c, 0x812a, 0x6007, 
  0xb434
};

int yellow_red[]={
  0xfa60, 0xeac0, 0xca01, 
  0xfa62, 0xfa60, 0xe2c0, 
  0xfac0, 0xfac3, 0xe38b, 
  0xfba3, 0xfb08,0xfa20,
  0xfc0e
};

void setup() {
  // put your setup code here, to run once:
  M5.begin(); 
  M5.Lcd.setBrightness(255); 
}

void loop() {
  // put your main code here, to run repeatedly:
  M5.Lcd.fillCircle(160, 120, 100, blue_green[i]); 
  i++; 
  if(i>=(sizeof(blue_green)/sizeof(int))){
    i=0; 
  }
  delay(1000); 
}
