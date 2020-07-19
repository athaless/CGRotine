
// Plot		 - place pixel to screen
// Set_Palette	 - set palette register
// Init_Palette  - 64 levels of grey, red, green and blue
// Init_Palette2 - 7 colors with 35 intensities each - use with Pixel
// Cycle_Palette - cycle through palette
// Circle	 - circle draw routine
// Draw		 - line draw routine
// Init_Graphics - initialize graphics
// Wait_For_Key	 - wait for key press
// Exit_Graphics - sound and wait for keypress before exiting graphics
// Title	 - set up text screen colors


#include "stdio.h"
#include "stdlib.h"
#include "dos.h"
#include "mem.h"
#include "conio.h"
#include "math.h"
#include "malloc.h"
#include "defs.h"
#include "mathb.h"
#include "graphb.h"
#include "graphics.h"


extern int far _Cdecl Svga256_fdriver[];

#define Low_Res    1
#define Medium_Res 2
#define High_Res   3


union  REGS reg;
struct SREGS inreg;

Word   X_Off, Y_Off;
static Word far *Pre_Calc_Y1;
static DWord far *Pre_Calc_Y2;
static Byte Res;

//Isso nao pode ser feito por parametro !
int huge detect0mode256() { return 0; }
int huge detect2mode256() { return 2; }
int huge detect3mode256() { return 3; }
int huge detect4mode256() { return 4; }

/* Original -------------
void Set_Mode(int Mode)
{
 reg.h.ah=0;
 reg.h.al=Mode;
 int86(0x10,&reg,&reg);
}
*/


/*
void Calc_Offsets()
{
  Word tmp, tmp2;

  if(XRes<MaxXRes)
  {
   tmp=MaxXRes>>1;
   tmp2=XRes>>1;
   X_Off=tmp-tmp2;
  }
  else
    X_Off=0;

  if(YRes<MaxYRes)
  {
   tmp=MaxYRes>>1;
   tmp2=YRes>>1;
   Y_Off=tmp-tmp2;
  }
  else
    Y_Off=0;
}

void Pre_Calc()
{
 Word j;

 for(j=0; j<=MaxYRes; j++)
 {
  if(Res==Medium_Res)
    Pre_Calc_Y2[j]=(DWord)MaxXRes*(DWord)j;
  else
    Pre_Calc_Y1[j]=MaxXRes*j;
  }
}
*/

static Word Old_Page, Old_Page_2;

void Plot(Word x, Word y, Byte color)
{
 putpixel(x,y,color);
}

/* Original ---------------------------
void Plot(Word x, Word y, Byte color)
{
  long L_Offset;
  Word Offset, Page;
  char far *address;

  if((x<XRes) && (y<YRes))
  {
    switch(Res)
    {
      case   High_Res : Offset=Pre_Calc_Y1[y+Y_Off]+x+X_Off;
			Page=y>>6;
			if(Page!=Old_Page)
			{
			 outpw(0x3CD, Page|64);
			 Old_Page=Page;
			}
			address=(char far *)(0xA0000000L+Offset);
			*address=color;
			break;

      case Medium_Res :	x+=X_Off;
			y+=Y_Off;
			L_Offset=Pre_Calc_Y2[y]+x;
			Page=(L_Offset>>16);
			Offset=L_Offset&65535;
			if(Page!=Old_Page)
			{
			  outpw(0x3CD, Page|64);
			  Old_Page=Page;
			}
			address=(char far *)(0xA0000000L+Offset);
			*address=color;
			break;

      case     Low_Res :Offset=Pre_Calc_Y1[y+Y_Off]+x+X_Off;
			address=(char far *)(0xA0000000L+Offset);
			*address=color;
			break;
    }
  }
}
*/

static Palette_Register Color;

void Set_Palette(Palette_Register Hue)
{
 reg.x.ax=0x1012;
 segread(&inreg);
 inreg.es=inreg.ds;
 reg.x.bx=0;
 reg.x.cx=256;
 reg.x.dx=(int)&Hue[0];
 int86x(0x10,&reg,&reg,&inreg);
}

