
//****************************************************************
//	PROJECT COMPUTER QUIZ
//****************************************************************

//****************************************************************
//	INCLUDED HEADER FILES
//****************************************************************

#include <iostream.h>
#include <conio.h>
#include <dos.h>
#include <string.h>
#include <fstream.h>
#include <process.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include<time.h>


//*************************************************************************
//	CLASS NAME : lines
//	DETAILS    : IT CONTROLS FUNCTIONS RELATED TO
//			      DRAWING LINES, BOXES, ETC.
//*************************************************************************

class lines
{
	public :
		void line_hor (int,int,int,char);
		void line_ver (int,int,int,char);
		void box (int,int,int,int,char);
};


//*************************************************************************
//	CLASS NAME : menu
//	DETAILS    : IT CONTROLS ALL THE FUNCTIONS
//*************************************************************************

class menu
{
	private :
		void edit_menu(void);

	public :
		void main_menu(void);
		char *sub_menu(void);
		void start(void);
};


//*************************************************************************
//	CLASS NAME : quiz
//	DETAILS    : IT CONTROLS ALL THE FUNCTIONS
//                            RELATED TO QUIZ
//*************************************************************************

class quiz
{
	private :
		int  ques_no;
		char question[100];
		char answer1[50];
		char answer2[50];
		char answer3[50];
		char solution;
		void delete_record(char filename[13],int);
		void modify_record(char filename[13],int);
		void display_score(char name[20],int,int);
		int recordno(char filename[13],int);
		int record_count(char filename[13]);
		int found_record(char filename[13],int);
		void display_record(char filename[13],int);

	public :
		void play(char filename[13]);
		void add(char filename[13]);
		void deletion(char filename[13]);
		void modify(char filename[13]);

};


//*************************************************************************
//	CLASS NAME    : lines
//	FUNCTION NAME : line_hor
//	DETAILS       : IT ACCEPTS THE ROWS AND COLUMNS
//				 AND DRAW THE HORIZONTAL LINE
//*************************************************************************

void lines::line_hor(int col1,int col2,int row,char c)
{
	for(col1;col1<=col2;col1++)
	{
		gotoxy(col1,row);
		cout <<c;
	}
}


//*************************************************************************
//	CLASS NAME    : lines
//	FUNCTION NAME : line_ver
//	DETAILS       : IT ACCEPTS THE ROWS AND COLUMNS
//	                        AND  DRAW THE VERTICAL LINE
//*************************************************************************

void lines::line_ver(int row1,int row2,int col,char c)
{
	for (row1;row1<=row2;row1++)
	{
		gotoxy(col,row1);
		cout<<c;
	}
}

//*************************************************************************
//	CLASS NAME    : lines
//	FUNCTION NAME : box
//	DETAILS       : IT ACCEPTS THE ROWS AND COLUMNS
//                  		 AND DRAW THE BOX
//*************************************************************************

void lines::box(int column1,int row1,int column2,int row2,char c)
{
	char ch=218;
	char c1,c2,c3,c4;
	char l1=196,l2=179;
	if (c==ch)
	{
		c1=218;
		c2=191;
		c3=192;
		c4=217;
		l1=196;
		l2=179;
	}
	else
	{
		c1=c;
		c2=c;
		c3=c;
		c4=c;
		l1=c;
		l2=c;
	}
	gotoxy(column1,row1);
	cout<<c1;
	gotoxy(column2,row1);
	cout<<c2;
	gotoxy(column1,row2);
	cout<<c3;
	gotoxy(column2,row2);
	cout<<c4;
	column1++;
	column2--;
	line_hor(column1,column2,row1,l1);
	line_hor(column1,column2,row2,l1);
	column1--;
	column2++;
	row1++;
	row2--;
	line_ver(row1,row2,column1,l2);
	line_ver(row1,row2,column2,l2);
}


//*************************************************************************
//	CLASS NAME    : menu
//	FUNCTION NAME : start
//	DETAILS       : IT CREATES THE OPENING SCREEN
//*************************************************************************

void menu::start(void)
{
	lines line;
	clrscr();
	textmode(C40);
	clrscr();
	clrscr();
	gotoxy(2,2);
	cout <<"KAUN BANEGA CROREPATI";
	gotoxy(19,12);
	cout <<"\nREAL CHALLENGE OF UR LIFE";
	gotoxy(8,14);
	cout<<" \tBY: ";
	delay(1000);

	gotoxy(10,16);

	cout<<"\tASHISH,ANAND,VAISAKH";
	cout<<"\tCLASS XII-B";
	delay(600);

	gotoxy(5,22);
	cout<<"PLEASE WAIT WHILE LOADING ........ ";
	sleep(2);
}


