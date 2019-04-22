/* Copyright (C) 2015 Rakshit Joshi. */


/*  QuizMaster PRO - Version 1 */


#include <fstream.h>
#include <conio.h>
#include <stdio.h>
#include <string.h>
#include <process.h>


fstream file, temp; // For file manipulation
int flag, r1, r2, r3, ich;
char cch, check[42], name[42];


class ques // Defining the class to store questions
{

	private:
		char q[200], a[100], b[100], c[100], d[100];
		int ans;

	public:
		int retans() // Return private data member 'ans'
		{
			return ans;
		}

		void getq() // Function to enter question details
		{
			clrscr();
			cout << endl << "Enter the question: " << endl;
			gets(q);
			cout << endl << "Enter the options: "
				 << endl << "Option One: " << endl;
			gets(a);
			cout << endl << "Option Two: " << endl;
			gets(b);
			cout << endl << "Option Three: " << endl;
			gets(c);
			cout << endl << "Option Four: " << endl;
			gets(d);
			cout << endl << "Number of the correct option: " << endl;
			cin >> ans;
		}

		void showq() // Display question
		{
			cout <<endl<<"Question is..."
				 << endl << q
				 << endl << endl << "Options are..."
				 << endl << "1. " << a
				 << endl << "2. " << b
				 << endl << "3. " << c
				 << endl << "4. " << d <<endl;
		}
} q1, q2;


class user // Class to store user details
{

	private:
		char nm[42], sex;
		int  age;

	public:
		int score, pass;
		float perc;
		void getuser() // Get data about the user
		{
			clrscr();
			cout << endl << "DON'T PANIC!"
				 << endl << "Enter username (maximum 40 characters): ";
			gets(nm);
			cout << "Enter age: ";
			cin >> age;
			cout << "Enter sex (M/F): ";
			cin >> sex;
			if (sex == 'm') // To standardise the database
				sex = 'M';
			else if (sex == 'f')
				sex = 'F';
			score = 0;
			pass = 0;
			perc = 0.0;
		}

		void showuser() // Show data about the user
		{	
			cout << endl << "Displaying Player Details..."
				 << endl << "Name: " << nm
				 << endl << "Age: " << age
				 << endl << "Sex: " << sex
				 << endl << "Score: " << score
                		<< endl << "Passes: " << pass
                		<< endl << "Percentage Accuracy: " <<perc <<endl;
		}

		char *retname() // Return private data member 'nm'
		{
			return nm;
		}

		int retage() // Return private data member 'age'
		{
			return age;
		}

		char retsex() // Return private data member 'sex'
		{
			return sex;
		}

} u1, u2;


void deluser() // Delete a particular user from the records
{
	clrscr();
	cout << endl << "Enter username of user whose record needs to be deleted: ";
	gets(check);
	file.open("user.dat", ios::in|ios::binary);
	temp.open("temp.dat", ios::out|ios::binary);
	flag = 0;
	while (file.read((char*)&u1, sizeof(u1)))
	{       
		strcpy(name, u1.retname());
		if(strcmpi (check, name) == 0)
			flag = 1;
		else temp.write((char*)&u1, sizeof(u1));
	}
	if (flag == 0)
	{
		cout << endl << "Username you searched for does not exist!" << endl;
		cout << endl << endl << "Press any key to continue...";
		getch();
	}
	file.close();
	temp.close();
	remove("user.dat");
	rename("temp.dat", "user.dat");
}


void edituser() // Edit records of a particular user
{
	clrscr();
	cout << endl << "Enter username of user whose record needs to be edited: ";
	gets(check);
	file.open("user.dat", ios::in|ios::binary);
	temp.open("temp.dat", ios::out|ios::binary);
	flag = 0;
	while (file.read((char*)&u1, sizeof(u1)))
	{       
		strcpy(name, u1.retname());
		if (strcmp (check, name) == 0)
		{
			flag = 1;
			cout << endl << "Enter new details for user " << name << endl;
			u2.getuser();
			u2.score = u1.score; // To prevent reset of score
			u2.pass = u1.pass; // To prevent reset of number of passes
			u2.perc = u1.perc; // To prevent reset of accuracy percentage
			temp.write((char*)&u2, sizeof(u2));
		}
		else temp.write((char*)&u1, sizeof(u1));
	}
	if (flag == 0)
	{
		cout << endl << "Username you searched for does not exist!" << endl;
		cout << endl  << endl << "Press any key to continue...";
		getch();
	}
	file.close();
	temp.close();
	remove("user.dat");
	rename("temp.dat", "user.dat");
}
	