void Init_Palette(Palette_Register Color)
{
 register Word i;

 for(i=0;i<64;i++)    {Color[i].Red=i; Color[i].Grn=i;  Color[i].Blu=i; }
 for(i=64;i<128;i++)  {Color[i].Red=i-64; Color[i].Grn=0; Color[i].Blu=0; }
 for(i=128;i<192;i++) {Color[i].Red=0; Color[i].Grn=i-128; Color[i].Blu=0; }
 for(i=192;i<=255;i++){Color[i].Red=0; Color[i].Grn=0; Color[i].Blu=i-192; }
}

void Init_Palette_2(Palette_Register Color)
{
 register Word i;

 for(i=0;i<36;i++)   {Color[i].Red=0; Color[i].Grn=0; Color[i].Blu=Round(1.8*i); }
 for(i=36;i<72;i++)  {Color[i].Red=0; Color[i].Grn=Round(1.8*(i-36)); Color[i].Blu=0; }
 for(i=72;i<108;i++) {Color[i].Red=0; Color[i].Grn=Round(1.8*(i-72)); Color[i].Blu=Round(1.8*(i-72)); }
 for(i=108;i<144;i++){Color[i].Red=Round(1.8*(i-108)); Color[i].Grn=0; Color[i].Blu=0; }
 for(i=144;i<180;i++){Color[i].Red=Round(1.8*(i-144)); Color[i].Grn=0; Color[i].Blu=Round(1.8*(i-144)); }
 for(i=180;i<216;i++){Color[i].Red=Round(1.8*(i-180)); Color[i].Grn=Round(1.8*(i-180)); Color[i].Blu=0; }
 for(i=216;i<252;i++){Color[i].Red=Round(1.8*(i-216)); Color[i].Grn=Round(1.8*(i-216)); Color[i].Blu=Round(1.8*(i-216)); }
}

void Cycle_Palette(Palette_Register Hue)
{
 Word i;
 RGB  tmp;

 tmp=Hue[0];
 memcpy(&Hue[0], &Hue[1], 765);
 Hue[255]=tmp;
 Set_Palette(Hue);
}

void Swap(int *first, int *second)
{
 int temp;

 temp=*first;
 *first=*second;
 *second=temp;
}

void Circle(Word x, Word y, Word radius, Byte color)
{
  int a, af, b, bf, target, r2, asp;

  if(Res==High_Res)
    asp=100;
  else
    asp=120;

  target=0;
  a=radius;
  b=0;
  r2=Sqr(radius);
  while(a>=b)
  {
   b=Round(sqrt(r2-Sqr(a)));
   Swap(&target,&b);

   while(b<target)
    {
     af=(asp*a)/100;
     bf=(asp*b)/100;
     Plot(x+af, y+b, color);
     Plot(x+bf, y+a, color);
     Plot(x-af, y+b, color);
     Plot(x-bf, y+a, color);
     Plot(x-af, y-b, color);
     Plot(x-bf, y-a, color);
     Plot(x+af, y-b, color);
     Plot(x+bf, y-a, color);
     ++b;
    }
    --a;
  }
}

void Draw(int xx1, int yy1, int xx2, int yy2, Byte color)
{
  int LgDelta, ShDelta, Cycle, LgStep, ShStep, dtotal;

  LgDelta=xx2-xx1;
  ShDelta=yy2-yy1;
  if(LgDelta<0)
  {
    LgDelta=-LgDelta;
    LgStep=-1;
  }
  else
    LgStep=1;
  if(ShDelta<0)
  {
    ShDelta=-ShDelta;
    ShStep=-1;
  }
  else
    ShStep=1;
  if(ShDelta<LgDelta)
  {
    Cycle=LgDelta>>1;
    while(xx1!=xx2)
    {
      Plot(xx1, yy1, color);
      Cycle+=ShDelta;
      if(Cycle>LgDelta)
      {
	Cycle-=LgDelta;
	yy1+=ShStep;
      }
      xx1+=LgStep;
    }
    Plot(xx1, yy1, color);
  }
  else
  {
    Cycle=ShDelta >> 1;
    Swap(&LgDelta, &ShDelta);
    Swap(&LgStep, &ShStep);
    while(yy1 != yy2)
    {
      Plot(xx1, yy1, color);
      Cycle+=ShDelta;
      if(Cycle>LgDelta)
      {
	Cycle-=LgDelta;
	xx1+=ShStep;
      }
      yy1+=LgStep;
    }
    Plot(xx1, yy1, color);
  }
}

