typedef unsigned char      Byte;

typedef unsigned int       Word;

typedef unsigned long      DWord;

typedef enum {false, true} Boolean;

typedef struct
{
  Byte Red;
  Byte Grn;
  Byte Blu;
}
RGB;

typedef RGB Palette_Register[256];

typedef float TDA[3];

typedef int   TDIA[3];

typedef float FDA[4];

typedef float Matx4x4[4][4];

#define MaxCol   7
#define MaxInten 35

#define TRUE  1
#define FALSE 0


#define TONS_AZUL     35
#define TONS_VERDE    71
#define TONS_AZULC    107
#define TONS_VERMELHO 143
#define TONS_LILAS    169
#define TONS_AMARELO  205
#define TONS_BRANCO   241

#define BRANCO  241
#define PRETO   0


#define Ln10 2.30258509299405E+000
#define OneOverLn10 0.43429448190325E+000
#define Pi 3.1415927
#define PiOver180 1.74532925199433E-002
#define PiUnder180 5.72957795130823E+001
