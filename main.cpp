#include <cmath>
#include <ctime>
#include <functional>
#include <memory_resource>
#include <string>
#include <time.h>
#include <raylib.h>
#include <iostream>
#include <math.h>
#include <unistd.h>
void Rotate(double& x,double& y,double xx,double yy,double theta);



Font f3270 ;
Font fcaskaydia;
Font fbigblue;
Font fpro;

int width = 800*2;
int height = 1000;




class Sun {
	int amx, amy , amr , Mleng;
	long int TiPerTrav , Mdeley;
	
public:
	int x=0 , y=0 ,r=10;



	Sun (int X , int Y , int R): x(X),y(Y),r(R)
	{}
	bool Moving = false;
	void draw (){	
		DrawCircle(  x,  y,  r,YELLOW);
		int dencity = r+r/5;
		int lineT = (r*3)/5;

		double lx1 = (double)x , ly1 = (double)(y+dencity) , lx2 = (double)x , ly2 = (double)ly1 + lineT;
		static double aneang = 0.0;
		Rotate(lx1, ly1, x, y, (double)aneang);
		Rotate(lx2, ly2, x, y, (double)aneang);

		for(int i = 0 ; i  < 8 ; i++){
			DrawLineBezier({lx1 , ly1}, {lx2 , ly2}, 5, YELLOW);
	
			Rotate(lx1, ly1, x, y, (double)45.0);
			Rotate(lx2, ly2, x, y, (double)45.0);
		
		}
		aneang+=0.001;

	}


};




class Earth {
	Texture2D earthT = LoadTexture("./sprits/earth.png"); 
	public:
	int x = 0 , y = 0 , r = 10;
	Color clor = BLUE;
	Earth (int X , int Y, int R)
		: x(X) , y(Y) , r(R) {

	}
	
	double balnSpeed = 0.001;
	unsigned int msPerMv = 1;
 
	void draw(){
		Color clorA = clor;
		static double sinCoun = 0.0;
		static unsigned int clk = clock()*1000/CLOCKS_PER_SEC;
		int sinEff = 20;

		clorA.a=30;
		
		DrawCircle(  x,  y + (sin(sinCoun)*sinEff),  r,clorA);
			
		clorA = SKYBLUE;
		clorA.a = 50;
		
		DrawCircle(  x,  y + (sin(sinCoun)*sinEff),  r-15,clorA);
		/*atmosfer , like, atmosfer*/
		
		float scale = (double)(r*1.7) / (double)((double)earthT.width *(double)(earthT.width / earthT.height) );
		
		DrawTextureEx(earthT, {x- ((earthT.width * scale) /2 ),y + (sin(sinCoun)*sinEff)-((earthT.width *scale )/2) + 20}, 0.0, scale  , WHITE);	

		if( ((clock()*1000)/CLOCKS_PER_SEC) >= (clk + msPerMv) ){
			//rota+=rotaSpeed;
			sinCoun+=balnSpeed;
			clk = (clock()*1000)/CLOCKS_PER_SEC;


		}
		//absolutly hack, and i dont know how it work , i mean , this is a phisics project after all?

	}
	
};



class Moon {
	int x = 0 , y = 0; 
	
	public:
	int r = 10;
	int des = 60;
	Earth earth;

	double rotaSpeed = 0.07;
	unsigned int msPerRot = 1;

	Color clor = WHITE;


	Moon ( int R , int Des, Earth E) 
		:  r(R) , earth(E) , des(Des)
	{
		x = earth.x - earth.r*2 - des;
		y = earth.y - r - des;
	}
	
	
	void draw(){
		//static double in = 0;
		static unsigned int clk = (clock()*1000)/CLOCKS_PER_SEC;		
		DrawCircle(  x,  y,  r,clor);
		if( ((clock()*1000)/CLOCKS_PER_SEC) >= (clk + msPerRot) ){
			//in += rotaSpeed;
			static double xx = (double) x, yy = (double)y;
			Rotate(xx, yy, (double)earth.x, (double) earth.y, rotaSpeed);
			clk = (clock()*1000)/CLOCKS_PER_SEC;
			y = (int)yy;
			x = (int)xx;
		}

		
	}
	

};