int   CentreX, CentreY;


void Init_Graphics(Byte Mode)
{
  int Graph=DETECT,AUX;

  //[1]->(NOT SUPORTED)
  //[0]->(320x200x256) //[2]->(640x480x256)
  //[3]->(800x600x256) //[4]->(1024x768x256) //[1]->(NOT SUPORTED)!!!

  switch(Mode)
  {
    case 0   : Res=Low_Res;
	       MaxXRes=320;MaxYRes=200;
	       installuserdriver("Svga256",detect0mode256);
	       break;

    case 2   : Res=Medium_Res;
	       MaxXRes=640;MaxYRes=480;
	       installuserdriver("Svga256",detect2mode256);
	       break;

    case 3   : Res=Medium_Res;
	       MaxXRes=800;MaxYRes=600;
	       installuserdriver("Svga256",detect3mode256);
	       break;

    case 4   : Res=High_Res;
	       MaxXRes=1024;MaxYRes=768;
	       installuserdriver("Svga256",detect4mode256);
	       break;

    default  : printf("Mode %d is not a valid graphics mode\n\n",Mode);
	       puts("Hit any key to exit");
	       getch();
	       exit(1);
	       break;
  }
  initgraph(&Graph,&AUX,"");


  MaxX=MaxXRes-1;
  MaxY=MaxYRes-1;
  if(XRes==0)
    XRes=MaxXRes;
  if(YRes==0)
    YRes=MaxYRes;

  CentreX=XRes/2;
  CentreY=YRes/2;

  Asp=(1024.0/768.0)*((float)YRes/(float)XRes);

  Init_Palette_2(Color);
  Set_Palette(Color);
}


/* Original ------------------
void Init_Graphics(Byte Mode)
{
  int Graph=DETECT,Mode;

  installuserdriver("Svga256",Set_Mode256(Mode));
  initgraph(&Graph,&Mode,"");

  switch(Mode)
  {
    case 19  : Res=Low_Res;
	       MaxXRes=320;
	       MaxYRes=200;
	       break;
    case 45  : Res=Medium_Res;
	       MaxXRes=640;
	       MaxYRes=350;
	       break;
    case 120 : Res=Medium_Res;
	       MaxXRes=640;
	       MaxYRes=400;
	       break;
    case 46  : Res=Medium_Res;
	       MaxXRes=640;
	       MaxYRes=480;
	       break;
    case 48  : Res=Medium_Res;
	       MaxXRes=800;
	       MaxYRes=600;
	       break;
    case 56  : Res=High_Res;
	       MaxXRes=1024;
	       MaxYRes=768;
	       break;
    default  : printf("Mode %d is not a valid graphics mode\n\n",Mode);
	       puts("Hit any key to exit");
	       getch();
	       exit(1);
	       break;
  }
  MaxX=MaxXRes-1;
  MaxY=MaxYRes-1;
  if(XRes==0)
    XRes=MaxXRes;
  if(YRes==0)
    YRes=MaxYRes;
  Calc_Offsets();
  if(Res==Medium_Res)
    Pre_Calc_Y2=farcalloc(768, sizeof(DWord));
  else
    Pre_Calc_Y1=farcalloc(768, sizeof(Word));
  CentreX=XRes/2;
  CentreY=YRes/2;
  Asp=(1024.0/768.0)*((float)YRes/(float)XRes);

  Pre_Calc();
  Set_Mode(Mode);
  Init_Palette_2(Color);
  Set_Palette(Color);
}
*/


void Set_Graphics_Mode(Word xRes, Word yRes)
{
  XRes=xRes;
  YRes=yRes;
  if((XRes<321) && (YRes<201))
    Init_Graphics(19);
  else if((XRes<641) && (YRes<351))
    Init_Graphics(45);
  else if((XRes<641) && (YRes<401))
    Init_Graphics(120);
  else if((XRes<641) && (YRes<481))
    Init_Graphics(46);
  else if((XRes<801) && (YRes<601))
    Init_Graphics(48);
  else
    Init_Graphics(56);
}

void Wait_For_Key()
{
  char k;

  while(!(k=getch()));
}

