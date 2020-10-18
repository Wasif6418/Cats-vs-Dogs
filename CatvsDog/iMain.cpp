#include "iGraphics.h"
#include <stdio.h>
#include "bitmap_loader.h"
//#include "stb_image.h"
#include <math.h>

int loadx=0;
int loady=72;
bool showMenu=false,loadMenu=true;
bool showPlay=false,showAbout=false,showInst=false,showOption=false,showResult=false,showGameOver=false;
bool startCan=false,startBone=false;
bool angleSetCat=true,angleSetDog=true;
bool player1=true,player2=false;
bool showNewGame=false,showResumeGame=false,show2ndMenu=false;
int k=2,l=2;
int menuBtnX=480;
int menuBtnY=500;
int velocityBarX1=25,velocityBarY1=100;
int velocityBarX2=1146,velocityBarY2=100;
int wind1=0,wind2=0;
int t=1;

double g=24.8/100;
double g2=24.8/100;

int v=15,vw=15,vAdd=0;
int th=0;
double theta=(th*3.1416)/180;
double theta2=(105*3.1416)/180;
double vx=v*cos(theta);
double vy=v*sin(theta);

double canX=142,canY=158;
double boneX=985,boneY=158;
int line=100;
int p=1,q=1;
double lineXcat=line*cos(theta),lineYcat=line*sin(theta);
double lineXdog=line*cos(theta),lineYdog=line*sin(theta);
int rotate_count =0;
int imageBone,imageCan,imageArrowDwn,imageGameOver,imageMenuIcon;

int dogLifeLength=411,dogLifeWidth=14;  //dogLifeLength=411
int dogLifeX=696,dogLifeY=637;

int catLifeLength=-411,catLifeWidth=14;
int catLifeX=501,catLifeY=636;
double windArrow1x[3]={654,668,654},windArrow1y[3]={600,606,612};
double windArrow2x[3]={540,526,540},windArrow2y[3]={600,606,612};

char winnerName[50];
int indexNumber=0;
int f=1,s=1;

