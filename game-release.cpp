//============================================================================
// Name        : Tetris.cpp
// Author      : Akash Harijan
// Description : Basic 2D game of Tetris...
//============================================================================


#ifndef TETRIS_CPP_
#define TETRIS_CPP_
#include "util.h"
#include <iostream>
#include<string>
#include<cmath> // for basic math functions such as cos, sin, sqrt

using namespace std;

#define SPACEBAR 32 // for including space bar
				
class Square	// for manipulating the tiles or cells 
{
	private:
		int x;
		int y;
		int color;
	public :
		Square(int x_=0, int y_=0){
			x=x_;
			y=y_;
		}
		int getX_S()const {
			return x;
		}
		int getY_S()const {
			return y;
		}
		void setX_S(int a){
			x=a;
		}
		void setY_S(int a){
			y=a;
		}
		void setColor(int a){
			color=a;
		}
		int getColor(){
			return color;
		}	
		~Square(){
		}
};		

class Shape    // Abstract class of Shape
{
		
		
	public:		
		int angle;
		Square * piece;
	
	public :
		Shape (int x=100, int y=800)				
		{
			
			piece=new Square [4];
			piece[0].setX_S(x);
			piece[0].setY_S(y);
			//piece[0].setColor("GREEN");
		}
	
		virtual void  draw(int x, int y)=0;   // pure virtual functions
		//virtual int getColor()=0;


		void setAngle(){           // for setting the angle in the range
			angle%=360;
		}


		bool check(int x){        // for checking the x_axis
			for (int i=0;i<4;i++)
				if ( piece[i].getX_S()+x<100 || piece[i].getX_S()+x>500)
					return false;
			return true;
		}
		
		bool checkY(int y){      // for checking the y_axis
			for ( int i=0;i<4;i++)
				if ( piece[i].getY_S()-y<=150 )
					return false;
			return true;
		} 
				
		virtual void Move(int x){  // virtual function for keys movement in x_axis
			if ( check(x)==true )
			{
				for (int i=0;i<4 ;i++){
				piece[i].setX_S(piece[i].getX_S()+x);
				
				}								
			}
		}

		virtual void MoveY(int y){   // virtual function for key move downward
			if ( checkY(y) ){
			
				for ( int i=0;i<4 ;i++){
				piece[i].setY_S(piece[i].getY_S()+y);
				}
			}
		}
			
};

class Straight : public Shape   // first shape straight line
{
	
	public :
		Straight(int x=300, int y=800)    // here x=300 only for using straight withour parameter
		:	Shape(x,y)
		{
			InitRandomizer();
			x=GetRandInRange(150,500);
			angle=0;
		}
		/*virtual int getColor(){
			return 5;
		}*/
		virtual void draw(int x, int y){    // for draw and rotate of piece
			setAngle();
			for ( int i=0;i<4;i++){
				if ( angle ==0 || angle ==180 ){
					if ( x+150<=500 && x+105>=100){
						for (int i=0;i<4;i++){
							
							DrawSquare(x+i*50,y,50,colors[5]);
							piece[i].setX_S(x+i*50);
							piece[i].setY_S(y);
							piece[i].setColor(5);		
						}
					}
					else{
						if (angle>0)
							angle=angle-90;
						else
							angle=270;
					}	
				}
				else if (angle ==90 || angle ==270){
					if ( y+150>100){
						for (int i=0;i<4;i++){
							DrawSquare ( x, y+i*50 ,50,colors[5]);
							piece[i].setX_S(x);
							piece[i].setY_S(y+i*50);
							piece[i].setColor(5);
						}
					}
					else{
						angle-=90;
					}	
				}
			
			}
		}
		

};
class Box: public Shape   // second shape a square box
{
	public :
		Box(int x=300, int y=800)
			:	Shape(x,y)
		{
			InitRandomizer();
			x=GetRandInRange(150,500);
			angle=0;
		}
		/*virtual int getColor(){
			return 76;
		}*/
		virtual void draw(int x, int y){   // for the draw and rotate of the piece
			setAngle();
			DrawSquare ( x,y,50 ,colors[76]);
			piece[0].setX_S(x);
			piece[0].setY_S(y);
			piece[0].setColor(76);
			x+=50;
			DrawSquare ( x,y,50 ,colors[76]);
			piece[1].setX_S(x);
			piece[1].setY_S(y);
			piece[1].setColor(76);
			y-=50;
			x-=50;
			DrawSquare ( x,y,50 ,colors[76]);
			piece[2].setX_S(x);
			piece[2].setY_S(y);
			piece[2].setColor(76);
			x+=50;
			DrawSquare ( x,y,50 ,colors[76]);
			piece[3].setX_S(x);
			piece[3].setY_S(y);
			piece[3].setColor(76);
			
		}
};