void Exit_Graphics()
{
  //sound(1000);
  //delay(500);
  //nosound();
  if(Pre_Calc_Y1>0) farfree(Pre_Calc_Y1);
  if(Pre_Calc_Y2>0) farfree(Pre_Calc_Y2);
  Wait_For_Key();
  //Set_Mode(3);
  closegraph();
}

void Title()
{
  textcolor(YELLOW);
  textbackground(BLUE);
  clrscr();
}

/*
   様様様様様様様様様様様様様様様様様様様様様
    *                                     *
    * Three Dimensional Plotting Routines *
    *				          *
   様様様様様様様様様様様様様様様様様様様様様

   InitPlotting       - rotation and tilt angles
   InitPerspective    - observer location and distances
   MapCoordinates     - maps 3D space onto the 2D screen
   CartesianPlot      - plot a cartesian system point
   CylindricalPlot3D  - plot a cylindrical system point
   SphericalPlot3D    - plot a spherical system point
   DrawLine3D	      - plots a line from 3D coordinates  */

float CosA, SinA;
float CosB, SinB;
float CosACosB, SinASinB;
float CosASinB, SinACosB;

void Init_Plotting(int Ang, int Tlt)
{
  CentreX=XRes/2;
  CentreY=YRes/2;
  Angl=Ang;
  Tilt=Tlt;
  CosA=CosD(Angl);
  SinA=SinD(Angl);
  CosB=CosD(Tilt);
  SinB=SinD(Tilt);
  CosACosB=CosA*CosB;
  SinASinB=SinA*SinB;
  CosASinB=CosA*SinB;
  SinACosB=SinA*CosB;
}

void Init_Perspective(Boolean Perspective, float x, float y, float z, float m)
{
  PerspectivePlot=Perspective;
  Mx=x;
  My=y;
  Mz=z;
  ds=m;
}

void Map_Coordinates(float X, float Y, float Z, int *Xp, int *Yp)
{
  float Xt, Yt, Zt;
  float OneOverZt;

  Xt=(Mx+X*CosA-Y*SinA);
  Yt=(My+X*SinASinB+Y*CosASinB+Z*CosB);
  if(PerspectivePlot)
  {
    Zt=Mz+X*SinACosB+Y*CosACosB-Z*SinB;
    OneOverZt=1.0/Zt;
    *Xp=CentreX+Round(ds*Xt*OneOverZt);
    if(Res!=Low_Res)
      *Yp=CentreY-Round(ds*Yt*OneOverZt);
    else
      *Yp=CentreY-Round(ds*Yt*OneOverZt*Asp);
  }
  else
  {
   *Xp=CentreX+Round(Xt);

   if(Res!=Low_Res)
    *Yp=CentreY-Round(Yt);
   else
    *Yp=CentreY-Round(Yt*Asp);
  }
}

void Cartesian_Plot_3D(float X, float Y, float Z, Byte Color)
{
  int Xp, Yp;

  Map_Coordinates(X, Y, Z, &Xp, &Yp);
  Plot(Xp, Yp, Color);
}

void Cylindrical_Plot_3D(float Rho, float Theta, float Z, Byte Color)
{
  float X, Y;

  Theta=Radians(Theta);
  X=Rho*cos(Theta);
  Y=Rho*sin(Theta);
  Cartesian_Plot_3D(X, Y, Z, Color);
}

void Spherical_Plot_3D(float R, float Theta, float Phi, Byte Color)
{
  float X, Y, Z;

  Theta=Radians(Theta);
  Phi=Radians(Phi);
  X=R*sin(Theta)*cos(Phi);
  Y=R*sin(Theta)*sin(Phi);
  Z=R*cos(Theta);
  Cartesian_Plot_3D(X, Y, Z, Color);
}

void Draw_Line_3D(TDA Pnt1, TDA Pnt2, Byte Color)
{
  int   Xp1, Yp1;
  int   Xp2, Yp2;
  float x1, y1, z1;
  float x2, y2, z2;

  UnVec(Pnt1, &x1, &y1, &z1);
  UnVec(Pnt2, &x2, &y2, &z2);
  Map_Coordinates(x1, y1, z1, &Xp1, &Yp1);
  Map_Coordinates(x2, y2, z2, &Xp2, &Yp2);
  Draw(Xp1, Yp1, Xp2, Yp2, Color);
}