//*************************************************************************
//	CLASS NAME    : menu
//	FUNCTION NAME : main_menu
//	DETAILS       : IT CREATES THE MAIN MENU TO
// 				 CONTROL ALL THE FUNCTIONS
//*************************************************************************

void  menu::main_menu(void)
{
	lines line;
	textmode(C40);
	char k;
	do
	{

		clrscr();
		textbackground(LIGHTGRAY);
		textcolor(GREEN);
		clrscr();

		line.line_hor(9,35,6,196);
		line.box (8,3,35,19,218);
		gotoxy(3,23);

		cout<<" <0>=Exit";

		gotoxy(18,5);
		cout<<"Q U I Z ";
		textbackground(BLUE);
		textcolor(YELLOW);
		gotoxy(18,8);
		cout<<"OPTIONS";
		gotoxy(18,9);
		cout<<"-------";
		gotoxy(14,11);
		cout<<"1. PLAY";
		gotoxy(14,12);
		cout<<"2. ADD QUESTIONS";
		gotoxy(14,13);
		cout<<"3. EDIT";
		line.box(1,1,39,25,219);
		gotoxy(14,16);
		cout<<"ENTER YOUR CHOICE";
		gotoxy(32,16);
		k=getch();
		if(k=='0')
			return;
		if(k=='1')
		{
			char filename[13];
			strcpy(filename,sub_menu());
			if (strcmp(filename,"null"))
			{
				quiz q;
				q.play(filename);
				clrscr();
			}
		}


		if(k=='2')
		{
			char filename[13];
			strcpy(filename,sub_menu());
			if(strcmp(filename,"null"))
			{
				textmode(C80);
				clrscr();
				quiz q;
				q.add(filename);
				textmode(C40);
				clrscr();
			}
		}

		if (k=='3')
			edit_menu();


	}while(k!=3);
	clrscr();
}


//*************************************************************************
//	CLASS NAME    : menu
//	FUNCTION NAME : edit_menu
//	DETAILS       : IT CREATES THE EDIT MAIN MENU
//*************************************************************************

void menu::edit_menu(void)
{
	lines line;
	char k=1;
	do
	{
		clrscr();
		line.box(2,2,38,24,218);
		textbackground(WHITE);
		textcolor(BLACK);
		gotoxy(6,5);
		cout<<"E D I T ";
		textbackground(BLUE);
		textcolor(YELLOW);
		gotoxy(6,8);
		cout<<"1. DELETE";
		gotoxy(6,9);
		cout<<"2. MODIFY";
		gotoxy(6,10);
		cout<<"3. RETURN";
		line.box(1,1,39,25,219);
		gotoxy(1,27);
		clreol();
		gotoxy(6,12);
		cout<<"ENTER YOUR CHOICE";
		gotoxy(25,12);
		k=getch();
		if(k=='0')
			return;
		if(k=='1')
		{
			char filename[13];
			strcpy(filename,sub_menu());
			if (strcmp(filename,"null"))
			{
				textmode(C80);
				clrscr();
				quiz q;
				q.deletion(filename);
				textmode(C40);
				clrscr();
				return;
			}
			clrscr();
			return;
		}
		else if(k=='2')
		{
			char filename[13];
			strcpy(filename,sub_menu());
			if (strcmp(filename,"null"))
			{
				textmode(C80);
				clrscr();
				quiz q;
				q.modify(filename);
				textmode(C40);
				clrscr();
				return;
			}
			clrscr();
			return;
		}
	}while(k!='3');
}


//*************************************************************************
//	CLASS NAME    : menu
//	FUNCTION NAME : sub_menu
//	DETAILS       : IT CREATES THE SUB MAIN MENU AND
//                               RETURN FILE NAME
//*************************************************************************

