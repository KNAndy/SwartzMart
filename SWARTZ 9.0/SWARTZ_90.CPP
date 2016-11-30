/*	__________
	||		||		 ||     |=======|   |========	===========   ========
	||		||		 ||	|	|   |	    |       ||		     /
	--------- 	||		 ||	|	|   | =======	    ||		   /
		||	||      |-|	 ||   	|=======|   |  \	    ||           /
		||	   ==	      ==	|	|   |	 \	    ||	       /
	----------	      ==   == 		|	|   |	   \	    ||	      ========

	========================================================================================

*/

/*
	Guidelines

	    --> All the commands can be accessed using help command in the
		command line
	    --> Drop-down boxes are used in 3 places:
		    * Homepage - can be accessed by pressing enter key
		    * Billing - can be accessed by pressing space bar
		    * view database - can be accessed by pressing enter
	    --> Note: Drop-down box doesn't contain all the commands. It
		      covers the major commands only.
	    --> In Billing, once the page is over, the commands up and down
		can be used to toggle between pages.
		    * Down - for going to the next page
		    * Up - for accessing the previous page

*/

/*
	CREDENTIALS FOR THE SOFTWARE

	Admin Details:-
		Username: swartzteam
		Password: chettinad

	User Accounts:-
		Username: admin
		Password: admin

		Username: sathiaraj
		Password: computer

*/

/*

	COPYRIGHT SWARTZ MART

		DEVELOPED AND DISTRIBUTED BY
				FLUORINE TEAM
					NIHESH ANDERON == SOFTWARE DESIGNER
					NISHANT SHARMA == DATABASE MANAGER
					MIHIR SRIRAM   == GRAPHIC ASSIST

		SUBMITTED FOR FINAL EVALUATION ON 02/09/2015

		VERSION 9.0 SWARTZ MART
*/

/* Header Files Start */

#include<string.h>
#include<conio.h>
#include<ctype.h>
#include<stdio.h>
#include<fstream.h>
#include<process.h>
#include<iomanip.h>
#include<math.h>
#include<graphics.h>
#include<stdlib.h>
#include<dos.h>

/* Header Files End */

/* Structure Declarations Start */

struct account // Worker details in accdet.dat
{
	char username[30];
	char password[30];
	int tag;
};

struct customer // zpoints database in zpoints.dat
{
	int id;
	char name[50];
	char mobno[12];
	char address[25];
	int zpoints;
};

struct product // product details in list.dat
{
	char prodname[50];
	int prodcode,rate,stock;
};

/* Structure Declarations End */

/* Global Scope */

int gd=DETECT,gm;
char add[]={"C:\\TC\\BGI"};
int zid; // for updating zpoints
int variable=0; // for zpoints pay method
int successcheck=0; // for stockupdate verification
long total=0; // globalised total for visibility in other functions
int zpoints; // equivalent money value = zpoints * 0.5. zpoints=billamt/10.
char operatorname[50]; // for operator login purposes
int optag; // operator tag

/* Function Prototypes */

void polygon(int,int[],int,int); // Creates a polygon (no of vertices,array of points,style of box,color of box)
void cbc(char[],int,int); // shows cursor while accepting character by character
void createaccount(); // Creates a salesman account
void nbn(int &,int,int); // Accepts number by number
void personalinfo(account); // Stores workers information
void pay(); // To pay a bill
void homepage(); // Main page of the software
void billing(); // To bill products
void defaultdisplay(); // Official SWARTZ MART display style
void membercreate(); // Creates Zpoints member
void viewstock(); // To view the stock availability of a product
void viewdatabase(); // To access the internal database of the shop
void stockupdate(); // Updates the stock once a product is billed
void editstock(); // To increase stock on arrival
void createproduct(); // To add new products to the database
void clearslot(int,int); // clears a blank in a position
void deleteproduct(); // Deletes a product from the database
void editproduct(); // To edit a product in the database
void workers(); // To display the list of workers in the shop
void datetime(); // Shows date and time
void zupdate(); // Updates Zpoints after billing
void motion(); // Welcome screen
void zpay(); // Payment via Zpoints portal
void helpprint(int); // Default help menu style
void text(); // Part of motion
void b_three(); // Part of motion
void dotmotion(); // Part of motion
void b_two(); // Part of motion
void b_one(); // Part of motion
void showall(); // Displays all Zpoints customers
void zhome(); // Homepage for zpoints
void clearbill(); // Clears the billing area in billing()
void clearmemory(int,int[],int[]); // Similar to a destructor. Reinitializes variable's value to null.
void decoder(char[],int,int); // Decodes the password
int authenticator(int,int); // Validates the password during login
void prodhelp(); // Lists all products during billing
void dropdownbox(char[][100],int,int,int,char[]); // Creates a drop down box that gives options to the user
void sort(product[],int); // Internal function that sorts the different products into an array
void credits(); // credits page

void defaultdisplay()
{
	int polypoints[]={12,12,628,12,628,63,12,63,12,12};
	polygon(4,polypoints,1,9);
	settextstyle(1,0,4);
	setcolor(0);
	outtextxy(200,15,"SWARTZ MART");
	gotoxy(1,5);
	cout<<setfill('_')<<setw(80)<<"_"<<endl;
}

void credits()
{
	int polypoints[]={100,95,500,95,500,125,100,125,100,95};
	int polypoints1[]={100,135,500,135,500,165,100,165,100,135};
	int polypoints2[]={100,175,500,175,500,205,100,205,100,175};

	clrscr();
	cleardevice();
	settextstyle(3,0,4);
	outtextxy(245,40,"CREDITS");
	setcolor(8);
	polygon(4,polypoints,1,8);
	polygon(4,polypoints2,1,8);
	polygon(4,polypoints1,1,8);
	setcolor(14);
	settextstyle(8,0,1);
	outtextxy(110,95,"Software Designer  : Nihesh Anderson");
	outtextxy(110,135,"Database Manager  : Nishant Sharma");
	outtextxy(110,175,"Graphics Assist     : Mihir Sriram");
	outtextxy(60,265,"We also thank our mentor , Mr.Sathiaraj Thomas");
	setcolor(11);
	outtextxy(230,350,"Fluorine Team");
	sleep(4);
	clrscr();
	cleardevice();
	exit(0);
}

void dropdownbox(char b[][100],int x,int y,int colour,char variable[])
{

	int font=2,size=5,i,len,j,charmax=0;
	char ch;
	int lim;
	int ppmove[10];
	int pp1[10];

	for(len=0;isalpha(b[len][0]) && isalpha(b[len][1]);len++);
	for(j=0;j<len;j++)
		if(strlen(b[j])>charmax)
			charmax=strlen(b[j]);
	lim=j;

	pp1[0]=x;
	pp1[1]=y;
	pp1[2]=x+20+(charmax*8);
	pp1[3]=y;
	pp1[4]=x+20+(charmax*8);
	pp1[5]=y-3+(len*22);
	pp1[6]=x;
	pp1[7]=y-3+(len*22);
	pp1[8]=x;
	pp1[9]=y;

	setcolor(colour);
	polygon(4,pp1,1,9);
	settextstyle(font,0,size);
	for(j=0;j<len;j++)
		outtextxy(x+10,y+2+(j*22),b[j]);

	ppmove[0]=x;
	ppmove[1]=y;
	ppmove[2]=x+20+(charmax*8);
	ppmove[3]=y;
	ppmove[4]=x+20+(charmax*8);
	ppmove[5]=y+19;
	ppmove[6]=x;
	ppmove[7]=y+19;
	ppmove[8]=x;
	ppmove[9]=y;

	polygon(4,ppmove,1,1);
	for(j=0;j<len;j++)
		outtextxy(x+10,y+2+(j*22),b[j]);
	i=0;
	for(;;)
	{
		ch=getche();
		if(ch==80)
		{
			if(i>=lim-1)
			{
			continue;

			}
			i++;

			polygon(4,pp1,1,9);
			ppmove[1]+=22;
			ppmove[3]+=22;
			ppmove[9]+=22;
			ppmove[5]+=22;
			ppmove[7]+=22;
			polygon(4,ppmove,1,1);
			for(j=0;j<len;j++)
			outtextxy(x+10,y+2+(j*22),b[j]);
		}
		else if(ch==72)
		{
			if(i<=0)
			{
				continue;
			}

			i--;

			polygon(4,pp1,1,9);
			ppmove[1]-=22;
			ppmove[3]-=22;
			ppmove[9]-=22;
			ppmove[5]-=22;
			ppmove[7]-=22;
			polygon(4,ppmove,1,1);
			for(j=0;j<len;j++)
				outtextxy(x+10,y+2+(j*22),b[j]);
		}
		else if(ch=='\r')
		{
			strcpy(variable,b[i]);
			goto end;
		}
		else
		{
			continue;
		}
	}
	end:
}

void clearbill()
{
	int i=0;
	for(;i<12;i++)
	{
		gotoxy(1,9+i);
		cout<<"                                                                             ";
	}
}

void dotmotion()
{
	int x=300,y=265,r=30,counter=0;
	float i;

	for(;;)
	{
		if(counter<10)
		{
			gotoxy(38,20);
			cout<<counter<<"%";
		}
		else if(counter<100)
		{
			gotoxy(37,20);
			cout<<counter<<"%";
		}
		else
		{
			gotoxy(37,20);
			cout<<"100%";
			for(i=0;i<6.272;i+=0.05)
			{
				setcolor(15);
				outtextxy((int)(x+(r*cos(i))),(int)(y+(r*sin(i))),".");
			}
			getch();
			homepage();
		}
		for(float i=0;i<6.772;i+=0.05)
		{
			setcolor(15);
			if(i<6.272)
			{
				outtextxy((int)(x+(r*cos(i))),(int)(y+(r*sin(i))),".");
				delay(10);
			}
			setcolor(0);
			outtextxy((int)(x+(r*cos(i-0.5))),(int)(y+(r*sin(i-0.5))),".");
		}
		counter+=random(30);
	}
}