class  TShape : public Shape  // third shape  a T type shape
{
	public :
		TShape ( int x=300, int y=800)
		: Shape(x,y)
		{
			InitRandomizer();
			x=GetRandInRange(150,500);				
			angle=0;
		}
		/*virtual int getColor(){
			return 15;
		}*/
		virtual void draw(int x,int y){   // for the draw and rotate of the piece
			setAngle();
			
			if ( !check(0) || !check(0)  || !checkY(-100) ){
				if (angle==0)
					angle=270;
				else
					angle-=90;

			}
			if ( angle==0){
					DrawSquare ( x, y, 50 , colors[15]);
					piece[0].setX_S(x);
					piece[0].setY_S(y);
					piece[0].setColor(15);
					
					x-=50;
					y-=50;
	
					DrawSquare ( x, y, 50, colors[15]);
					piece[1].setX_S(x);
					piece[1].setY_S(y);
					piece[1].setColor(15);
					x+=50;
			
					DrawSquare ( x,y,50,colors[15]);
					piece[2].setX_S(x);
					piece[2].setY_S(y);
					piece[2].setColor(15);
					x+=50;
					
					DrawSquare ( x, y, 50 , colors[15]);
					piece[3].setX_S(x);
					piece[3].setY_S(y);
					piece[3].setColor(15);
							
			
			}
			else if ( angle ==90){

					DrawSquare ( x, y, 50, colors[15]);
					piece[0].setX_S(x);
					piece[0].setY_S(y);
					piece[0].setColor(15);
					x-=50;y-=50;
					DrawSquare ( x, y, 50, colors[15]);
					piece[1].setX_S(x);
					piece[1].setY_S(y);		
					piece[1].setColor(15);
		
					x+=50;
					DrawSquare ( x, y, 50, colors[15]);
					piece[2].setX_S(x);
					piece[2].setY_S(y);
					piece[2].setColor(15);				
					y-=50;
					DrawSquare ( x, y, 50, colors[15]);
					piece[3].setX_S(x);
					piece[3].setY_S(y);				
					piece[3].setColor(15);
			}
			else if ( angle == 180){

					DrawSquare ( x, y, 50, colors[15]);
					piece[0].setX_S(x);
					piece[0].setY_S(y);
					piece[0].setColor(15);				
					x+=50;
					DrawSquare ( x, y, 50, colors[15]);
					piece[1].setX_S(x);
					piece[1].setY_S(y);		
					piece[1].setColor(15);		
					x+=50;
					DrawSquare ( x, y, 50, colors[15]);
					piece[2].setX_S(x);
					piece[2].setY_S(y);		
					piece[2].setColor(15);		
					x-=50;
					y-=50;
					DrawSquare ( x, y, 50, colors[15]);
					piece[3].setX_S(x);
					piece[3].setY_S(y);
					piece[3].setColor(15);
				
			}
			
			else if ( angle==270){
					DrawSquare ( x, y, 50, colors[15]);
					piece[0].setX_S(x);
					piece[0].setY_S(y);
					piece[0].setColor(15);
					y-=50;
					DrawSquare ( x, y, 50, colors[15]);
					piece[1].setX_S(x);
					piece[1].setY_S(y);		
					piece[1].setColor(15);		
					x+=50;
					DrawSquare ( x, y, 50, colors[15]);
					piece[2].setX_S(x);
					piece[2].setY_S(y);		
					piece[2].setColor(15);		
					x-=50;y-=50;
					DrawSquare ( x, y, 50, colors[15]);
					piece[3].setX_S(x);
					piece[3].setY_S(y);
					piece[3].setColor(15);
			}
		}
					
};

class RShape : public Shape // fourth shape right  L shaped
{