char *menu::sub_menu(void)
{
	lines line;
	clrscr();
	char k=1;
	line.box(1,1,39,25,219);
	line.line_hor(2,38,23,196);
	textbackground(BLACK);
	textcolor(GREEN);
	clrscr();
	gotoxy(14,6);
	cout<<"S U B - M E N U ";
	textbackground(BLACK);
	textcolor(LIGHTGRAY);
	line.box(11,5,31,7,218);
	gotoxy(14,10);
	cout<<"1. COMPUTERS";
	gotoxy(14,12);
	cout<<"2. MATHEMATICS";
	gotoxy(14,14);
	cout<<"3. SCIENCE";
	gotoxy(14,16);
	cout<<"4. GENERAL";
	gotoxy(14,18);
	cout<<"5. RETURN";
	gotoxy(14,20);
	line.box(1,1,39,25,219);
	gotoxy(14,20);
	cout<<"ENTER YOUR CHOICE";
	gotoxy(32,20);
	k=getch();
	if(k=='0')
	     return("null");

	clrscr();
	if(k=='1')
		return("computer.dat");
	else if(k=='2')
		return("maths.dat");
	else if(k=='3')
		return("science.dat");
	else if(k=='4')
		return("general.dat");
	else
		return("null");


}


//*************************************************************************
//	CLASS NAME    : quiz
//	FUNCTION NAME : record_count
//	DETAILS       : IT RETURNS THE NO. OF RECORD IN THE
//      		 GIVEN FILE
//*************************************************************************

int  quiz::record_count(char filename[13])
{
	fstream file;
	file.open(filename, ios::in);
	file.seekg(0,ios::beg);
	int t_ques_no=0;
	while(file.read((char*)this,sizeof(quiz)))
		t_ques_no++;
	file.close();
	return t_ques_no;
}


//*************************************************************************
//	CLASS NAME    : quiz
//	FUNCTION NAME : add
//	DETAILS       : IT ADDS THE RECORDS IN THE GIVEN
//                               FILE
//*************************************************************************

void quiz::add(char filename[13])
{
	lines line;
	int valid;
	int t_ques_no;
	t_ques_no=record_count(filename);
	t_ques_no++;
	char ch;
	do
	{
		clrscr();
		textbackground(GREEN);
		textcolor(LIGHTGRAY);
		clrscr();
		line.box(1,1,80,20,218);
		gotoxy(3,5);
		cout<<"Question # "<<t_ques_no;
		gotoxy(3,8);
		cout<<"Question : ";
		gotoxy(3,10);
		cout<<"Answer 1 : ";
		gotoxy(3,12);
		cout<<"Answer 2 : ";
		gotoxy(3,14);
		cout<<"Answer 3 : ";
		gotoxy(3,16);
		cout<<"Solution : ";
		do
		{
			line.box(1,1,80,20,218);
			valid=1;
			gotoxy(72,24);
			cout<<"<0>=EXIT";
			gotoxy(3,24);
			cout<<"ENTER QUESTION";
			gotoxy(14,8);
			gets(question);
			strupr(question);
			if(question[0]=='0')
				return;
			if(strlen(question)>99 || strlen(question)==0)
			{
				valid=0;
				gotoxy(1,22);
				cout<<"LENGTH SHOULD NOT BE GREATER THAN 99";
				gotoxy(1,24);
				cout<<"Press any key to continue...";
				getch();
				gotoxy(1,24);
				clreol();
				gotoxy(1,22);
				clreol();
				gotoxy(14,8);
				clreol();
			}
		}while(!valid);
		do
		{
			line.box(1,1,80,20,218);
			valid=1;
			gotoxy(72,24);
			cout<<"<0>=EXIT";
			gotoxy(3,24);
			clreol();
			gotoxy(3,24);
			cout<<"ENTER ANSWER FOR THE QUESTION";
			gotoxy(14,10);
			gets(answer1);
			strupr(answer1);
			if(answer1[0]=='0')
				return;
			if(strlen(answer1)>49 || strlen(answer1)==0)
			{
				valid=0;
				gotoxy(3,24);
				clreol();
				gotoxy(1,22);
				cout<<"LENGTH SHOULD NOT BE GREATER THAN 49";
				gotoxy(1,24);
				cout<<"Press any key to continue...";
				getch();
				gotoxy(1,24);
				clreol();
				gotoxy(1,22);
				clreol();
				gotoxy(14,10);
				clreol();
			}
		}while(!valid);
		do
		{
			line.box(1,1,80,20,218);
			valid=1;
			gotoxy(72,24);
			cout<<"<0>=EXIT";
			gotoxy(3,24);
			clreol();
			gotoxy(3,24);
			cout<<"ENTER ANSWER FOR THE QUESTION";
			gotoxy(14,12);
			gets(answer2);
			strupr(answer2);
			if(answer2[0]=='0')
				return;
			if(strlen(answer2)>49 || strlen(answer2)==0)
			{
				valid=0;
				gotoxy(3,24);
				clreol();
				gotoxy(1,22);
				cout<<"LENGTH SHOULD NOT BLANK GREATER THAN 49";
				gotoxy(1,24);
				cout<<"Press any key to continue...";
				getch();
				gotoxy(1,24);
				clreol();
				gotoxy(1,22);
				clreol();
				gotoxy(14,12);
				clreol();
			}
		}while(!valid);
		do
		{
			line.box(1,1,80,20,218);
			valid=1;
			gotoxy(72,24);
			cout<<"<0>=EXIT";
			gotoxy(3,24);
			clreol();
			gotoxy(3,24);
			cout<<"ENTER ANSWER FOR THE QUESTION";
			gotoxy(14,14);
			gets(answer3);
			strupr(answer3);
			if(answer3[0]=='0')
				return;
			if(strlen(answer3)>49 || strlen(answer3)==0)
			{
				valid=0;
				gotoxy(3,24);
				clreol();
				gotoxy(1,22);
				cout<<"LENGTH SHOULD NOT BLANK GREATER THAN 49";
			    gotoxy(1,24);
				cout<<"Press any key to continue...";
				getch();
				gotoxy(1,24);
				clreol();
				gotoxy(1,22);
				clreol();
				gotoxy(14,14);
				clreol();
			}
		}while(!valid);
		do
		{
			line.box(1,1,80,20,218);
			valid=1;
			gotoxy(72,24);
			cout<<"<0>=EXIT";
			gotoxy(3,24);
			clreol();
			gotoxy(3,24);
			cout<<"ENTER CORRECT SOLUTION FOR THE"
			       <<" QUESTION (1/2/3)" ;
			gotoxy(14,16);
			solution=getche();
			if(solution=='0')
				return;
			if (solution != '1' && solution != '2' && solution != '3')
			{
				valid=0;
				gotoxy(14,16);
				clreol();
			}
		}while(!valid);
		gotoxy(1,22);
		clreol();
		gotoxy(72,24);
		cout<<"<0>=EXIT";
		gotoxy(3,19);
		cout<<"Do you want to save the record (y/n) : ";
		cin>>ch;
		ch=toupper(ch);
		if(ch=='Y')
		{
			ques_no=t_ques_no;
			fstream file;
			file.open(filename,ios::app);
			file.write((char *)this,sizeof(quiz));
			file.close();
			t_ques_no++;
		}
		gotoxy(72,24);
		cout<<"<0>=EXIT";
		gotoxy(3,21);
		cout<<"Do you want to add more questions (y/n) : ";
		cin>>ch;
		ch=toupper(ch);
	}while(ch=='Y');

}