void b_one()
{
	int c=3	,i,j;

	randomize();

	/* HORIZONTAL TOP */

	for(i=0,j=21;j<480||i<640 ;i++,j++)
	{
		putpixel(i,0,c);
		putpixel(i,6,c);
		putpixel(i,12,c);
		putpixel(i,18,c);

		/* VERTICAL LEFT */

		if(j<480)
		{
			putpixel(0,j,c);
			putpixel(6,j,c);
			putpixel(12,j,c);
			putpixel(18,j,c);
		}
		delay(1);
	}

	/* VERTICAL RIGHT */

	for(i=21,j=21;j<620;i++,j++)
	{
		putpixel(619,i,c);
		putpixel(625,i,c);
		putpixel(631,i,c);
		putpixel(637,i,c);

		/* HORIZONTAL BOTTOM */

		if(j<620)
		{
			putpixel(j,459,c);
			putpixel(j,465,c);
			putpixel(j,471,c);
			putpixel(j,477,c);
		}
		delay(1);
	}
}

void b_two()
{
	int c=3,i,j;

	randomize();

	/* HORIZONTAL TOP */

	for(i=0,j=21;j<400 || i<560;i++,j++)
	{
		if(i<560)
		{
			putpixel(40+i,40,c);
			putpixel(40+i,46,c);
			putpixel(40+i,52,c);
			putpixel(40+i,58,c);
		}

		/* VERTICAL LEFT */

		if(j<400)
		{
			putpixel(40,40+j,c);
			putpixel(46,40+j,c);
			putpixel(52,40+j,c);
			putpixel(58,40+j,c);
		}
		delay(1);
	}

	/* VERTICAL RIGHT */

	for(i=21,j=21;j<540;i++,j++)
	{
		if(i<400)
		{
			putpixel(579,40+i,c);
			putpixel(585,40+i,c);
			putpixel(591,40+i,c);
			putpixel(597,40+i,c);
		}

		/* HORIZONTAL BOTTOM */
		putpixel(40+j,419,c);
		putpixel(40+j,425,c);
		putpixel(40+j,431,c);
		putpixel(40+j,437,c);
		delay(1);
	}
}

void b_three()
{
	int c=3,i,j;

	randomize();

	/* HORIZONTAL TOP */

	for(i=40,j=0;j<300 || i<520;i++,j++)
	{
		if(i<520)
		{
			putpixel(40+i,80,c);
			putpixel(40+i,86,c);
			putpixel(40+i,92,c);
			putpixel(40+i,98,c);

		}

		/* VERTICLE LEFT */

		if(j<300)
		{
			putpixel(80,100+j,c);
			putpixel(86,100+j,c);
			putpixel(92,100+j,c);
			putpixel(98,100+j,c);
		}
		delay(1);
	}

	/* VERTICLE RIGHT */

	for(i=60,j=21;j<460;i++,j++)
	{
		if(i<360)
		{
			putpixel(539,40+i,c);
			putpixel(545,40+i,c);
			putpixel(551,40+i,c);
			putpixel(557,40+i,c);

		}

		/* HORIZONTAL BOTTOM */

		putpixel(80+j,380,c);
		putpixel(80+j,386,c);
		putpixel(80+j,392,c);
		putpixel(80+j,398,c);
		delay(1);
	}
}

void text()
{
	int j=75,i=0;
	randomize();
	while(1)
	{
		if(i<2000)
		{
			putpixel(random(441)+101,random(280)+100,random(17));
		}
		settextstyle(6,0,5);
		setcolor(12);
		if(i==30)
		outtextxy(153+j,150,"S");
		if(i==60)
		outtextxy(175+j,150,"W");
		if(i==90)
		outtextxy(205+j,150,"A");
		if(i==120)
		outtextxy(235+j,150,"R");
		if(i==150)
		outtextxy(260+j,150,"T");
		if(i==180)
		outtextxy(285+j,150,"Z");
		if(i==210)
		outtextxy(175+j,190,"M");
		if(i==240)
		outtextxy(205+j,190,"A");
		if(i==270)
		outtextxy(235+j,190,"R");
		if(i==300)
		outtextxy(260+j,190,"T");
		delay(10);
		if(i==350)
		{
			dotmotion();
		}
		i++;
	}
}

void helpprint(int y)
{
	int polypoints0[]={0,90,635,90,635,120,0,120,0,90};
	int polypoints1[]={0,121,635,121,635,y+30,0,y+30,0,121};

	setcolor(9);
	clrscr();
	cleardevice();
	defaultdisplay();
	setcolor(15);
	polygon(4,polypoints0,1,12);
	settextstyle(6,0,1);
	setcolor(11);
	outtextxy(70,90,"FUNCTION");
	outtextxy(470,90,"COMMAND");
	setcolor(2);
	polygon(4,polypoints1,1,1);
}

void sort(product prodveri[],int fdig)
{
	int i=0,j=0,temp;
	product p;
	ifstream x("LIST.dat",ios::binary);

	for(;!x.eof();i++)
	{
		x.read((char*)&p,sizeof(p));
		temp=p.prodcode/100;
		if(temp==fdig)
		{
			prodveri[j++]=p;
		}
	}
}

void prodhelp()
{
	int fdig,first,m,k,i;
	fstream x;
	product p;
	char command[50];
	product prodveri[200],allprod[400];

	int polypoints0[]={0,90,635,90,635,120,0,120,0,90};
	int polypoints[]={0,350,100,350,100,370,0,370,0,350};
	int polypoints2[]={500,12,618,12,618,40,500,40,500,12};

	top:
	first=0,i=0;
	clrscr();
	cleardevice();
	setcolor(9);
	defaultdisplay();
	polygon(4,polypoints2,1,1);
	settextstyle(3,0,1);
	setcolor(15);
	outtextxy(525,10,"Products");
	setcolor(12);
	polygon(4,polypoints0,1,12);
	setcolor(15);
	settextstyle(6,0,1);
	outtextxy(100,90,"Prod Code");
	outtextxy(232,90,"Prod Name");
	outtextxy(480,90,"Rate");
	setcolor(12);
	polygon(4,polypoints,1,12);
	settextstyle(6,0,1);
	setcolor(15);
	outtextxy(10,345,"Command");
	gotoxy(3,25);
	setcolor(6);
	datetime();
	for(;;)
	{
		clearslot(15,23);
		cbc(command,15,23);
		clearslot(15,23);
		if(strcmpi(command,"grocery")==0)
		{
			fdig=1;
			first=0;
			for(k=0;k<100;k++)
			{
				prodveri[k].prodcode='\0';
				strcpy(prodveri[k].prodname,'\0');
				prodveri[k].rate='\0';
			}
		}
		else if(strcmpi(command,"cookery")==0)
		{
		fdig=2;
		first=0;
		for(k=0;k<100;k++)
			{
				prodveri[k].prodcode='\0';
				strcpy(prodveri[k].prodname,'\0');
				prodveri[k].rate='\0';
			}
		}
		else if(strcmpi(command,"accessories")==0)
		{
			fdig=3;
			first=0;
			for(k=0;k<100;k++)
			{
				prodveri[k].prodcode='\0';
				strcpy(prodveri[k].prodname,'\0');
				prodveri[k].rate='\0';
			}
		}
		else if(strcmpi(command,"electronics")==0)
		{
			first=0;
			fdig=4;
			for(k=0;k<100;k++)
			{
				prodveri[k].prodcode='\0';
				strcpy(prodveri[k].prodname,'\0');
				prodveri[k].rate='\0';
			}
		}
		else if(strcmpi(command,"snacks")==0)
		{
			first=0;
			fdig=5;
			for(k=0;k<100;k++)
			{
				prodveri[k].prodcode='\0';
				strcpy(prodveri[k].prodname,'\0');
				prodveri[k].rate='\0';
			}
		}
		else if(strcmpi(command,"misc")==0)
		{
			first=0;
			fdig=6;
			for(k=0;k<100;k++)
			{
				prodveri[k].prodcode='\0';
				strcpy(prodveri[k].prodname,'\0');
				prodveri[k].rate='\0';
			}
		}
		else if(strcmpi(command,"exit")==0)
		{
			credits();
		}
		else if(strcmpi(command,"help")==0)
		{
			helpprint(270);
			setcolor(3);
			settextstyle(2,0,6);
			outtextxy(70,130,"Grocery items (100-199)");
			outtextxy(470,130,"grocery");
			outtextxy(70,150,"Cookery (200-299)");
			outtextxy(470,150,"cookery");
			outtextxy(70,170,"Accessories (300-399)");
			outtextxy(470,170,"accessories");
			outtextxy(70,190,"Electronic items (400-499)");
			outtextxy(470,190,"electronics");
			outtextxy(70,210,"Snacks (500-599)");
			outtextxy(470,210,"snacks");
			outtextxy(70,230,"Miscellaneous products (600-699)");
			outtextxy(470,230,"misc");
			outtextxy(70,250,"Continue billing");
			outtextxy(470,250,"back");
			outtextxy(70,270,"Exit the software");
			outtextxy(470,270,"exit");
			getch();
			goto top;
		}
		else if(strcmpi(command,"back")==0)
		{
			return;
		}
		else if(strcmpi(command,"down")==0)
		{
			clearbill();
			cout<<"\n                                                                     ";
			m=i;
			for(i=0;((i<12) && (prodveri[i+m].prodcode!='\0') && (prodveri[i+m].prodcode!=prodveri[i+m-1].prodcode));)
			{
				gotoxy(17,10+i);
				cout<<prodveri[i+m].prodcode;
				gotoxy(30,10+i);
				cout<<prodveri[i+m].prodname;
				gotoxy(62,10+i);
				cout<<prodveri[i+m].rate;
				i++;
			}
			i=m+12;
		}
		else if(strcmpi(command,"up")==0)
		{
			clearbill();
			cout<<"\n                                                                    ";
			m=i-24;
			for(i=0;((i<12) && (prodveri[i+m].prodcode!='\0') && (prodveri[i+m].prodcode!=prodveri[i+m-1].prodcode));)
			{
				gotoxy(17,10+i);
				cout<<prodveri[i+m].prodcode;
				gotoxy(30,10+i);
				cout<<prodveri[i+m].prodname;
				gotoxy(62,10+i);
				cout<<prodveri[i+m].rate;
				i++;
			}
			i=m+12;
		}
		else
		{
			continue;
		}
		if(first==0)
		{
			m=0;
			sort(prodveri,fdig);
			clearbill();
			cout<<"\n                                                                       ";
			for(i=0;i<12 && (prodveri[i].prodcode!=prodveri[i-1].prodcode);i++)
			{
				gotoxy(17,10+i);
				cout<<prodveri[i].prodcode;
				gotoxy(30,10+i);
				cout<<prodveri[i].prodname;
				gotoxy(62,10+i);
				cout<<prodveri[i].rate;
			}
			first=1;
		}
	}
}


