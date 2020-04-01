/*
Project Name: 2D racing Game
Feature Description:
1)Real Time Score Board
2)Best Score Ever Done by player will be saved in a text file
3)collision detection
4)Game Sound
5)controlling car with right and left button
6)speed and acceleration will be handled by itself and will be defined from Hardness level of the game
*/

#include<windows.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <cmath>
//#include<winmm.lib>

//Game Speed
int FramePerSecond = 1;
//Game Track
int start=0;
int isGameOver=0;
int gameLevel = 0;

//Track Score
int score = 0;

//Form move track
int Upper_Road_Division = 0;
int Middle_Road_Division = 0;
int bottom_Road_Division = 0;

//For Car Left / RIGHT ( X axis movement )
int xValue = 0 ;

//Car Coming
int Vehicle1 = 0; // y axis value of car 1 , coming against player
int xValue1=0;
int vehicle2 = +35;
int xValue2=0;
int vehicle3 = +70;
int xValue3=0;

//For Displaying TEXT
const int font1=(int)GLUT_BITMAP_TIMES_ROMAN_24;
const int font2=(int)GLUT_BITMAP_HELVETICA_18 ;
const int font3=(int)GLUT_BITMAP_8_BY_13;

char s[30];
void renderBitmapString(float x, float y, void *font,const char *string){
    const char *c;
    glRasterPos2f(x, y);
    for (c=string; *c != '\0'; c++) {
        glutBitmapCharacter(font, *c);
    }
}