//*************************************************************************
//	CLASS NAME    : quiz
//	FUNCTION NAME : found_record
//	DETAILS       : IT SEARCH THE GIVEN RECORDS IN THE
//                      		 GIVEN FILE AND RETURN 0 IF NOT FOUND
//*************************************************************************

int quiz::found_record(char filename[13],int t_ques_no)
{
	fstream file;
	file.open(filename,ios::in);
	file.seekg(0,ios::beg);
	int found=0;
	while(file.read((char *)this,sizeof(quiz)))
	{
		if(t_ques_no==ques_no)
		{
			found++;
			break;
		}
	}
	file.close();
	return found;
}



//*************************************************************************
//	CLASS NAME    : quiz
//	FUNCTION NAME : display_record
//	DETAILS       : IT DISPLAY THE RECORD FOR THE GIVEN
//                      		 QUESTION NO. FROM THE GIVEN FILE
//*************************************************************************

void quiz::display_record(char filename[13],int t_ques_no)
{
	fstream file;
	file.open(filename,ios::in);
	file.seekg(0,ios::beg);
	while(file.read((char*)this,sizeof(quiz)))
	{
		if(t_ques_no==ques_no)
		{
			gotoxy(3,3);
			cout<<"Question # "<<t_ques_no;
			gotoxy(3,5);
			cout<<"Question : "<<question;
			gotoxy(3,6);
			cout<<"Answer 1 : "<<answer1;
			gotoxy(3,7);
			cout<<"Answer 2 : "<<answer2;
			gotoxy(3,8);
			cout<<"Answer 3 : "<<answer3;
			break;
		}
	}
	file.close();
}