void searchuser() // Search for users in database according to different criteria
{
	clrscr();
	cout << endl << "User Details Search"
		 << endl << "Search by"
		 << endl << "\t1. Name"
		 << endl << "\t2. Age"
		 << endl << "Enter your choice (1-2): ";
	cin >> ich;
	file.open("user.dat", ios::in|ios::binary);
	switch(ich)
	{
		case 1 :	// For searching by name
				cout << endl << "Enter username to be searched: ";
				gets(check);
				flag = 0;
				while(file.read((char*)&u1, sizeof(u1)))
				{
					strcpy(name, u1.retname());
					if(strcmpi(name, check) == 0)
					{
						flag = 1;
						u1.showuser();
						cout << endl << endl<< "Press any key to continue..." << endl;;
						getch();
					}
				}
				if (flag == 0)
				{
					cout << "Username you searched for does not exist!" << endl;
					cout << endl  << endl << "Press any key to continue:" << endl;
					getch();
				}
				break;
		case 2 :	// For searching by age
				cout << endl << "Enter the age to be searched in records: ";
				cin >> r1;
				flag = 0;
				while (file.read((char*)&u1, sizeof(u1)))
				{
					r2 = u1.retage();
					if (r1 == r2)
					{
						flag = 1;
						u1.showuser();
						cout << endl << endl << "Press any key to continue..." << endl;
						getch();
					}
				}
				if (flag == 0)
				{
					cout << "Age you searched for does not exist in any record!" << endl;
					cout << endl  << endl << "Press any key to continue:" << endl;
					getch();
				}
				break;
		default :	cout << endl << "You entered an invalid choice!" << endl;
	}
	file.close();
}
				

void playquiz() // Normal mode playquiz
{
	clrscr();
	cout << endl << "QuizMaster PRO Normal User Mode"
		 << endl << endl << "Rules"
        	<< endl << "\t1. Each correct answer gets you +42 points"
        	<< endl << "\t2. Each incorrect answer gets you -21 points"
        	<< endl << "\t3. No points / penalties for a pass";
	cout << endl << endl << endl << "Get ready to play the quiz! Press any key to continue...";
	getch();
	r3 = 0;
	ich = 0;
	file.open("ques.dat", ios::in|ios::binary);
	while(file.read((char*)&q1, sizeof(q1)))
	{
		r3++;
		clrscr();
		cout << endl << "Question Number " << r3;
       		q1.showq();
		cout << endl << "Enter your answer (1-4; 5 for a 'pass'): ";
		cin >> r1;
		r2 = q1.retans();
		if (r1 == r2)
		{
			cout << endl << "CORRECT ANSWER!\nCORRECT ANSWER\n You get 42 points!";
			u1.score += 42;
			ich++;
		}
		else if (r1 == 5)
			u1.pass++;
		else
		{
			u1.score -= 21;	    
            cout << endl << "WRONG ANSWER! \nWRONG ANSWER! \nCorrect option is " << r2 << ".";
        }
		cout << endl << endl << "Press any key to continue (or '0' to finish quiz)...";
		cch = getch();
		if (cch == '0')
            break;
	}
	u1.perc = ((float) ich / (float) r3) * 100; // Just for making code clearer
    cout << endl  << endl << endl << "You scored " << u1.score << " points with " 
		 << u1.pass
    	 << " passes out of a total of " << r3 << " questions"
    	 << " resulting in an accuracy of " << u1.perc << " percentage.";
   	file.close();
	file.open("user.dat", ios::app|ios::binary);
	file.write((char*)&u1, sizeof(u1));
	file.close();
	cout << endl << endl << "Press any key to continue...";
	getch();
}