void PlayGame(){
    //Road
    glColor3f(.55, .60, .68);
    glBegin(GL_POLYGON);
    glVertex2f(20,0);
    glVertex2f(20,100);
    glVertex2f(80,100);
    glVertex2f(80,0);
    glEnd();

    //Road Left Border
    glColor3f(0.70, 0.86, 0.75);
    glBegin(GL_POLYGON);
    glVertex2f(20,0);
    glVertex2f(20,100);
    glVertex2f(23,100);
    glVertex2f(23,0);
    glEnd();

    //Road Right Border
	glColor3f(0.70, 0.86, 0.75);
    glBegin(GL_POLYGON);
    glVertex2f(77,0);
    glVertex2f(77,100);
    glVertex2f(80,100);
    glVertex2f(80,0);
    glEnd();

    //Road Upper Border
    glColor3f(0.95, 1.00, 0.74); // ultra light paste
    glBegin(GL_POLYGON);
    glVertex2f(48,Upper_Road_Division+80);
    glVertex2f(48,Upper_Road_Division+100);
    glVertex2f(52,Upper_Road_Division+100);
    glVertex2f(52,Upper_Road_Division+80);
    glEnd();
    Upper_Road_Division--;
    if(Upper_Road_Division<-100){
        Upper_Road_Division =20;
        score++;
    }

    //Road Middle Border
    glColor3f(0.70, 0.86, 0.75); // light paste
    glBegin(GL_POLYGON);
    glVertex2f(48,Middle_Road_Division+40);
    glVertex2f(48,Middle_Road_Division+60);
    glVertex2f(52,Middle_Road_Division+60);
    glVertex2f(52,Middle_Road_Division+40);
    glEnd();

    Middle_Road_Division--;
    if(Middle_Road_Division<-60){
        Middle_Road_Division =60;
        score++;
    }
    //Road Bottom Division
    glColor3f(0.44, 0.76, 0.70);
    glBegin(GL_POLYGON);
    glVertex2f(48,bottom_Road_Division+0);
    glVertex2f(48,bottom_Road_Division+20);
    glVertex2f(52,bottom_Road_Division+20);
    glVertex2f(52,bottom_Road_Division+0);
    glEnd();
    bottom_Road_Division--;
    if(bottom_Road_Division<-20){
        bottom_Road_Division=100;
        score++;
    }
    //Score Board
    glColor3f(0.53, 0.83, 0.60);
    glBegin(GL_POLYGON);
    glVertex2f(80,97);
    glVertex2f(100,97);
    glVertex2f(100,98-8);
    glVertex2f(80,98-8);
    glEnd();

    //Print Score
    char buffer [50];
    sprintf (buffer, "SCORE: %d", score);
    glColor3f(0.00, 0.00, 0.00);
    renderBitmapString(80.5,95,(void *)font3,buffer);
    //Speed Print
    char buffer1 [50];
    sprintf (buffer1, "SPEED:%d Km/h", FramePerSecond);
   glColor3f(0.00, 0.00, 0.00);
    renderBitmapString(80.5,95-2,(void *)font3,buffer1);
    //level Print
    if(score % 50 == 0){
        int last = score /50;
        if(last!=gameLevel){
            gameLevel = score /50;
            FramePerSecond=FramePerSecond+2;

        }
    }
    char level_buffer [50];
    sprintf (level_buffer, "LEVEL: %d", gameLevel);
    glColor3f(0.00, 0.00, 0.00);
    renderBitmapString(80.5,95-4,(void *)font3,level_buffer);

    //Increse Speed With level

// Player car
//=======================================================================
{
    //Front Tire
    glColor3f(0.000, 0.000, 0.000);
    glBegin(GL_POLYGON);
    glVertex2f(xValue+27-2,5);
    glVertex2f(xValue+27-2,7);
    glVertex2f(xValue+29+2,7);
    glVertex2f(xValue+29+2,5);
    glEnd();
    //Back Tire
    glColor3f(0.000, 0.000, 0.000);
    glBegin(GL_POLYGON);
    glVertex2f(xValue+27-2,1);
    glVertex2f(xValue+27-2,3);
    glVertex2f(xValue+29+2,3);
    glVertex2f(xValue+29+2,1);
    glEnd();
        //Car Body
    glColor3f(0.07, 0.29, 0.37);
    glBegin(GL_POLYGON);
    glVertex2f(xValue+27,1);
    glVertex2f(xValue+27,8);
    //glColor3f(0.000, 0.545, 0.545);

    glVertex2f(xValue+28,10);
    glVertex2f(xValue+29,8);
    glVertex2f(xValue+29,1);
    glEnd();
}
//========================================================================

    //Opposite car 1
    {
    glColor3f(0.000, 0.000, 0.000);
    glBegin(GL_POLYGON);
    glVertex2f(xValue1+27-2,Vehicle1+100-4);
    glVertex2f(xValue1+27-2,Vehicle1+100-6);
    glVertex2f(xValue1+29+2,Vehicle1+100-6);
    glVertex2f(xValue1+29+2,Vehicle1+100-4);
    glEnd();

    glColor3f(0.000, 0.000, 0.000);
    glBegin(GL_POLYGON);
    glVertex2f(xValue1+27-2,Vehicle1+100);
    glVertex2f(xValue1+27-2,Vehicle1+100-2);
    glVertex2f(xValue1+29+2,Vehicle1+100-2);
    glVertex2f(xValue1+29+2,Vehicle1+100);
    glEnd();

    glColor3f(1.00, 0.55, 0.26);
    glBegin(GL_POLYGON);
    glVertex2f(xValue1+27,Vehicle1+100);
    glVertex2f(xValue1+27,Vehicle1+100-7);
    glVertex2f(xValue1+28,Vehicle1+100-9);
    glVertex2f(xValue1+29,Vehicle1+100-7);
    glVertex2f(xValue1+29,Vehicle1+100);
    glEnd();
    Vehicle1--;
    if(Vehicle1<-100){
        Vehicle1=0;
        xValue1=xValue;
    }
    //KIll check car1
    if((abs(xValue-xValue1)<6) && (Vehicle1+100<17)){
            start = 0;
            isGameOver=1;

    }
    }
    //Opposite car 2
    {
    glColor3f(0.000, 0.000, 0.000);
    glBegin(GL_POLYGON);
    glVertex2f(xValue2+27-2,vehicle2+100-4);
    glVertex2f(xValue2+27-2,vehicle2+100-6);
    glVertex2f(xValue2+29+2,vehicle2+100-6);
    glVertex2f(xValue2+29+2,vehicle2+100-4);
    glEnd();

    glColor3f(0.000, 0.000, 0.000);
    glBegin(GL_POLYGON);
    glVertex2f(xValue2+27-2,vehicle2+100);
    glVertex2f(xValue2+27-2,vehicle2+100-2);
    glVertex2f(xValue2+29+2,vehicle2+100-2);
    glVertex2f(xValue2+29+2,vehicle2+100);
    glEnd();

    glColor3f(0.31, 0.80, 0.77);
    glBegin(GL_POLYGON);
    glVertex2f(xValue2+27,vehicle2+100);
    glVertex2f(xValue2+27,vehicle2+100-7);
    glVertex2f(xValue2+28,vehicle2+100-9);
    glVertex2f(xValue2+29,vehicle2+100-7);
    glVertex2f(xValue2+29,vehicle2+100);
    glEnd();
    vehicle2--;
    if(vehicle2<-100){
        vehicle2=0;
        xValue2=xValue;
    }
    //KIll check car2
    if((abs(xValue-xValue2)<6) && (vehicle2+100<17)){
            start = 0;
            isGameOver=1;
    }

    }
    //Opposite car 3
    {
    glColor3f(0.000, 0.000, 0.000);
    glBegin(GL_POLYGON);
    glVertex2f(xValue3+27-2,vehicle3+100-4);
    glVertex2f(xValue3+27-2,vehicle3+100-6);
    glVertex2f(xValue3+29+2,vehicle3+100-6);
    glVertex2f(xValue3+29+2,vehicle3+100-4);
    glEnd();
    glColor3f(0.000, 0.000, 0.000);
    glBegin(GL_POLYGON);
    glVertex2f(xValue3+27-2,vehicle3+100);
    glVertex2f(xValue3+27-2,vehicle3+100-2);
    glVertex2f(xValue3+29+2,vehicle3+100-2);
    glVertex2f(xValue3+29+2,vehicle3+100);
    glEnd();

    glColor3f(1.00, 0.42, 0.42);
    glBegin(GL_POLYGON);
    glVertex2f(xValue3+27,vehicle3+100);
    glVertex2f(xValue3+27,vehicle3+100-7);
    glVertex2f(xValue3+28,vehicle3+100-9);
    glVertex2f(xValue3+29,vehicle3+100-7);
    glVertex2f(xValue3+29,vehicle3+100);
    glEnd();
    vehicle3--;
    if(vehicle3<-100){
        vehicle3=0;
        xValue3=xValue;
    }
    //KIll check car3
    if((abs(xValue-xValue3)<6) && (vehicle3+100<17)){
            start = 0;
            isGameOver=1;

    }
    }
  //glFlush();
  //PlaySound("game.wav", NULL, SND_FILENAME|SND_LOOP);
}