//*************************************************************************
//	CLASS NAME    : quiz
//	FUNCTION NAME : delete_record
//	DETAILS       : IT DELETE THE RECORD FOR THE GIVEN
//                      QUESTION NO. FROM THE GIVEN FILE
//*************************************************************************

void quiz::delete_record(char filename[13],int t_ques_no)
{
	fstream file;
	file.open(filename,ios::in);
	fstream temp;
	temp.open("temp.dat",ios::out);
	file.seekg(0,ios::beg);
	while(!file.eof())
	{
		file.read((char*)this,sizeof(quiz));
		if(file.eof())
			break;
		if(ques_no!=t_ques_no)
		{
			if(ques_no>t_ques_no)
			{
				ques_no-=1;
			}
			temp.write((char*)this,sizeof(quiz));
		}
	}
	remove(filename);
	rename("temp.dat",filename);
	file.close();
	temp.close();
}



//*************************************************************************
//	CLASS NAME    : quiz
//	FUNCTION NAME : deletion
//	DETAILS       : IT GIVE THE QUESTION NO. TO DELETE
//                      		 RECORD FROM THE GIVEN FILE
//*************************************************************************

void quiz::deletion(char filename[13])
{
	lines line;
	textbackground(RED+BLINK);
	textcolor(LIGHTGRAY);
	clrscr();
	int valid;
	int q;
	char ch;

	line.box(1,1,80,23,219);
	line.box(2,2,79,22,218);
	gotoxy(72,24);
	cout<<"<0>=EXIT";
	gotoxy(4,4);
	cout<<"Enter Question no. to be deleted : ";
	cin>>q;
	if(q=='0')
		return;
	if(!found_record(filename,q))
	{
		gotoxy(4,15);
		cout<<"Question not found";
		line.line_hor(3,79,24,196);
		gotoxy(4,25);
		cout<<"Press any key to continue...";
		getch();
		return;
	}
	clrscr();
	line.box(1,1,80,23,219);
	line.box(2,2,79,22,218);
	display_record(filename,q);
	gotoxy(3,10);
	cout<<"Do you want to delete this Record (y/n) : ";
	cin>>ch;
	ch=toupper(ch);
	if(ch=='N')
	{
		gotoxy(3,20);
		cout<<"O.K.";
		sleep(1);
		return;
	}
	else if(ch=='Y')
	{
		gotoxy(1,25);
		cout <<"Wait...";
		sleep(2);
		delete_record(filename,q);
		clrscr();
		gotoxy(3,14);
		cout<<"Record Deleted";
		line.line_hor(1,79,24,196);
		gotoxy(1,25);
		cout<<"Press any key to continue....";
		getch();
	}
	else
	{
	       gotoxy(3,14);
	       cout<<"Wrong choice";
	       gotoxy(1,25);
	       cout<<"Press any key to continue...";
	       getch();
	}
}
//*************************************************************************
//	CLASS NAME    : quiz
//	FUNCTION NAME : modify_record
//	DETAILS       : IT MODIFY THE RECORD FOR THE GIVEN
//                      		 QUESTION NO. FROM THE GIVEN FILE
//*************************************************************************