int authenticator(int tag1=2,int tag2=2)
{
	account q;
	ifstream file;
	char ch,username[30],password[30];
	int f,i=0;

	int polypoints2[]={540,12,618,12,618,40,540,40,540,12};
	int pp1[]={190,150,300,150,300,220,190,220,190,150};
	int pp2[]={180,140,185,140,185,230,180,230,180,140};
	int pp3[]={180,140,450,140,450,145,180,145,180,140};
	int pp4[]={445,140,445,230,450,230,450,140,445,140};
	int pp5[]={180,230,450,230,450,225,180,225,180,230};

	clrscr();
	cleardevice();
	setcolor(9);
	defaultdisplay();
	setcolor(1);
	polygon(4,polypoints2,1,1);
	settextstyle(3,0,1);
	setcolor(15);
	outtextxy(558,10,"Login");
	polygon(4,pp3,2,3);
	polygon(4,pp5,2,3);
	polygon(4,pp4,2,3);
	polygon(4,pp2,2,3);
	polygon(4,pp1,1,1);
	setcolor(10);
	settextstyle(3,0,1);
	outtextxy(200,153,"USERNAME");
	outtextxy(200,185,"PASSWORD");
	if(tag2==2)
	{
		for(;i<61;i++)
		{
			gotoxy(80-i,20);
			cout<<"This section can be accessed only by staff           ";
			gotoxy(1,21);
			cout<<"                                               ";
			delay(100);
			if(kbhit())
			{
				f=1;
				gotoxy(19,20);
				cout<<"This section can be accessed only by staff                    ";
				break;
			}
		}
	}
	if(f==1)
	{
		ch=getche();
		gotoxy(1,25);
		cout<<ch;
		clearslot(1,25);
	}
	cbc(username,40,11);
	decoder(password,40,13);
	gotoxy(0,22);
	datetime();
	file.open("accdet.dat",ios::binary);
	file.read((char*)&q,sizeof(q));
	do
	{
		if(strcmpi(q.username,username)==0)
		{
			if(strcmp(q.password,password)==0)
			{
				if(q.tag==tag1||q.tag==tag2)
				{
					strcpy(operatorname,username);
					optag=q.tag;
					file.close();
					return(1);
				}
				else
				{
					file.close();
					return(0);
				}
			}
			else
			{
				file.close();
				return(0);
			}
		}
		file.read((char*)&q,sizeof(q));
	} while(!file.eof());
	file.close();
	return(0);
}

void datetime()
{
	int poly[]={0,380,630,380,630,400,0,400,0,380};
	struct date d;
	struct  time t;

	drawpoly(5,poly);
	getdate(&d);
	printf("Date : %d", d.da_day);
	printf("/%d/", d.da_mon);
	printf("%d", d.da_year);
	cout<<"\t\t";
	gettime(&t);
	printf("Time: %2d:%02d ", t.ti_hour, t.ti_min, t.ti_sec);
	cout<<"\t\tUser: "<<operatorname;
}

void decoder(char password[],int x,int y)
{
	int i=-1;
	gotoxy(x,y);
	cout<<"|";
	do
	{
		i++;
		gotoxy(x+i+1,y);
		cout<<"  ";
		gotoxy(x+i+1,y);
		password[i]=getche();
		if(password[i]==8)
		{
			password[i]='\0';
			password[i-1]='\0';
			i-=2;
			if(i<0)
			{
				i=-1;
				clearslot(x+i,y);
				cout<<" |";
				continue;
			}
			gotoxy(x+i+1,y);
			cout<<"| ";
			continue;
		}
		gotoxy(x+i,y);
		cout<<"*|";
	}while(password[i]!=13);
	password[i]='\0';
}

void motion()
{
	cleardevice();
	b_one();
	b_two();
	b_three();
	text();
}

void workers()
{
	char uid[30],name[30];
	int i=0,age;
	long salary;
	ifstream x("details.txt");

	int polypoints0[]={0,90,635,90,635,120,0,120,0,90};

	clrscr();
	cleardevice();
	setcolor(9);
	defaultdisplay();
	polygon(4,polypoints0,1,12);
	settextstyle(6,0,1);
	setcolor(11);
	outtextxy(20,88,"USER ID");
	outtextxy(170,88,"NAME");
	outtextxy(300,88,"AGE");
	outtextxy(375,88,"SALARY");
	while(!x.eof())
	{
		x>>uid;
		x>>name;
		x>>age;
		x>>salary;
		gotoxy(3,9+i);
		puts(uid);
		gotoxy(22,9+i);
		puts(name);
		gotoxy(39,9+i);
		cout<<age;
		gotoxy(49,9+i);
		cout<<salary;
		i++;
	}
	gotoxy(1,8+i);
	cout<<"                                                                             ";
	x.close();
	getch();
	return;
}

void showall()
{
	int j;
	customer c;
	fstream file("zpoints.dat",ios::in|ios::binary);

	int polypoints0[]={0,90,635,90,635,120,0,120,0,90};

	clrscr();
	cleardevice();
	defaultdisplay();
	polygon(4,polypoints0,1,12);
	settextstyle(6,0,1);
	setcolor(11);
	outtextxy(10,88,"Z ID");
	outtextxy(80,88,"NAME");
	outtextxy(225,88,"MOBILE");
	outtextxy(350,88,"ADDRESS");
	outtextxy(560,88,"ZPOINTS");
	file.read((char*)&c,sizeof(c));
	for(j=0;!file.eof();j++)
	{
		gotoxy(3,10+j);
		cout<<c.id;
		gotoxy(11,10+j);
		cout<<c.name;
		gotoxy(29,10+j);
		cout<<c.mobno;
		gotoxy(45,10+j);
		puts(c.address);
		gotoxy(71,10+j);
		cout<<c.zpoints;
		file.read((char*)&c,sizeof(c));
	}
	file.close();
	return;
}

void zhome()
{
	top:

	int j;
	char command[50];
	customer c;
	fstream file("zpoints.dat",ios::in|ios::binary);

	int polypoints2[]={500,12,618,12,618,40,500,40,500,12};
	int polypoints0[]={0,90,635,90,635,120,0,120,0,90};
	int polypoints[]={0,350,100,350,100,370,0,370,0,350};

	restart:
	clrscr();
	cleardevice();
	setcolor(9);
	defaultdisplay();
	polygon(4,polypoints2,1,1);
	settextstyle(3,0,1);
	setcolor(15);
	outtextxy(515,10,"Z Points");
	setcolor(12);
	polygon(4,polypoints0,1,12);
	settextstyle(6,0,1);
	setcolor(11);
	outtextxy(10,88,"Z ID");
	outtextxy(110,88,"NAME");
	outtextxy(230,88,"MOBILE");
	outtextxy(350,88,"ADDRESS");
	outtextxy(560,88,"ZPOINTS");
	setcolor(6);
	polygon(4,polypoints,1,12);
	settextstyle(6,0,1);
	setcolor(15);
	outtextxy(10,345,"Command");
	gotoxy(3,25);
	setcolor(6);
	datetime();
	for(j=0;;j++)
	{
		if(j!=0)
		{
			gotoxy(1,9+j);
			cout<<" ";
		}
		clearslot(15,23);
		cbc(command,15,23);
		clearslot(15,23);
		if(strcmpi(command,"show all")==0)
		{
			showall();
			getch();
			goto restart;
		}
		else if(strcmpi(command,"help")==0)
		{
			helpprint(170);
			setcolor(3);
			settextstyle(2,0,6);
			outtextxy(70,130,"Go to homepage");
			outtextxy(470,130,"home");
			outtextxy(70,150,"List all records");
			outtextxy(470,150,"show all");
			outtextxy(70,170,"Exit the software");
			outtextxy(470,170,"exit");
			getch();
			goto top;
		}
		else if(strcmpi(command,"home")==0)
		{
			homepage();
		}
		else if(strcmpi(command,"exit")==0)
		{
			credits();
		}
		else
		{
			gotoxy(1,10+j);
			cout<<">";
			gotoxy(3,10+j);
			cin>>zid;
			file.read((char*)&c,sizeof(c));
			while(!file.eof())
			{
				if(zid==c.id)
				{
					break;
				}
				else
					file.read((char*)&c,sizeof(c));
			}
			gotoxy(15,10+j);
			cout<<c.name;
			gotoxy(30,10+j);
			cout<<c.mobno;
			gotoxy(45,10+j);
			puts(c.address);
			gotoxy(71,10+j);
			cout<<c.zpoints;
		}
	}
}

void zupdate()
{
	int i=0;
	customer p;
	fstream file("zpoints.dat",ios::in|ios::binary);

	file.read((char*)&p,sizeof(p));
	while(!file.eof())
	{
		if(p.id==zid)
			break;
		else
		{
			file.read((char*)&p,sizeof(p));
			i++;
		}
	}
	file.close();
	p.zpoints+=zpoints;
	file.open("zpoints.dat",ios::out|ios::binary);
	file.seekp(i*sizeof(p),ios::beg);
	file.write((char*)&p,sizeof(p));
	::zpoints=0;
	file.close();
}