class Bootn {
protected:
	bool  Bool  = false;
	std::function<void()> func;
	int clk = 0;
public:
	int x = 0 , y = 0;
	int w = 50 , h = 20;
	std::string str = "Not Defined";
	Font fnt;
	
	Color InClr = Color{25,25,25,255};
	Color FrmClr = {50,50,50,255};
	Color TextClr = YELLOW;

	int fntSz = 40;
	int Spacs = 4;

	Bootn(int X , int Y , std::string S, std::function<void()> fn):x(X) , y(Y) ,str(S)
	{
		fnt=fpro;
		func = fn;
		rloadScals();
		
	}
	
	void rloadScals(){
		w = str.size() * (fntSz/2 ) + 10  ;
		h = fntSz + 8;
	}
	
	bool isPreesd(){
		return Bool;
	}

	void draw(){
		Color tFrm = FrmClr;
		tFrm.a=100;
		DrawRectangleRounded({x-3,y-3,w+6,h+6}, 0.7, 20, tFrm);
		DrawRectangleRounded({x-1,y-1,w+2,h+2}, 0.7, 20, FrmClr);
		
		DrawRectangleRounded({x,y,w,h}, 0.7, 20, InClr);
		DrawTextEx(fnt, str.c_str(), {x+10,y+8}, fntSz, 0, TextClr);
		if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)&& 
				GetMousePosition().x >= x && GetMousePosition().x < x+w &&
				GetMousePosition().y >= y && GetMousePosition().y < y+h)
		{
			Bool = true;
			func();
		}else {
			Bool = false;

		}

	}

};






void Esp1(Sun& sun, Earth& earth , Moon& moon, Bootn& b1 , Bootn& b2 , Bootn& b3 , Bootn& b4 , Bootn& b5 , Bootn& b6 , Bootn& b7);