void quiz::modify_record(char filename[13],int q)
{
	lines line;
	int valid, modified=0;
	char ch;
	line.line_hor(2,78,12,196);
	line.box(1,1,79,23,218);
	gotoxy(3,14);
	cout<<"Question # "<<q;
	gotoxy(3,16);
	cout<<"Question : ";
	gotoxy(3,17);
	cout<<"Answer 1 : ";
	gotoxy(3,18);
	cout<<"Answer 2 : ";
	gotoxy(3,19);
	cout<<"Answer 3 : ";
	gotoxy(3,20);
	cout<<"Solution : ";
	gotoxy(72,25);
	cout<<"<0>=EXIT";
	line.line_hor(1,79,23,196);
	gotoxy(14,16);
	cout<<"Change (y/n)  ";
	do
	{
		line.box(1,1,79,23,218);
		valid=1;
		gotoxy(28,16);
		ch=getche();
		ch=toupper(ch);
		if(ch!='Y' && ch!='N')
		{
			valid=0;
			gotoxy(28,16);
			clreol();
		}
	}while(!valid);
	valid=0;
	while(!valid && ch=='Y')
	{
		line.box(1,1,79,23,218);
		modified=1;
		valid=1;
		gotoxy(14,16);
		clreol();
		gotoxy(72,25);
		cout<<"<0>=EXIT";
		gotoxy(3,25);
		cout<<"ENTER QUESTION";
		gotoxy(14,16);
		gets(question);
		strupr(question);
		if(question[0]=='0')
			return;
		if(strlen(question)>59 || strlen(question)== 0)
		{
			valid=0;
			gotoxy(1,25);
			clreol();
			gotoxy(1,24);
			cout<<"LENGTH SHOULD NOT BLANK OR"
			       <<" GREATER THAN 59";
			gotoxy(1,25);
			cout<<"Press any key to continue...";
			getch();
			gotoxy(1,24);
			clreol();
			gotoxy(1,25);
			clreol();
			gotoxy(14,16);
			clreol();
		}
	}
	gotoxy(1,25);
	clreol();
	gotoxy(14,17);
	cout<<"Change (y/n)  ";
	do
	{
		line.box(1,1,79,23,218);
		valid=1;
		gotoxy(28,17);
		ch=getche();
		ch=toupper(ch);
		if(ch!='Y' && ch!='N')
		{
			valid=0;
			gotoxy(28,17);
			clreol();
		}
	}while(!valid);
	valid=0;
	while(!valid && ch=='Y')
	{
		line.box(1,1,79,23,218);
		modified=1;
		valid=1;
		gotoxy(13,17);
		clreol();
		gotoxy(72,25);
		cout<<"<0>=EXIT";
		gotoxy(3,25);
		cout<<"ENTER ANSWER FOR THE QUESTION";
		gotoxy(14,17);
		gets(answer1);
		strupr(answer1);
		if(answer1[0]=='0')
			return;
		if(strlen(answer1)>49)
		{
			valid=0;
			gotoxy(1,25);
			clreol();
			gotoxy(1,24);
			cout<<"LENGTH SHOULD NOT GREATER THAN"
			       <<" 49";
			gotoxy(1,25);
			cout<<"Press any key to continue...";
			getch();
			gotoxy(1,24);
			clreol();
			gotoxy(1,25);
			clreol();
			gotoxy(14,17);
			clreol();
		}
	}
	gotoxy(1,25);
	clreol();
	gotoxy(14,18);
	cout<<"Change (y/n)  ";
	do
	{
		line.box(1,1,79,23,218);
		valid=1;
		gotoxy(28,18);
		ch=getche();
		ch=toupper(ch);
		if(ch!='Y' && ch!='N')
		{
			valid=0;
			gotoxy(28,18);
			clreol();
		}
	}while(!valid);
	valid=0;
	while(!valid && ch=='Y')
	{
		line.box(1,1,79,23,218);
		modified=1;
		valid=1;
		gotoxy(14,18);
		clreol();
		gotoxy(72,25);
		cout<<"<0>=EXIT";
		gotoxy(3,25);
		cout<<"ENTER ANSWER FOR THE QUESTION";
		gotoxy(14,18);
		gets(answer2);
		strupr(answer2);
		if(answer2[0]=='0')
			return;
		if(strlen(answer2)>49)
		{
			valid=0;
			gotoxy(1,25);
			clreol();
			gotoxy(1,24);
			cout<<"LENGTH SHOULD NOT GREATER THAN"
			       <<" 49";
			gotoxy(1,25);
			cout<<"Press any key to continue...";
			getch();
			gotoxy(1,24);
			clreol();
			gotoxy(1,25);
			clreol();
			gotoxy(14,18);
			clreol();
		}
	}
	gotoxy(1,25);
	clreol();
	gotoxy(14,19);
	cout<<"Change (y/n)  ";
	do
	{
		line.box(1,1,79,23,218);
		valid=1;
		gotoxy(28,19);
		ch=getche();
		ch=toupper(ch);
		if(ch!='Y' && ch!='N')
		{
			valid=0;
			gotoxy(28,19);
			clreol();
		}
	}while(!valid);
	valid=0;
	while(!valid && ch=='Y')
	{
		line.box(1,1,79,23,218);
		modified=1;
		valid=1;
		gotoxy(14,19);
		clreol();
		gotoxy(72,25);
		cout<<"<0>=EXIT";
		gotoxy(3,25);
		cout<<"ENTER ANSWER FOR THE QUESTION";
		gotoxy(14,19);
		gets(answer3);
		strupr(answer3);
		if(answer3[0]=='0')
			return;
		if(strlen(answer3)>49)
		{
			valid=0;
			gotoxy(1,25);
			clreol();
			gotoxy(1,24);
			cout<<"LENGTH SHOULD NOT GREATER THAN"
			       <<" 49";
			gotoxy(1,25);
			cout<<"Press any key to continue...";
			getch();
			gotoxy(1,24);
			clreol();
			gotoxy(1,25);
			clreol();
			gotoxy(14,19);
			clreol();
		}
	}
	if(!modified)
		return;
	do
	{
		line.box(1,1,79,23,218);
		gotoxy(1,25);
		clreol();
		valid=1;
		gotoxy(72,25);
		cout<<"<0>=EXIT";
		gotoxy(3,25);
		cout<<"ENTER CORRECT SOLUTION FOR THE"
		       <<" QUESTION (1/2/3)";
		gotoxy(14,20);
		solution=getche();
		if(solution=='0')
			return;
		if(solution!='1' && solution!='2' && solution!='3')
		{
			valid=0;
			gotoxy(14,20);
			clreol();
		}
	}while(!valid);
	gotoxy(1,25);
	clreol();
	gotoxy(1,24);
	clreol();
	gotoxy(2,22);
	cout<<"Do you want to save the record (y/n)  : ";
	do
	{
		line.box(1,1,79,23,218);
		valid=1;
		gotoxy(41,22);
		ch=getche();
		ch=toupper(ch);
		if(ch!='Y' && ch!='N')
		{
			valid=0;
			gotoxy(41,22);
			clreol();
		}
	}while(!valid);
	if(ch=='N')
		return;
	fstream file;
	file.open(filename,ios::out | ios::ate);
	int location;
	location= (q-1)*sizeof(quiz);
	file.seekp(location);
	file.write((char*)this,sizeof(quiz));
	file.close();
	clrscr();
	gotoxy(1,14);
	cout<<"Record Modified";
	line.line_hor(1,79,24,196);
	gotoxy(1,25);
	cout<<"Press any key to continue...";
	getch();
}