void zpay()
{
	top:

	char command[50];
	customer p;
	ifstream file;

	int polypoints2[]={500,12,618,12,618,40,500,40,500,12};
	int polypoints[]={0,350,100,350,100,370,0,370,0,350};
	int pp1[]={125,155,270,155,270,181,125,181,125,155};
	int pp2[]={125,187,270,187,270,212,125,212,125,187};
	int pp3[]={125,218,270,218,270,243,125,243,125,218};
	int pp4[]={125,249,270,249,270,273,125,273,125,249};

	restart:
	clrscr();
	cleardevice();
	setcolor(9);
	defaultdisplay();
	setcolor(6);
	setcolor(1);
	polygon(4,polypoints2,1,1);
	settextstyle(3,0,1);
	setcolor(15);
	outtextxy(515,10,"Z Login");
	polygon(4,polypoints,1,12);
	settextstyle(6,0,1);
	setcolor(15);
	outtextxy(10,345,"Command");
	gotoxy(3,25);
	setcolor(6);
	datetime();
	setcolor(0);
	polygon(4,pp1,1,3);
	polygon(4,pp2,1,3);
	polygon(4,pp3,1,3);
	polygon(4,pp4,1,3);
	setcolor(11);
	settextstyle(3,0,2);
	outtextxy(130,154,"Zpoints ID");
	outtextxy(130,185,"Name");
	outtextxy(130,215,"Mobile");
	outtextxy(130,247,"Zpoints");
	setcolor(10);
	outtextxy(190,105,"CUSTOMER DETAILS");
	gotoxy(39,11);
	cout<<"|                   ";
	gotoxy(39,11);
	cin>>zid;
	file.open("zpoints.dat",ios::binary);
	file.read((char*)&p,sizeof(p));
	while(!file.eof())
	{
		if(p.id==zid)
			break;
		else
			file.read((char*)&p,sizeof(p));
	}
	gotoxy(39,13);
	puts(p.name);
	gotoxy(39,15);
	cout<<p.mobno;
	gotoxy(39,17);
	cout<<p.zpoints;
	file.close();

	retry:
	gotoxy(15,23);
	cbc(command,15,23);
	clearslot(15,23);
	if(strcmpi(command,"pay")==0)
	{
		variable=1;
		pay();
		return;
	}
	else if(strcmpi(command,"help")==0)
	{
		helpprint(210);
		setcolor(3);
		settextstyle(2,0,6);
		outtextxy(70,130,"Pay bill");
		outtextxy(470,130,"Pay");
		outtextxy(70,150,"Reopen zpoints account");
		outtextxy(470,150,"restart");
		outtextxy(70,170,"Go to homepage");
		outtextxy(470,170,"home");
		outtextxy(70,190,"Cancel bill");
		outtextxy(470,190,"cancel");
		outtextxy(70,210,"Exit the software");
		outtextxy(470,210,"exit");
		getch();
		goto top;
	}
	else if(strcmpi(command,"restart")==0)
	{
		goto restart;
	}
	else if(strcmpi(command,"exit")==0)
	{
		credits();
	}
	else if(strcmpi(command,"cancel")==0)
	{
		return;
	}
	else if(strcmpi(command,"home")==0)
	{
		homepage();
	}
	else
	{
		goto retry;
	}
}

void polygon(int size,int p[],int style,int colour)
{
	setfillstyle(style,colour);
	drawpoly(size+1,p);
	fillpoly(size+1,p);
}

void deleteproduct()
{
	top:

	product p,q,r;
	fstream outfile;
	ifstream infile,recover;
	fstream file;
	char stock[20],optionsdel[][100]={"yes","no"},command[50],rate[50],prodname[50],temp[50];
	int j,prodcode,i;

	int polypoints2[]={485,12,618,12,618,40,485,40,485,12};
	int pperase[]={190,190,500,190,500,280,190,280,190,190};
	int polypoints0[]={0,110,635,110,635,140,0,140,0,110};
	int polypoints3[]={0,350,100,350,100,370,0,370,0,350};

	clrscr();
	cleardevice();
	setcolor(9);
	defaultdisplay();
	polygon(4,polypoints2,1,1);
	settextstyle(3,0,1);
	setcolor(15);
	outtextxy(490,10,"Delete Product");
	setcolor(12);
	polygon(4,polypoints0,1,12);
	settextstyle(6,0,1);
	setcolor(11);
	outtextxy(95,108,"PRODUCT CODE");
	outtextxy(255,108,"PRODUCT NAME");
	outtextxy(450,108,"RATE");
	outtextxy(510,108,"STOCK");
	gotoxy(0,22);
	setcolor(6);
	polygon(4,polypoints3,1,12);
	settextstyle(6,0,1);
	setcolor(15);
	outtextxy(10,345,"Command");
	clearslot(15,23);
	setcolor(6);
	gotoxy(3,25);
	datetime();
	recover.open("product.dat");
	recover.read((char*)&r,sizeof(r));
	for(j=0;;j++)
	{
		gotoxy(10,11);
		cout<<" ";
		clearslot(15,23);
		cbc(command,15,23);
		clearslot(15,23);
		clearslot(31,11);
		clearslot(51,11);
		clearslot(56,11);
		clearslot(13,11);
		if(strcmpi(command,"exit")==0)
		{
			credits();
		}
		else if(strcmpi(command,"help")==0)
		{
			helpprint(190);
			setcolor(3);
			settextstyle(2,0,6);
			outtextxy(70,130,"Go to the previous page");
			outtextxy(470,130,"back");
			outtextxy(70,150,"Go to homepage");
			outtextxy(470,150,"home");
			outtextxy(70,170,"Delete the opened product");
			outtextxy(470,170,"delete");
			outtextxy(70,190,"Exit the software");
			outtextxy(470,190,"exit");
			getch();
			goto top;
		}
		else if(strcmpi(command,"back")==0)
		{
			viewdatabase();
		}
		else if(strcmpi(command,"home")==0)
		{
			homepage();
		}
		else
		{
			clearslot(15,23);
			restart:

			if(strcmpi(command,"delete")==0 || strcmpi(command,"yes")==0)
			{
				infile.open("LIST.dat",ios::binary);
				outfile.open("NEW.dat",ios::out|ios::binary);
				while(!infile.eof())
				{
					gotoxy(1,1);
					infile.read((char*)&q,sizeof(q));
					if(q.prodcode!=prodcode)
						outfile.write((char*)&q,sizeof(q));
				}
				infile.close();
				outfile.close();
				remove("LIST.dat");
				rename("NEW.dat","LIST.dat");
				clearslot(15,23);
				clearslot(31,11);
				clearslot(51,11);
				clearslot(56,11);
				clearslot(13,11);
				continue;
			}
			else if(strcmpi(command,"no")==0)
			{
				clearslot(15,23);
				clearslot(31,11);
				clearslot(51,11);
				clearslot(56,11);
				clearslot(13,11);
				continue;
			}
			gotoxy(10,11);
			cout<<">";
			gotoxy(18,11);
			nbn(prodcode,18,11);
			file.open("LIST.dat",ios::binary|ios::in);
			gotoxy(33,11);
			file.read((char*)&p,sizeof(p));
			while(!file.eof())
			{
				if(p.prodcode==prodcode)
					break;
				else
					file.read((char*)&p,sizeof(p));
			}
			file.close();
			if(p.rate<0 || (prodcode!=r.prodcode && (strcmpi(p.prodname,r.prodname)==0)))
			{
				gotoxy(1,11);
				cout<<"							";
				goto restart;
			}
			cout<<p.prodname;
			gotoxy(57,11);
			cout<<p.rate;
			gotoxy(65,11);
			cout<<p.stock;
			setcolor(7);
			settextstyle(1,0,1);
			outtextxy(200,200,"Delete Product?");
			dropdownbox(optionsdel,365,210,3,command);
			setcolor(0);
			polygon(4,pperase,1,0);
			goto restart;
		}
	}
}
void editproduct()
{
	top:

	ifstream file;
	ifstream infile,recover;
	fstream outfile;

	product p,q,r;
	char stock[20],command[50],rate[50],prodname[50],temp[50];
	int j,prodcode,i;

	int polypoints2[]={490,12,618,12,618,40,490,40,490,12};
	int polypoints0[]={0,110,635,110,635,140,0,140,0,110};
	int polypoints3[]={0,350,100,350,100,370,0,370,0,350};

	clrscr();
	cleardevice();
	setcolor(9);
	defaultdisplay();
	polygon(4,polypoints2,1,1);
	settextstyle(3,0,1);
	setcolor(15);
	outtextxy(503,10,"Edit Product");
	setcolor(12);
	polygon(4,polypoints0,1,12);
	settextstyle(6,0,1);
	setcolor(11);
	outtextxy(95,108,"PRODUCT CODE");
	outtextxy(255,108,"PRODUCT NAME");
	outtextxy(450,108,"RATE");
	outtextxy(510,108,"STOCK");
	gotoxy(0,22);
	setcolor(6);
	polygon(4,polypoints3,1,12);
	settextstyle(6,0,1);
	setcolor(15);
	outtextxy(10,345,"Command");
	clearslot(15,23);
	setcolor(6);
	gotoxy(3,25);
	datetime();
	recover.open("product.dat");
	recover.read((char*)&r,sizeof(r));
	for(j=0;;j++)
	{
		if(j!=0)
		{
			gotoxy(10,10+j);
			cout<<" ";
		}
		clearslot(15,23);
		cbc(command,15,23);
		if(strcmpi(command,"exit")==0)
		{
			credits();
		}
		else if(strcmpi(command,"help")==0)
		{
			helpprint(170);
			setcolor(3);
			settextstyle(2,0,6);
			outtextxy(70,130,"Go to the previous page");
			outtextxy(470,130,"back");
			outtextxy(70,150,"Go to homepage");
			outtextxy(470,150,"home");
			outtextxy(70,170,"Exit the software");
			outtextxy(470,170,"exit");
			getch();
			goto top;
		}
		else if(strcmpi(command,"back")==0)
		{
			return;
		}
		else if(strcmpi(command,"home")==0)
		{
			homepage();
		}
		else
		{
			clearslot(15,23);
			gotoxy(10,11+j);
			cout<<">";
			gotoxy(18,11+j);
			cin>>prodcode;
			file.open("LIST.dat",ios::binary);
			gotoxy(33,11+j);
			file.read((char*)&p,sizeof(p));
			while(!file.eof())
			{
				if(p.prodcode==prodcode)
					break;
				else
					file.read((char*)&p,sizeof(p));
			}
			file.close();
			cout<<p.prodname;
			gotoxy(57,11+j);
			cin>>p.rate;
			gotoxy(65,11+j);
			cout<<p.stock;
			infile.open("LIST.dat",ios::binary);
			outfile.open("NEW.dat",ios::out|ios::binary);
			while(!infile.eof())
			{
				gotoxy(1,1); //dummy command
				infile.read((char*)&q,sizeof(q));
				if(q.prodcode==prodcode)
					outfile.write((char*)&p,sizeof(p));
				else
					outfile.write((char*)&q,sizeof(q));
			}
			infile.close();
			outfile.close();
			remove("LIST.dat");
			rename("NEW.dat","LIST.dat");
		}
	}
}

