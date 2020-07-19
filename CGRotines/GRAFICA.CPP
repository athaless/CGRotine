
#include "stdio.h"
#include "stdlib.h"
#include "conio.h"
#include "graphics.h"
#include "math.h"
#include "dos.h"

#include "defs.h"
#include "globals.h"
#include "mathb.h"
#include "graphb.h"

#define TreeColor (2*36-1)-10
#define LeafColor (5*36-1)


void Tree(Word y, Word x,float Angle, float BranchFan,float Height, float HeightFactor, Byte Depth);
void orbits(int,int);
void myorbit();
void casa();
void estrela();
void coisa();
void piramide();
void linha();
void limpa_area(int,int,int,int,int);




//Relativo somente a funcao Tree
  Word x=512;             /*  coordinate for base of trunk  */
  Word y=767;
  float Angle=0.0;        /*  trunk Angle with respect to ground normal  */
  float BranchFan=45.0;   /*  maximum 'fan' of branch grouping  */
  float Height=120.0;     /*  Height of trunk  */
  float HeightFactor=0.75;
  float AngleFactor=0.75;
  float BranchDensity=2.0;
  Byte Depth=10;
  float InvBranchDensity;
//------------------------------------------------------------------





void main()
{
  Init_Graphics(3);
  Init_Perspective(false, 0, 0, 500, 500);

  orbits(2,0);
  getch();  linha();
  getch();  piramide();
  getch();  casa();
  getch();  estrela();
  //getch();  coisa();
  getch();  myorbit();

  limpa_area(90,1,799,599,TRUE);
  InitRand(3.9);
  InvBranchDensity=1.0/BranchDensity;
  Tree(y, x, Angle, BranchFan, Height, HeightFactor, Depth);
  getch();

  Exit_Graphics();

  //200(ศ) 201(ษ) 187(ป) 188(ผ) 186(บ) 205(อ)
  textcolor(7);
  window(0,0,80,25);
  cprintf("ษออออออออออออออออออออออออป\r\n");
  cprintf("บ Teste para COMP.GRAFICAบ\r\n");
  cprintf("ฬออออออออออออออออออออออออสออออออออออออออออออออออออออออออออออออออออออออออออออป\r\n");
  cprintf("บ Novas rotinas de manipulacao grafica em 3D      by Alessander Oliveira... บป\r\n");
  cprintf("ศอออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผบ\r\n");
  cprintf(" ศอออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ\r\n");
  cprintf("                                                            That's all folks !\r\n");

  exit(0);
}





void limpa_area(int xi,int yi,int xf,int yf,int border)
{
 setfillstyle(SOLID_FILL,PRETO);
 bar(xi,yi,xf,yf);
 if (border)
 {
  setcolor(BRANCO);
  rectangle(xi,yi,xf,yf);
 }

}