//*************************************************************************
//	CLASS NAME    : quiz
//	FUNCTION NAME : modify
//	DETAILS       : IT GIVE THE QUESTION NO. TO MODIFY
//                      		 RECORD FROM THE GIVEN FILE
//*************************************************************************

void quiz::modify(char filename[13])
{
	lines line;
	textbackground(RED+BLINK);
	textcolor(YELLOW);
	clrscr();

	int valid;
	int q;
	char ch;
	line.box(1,1,80,23,218);
	gotoxy(72,24);
	cout<<"<0>=EXIT";
	gotoxy(3,3);
	cout<<"Enter Question no. to be modify  : ";
	cin>>q;
	if(q=='0')
		return;
	if(!found_record(filename,q))
	{
		gotoxy(3,15);
		cout <<"Question not found";
		line.line_hor(3,70,24,196);
		gotoxy(3,24);
		cout<<"Press any key to continue...";
		getch();
		return;
	}
	clrscr();
	display_record(filename,q);
	gotoxy(3,10);
	cout<<"Do you want to modify this Record (y/n) : ";
	ch=getche();
	ch=toupper(ch);
	if(ch=='N')
		return;
	else if(ch=='Y')
		modify_record(filename,q);
	else
	{
		gotoxy(3,12);
		cout<<"Wrong choice !";
		getch();
		return;
	}
}


//*************************************************************************
//	CLASS NAME    : quiz
//	FUNCTION NAME : display_score
//	DETAILS       : IT DISPLAY THE SCORE FOR THE GIVEN
//                      		 PLAYER'S NAME
//*************************************************************************

void quiz::display_score(char name[20],int played,int correct)
{
	clrscr();
	lines line;
	textbackground(WHITE);
	textcolor(BROWN);
	clrscr();

	line.box(1,1,39,25,218);
	line.box(2,2,38,24,219);
	gotoxy(9,4);

	cout<<"S C O R E   B O A R D";
	line.line_hor(9,29,5,196);
	gotoxy(6,7);
	cout<<"Player's Name       : "<<name;
	gotoxy(6,9);
	cout<<"Questions Attempted : "<<played;
	gotoxy(6,11);
	cout<<"Correct Answer      : "<<correct;
	gotoxy(6,13);
	cout<<"Wrong Answer        : "<<played-correct;
	int score;
	score=correct * 10;
	gotoxy(6,16);
	cout<<"Score               : "<<score;
	int tplayed;
	tplayed= played * 10;
	float percentage;
	percentage= ((score*100)/tplayed);
	gotoxy(6,18);
	cout<<"Percentage          : "<<percentage;
	getch();
}