void clearslot(int m,int n)
{
	gotoxy(m,n);
	cout<<"               ";
	gotoxy(m,n);
}

void createproduct()
{
	top:

	char command[50];
	ofstream recover;
	int j;
	product p;
	fstream x;

	int pbox[]={275,155,470,155,470,273,275,273,275,155};
	int pp1[]={125,155,270,155,270,181,125,181,125,155};
	int pp2[]={125,187,270,187,270,212,125,212,125,187};
	int pp3[]={125,218,270,218,270,243,125,243,125,218};
	int pp4[]={125,249,270,249,270,273,125,273,125,249};
	int polypoints2[]={480,12,618,12,618,40,480,40,480,12};
	int polypoints3[]={0,350,100,350,100,370,0,370,0,350};

	clrscr();
	cleardevice();
	setcolor(9);
	defaultdisplay();
	polygon(4,polypoints2,1,1);
	settextstyle(3,0,1);
	setcolor(15);
	outtextxy(485,10,"Create Product");
	setcolor(11);
	polygon(4,pp1,1,12);
	polygon(4,pp2,1,12);
	polygon(4,pp3,1,12);
	polygon(4,pp4,1,12);
	setcolor(11);
	settextstyle(3,0,2);
	outtextxy(128,154,"Product Code");
	outtextxy(128,185,"Product Name");
	outtextxy(128,215,"Rate");
	outtextxy(128,247,"Stock");
	setcolor(6);
	polygon(4,pbox,1,2);
	polygon(4,polypoints3,1,12);
	settextstyle(6,0,1);
	setcolor(15);
	outtextxy(10,345,"Command");
	setcolor(6);
	gotoxy(3,25);
	datetime();
	for(j=0;;j++)
	{
		start:

		clearslot(15,23);
		cbc(command,15,23);
		if(strcmpi(command,"exit")==0)
		{
			credits();
		}
		else if(strcmpi(command,"help")==0)
		{
			helpprint(170);
			setcolor(3);
			settextstyle(2,0,6);
			outtextxy(70,130,"Go to the previous page");
			outtextxy(470,130,"back");
			outtextxy(70,150,"Go to homepage");
			outtextxy(470,150,"home");
			outtextxy(70,170,"Exit the software");
			outtextxy(470,170,"exit");
			getch();
			goto top;
		}
		else if(strcmpi(command,"home")==0)
		{
			homepage();
		}
		else if(strcmpi(command,"back")==0)
		{
			return;
		}
		else
		{
			clearslot(15,23);
			x.open("LIST.dat",ios::out|ios::binary|ios::app);
			recover.open("product.dat",ios::trunc);
			gotoxy(36,11);
			cout<<" ";
			gotoxy(36,11);
			cin>>p.prodcode;
			gotoxy(36,13);
			cout<<" ";
			gotoxy(36,13);
			cin>>p.prodname;
			gotoxy(36,15);
			cout<<" ";
			gotoxy(36,15);
			cin>>p.rate;
			gotoxy(36,17);
			cout<<" ";
			gotoxy(36,17);
			cin>>p.stock;
			x.write((char*)&p,sizeof(p));
			recover.write((char*)&p,sizeof(p));
			x.close();
			recover.close();
			clearslot(36,11);
			clearslot(36,13);
			clearslot(36,15);
			clearslot(36,17);
			setcolor(6);
			polygon(4,pbox,1,2);
			goto start;
		}
	}
}

void stockupdate(int qty,int prodcode)
{
	product p,q;
	ifstream file,infile;
	fstream outfile;

	file.open("LIST.dat",ios::binary);
	file.read((char*)&p,sizeof(p));
	while(!file.eof())
	{
		if(p.prodcode==prodcode)
			break;
		else
			file.read((char*)&p,sizeof(p));
	}
	p.stock-=qty;
	file.close();
	infile.open("LIST.dat",ios::binary);
	outfile.open("NEW.dat",ios::out|ios::binary);
	while(!infile.eof())
	{
		gotoxy(1,1);
		infile.read((char*)&q,sizeof(q));
		if(q.prodcode==prodcode)
			outfile.write((char*)&p,sizeof(p));
		else
			outfile.write((char*)&q,sizeof(q));
	}
	infile.close();
	outfile.close();
	remove("LIST.dat");
	rename("NEW.dat","LIST.dat");
}

void editstock()
{
	top:

	product p,q,r;
	char stock[20],command[50],rate[50],prodname[50],temp[50];
	int j,prodcode,i;
	ifstream infile,recover;
	fstream outfile;
	ifstream file;

	int polypoints2[]={500,12,618,12,618,40,500,40,500,12};
	int polypoints0[]={0,110,635,110,635,140,0,140,0,110};
	int polypoints3[]={0,350,100,350,100,370,0,370,0,350};

	clrscr();
	cleardevice();
	setcolor(9);
	defaultdisplay();
	polygon(4,polypoints2,1,1);
	settextstyle(3,0,1);
	setcolor(15);
	outtextxy(515,10,"Edit Stock");
	setcolor(12);
	polygon(4,polypoints0,1,12);
	settextstyle(6,0,1);
	setcolor(11);
	outtextxy(95,108,"PRODUCT CODE");
	outtextxy(255,108,"PRODUCT NAME");
	outtextxy(450,108,"RATE");
	outtextxy(510,108,"STOCK");
	gotoxy(0,22);
	setcolor(6);
	polygon(4,polypoints3,1,12);
	settextstyle(6,0,1);
	setcolor(15);
	outtextxy(10,345,"Command");
	clearslot(15,23);
	setcolor(6);
	gotoxy(3,25);
	datetime();
	recover.open("product.dat");
	recover.read((char*)&r,sizeof(r));
	for(j=0;;j++)
	{
		if(j!=0)
		{
			gotoxy(10,10+j);
			cout<<" ";
		}
		clearslot(15,23);
		cbc(command,15,23);
		if(strcmpi(command,"exit")==0)
		{
			credits();
		}
		else if(strcmpi(command,"home")==0)
		{
			homepage();
		}
		else if(strcmpi(command,"help")==0)
		{
			helpprint(170);
			setcolor(3);
			settextstyle(2,0,6);
			outtextxy(70,130,"Go to the previous page");
			outtextxy(470,130,"back");
			outtextxy(70,150,"Go to homepage");
			outtextxy(470,150,"home");
			outtextxy(70,170,"Exit the software");
			outtextxy(470,170,"exit");
			getch();
			goto top;
		}
		else if(strcmpi(command,"back")==0)
		{
			return;
		}
		else
		{
			clearslot(15,23);
			restart:

			gotoxy(10,11+j);
			cout<<">";
			gotoxy(18,11+j);
			nbn(prodcode,18,11+j);
			file.open("LIST.dat",ios::binary);
			gotoxy(33,11+j);
			file.read((char*)&p,sizeof(p));
			while(!file.eof())
			{
				if(p.prodcode==prodcode)
					break;
				else
					file.read((char*)&p,sizeof(p));
			}
			file.close();
			if(p.rate<0 || (prodcode!=r.prodcode && (strcmpi(p.prodname,r.prodname)==0)))
			{
				gotoxy(57,11+j);
				cout<<" 						";
				goto restart;
			}
			cout<<p.prodname;
			gotoxy(57,11+j);
			cout<<p.rate;
			nbn(p.stock,65,11+j);
			infile.open("LIST.dat",ios::binary);
			outfile.open("NEW.dat",ios::out|ios::binary);
			while(!infile.eof())
			{
				gotoxy(1,1);//dummy command
				infile.read((char*)&q,sizeof(q));
				if(q.prodcode==prodcode)
					outfile.write((char*)&p,sizeof(p));
				else
					outfile.write((char*)&q,sizeof(q));
			}
			infile.close();
			outfile.close();
			remove("LIST.dat");
			rename("NEW.dat","LIST.dat");
		}
	}
}