void orbits (int orbit,int rastro)
{
  float X1, Y1, Z1, Vx1, Vy1, Vz1, Ax1, Ay1, Az1;
  float X2, Y2, Z2, Vx2, Vy2, Vz2, Ax2, Ay2, Az2;
  float X3, Y3, Z3, Vx3, Vy3, Vz3, Ax3, Ay3, Az3;
  float D12, D23, D31, dt;
  float Dx12, Dx23, Dx31;
  float Dy12, Dy23, Dy31;
  float Dz12, Dz23, Dz31;
  float Tx12, Tx23, Tx31;
  float Ty12, Ty23, Ty31;
  float Tz12, Tz23, Tz31;
  int   Xp1, Yp1, Zp1, Xp2, Yp2, Zp2, Xp3, Yp3, Zp3;
  int   M1, M2, M3;
  float s;


  limpa_area(90,1,799,599,TRUE);

  Init_Plotting(245, 25);
  Put_Axis_And_Palette(true);
  Axis_And_Palette();
  outtextxy(15,10,"PALETTE");

  switch(orbit)
    {
     case 0:
	    M1=12;
	    M2=1;
	    M3=1;
	    X1=0.0;	Y1=0.0;		Z1=  0.0;
	    X2=0.0;	Y2=0.0;         Z2=-40.0;
	    X3=0.0;	Y3=0.0;         Z3= 40.0;
	    Vx1= 0.0000;	Vy1= 0.0000;    Vz1= 0.0000;
	    Vx2=-0.1000;	Vy2=-0.1000;    Vz2=-0.1000;
	    Vx3= 0.1000;	Vy3= 0.1000;    Vz3= 0.1000;
	    dt=0.2;
	    s=2.0; //zoom
	    break;
    case 1:
	    M1=1;
	    M2=10;
	    M3=3;
	    X1=-40.0;	Y1=0.0;		Z1=0.0;
	    X2= 00.0;	Y2=0.0;         Z2=0.0;
	    X3= 90.0;	Y3=0.0;         Z3=0.0;
	    Vx1= 0.1010;	Vy1= 0.2500;    Vz1=-0.0240;
	    Vx2= 0.0010;	Vy2= 0.0010;    Vz2= 0.0240;
	    Vx3=-0.0200;	Vy3=-0.1010;    Vz3= 0.1540;
	    dt=0.4;
	    s=1.0;
	    break;
    case 2:
	    M1=5;
	    M2=1;
	    M3=10;
	    X1=-10.0;	Y1=-90.0;	Z1= 10.0;
	    X2=  0.0;	Y2=-70.0;       Z2=-40.0;
	    X3= 15.0;	Y3=-90.0;       Z3= 40.0;
	    Vx1= 0.2000;	Vy1= 0.0300;    Vz1= 0.0070;
	    Vx2=-0.1000;	Vy2=-0.1020;    Vz2=-0.1000;
	    Vx3= 0.1000;	Vy3= 0.0991;    Vz3= 0.1000;
	    dt=0.3;
	    s=1.5;
	    break;

    case 3:
	    M1=1;
	    M2=6;
	    M3=4;
	    X1=-40.0;	Y1=  0.0;	Z1=  0.0;
	    X2=  0.0;	Y2=  0.0;       Z2=  0.0;
	    X3= 90.0;	Y3=  0.0;       Z3=  0.0;
	    Vx1= 0.1010;	Vy1= 0.2500;    Vz1=-0.0240;
	    Vx2= 0.0010;	Vy2= 0.0010;    Vz2=-0.0440;
	    Vx3=-0.0200;	Vy3=-0.1010;    Vz3= 0.1240;
	    dt=0.1;
	    s=1.0;
	    break;
    case 4:
	    M1=5;
	    M2=7;
	    M3=12;
	    X1=-40.0;	Y1= 16.0;	Z1=-20.0;
	    X2=  0.0;	Y2= 64.0;       Z2=  2.0;
	    X3=-10.0;	Y3=-20.0;       Z3= 52.0;
	    Vx1= 0.2010;	Vy1= 0.2600;    Vz1=-0.1240;
	    Vx2= 0.2600;	Vy2= 0.2010;    Vz2=-0.1623;
	    Vx3=-0.0200;	Vy3=-0.1010;    Vz3= 0.3140;
	    dt=0.15;
	    s=0.5;
	    break;
    case 5:
	    M1=6;
	    M2=1;
	    M3=16;
	    X1=-20.0;	Y1=-16.0;	Z1=-25.0;
	    X2= 20.0;	Y2= 14.0;       Z2= -2.0;
	    X3= 10.0;	Y3= 20.0;       Z3= 12.0;
	    Vx1= 0.2010;	Vy1= 0.2200;    Vz1=-0.1240;
	    Vx2= 0.1600;	Vy2= 0.3010;    Vz2=-0.2623;
	    Vx3=-0.1200;	Vy3=-0.3910;    Vz3=-0.1140;
	    dt=0.30;
	    s=0.25;
	    break;

    case 6:
	    M1=35;
	    M2=2;
	    M3=4;
	    X1=  0.0;	Y1=  0.0;	Z1=  0.0;
	    X2=  0.0;	Y2= 40.0;       Z2=  0.0;
	    X3=  0.0;	Y3= 80.0;       Z3=  0.0;
	    Vx1= 0.0000;	Vy1= 0.0000;    Vz1= 0.0000;
	    Vx2= 0.0000;	Vy2= 0.0000;    Vz2= 1.0000;
	    Vx3= 0.0000;	Vy3= 0.0000;    Vz3=-0.6500;
	    dt=0.10;
	    s=1.0;
	    break;

    case 7:
	    M1=35;
	    M2=2;
	    M3=4;
	    X1=  0.0;	Y1=  0.0;	Z1=  0.0;
	    X2=  0.0;	Y2= 40.0;       Z2=  0.0;
	    X3=  0.0;	Y3=100.0;       Z3=  0.0;
	    Vx1= 0.0000;	Vy1= 0.0000;    Vz1= 0.0000;
	    Vx2= 0.0010;	Vy2= 0.0000;    Vz2= 1.0000;
	    Vx3=-0.0010;	Vy3= 0.0000;    Vz3=-0.5000;
	    dt=0.10;
	    s=1.0;
	    break;

    case 8:
	    M1=35;
	    M2=2;
	    M3=4;
	    X1=  0.0;	Y1=  0.0;	Z1=  0.0;
	    X2=  0.0;	Y2= 40.0;       Z2=  0.0;
	    X3=  0.0;	Y3=100.0;       Z3=  0.0;
	    Vx1= 0.0000;	Vy1= 0.0000;    Vz1= 0.0000;
	    Vx2= 0.0000;	Vy2= 0.0000;    Vz2= 1.0000;
	    Vx3= 0.6500;	Vy3= 0.4000;    Vz3=-0.0400;
	    dt=0.10;
	    s=1.0;
	    break;
   }

  do
  {
    if (rastro==1)
     {
      Cartesian_Plot_3D(X1*s, Y1*s, Z1*s, 0);
      Cartesian_Plot_3D(X2*s, Y2*s, Z2*s, 0);
      Cartesian_Plot_3D(X3*s, Y3*s, Z3*s, 0);
     }
    X1+=Vx1*dt;
    Y1+=Vy1*dt;
    Z1+=Vz1*dt;
    X2+=Vx2*dt;
    Y2+=Vy2*dt;
    Z2+=Vz2*dt;
    X3+=Vx3*dt;
    Y3+=Vy3*dt;
    Z3+=Vz3*dt;
    Cartesian_Plot_3D(X1*s, Y1*s, Z1*s, 143);
    Cartesian_Plot_3D(X2*s, Y2*s, Z2*s, 169);
    Cartesian_Plot_3D(X3*s, Y3*s, Z3*s, 205);
    Dx12=X1-X2;
    Dy12=Y1-Y2;
    Dz12=Z1-Z2;
    Dx23=X2-X3;
    Dy23=Y2-Y3;
    Dz23=Z2-Z3;
    Dx31=X3-X1;
    Dy31=Y3-Y1;
    Dz31=Z3-Z1;
    D12=sqrt(SqrFP(Dx12)+SqrFP(Dy12)+SqrFP(Dz12));
    D12=1.0/(D12*D12*D12);
    D23=sqrt(SqrFP(Dx23)+SqrFP(Dy23)+SqrFP(Dz23));
    D23=1.0/(D23*D23*D23);
    D31=sqrt(SqrFP(Dx31)+SqrFP(Dy31)+SqrFP(Dz31));
    D31=1.0/(D31*D31*D31);
    Tx31=Dx31*D31;
    Ty31=Dy31*D31;
    Tz31=Dz31*D31;
    Tx12=Dx12*D12;
    Ty12=Dy12*D12;
    Tz12=Dz12*D12;
    Tx23=Dx23*D23;
    Ty23=Dy23*D23;
    Tz23=Dz23*D23;
    Ax1=(M3*Tx31-M2*Tx12);
    Ay1=(M3*Ty31-M2*Ty12);
    Az1=(M3*Tz31-M2*Tz12);
    Ax2=(M1*Tx12-M3*Tx23);
    Ay2=(M1*Ty12-M3*Ty23);
    Az2=(M1*Tz12-M3*Tz23);
    Ax3=(M2*Tx23-M1*Tx31);
    Ay3=(M2*Ty23-M1*Ty31);
    Az3=(M2*Tz23-M1*Tz31);
    Vx1+=Ax1*dt;
    Vy1+=Ay1*dt;
    Vz1+=Az1*dt;
    Vx2+=Ax2*dt;
    Vy2+=Ay2*dt;
    Vz2+=Az2*dt;
    Vx3+=Ax3*dt;
    Vy3+=Ay3*dt;
    Vz3+=Az3*dt;

  }
  while(!(kbhit()));
}