int main() {
	InitWindow(width,height,"The Global Warming");
	f3270 =      LoadFont("./fonts/3270.ttf"	 );
	fcaskaydia = LoadFont("./fonts/CaskaydiaCove.ttf");
	fbigblue =   LoadFont("./fonts/BigBlueTerm.ttf"  );
	fpro  =      LoadFont("./fonts/pro.ttf"  );
	fpro.baseSize=40;
	f3270.baseSize=50;
	fcaskaydia.baseSize=50;
 
	
	Sun sun(400,height/2,50);
	Earth earth(80 , height/2, 400);
	Moon moon(20,50,earth);
	
	moon.rotaSpeed = 0.005;

	
	
	double Persent  = 100.0;
	int PresentYear = 2026;
	double Dgris = 15.0;
	double TheNoumalD = 13.7;


	int btnYs = height + 500;
	
	Bootn btn1(width/2,100 + btnYs,"Transport" ,
	[&](){
		static bool swth = false;
		btn1.InClr = swth?Color{25,25,25,255}:Color{150,150,150,255}; 
		btn1.TextClr = swth?YELLOW:BLACK;
		Persent += swth?15.0:-15.0;
		swth = !swth;
	});

	Bootn btn2(width/2,200 + btnYs,"Industry" ,
	[&](){
		static bool swth = false;
		btn2.InClr = swth?Color{25,25,25,255}:Color{150,150,150,255}; 
		btn2.TextClr = swth?YELLOW:BLACK;
		Persent += swth?24.0:-24.0;
		swth = !swth;
	});

	Bootn btn3(width/2,300 + btnYs,"Electricity+heat" ,
	[&](){
		static bool swth = false;
		btn3.InClr = swth?Color{25,25,25,255}:Color{150,150,150,255}; 
		btn3.TextClr = swth?YELLOW:BLACK;
		Persent += swth?23.0:-23.0;
		swth = !swth;
	});
	Bootn btn4(width/2,400 + btnYs,"Agriculture" ,
	[&](){
		static bool swth = false;
		btn4.InClr = swth?Color{25,25,25,255}:Color{150,150,150,255}; 
		btn4.TextClr = swth?YELLOW:BLACK;
		Persent += swth?22.0:-22.0;
		swth = !swth;
	});
	Bootn btn5(width/2,500 + btnYs,"Buildings" ,
	[&](){
		static bool swth = false;
		btn5.InClr = swth?Color{25,25,25,255}:Color{150,150,150,255}; 
		btn5.TextClr = swth?YELLOW:BLACK;
		Persent += swth?5.6:-5.6;
		swth = !swth;
	});
	Bootn btn6(width/2,600 + btnYs,"Others" ,
	[&](){
		static bool swth = false;
		btn6.InClr = swth?Color{25,25,25,255}:Color{150,150,150,255}; 
		btn6.TextClr = swth?YELLOW:BLACK;
		Persent += swth?10.4:-10.4;
		swth = !swth;
	});

	Bootn run(width/2 - 50,800 + btnYs,"+50 Y" ,
	[&](){
		static bool swth = false;
		swth = !swth;
		Dgris += ((double)(PresentYear+50 - PresentYear)/100.0) * 2.0 * (Persent/100.0);
		Dgris -= 0.05 * ((double)(PresentYear+50 - PresentYear)/100.0) ;
		PresentYear+=50;
		//this first what i fande the first what i put
	});

	
	Bootn reset( width /2  - 40 , height/2 + 400 ,"Reset" ,
	[&](){
		PresentYear=2026;
		Dgris = 15.0;
	});
	
	run.TextClr = GREEN;
	run.InClr = BLACK;

	reset.InClr = RED;
	reset.TextClr = BLACK;

	Esp1(sun, earth , moon , btn1 , btn2, btn3, btn4, btn5, btn6, run );
	
	Color white  = WHITE;
	Color skyblue= SKYBLUE;
	Color green  = GREEN;
	Color red    = RED;
	Color orange = ORANGE;
	Color yellow = YELLOW;
	
	white.a  = 0;
	skyblue.a= 0;
	green.a  = 0;
	red.a    = 0;
	orange.a = 0;
	yellow.a = 0;//to make things nicly faide in
	int clk = clock()*1000 / CLOCKS_PER_SEC;
	while (!WindowShouldClose()) {
		
		BeginDrawing();
		
        	ClearBackground(BLACK);
		////////////////////////////////////////////////////////
		std::string prs =  std::to_string((int)(Persent*10.0)).c_str();
		if(Persent > 0.0)prs.insert(prs.size() - 1 , ".");
		prs.append("%");
		prs.insert(0 , "The Global Warming Effect: ");
		
		DrawTextEx(fcaskaydia,prs.c_str(), {width - 600 ,height - 40}, 30, 5, white);

		
		//////////////////////////////////////////////////////
		
		DrawTextEx(fpro,"The year is :", {50 ,0}, 30, 0, skyblue);
		DrawTextEx(fpro,std::to_string(PresentYear).c_str(), {90 ,30}, 50, 0, skyblue);
		
		/////////////////////////////////////////////////////
		
		DrawTextEx(fpro,"Avrage Temperature", {500 ,height/2 - 150}, 30, 0, white);
		
		std::string dgr =  std::to_string((int)(Dgris*10.0)).c_str();
		if(Dgris > 0.0)dgr.insert(dgr.size() - 1 , ".");
		dgr.append(" C");
		DrawTextEx(fcaskaydia,dgr.c_str(), {550 ,height/2 -50}, 60, 0, (Dgris - TheNoumalD )> 0.0 ? Dgris > 15.0 ?red : orange : green);
		
		std::string delta =  std::to_string((int)((Dgris-TheNoumalD)*10.0)).c_str();	
		if(Dgris-TheNoumalD > 0.0)delta.insert(delta.size() - 1 , ".");
		delta.append(" C");
		if(Dgris > TheNoumalD)delta.insert(0,"+");
		
		delta.append(" than it should be.");

		DrawTextEx(fcaskaydia,delta.c_str(), {550 ,height/2 -10}, 20, 0, (Dgris - TheNoumalD )> 0.0 ? Dgris > 15.0 ?red : orange : green);
		

		
		
		////////////////////////////////////////////////////
		if(clock()*1000 / CLOCKS_PER_SEC > clk +1){
			white.a < 255 ? white.a ++ , skyblue.a ++ , green.a++ , yellow.a++ , red.a ++ , orange.a++ : 0;
			clk = clock()*1000 / CLOCKS_PER_SEC ;
		}
		
		sun.draw();
		earth.draw();
		moon.draw();

		btn1.draw();
		btn2.draw();
		btn3.draw();
		btn4.draw();
		btn5.draw();
		btn6.draw();
		run.draw();
		if(PresentYear > 2026){
			reset.draw();
		}
        	EndDrawing();
	}
	return 0;
}