	public :
		RShape (int x=300, int y=800)
		:Shape(x,y)
		{
			InitRandomizer();
			x=GetRandInRange(150,500);
			angle=0;
		}
		/*virtual int getColor(){
			return 22;
		}*/
		virtual void draw(int x,int y){   // for the draw and rotate of the piece
			setAngle();
			if ( !check(0) || !check(0)  || !checkY(-100) ){
				if (angle==0)
					angle=270;
				else
					angle-=90;

			}
			if (angle==0){
				DrawSquare ( x, y,50, colors[22]);
				piece[0].setX_S(x);
				piece[0].setY_S(y);		
				piece[0].setColor(22);		
				x+=50;
				DrawSquare ( x,y,50, colors[22]);
				piece[1].setX_S(x);
				piece[1].setY_S(y);		
				piece[1].setColor(22);		
				x-=50;
				y-=50;
				DrawSquare ( x,y,50,colors[22]);
				piece[2].setX_S(x);
				piece[2].setY_S(y);		
				piece[2].setColor(22);		
				y-=50;
				DrawSquare ( x, y, 50, colors[22]);
				piece[3].setX_S(x);
				piece[3].setY_S(y);		
				piece[3].setColor(22);		
				
			}
			else if ( angle==90){
				DrawSquare ( x, y, 50 , colors[22]);
				piece[0].setX_S(x);
				piece[0].setY_S(y);		
				piece[0].setColor(22);		
				y-=50;
				DrawSquare ( x, y, 50 , colors[22]);
				piece[1].setX_S(x);
				piece[1].setY_S(y);		
				piece[1].setColor(22);		
				x+=50;
				DrawSquare ( x, y, 50 , colors[22]);
				piece[2].setX_S(x);
				piece[2].setY_S(y);
				piece[2].setColor(22);
				x+=50;
				DrawSquare ( x, y, 50 , colors[22]);
				piece[3].setX_S(x);
				piece[3].setY_S(y);		
				piece[3].setColor(22);		
				
		

				
			}
			else if ( angle==180){

				DrawSquare ( x,y,50,colors[22]);
				piece[0].setX_S(x);
				piece[0].setY_S(y);
				piece[0].setColor(22);
				y-=50;
				DrawSquare ( x, y, 50 , colors[22]);
				piece[1].setX_S(x);
				piece[1].setY_S(y);
				piece[1].setColor(22);
				y-=50;x-=50;
				DrawSquare ( x, y, 50 , colors[22]);
				piece[2].setX_S(x);
				piece[2].setY_S(y);
				piece[2].setColor(22);
				x+=50;
				DrawSquare ( x, y, 50 , colors[22]);
				piece[3].setX_S(x);
				piece[3].setY_S(y);
				piece[3].setColor(22);

			}
			else if ( angle==270){
	
				DrawSquare ( x,y,50,colors[22]);
				piece[0].setX_S(x);
				piece[0].setY_S(y);		
				piece[0].setColor(22);		
				x+=50;
				DrawSquare ( x, y, 50 , colors[22]);
				piece[1].setX_S(x);
				piece[1].setY_S(y);		
				piece[1].setColor(22);		
				x+=50;
				DrawSquare ( x, y, 50 , colors[22]);
				piece[2].setX_S(x);
				piece[2].setY_S(y);
				piece[2].setColor(22);				
				x-=100;
				y-=50;
				DrawSquare ( x, y, 50 , colors[22]);
				piece[3].setX_S(x);
				piece[3].setY_S(y);
				piece[3].setColor(22);		
			}
		}


};