void casa()
{
 TDA pontoI,pontoF;
 int zss=10,zdd=0,flag;
 float dist=80;

 Init_Plotting(zss, 18);
 limpa_area(90,1,799,599,TRUE);

 dist=0;flag=TRUE;

 while (!kbhit())
  {
   limpa_area(200,100,600,500,FALSE);
   zss+=2;zdd++;
   Init_Plotting(zss, 18);

   if (flag==TRUE)
    dist++;
   else
    dist--;

   if (dist>=110) flag=FALSE;
   if (dist<=0) flag=TRUE;


   //Draw_Line_3D(TDA Pnt1, TDA Pnt2, Byte Color)
   //Base da casa float
    pontoI[0]=dist ; pontoI[1]=dist; pontoI[2]=0.0;
    pontoF[0]=-dist; pontoF[1]=dist; pontoF[2]=0.0;Draw_Line_3D (pontoI,pontoF,TONS_VERMELHO);
    pontoI[0]=-dist; pontoI[1]=dist; pontoI[2]=0.0;
    pontoF[0]=-dist; pontoF[1]=-dist;pontoF[2]=0.0;Draw_Line_3D (pontoI,pontoF,TONS_VERMELHO);
    pontoI[0]=-dist; pontoI[1]=-dist;pontoI[2]=0.0;
    pontoF[0]=dist ; pontoF[1]=-dist;pontoF[2]=0.0;Draw_Line_3D (pontoI,pontoF,TONS_VERMELHO);
    pontoI[0]=dist ; pontoI[1]=-dist;pontoI[2]=0.0;
    pontoF[0]=dist ; pontoF[1]=dist; pontoF[2]=0.0;Draw_Line_3D (pontoI,pontoF,TONS_VERMELHO);
   //Foro da casa
    pontoI[0]=dist ; pontoI[1]=dist; pontoI[2]=dist;
    pontoF[0]=-dist; pontoF[1]=dist; pontoF[2]=dist;Draw_Line_3D (pontoI,pontoF,TONS_LILAS);
    pontoI[0]=-dist; pontoI[1]=dist; pontoI[2]=dist;
    pontoF[0]=-dist; pontoF[1]=-dist;pontoF[2]=dist;Draw_Line_3D (pontoI,pontoF,TONS_LILAS);
    pontoI[0]=-dist; pontoI[1]=-dist;pontoI[2]=dist;
    pontoF[0]=dist ; pontoF[1]=-dist;pontoF[2]=dist;Draw_Line_3D (pontoI,pontoF,TONS_LILAS);
    pontoI[0]=dist ; pontoI[1]=-dist;pontoI[2]=dist;
    pontoF[0]=dist ; pontoF[1]=dist; pontoF[2]=dist;Draw_Line_3D (pontoI,pontoF,TONS_LILAS);
   //Ligacao das paredes
    pontoI[0]=dist ; pontoI[1]=dist; pontoI[2]=dist;
    pontoF[0]=dist ; pontoF[1]=dist; pontoF[2]=0.0 ;Draw_Line_3D (pontoI,pontoF,TONS_LILAS);
    pontoI[0]=-dist; pontoI[1]=dist; pontoI[2]=0.0;
    pontoF[0]=-dist; pontoF[1]=dist; pontoF[2]=dist;Draw_Line_3D (pontoI,pontoF,TONS_LILAS);
    pontoI[0]=-dist; pontoI[1]=-dist;pontoI[2]=0.0;
    pontoF[0]=-dist; pontoF[1]=-dist;pontoF[2]=dist;Draw_Line_3D (pontoI,pontoF,TONS_LILAS);
    pontoI[0]=dist ; pontoI[1]=-dist;pontoI[2]=0.0;
    pontoF[0]=dist ; pontoF[1]=-dist;pontoF[2]=dist;Draw_Line_3D (pontoI,pontoF,TONS_LILAS);
   //Telhado
    pontoI[0]=110.0; pontoI[1]=-dist; pontoI[2]=dist;
    pontoF[0]=0.0;   pontoF[1]=-dist; pontoF[2]=110.0;Draw_Line_3D (pontoI,pontoF,TONS_AMARELO);
    pontoI[0]=0.0;   pontoI[1]=-dist; pontoI[2]=110.0;
    pontoF[0]=-110.0;pontoF[1]=-dist; pontoF[2]=dist;Draw_Line_3D (pontoI,pontoF,TONS_AMARELO);
    pontoI[0]=0.0;   pontoI[1]=-dist; pontoI[2]=110.0;
    pontoF[0]=0.0;   pontoF[1]=dist ; pontoF[2]=110.0;Draw_Line_3D (pontoI,pontoF,TONS_AMARELO);
    pontoI[0]=110.0; pontoI[1]=dist;  pontoI[2]=dist;
    pontoF[0]=0.0;   pontoF[1]=dist;  pontoF[2]=110.0;Draw_Line_3D (pontoI,pontoF,TONS_AMARELO);
    pontoI[0]=0.0;   pontoI[1]=dist;  pontoI[2]=110.0;
    pontoF[0]=-110.0;pontoF[1]=dist;  pontoF[2]=dist;Draw_Line_3D (pontoI,pontoF,TONS_AMARELO);
   //Porta
    pontoI[0]=30.0;pontoI[1]=dist;pontoI[2]=0.0;
    pontoF[0]=30.0;pontoF[1]=dist;pontoF[2]=40.0;Draw_Line_3D (pontoI,pontoF,TONS_AZUL);
    pontoI[0]=30.0;pontoI[1]=dist;pontoI[2]=40.0;
    pontoF[0]=60.0;pontoF[1]=dist;pontoF[2]=40.0;Draw_Line_3D (pontoI,pontoF,TONS_AZUL);
    pontoI[0]=60.0;pontoI[1]=dist;pontoI[2]=40.0;
    pontoF[0]=60.0;pontoF[1]=dist;pontoF[2]=0.0; Draw_Line_3D (pontoI,pontoF,TONS_AZUL);
   //Janela
    pontoI[0]=-50.0;pontoI[1]=dist;pontoI[2]=30.0;
    pontoF[0]=-50.0;pontoF[1]=dist;pontoF[2]=65.0;Draw_Line_3D (pontoI,pontoF,TONS_VERDE);
    pontoI[0]=-50.0;pontoI[1]=dist;pontoI[2]=65.0;
    pontoF[0]=0.0;  pontoF[1]=dist;pontoF[2]=65.0;Draw_Line_3D (pontoI,pontoF,TONS_VERDE);
    pontoI[0]=0.0;  pontoI[1]=dist;pontoI[2]=65.0;
    pontoF[0]=0.0;  pontoF[1]=dist;pontoF[2]=30.0;Draw_Line_3D (pontoI,pontoF,TONS_VERDE);
    pontoI[0]=-50.0;pontoI[1]=dist;pontoI[2]=30.0;
    pontoF[0]=0.0;  pontoF[1]=dist;pontoF[2]=30.0;Draw_Line_3D (pontoI,pontoF,TONS_VERDE);
   //Telhado-Pintura
    int aux=-80,i;
    /*
    for (i=0;i<11;i++)
     { pontoI[0]=110.0 ; pontoI[1]=aux; pontoI[2]=dist;
       pontoF[0]=0.0   ; pontoF[1]=aux; pontoF[2]=110.0;
       Draw_Line_3D (pontoI,pontoF,TONS_AMARELO);
       aux+=15; }

    aux=80;
    for (i=0;i<11;i++)
     { pontoI[0]=-110.0; pontoI[1]=aux; pontoI[2]=dist;
       pontoF[0]=0.0; pontoF[1]=aux; pontoF[2]=110.0;Draw_Line_3D (pontoI,pontoF,TONS_AMARELO);
       aux-=15; }
    */
   delay(10);
  }

}