void MainMenu(){


        //background
        glColor3f(0.19, 0.19, 0.27);
        glBegin(GL_QUADS);
        glVertex2f(0,0);
        glVertex2f(100,0);
        glVertex2f(100,100);
        glVertex2f(0,100);
        glEnd();

        //Text Information in Frist Page
        if(isGameOver==1){
            glColor3f(1.000, 0.000, 0.000);
            renderBitmapString(38,72,(void *)font1,"GAME OVER");
            glColor3f(1.000, 0.000, 0.000);
            char buffer2 [50];
            sprintf (buffer2, "Your Score is : %d", score);
            renderBitmapString(38,68,(void *)font1,buffer2);

        }
////////////////////////////////////////////////////////////////////////////////////////
// 2D car racing game
       //box
        glColor3f(0.37, 0.70, 0.98);
        glBegin(GL_POLYGON);
        glVertex2f(25,80-3);
        glVertex2f(25,80+5);
        glVertex2f(75,80+5);
        glVertex2f(75,80-3);
        glEnd();
        //text
        glColor3f(1.00, 1.00, 1.00);
        renderBitmapString(35,80,(void *)font1,"2D Car Racing Game ");
////////////////////////////////////////////////////////////////////////////////////////

        //box
        glColor3f(0.99, 0.48, 0.53);
        glBegin(GL_POLYGON);
        glVertex2f(25,60-3);
        glVertex2f(25,60+5);
        glVertex2f(75,60+5);
        glVertex2f(75,60-3);
        glEnd();

        //Text
        glColor3f(1.00, 1.00, 1.00);
        renderBitmapString(35,60,(void *)font2,"Press S to START");

///////////////////////////////////////////////////////////////////////////////////////////
         //box
        glColor3f(0.10, 0.33, 0.36);
        glBegin(GL_POLYGON);
        glVertex2f(25,50-3);
        glVertex2f(25,50+5);
        glVertex2f(75,50+5);
        glVertex2f(75,50-3);
        glEnd();
        //Text
        glColor3f(1.00, 1.00, 1.00);
        renderBitmapString(35,50,(void *)font2,"Press ESC to Exit");

//////////////////////////////////////////////////////////////////////////////////////////
         //box
        glColor3f(0.99, 0.65, 0.38);
        glBegin(GL_POLYGON);
        glVertex2f(25,40-8);
        glVertex2f(25,40+5);
        glVertex2f(75,40+5);
        glVertex2f(75,40-8);
        glEnd();

        //text
        glColor3f(1.000, 1.000, 1.000);
        renderBitmapString(35,40,(void *)font3, " UP    ->  increase Speed");
        renderBitmapString(35,38,(void *)font3, "DWON   ->  decrease Speed");
        renderBitmapString(35,36,(void *)font3,"RIGHT  ->  Go Right");
        renderBitmapString(35,34,(void *)font3,"LEFT   ->  turn Left");


        glColor3f(1.000, 1.000, 1.000);
        renderBitmapString(5,5,(void *)font3,"This Project was Created By:");
        renderBitmapString(5,3,(void *)font3,"AHAD, ABDUL");
        renderBitmapString(5,1,(void *)font3,"ID:16-32236-2");



}



