//
//  StudentInfo.cpp
//  Computer Science Project
//  Copyright (c) 2013 Rohan Chandrashekar. All rights reserved.
//


//***************************************************************
// HEADER FILES USED IN PROJECT
//***************************************************************

			#include<conio.h>
			#include<iostream>
			#include<fstream>
			#include<string>
			#include<windows.h>
			
			using namespace std;
			
//***************************************************************
// MAIN MENU STRUCTURE 
//***************************************************************	   	   	   

struct Menus
{			
	void opening()												// Program beggining.
	{
		cout<<"\n\n\n\n\n\n\n\n\n\n\t\t\t  STUDENT INFORMATION SYSTEM\n\n\n";
	 	Sleep(600);   
		Sleep(500);
		cout<<"\t\t\t  \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB";
		Sleep(1000);
		cout<<"\xDB\xDB\xDB\xDB";
		Sleep(500);
	  	cout<<"\xDB\xDB\xDB\xDB\xDB\xDB";
	 	Sleep(500);
		cout<<"\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB";
		Sleep(750);	
	}
	
	void mainmenu()												// Function to print main menu.
	{
		cout<<"\n\n\t\t   ******* Student Information System *******\n\n\n\t" 
			<<"Main Menu: \n\n\t" 
			<<"1.Create a student record.\n\n\t"
  			<<"2.Search/Display a student record.\n\n\t"
 			<<"3.Modify a student record.\n\n\t"
			<<"4.Delete all student records.\n\n\t"
			<<"5.Exit the program. \n\n\t";
		cout<<"\n\t\t\tEnter your choice:-> ";
	}
	
	void mod_menu()												// Function to print modifcations menu.
	{
		cout<<"\n\n\t\t   ******* Student Information System *******\n\t"; 
		cout<<"\n\n\t\tSelect field to modify : \n\t" 
			<<"\n\t\t1.Name. "	
			<<"\n\t\t2.Father's Name. "
			<<"\n\t\t3.Mother's Name. "
			<<"\n\t\t4.Age. "
			<<"\n\t\t5.Date Of Birth."
			<<"\n\t\t6.Gender. "
			<<"\n\t\t7.Blood Group. "
			<<"\n\t\t8.House Address. "
			<<"\n\t\t9.Number"
			<<"\n\t\t10.Email Address."
			<<"\n\t\t11.Admission number."
			<<"\n\t\t12.Current Class."
			<<"\n\t\t13.Rollno. "
			<<"\n\t\t14.Marks. "
			<<"\n\t\t15.Exit. ";
		cout<<"\n\n\t\t\tEnter your choice:-> ";
	}
	
	void gotoxy (int x, int y)
	{
		COORD coord; 
		coord.X = x; coord.Y = y; 
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	}
};																//Structure Menus ends here.

//***************************************************************
// ADMINISTRATOR CLASS 
//***************************************************************	  

class Admin
{
	int temp;
	long filesize,norec;
	char ch,username[31],password[31],upassword[31];
	public:
	Admin()
	{
		username[0]='\0';
		password[0]='\0';
		upassword[0]='\0';
		norec=0;
		temp=1;
	}
	