void estrela()
{
 TDA pontoI,pontoF;
 int zss=10,zdd=0,ponta,color,flagC,flagP;

 zss+=2; zdd+=1;
 Init_Plotting(zss,zdd);
 limpa_area(90,1,799,599,TRUE);

 color=36;ponta=0;
 flagC=TRUE;flagP=TRUE;

 while (!kbhit())
  {
   limpa_area(160,60,640,540,FALSE);
   zss+=2; zdd+=1;
   Init_Plotting(zss,zdd);


   if (flagC==TRUE)
    color++;
   else
    color--;
   if (color>=70) flagC=FALSE;
   if (color<=45) flagC=TRUE;


   if (flagP==TRUE)
    ponta++;
   else
    ponta--;
   if (ponta>=240) flagP=FALSE;
   if (ponta<=1)   flagP=TRUE;

   pontoF[0]=0; pontoF[1]=0; pontoF[2]=ponta;
    pontoI[2]=40.0; /*Varia Abaixo*/   /*Varia Abaixo*/
    pontoI[0]=40.0  ; pontoI[1]=-40.0; Draw_Line_3D (pontoI,pontoF,color);
    pontoI[0]=40.0  ; pontoI[1]=40.0;  Draw_Line_3D (pontoI,pontoF,color);
    pontoI[0]=-40.0 ; pontoI[1]=-40.0; Draw_Line_3D (pontoI,pontoF,color);
    pontoI[0]=-40.0 ; pontoI[1]=40.0;  Draw_Line_3D (pontoI,pontoF,color);
   pontoF[0]=0; pontoF[1]=0; pontoF[2]=-ponta;
    pontoI[2]=-40.0; /*Varia Abaixo*/ /*Varia Abaixo*/
    pontoI[0]=40.0 ; pontoI[1]=-40.0; Draw_Line_3D (pontoI,pontoF,color);
    pontoI[0]=40.0 ; pontoI[1]=40.0;  Draw_Line_3D (pontoI,pontoF,color);
    pontoI[0]=-40.0; pontoI[1]=-40.0; Draw_Line_3D (pontoI,pontoF,color);
    pontoI[0]=-40.0; pontoI[1]=40.0;  Draw_Line_3D (pontoI,pontoF,color);

   pontoF[0]=0;     pontoF[1]=ponta;  pontoF[2]=0;
    /*Varia Abaixo*/  pontoI[1]=40.0; /*Varia Abaixo*/
    pontoI[0]=40.0 ;  pontoI[2]=-40.0; Draw_Line_3D (pontoI,pontoF,color);
    pontoI[0]=40.0 ;  pontoI[2]=40.0;  Draw_Line_3D (pontoI,pontoF,color);
    pontoI[0]=-40.0 ; pontoI[2]=-40.0; Draw_Line_3D (pontoI,pontoF,color);
    pontoI[0]=-40.0 ; pontoI[2]=40.0;  Draw_Line_3D (pontoI,pontoF,color);
   pontoF[0]=0; pontoF[1]=-ponta; pontoF[2]=0;
    /*Varia Abaixo*/ pontoI[1]=-40.0; /*Varia Abaixo*/
    pontoI[0]=40.0 ; pontoI[2]=40.0;  Draw_Line_3D (pontoI,pontoF,color);
    pontoI[0]=40.0 ; pontoI[2]=-40.0; Draw_Line_3D (pontoI,pontoF,color);
    pontoI[0]=-40.0; pontoI[2]=40.0;  Draw_Line_3D (pontoI,pontoF,color);
    pontoI[0]=-40.0; pontoI[2]=-40.0; Draw_Line_3D (pontoI,pontoF,color);

   pontoF[0]=-ponta;  pontoF[1]=0.0;   pontoF[2]=0.0;
    pontoI[0]=-40.0; /*Varia Abaixo*/ /*Varia Abaixo*/
    pontoI[1]=40.0; pontoI[2]=40.0;   Draw_Line_3D (pontoI,pontoF,color);
    pontoI[1]=-40.0; pontoI[2]=40.0;  Draw_Line_3D (pontoI,pontoF,color);
    pontoI[1]=40.0; pontoI[2]=-40.0;  Draw_Line_3D (pontoI,pontoF,color);
    pontoI[1]=-40.0; pontoI[2]=-40.0; Draw_Line_3D (pontoI,pontoF,color);
   pontoF[0]=ponta;  pontoF[1]=0.0;   pontoF[2]=0.0;
    pontoI[0]=40;    /*Varia Abaixo*/ /*Varia Abaixo*/
    pontoI[1]=40.0;  pontoI[2]=40.0;  Draw_Line_3D (pontoI,pontoF,color);
    pontoI[1]=-40.0; pontoI[2]=40.0;  Draw_Line_3D (pontoI,pontoF,color);
    pontoI[1]=40.0;  pontoI[2]=-40.0; Draw_Line_3D (pontoI,pontoF,color);
    pontoI[1]=-40.0; pontoI[2]=-40.0; Draw_Line_3D (pontoI,pontoF,color);

   delay(10);
  }
}