/* **********************
   *                    *
   *       Pixel        *
   *		        *
   **********************

   PutPixel - plots pixel
   GetPixel - gets pixel

   Color 1 - Blue   2 - Green    3 - Cyan
	 4 - Red    5 - Magenta	 6 - Brown/Yellow  7 - Gray Scale

   Intensity levels (0..35) for each color
*/

void Put_Pixel(int x, int y, Byte Color, Byte Intensity)
{
  Byte Col;

  if(Intensity>MaxInten)  exit(1);

  Col = ((MaxInten+1)*(Color-1)+Intensity) & 255;
  Plot(x, y, Col);
}

Byte Get_Pixel(Word x, Word y)
{
  long L_Offset;
  Word Offset, Page;
  char far *address;
  Byte color;

  if((x<XRes) && (y<YRes))
  {
    switch(Res)
    {
      case High_Res :   Offset=Pre_Calc_Y1[y+Y_Off]+x+X_Off;
			Page=(y>>6)&15;
			if(Page!=Old_Page_2)
			{
			  outpw(0x3CD, (Page<<4)|Old_Page);
			  Old_Page_2=Page;
			}
			address=(char far *)(0xA0000000L+Offset);
			color=*address;
			break;
      case Medium_Res :	x+=X_Off;
			y+=Y_Off;
			L_Offset=Pre_Calc_Y2[y]+x;
			Page=(L_Offset>>16);
			Offset=L_Offset&65535;

			if(Page!=Old_Page_2)
			{
			 outpw(0x3CD, (Page<<4)|Old_Page);
			 Old_Page_2=Page;
			}
			address=(char far *)(0xA0000000L+Offset);
			color=*address;
			break;

      case Low_Res    :	Offset=Pre_Calc_Y1[y+Y_Off]+x+X_Off;
			address=(char far *)(0xA0000000L+Offset);
			color=*address;
			break;
    }
  }

  return(color);
}

Byte Get_Pixel_2(Word x, Word y)
{
  x+=X_Off;
  y+=Y_Off;
  reg.x.ax=3328;
  reg.x.dx=y;
  reg.x.cx=x;
  int86(0x10,&reg,&reg);
  outpw(0x3CD, Old_Page|64);
  return(reg.x.ax&255);
}

/* **********************************************
   *						*
   * Setup of Coordinate Axes and Color Palette	*
   *						*
   **********************************************

   PutAxisAndPalette - toggle for Axis and Palette
   AxisAndPalette    - places Axis and Color Palette on screen
*/

void Put_Axis_And_Palette(Boolean PlaceOnScreen)
{
 if(PlaceOnScreen)
  Draw_Axis_And_Palette=true;
 else
  Draw_Axis_And_Palette=false;
}

void Display_Axis()
{
  int x, y, z, sx, sy;

  sx=XRes/320;
  sy=YRes/200;

  for(x=-100*sx; x<101*sx; x++)
  {
   Cartesian_Plot_3D(x, 0, 0, 35);
   Cartesian_Plot_3D(100*sx, 0, 0, 251);
  }

  for(y=-100*sy; y<101*sy; y++)
  {
   Cartesian_Plot_3D(0, y, 0, 71);
   Cartesian_Plot_3D(0, 100*sy, 0,251);
  }

  for(z=-100*sx; z<101*sx; z++)
  {
   Cartesian_Plot_3D(0, 0, z, 107);
   Cartesian_Plot_3D(0, 0, 100*sx, 251);
  }
}

void Display_Palette()
{
  int  X, Y, sx, sy;
  Byte Color;
  Byte Intensity;

  sx=XRes/320;
  sy=YRes/200;
  for(Color=1; Color<=MaxCol; Color++)
  {
   for(Intensity=0; Intensity<=MaxInten; Intensity++)
   {
    for(X=0; X<4*sx; X++)
    {
     for(Y=0; Y<4*sy; Y++)
     Put_Pixel(X+(5*sx)*Color,(190*sy)-Y-(5*sy)*Intensity,Color,Intensity);

    }
   }
  }
}

void Axis_And_Palette()
{
  if(Draw_Axis_And_Palette)
  {
   Display_Axis();
   Display_Palette();
  }
}