	int profile(fstream &f,int a=0)								// Function to accept administrator username/password.
	{	 	  	  	  	  	  	  	  	  
		if(!f)
		{
			cout<<"\n\n\n\t\t   ******* Student Information System *******\n\n\t";  
			cout<<"\n\n\t    Enter following details to start using the program:"
				<<"\n\n\n\n\t\tEnter administrator username: ";
			cin.getline(username,31);
				while(strlen(username)>30)
				{
					cout<<"\n\n\tUsername length exceeded. Re-enter: ";
					cin.getline(username,31);
				}
			cout<<"\n\t\tEnter administrator password: ";
			for(int i=0;temp;)
				{
					ch=getch();
        			if(ch!='\b' && ch!='\r')
					{
						password[i]=ch;
            			i++;
            			cout<<"*";
					}
					if(ch=='\b' && i>=1)
        			{
            			cout<<"\b \b";
            			i--;
        			}
        			if(ch=='\r')
        			{
            			password[i]='\0';
            			temp=0;
					}
				}
			cout<<"\n\n\n\tNote: Note administrator password to modify/delete records.";	
			cout<<"\n\n\n\t\t\t Press any key to continue.";					
				getch();
				system("CLS");
			{
				ofstream fout("STUDENTINFO.dat",ios::binary|ios::out);
				fout.write((char*)username, sizeof(username));
				fout.write((char*)password, sizeof(password));
				fout.close();
			}	 	 	 	 
		}
		else if(a==3 || a==4)
		{
			cout<<"\n\n\n\t\t   ******* Student Information System *******\n\n\t";  
			upassword[0]='\0';
			temp=1;
			cout<<"\n\n\n\n\n\n\t\t   Enter administrator password: ";
				for(int i=0;temp;)
				{
					ch=getch();
        			if(ch!='\b' && ch!='\r')
					{
						upassword[i]=ch;
            			i++;
            			cout<<"*";
					}
					if(ch=='\b' && i>=1)
        			{
            			cout<<"\b \b";
            			i--;
        			}
        			if(ch=='\r')
        			{
            			upassword[i]='\0';
            			temp=0;
					}
				}
				f.seekg(31L,ios::beg);
				f.read((char*)password, sizeof(password));
			if(strcmp(upassword,password)==0)
			{
				system("CLS");
				return 1;
			}
			else 
			{
				system("CLS");
				cout<<"\n\n\t\t\t\tInvalid password.";
				return 0;
			}
		}	 	 	 	 
	}
		
	int sizefind(fstream &f)									//Function to find the size of STUDENTDATA.dat .
	{
		if(f)
		{
			f.seekg(0L,ios::end);
			filesize=f.tellg();
			norec=filesize/392;
		}
		
		return norec;
	}
};																// Class Admin ends here.
		
//***************************************************************
// STUDENT STRUCTURE - ADD/MODIFY/DISPLAY RECORDS 
//***************************************************************	   	   	   
			
struct Student:public Menus
{
	int studid,age,ccls,rollno,admno,amarks[5],emarks[5];
	long long int phone[2];
	char gender,sname[50],fname[50],mname[50],dob[11],bgroup[8],hadd[85],email[50];
	
	public:
	
	Student()
	{
		age=ccls=rollno=admno=0;
		phone[0]=phone[1]=0;
		amarks[0]=amarks[1]=amarks[2]=amarks[3]=amarks[4]=0;
		emarks[0]=emarks[1]=emarks[2]=emarks[3]=emarks[4]=0;
		sname[0]=fname[0]=mname[0]=dob[0]=bgroup[0]=hadd[0]=email[0]=gender='\0';
	}	 	 
	