void piramide()
{
 TDA pontoI,pontoF;
 int zss=10,zdd=0,ponta,color,flagC,flagP;

 zss+=2; zdd+=1;
 Init_Plotting(zss,zdd);
 limpa_area(90,1,799,599,TRUE);

 color=148;ponta=210;
 flagC=TRUE;flagP=TRUE;

 while (!kbhit())
  {
   limpa_area(160,60,640,540,FALSE);
   zss+=2; zdd+=1;
   Init_Plotting(zss,zdd);


   if (flagC==TRUE)
    color++;
   else
    color--;
   if (color>=180) flagC=FALSE;
   if (color<=150) flagC=TRUE;


   if (flagP==TRUE)
    ponta++;
   else
    ponta--;
   if (ponta>=240) flagP=FALSE;
   if (ponta<=1)   flagP=TRUE;


   pontoF[0]=0; pontoF[1]=0; pontoF[2]=ponta;
    pontoI[2]=80.0; /*Varia Abaixo*/   /*Varia Abaixo*/
    pontoI[0]=80.0  ; pontoI[1]=-80.0; Draw_Line_3D (pontoI,pontoF,color);
    pontoI[0]=80.0  ; pontoI[1]=80.0;  Draw_Line_3D (pontoI,pontoF,color);
    pontoI[0]=-80.0 ; pontoI[1]=-80.0; Draw_Line_3D (pontoI,pontoF,color);
    pontoI[0]=-80.0 ; pontoI[1]=80.0;  Draw_Line_3D (pontoI,pontoF,color);
   pontoF[0]=80.0; pontoF[1]=80.0; pontoF[2]=80.0;
    pontoI[0]=80.0;pontoI[1]=-80.0;pontoI[2]=80.0;Draw_Line_3D (pontoI,pontoF,color);
    pontoI[0]=-80.0;pontoI[1]=80.0;pontoI[2]=80.0;Draw_Line_3D (pontoI,pontoF,color);
   pontoF[0]=-80.0; pontoF[1]=-80.0; pontoF[2]=80.0;
    pontoI[0]=-80.0;pontoI[1]=80.0;pontoI[2]=80.0;Draw_Line_3D (pontoI,pontoF,color);
    pontoI[0]=80.0;pontoI[1]=-80.0;pontoI[2]=80.0;Draw_Line_3D (pontoI,pontoF,color);

   pontoF[0]=0; pontoF[1]=0; pontoF[2]=ponta;
    pontoI[2]=60.0; /*Varia Abaixo*/   /*Varia Abaixo*/
    pontoI[0]=60.0  ; pontoI[1]=-60.0; Draw_Line_3D (pontoI,pontoF,color);
    pontoI[0]=60.0  ; pontoI[1]=60.0;  Draw_Line_3D (pontoI,pontoF,color);
    pontoI[0]=-60.0 ; pontoI[1]=-60.0; Draw_Line_3D (pontoI,pontoF,color);
    pontoI[0]=-60.0 ; pontoI[1]=60.0;  Draw_Line_3D (pontoI,pontoF,color);
   pontoF[0]=60.0; pontoF[1]=60.0; pontoF[2]=60.0;
    pontoI[0]=60.0;pontoI[1]=-60.0;pontoI[2]=60.0;Draw_Line_3D (pontoI,pontoF,color);
    pontoI[0]=-60.0;pontoI[1]=60.0;pontoI[2]=60.0;Draw_Line_3D (pontoI,pontoF,color);
   pontoF[0]=-60.0; pontoF[1]=-60.0; pontoF[2]=60.0;
    pontoI[0]=-60.0;pontoI[1]=60.0;pontoI[2]=60.0;Draw_Line_3D (pontoI,pontoF,color);
    pontoI[0]=60.0;pontoI[1]=-60.0;pontoI[2]=60.0;Draw_Line_3D (pontoI,pontoF,color);

   delay(10);
  }
}