void viewdatabase()
{
	char command[30];
	char options[][100]={"view stock","edit stock","create product","edit product","delete product","home","command","exit"};

	int polypoints1[]={480,12,618,12,618,40,480,40,480,12};
	int polypoints0[]={194,129,406,129,406,298,194,298,194,129};
	int polypoints[]={200,135,400,135,400,165,200,165,200,135};
	int polypoints2[]={200,167,400,167,400,195,200,195,200,167};
	int polypoints3[]={200,197,400,197,400,228,200,228,200,197};
	int polypoints4[]={200,230,400,230,400,260,200,260,200,230};
	int polypoints5[]={200,262,400,262,400,292,200,292,200,262};
	int polypointsc[]={0,350,100,350,100,370,0,370,0,350};

	start:
	clrscr();
	cleardevice();
	setcolor(9);
	defaultdisplay();
	polygon(4,polypoints1,1,1);
	settextstyle(3,0,1);
	setcolor(15);
	outtextxy(490,10,"View Database");
	setcolor(0);
	polygon(4,polypoints0,1,1);
	polygon(4,polypoints,1,12);
	polygon(4,polypoints2,1,12);
	polygon(4,polypoints3,1,12);
	polygon(4,polypoints4,1,12);
	polygon(4,polypoints5,1,12);
	settextstyle(6,0,1);
	setcolor(11);
	gotoxy(27,10);
	cout<<""; // c++ symbol
	gotoxy(27,12);
	cout<<""; // c++ symbol
	gotoxy(27,14);
	cout<<""; // c++ symbol
	gotoxy(27,16);
	cout<<""; // c++ symbol
	gotoxy(27,18);
	cout<<""; // c++ symbol
	outtextxy(227,135,"View Stock");
	outtextxy(227,167,"Edit Stock");
	outtextxy(227,199,"Create Product");
	outtextxy(227,232,"Edit Product");
	outtextxy(227,266,"Delete Product");
	setcolor(6);
	gotoxy(3,25);
	datetime();
	for(;;)
	{
		gotoxy(0,24);
		setcolor(6);
		polygon(4,polypointsc,1,12);
		settextstyle(6,0,1);
		setcolor(11);
		outtextxy(10,345,"Command");
		clearslot(15,23);
		cbc(command,15,23);
		clearslot(15,23);
		if(command[0]=='\r')
		{
			command[0]='\0';
			dropdownbox(options,101,300,15,command);
		}
		if(strcmpi(command,"view stock")==0)
		{
			viewstock();
			goto start;
		}
		else if(strcmpi(command,"command")==0)
		{
			goto start;
		}
		else if(strcmpi(command,"help")==0)
		{
			helpprint(250);
			setcolor(3);
			settextstyle(2,0,6);
			outtextxy(70,130,"View product availability");
			outtextxy(470,130,"view stock");
			outtextxy(70,150,"To edit stock");
			outtextxy(470,150,"edit stock");
			outtextxy(70,170,"To create new product(s)");
			outtextxy(470,170,"create product");
			outtextxy(70,190,"To edit product details");
			outtextxy(470,190,"edit product");
			outtextxy(70,210,"To delete product");
			outtextxy(470,210,"delete product");
			outtextxy(70,230,"Go to homepage");
			outtextxy(470,230,"home");
			outtextxy(70,250,"Exit the software");
			outtextxy(470,250,"exit");
			getch();
			goto start;
		}
		else if(strcmpi(command,"edit stock")==0)
		{
			if(optag==1)
			{
				editstock();
				goto start;
			}
			else
			{
				if(authenticator(1)==1)
				{
					editstock();
					goto start;
				}
				else
				{
					goto start;
				}
			}

		}
		else if(strcmpi(command,"create product")==0)
		{
			if(optag==1)
			{
				createproduct();
				goto start;
			}
			else
			{
				if(authenticator(1)==1)
				{
					createproduct();
					goto start;
				}
				else
				{
					goto start;
				}
			}
		}
		else if(strcmpi(command,"edit product")==0)
		{
			if(optag==1)
			{
				editproduct();
				goto start;
			}
			else
			{
				if(authenticator(1)==1)
				{
					editproduct();
					goto start;
				}
				else
				{
					goto start;
				}
			}
		}
		else if(strcmpi(command,"exit")==0)
		{
			credits();
		}
		else if(strcmpi(command,"delete product")==0)
		{
			if(optag==1)
			{
				deleteproduct();
				goto start;
			}
			else
			{
				if(authenticator(1)==1)
				{
					deleteproduct();
					goto start;
				}
				else
				{
					goto start;
				}
			}
		}
		else if(strcmpi(command,"home")==0)
		{
			homepage();
		}
	}
}

void viewstock()
{
	top:

	char prodname[40],command[30],rate[30],stock[30];
	product p,r;
	int i,j,prodcode;
	ifstream recover,file;

	int polypoints2[]={500,12,618,12,618,40,500,40,500,12};
	int polypoints0[]={0,110,635,110,635,140,0,140,0,110};
	int polypoints3[]={0,350,100,350,100,370,0,370,0,350};

	clrscr();
	cleardevice();
	setcolor(9);
	defaultdisplay();
	polygon(4,polypoints2,1,1);
	settextstyle(3,0,1);
	setcolor(15);
	outtextxy(515,10,"View Stock");
	setcolor(12);
	polygon(4,polypoints0,1,12);
	settextstyle(6,0,1);
	setcolor(11);
	outtextxy(95,108,"PRODUCT CODE");
	outtextxy(255,108,"PRODUCT NAME");
	outtextxy(450,108,"RATE");
	outtextxy(510,108,"STOCK");
	gotoxy(0,22);
	polygon(4,polypoints3,1,12);
	settextstyle(6,0,1);
	setcolor(15);
	outtextxy(10,345,"Command");
	clearslot(15,23);
	setcolor(6);
	gotoxy(3,25);
	datetime();
	recover.open("product.dat");
	recover.read((char*)&r,sizeof(r));
	for(j=0;;j++)
	{
		if(j!=0)
		{
			gotoxy(10,10+j);
			cout<<" ";
		}
		clearslot(15,23);
		cbc(command,15,23);
		if(strcmpi(command,"exit")==0)
		{
			credits();
		}
		else if(strcmpi(command,"help")==0)
		{
			helpprint(170);
			setcolor(3);
			settextstyle(2,0,6);
			outtextxy(70,130,"Go to the previous page");
			outtextxy(470,130,"back");
			outtextxy(70,150,"Go to homepage");
			outtextxy(470,150,"home");
			outtextxy(70,170,"Exit the software");
			outtextxy(470,170,"exit");
			getch();
			goto top;
		}
		else if(strcmpi(command,"home")==0)
		{
			homepage();
		}
		else if(strcmpi(command,"back")==0)
		{
			viewdatabase();
		}
		else
		{
			clearslot(15,23);
			refresh:

			gotoxy(10,11+j);
			cout<<">";
			nbn(prodcode,18,11+j);
			file.open("LIST.dat",ios::binary);
			file.read((char*)&p,sizeof(p));
			while(!file.eof())
			{
				if(p.prodcode==prodcode)
					break;
				else
					file.read((char*)&p,sizeof(p));
			}
			gotoxy(33,11+j);
			cout<<p.prodname;
			file.close();
			if(p.rate<0 || (prodcode!=r.prodcode && (strcmpi(p.prodname,r.prodname)==0)))
			{
				gotoxy(1,11+j);
				cout<<"								";
				goto refresh;
			}
			gotoxy(57,11+j);
			cout<<p.rate;
			gotoxy(65,11+j);
			cout<<p.stock;
		}
	}
}

void membercreate()
{
	ifstream x("zpoints.dat",ios::binary);
	int max=0;
	customer b,c;
	fstream file;

	int polypoints2[]={500,12,618,12,618,40,500,40,500,12};
	int pp1[]={125,155,320,155,320,181,125,181,125,155};
	int pp2[]={125,187,320,187,320,212,125,212,125,187};
	int pp3[]={125,218,320,218,320,243,125,243,125,218};
	int pp4[]={125,249,320,249,320,273,125,273,125,249};

	clrscr();
	cleardevice();
	setcolor(9);
	defaultdisplay();
	do
	{
		x.read((char*)&b,sizeof(b));
		if(b.id>max)
		max=b.id;
	} while(!x.eof());
	setcolor(1);
	polygon(4,polypoints2,1,1);
	settextstyle(3,0,1);
	setcolor(15);
	outtextxy(515,10,"Z Sign-up");
	settextstyle(6,0,1);
	setcolor(6);
	gotoxy(3,25);
	datetime();
	setcolor(0);
	polygon(4,pp1,1,3);
	polygon(4,pp2,1,3);
	polygon(4,pp3,1,3);
	polygon(4,pp4,1,3);
	setcolor(11);
	settextstyle(3,0,2);
	outtextxy(130,154,"Zpoints ID");
	outtextxy(130,185,"Customer Name");
	outtextxy(130,215,"Mobile");
	outtextxy(130,247,"Address");
	setcolor(10);
	outtextxy(240,105,"NEW CUSTOMER");
	gotoxy(43,11);
	cout<<"|                   ";
	gotoxy(43,11);
	file.open("zpoints.dat",ios::out|ios::binary|ios::app);
	cout<<max+1;
	c.id=max+1;
	cbc(c.name,43,13);
	gotoxy(43,15);
	cout<<"|";
	gotoxy(43,15);
	cin>>c.mobno;
	gotoxy(43,17);
	cbc(c.address,43,17);
	c.zpoints=0;
	file.write((char*)&c,sizeof(c));
	settextstyle(1,0,1);
	setcolor(6);
	outtextxy(190,300,"ZPOINTS ACCOUNT CREATED!");
	sleep(3);
	file.close();
	x.close();
	return;
}

void pay()
{
	long paidamt;
	char ch[5],options[2][100]={"cash","card"},opt[5][100]={"yes","no"};
	char mode[20],name[50],cardtype[30],bank[30];
	char bno[5],bamt[6];
	int i=0,x,cardno;
	fstream zp;
	ofstream bill,file;
	customer p;
	ifstream billno;

	int pp1[]={125,155,270,155,270,181,125,181,125,155};
	int pp2[]={125,187,270,187,270,212,125,212,125,187};
	int pp3[]={125,218,270,218,270,243,125,243,125,218};
	int pp4[]={125,249,270,249,270,273,125,273,125,249};
	int pp5[]={125,280,270,280,270,304,125,304,125,280};
	int pperase[]={290,190,500,190,500,300,290,300,290,190};
	int polypoints[]={0,90,635,90,635,120,0,120,0,90};
	int pperase2[]={290,210,350,210,350,270,290,270,290,210};

	clrscr();
	cleardevice();
	setcolor(9);
	defaultdisplay();
	file.open("custdet.txt",ios::ate);
	billno.open("curbill.txt");
	billno>>x;
	polygon(4,polypoints,1,12);
	settextstyle(6,0,1);
	setcolor(15);
	outtextxy(80,88,"BILL NO:");
	sprintf(bno,"%d",x+1);
	setcolor(0);
	outtextxy(150,88,bno);
	setcolor(15);
	outtextxy(355,88,"BILL AMOUNT:");
	sprintf(bamt,"%d",total);
	setcolor(0);
	outtextxy(465,88,bamt);
	setcolor(15);
	billno.close();
	bill.open("curbill.txt");
	bill<<x+1;
	bill.close();
	if(variable==1)
	{
		goto jump1;
	}
	polygon(4,pp1,1,1);
	outtextxy(130,153,"Name");

	jump1:
	polygon(4,pp2,1,1);
	outtextxy(130,185,"Payment mode");
	if(variable==1)
	{
		goto jump2;
	}
	cbc(name,37,11);
	jump2:
	setcolor(15);
	dropdownbox(options,290,190,15,mode);
	setcolor(0);
	polygon(4,pperase,1,0);
	gotoxy(37,13);
	cout<<mode;
	gotoxy(17,14);
	if(variable==1)
	{
		settextstyle(6,0,1);
		setcolor(15);
		polygon(4,pp3,1,1);
		outtextxy(130,216,"Reedem Zpoints");
		setcolor(15);
		dropdownbox(opt,290,225,15,ch);
		setcolor(0);
		polygon(4,pperase2,1,0);
		if(strcmp(ch,"yes")==0)
		{
			gotoxy(37,15);
			cout<<"                                   ";
			zp.open("zpoints.dat",ios::in|ios::out|ios::binary);
			zp.read((char*)&p,sizeof(p));
			while(!zp.eof())
			{
				if(p.id==zid)
					break;
				else
				{
					zp.read((char*)&p,sizeof(p));
					i++;
				}
			}
			if(total>=(p.zpoints*0.5))
			{
				total-=(p.zpoints*0.5);
				p.zpoints=0;
			}
			else
			{
				total=0;
				p.zpoints-=(total*2);
			}
			zp.seekp(i*sizeof(p));
			zp.write((char*)&p,sizeof(p));
		}
		zp.close();
	}
	clearslot(60,7);
	cout<<total;
	polygon(4,polypoints,1,12);
	settextstyle(6,0,1);
	setcolor(15);
	outtextxy(80,88,"BILL NO:");
	sprintf(bno,"%d",x+1);
	setcolor(0);
	outtextxy(150,88,bno);
	setcolor(15);
	outtextxy(355,88,"BILL AMOUNT:");
	sprintf(bamt,"%d",total);
	setcolor(0);
	outtextxy(465,88,bamt);
	setcolor(15);
	if(strcmpi(mode,"card")==0)
	{
		polygon(4,pp3,1,1);
		outtextxy(130,216,"Card number");
		polygon(4,pp4,1,1);
		outtextxy(130,247,"Card type");
		polygon(4,pp5,1,1);
		outtextxy(130,278,"Bank");
		file<<name<<"\n";
		clearslot(37,15);
		cout<<"|";
		gotoxy(37,15);
		cin>>cardno;
		file<<cardno<<"\n";
		cbc(cardtype,37,17);
		setcolor(0);
		setcolor(15);
		file<<cardtype<<endl;
		gotoxy(37,19);
		cbc(bank,37,19);
		file<<bank<<endl;
		file<<total<<endl;
		file.close();
		successcheck=1;
	}
	else if(strcmpi(mode,"cash")==0)
	{
		polygon(4,pp3,1,1);
		outtextxy(130,216,"Amount Paid");
		polygon(4,pp4,1,1);
		outtextxy(130,247,"Balance");
		clearslot(37,15);
		cout<<"|";
		gotoxy(37,15);
		cin>>paidamt;
		gotoxy(37,17);
		cout<<(paidamt-total);
		getch();
		successcheck=1;
	}
	if(variable==1)
	{
		variable=0;
		zpoints=total/10;
		zupdate();
		total=0;
	}
	cleardevice();
	defaultdisplay();
	settextstyle(3,0,1);
	setcolor(3);
	outtextxy(200,240,"Your bill is being printed...");
	gotoxy(52,25);
	sleep(3);
	return;
}