void highscore() // Display highest score achieved till now
{
	clrscr();
	file.open("user.dat", ios::in|ios::binary);
	file.read((char*)&u1, sizeof(u1));
	cout << endl << "Display High Score According To Selected Criteria"
		 << endl << "\t1. Actual Score"
		 << endl << "\t2. Accuracy Percentage"
		 << endl << "Enter your choice (1-2): ";
	cin >> ich;
	switch(ich)
	{
		case 1 :	r1 = u1.score;
				while (file.read((char*)&u1, sizeof(u1)))
				{
					r2 = u1.score;
					if (r2 > r1)
					r1 = r2;
				}
				cout << endl << "High Score is: " << r1
					 << endl << "Details of user(s) with high score: ";
				file.close();
				file.open("user.dat", ios::in|ios::binary);
				while (file.read((char*)&u1, sizeof(u1)))
				{
					if (u1.score == r1)
					{
		  				u1.showuser();
		 				cout << endl << "Press any key to continue...";
		  				getch();
					}
				}
				file.close();
				break;
		case 2 :	float p1, p2;
				p1 = u1.perc;
				while (file.read((char*)&u1, sizeof(u1)))
				{
					p2 = u1.perc;
					if (p2 > p1)
						p1 = p2;
				}
				cout << endl << "Highest Accuracy Percentage is: " << p1
					 << endl << "Details of user(s) with high score: ";
				file.close();
				file.open("user.dat", ios::in|ios::binary);
				while (file.read((char*)&u1, sizeof(u1)))
				{
					if (u1.perc == p1)
					{
		  				u1.showuser();
		 				cout << endl << "Press any key to continue...";
		  				getch();
					}
				}
				file.close();
				break;
		default :	cout << endl << "You entered an incorrect choice!";
				break;
	}
}


void countq() // Count the number of questions in database
{
	r3 = 0;
	file.open("ques.dat", ios::in|ios::binary);
	while (file.read((char*)&q1, sizeof(q1)))
		r3++;
	file.close();
}


void addq() // Add new questions to database
{
	clrscr();
	file.open("ques.dat", ios::app|ios::binary);
	cout << endl << "Enter new questions" << endl;
	do
	{
		q1.getq();
		file.write((char*)&q1, sizeof(q1));
		cout << endl << "Question added to database"
			 << endl << "Do you want to enter another question? (Y/N) : ";
		cin >> cch;
	} while (cch == 'y' || cch == 'Y');
	file.close();
}


void editq() // Edit existing questions in database
{
	adminedit:
	clrscr();
	cout << endl << "Enter question number to be edited (0 to exit): ";
	cin >> r2;
	countq();
	if ((r2 < 0) || (r2 > r3))
	{	
		cout << endl << "Sorry, record number you requested does not exist!";
		cout << endl << "Press any key to continue...";
		getch();
		goto adminedit;
	}
	r1 = 0;
	file.open("ques.dat", ios::in|ios::binary);
	temp.open("temp.dat", ios::out|ios::binary);
	while (file.read((char*)&q1, sizeof(q1)))
	{       
		r1++;
		if (r1 == r2)
		{	
			q1.showq();
			cout << endl << "Is this the question you want to edit? (Y/N): ";
			cin >> cch;
			if (cch == 'y' || cch == 'Y')
			{
				cout << endl << "Enter new details for question";
				q2.getq();
				temp.write((char*)&q2, sizeof(q2));
			}
			else
			{
				cout << endl << "Question has not been edited" << endl;
				file.close();
				temp.close();
				goto adminedit;
			}
		}
		else temp.write((char*)&q1, sizeof(q1));
	}
	file.close();
	temp.close();
	remove("ques.dat");
	rename("temp.dat", "ques.dat");
}
	

void delq() // Delete existing questions in database
{
	admindel:
	clrscr();
	cout << endl << "Enter question number to be deleted (0 to exit): ";
	cin >> r2;
	countq();
	if ((r2 < 0) || (r2 > r3))
	{	
		cout << endl << "Sorry, record number you requested does not exist!";
		cout << endl << "Press any key to continue...";
		getch();
		goto admindel;
	}
	r1 = 0;
	file.open("ques.dat", ios::in|ios::binary);
	temp.open("temp.dat", ios::out|ios::binary);
	while (file.read((char*)&q1, sizeof(q1)))
	{       
		r1++;
		if (r1 != r2)
			temp.write((char*)&q1, sizeof(q1));
		else
		{
			q1.showq();
			cout << endl << "Is this the question you want to delete? (Y/N): ";
			cin >> cch;
			if (cch == 'n' || cch == 'N')
			{
				temp.write((char*)&q1, sizeof(q1));
				cout << endl << "Question has not been deleted" << endl;
				cout << endl << "Press any key to continue...";
				getch();
				file.close();
				temp.close();
				goto admindel;
			}
		}
	}
	file.close();
	temp.close();
	remove("ques.dat");
	rename("temp.dat", "ques.dat");
}