void linha()
{
 TDA pontoI,pontoF;
 int zss=10,zdd=0,color,flagC;

 zss+=2; zdd+=1;
 Init_Plotting(zss,zdd);
 limpa_area(90,1,799,599,TRUE);

 color=36;
 flagC=TRUE;

 while (!kbhit())
  {
   limpa_area(160,60,640,540,FALSE);
   zss+=2; zdd+=1;
   Init_Plotting(zss,zdd);


   if (flagC==TRUE)
    color++;
   else
    color--;
   if (color>=70) flagC=FALSE;
   if (color<=40) flagC=TRUE;

    pontoI[0]=240.0;pontoI[1]=0.0;pontoI[2]=0.0;
    pontoF[0]=50.0;pontoF[1]=0.0; pontoF[2]=50.0;
    Draw_Line_3D (pontoI,pontoF,color);

   delay(10);
  }
}



void myorbit()
{
 unsigned int zss=0,zdd=0;

 limpa_area(90,1,799,599,TRUE);
 Init_Plotting(400, 18);
 Put_Axis_And_Palette(true);
 Axis_And_Palette();

 while (!kbhit())
  {
   zss+=2; zdd+=1;
   Cartesian_Plot_3D(200,0,0,TONS_VERMELHO);
   Cartesian_Plot_3D(30,200,0,TONS_VERDE);
   Cartesian_Plot_3D(0,50,200,TONS_AMARELO);
   Init_Plotting(zss,zdd);
   Cartesian_Plot_3D(200,0,0,BRANCO);
   Cartesian_Plot_3D(30,200,0,BRANCO);
   Cartesian_Plot_3D(0,50,200,BRANCO);
   delay(15);
  }
}



void Tree(Word y, Word x,float Angle, float BranchFan,float Height, float HeightFactor, Byte Depth)
{
  Byte i;
  Word xinc, yinc;
  float Start, Theta;
  Word NewHeight;

  if(Depth==0)
  {
   Draw(x-3, y, x+3, y, LeafColor);
   Draw(x, y-3, x, y+3, LeafColor);
  }
  else
  {
    Start=Angle-BranchFan*0.5;
    Theta=BranchFan*InvBranchDensity;
    if(Depth<3) HeightFactor=HeightFactor*0.5;
    xinc=Round(Height*SinD(Angle))&0xFFFF;
    yinc=Round(Height*CosD(Angle))&0xFFFF;
    Draw(x, y, x+xinc, y-yinc, TreeColor);
    for(i=0; i<=BranchDensity; i++)
    {
      NewHeight=Round(Height*HeightFactor)&0xFFFF;
      Tree(y-yinc, x+xinc,
	   Start*0.5+Sign(Start)*RandInt(abs(Round(Start))+1),
	   BranchFan*AngleFactor,
	   NewHeight*0.5+RandInt(NewHeight+1),
	   HeightFactor,
	   Depth-1);
      Start=Start+Theta;
    }
  }
}