void Esp1(Sun& sun , Earth& earth , Moon& moon , Bootn& b1 , Bootn& b2 , Bootn& b3 , Bootn& b4 , Bootn& b5 , Bootn& b6 , Bootn& b7 ){

	//sun.AnemetionMove(width/2, 30, 50, 1000);
	sun.x = width/2;
	sun.y = -450;
	sun.r = 500;
	while(!WindowShouldClose()){
		BeginDrawing();
		ClearBackground(BLACK);
		
		sun.draw();
		DrawTextEx(fcaskaydia, "About", {width/2-5*5,height/2-25}, 20, 5, WHITE);
		DrawTextEx(fcaskaydia, "The global warming", {width/2-(18*10),height/2+15}, 40, 5, WHITE);

		EndDrawing();
		if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))break;

	}
	for(int i =  0 ; (i < (sun.r * 2 +  sun.r/5 + ((sun.r*3)/5   - 5)) + sun.y  || b1.y>100) && !WindowShouldClose(); i++ ){
		
		b1.y--;
		b2.y--;
		b3.y--;
		b4.y--;
		b5.y--;
		b6.y--;
		b7.y--;

		BeginDrawing();
		ClearBackground(BLACK);
		sun.y--;
		sun.draw();
		int r = 255 > i ? 255- i : 0;
		DrawTextEx(fcaskaydia, "About", {width/2-5*5,height/2-25-i}, 20, 5, (Color){255,255,255,r});
		DrawTextEx(fcaskaydia, "The global warming", {width/2-(18*10),height/2+15-i}, 40, 5, (Color){255,255,255,r});
		
		b1.draw();
		b2.draw();
		b3.draw();
		b4.draw();
		b5.draw();
		b6.draw();
		b7.draw();


		usleep(1000);
		EndDrawing();
	}
	if(WindowShouldClose())return;
	earth.x = -400;
	usleep(700000);
	double pBlanS = earth.balnSpeed;
	earth.balnSpeed = 0.0;
	int des = abs(-80 - earth.x);
	for(double siC = 0.0 , ex = (double)earth.x , bx = 0.0;  ((earth.x)<  -80) && !WindowShouldClose() ; siC += /*3.14159*/1.0/(double)des){
		
		BeginDrawing();
		ClearBackground(BLACK);
		bx += sin(siC)*0.5 - (double)(int)bx; 
		b1.x+= bx;
		b2.x+= bx;
		b3.x+= bx;
		b4.x+= bx;
		b5.x+= bx;
		b6.x+= bx;
		b7.x+= bx;

		moon.earth= earth;
		ex +=  sin(siC)* 0.5;
		
		earth.x=(int)ex;
		earth.draw();
		

		b1.draw();
		b2.draw();
		b3.draw();
		b4.draw();
		b5.draw();
		b6.draw();
		b7.draw();
		
		usleep(2000);
		EndDrawing();
	}
	if(WindowShouldClose())return;
	usleep(500000);
	earth.balnSpeed = pBlanS;
	



}




void Rotate(double& x,double& y,double xx,double yy,double theta){
	double raduis=(theta*3.14159)/(180.0);
	double X = x-xx;
	double Y = y-yy;
	x=xx+X*cos(raduis)-Y*sin(raduis);
	y=yy+X*sin(raduis)+Y*cos(raduis);
	return ;
}
