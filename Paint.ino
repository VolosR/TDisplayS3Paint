#include <TFT_eSPI.h> 
TFT_eSPI    tft = TFT_eSPI(); 
TFT_eSprite img = TFT_eSprite(&tft);
TFT_eSprite stats = TFT_eSprite(&tft);
#define gray  0xD69A
#define dgray 0xA514
#define ddgray 0x2124

int fase=0;
int debounce=0;
int debounce2=0;
int debounce3=0;
int debounce4=0;
int x,y;
int nShapes=0;
int chosenShape=0;
int tx1,ty1,tx2,ty2;

const int pwmFreq = 5000;
const int pwmResolution = 8;
const int pwmLedChannelTFT = 5;


int colorsY[10]={40,40,58,58,76,76,94,94,112,112};
int colorsX[10]={280,298,280,298,280,298,280,298,280,298};

int shapesY[8]={40,40,58,58,76,76,94,94};
int shapesX[8]={232,250,232,250,232,250,232,250};


unsigned short shapes[250][8];
const unsigned short colors[10]={TFT_RED,0x1D5E,TFT_GREEN,TFT_ORANGE,TFT_PURPLE,dgray,TFT_YELLOW, 0xBA22,TFT_BLACK,TFT_WHITE};
int c=0;

int imageW=220;
int imageH=168;

void setup() {
 pinMode(21,INPUT_PULLUP);  //pen push button
 pinMode(44,INPUT_PULLUP);   //undo button
 pinMode(0,INPUT_PULLUP);   //chose shape
 pinMode(14,INPUT_PULLUP);  //chose colors

  pinMode(18,OUTPUT);
  digitalWrite(18,1);
 
 tft.init();
 tft.setRotation(1);
 tft.fillScreen(gray); 
 tft.setTextColor(TFT_WHITE,0xA000);
 tft.drawString(" X ",300,0,2);
  tft.setTextColor(TFT_BLACK,gray);
 
 tft.drawRect(0,0,imageW+2,imageH,dgray);
 tft.drawRoundRect(226,20,44,112,3,dgray);
 tft.drawRoundRect(274,20,44,112,3,dgray);

 tft.drawRoundRect(226,134,90,34,3,dgray);
 
 tft.drawString("FILE | EDIT",226,1,2);
 tft.setTextColor(0x4208,gray);
 tft.drawString("COL",278,22,2);
  tft.drawString("SHA",232,22,2);
 img.createSprite(imageW, imageH);
 stats.createSprite(90, 34);
 stats.setTextColor(TFT_BLACK,gray);
 img.fillSprite(TFT_WHITE); 
 
shapes[0][0]=0;  //shape
shapes[0][1]=20; //x1 coordinae
shapes[0][2]=20; //x1 coordinae
shapes[0][3]=100; //x1 coordinae
shapes[0][4]=180; //x1 coordinae
shapes[0][5]=TFT_GREEN; //x1 coordinae
tft.setTextColor(ddgray,gray);
tft.drawString(String(fase),214,212,4);
//tft.fillRect(206,210,32,28,colors[c]);

int counter=0;

for(int j=0;j<10;j++)
tft.fillRect(colorsX[j],colorsY[j],14,14,colors[j]);
tft.drawRect(colorsX[c]-1,colorsY[c]-1,16,16,TFT_BLACK);
tft.drawRect(colorsX[c]-2,colorsY[c]-2,18,18,TFT_BLACK);

for(int m=0;m<7;m++)
tft.fillRect(shapesX[m],shapesY[m],14,14,TFT_WHITE);
tft.drawRect(shapesX[chosenShape]-1,shapesY[chosenShape]-1,16,16,TFT_BLACK);
tft.drawRect(shapesX[chosenShape]-2,shapesY[chosenShape]-2,18,18,TFT_BLACK);

tft.drawLine(shapesX[0]+2,shapesY[0]+2,shapesX[0]+12,shapesY[0]+12,TFT_BLACK);
tft.fillRect(shapesX[1]+3,shapesY[1]+3,8,8,TFT_PURPLE);
tft.fillCircle(shapesX[2]+7,shapesY[2]+7,5,TFT_RED);
tft.fillTriangle(shapesX[3]+1,shapesY[3]+12,shapesX[3]+13,shapesY[3]+12,shapesX[3]+7,shapesY[3]+1,TFT_BLUE);
tft.drawRect(shapesX[4]+3,shapesY[4]+3,8,8,TFT_PURPLE);
tft.drawCircle(shapesX[5]+7,shapesY[5]+7,5,TFT_RED);

 ledcSetup(0, 10000, 8);
     ledcAttachPin(38, 0);
     ledcWrite(0, 180);

}
 //0  is line, 1 is rect, 2 is circle, 3 is triangle 

void loop() {
 x=map(analogRead(17),0,4095,0,imageW);
 y=map(analogRead(16),0,4095,0,imageH);
// tft.drawString("  "+String(x)+"     ",6,0,2);
// tft.drawString("  "+String(y)+"     ",26,0,2);
 draw(x,y);

}