	void create_record()										// Function to add/create new records.
	{
		{
			cout<<"\n\n\t\t\t    ## Student ID: "<<studid<<" ##"
				<<"\n\n\tGeneral Details: "
				<<"\n\n\tName: ";
				Menus::gotoxy(50,6);
				cout<<"Number:"
				<<"\n\n\tFather's Name: ";
				Menus::gotoxy(50,8);
				cout<<"Landline: "
				<<"\n\n\tMother's Name: ";
				Menus::gotoxy(50,10);
				cout<<"Mobile: "
				<<"\n\n\tEmail Address: "
				<<"\n\n\tDate Of Birth (dd/mm/yyyy): ";
				Menus::gotoxy(50,14);
				cout<<"Age: "
				<<"\n\n\tGender(M/F): ";
				Menus::gotoxy(50,16);
				cout<<"Blood Group: "
				<<"\n\n\tHouse Address: ";
				Menus::gotoxy(14,6);	cin.get();
				cin.getline(sname,50);
				Menus::gotoxy(23,8);
				cin.getline(fname,50);
				Menus::gotoxy(23,10);
				cin.getline(mname,50);
				Menus::gotoxy(23,12);
				cin.getline(email,50);
				Menus::gotoxy(36,14);
				cin.getline(dob,11);
				Menus::gotoxy(21,16);
				cin>>gender;
				Menus::gotoxy(23,18);	cin.get();
				cin.getline(hadd,85);
				Menus::gotoxy(60,8);
				cin>>phone[0];
				Menus::gotoxy(58,10);
				cin>>phone[1];
				Menus::gotoxy(55,14);
				cin>>age;
				Menus::gotoxy(63,16);	cin.get();
				cin.getline(bgroup,8);
		}
		{
			system("CLS");	
			cout<<"\n\n\t\t\t    ## Student ID: "<<studid<<" ##";  
			cout<<"\n\n\tSchool Details: "
				<<"\n\n\tAdmission number: ";
			Menus::gotoxy(33,6);
			cout<<"Current Class: ";
			Menus::gotoxy(54,6);
			cout<<"Rollno: ";
			Menus::gotoxy(31,9);
			cout<<"Assignment marks: "
				<<"\n\n\tEnglish: ";
			Menus::gotoxy(21,11);	
			cout<<"Maths: ";
			Menus::gotoxy(32,11);
			cout<<"Physics: ";
			Menus::gotoxy(45,11);
			cout<<"Chemistry: ";
			Menus::gotoxy(60,11);
			cout<<"C.Sc: ";   	  	  	   	   	      	   
			Menus::gotoxy(31,14);
			cout<<"Examination marks: "
				<<"\n\n\tEnglish: ";
			Menus::gotoxy(21,16);	
			cout<<"Maths: ";
			Menus::gotoxy(32,16);
			cout<<"Physics: ";
			Menus::gotoxy(45,16);
			cout<<"Chemistry: ";
			Menus::gotoxy(60,16);
			cout<<"C.Sc: ";   	  	  	     	   	   	   	   	   
		  	Menus::gotoxy(26,6);
		  	cin>>admno;
		  	Menus::gotoxy(48,6);
		  	cin>>ccls;
		  	Menus::gotoxy(62,6);
		  	cin>>rollno;
			Menus::gotoxy(17,11);
			cin>>amarks[0];
			Menus::gotoxy(28,11);
			cin>>amarks[1];
			Menus::gotoxy(41,11);
			cin>>amarks[2];
			Menus::gotoxy(56,11);
			cin>>amarks[3];
			Menus::gotoxy(66,11);
			cin>>amarks[4];
			Menus::gotoxy(17,16);
			cin>>emarks[0];
			Menus::gotoxy(28,16);
			cin>>emarks[1];
			Menus::gotoxy(41,16);
			cin>>emarks[2];
			Menus::gotoxy(56,16);
			cin>>emarks[3];
			Menus::gotoxy(66,16);
			cin>>emarks[4];
		}
				
	}
		
