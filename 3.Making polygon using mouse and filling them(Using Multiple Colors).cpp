#include<bits/stdc++.h>
#include<GL/glut.h>
using namespace std;
int a=0;
struct c
{
float r,g,b;
}col,curr;
vector<int>x_v,y_v;
void init()
{
	glClearColor(1.0,1.0,1.0,0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	gluOrtho2D(0,600,0,600);
	glEnd();
	glFlush();
}
void setpixel(int x,int y)
{
	glBegin(GL_POINTS);
	glColor3f(col.r,col.g,col.b);
	glVertex2i(x,y);
	glEnd();
	glFlush();
}
void palete()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(1.0,1.0,1.0,0.0);
	glColor3f(1.0,0.0,0.0);
	glRecti(50,50,150,100);
	glColor3f(0.0,1.0,0.0);
	glRecti(150,50,250,100);
	glColor3f(0.0,0.0,1.0);
	glRecti(50,100,150,150);
	glColor3f(0.0,1.0,1.0);
	glRecti(150,100,250,150);
	glColor3f(0.0,0.0,0.0);
	glRecti(50,150,150,200);
	glColor3f(1.0,1.0,1.0);
	glRecti(150,150,250,200);
	glColor3f(1.0,0.0,1.0);
	glRecti(50,200,150,250);
	glColor3f(1.0,1.0,0.0);
	glRecti(150,200,250,250);
	glFlush();

}
void color(int x,int y)
{
	if(x>=50&&x<=150)	
	{
		if(y>=50&&y<=100)
		{col.r=1.0;col.g=0.0;col.b=0.0;}

		if(y>=100&&y<=150)
		{col.r=0.0;col.g=0.0;col.b=1.0;}

		if(y>=150&&y<=200)
		{col.r=0.0;col.g=0.0;col.b=0.0;}

		if(y>=200&&y<=250)
		{col.r=1.0;col.g=0.0;col.b=1.0;}
	}

	if(x>=150&&x<=250)	
	{
		if(y>=50&&y<=100)
		{col.r=0.0;col.g=1.0;col.b=0.0;}

		if(y>=100&&y<=150)
		{col.r=0.0;col.g=1.0;col.b=1.0;}

		if(y>=150&&y<=200)
		{col.r=1.0;col.g=1.0;col.b=1.0;}

		if(y>=200&&y<=250)
		{col.r=1.0;col.g=1.0;col.b=0.0;}
	}
}
void dda(double x1,double y1,double x2,double y2)
{	
	double xinc,yinc,x,y,len,dx,dy;
	dx=x2-x1;	
	dy=y2-y1;
	len=max(abs(dx),abs(dy));
	xinc=dx/(float)len;
	yinc=dy/(float)len;
	x=x1;
	y=y1;
	setpixel(round(x),round(y));
	for(int i=0;i<len;i++)
	{
		x+=xinc;
		y+=yinc;
		setpixel(round(x),round(y));
	}
	
}
void floodfill(int a,int b)
{
	glReadPixels(a,b,1,1,GL_RGB,GL_FLOAT,&curr);
	if(curr.r!=col.r||curr.g!=col.g||curr.b!=col.b)
	{
		setpixel(a,b);
		floodfill(a,b+1);
		floodfill(a,b-1);
		floodfill(a+1,b);
		floodfill(a-1,b);
	}
}
void mouse(int b,int s,int x,int y)
{	if(s==GLUT_DOWN)
	{
	y=600-y;
	if(x>=50&&x<=250&&y>=50&&y<=250)
	{color(x,y);}
	else
	{
		
		int xsum=0,ysum=0;
		if(b==GLUT_LEFT_BUTTON)
		{	
			cout<<x<<" "<<y;
			if(a==1)
			{
				x_v.clear();
				y_v.clear();
				a=0;
			}
			
				setpixel(x,y);
				x_v.push_back(x);
				y_v.push_back(y);
			
		}
		
		else  if(b==GLUT_RIGHT_BUTTON)
		{
			for(int i=0;i<x_v.size();i++)
			{
				if(i==(x_v.size()-1))
				dda(x_v[i],y_v[i],x_v[0],y_v[0]);
	
				else
				dda(x_v[i],y_v[i],x_v[i+1],y_v[i+1]);
	
				xsum+=x_v[i];
				ysum+=y_v[i];
				
			}
			xsum/=x_v.size();
			ysum/=y_v.size();
			floodfill(xsum,ysum);
			a=1;
		}

		else if(a==2&&b==GLUT_LEFT_BUTTON)
		{
			floodfill(x,y);
		}
	}
	}
}


int main(int argc,char **argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE);
	glutInitWindowSize(600,600);
	glutInitWindowPosition(100,100);
	glutCreateWindow("Polygon Using Mouse");
	init();
	glutDisplayFunc(palete);
	glutMouseFunc(mouse);
	glutMainLoop();
	return 0;
}