class LShape : public Shape // fifth shape left L shaped 
{
	public :
		LShape(int x=300,int y=800)
			: Shape(x,y)
		{
			InitRandomizer();
			x=GetRandInRange(150,500);			
			angle=0;
		}
		/*virtual int getColor(){
			return 30;
		}*/
		virtual void draw(int x,int y){ // for the draw and rotate of the piece
			setAngle();
			if ( !check(0) || !check(0)  || !checkY(-100) ){
				if (angle==0)
					angle=270;
				else
					angle-=90;

			}
			if ( angle==0){
				DrawSquare ( x, y, 50 , colors[30]);
				piece[0].setX_S(x);
				piece[0].setY_S(y);		
				piece[0].setColor(30);		
				x+=50;
				DrawSquare ( x, y, 50 , colors[30]);
				piece[1].setX_S(x);
				piece[1].setY_S(y);		
				piece[1].setColor(30);		
				y-=50;
				DrawSquare ( x, y, 50 , colors[30]);
				piece[2].setX_S(x);
				piece[2].setY_S(y);		
				piece[2].setColor(30);		
				y-=50;
				DrawSquare ( x, y, 50 , colors[30]);
				piece[3].setX_S(x);
				piece[3].setY_S(y);
				piece[3].setColor(30);
				
			}
			else if ( angle == 90 ){
				DrawSquare ( x, y, 50 , colors[30]);
				piece[0].setX_S(x);
				piece[0].setY_S(y);
				piece[0].setColor(30);
				x+=50;
				DrawSquare ( x, y, 50 , colors[30]);
				piece[1].setX_S(x);
				piece[1].setY_S(y);
				piece[1].setColor(30);
				x+=50;
				DrawSquare ( x, y, 50 , colors[30]);
				piece[2].setX_S(x);
				piece[2].setY_S(y);
				piece[2].setColor(30);
				y-=50;
				x-=100;
				DrawSquare ( x, y, 50 , colors[30]);
				piece[3].setX_S(x);
				piece[3].setY_S(y);
				piece[3].setColor(30);
			}
			else if ( angle == 180 ){
				DrawSquare ( x ,y ,50, colors[30]);
				piece[0].setX_S(x);
				piece[0].setY_S(y);
				piece[0].setColor(30);
				y-=50;
				DrawSquare ( x, y, 50 , colors[30]);
				piece[1].setX_S(x);
				piece[1].setY_S(y);
				piece[1].setColor(30);
				y-=50;
				DrawSquare ( x, y, 50 , colors[30]);
				piece[2].setX_S(x);
				piece[2].setY_S(y);
				piece[2].setColor(30);
				x+=50;
				DrawSquare ( x, y, 50 , colors[30]);
				piece[3].setX_S(x);
				piece[3].setY_S(y);				
				piece[3].setColor(30);
			}
			else if ( angle ==270 ){
				DrawSquare ( x,y, 50, colors[30]);
				piece[0].setX_S(x);
				piece[0].setY_S(y);
				piece[0].setColor(30);
				x-=100;
				y-=50;
				DrawSquare ( x, y, 50 , colors[30]);
				piece[1].setX_S(x);
				piece[1].setY_S(y);
				piece[1].setColor(30);
				x+=50;
				DrawSquare ( x, y, 50 , colors[30]);
				piece[2].setX_S(x);
				piece[2].setY_S(y);
				piece[2].setColor(30);
				x+=50;	
				DrawSquare ( x, y, 50 , colors[30]);								
				piece[3].setX_S(x);
				piece[3].setY_S(y);
				piece[3].setColor(30);
			}	
		}


};

class RStep : public Shape // sixth shape of right step
{
	public :
		RStep(int x=300, int y=800)
			:Shape(x,y)
		{
			InitRandomizer();
			x=GetRandInRange(150,500);			
			angle=0;
		}
		/*virtual int getColor(){
			return 61;
		}*/
		virtual void draw(int x,int y){  // for the draw and rotate of the piece
			setAngle();
			if ( !check(0) || !check(0)  || !checkY(-100) ){
				if (angle==0)
					angle=270;
				else
					angle-=90;

			}
			if ( angle==0 || angle==180){
				
				
				DrawSquare(x,y,50,colors[61]);
				piece[0].setX_S(x);
				piece[0].setY_S(y);
				piece[0].setColor(61);
				y-=50;
				DrawSquare ( x,y,50,colors[61]);
				piece[1].setX_S(x);
				piece[1].setY_S(y);
				piece[1].setColor(61);
				x+=50;
				DrawSquare ( x,y,50,colors[61]);
				piece[2].setX_S(x);
				piece[2].setY_S(y);		
				piece[2].setColor(61);		
				y-=50;
				DrawSquare (x,y,50, colors[61]);			
				piece[3].setX_S(x);
				piece[3].setY_S(y);
				piece[3].setColor(61);
				
			}
			else if ( angle == 90 || angle == 270){
								
				DrawSquare (x,y,50,colors[61]);
				piece[0].setX_S(x);
				piece[0].setY_S(y);
				piece[0].setColor(61);
				x+=50;
				DrawSquare ( x, y,50, colors[61]);
				piece[1].setX_S(x);
				piece[1].setY_S(y);		
				piece[1].setColor(61);		
				y-=50;
				x-=100;
				DrawSquare ( x,y, 50, colors[61]);
				piece[2].setX_S(x);
				piece[2].setY_S(y);		
				piece[2].setColor(61);		
				x+=50;
				DrawSquare ( x, y, 50 , colors[61]);
				piece[3].setX_S(x);
				piece[3].setY_S(y);
				piece[3].setColor(61);
			}			
		}	
	
};