void newGame()															///new game starting ! reseting all the values
{
	showMenu=true,loadMenu=false;
	showPlay=false,showAbout=false,showInst=false,showOption=false,showResult=false,showGameOver=false,show2ndMenu=false;
	startCan=false,startBone=false;
	player1=true,player2=false;
	showNewGame=false,showResumeGame=false;

	velocityBarX1=25,velocityBarY1=100;
	velocityBarX2=1146,velocityBarY2=100;
	wind1=0,wind2=0;
    t=1,s=1,f=1;

	v=15,vw=15,vAdd=0;
	canX=142,canY=158;
	boneX=985,boneY=158;
	rotate_count =0;

	dogLifeLength=411,dogLifeWidth=14;
	dogLifeX=696,dogLifeY=637;

	catLifeLength=-411,catLifeWidth=14;
	catLifeX=501,catLifeY=636;
}	
void saveName()
{
	FILE *result;

	result=fopen("results.txt","a");
	fprintf(result,"%s\n",winnerName);
	fclose(result);
}
void nameInput()
{
	iSetColor(255,255,255);
	iFilledRectangle(490,218,300,25);
	iSetColor(0,0,0);
	iText(500,180+40,"ENTER WINNER'S NAME:",GLUT_BITMAP_TIMES_ROMAN_24);
	iFilledRectangle(500,180,200,25);
	iSetColor(255,255,255);
	iText(510,185,winnerName,GLUT_BITMAP_TIMES_ROMAN_24);

}
void saveGame()
{
	int p1,p2;
	if(player1==true)
	{
		p1=1;
		p2=0;
	}
	else
	{
		p1=0;
		p2=1;
	}
	int ax[4]={catLifeLength,dogLifeLength,p1,p2};
	FILE *saveGm;
	saveGm=fopen("saveGame.txt","w");
	for(int s=0; s<4; s++)
	fprintf(saveGm,"%d\n",ax[s]);
	
	fclose(saveGm);
}
void gameOver()														/// game over condition! name input of the winner
{
	iShowImage(0,0,1198,700,imageGameOver);
	showPlay = false,showAbout=false,showInst=false,showOption=false,showMenu=false,showResult=false,player1=false,player2=false,show2ndMenu=false,showNewGame=false,showResumeGame=false;
	nameInput();
	//newGame();
}
void wind()																///wind bar for wind with respect to velocity vw=v
{
	iSetColor(0,0,0);
	iRectangle(528,568,68*2,15);										///outer box of the wind bar
	iSetColor(00,00,255);
	iLine(594,568,594,583);												//outer box middle point
	if(player1==true)
	{
		if(vw==14)
		iFilledRectangle(580,568,13.6,15);
		if(vw==13)
		iFilledRectangle(566,568,27,15);
		if(vw==12)
		iFilledRectangle(553,568,41,15);
		if(vw==11)
		iFilledRectangle(540,568,54,15);
		if(vw==10)
		iFilledRectangle(526,568,68,15);							//wind bar for player1
		if(vw==16)
		iFilledRectangle(594,568,13.6,15);
		if(vw==17)
		iFilledRectangle(594,568,27,15);
		if(vw==18)
		iFilledRectangle(594,568,41,15);
		if(vw==19)
		iFilledRectangle(594,568,54,15);
		if(vw==20)
		iFilledRectangle(594,568,68,15);
		if(vw>15)
		{
			iSetColor(0,0,230);
			iFilledPolygon(windArrow1x,windArrow1y,3);				//wind direction arrow
		}
		if(vw<15)
		{
			iSetColor(0,0,230);
			iFilledPolygon(windArrow2x,windArrow2y,3);
		}
	}
	if(player2==true)
	{
		if(vw==16)
		iFilledRectangle(580,568,13.6,15);
		if(vw==17)
		iFilledRectangle(566,568,27,15);
		if(vw==18)
		iFilledRectangle(553,568,41,15);
		if(vw==19)
		iFilledRectangle(540,568,54,15);
		if(vw==20)
		iFilledRectangle(526,568,68,15);
		if(vw==14)
		iFilledRectangle(594,568,13.6,15);						///wind bar for player 2
		if(vw==13)
		iFilledRectangle(594,568,27,15);
		if(vw==12)
		iFilledRectangle(594,568,41,15);
		if(vw==11)
		iFilledRectangle(594,568,54,15);
		if(vw==10)
		iFilledRectangle(594,568,68,15);
		if(vw<15)
		{
			iSetColor(0,0,230);
			iFilledPolygon(windArrow1x,windArrow1y,3);
		}
		if(vw>15)												//wind direction arrow
		{
			iSetColor(0,0,230);
			iFilledPolygon(windArrow2x,windArrow2y,3);
		}
	}


}
void showResults()
{
	FILE *result;
	char s[10][50];
	int p=0,ry=490,i;
	iSetColor(0,0,255);
	iText(500,ry+40,"List of Winners of last 10 games",GLUT_BITMAP_TIMES_ROMAN_24);
	result=fopen("results.txt","r");

	while(fscanf(result,"%s",&s[p])!=EOF)
	{
		p++;
		if(p==10)
			break;
	}
	
	for(i=0;i<p;i++)
	{	
		iSetColor(0,0,255);
		iText(500,ry,s[i],GLUT_BITMAP_TIMES_ROMAN_24);
		ry=ry-40;
	}
	fclose(result);

}
void velocityControl1()										//velocity bar with different colours for cat. Can throughing
{
	//iSetColor(0,0,255);
	//iFilledRectangle(25,100,20,115);
	iSetColor(255,0,0);
	iFilledRectangle(25,100,20,15);
	iSetColor(235,0,0);
	iFilledRectangle(25,115,20,10);
	iSetColor(215,0,0);
	iFilledRectangle(25,125,20,10);
	iSetColor(195,0,0);
	iFilledRectangle(25,135,20,10);
	iSetColor(175,0,0);
	iFilledRectangle(25,145,20,10);
	iSetColor(155,0,0);
	iFilledRectangle(25,155,20,10);
	iSetColor(135,0,0);
	iFilledRectangle(25,165,20,10);
	iSetColor(115,0,0);
	iFilledRectangle(25,175,20,10);
	iSetColor(95,0,0);
	iFilledRectangle(25,185,20,10);
	iSetColor(75,0,0);
	iFilledRectangle(25,195,20,10);
	iSetColor(65,0,0);
	iFilledRectangle(25,205,20,10);

	iSetColor(0,255,0);
	iLine(velocityBarX1,velocityBarY1,velocityBarX1+20,velocityBarY1);			//green line up down at velocity bar
}										
void velocityControl2()															//velocity bar with different colours for dog.Bone throughing									
{
	//iSetColor(0,0,255);
	//iFilledRectangle(25,100,20,115);
	iSetColor(255,0,0);
	iFilledRectangle(1146,100,20,15);
	iSetColor(235,0,0);
	iFilledRectangle(1146,115,20,10);
	iSetColor(215,0,0);
	iFilledRectangle(1146,125,20,10);
	iSetColor(195,0,0);
	iFilledRectangle(1146,135,20,10);
	iSetColor(175,0,0);
	iFilledRectangle(1146,145,20,10);
	iSetColor(155,0,0);
	iFilledRectangle(1146,155,20,10);
	iSetColor(135,0,0);
	iFilledRectangle(1146,165,20,10);
	iSetColor(115,0,0);
	iFilledRectangle(1146,175,20,10);
	iSetColor(95,0,0);
	iFilledRectangle(1146,185,20,10);
	iSetColor(75,0,0);
	iFilledRectangle(1146,195,20,10);
	iSetColor(65,0,0);
	iFilledRectangle(1146,205,20,10);

	iSetColor(0,255,0);
	iLine(velocityBarX2,velocityBarY2,velocityBarX2+20,velocityBarY2);			//green line up down at velocity bar for dog
}
void playGame()																//game starts
{
	wind();																	//calling wind function for viewing wind direction
	iSetColor(255,255,0);
	iFilledRectangle(696,637,410,14);										//dog life yellow bar
	iSetColor(230,0,0);
	iFilledRectangle(dogLifeX,dogLifeY,dogLifeLength,dogLifeWidth);			///dog life bar

	iSetColor(255,255,0);
	iFilledRectangle(501,636,-410,14);										//cat life yellow bar
	iSetColor(230,0,0);
	iFilledRectangle(catLifeX,catLifeY,catLifeLength,catLifeWidth);			///dcat life bar


	if(player1==true)
	{
		iShowImage(105,220,35,50,imageArrowDwn);							///active player arrow sign
		iLine(152,168,lineXcat+142,lineYcat+158);
		if(startCan)
	
		iRotate(canX+20,canY+10,(double) (5*rotate_count++));
		//printf("%lf %lf\n",BallX,BallY);
		//iFilledRectangle(BallX,BallY,40,20);
		
		iShowImage(canX,canY,40,40,imageCan);								///can_image
		iUnRotate();
		if(!angleSetCat)
		{
			velocityControl1();													///calling velocity control bar for cat
		}

	}
	if(player2==true)
	{
		iShowImage(1030,190,35,50,imageArrowDwn);							///active player arrow sign
		iLine(990,175,-lineXdog+985,lineYdog+158);
		if(startBone)
		iRotate(boneX+20,boneY+10,(double) (5*rotate_count++));
		//printf("%lf %lf\n",BallX,BallY);
		//iFilledRectangle(BallX,BallY,40,20);
		iShowImage(boneX,boneY,40,40,imageBone);							///bone_image
		iUnRotate();
		if(!angleSetDog)
		{
			velocityControl2();													///calling velocity control bar for dog
		}
	}

}
void resumeGame()
{
	int cx[4],p1,p2;
	if(f)
	{
	FILE *resumeGm;
	resumeGm=fopen("saveGame.txt","r");
	for(int i=0; i<4; i++)
		fscanf(resumeGm,"%d",&cx[i]);
	fclose(resumeGm);
	catLifeLength=cx[0];
	//catLifeY=cy;
	dogLifeLength=cx[1];
	if(cx[2]==1)
	{
		player1=true;
		player2=false;
	}
	else
	{
		player1=false;
		player2=true;
	}
	f=0;
	//dogLifeY=dy;
	}
	wind();																	//calling wind function for viewing wind direction
	iSetColor(255,255,0);
	iFilledRectangle(696,637,410,14);										//dog life yellow bar
	iSetColor(230,0,0);
	iFilledRectangle(dogLifeX,dogLifeY,dogLifeLength,dogLifeWidth);			///dog life bar

	iSetColor(255,255,0);
	iFilledRectangle(501,636,-410,14);										//cat life yellow bar
	iSetColor(230,0,0);
	iFilledRectangle(catLifeX,catLifeY,catLifeLength,catLifeWidth);			///dcat life bar


	if(player1==true)
	{
		iShowImage(105,220,35,50,imageArrowDwn);							///active player arrow sign
		iLine(152,168,lineXcat+142,lineYcat+158);
		if(startCan)
	
		iRotate(canX+20,canY+10,(double) (5*rotate_count++));
		//printf("%lf %lf\n",BallX,BallY);
		//iFilledRectangle(BallX,BallY,40,20);
		
		iShowImage(canX,canY,40,40,imageCan);								///can_image
		iUnRotate();
		if(!angleSetCat)
		{
			velocityControl1();													///calling velocity control bar for cat
		}

	}
	if(player2==true)
	{
		iShowImage(1030,190,35,50,imageArrowDwn);							///active player arrow sign
		iLine(990,175,-lineXdog+985,lineYdog+158);
		if(startBone)
		iRotate(boneX+20,boneY+10,(double) (5*rotate_count++));
		//printf("%lf %lf\n",BallX,BallY);
		//iFilledRectangle(BallX,BallY,40,20);
		iShowImage(boneX,boneY,40,40,imageBone);							///bone_image
		iUnRotate();
		if(!angleSetDog)
		{
			velocityControl2();													///calling velocity control bar for dog
		}
	}
}
void menu()																///menu background and buttons
{
	iShowBMP(0,0,"images//menubg.bmp");
	iShowBMP2(menuBtnX,menuBtnY,"images//playbtn.bmp",0);
	//iShowBMP2(menuBtnX,menuBtnY-100,"images//optionbtn.bmp",0);
	iShowBMP2(menuBtnX,menuBtnY-100,"images//resultbtn.bmp",0);
	iShowBMP2(menuBtnX,menuBtnY-200,"images//instbtn.bmp",0);
	iShowBMP2(menuBtnX,menuBtnY-300,"images//aboutbtn.bmp",0);
	iShowBMP2(menuBtnX,menuBtnY-400,"images//exitbtn.bmp",0);

}
void goToMenuOptions()													//going to any selected option
{
	if(showPlay==true)
	{
		if(show2ndMenu)
		{
		iShowBMP(0,0,"images//menubg.bmp");
		
		iShowBMP2(menuBtnX,menuBtnY-100,"images//newgmbtn.bmp",0);
		iShowBMP2(menuBtnX,menuBtnY-200,"images//loadgmbtn.bmp",0);
		iShowBMP2(10,550,"images//backbtn.bmp",0);
		}
		if(showNewGame && !show2ndMenu)
		{
			iSetColor(0,0,0);
			iShowBMP(0,0,"images//gamebg.bmp");
			iShowBMP2(20,625,"images//exiticon.bmp",0);
			iShowBMP2(1140,625,"images//savebtn.bmp",0);
			iShowImage(20,570,43,43,imageMenuIcon);
			if(s==1)
			{
				dogLifeLength=411,dogLifeWidth=14;
				dogLifeX=696,dogLifeY=637;
				catLifeLength=-411,catLifeWidth=14;
				catLifeX=501,catLifeY=636;
				player1=true,player2=false;
				s++;
			}
			playGame();													//game starting function calling

		}
		if(showResumeGame && !show2ndMenu)
		{
			iShowBMP(0,0,"images//gamebg.bmp");
			iShowBMP2(20,625,"images//exiticon.bmp",0);
			iShowBMP2(1140,625,"images//savebtn.bmp",0);
			iShowImage(20,570,43,43,imageMenuIcon);
			resumeGame();
			//playGame();	
		}

	}
/*	if(showOption==true)
	{
		iSetColor(255,200,255);
		iFilledRectangle(0,0,1200,700);
		iSetColor(0,0,0);
		iText(480,450,"Here is Optin. . . .");
		iShowBMP2(10,550,"images//backbtn.bmp",0);
	}*/
	if(showInst==true)
	{
		iShowBMP2(0,0,"images//instruction.bmp",0);
		iShowBMP2(10,550,"images//backbtn.bmp",0);
	}
	if(showAbout==true)
	{
		iShowBMP2(0,0,"images//about.bmp",0);
		iShowBMP2(10,550,"images//backbtn.bmp",0);
	
	}
	if(showResult==true)
	{
		iShowBMP2(0,0,"images//results.bmp",0);
		iShowBMP2(10,550,"images//backbtn.bmp",0);
		showResults();
	}
}