void cbc(char a[],int x,int y)
{
	int i=0;

	start:
	clearslot(x+i,y);
	for(;a[i-1]!='\r';i++)
	{
		gotoxy(x+1+i,y);
		cout<<"  ";
		gotoxy(x+i,y);
		cout<<"|";
		a[i]=getche();
		if(a[0]=='\r')
		{
			goto end;
		}
		if(a[0]==32)
		{
			goto end;
		}
		if(i<0)
		{
			strcpy(a,'\0');
			i=0;
			goto start;
		}
		if(a[i]==8)
		{
			a[i]='\0';
			if(i>0)
			{
			a[i-1]='\0';
			i-=2;
			}
			else
			i--;
			continue;
		}
		else if(a[i]==27)
		{
			a[i]='\0';
			i--;
			continue;
		}
		if(a[i]=='\r')
		{
			i++;
			break;
		}
		gotoxy(x+i,y);
		cout<<a[i];
		cout<<"|";
	}
	a[i-1]='\0';
	end:
	gotoxy(x+i-1,y);
	cout<<" ";
}

void nbn(int &variable,int x,int y)
{
	int i,count,flag=0,input,numeric[5];
	char num[5];

	up:
	variable=0;
	cbc(num,x,y);
	for(i=0;num[i]!='\0';i++)
	{
		if(!(isdigit(num[i])))
		{
			flag=1;
		}
	}
	if(flag==1)
	{
		for(i=0;num[i]!='\0';i++)
			num[i]='\0';
		flag=0;
		goto up;
	}
	for(count=0;num[count]!='\0';count++);
	for(input=0;input<count;input++)
		numeric[input]=((int)num[input])-48;
	for(input=count-1;input>=0;input--)
		variable+=(pow(10,input)*numeric[count-input-1]);
}

void billing()
{
	product p;
	int m,i,amount=0,loc,l=0,k,j,qty[100],prodcode[100],rate;
	char options[][100]={"pay","up","down","create member","zlogin","home","command","exit"};
	char prodname[40],command[50];
	ifstream file;

	int pperase[]={101,278,230,278,230,480,101,480,101,279};
	int polypoints2[]={500,12,618,12,618,40,500,40,500,12};
	int polypoints[]={0,85,635,85,635,115,0,115,0,85};
	int polypoints0[]={0,350,100,350,100,370,0,370,0,350};

	top:
	cleardevice();
	setcolor(9);
	defaultdisplay();
	polygon(4,polypoints2,1,1);
	settextstyle(3,0,1);
	setcolor(15);
	outtextxy(535,10,"Billing");
	total=0;
	gotoxy(1,7);
	setcolor(6);
	polygon(4,polypoints,1,12);
	settextstyle(6,0,1);
	setcolor(11);
	outtextxy(2,85,"NO.");
	outtextxy(40,85,"PRODUCT CODE");
	outtextxy(185,85,"PRODUCT NAME");
	outtextxy(415,85,"RATE");
	outtextxy(500,85,"QTY");
	outtextxy(560,85,"AMOUNT");
	gotoxy(55,22);
	cout<<"NET AMOUNT: "<<total;
	gotoxy(0,24);

	replay:
	setcolor(6);
	polygon(4,polypoints0,1,12);
	settextstyle(6,0,1);
	setcolor(11);
	outtextxy(10,345,"Command");
	gotoxy(3,25);
	setcolor(6);
	datetime();
	for(i=0;;i++)
	{
		if(i!=0)
		{
			gotoxy(1,i+8+l);
			cout<<" ";
		}

		restart:
		clearslot(15,23);
		cbc(command,15,23);
		clearslot(15,23);
		if(command[0]==32)
		{
			command[0]='\0';
			dropdownbox(options,101,300,15,command);
		}
		if(strcmpi(command,"pay")==0)
		{
			for(i=0;prodcode[i]!='\0';i++)
			{
				stockupdate(qty[i],prodcode[i]);
				prodcode[i]='\0';
				qty[i]='\0';
			}
			pay();
			total=0;
			i=0;
			goto top;
		}
		else if(strcmpi(command,"command")==0)
		{
			setcolor(0);
			polygon(4,pperase,1,0);
			goto replay;
		}
		else if(strcmpi(command,"prodhelp")==0)
		{
			prodhelp();
			total=0;
			i=0;
			goto top;
		}
		else if(strcmpi(command,"help")==0)
		{
			helpprint(320);
			setcolor(3);
			settextstyle(2,0,6);
			outtextxy(70,130,"To pay the bill");
			outtextxy(470,130,"pay");
			outtextxy(70,150,"To clear the existing bill");
			outtextxy(470,150,"clear");
			outtextxy(70,170,"Pay using zpoints");
			outtextxy(470,170,"zlogin");
			outtextxy(70,190,"Register a member in Zpoints");
			outtextxy(470,190,"create member");
			outtextxy(70,210,"Go to the previous billing page");
			outtextxy(470,210,"up");
			outtextxy(70,230,"Go to the next billing page");
			outtextxy(470,230,"down");
			outtextxy(70,250,"Access the list of products");
			outtextxy(470,250,"prodhelp");
			outtextxy(70,270,"Goto the homepage");
			outtextxy(470,270,"home");
			outtextxy(70,290,"Exit the software");
			outtextxy(470,290,"exit");
			outtextxy(120,320,"Drop-down box can be accessed using spacebar");
			getch();
			total=0;
			i=0;
			goto top;
		}
		else if(strcmpi(command,"clear")==0)
		{
			total=0;
			i=0;
			goto top;
		}
		else if(strcmpi(command,"home")==0)
		{
			homepage();
		}
		else if(strcmpi(command,"exit")==0)
		{
			credits();
		}
		else if(strcmpi(command,"create member")==0)
		{
			membercreate();
			total=0;
			i=0;
			goto top;
		}
		else if(strcmpi(command,"zlogin")==0)
		{
			for(i=0;prodcode[i]!='\0';i++)
			{
				stockupdate(qty[i],prodcode[i]);
				prodcode[i]='\0';
				qty[i]='\0';
			}
			zpay();
			i=0;
			total=0;
			goto top;
		}
		else if(strcmpi(command,"up")==0)
		{
			loc=((loc/12)-1)*12;
			clearbill();
			for(m=0;m<12;m++)
			{
				gotoxy(3,m+9);
				cout<<loc+1;
				gotoxy(12,m+9);
				cout<<prodcode[loc];
				file.open("LIST.dat",ios::binary);
				file.read((char*)&p,sizeof(p));
				while(!file.eof())
				{
					if(p.prodcode==prodcode[loc])
						break;
					else
						file.read((char*)&p,sizeof(p));
				}
				gotoxy(24,m+9);
				cout<<p.prodname;
				gotoxy(54,m+9);
				file.close();
				cout<<p.rate;
				gotoxy(65,m+9);
				cout<<qty[loc];
				rate=p.rate;
				amount=rate*qty[loc];
				gotoxy(72,m+9);
				cout<<amount;
				loc++;
			}
			loc-=12;
			i--;
		}
		else if(strcmpi(command,"down")==0)
		{
			loc+=12;
			clearbill();
			for(m=0;prodcode[loc]!='\0' && m<12;m++)
			{
				gotoxy(3,m+9);
				cout<<loc+1;
				gotoxy(12,m+9);
				cout<<prodcode[loc];
				file.open("LIST.dat",ios::binary);
				file.read((char*)&p,sizeof(p));
				while(!file.eof())
				{
					if(p.prodcode==prodcode[loc])
						break;
					else
						file.read((char*)&p,sizeof(p));
				}
				gotoxy(24,m+9);
				cout<<p.prodname;
				gotoxy(54,m+9);
				file.close();
				cout<<p.rate;
				gotoxy(65,m+9);
				cout<<qty[loc];
				rate=p.rate;
				amount=rate*qty[loc];
				gotoxy(72,m+9);
				cout<<amount;
				loc++;
			}
			loc-=12;
			i--;
			if(prodcode[loc+12]=='\0')
				loc=i+1;
		}
		else
		{
			loc=i+1;
			clearslot(14,24);
			gotoxy(3,25);
			setcolor(6);
			datetime();
			gotoxy(1,i+9+l);
			cout<<">";
			gotoxy(3,i+9+l);
			cout<<i+1;

			reset:
			gotoxy(12,i+9+l);
			cout<<"                                                        ";
			nbn(prodcode[i],12,i+9+l);
			file.open("LIST.dat",ios::binary);
			file.read((char*)&p,sizeof(p));
			while(!file.eof())
			{
				if(p.prodcode==prodcode[i])
					break;
				else
					file.read((char*)&p,sizeof(p));
			}
			gotoxy(24,i+9+l);
			cout<<p.prodname;
			gotoxy(54,i+9+l);
			file.close();
			cout<<p.rate;
			if(p.rate<0)
				goto reset;
			clearslot(65,i+9+l);
			nbn(qty[i],65,i+9+l);
			rate=p.rate;
			amount=rate*qty[i];
			gotoxy(72,i+9+l);
			cout<<amount;
			total+=amount;
			gotoxy(55,22);
			cout<<"NET AMOUNT: "<<total;
			clearmemory(i,prodcode,qty);
			if((i+1)%12==0)
			{
				clearbill();
				l-=12;
			}
		}
	}
}