void draw(int x,int y)
  {
   img.fillSprite(TFT_WHITE); 
   stats.fillSprite(gray);
   
   stats.drawString( "X: "+String(x),48,2,2);
   stats.drawString("Y: "+String(y),48,18,2);
   stats.drawString("PEN",0,2,2);
   if(fase==0)
   stats.drawString("UP",0,18,2);
   else
   stats.drawString("DOWN",0,18,2);
   

   //draw Old Objects
   for(int i=0;i<nShapes;i++){
   if(shapes[i][0]==0) //line
   img.drawLine(shapes[i][1],shapes[i][2],shapes[i][3],shapes[i][4],shapes[i][5]); 
   if(shapes[i][0]==1) //rect
   img.fillRect(shapes[i][1],shapes[i][2],shapes[i][3]-shapes[i][1],shapes[i][4]-shapes[i][2],shapes[i][5]);
   if(shapes[i][0]==4) //rect
   img.drawRect(shapes[i][1],shapes[i][2],shapes[i][3]-shapes[i][1],shapes[i][4]-shapes[i][2],shapes[i][5]);
   if(shapes[i][0]==2) //circle
   img.fillCircle(shapes[i][1],shapes[i][2],shapes[i][4]/2,shapes[i][5]); 
   if(shapes[i][0]==5) //circle
   img.drawCircle(shapes[i][1],shapes[i][2],shapes[i][4]/2,shapes[i][5]); 
   if(shapes[i][0]==3) //triangle
   img.fillTriangle(shapes[i][1],shapes[i][2],shapes[i][3],shapes[i][4],shapes[i][6],shapes[i][7],shapes[i][5]); 
   }


   
    if(digitalRead(44)==0) // delete shapes
   {
   if(debounce4==0) 
     {
      debounce4=1;
        if(nShapes>0){
      nShapes--;
      tft.drawString("SHAPES: "+String(nShapes)+"  ",130,2,2);
      fase=0;}
      delay(100);
     }
   }else debounce4=0;

    if(digitalRead(0)==0) // chose shapes
   {
   if(debounce3==0) 
     {
      debounce3=1;
      tft.drawRect(shapesX[chosenShape]-1,shapesY[chosenShape]-1,16,16,gray);
      tft.drawRect(shapesX[chosenShape]-2,shapesY[chosenShape]-2,18,18,gray);
      chosenShape++;
      if(chosenShape>6)
      chosenShape=0;
      tft.drawRect(shapesX[chosenShape]-1,shapesY[chosenShape]-1,16,16,TFT_BLACK);
      tft.drawRect(shapesX[chosenShape]-2,shapesY[chosenShape]-2,18,18,TFT_BLACK);
      delay(100);
     }
   }else debounce3=0;

   if(digitalRead(14)==0) // chose colors 14
   {
   if(debounce2==0) 
     {
      debounce2=1;
      
     
      tft.drawRect(colorsX[c]-1,colorsY[c]-1,16,16,gray);
      tft.drawRect(colorsX[c]-2,colorsY[c]-2,18,18,gray);
       c++;
       if(c>9)
       c=0;
      tft.drawRect(colorsX[c]-1,colorsY[c]-1,16,16,TFT_BLACK);
      tft.drawRect(colorsX[c]-2,colorsY[c]-2,18,18,TFT_BLACK);
      
     
     // tft.fillRect(206,210,32,28,colors[c]);
      delay(100);
     }
   }else debounce2=0;

   if(digitalRead(21)==0)
   {
   if(debounce==0) 
       {
        if(chosenShape==3)
        {
        debounce=1;
        fase++;
        tft.drawString(String(fase),214,212,4);
        if(fase==1)
        {
          tx1=x;
          ty1=y;
          fase++;
        }
          if(fase==3)
        {
          tx2=x;
          ty2=y;
          fase++;
        }
        if(fase==5)
        {
          
          shapes[nShapes][0]=chosenShape;
          shapes[nShapes][1]=tx1;
          shapes[nShapes][2]=ty1;
          shapes[nShapes][3]=tx2;
          shapes[nShapes][4]=ty2;
          shapes[nShapes][6]=x;
          shapes[nShapes][7]=y;
          shapes[nShapes][5]=colors[c];
          nShapes++;
         tft.drawString("SHAPES: "+String(nShapes),130,3,2);
          fase=0;
          tft.drawString(String(fase),214,212,4);
        }
         
        }else{
        debounce=1;
        fase++;
         tft.drawString(String(fase),214,212,4);
       
        if(fase==1)
        {
          tx1=x;
          ty1=y;
          fase++;
        }
        if(fase==3)
        {
          
          shapes[nShapes][0]=chosenShape;
          shapes[nShapes][1]=tx1;
          shapes[nShapes][2]=ty1;
          shapes[nShapes][3]=x;
          shapes[nShapes][4]=y;
          shapes[nShapes][5]=colors[c];
          fase=0;
          nShapes++;
          tft.drawString(String(fase),214,212,4);
           
        }
       }}
       delay(100);
   }else {debounce=0;}

   
  
    if(chosenShape==0 && fase==2)
    img.drawLine(tx1,ty1,x,y,colors[c]);
    if(chosenShape==1 && fase==2)
    img.fillRect(tx1,ty1,x-tx1,y-ty1,colors[c]);
    if(chosenShape==4 && fase==2)
    img.drawRect(tx1,ty1,x-tx1,y-ty1,colors[c]);
    if(chosenShape==2 && fase==2)
    img.fillCircle(tx1,ty1,y/2,colors[c]);
    if(chosenShape==5 && fase==2)
    img.drawCircle(tx1,ty1,y/2,colors[c]);
    if(chosenShape==3 && fase==4)
    img.fillTriangle(tx1,ty1,tx2,ty2,x,y,colors[c]);
   
   
   img.fillCircle(x,y,2,TFT_RED);
   img.pushSprite(1, 1);
   stats.pushSprite(226,134);
  }