void iDraw()
{
	//place your drawing codes here
	iClear();
	
	if(showGameOver==true)							///checking game ove condition
	{
	 gameOver();									
	}
	if(showMenu == false && loadMenu==true)				//loading screen
	{
	
	iShowBMP(0,0,"images//menu1bg.bmp");
	iSetColor(0,0,0);
	iRectangle(470,72,280,30);
	iFilledRectangle(470,72,loadx,30);
	iText(550,50,"Loading . . .");
	}	
	if(showMenu == true && loadMenu==false )			///checking if game load is finished
	{
		menu();											///calling menu function for showing menu
	}
	goToMenuOptions();									//calling goToMenuOptions
	
	
}

void iMouseMove(int mx, int my)
{
	//printf("%d %d %d\n",mx,my);

	//place your codes here
}
void iMouse(int button, int state, int mx, int my)
{
	if(showMenu==true)													///when menu is true and other options are false
	{
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		{
				printf("x = %d, y= %d\n",mx,my);
			
					if(mx>=485 && mx<=735 && my>= menuBtnY && my<=560)										///for PLAY
					{
						showPlay = true,show2ndMenu=true;
						showAbout=false,showInst=false,showOption=false,showMenu=false,showResult=false;
					}
					/*if(mx>=485 && mx<=735 && my>= menuBtnY-100 && my<=560)
					{
						showOption=true;
						showInst=false,showPlay = false,showAbout=false,showMenu=false,showResult=false;
					}*/
					if(mx>=485 && mx<=735 && my>= menuBtnY-100 && my<=460)									///for RESULT
					{
						showResult=true;
						showInst=false,showPlay = false,showAbout=false,showMenu=false,showOption=false;
					}
					if(mx>=485 && mx<=735 && my>= menuBtnY-200 && my<=360)									///for INSTRUCTION
					{
						showInst = true;
						showAbout=false,showPlay=false,showOption=false,showMenu=false,showResult=false;
					}
					if(mx>=485 && mx<=735 && my>= menuBtnY-300 && my<=260)									///for ABOUT
					{
						showAbout = true;
						showPlay=false,showInst=false,showOption=false,showMenu=false,showResult=false;
					}
					if(mx>=485 && mx<=735 && my>= menuBtnY-400 && my<=160)									///forEXIT
					{
						exit(0);
					}

		}
	}
	if(showMenu==false && (showAbout==true || showInst== true || showOption== true || showResult==true))		///for BACK BUTTON
	{
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		{
			printf("x = %d, y= %d\n",mx,my);
			if(mx>=12 && mx<=128 && my>= 610 && my<=645)
			{
				showMenu=true;
				showPlay = false,showAbout=false,showInst=false,showOption=false,showResult=false;
			}
		}
	}
	
	if(showPlay==true && show2ndMenu==false)								
	{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		{
			printf("x = %d, y= %d\n",mx,my);
			if(mx>=23 && mx<=60 && my>=633 && my<=666)					//for exit icon during gameplay
			{
				exit(0);
			}
			if(mx>=1140 && mx<=1187 && my>=628 && my<=670)				//for save icon during gameplay
			{
				saveGame();
			}
			if(mx>=20 && mx<=63 && my>=570 && my<=613)						//for menu icon during gameplay
			{
				showMenu=true;
				showPlay = false,showAbout=false,showInst=false,showOption=false,showResult=false,show2ndMenu=false,showNewGame=false,showResumeGame=false;
				s=1,f=1;
			}

		}
	}
	if(showMenu==false && showPlay==true && show2ndMenu==true)								
	{
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		{
				if(mx>=485 && mx<=735 && my>= menuBtnY-100 && my<=460)									
				{
					showNewGame=true,show2ndMenu=false;
					showResult=false;
					showInst=false,showAbout=false,showMenu=false,showOption=false;
				}
				if(mx>=485 && mx<=735 && my>= menuBtnY-200 && my<=360)								
				{
					showResumeGame=true,show2ndMenu=false;
					showResult=false;
					showInst=false,showAbout=false,showMenu=false,showOption=false;
				}
				if(mx>=12 && mx<=128 && my>= 610 && my<=645)
				{
					showMenu=true;
					showPlay = false,showAbout=false,showInst=false,showOption=false,showResult=false,show2ndMenu=false;
				}

			}
	}

	if(player1==true)								///throwing can for player 1
	{	
		if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
		{	
			if(!angleSetCat)
	 			startCan=true;
			else
				angleSetCat=false;
		}
	}
	if(player2==true)								///throwing bone for player 2
	{	
		if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
		{	
			if(!angleSetDog)
	 			startBone=true;
			else
				angleSetDog=false;
		}
	}


}
 void iKeyboard(unsigned char key)
{

	if(show2ndMenu==false && showPlay==true)
	{
			if(key == 's')
			saveGame();
	}
	if(showMenu==false && showGameOver==true && showPlay==false)
	{
		if (key == '\r')
		{
			saveName();
			newGame();
			f=1;
		}
	}
	if(showMenu==false && (showAbout==true || showInst== true || showOption== true || showResult==true))
	{
		if (key == '\b')
		{
				showMenu=true;
				showPlay = false,showAbout=false,showInst=false,showOption=false,showResult=false,show2ndMenu=false;
		}
	}
	if(showMenu==false && showPlay==true && show2ndMenu==true)
	{
		if (key == '\b')
		{
				showMenu=true;
				showPlay = false,showAbout=false,showInst=false,showOption=false,showResult=false,show2ndMenu=false;
		}
	}
	if(player1==true)
	{
		if(!angleSetCat)
		{
			if (key == ' ')
			{
				startCan=true;
			}
		}
		else
		{
			if (key == ' ')
			angleSetCat=false;
		}
	}

	if(player2==true)
	{
		if(!angleSetDog)
		{
			if (key == ' ')
			{
				startBone=true;
			}
		}
		else
		{
			if (key == ' ')
			angleSetDog=false;
		}
	}

	if(showGameOver==true)
	{
		if(key != '\b')
		{
			winnerName[indexNumber]=key;
			winnerName[indexNumber+1]='\0';
			indexNumber++;
		}
		else
		{
			indexNumber--;
			winnerName[indexNumber]='\0';
		}
	}


}
void iSpecialKeyboard(unsigned char key)
{

	if (key == GLUT_KEY_END)	//exit from game at any time
	{
		exit(0);
	}

}