class LStep : public Shape  // seventh shape right side R shaped
{
	public :
	LStep (int x=300, int y=800)
		: Shape ( x,y )
	{
		InitRandomizer();
		x=GetRandInRange(150,500);		
		angle=0;
	}
	/*virtual int getColor(){
		return 65;
	}*/
	virtual void draw (int x, int y){ // for the draw and rotate of the piece
		setAngle();
		if ( !check(0) || !check(0)  || !checkY(-100) ){
				if (angle==0)
					angle=270;
				else
					angle-=90;

			}
		if ( angle==0 || angle == 180)
		{
			DrawSquare ( x, y, 50, colors[65]);
			piece[0].setX_S(x);
			piece[0].setY_S(y);
			piece[0].setColor(65);
			x-=50;
			y-=50;
			DrawSquare ( x, y, 50, colors[65]);
			piece[1].setX_S(x);
			piece[1].setY_S(y);
			piece[1].setColor(65);
			x+=50;
			DrawSquare ( x, y, 50, colors[65]);
			piece[2].setX_S(x);
			piece[2].setY_S(y);
			piece[2].setColor(65);
			y-=50;
			x-=50;
			DrawSquare ( x,y, 50 , colors[65]);
			piece[3].setX_S(x);
			piece[3].setY_S(y);
			piece[3].setColor(65);
			
		}	
		else if ( angle == 90 || angle ==270 ){
			
			DrawSquare ( x, y, 50 , colors[65]);
			piece[0].setX_S(x);
			piece[0].setY_S(y);
			piece[0].setColor(65);
			x+=50;
			DrawSquare ( x, y, 50, colors [65]);
			piece[1].setX_S(x);
			piece[1].setY_S(y);
			piece[1].setColor(65);
			y-=50;
			DrawSquare ( x, y, 50, colors[65]);
			piece[2].setX_S(x);
			piece[2].setY_S(y);
			piece[2].setColor(65);
			x+=50;
			DrawSquare ( x, y, 50 , colors[65]);
			piece[3].setX_S(x);
			piece[3].setY_S(y);		
			piece[3].setColor(65);
	
		}		
	}



};
class Game //Game Class for manipulation of whole game
{
	public :
		
		bool pause; // for the action of pause in game
		bool space; // for the action space in game
		int index; // for accessing the index in the game
		int speed; // for speed of the pieces
		string score; // for the showing of the score
		Shape ** boxArray; // for manipulating different shapes
		Square visible[12][16]; // for saving the address of the board
		int time;  // for increasing the speed of pieces as time passes



	public :


	
		Game(){	
		
							// constructor of Game
			boxArray=new Shape * [7];
			setIndex();
			speed=0;
			space=0;
			pause=false;
			score="000";
			time=150;	
			
			for ( int i=0;i<12;i++){       // first saving -1 indicates that their is nothing on board
				for ( int j=0;j<16;j++){
					visible[i][j].setX_S(-1);
					visible[i][j].setY_S(-1);
					
				}
			}
					
		}
		
		void setAddress(){                 // setting the address of boundry squares
			for ( int i=0;i<12;i++){
				for (int j=0;j<16;j++){
					if ( (  i<2 || i>10) || (j<2 /*|| j>14*/)){
						visible[i][j].setX_S(i*50);
						visible[i][j].setY_S(j*50);
					
					}
					
				}
				
			}
		}
	