void clearmemory(int i,int prodcode[], int qty[])
{
	i++;

	for(;i<100;i++)
	{
		prodcode[i]='\0';
		qty[i]='\0';
	}
}

void homepage()
{
	char command[50];
	int x,y;
	char options[][100]={"billing","create account","workers","signin","view database","zpoints","command","exit"};

	int polypoints1[]={500,12,618,12,618,40,500,40,500,12};
	int polypoints0[]={194,129,406,129,406,298,194,298,194,129};
	int polypoints[]={200,135,400,135,400,165,200,165,200,135};
	int polypoints2[]={200,167,400,167,400,195,200,195,200,167};
	int polypoints3[]={200,197,400,197,400,228,200,228,200,197};
	int polypoints4[]={200,230,400,230,400,260,200,260,200,230};
	int polypoints5[]={200,262,400,262,400,292,200,292,200,262};
	int polypointsc[]={0,350,100,350,100,370,0,370,0,350};

	start2:
	clrscr();
	cleardevice();
	setcolor(9);
	defaultdisplay();
	polygon(4,polypoints1,1,1);
	settextstyle(3,0,1);
	setcolor(15);
	outtextxy(520,10,"Homepage");
	setcolor(0);
	if(strlen(operatorname)!=0)
	strcpy(options[3],"signout");
	polygon(4,polypoints0,1,1);
	polygon(4,polypoints,1,12);
	polygon(4,polypoints2,1,12);
	polygon(4,polypoints3,1,12);
	polygon(4,polypoints4,1,12);
	polygon(4,polypoints5,1,12);
	settextstyle(6,0,1);
	setcolor(11);
	gotoxy(27,10);
	cout<<"";
	gotoxy(27,12);
	cout<<"";
	gotoxy(27,14);
	cout<<"";
	gotoxy(27,16);
	cout<<"";
	gotoxy(27,18);
	cout<<"";
	outtextxy(227,135,"Billing");
	outtextxy(227,167,"ZPoints");
	outtextxy(227,199,"Create Account");
	outtextxy(227,232,"View Database");
	outtextxy(227,266,"Exit");
	setcolor(6);
	gotoxy(3,25);
	datetime();
	for(;;)
	{
		start1:
		gotoxy(0,22);
		polygon(4,polypointsc,1,12);
		settextstyle(6,0,1);
		setcolor(15);
		outtextxy(10,345,"Command");
		clearslot(15,23);
		cbc(command,15,23);
		clearslot(15,23);
		if(command[0]=='\r')
		{
			command[0]='\0';
			dropdownbox(options,101,280,15,command);
		}
		if(strcmpi(command,"create account")==0)
		{
			createaccount();
			goto start2;
		}
		else if(strcmpi(command,"command")==0)
		{
			goto start2;
		}
		else if(strcmpi(command,"help")==0)
		{
			helpprint(290);
			setcolor(3);
			settextstyle(2,0,6);
			outtextxy(70,130,"To create a worker account");
			outtextxy(470,130,"create account");
			outtextxy(70,150,"To bill new products");
			outtextxy(470,150,"billing");
			outtextxy(70,170,"To signout of the current user account");
			outtextxy(470,170,"signout");
			outtextxy(70,190,"To sign into an account");
			outtextxy(470,190,"signin");
			outtextxy(70,210,"To view Zpoints customer details");
			outtextxy(470,210,"zpoints");
			outtextxy(70,230,"View shop's database");
			outtextxy(470,230,"down");
			outtextxy(70,250,"view database");
			outtextxy(470,250,"home");
			outtextxy(70,270,"Worker details");
			outtextxy(470,270,"workers");
			outtextxy(70,290,"Exit the software");
			outtextxy(470,290,"exit");
			getch();
			goto start2;
		}
		else if(strcmpi(command,"exit")==0)
		{
			credits();
		}
		else if(strcmpi(command,"workers")==0)
		{
			workers();
			goto start2;
		}
		else if(strcmpi(command,"billing")==0)
		{
			if(strcmp(operatorname,'\0')==0)
			{
				if(authenticator(0,1)==1)
				{
					billing();
				}
				else
				{
					goto start2;
				}
			}
			else
			{
				billing();
			}
		}
		else if(strcmpi(command,"signout")==0)
		{
			strcpy(operatorname,'\0');
			homepage();
		}
		else if(strcmpi(command,"signin")==0)
		{
			if(authenticator(0,1))
			{
				goto start2;
			}
			else
				goto start2;
		}
		else if(strcmpi(command,"zpoints")==0)
		{
			zhome();
		}
		else if(strcmpi(command,"view database")==0)
		{
			if(strcmp(operatorname,'\0')==0)
			{
				if(authenticator(0,1)==1)
				{
					viewdatabase();
				}
				else
				{
					goto start2;
				}
			}
			else
			{
				viewdatabase();
			}
		}
		else
		{
			goto start1;
		}
	}

}

void createaccount()
{
	account p;
	ofstream outfile;

	int polypoints1[]={450,12,618,12,618,40,450,40,450,12};
	int pp1[]={190,150,300,150,300,220,190,220,190,150};
	int pp2[]={180,140,185,140,185,230,180,230,180,140};
	int pp3[]={180,140,450,140,450,145,180,145,180,140};
	int pp4[]={445,140,445,230,450,230,450,140,445,140};
	int pp5[]={180,230,450,230,450,225,180,225,180,230};
	int pp[]={20,290,600,290,600,390,20,390,20,290};

	clrscr();
	cleardevice();
	setcolor(9);
	defaultdisplay();
	outfile.open("accdet.dat",ios::binary|ios::app);
	polygon(4,polypoints1,1,1);
	settextstyle(3,0,1);
	setcolor(15);
	outtextxy(470,10,"Create Account");
	polygon(4,pp3,2,3);
	polygon(4,pp5,2,3);
	polygon(4,pp4,2,3);
	polygon(4,pp2,2,3);
	polygon(4,pp1,1,1);
	setcolor(10);
	settextstyle(3,0,1);
	outtextxy(200,153,"USERNAME");
	outtextxy(200,185,"PASSWORD");
	setcolor(10);
	settextstyle(2,0,5);
	polygon(4,pp,1,1);
	outtextxy(30,300,"--> Maximum character length for username and password : 10 characters");
	outtextxy(30,320,"--> Password can contain numbers, characters or spaces");
	outtextxy(30,340,"--> Only staff accounts can be created");
	outtextxy(30,360,"--> Spaces are not allowed");
	cbc(p.username,40,11);
	decoder(p.password,40,13);
	p.tag=0;
	outfile.write((char*)&p,sizeof(p));
	outfile.close();
	personalinfo(p);
	return;
}

void personalinfo(account p)
{
	ofstream outfile;
	char name[50],command[50];
	int age;
	long salary;

	int pp1[]={125,155,270,155,270,181,125,181,125,155};
	int pp2[]={125,187,270,187,270,212,125,212,125,187};
	int pp3[]={125,218,270,218,270,243,125,243,125,218};
	int pp6[]={110,140,115,140,115,260,110,256,110,140};
	int pp7[]={110,140,500,140,500,145,110,145,110,140};
	int pp8[]={495,140,495,260,500,260,500,140,495,140};
	int pp9[]={110,260,500,260,500,255,110,255,110,260};

	clrscr();
	cleardevice();
	setcolor(9);
	defaultdisplay();
	gotoxy(30,8);
	settextstyle(4,0,3);
	setcolor(7);
	outtextxy(150,95,"PERSONAL INFORMATION");
	setcolor(11);
	polygon(4,pp6,2,3);
	polygon(4,pp8,2,3);
	polygon(4,pp9,2,3);
	polygon(4,pp7,2,3);
	polygon(4,pp1,1,12);
	polygon(4,pp2,1,12);
	polygon(4,pp3,1,12);
	setcolor(11);
	settextstyle(3,0,2);
	outtextxy(132,154,"Name");
	outtextxy(132,185,"Age");
	outtextxy(132,215,"Salary");
	cbc(name,36,11);
	gotoxy(36,13);
	cout<<"|";
	gotoxy(36,13);
	cin>>age;
	gotoxy(36,15);
	cout<<"|";
	gotoxy(36,15);
	cin>>salary;
	outfile.open("details.txt",ios::ate);
	outfile<<p.username<<"\n"<<name<<"\n"<<age<<"\n"<<salary<<"\n";
	outfile.close();

	start2:
	clrscr();
	cleardevice();
	gotoxy(25,12);
	settextstyle(3,0,3);
	setcolor(5);
	outtextxy(150,180,"ACCOUNT CREATION SUCCESSFUL!");
	sleep(2);
	return;
}

void main()
{
	clrscr();
	initgraph(&gd,&gm,add);
	motion();
}