void qmmode() // Quizmaster Mode - For viewing all questions with answers
{
	cout << endl << "Entering Quizmaster Mode"
		 << endl << "This displays all questions in the database along with the answer";
	file.open("ques.dat", ios::in|ios::binary);
	while(file.read((char*)&q1, sizeof(q1)))
	{
		clrscr();
		q1.showq();
		r1 = q1.retans();
		cout << endl << "Option number " << r1 << " is correct"
			 << endl << "Press any key to continue (or '0' to exit QM mode)...";
		cch = getch();
		if (cch == '0')
			break;
	}
	file.close();
}


void viewusers() // To view details of all users till now
{
	clrscr();
	cout << endl << "Showing records of all users till now..." << endl;
	file.open("user.dat", ios::in|ios::binary);
	while(file.read((char*)&u1, sizeof(u1)))
	{
		u1.showuser();
		cout << endl << "Press any key to continue (or '0' to exit this mode)...";
		cch = getch();
		if (cch == '0')
			break;
	}
	file.close();
}


void proghelp() // Program help
{
	clrscr();
	r1 = 0;
	file.open("proghelp.txt", ios::in);
	while (!file.eof())
	{                                            // NEEDS TO BE CORRECTED
		r1++;
		cch = file.get();
		cout << cch;
		if ( (r1%717) == 0)
		{
			cout << endl << endl << "Press any key to continue (or '0' to exit this mode)..." << endl << endl;
			cch = getch();
			if (cch == '0')
				break;
		}
	}
	file.close();
	cout << endl << endl << "Press any key to continue...";
	getch();
}


void aboutus() // About the QuizMaster PRO Project
{
	clrscr();
	r1 = 0;
	file.open("aboutus.txt", ios::in);
	while (!file.eof())
	{
		r1++;
		cch = file.get();
		cout << cch;
		if ((r1%551) == 0)
		{
			cout << endl << endl << "Press any key to continue (or '0' to exit this mode)..." << endl << endl;
			cch = getch();
			if (cch == '0')
				break;
		}
	}
	file.close();
	cout << endl << endl << "Press any key to continue...";
	getch();
}


void zaphod() // Easter egg
{
	clrscr();
	r1 = 0;
	file.open("zaphod.txt", ios::in);
	while (!file.eof())
	{
		r1++;
		cch = file.get();
		cout << cch;
		if ( (r1%1000) == 0)
		{
			cout << endl << endl << "Press any key to continue (or '0' to exit this mode)..." << endl << endl;
			cch = getch();
			if (cch == '0')
				break;
		}
	}
	file.close();
	cout << endl << endl << "Press any key to continue...";
	getch();
}


void pwdchk()
{
	clrscr();
	cout << endl << "QuizMaster PRO Password Authentication"
		 << endl << endl << "Enter current password: ";
	for (int i = 0; ;i++)
	{
		check[i] = getch();
		if (check[i] == '\r')
			break;
		else if (check[i] == '\b')
		{	
			cout << '\b' << " " << '\b';
			i -= 2;
		}
		else
		    cout << "*";
	}
	check[i] = '\0';
	file.open("pwd.dat", ios::in|ios::binary);
	file.read((char*)&name, 42);
	file.close();
	flag = 0;
	if (strcmp (check, name) == 0)
	{
		flag = 1;
		cout << endl << "Authentication confirmed" << endl;
	}
	else 
		cout << endl << "Sorry! Invalid password!";
}	