//*************************************************************************
//	CLASS NAME    : quiz
//	FUNCTION NAME : play
//	DETAILS       : IT CREATES SCREEN FOR PLAYING QUIZ
//                      		 TO THE PLAYER FOR THE GIVEN FILE
// 				 NAME AND KEEP SCORE.
//*************************************************************************

void quiz::play(char filename[13])
{
	clrscr();
	randomize();
	int valid;
	lines line;
	char name[20];
	do
	{
		clrscr();
		gotoxy(5,6);
		cout<<"Enter your name : ";

		line.box(1,1,39,25,219);
		valid=1;
		gotoxy(30,24);
		cout<<"<0>=EXIT";
		gotoxy(27,6);
		gets(name);
		strupr(name);
		if(name[0]=='0')
			return;

		if(strlen(name)>18)
		{
			valid=0;
			gotoxy(30,24);
			cout<<"        ";
			gotoxy(5,20);
			cout<<"LENGTH SHOULD NOT GREATER THAN"

			       <<" 18";
			gotoxy(5,22);
			cout<<"Press any key to continue...";
			getch();
		}
	}while(!valid);
	char t_sol,ch;
	int correct=0,played=0,gr=1;
	fstream file;
	file.open(filename,ios::in);
	file.seekg(0,ios::beg);

	if(file.read((char*)this,sizeof(quiz))=='\0')
	{
		gotoxy(3,20);
		cout<<" Question bank is empty...";
		sleep(2);
		return;
	}
	file.seekg(0,ios::beg);
	int qu;
	int h=1,qs[7],y;
	for(int p=1;p<7;++p)
	{
		cont:
		qu=random(6)+1;
		qs[h]=qu;
		for(y=1;y<h;++y)
			if(qu==qs[y])
				goto cont;

		++h;
		file.seekg(sizeof(quiz)*qu);
		file.read((char *) this, sizeof(quiz));

		clrscr();

		line.box(1,1,39,25,219);
		line.box(2,2,38,24,218);

		gotoxy(25,3);
		cout<<"SCORE:"<<correct*10;
		valid=1;
		gotoxy(28,23);
		cout<<"<ESC>=Exit";
		gotoxy(4,4);
		cout<<"Question # "<<correct+1;
		gotoxy(4,6);

		int i,j,k=6,flag=0;
		cout <<"Question : ";
		for(i=0;question[i]!='\0';)
		{
			if(flag==0)
			{
				flag=1;
				for(j=0;j<20 && question[i]!='\0';++j,++i)
					cout<<question[i];
			}
			else
			{
				gotoxy(15,k) ;
				for(j=0;j<20 && question[i]!='\0';++j,++i)
					cout<<question[i];
			}
			++k;
		}
		gotoxy(4,k);
		cout<<"Answer 1 : "<<answer1;
		gotoxy(4,k+1) ;
		cout<<"Answer 2 : "<<answer2;
		gotoxy(4,k+2);
		cout<<"Answer 3 : "<<answer3;
		gotoxy(4,k+4);
		cout<<"Enter correct solution : ";
		gotoxy(29,k+4);
		t_sol=getche();
		played++;
		if(t_sol!=solution)
		{
			if(t_sol==0)
			{
				gotoxy(14,14);
				cout<<"Aborting...";
				sleep(2);
				break;
			}
			gr=0;
			gotoxy(14,14);
			cout <<"WRONG ANSWER";
			gotoxy(13,16);
			cout<<"Correct Answer : "<<solution;
			getch();
			break;
		}

		else
		{
			correct++;
			gotoxy(12,14);
			cout<<"CONGRATES! IT'S CORRECT";
			gotoxy(25,3);
			cout<<"SCORE:"<<correct*10;
			getch();
		}
	}
	gotoxy(3,20);
	if(gr)
		cout<<"No more question available";
	gotoxy(3,22);
	cout<<"\t Calculating your scores...";
	sleep(2);

	display_score(name,played,correct);
}


//*************************************************************************
//	FUNCTION NAME : main
//	DETAILS       : IT CALLS THE START FUNCTION AND
//                      		 MENU FUNCTION.
//*************************************************************************

void main()
{
	menu m;
	m.start();
	m.main_menu();
	textcolor(YELLOW+BLINK);
	clrscr();
	gotoxy(15,13);
	textmode(C40);
	cout<<"G O O D  B Y E ";
	sleep(4);
}