	void display()												// Function to display record details.
	{	
		system("CLS");
		{
			{
				cout<<"\n\n\t\t\t    ## Student ID: "<<studid<<" ##"
				<<"\n\n\tGeneral Details: "
				<<"\n\n\tName: "<<sname;
				Menus::gotoxy(50,6);
				cout<<"Number:"
				<<"\n\n\tFather's Name: "<<fname;
				Menus::gotoxy(50,8);
				cout<<"Landline: "<<phone[0]
				<<"\n\n\tMother's Name: "<<mname;
				Menus::gotoxy(50,10);
				cout<<"Mobile: "<<phone[1]
				<<"\n\n\tEmail Address: "<<email
				<<"\n\n\tDate Of Birth (dd/mm/yyyy): "<<dob;
				Menus::gotoxy(50,14);
				cout<<"Age: "<<age
				<<"\n\n\tGender : "<<gender;
				Menus::gotoxy(50,16);
				cout<<"Blood Group: "<<bgroup
				<<"\n\n\tHouse Address: "<<hadd;
				Menus::gotoxy(50,19);	
				cout<<"Press enter to go to next page";	  getch();
			}
			{
				system("CLS");	
				cout<<"\n\n\t\t\t    ## Student ID: "<<studid<<" ##";  	   	   	   	   
				cout<<"\n\n\tSchool Details: "
				<<"\n\n\tAdmission number: "<<admno;
				Menus::gotoxy(33,6);
				cout<<"Current Class: "<<ccls;
				Menus::gotoxy(55,6);
				cout<<"Rollno: "<<rollno<<endl;
				Menus::gotoxy(31,9);
				cout<<"Assignment marks: "
				<<"\n\n\tEnglish: "<<amarks[0];
				Menus::gotoxy(21,11);	
				cout<<"Maths: "<<amarks[1];
				Menus::gotoxy(32,11);
				cout<<"Physics: "<<amarks[2];
				Menus::gotoxy(45,11);
				cout<<"Chemistry: "<<amarks[3];
				Menus::gotoxy(60,11);
				cout<<"C.Sc: "<<amarks[4];   	  	   	   	      	   
				Menus::gotoxy(31,14);
				cout<<"Examination marks: "
					<<"\n\n\tEnglish: "<<emarks[0];
				Menus::gotoxy(21,16);	
				cout<<"Maths: "<<emarks[1];
				Menus::gotoxy(32,16);
				cout<<"Physics: "<<emarks[2];
				Menus::gotoxy(45,16);
				cout<<"Chemistry: "<<emarks[3];
				Menus::gotoxy(60,16);
				cout<<"C.Sc: "<<emarks[4]<<endl;   		   	      
			}
		}
	}	 	 

	
	void search(fstream &f,int a,int b=0)	   	   	   // Function to search for records.
	{	
		switch(a)
		{
			case 1:
			{
				long p=sizeof(*this)*(b-1);
				f.seekg(p);
				f.read((char*)this,sizeof(*this));
				display();
				cout<<"\n\n\t\t\tPress any key to continue. ";
				getch();
				system("CLS");
			}
			break;
			case 2:
			{
				f.seekg(0L,ios::beg);
				if(!f.read((char*)this,sizeof(*this)))
				{
					system("CLS");
					cout<<"\n\n\t\t\t      No records to display";
				}
				else 
				{
					while(!f.eof())
					{
						display();
						if(f.read((char*)this,sizeof(*this)))
						{
							cout<<"\n\n\t\tPress any key to continue to next record. ";
							getch();
						}
						else 
						{
							cout<<"\n\n\t\t\tPress any key to continue. ";
							getch();
							system("CLS");
						}
					}
				}
			}
			break;	  	  	  
		}
	}
	