		void setSquare(int x, int y){   // for setting the address of new square in visible array
			int a=0,b=0;
			for ( a=0;a*50!=x;a++);
			for ( b=0;b*50!=y;b++);
			visible[a][b].setX_S(x);
			visible[a][b].setY_S(y);
			visible[a][b].setColor(boxArray[index]->piece->getColor());
			
		}

		bool detect( int x, int y){      // for the detection of pieces
			for ( int i=0;i<12;i++){
				for (int j=0;j<16;j++){
						
					if ( visible[i][j].getX_S()==x && visible[i][j].getY_S()+50==y && x>=100 && x<550)
						return true;
					//if ( visible[i][j].getX_S()+50==x && visible[i][j].getY_S()==y )
					
				}
			}
			return false;		
		}			

		int getIndex(){   //for the index and saving the address of piece which touched another piece
			int count=0;
			for ( int  i=0;i<4;i++){
				if ( detect(boxArray[index]->piece[i].getX_S(),boxArray[index]->piece[i].getY_S())  )
					count++;
				if ( count>0){ 
				setSquare( boxArray[index]->piece[0].getX_S() ,boxArray[index]->piece[0].getY_S() );
				setSquare( boxArray[index]->piece[1].getX_S() ,boxArray[index]->piece[1].getY_S() );
				setSquare( boxArray[index]->piece[2].getX_S() ,boxArray[index]->piece[2].getY_S() );
				setSquare( boxArray[index]->piece[3].getX_S() ,boxArray[index]->piece[3].getY_S() );
				setIndex();
				count=0;
				}
			}
			full(); // for row removing and moving down if row remove
			return index;
		}

		void setIndex(){  // for initializing new Shape
			InitRandomizer();
			index=GetRandInRange(0,7);
				pause=false;
				space=false;
				if ( index==0)
				boxArray[0]=new Straight;
				else if ( index==1)
				boxArray[1]=new Box;
				else if ( index==2)
				boxArray[2]=new TShape;
				else if ( index==3)
				boxArray[3]=new RShape;
				else if ( index==4)
				boxArray[4]=new LShape;
				else if (index==5)
				boxArray[5]=new RStep;
				else if ( index==6)
				boxArray[6]= new LStep;
			
		}

		int error; 
	
		string setScore(string s){   // for addition in the score string
			int i=atoi(s.c_str());
			i++;
			string l="000";;
			int index=2;
			while(i!=0){
				l[index]=(i%10+48);
				i=i/10;
				index--;
				
			}
			return l;
			
		}	
		void full(){   // for the removing of rows and shifting down if row removed 
			int count=0,temp=0;
			for ( int i=2;i<15;i++){
				temp=visible[0][i].getY_S();
				
				for ( int j=2;j<11;j++){
					if ( visible[j][i].getY_S() == temp){
						count++;
					
						
					}
				}
				truncate(); // for closing the game
				if ( count==9 ){
					int l=i;
					score=setScore(score);
					error++;
					if ( error%2==0 && time>30)
						time-=10;
					//cout<<error<<" "<<time<<endl;	
					for ( int j=2;j<11;j++){						
						visible[j][i].setY_S(-1);
						visible[j][i].setX_S(-1);			
						
					
					}
					for (int k=2;k<11;k++){
						for ( int j=l;j<12;j++){
							
							visible[k][j].setY_S(visible[k][j+1].getY_S()-50 )	;
							visible[k][j].setX_S(visible[k][j+1].getX_S() );
						}
						
					}				
				}
				
				
				count=0;	
			}
		}
		

		void truncate(){ // for the closing the game
			for ( int i=2;i<11;i++){
				for ( int j=2;j<16;j++)
					if (  visible[i][j].getY_S()>=750 && visible[i][j].getY_S() != -1)
					{	DrawString(260, 520, "--GAME OVER--", colors[NAVAJO_WHITE]);
							pause=true;
					}	
			}	
		}
		bool checkRight(){
			for ( int i=2;i<11;i++){
				for (int j=2;j<15;j++){
					for (int k=0;k<4;k++){
						if ( visible[i][j].getX_S()+50==boxArray[index]->piece[k].getX_S() && visible[i][j].getY_S()==boxArray[index]->piece[k].getY_S() )
							return true;
						}
					}
				}
			return false;			
		}