void menuLoad()				///menu loading function!
{
	if(loadx<280)
	loadx+=5;
	if(loadx==280)
	{
		showMenu = true;
		loadMenu =false;
		iPauseTimer(0);
	}
}

void canMove()						//can moving function
{
	if(startCan)
	{
		vx=v*cos(theta);
		vy=v*sin(theta);
		canX=142+(vx*t);							//position of can
		canY=158+(vy*t-(0.5*g*t*t));
		t++;

		if(canX+20>=1200 || canY+10>=1400 || canY+10<=40)                        ////boundary
		{
			canX=142;
			canY=158;
			startCan=false;
			rotate_count = 0;
			t=1;
			wind1=rand()%5;
			wind2=rand()%5;

			v=15+wind1-wind2;
			vw=15+wind1-wind2;
			iResumeTimer(2);
			velocityBarX1=25,velocityBarY1=100;								//green bar up and down
			player1=false,player2=true,angleSetCat=true;
			th=0;
		}
		if(canX+20<=1030 && canX+20>=990 && canY+10<=170 && canY+10>=50)  ////Dog front
		{
			canX=142;
			canY=158;
			startCan=false;
			rotate_count = 0;
			t=1;th=0;
			wind1=rand()%5;
			wind2=rand()%5;
		
			v=15+wind1-wind2;
			vw=15+wind1-wind2;
			iResumeTimer(2);
			velocityBarX1=25,velocityBarY1=100;
			if(dogLifeLength>0)
			{
				dogLifeLength=dogLifeLength-20;
				if(dogLifeLength<0)
				{
					dogLifeLength=0;
					showGameOver=true;
				}
			}
			player1=false,player2=true,angleSetCat=true;

		}
		if(canX+20<=1087 && canX+20>=1023 && canY+10<=170 && canY+10>=50)   ////Dog Head
		{
			canX=142;
			canY=158;
			startCan=false;
			rotate_count = 0;
			t=1;th=0;
			wind1=rand()%5;
			wind2=rand()%5;
		
			v=15+wind1-wind2;
			vw=15+wind1-wind2;
			iResumeTimer(2);
			velocityBarX1=25,velocityBarY1=100;
			if(dogLifeLength>0)
			{
				dogLifeLength=dogLifeLength-40;
				if(dogLifeLength<0)
				{
					dogLifeLength=0;
					showGameOver=true;
				}
			}
			player1=false,player2=true,angleSetCat=true;

		}

		if(canX+20>=568 && canX+20<=630 && canY+10<=288)   ///wall
		{
			canX=142;
			canY=158;
			startCan=false;
			rotate_count = 0;
			t=1;th=0;
			wind1=rand()%5;
			wind2=rand()%5;
	
			v=15+wind1-wind2;
			vw=15+wind1-wind2;
			iResumeTimer(2);
			velocityBarX1=25,velocityBarY1=100;
			player1=false,player2=true,angleSetCat=true;
		}
	}

}
void boneMove()
{
	if(startBone)
	{
		vx=v*cos(theta);
		vy=v*sin(theta);
		boneX=985-(vx*t);									///bone position
		boneY=158+(vy*t-(0.5*g*t*t));
		t++;

		if(boneX+20<=0 || boneY+10>=1400 || boneY+10<=40)                        ////boundary
		{
			boneX=985;
			boneY=158;
			startBone=false;
			rotate_count = 0;
			t=1;th=0;
			wind1=rand()%5;
			wind2=rand()%5;

			v=15+wind1-wind2;
			vw=15+wind1-wind2;
			iResumeTimer(4);
			velocityBarX2=1146,velocityBarY2=100;
			player1=true,player2=false,angleSetDog=true;
		}
		if(boneX+20<=148 && boneX+20>=90 && boneY+10<=210 && boneY+10>=180)   ////cat Head
		{
			boneX=985;
			boneY=158;
			startBone=false;
			rotate_count = 0;
			t=1;th=0;
			wind1=rand()%5;
			wind2=rand()%5;
		
			v=15+wind1-wind2;
			vw=15+wind1-wind2;
			iResumeTimer(4);
			velocityBarX2=1146,velocityBarY2=100;
			if(catLifeLength<0)
			{
				catLifeLength=catLifeLength+40;
				if(catLifeLength>0)
				{
					catLifeLength=0;
					showGameOver=true;
				}
			}
			player1=true,player2=false,angleSetDog=true;

		}
		if(boneX+20<=175 && boneX+20>=128 && boneY+10<=207 && boneY+10>=110)  ////Cat front
		{
			boneX=985;
			boneY=158;
			startBone=false;
			rotate_count = 0;
			t=1;th=0;
			wind1=rand()%5;
			wind2=rand()%5;
		
			v=15+wind1-wind2;
			vw=15+wind1-wind2;
			iResumeTimer(4);
			velocityBarX2=1146,velocityBarY2=100;
			if(catLifeLength<0)
			{
				catLifeLength=catLifeLength+20;
				if(catLifeLength>0)
				{
					catLifeLength=0;
					showGameOver=true;
				}
			}
			player1=true,player2=false,angleSetDog=true;

		}
		if(boneX+20>=568 && boneX+20<=630 && boneY+10<=288)   ///wall
		{
			boneX=985;
			boneY=158;
			startBone=false;
			rotate_count = 0;
			t=1;th=0;
			wind1=rand()%5;
			wind2=rand()%5;
	
			v=15+wind1-wind2;
			vw=15+wind1-wind2;
			iResumeTimer(4);
			velocityBarX2=1146,velocityBarY2=100;
			player1=true,player2=false,angleSetDog=true;
		}
	}

}
void VelocityBar1()								///in this function green line goes up and down and after pressing space the final velocity is set for cat
{
	velocityBarY1=velocityBarY1+k;
	if(velocityBarY1>=212)
	{
		k=-2;
	}
	if(velocityBarY1<=100)
	{
		k=2;
	}
	if(startCan)
	{
		iPauseTimer(2);
		if(velocityBarY1>=100 && velocityBarY1<=115)
		{
			v=v-5;
		}if(velocityBarY1>=116 && velocityBarY1<=125)
		{
			v=v-4;
		}if(velocityBarY1>=126 && velocityBarY1<=135)
		{
			v=v-3;
		}if(velocityBarY1>=136 && velocityBarY1<=145)
		{
			v=v-2;
		}if(velocityBarY1>=146 && velocityBarY1<=155)
		{
			v=v-1;
		}if(velocityBarY1>=156 && velocityBarY1<=165)
		{
			v=v-0;
		}if(velocityBarY1>=166 && velocityBarY1<=175)
		{
			v=v+1;
		}if(velocityBarY1>=176 && velocityBarY1<=185)
		{
			v=v+2;
		}if(velocityBarY1>=186 && velocityBarY1<=195)
		{
			v=v+3;
		}if(velocityBarY1>=196 && velocityBarY1<=205)
		{
			v=v+4;
		}if(velocityBarY1>=206 && velocityBarY1<=215)
		{
			v=v+5;
		}
	}

}
void VelocityBar2()											///in this function green line goes up and down and after pressing space the final velocity is set for dog									
{
	velocityBarY2=velocityBarY2+l;
	if(velocityBarY2>=212)
	{
		l=-2;
	}
	if(velocityBarY2<=100)
	{
		l=2;
	}
	if(startBone)
	{
		iPauseTimer(4);
		if(velocityBarY2>=100 && velocityBarY2<=115)
		{
			v=v-5;
		}if(velocityBarY2>=116 && velocityBarY2<=125)
		{
			v=v-4;
		}if(velocityBarY2>=126 && velocityBarY2<=135)
		{
			v=v-3;
		}if(velocityBarY2>=136 && velocityBarY2<=145)
		{
			v=v-2;
		}if(velocityBarY2>=146 && velocityBarY2<=155)
		{
			v=v-1;
		}if(velocityBarY2>=156 && velocityBarY2<=165)
		{
			v=v-0;
		}if(velocityBarY2>=166 && velocityBarY2<=175)
		{
			v=v+1;
		}if(velocityBarY2>=176 && velocityBarY2<=185)
		{
			v=v+2;
		}if(velocityBarY2>=186 && velocityBarY2<=195)
		{
			v=v+3;
		}if(velocityBarY2>=196 && velocityBarY2<=205)
		{
			v=v+4;
		}if(velocityBarY2>=206 && velocityBarY2<=215)
		{
			v=v+5;
		}
	}

}