	void modify(fstream &f,int a)								// Function to modify records.
	{
		long p=sizeof(*this)*(a-1);
		f.seekp(p);
		f.read((char*)this,sizeof(*this));
		int modopt=1;
		do 
		{
			system("CLS");
			Menus::mod_menu();
			cin>>modopt;
			Menus::gotoxy(24,25);
			switch(modopt)
			{
				case 1:
				{
					cout<<"Name: ";	   
					cin.get();
					cin.getline(sname,50);
				}
				break;
				case 2:
				{	 
					cout<<"Father's Name: ";
					cin.get();
					cin.getline(fname,50);
				}
				break;
				case 3:
				{
					cout<<"Mother's Name: ";
					cin.get();
					cin.getline(mname,50);
				}
				break;
				case 4:
				{
					cout<<"Age: ";
					cin>>age;
				}
				break;
				case 5:
				{
					cout<<"Date Of Birth (dd/mm/yyyy): ";	 
					cin.get();
					cin.getline(dob,11);
				}
				break;
				case 6:
				{
					cout<<"Gender (M/F): ";	  
					cin.get();
					cin>>gender;
				}
				break;
				case 7:
				{
					cout<<"Blood Group: "; 
					cin.get();
					cin.getline(bgroup,10);
				}
				break;
				case 8:
				{
					cout<<"House Address: ";
					cin.get();
					cin.getline(hadd,100);
				}
				break;
				case 9:
				{
					cout<<"Number: "<<endl;
					Menus::gotoxy(24,26);
					cout<<"Landline: ";
					cin>>phone[0];
					Menus::gotoxy(24,27);
					cout<<"Mobile: ";
					cin>>phone[1];	  	  	  	  	  
				}
				break;
				case 10:
				{
					cout<<"Email Address: "; 
					cin.get();
					cin.getline(email,50);
				}
				break;
				case 11:
				{
					cout<<"Admission number: ";
					cin>>admno;
				}
				break;
				case 12:
				{
					cout<<"Current Class (1-12): ";
					cin>>ccls;
				}
				break;
				case 13:
				{
					cout<<"Rollno: ";
					cin>>rollno;
				}
				break;
				case 14:
				{
					system("CLS");
					Menus::gotoxy(30,8);
					cout<<"Assignment marks: "
					<<"\n\n\tEnglish: ";
					Menus::gotoxy(21,10);	
					cout<<"Maths: ";
					Menus::gotoxy(32,10);
					cout<<"Physics: ";
					Menus::gotoxy(45,10);
					cout<<"Chemistry: ";
					Menus::gotoxy(60,10);
					cout<<"C.Sc: ";   	  	  	   	   	      	   
					Menus::gotoxy(31,13);
					cout<<"Examination marks: "
					<<"\n\n\tEnglish: ";
					Menus::gotoxy(21,15);	
					cout<<"Maths: ";
					Menus::gotoxy(32,15);
					cout<<"Physics: ";
					Menus::gotoxy(45,15);
					cout<<"Chemistry: ";
					Menus::gotoxy(60,15);
					cout<<"C.Sc: ";   	  	  	     	   	   	   	   	   
				  	Menus::gotoxy(17,10);
					cin>>amarks[0];
					Menus::gotoxy(28,10);
					cin>>amarks[1];
					Menus::gotoxy(41,10);
					cin>>amarks[2];
					Menus::gotoxy(56,10);
					cin>>amarks[3];
					Menus::gotoxy(66,10);
					cin>>amarks[4];
					Menus::gotoxy(17,15);
					cin>>emarks[0];
					Menus::gotoxy(28,15);
					cin>>emarks[1];
					Menus::gotoxy(41,15);
					cin>>emarks[2];
					Menus::gotoxy(56,15);
					cin>>emarks[3];
					Menus::gotoxy(66,15);
					cin>>emarks[4];
				}
				break; 	   	   	   	   
				default:
				{
					if(modopt==15)
					{
						f.seekg(p);
						f.write((char*)this,sizeof(*this));
						cout<<"\n\t\t   All modifications have been made."; getch();
						system("CLS");
					}
					else 
					{
						Menus::gotoxy(28,25);	 
						cout<<"Invalid option";	getch();
					}
				}
			}
		}while(modopt!=15);	   	   	   
	}	   	   
};																// Structure Student ends here.

class queue
{
	Student data;
	queue *next,*front,*rear;
	public:
	
	queue()
	{
		next=0;
		rear=0;
		front=0;
	}
	
	void queueinsert(Student a)										//Queue Insert function.
	{
		queue *tmp= new queue;
		if(tmp)
		{
			tmp->data=a;
			if(!front)
			{
				front=rear=tmp;
			}
			else 
			{
				rear->next=tmp;
				rear=tmp;
			}
		}			
	}
	
	int queuedelete(Student &a)										//Queue Delete function.
	{
		if(front)
		{
			queue *tmp=front;
			a=front->data;
			front=front->next;
			delete tmp;
			if(!front)
			{
				rear=0;
			}
		return 1;
		}
		else 
		return 0;
	}
};