		bool checkLeft(){
			for ( int i=2;i<11;i++){
				for (int j=2;j<15;j++){
					for (int k=0;k<4;k++){
						if ( visible[i][j].getX_S()-50==boxArray[index]->piece[k].getX_S() && visible[i][j].getY_S()==boxArray[index]->piece[k].getY_S() )
							return true;
						}
					}
				}
			return false;			
		}
			 
};


Game * ptr= new Game;                                           // main global pointer for manipulating whole game



/* Function sets canvas size (drawing area) in pixels...
 *  that is what dimensions (x and y) your game will have
 *  Note that the bottom-left coordinate has value (0,0) and top-right coordinate has value (width-1,height-1)
 * */
void SetCanvasSize(int width, int height) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, width, 0, height, -1, 1); // set the screen size to given width and height.
    glMatrixMode( GL_MODELVIEW);
    glLoadIdentity();
}
/*
 * Main Canvas drawing function.
 * */
double startx=320,starty=400;

void Display()/**/{
    // set the background color using function glClearColor.
    // to change the background play with the red, green and blue values below.
    // Note that r, g and b values must be in the range [0,1] where 0 means dim rid and 1 means pure red and so on.
	
    glClearColor(0/*Red Component*/, 0.0/*Green Component*/,
            0.0/*Blue Component*/, 0 /*Alpha component*/);// Red==Green==Blue==1 --> White Colour
    glClear(GL_COLOR_BUFFER_BIT);   //Update the colors
		
	/*for ( int i=0;i<12;i++){
		for (int j=0;j<16;j++){
				if ( (  i<2 || i>10) || (j<2 || j>14))
					DrawSquare(i*50,j*50,50, colors[BLUE_VIOLET]);
			}
	}*/
	
	ptr->setAddress();  // setting addresses of boundaries
	for ( int i=0;i<12;i++){    // for the drawing the the squares which is saved in visible 
		for ( int j=0;j<16;j++){
			if ( ptr->visible[i][j].getX_S()==-1 && ptr->visible[i][j].getY_S()==-1)
				continue;
			if ( (  i<2 || i>10) || (j<2))
					DrawSquare(i*50,j*50,50, colors[BLUE_VIOLET]);
			else
			DrawSquare ( ptr->visible[i][j].getX_S(), ptr->visible[i][j].getY_S(),50,colors[ptr->visible[i][j].getColor()]);
	//colors[ptr->boxArray[ptr->getIndex()]->getColor( ) ]);
		}
	}
	
	if ( ptr->pause==true){  // for the pause of game
		if ( ptr->boxArray[ptr->index]->piece[3].getY_S()<=800)
		 DrawString(350, 400, "PAUSED", colors[NAVAJO_WHITE]);
	}
	
									
	DrawString(620, 550-ptr->speed*5, "WELCOME", colors[PLUM]);               // for Showing different words
	DrawString(700, 500-ptr->speed*5, "    HERE   ", colors[RED]);
	DrawString(600, 650, " INSTRUCTION ", colors[HONEYDEW]);	
	DrawString(605, 620, "p-> for pause  ", colors[GREEN]);
	DrawString(605, 590, "space -> quick fire" , colors[GREEN]);
	DrawString(605, 560, " r-> rotate ", colors[GREEN]);
	

	DrawRoundRect( 630, 680,160 , 60 ,  colors[50],12);     // box for score
	
	if ( ptr->space && !ptr->pause){          			//for quick shoot by space
		ptr->boxArray[ptr->getIndex()]->MoveY(-50);	
	}

	ptr->speed++;	
	if ( ptr->speed>=ptr->time ){ // speed of the object
		if (!ptr->pause)
			ptr->boxArray[ptr->getIndex()]->MoveY(-50);
		ptr->speed=0;
	} 

	ptr->boxArray[ptr->getIndex()]->draw(ptr->boxArray[ptr->getIndex()]->piece[0].getX_S(),ptr->boxArray[ptr->getIndex()]->piece[0].getY_S() );  // for the drawing of new pieces
	
    DrawString(650, 750, " Your Score is ", colors[NAVAJO_WHITE]);
    DrawString(650, 700, "       "+ptr->score, colors[NAVAJO_WHITE]);
    glutSwapBuffers(); // do not modify this line..
}