void pswd() // Password manipulation
{
	pwdchk();
	if (flag == 1)
	{
		pwdchange:
		cout << endl << "Enter new password (alphanumeric): ";
		for (int i = 0; ;i++)
		{
			check[i] = getch();
			if (check[i] == '\r')
				break;
			else if (check[i] == '\b')
			{	
				cout << '\b' << " " << '\b';
				i -= 2;
			}
			else
				cout << "*";
		}
		check[i] = '\0';
		cout << endl << "Confirm new password: ";
		for (i = 0; ; i++)
		{
			name[i] = getch();
			if (name[i] == '\r')
				break;
			else if (name[i] == '\b')
			{	
				cout << '\b' << " " << '\b';
				i -= 2;
			}
			else
				cout << "*";
		}
		name[i] = '\0';
		if (strcmp(check,name) == 0)
		{
			file.open("pwd.dat", ios::out|ios::binary);
			file.write((char*)&name, 42);
			file.close();
		}
		else
		{
			cout << endl << "Sorry! Passwords do not match! Try again!";
			goto pwdchange;
		}
	}
}	


void admin() // Options for administrator mode
{
	clrscr();
	pwdchk();
	if (flag == 1)
	{
		admenu:             //to maintain uniformity
			clrscr();
			gotoxy(24,2);
			cout << endl << "QuizMaster PRO Administrator Menu" << endl;
			cout << endl << "\t1. Quizmaster Mode" << endl;
			cout << endl << "\tQuestion Database Options"
				 << endl << "\t\t2. Add Questions To Database";
			cout << endl << "\t\t3. Edit Question Currently In Database"
				 << endl << "\t\t4. Delete Question Currently In Database"
				 << endl << "\t\t5. Count Number of Questions In Database" << endl;
			cout << endl << "\tUser Database Options"
				 << endl << "\t\t6. View Users"
				 << endl << "\t\t7. Search User Records";
			cout << endl << "\t\t8. Edit User Record"
				 << endl << "\t\t9. Delete User Record" << endl
				 << endl << "\t10. View High Score";
			cout << endl << "\t11. Change Administrator Password" << endl
				 << endl << "12. Help"
				 << endl << "0. Exit Administrator Mode" << endl
				 << endl << "Enter your choice (0-12): ";
			cin >> ich;
			switch(ich)
			{
				case 0 :	goto end;
				case 1 :	qmmode();
						break;
				case 2 :	addq();
						break;
				case 3 :	editq();
						break;
				case 4 :	delq();
						break;
				case 5 :	countq();
						cout << endl << "The database has " << r3 << " questions";
						cout << endl << endl << "Press any key to continue...";
						getch();
						break;
				case 6 :	viewusers();
						break;
				case 7 :	searchuser();
						break;
				case 8 :	edituser();
						break;
				case 9 :	deluser();
						break;
				case 10 :	highscore();
						break;
				case 11 :	pswd();
						break;
				case 12 :	proghelp();
						break;
				case 42 :	zaphod();
						break;
		default :	cout << endl << "You entered an invalid choice!";
		}
	goto admenu;
	}
	end:
	cout << endl << "You are about to exit QuizMaster PRO Administrator Menu"
		 << endl << "Press any key to continue...";
	getch();
}


void main() // And then, there were none (functions, I mean...)
{
	menu:
		clrscr();
		gotoxy(29,3);
		cout << "Welcome to QuizMaster PRO!" << endl;
		gotoxy(12,9);
		cout << "1. Normal User Mode";
		gotoxy(50,9);
		cout << "2. Administrator Mode";
		gotoxy(35,15);
		cout << "0. Exit";
		gotoxy(12,21);
		cout << "3. Help";
		gotoxy(50,21);
		cout << "4. About";
		gotoxy(1,24);
		cout << "Enter your choice (0-4): ";
		cin >> ich;
		switch(ich)
		{
			case 1 :	u1.getuser(); // Get user details
					playquiz(); // Allow user to start playing
					break;
			case 2 :	admin(); // Function available to administrators
					break;
			case 3 :	proghelp(); // Program help
					break;
			case 4 :	aboutus();
					break;
			case 0 :	exit(0);
			case 42 :	zaphod(); // An easter egg
					break;
			default :	cout << endl << "You entered an invalid choice!";
		}
		goto menu;
}

/*Made by RAKSHIT JOSHI, 
	Contact - rakshit_22@yahoo.in*/