void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    if(start==1){
        glClearColor(0.01, 0.76, 0.60,1);
        PlayGame();
    }
    else{
        MainMenu();
    }
    glFlush();
    glutSwapBuffers();
}

void GamePlayKey(int key, int x, int y){
        switch (key) {
        case GLUT_KEY_DOWN:
            if(FramePerSecond>(50+(gameLevel*2)))
            FramePerSecond=FramePerSecond-2;
            break;
        case GLUT_KEY_UP:
            FramePerSecond=FramePerSecond+2;
            break;

        case GLUT_KEY_LEFT:
            if(xValue>=0){
                xValue = xValue - 1;
                if(xValue<0){
                    xValue=-1;
                }
            }
            break;


        case GLUT_KEY_RIGHT:
            if(xValue<=44){

                xValue = xValue + 1;
                if(xValue>44){
                    xValue = 45;
                }

            }
            break;

        default:
                break;
        }

}

void mainMenuKey(unsigned char key, int x, int y) {
      switch (key)
            {
                case 'S': // NO Break used , sO IF capital S press --> it will flow through small s condition and game will start
                case 's':

            if(start==0){
                start = 1;
                isGameOver = 0;
                Vehicle1 = 0; // y axis value of car 1 , coming against player
                xValue1=0;
                vehicle2 = +35;
                xValue2=0;
                vehicle3 = +70;
                xValue3=0;
                FramePerSecond = 40;
                score=0;
                gameLevel=0;
            }
             break;

             case 27:
                 exit(0);
             break;
             default:
                break;
        }
}

void timer(int){
    glutPostRedisplay();
    glutTimerFunc(1000/FramePerSecond,timer,0);
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(650,845);//window size
    glutInitWindowPosition(500,100); // game window will stay in the middle of the screen
    glutCreateWindow("2D Car Racing Game");

    glutDisplayFunc(display);
    glutSpecialFunc(GamePlayKey);
    glutKeyboardFunc(mainMenuKey );

    glOrtho(0,100,0,100,-1,1);
    //void gluOrtho2D(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top) (0,0)->(100,100)
    //redefining co-ordinates
    glClearColor(0.184, 0.310, 0.310,1);


    glutTimerFunc(1000,timer,0);
    glutMainLoop();

    return 0;
}