/*This function is called (automatically) whenever any non-printable key (such as up-arrow, down-arraw)
 * is pressed from the keyboard
 *
 * You will have to add the necessary code here when the arrow keys are pressed or any other key is pressed...
 *
 * This function has three argument variable key contains the ASCII of the key pressed, while x and y tells the
 * program coordinates of mouse pointer when key was pressed.
 *
 * */

void NonPrintableKeys(int key, int x, int y) {
    if (key == GLUT_KEY_LEFT /*GLUT_KEY_LEFT is constant and contains ASCII for left arrow key*/) {
	if ( !ptr->pause){
		if ( !ptr->checkRight())        
			ptr->boxArray[ptr->getIndex()]->Move(-50);
		
	}// what to do when left key is pressed...
    } else if (key == GLUT_KEY_RIGHT /*GLUT_KEY_RIGHT is constant and contains ASCII for right arrow key*/) {
	if ( !ptr->pause)
		if ( !ptr->checkLeft())	
			ptr->boxArray[ptr->getIndex()]->Move(50);
    } else if (key == GLUT_KEY_UP/*GLUT_KEY_UP is constant and contains ASCII for up arrow key*/) {
		
	
    }

    else if (key == GLUT_KEY_DOWN/*GLUT_KEY_DOWN is constant and contains ASCII for down arrow key*/) {
	if ( !ptr->pause)	
	ptr->boxArray[ptr->getIndex()]->MoveY(-50);    
		
}

    /* This function calls the Display function to redo the drawing. Whenever you need to redraw just call
     * this function*/

     glutPostRedisplay();

}

/*This function is called (automatically) whenever any printable key (such as x,b, enter, etc.)
 * is pressed from the keyboard
 * This function has three argument variable key contains the ASCII of the key pressed, while x and y tells the
 * program coordinates of mouse pointer when key was pressed.
 * */
void PrintableKeys(unsigned char key, int x, int y) {
    if (key == KEY_ESC/* Escape key ASCII*/) {
        exit(1); // exit the program when escape key is pressed.
    }
    if (key == 'R' || key=='r'/* Escape key ASCII*/) {
        //exit(1); // exit the program when escape key is pressed.
	if ( !ptr->pause)
    	ptr->boxArray[ptr->getIndex()]->angle+=90;
    }
    if (key == SPACEBAR ){         // for spacebar ASCI is defined as macros
	if (ptr->pause==false)
	ptr->space=!ptr->space;
	
    }
    if ( key=='p' || key=='P' )
    {
	ptr->pause=!ptr->pause;
	
    }
    glutPostRedisplay();
}

/*
 * This function is called after every 1000.0/FPS milliseconds
 * (FPS is defined on in the beginning).
 * You can use this function to animate objects and control the
 * speed of different moving objects by varying the constant FPS.
 *
 * */

void Timer(int m) {

// implement your functionality here
	glutPostRedisplay();
// once again we tell the library to call our Timer function after next 1000/FPS
    glutTimerFunc(1000.0 / FPS, Timer, 0);
}

/*
 * our gateway main function
 * */
int main(int argc, char*argv[]) {
    int width = 800, height = 800; // i have set my window size to be 800 x 600
    InitRandomizer(); // seed the random number generator...
    glutInit(&argc, argv); // initialize the graphics library...

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // we will be using color display mode
    glutInitWindowPosition(50, 50); // set the initial position of our window
    glutInitWindowSize(width, height); // set the size of our window
    glutCreateWindow("CP's Tetris"); // set the title of our game window
    SetCanvasSize(width, height); // set the number of pixels...

// Register your functions to the library,
// you are telling the library names of function to call for different tasks.
//glutDisplayFunc(display); // tell library which function to call for drawing Canvas.
    glutDisplayFunc(Display); // tell library which function to call for drawing Canvas.
    glutSpecialFunc(NonPrintableKeys); // tell library which function to call for non-printable ASCII characters
    glutKeyboardFunc(PrintableKeys); // tell library which function to call for printable ASCII characters
// This function tells the library to call our Timer function after 1000.0/FPS milliseconds...
    glutTimerFunc(1000.0 / FPS, Timer, 0);

// now handle the control to library and it will call our registered functions when
// it deems necessary...
    glutMainLoop();
    return 1;
}
#endif /* TETRIS_CPP_ */