//***************************************************************
// MAIN FUNCTION 
//***************************************************************	   	   	   

int main()
{
	Admin a;	Student s;	Menus m;	queue q;
	int mmopt,dispopt,ustudid,temp=1;	long norec;	 
	m.opening();
	system("CLS"); 
	do 
	{
			fstream f1("STUDENTINFO.dat",ios::binary|ios::in);
			if(temp)
			{
				a.profile(f1);
				temp=0;
			}
			fstream f2("STUDENTDATA.dat",ios::binary|ios::in|ios::out);
			norec=a.sizefind(f2);
			m.mainmenu();	 	   	 	 
			cin>>mmopt;
			switch(mmopt)
			{
				case 1:											//Adding a record
				{
					system("CLS");	 	 	 	 	 
					s.studid=norec+1;
					
					if(!f2)
					{
						ofstream fout("STUDENTDATA.dat",ios::binary);
						s.create_record();
						fout.write((char*)&s,sizeof(s));
						fout.close();
					}
					else 
					{
						s.create_record();
						f2.seekp(0L,ios::end);
						f2.write((char*)&s,sizeof(s));
					}
					cout<<"\n\n\tRecord has been created sucessfully. Press any key to continue. ";
					getch();
					system("CLS");	  	  	  	  
				}
				break;
				case 2:											// Searching/Displaying a record.
				{
					system("CLS");
					if(f2)
					{
						cout<<"\n\n\n\t\t   ******* Student Information System *******\n\n\t"
							<<"\n\n\n\n\t\t1.Display a paricular record."
  							<<"\n\n\t\t2.Display all records.\n\t"
							<<"\n\t\tEnter your choice:-> ";
							cin>>dispopt;
							if(dispopt<0 || dispopt>2)
							{
								system("CLS");
								cout<<"\n\t\t\t\tInvalid option";
							}
							else if(dispopt==1)  
							{
								cout<<"\n\n\t\t\t  Enter Student ID: ";
								cin>>ustudid;
								if(ustudid<1 || ustudid>norec)
								{
									system("CLS");
									cout<<"\n\n\t\t\t        Record not found. ";
								}
								else	  
								s.search(f2,dispopt,ustudid);
							}
							else 
							{
								s.search(f2,dispopt);
							}
					}
					else 
					{
						system("CLS");
						cout<<"\n\n\t\t\t      No records to display.";
					}
				}
				break; 
				case 3:											//Modifying a record.
				{
					if(f2)
					{
						system("CLS");
						cin.get();
						if(a.profile(f1,mmopt))
						{
							cout<<"\n\n\n\t\t   ******* Student Information System *******\n\n\t"
							<<"\n\n\t\t   Enter Student ID (to be modified) : ";
							cin>>ustudid;
							if(ustudid<1 || ustudid>norec)
							{
								system("CLS");
								cout<<"\n\n\t\t\t        Record not found. ";
							}
							else 
							{
								s.modify(f2,ustudid);
							}
						}
					}
					else 
					{
						system("CLS");
						cout<<"\n\n\t\t\t      No records to modify.";
					}	 	 	 
				}
				break;
				case 4:											// Delete's all records present.
				{
					system("CLS");	
					if(f2)
					{
						cin.get();
						if(a.profile(f1,mmopt))
						{
							ofstream fout("STUDENTDATA.dat",ios::binary);
							fout.close();	 	 	 
							cout<<"\n\n\t\t\t  All records have been deleted. ";
						}
					}
					else 
					{
						cout<<"\n\n\t\t\t      No records to delete.";
					} 	   	   	   	   	   	   	   	   	   
				}
				break;
				default:
				{
					if(mmopt!=5)
					{
						system("CLS");
						cout<<"\n\n\t\t\t\tInvalid option";
					}
				}
			}
			
		f2.close();	
		f1.close();
	}while(mmopt!=5);  
}

//***************************************************************
// END OF PROJECT 
//***************************************************************