void thetaChange()
{
	if(player1)
	{

		if(angleSetCat)
		{
			th=th+p;
			theta=(th*3.1416)/180;
			lineXcat=line*cos(theta);
			lineYcat=line*sin(theta);

			if(th>=90)
			{
				p=-1;
			}
			if(th<=0)
			{
				p=1;
			}
		}
	}
	if(player2)
	{
		if(angleSetDog)
		{
			th=th+q;
			theta=(th*3.1416)/180;
			lineXdog=line*cos(theta);
			lineYdog=line*sin(theta);

			if(th>=90)
			{
				q=-1;
			}
			if(th<=0)
			{
				q=1;
			}
		}
	}
}
int main()
{
		
	iSetTimer(100,menuLoad);				//timer 0
	iSetTimer(1,canMove);					//timer 1
	iSetTimer(10,VelocityBar1);				//timer 2
	iSetTimer(1,boneMove);					//timer 3
	iSetTimer(10,VelocityBar2);				//timer 4
	iSetTimer(10,thetaChange);	
	iInitialize(1198, 700, "demo");

	imageCan = iLoadImage("images\\can.png");
	imageBone = iLoadImage("images\\bone.png");
	imageArrowDwn = iLoadImage("images\\arrowdown.png");
	imageGameOver = iLoadImage("images\\gameover.png");
	imageMenuIcon = iLoadImage("images\\menuicon.png");
	iStart();

	return 0;
}