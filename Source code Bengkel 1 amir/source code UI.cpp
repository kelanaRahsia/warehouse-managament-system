#define _CRT_SECURE_NO_WARNINGS
#include <ctime>
#include <iostream>
#include <cstdio>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <conio.h>
#include <windows.h>
#include <mysql.h>
#include <iomanip>
#include<ctype.h>

using namespace std;

// Global Variable
int qstate;
MYSQL* conn;
MYSQL_ROW row;
MYSQL_RES* res;
// Global Variable End

class db_response
{
public:
	static void ConnectionFunction()
	{
		conn = mysql_init(0);
		if (conn)
		{
			cout << "Database Connected" << endl;
			cout << "Press any key to continue..." << endl;
			//getch();
			system("cls");
		}
		else
			cout << "Failed To Connect!" << mysql_errno(conn) << endl;
		conn = mysql_real_connect(conn, "localhost", "root", "", "db_cppmysql", 3306, NULL, 0);
		if (conn)
		{
			cout << "Database Connected To MySql" << conn << endl;
			cout << "Press any key to continue..." << endl;
			//getch();
			system("cls");
		}
		else
			cout << "Failed To Connect!" << mysql_errno(conn) << endl;
	}
};


void RegisterStocks();
void ViewStocks();
void UpdateStocks();
void CheckoutStocks();
void SearchStocks();
void SearchAsker();
void AdminStockMenu();
void AdminMainmenu();
void Staffmenu();
void Addstaff();
void Deletestaff();
void Viewstaff();
void Searchstaff();
void AdminSearchAsker();
void MenuChoosing();
void StaffAccDetails();
void AdminAccDetails();
int checkinput(string inputcopy);
void UpdateStaffDetails();
void barchart();
void viewInOutStocks();

string userID;
string type;  //userType
string typecp ; //type copy
int const sectionsize = 1000;


int main()
{
login:
	char ch;
	//string userID;
	string pssword;

	// Call Methods
	db_response::ConnectionFunction();
	// Call Methods End
	system("cls");

	cout << " \t\t\t                    **********************************" << endl;
	cout << " \t\t\t                          JMK Warehouse System" << endl;
	cout << " \t\t\t                    **********************************" << endl;
	cout << " \t\t\t                                  WELCOME " << endl;
	cout << " \t\t\t                    **********************************" << endl << endl;
	cout << "UserID : ";
	cin >> userID;

	cout << "\nPassword : ";
	while ((ch = _getch()) != '\r')
	{
		if (ch == '\b') {
			// Process a destructive backspace
			if (pssword.size() > 0) {
				pssword.erase(pssword.size() - 1, 1);
				std::cout << "\b \b";
			}
		}
		else {
			pssword.push_back(ch);
			std::cout.put('*');//password asterisk
		}
	}
	string checkuser = "SELECT * FROM users ";
	const char* qn = checkuser.c_str();
	qstate = mysql_query(conn, qn);
	if (!qstate)
	{
		res = mysql_store_result(conn);
		while ((row = mysql_fetch_row(res)))
		{
			if (userID == row[0] && pssword == row[2])
			{
				string type;
				system("cls");
				type = row[3];
				cout << "**********************************" << endl;
				cout << "JMK Warehouse System" << endl;
				cout << "**********************************" << endl << endl;
				cout << "Authorized!" << endl;
				system("pause"); 
				cout << endl<<endl;

				if (type == "a" || type == "A")
				{
					typecp = type;   //utk copy type value kepada typecp 
					AdminMainmenu();
				}
				else
				{
					typecp = type;    //utk copy type value kepada typecp 
					Staffmenu();
				}
			}

		}
		system("cls");
		cout << "**********************************" << endl;
		cout << "JMK Warehouse System" << endl;
		cout << "**********************************" << endl << endl;
		cout << "Incorrect Username or Password!" << endl;
		cout << "Please Try Again . . ." << endl << endl;
		system("pause");
		goto login;
	}  
	
}

void AdminMainmenu()
{
	int choose ;
	char exitacc;
	system("cls");
	//cin.ignore(10, '\n');
	cout << "type : " << type<<endl;
	cout << "--- Admin Main Menu ---" << endl<<endl;
	cout << "1. Add Staff" << endl;
	cout << "2. Delete Staff " << endl;
	cout << "3. View Staff" << endl;
	cout << "4. Edit Staff Details " << endl;
	cout << "5. Stocks Menu " << endl;
	cout << "6. Admin Account Setting." << endl;
	cout << "7. Logout " << endl;
	cout << "Please Enter your Choice : ";
	cin >> choose;

	switch (choose)
	{
	case 1:
		Addstaff();
		break;
	case 2:
		Deletestaff();
		break;
	case 3:
		Viewstaff();
		break;
	case 5:
		AdminStockMenu();   //ini adalah stok menu
		break;
	case 6:
		AdminAccDetails();
		break;
	case 7:
	LogOut:
		system("cls");
		cout << "--- Admin Main Menu---" << endl << endl;

		cout << "Loging out.. Are you sure? (y/N): ";
		cin >> exitacc;
		if (exitacc == 'y' || exitacc == 'Y') {
			main();
		}
		else if (exitacc == 'n' || exitacc == 'N') {
			system("cls");
			AdminMainmenu();
		}
		else {
			cout << "Please re enter again." << endl;
			goto LogOut;
		}
		break;
	case 4:
		UpdateStaffDetails();
		break;
	default:
		cout << "Please choose between 1 - 7. ";
		cin.clear();   //clears the error flag on cin (so that future I/O operations will work correctly)
		system("PAUSE");
		system("cls");
		AdminMainmenu();
		break;
	}
}

void AdminAccDetails()
{
	string username, userpassword;
	char choose, choose2;
	system("cls");
	cout << "--- Admin Account Settings ---\n\n";
	cout << "Press 1 to edit username, Press 2 to edit password :                                               [press 'x' to exit ]" << endl;
	cin >> choose;

	if (choose == '1')
	{
		//cout << "userID : " << userID; 
		string search_query = "select username from users where userID = '" + userID + "'";  
		const char* q = search_query.c_str();
		qstate = mysql_query(conn, q);

		res = mysql_store_result(conn);
		while (row = mysql_fetch_row(res))
		{
			cout << "Current Username : " << row[0] << endl;
		}

		cin.ignore(1, '\n');
		cout << "New Username : ";
		getline(cin, username);
		cout << "Are you confirm to change your username(y/N) :" << endl;
		cin >> choose2;
		if (choose2 == 'y' || choose2 == 'Y')
		{
			string update_query = "update users set username= '" + username + "' where userID = '" + userID + "'";
			const char* qi = update_query.c_str();
			qstate = mysql_query(conn, qi);

			string insert_query2 = "insert into staff (STAFF_NAME) values ('" + username + "')";
			const char* fi = insert_query2.c_str();
			qstate = mysql_query(conn, fi);

			cout << "Your username is succesfully updated..." << endl;
			_getch();
			system("cls");
			AdminMainmenu();

		}
		if (choose2 == 'n' || choose2 == 'N')
		{
			system("cls");
			AdminAccDetails();
		}
		else if (choose2 == 'x' || choose2 == 'X')
		{
			system("cls");
			AdminMainmenu();
		}
		else
		{
			system("cls");
			AdminMainmenu();
		}
	}
	if (choose == '2')
	{
	Password:
		string search_query = "select userPassword from users where userID = '" + userID + "'";  // Tak tahu knapa salah.
		const char* q = search_query.c_str();
		qstate = mysql_query(conn, q);

		res = mysql_store_result(conn);
		while (row = mysql_fetch_row(res))
		{
			cout << "Please Enter your current password : ";
			cin >> userpassword;
			if (userpassword == row[0])
			{
				cout << "Enter New Password :";
				cin >> userpassword;
				cout << endl;
				cout << "Are you confirm to change your password(y/N) :";
				cin >> choose2;
				cout << endl << endl;

				if (choose2 == 'y' || choose2 == 'Y')
				{
					string update_query = "update users set userPassword= '" + userpassword + "' where userID = '" + userID + "'";
					const char* qi = update_query.c_str();
					qstate = mysql_query(conn, qi);

					cout << "Your Password have been changed." << endl;
					_getch();
					system("cls");
					AdminMainmenu();
				}
				if (choose2 == 'n' || choose2 == 'N')
				{
					system("cls");
					AdminAccDetails();
				}
				else
				{
					system("cls");
					AdminMainmenu();
				}

			}
			else
			{
				cout << "Wrong Password. Please Re enter again.\n";
				_getch();
				system("cls");
				cout << "--- Admin Account Settings---" << endl<<endl;
				goto Password;
			}
		}
	}
	else if (choose2 == 'x' || choose2 == 'X')
	{
		system("cls");
		AdminMainmenu();
	}
}
void Addstaff()
{
	string staffID,staffname, staffic, staffpnum, staffaddress,stafftype="b",staffTemppasword="123";
	//int staffic;
	char choose;
	system("cls");
	cout << "\t\t\t\t\t\t************************************" << endl;
	cout << "\t\t\t\t\t\t\tJMK Warehouse System" << endl;
	cout << "\t\t\t\t\t\t************************************" << endl << endl;
	cout << "~~~ Add New Staff Menu ~~~" << endl<<endl;
	cout << "                                                                                                      Press 'x' to exit" << endl;
	cin.ignore(1, '\n');
	cout << "Enter staff ID(new ID):";
	ID:
	getline(cin, staffID);

	if (staffID == "x" || staffID == "X")
	{
		AdminMainmenu();
	}


	string search_query = "select count(*) from staff where STAFF_ID = '" + staffID + "'";
	const char* m = search_query.c_str();
	qstate = mysql_query(conn, m);

	mysql_free_result(res);
	res = mysql_store_result(conn);
	row = mysql_fetch_row(res);

	if (atoi(row[0]) > 0)
	{
		cout << "   Error. The staff ID you inserted has been used." << endl;
		cout << "   Please Re enter again." << endl;
		cout << "  Enter staff ID : ";
		goto ID;
	}

	cout << "Enter Fullname: ";
	getline(cin, staffname);

	cout << "Enter Identification Card(do not include -): ";
	Enter:
	getline(cin, staffic);
	if (checkinput(staffic) > 0)
	{
		cout << "    Error. Please enter number only : ";
		goto Enter;
	}

	cout << "Enter Contact Number: ";
	Enter2:
	getline(cin, staffpnum);
	if (checkinput(staffpnum) > 0)    
	{
		cout << "    Error. Please enter number only : ";
		goto Enter2;
	}

	cout << "Enter Address: ";
	getline(cin, staffaddress);

	string insert_query = "insert into staff (STAFF_ID,STAFF_NAME, STAFF_IC, STAFF_PHONENUMBER, STAFF_ADDRESS) values ('"+staffID+"','" + staffname + "','" + staffic + "','" + staffpnum + "','" + staffaddress + "')";

	const char* q = insert_query.c_str(); // c_str converts string to constant char and this is required
	qstate = mysql_query(conn, q);

	if (!qstate)
	{
		cout << endl << "Successfully added staff to database." << endl;
	}
	else
	{
		cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
	}

	string insert_query2 = "insert into users (userID,username, userPassword, userType) values ('" + staffID + "','" + staffname + "','" + staffTemppasword + "','" + stafftype+ "')";
	const char* qi = insert_query2.c_str();
	qstate = mysql_query(conn, qi);

	cout << "Press 'a' to add more staff and 'b' to go to Menu : ";
	cin >> choose;

	if (choose == 'a' || choose == 'A')
	{
		system("cls");
		Addstaff();
	}
	else if (choose == 'b' || choose == 'B')
	{
		system("cls");
		AdminMainmenu();
	}
}

int checkinput(string inputcopy)
{
	
	int number = 0;

		for (int i = 0; i < inputcopy.length(); i++)
		{
			if (!(isdigit(inputcopy[i])||inputcopy[i]=='/'))
			{
				number = number++;
			}
		}
		return number;
}
void Deletestaff()
{
	system("cls");
	string staffID;
	cout << "~~~ DELETE Staff Menu ~~~" << endl<<endl;
	cout << "Enter Staff ID You Want To Delete ['m' to Menu] : ";
	cin >> staffID;
	if (staffID == "m" || staffID == "M")
	{
		AdminMainmenu();
	}
	else
	{
		string search_query = "select count(*) from staff where STAFF_ID = '" + staffID + "'";
		const char* q = search_query.c_str();
		qstate = mysql_query(conn, q);

		mysql_free_result(res);
		res = mysql_store_result(conn);
		row = mysql_fetch_row(res);

		if (atoi(row[0]) < 1)
		{
			cout << endl;
			cout << "Staff does not exist in database. Enter Again. " << endl;
			cout << "Please Check your spelling." << endl;
			cout << "Press any key to continue..." << endl;
			_getch();
			system("cls");
			Deletestaff();
		}
		else
		{
			string search_query2 = "select * from staff where STAFF_ID = '" + staffID + "'";
			const char* fi = search_query2.c_str();
			qstate = mysql_query(conn, fi);

			if (!qstate)
			{
				cout << setw(11) << "STAFF_ID" << setw(25) << "STAFF_NAME" << setw(9) << "   " << "   STAFF_IC" << setw(28) << 
                "  STAFF_PHONENUMBER";
				//Color(7);
				cout << endl<<endl;

				res = mysql_store_result(conn);
				while (row = mysql_fetch_row(res))
				{
					cout << setw(9) << row[0] << setw(27) << row[1] << setw(23) << row[2] << setw(20) << row[3]<<endl<<endl;
				}
			}
			else
				cout << "Query Execution Problem!" << mysql_errno(conn) << endl;

			char choose;
			cout << "Are You Sure To Delete This Staff ? ['y' or 'N'] : ";
			cin >> choose;
			if (choose == 'y' || choose == 'Y')
			{
				string insert_query = "DELETE FROM staff WHERE `STAFF_ID`='" + staffID + "'";
				const char* q = insert_query.c_str(); // c_str converts string to constant char and this is required
				qstate = mysql_query(conn, q);

				if (!qstate)
				{
					string insert_query = "DELETE FROM users WHERE userID ='" + staffID + "'";
					const char* qi = insert_query.c_str(); // c_str converts string to constant char and this is required
					qstate = mysql_query(conn, qi);

					cout << endl << "Successfully deleted Staff in database." << endl;

					cout << "Press 'a' to delete more staff and 'b' to go to Menu : ";
					cin >> choose;

					if (choose == 'a' || choose == 'A')
					{
						system("cls");
						Deletestaff();
					}
					else if (choose == 'b' || choose == 'B')
					{
						system("cls");
						AdminMainmenu();
					}
				}
				else
				{
					cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
				}

			}
			if (choose == 'n' || choose == 'N')
			{
				Deletestaff();
			}
		}
	}

}
void UpdateStaffDetails()
{
	int stock = 0;
	string staff_id;
	int newquantity;
	system("cls");
	cout << "~~~ Update Staff Details Menu ~~~\n\n";

	cout << "Enter Staff ID : ";
	cin >> staff_id;  // global variable 
	cout << endl;
	string name, icnum, pnum, address;
	int chooseUpdate = 0;

	do
	{
		char choose;
		string search_query = "select STAFF_ID,STAFF_NAME,STAFF_IC,STAFF_PHONENUMBER,STAFF_ADDRESS from staff where STAFF_ID = '" + staff_id + "'";  

		const char* q = search_query.c_str();
		qstate = mysql_query(conn, q);
		res = mysql_store_result(conn);
		while (row = mysql_fetch_row(res))
		{
			system("cls");
			cout << "\n\n~~~ Update Staff Details Menu ~~~\n\n";
			cout << "--- Current Details of Staff ---" << endl << endl;
			cout << "                                                                                              Press 'x' to exit" << endl;
			cout << "Staff ID : " << row[0] << "(Uneditable)"
				<< "\n\n1. Name: " << row[1]
				<< "\n2. Ic number: " << row[2]
				<< "\n3. Phone Number:" << row[3]
				<< "\n4. Address:" << row[4]
				<< "\n5. Save";
		}
		cout << "\nChoose one : ";
		cin >> chooseUpdate;
		cin.ignore(1, '\n');
		if (chooseUpdate == 1)
		{
			cout << "insert New name :";
			getline(cin, name);
			string update_query = "update staff set STAFF_NAME= '" + name + "' where STOCKS_ID = '" + staff_id + "'";
			const char* q = update_query.c_str();
			qstate = mysql_query(conn, q);

			string update_query2 = "update users set username ='" +name  + "'where userID = '" + staff_id + "'";
			const char* qi = update_query2.c_str();
			qstate = mysql_query(conn, qi);

		}
		else if (chooseUpdate == 2)
		{
			cout << "Insert New IC number : ";
			cin >> icnum;
			string update_query = "update staff set STAFF_IC = '" + icnum + "' where STAFF_ID = '" + staff_id + "'"; //

			const char* q = update_query.c_str();
			qstate = mysql_query(conn, q);
		}
		else if (chooseUpdate == 3)
		{
			cout << "insert new Phone number :";
			getline(cin, pnum);
			string update_query = "update staff set STAFF_PHONENUMBER ='" + pnum + "'where STAFF_ID = '" + staff_id + "'";

			const char* q = update_query.c_str();
			qstate = mysql_query(conn, q);
		}
		else if (chooseUpdate == 4)
		{
			cout << "insert New Adress : ";
			getline(cin, address);
			string update_query = "update staff set STAFF_ADDRESS = '" + address + "'where STAFF_ID= '" + staff_id + "'";

			const char* q = update_query.c_str();
			qstate = mysql_query(conn, q);
		}
		else if (chooseUpdate == 5)
		{
			cout << "\n\nThe change have been saved...\n\n\n";
			string select_query = "select * from staff where STAFF_ID = '" + staff_id + "'";

			const char* q = select_query.c_str();
			qstate = mysql_query(conn, q);

			cout << setw(11) << "STAFF_ID" << setw(25) << "STAFF_NAME" << setw(9) << "   " << "   STAFF_IC" << setw(28) <<
				"  STAFF_PHONENUMBER" << setw(30) << "   STAFF_ADDRESS" << endl;
			//Color(7);
			cout << endl;

			res = mysql_store_result(conn);
			while (row = mysql_fetch_row(res))
			{
				cout << setw(9) << row[0] << setw(27) << row[1] << setw(23) << row[2] << setw(20) << row[3] << setw(38) << row[4] << endl << endl;
			}
			cout << "\n\n\n";

			do
			{
				cout << "Do you want update another Staff? (y/n): ";
				cin >> choose;
				if (choose == 'y' || choose == 'Y')
					UpdateStaffDetails();
				else if (choose == 'n' || choose == 'N')
					AdminMainmenu();
				cout << "Hello Hallo Bye bye " << endl;
			} while (choose != 'y' && choose != 'Y' && choose != 'n' && choose != 'N');
		}
		else
		{
			cout << "\n";
			cout << "Wrong choice.Please enter again!" << endl;
			cout << "Please Enter your choice : ";
			cin >> choose;
		}
	} while (true);
}

void Viewstaff()
{
	system("cls");
	int choice;

	cout << "~~~ View Staff Menu ~~~\n";

	cout << "Do you want to view all staff or search specific staff?" << endl;
	cout << "Press 1 : for viewing all staff." << endl;
	cout << "Press 2 : for searching specific staff." << endl;
	cout << "Press 3 : exit View" << endl;
	cin >> choice;

	switch (choice)
	{
	case 1:
		system("cls");
		cout << "\t\t\t\t------- List of All Staff -------" << endl << endl;

		qstate = mysql_query(conn, "select * from staff");

		if (!qstate)
		{
			cout << setw(11) << "STAFF_ID" << setw(25) << "STAFF_NAME" << setw(9) << "   " << "   STAFF_IC" << setw(28) <<
				"  STAFF_PHONENUMBER" << setw(30) << "   STAFF_ADDRESS" << endl;
			//Color(7);
			cout << endl << endl;

			res = mysql_store_result(conn);
			while (row = mysql_fetch_row(res))
			{
				cout << setw(9) << row[0] << setw(27) << row[1] << setw(23) << row[2] << setw(20) << row[3] << setw(38) << row[4] << endl << endl;
			}
		}
		else
			cout << "Query Execution Problem!" << mysql_errno(conn) << endl;

		cout << "Press any key to continue...." << endl;
		_getch();
		cout << endl << endl;
		system("cls");
		AdminMainmenu();

	case 2:
		Searchstaff();
	case 3:
		AdminMainmenu();
	default:
		cout << "Wrong input. Please enter Again." << endl;
		cin.clear();   //clears the error flag on cin (so that future I/O operations will work correctly)
		system("PAUSE");
		cin.ignore(10, '\n');
		Viewstaff();
		break;
	}
}

void Searchstaff()
{
	system("cls");
	string staffid, staffname, staffic, staffaddress;
	char choice;
	cin.ignore(1, '\n');

	cout << "Please Enter what types of searched you want to use : " << endl;
	cout << "1) Search Staff by ID.\n";
	cout << "2) Search Staff by name.\n";
	cout << "3) Search Staff by ic number.\n";
	cout << "4) Search Staff by address.\n";
	cout << "5) exit search.\n";
	cout << "Enter your Choice :";
	cin >> choice;
	cout << endl;

	cin.ignore();

	do
	{
		if (choice == '1')   
		{
			cout << "Enter ID : ";
			cin >> staffid;

			string search_query2 = "select count(*) from staff where STAFF_ID = '" + staffid + "'";
			const char* fi = search_query2.c_str();
			qstate = mysql_query(conn, fi);

			mysql_free_result(res);
			res = mysql_store_result(conn);
			row = mysql_fetch_row(res);

			if (atoi(row[0]) < 1)
			{
				cout << "the staff you want to search does not exits..." << endl;
				cout << "Please Check your spelling" << endl;
				cout << "Press any key to re enter again..." << endl;
				_getch();
				Searchstaff();
			}

			cout << endl;
			cout << "\t\t\t\t--- List of Searched Staff ---" << endl << endl;

			string search_query = "select * from staff where STAFF_ID = '" + staffid + "'";
			const char* q = search_query.c_str();
			qstate = mysql_query(conn, q);

			if (!qstate)
			{
				cout << setw(11) << "STAFF_ID" << setw(25) << "STAFF_NAME" << setw(9) << "   " << "   STAFF_IC" << setw(28) <<
					"  STAFF_PHONENUMBER" << setw(30) << "   STAFF_ADDRESS" << endl;
				//Color(7);
				cout << endl << endl;

				res = mysql_store_result(conn);
				while (row = mysql_fetch_row(res))
				{
					cout << setw(9) << row[0] << setw(27) << row[1] << setw(23) << row[2] << setw(20) << row[3] <<setw(38)<<row[4]<< endl << endl;
				}

			}
			else
				cout << "Query Execution Problem!" << mysql_errno(conn) << endl;

			cout << endl << endl;
			AdminSearchAsker();
		}
		
		if (choice == '2') 
		{
			cout << "Enter name: ";
			getline(cin, staffname);

			string search_query2 = "select count(*) from staff where STAFF_NAME like '%" + staffname + "%'";
			const char* fi = search_query2.c_str();
			qstate = mysql_query(conn, fi);

			mysql_free_result(res);
			res = mysql_store_result(conn);
			row = mysql_fetch_row(res);

			if (atoi(row[0]) < 1)
			{
				cout << "the staff you want to search does not exits..." << endl;
				cout << "Please Check your spelling" << endl;
				cout << "Press any key to re enter again..." << endl;
				_getch();
				Searchstaff();
			}

			cout << endl;
			cout << "\t\t\t\t--- List of Searched Staff ---" << endl << endl;

			string search_query = "select * from staff where STAFF_NAME like '%" + staffname + "%'";
			const char* q = search_query.c_str();
			qstate = mysql_query(conn, q);


			if (!qstate)
			{
				cout << setw(11) << "STAFF_ID" << setw(25) << "STAFF_NAME" << setw(9) << "   " << "   STAFF_IC" << setw(28) <<
					"  STAFF_PHONENUMBER" << setw(30) << "   STAFF_ADDRESS" << endl;
				//Color(7);
				cout << endl << endl;

				res = mysql_store_result(conn);
				while (row = mysql_fetch_row(res))
				{
					cout << setw(9) << row[0] << setw(27) << row[1] << setw(23) << row[2] << setw(20) << row[3] << setw(38) << row[4] << endl << endl;
				}

			}
			else
				cout << "Query Execution Problem!" << mysql_errno(conn) << endl;

			cout << endl << endl;
			AdminSearchAsker();
		}

		if (choice == '3') 
		{
			cout << "Enter IC number: ";
			cin >> staffic;

			string search_query2 = "select count(*) from staff where STAFF_IC = '" + staffic + "'";
			const char* fi = search_query2.c_str();
			qstate = mysql_query(conn, fi);

			mysql_free_result(res);
			res = mysql_store_result(conn);
			row = mysql_fetch_row(res);

			if (atoi(row[0]) < 1)
			{
				cout << "the staff you want to search does not exits..." << endl;
				cout << "Please Check your spelling" << endl;
				cout << "Press any key to re enter again..." << endl;
				_getch();
				Searchstaff();
			}

			cout << endl;
			cout << "\t\t\t\t--- List of Searched Stocks ---" << endl << endl;

			string search_query = "select * from staff where STAFF_IC = '" + staffic + "'";
			const char* q = search_query.c_str();
			qstate = mysql_query(conn, q);

			if (!qstate)
			{
				cout << setw(11) << "STAFF_ID" << setw(25) << "STAFF_NAME" << setw(9) << "   " << "   STAFF_IC" << setw(28) <<
					"  STAFF_PHONENUMBER" << setw(30) << "   STAFF_ADDRESS" << endl;
				//Color(7);
				cout << endl << endl;

				res = mysql_store_result(conn);
				while (row = mysql_fetch_row(res))
				{
					cout << setw(9) << row[0] << setw(27) << row[1] << setw(23) << row[2] << setw(20) << row[3] << setw(38) << row[4] << endl << endl;
				}

			}
			else
				cout << "Query Execution Problem!" << mysql_errno(conn) << endl;

			cout << endl << endl;
			AdminSearchAsker();

		}

		if (choice == '4') 
		{
			cout << "Enter Staff address : ";
			getline(cin, staffaddress);

			string search_query2 = "select count(*) from staff where STAFF_ADDRESS like '%" + staffaddress + "%'";
			const char* fi = search_query2.c_str();
			qstate = mysql_query(conn, fi);

			mysql_free_result(res);
			res = mysql_store_result(conn);
			row = mysql_fetch_row(res);

			if (atoi(row[0]) < 1)
			{
				cout << "the staff you want to search does not exits..." << endl;
				cout << "Please Check your spelling" << endl;
				cout << "Press any key to re enter again..." << endl;
				_getch();
				Searchstaff();
			}

			cout << endl;
			cout << "\t\t\t\t--- List of Searched Stocks ---" << endl << endl;

			string search_query = "select * from staff where STAFF_ADDRESS like '%" + staffaddress + "%'";
			const char* q = search_query.c_str();
			qstate = mysql_query(conn, q);

			if (!qstate)
			{
				cout << setw(11) << "STAFF_ID" << setw(25) << "STAFF_NAME" << setw(9) << "   " << "   STAFF_IC" << setw(28) <<
					"  STAFF_PHONENUMBER" << setw(30) << "   STAFF_ADDRESS" << endl;
				//Color(7);
				cout << endl << endl;

				res = mysql_store_result(conn);
				while (row = mysql_fetch_row(res))
				{
					cout << setw(9) << row[0] << setw(27) << row[1] << setw(23) << row[2] << setw(20) << row[3] << setw(38) << row[4] << endl << endl;
				}

			}
			else
				cout << "Query Execution Problem!" << mysql_errno(conn) << endl;

			cout << endl << endl;
			AdminSearchAsker();
		}
		
		if (choice == '5')
		{
			system("cls");
			Viewstaff();
		}

		else
		{
			cout << "\n";
			cout << "Wrong choice.Please enter again!" << endl;
			cout << "Press any key to continue..." << endl;
			_getch();
			Searchstaff();
		}

	} while (true);

}

void AdminSearchAsker()
{
	char choose;
	do
	{
		cout << "Do you want to search another staff ? (y/n)" << endl;
		cin >> choose;
		if (choose == 'y' || choose == 'Y')
			Searchstaff();
		else if (choose == 'n' || choose == 'N')
		{
			system("cls");
			AdminMainmenu();
		}
		cout << "Hello Hallo Bye bye " << endl;
	} while (choose != 'y' && choose != 'Y' && choose != 'n' && choose != 'N');
}

void Staffmenu()
{
	system("cls");
	cout << "**********************************" << endl;
	cout << "JMK Warehouse System" << endl;
	cout << "**********************************" << endl << endl;

	int choose;
	char exitacc;
	//Color(228);
	cout << "---Staff Menu ---" << endl;

	cout << "1. Register Stocks" << endl;
	cout << "2. View Stocks " << endl;
	cout << "3. Update Stocks" << endl;
	cout << "4. Checkout Stocks " << endl;
	cout << "5. Staff Account details" << endl;
	cout << "6. Logout " << endl<<endl;
	cout << "Please Enter your Choice : ";
	cin >> choose;

	switch (choose)
	{
	case 1:
		RegisterStocks();
		break;
	case 2:
		ViewStocks();
		break;
	case 3:
		UpdateStocks();
		break;
	case 4:
		CheckoutStocks();
		break;
	case 6:
	LogOut:
		cout << endl;
		cout << "Loging out.. Are you sure? (y/N): ";
		cin >> exitacc;
		if (exitacc == 'y' || exitacc == 'Y') {
			main();
		}
		else if (exitacc == 'n' || exitacc == 'N') {
			system("cls");
			Staffmenu();
		}
		else {
			cout << "Please re enter again." << endl;
			goto LogOut;
		}
		break;
	case 5:
		StaffAccDetails();
		break;
	default:
		cout << "Your Choice is not in the list. Please Enter again. Press Enter To Continue.... " << endl;
	}
}

void StaffAccDetails()  //untuk edit username dan password staff
{
	
	string username,userpassword;
	char choose,choose2;
	system("cls");
	cout << "--- Staff Account Settings ---\n\n";
	cout << "Press 1 to edit username, Press 2 to edit password :                                               [press 'x' to exit ]" << endl;
	cin >> choose;
	cout << endl;

	if (choose == '1')
	{
		string search_query = "select username from users where userID = '" + userID + "'";  
		const char* q = search_query.c_str();
		qstate = mysql_query(conn, q);

		res = mysql_store_result(conn);
		while (row = mysql_fetch_row(res))
		{
			cout << "Current Username : " << row[0] << endl;		
		}

		cin.ignore(1, '\n');
		cout << "New Username : ";
		getline(cin, username);
		cout << endl;
		cout << "Are you confirm to change your username(y/N) :" << endl;
		cin >> choose2;
		if (choose2 == 'y' || choose2 == 'Y')
		{
			string update_query = "update users set username= '" + username + "' where userID = '" + userID + "'";
			const char* qi = update_query.c_str();
			qstate = mysql_query(conn, qi);

			string insert_query2 = "insert into staff (STAFF_NAME) values ('" + username + "')";
			const char* fi = insert_query2.c_str();
			qstate = mysql_query(conn, fi);

			cout << endl;
			cout << "Your username is succesfully updated..." << endl; 
			_getch();
			system("cls");
			Staffmenu();

		}
		if (choose2 == 'n' || choose2 == 'N')
		{
			system("cls");
			StaffAccDetails();
		}
		else if (choose2 == 'x' || choose2 == 'X')
		{
			system("cls");
			Staffmenu();
		}
		else
		{
			system("cls");
			Staffmenu();
		}
	}
	if (choose == '2')
	{
	Password:
		string search_query = "select userPassword from users where userID = '" + userID + "'";  // Tak tahu knapa salah.
		const char* q = search_query.c_str();
		qstate = mysql_query(conn, q);

		res = mysql_store_result(conn);
		while (row = mysql_fetch_row(res))
		{
			cout << "Please Enter your current password : ";
			cin >> userpassword;
			if (userpassword == row[0])
			{
				cout << "Enter New Password :";
				cin >> userpassword;
				cout << "Are you confirm to change your password(y/N) :" << endl;
				cin >> choose2;
				if (choose2 == 'y' || choose2 == 'Y')
				{
					string update_query = "update users set userPassword= '" + userpassword + "' where userID = '" + userID + "'";
					const char* qi = update_query.c_str();
					qstate = mysql_query(conn, qi); 

					cout << "Your Password have been changed." << endl;
					_getch();
					system("cls");
					Staffmenu();
				}
				if (choose2 == 'n' || choose2 == 'N')
				{
					system("cls");
					StaffAccDetails();
				}
				else if (choose2 == 'x' || choose2 == 'X')
				{
					system("cls");
					Staffmenu();
				}
				else
				{
					system("cls");
					Staffmenu();
				}

			}
			else
			{
				cout << "Wrong Password. Please Re enter again.\n";
				_getch();
				system("cls");

				goto Password;
			}
			
		}
	}
}

void viewInOutStocks()
{
	system("cls");
	string id, name, price, supplier;
	int choice;
	cin.ignore(1, '\n');

	cout << "Please Enter what types of searched you want to use : " << endl;
	cout << "1) Search Stocks by stock ID.\n";
	cout << "2) Search Stocks by stock name.\n";
	cout << "3) exit search.\n";
	cout << "Enter your Choice :";
	cin >> choice;
	cout << endl;

	cin.ignore();

	do
	{
		if (choice == 1)   
		{
			cout << "Enter ID : ";
			cin >> id;

			string search_query2 = "select count(*) from stocks where STOCKS_ID = '" + id + "'";  //utk check samada stok wujud ke tak
			const char* fi = search_query2.c_str();
			qstate = mysql_query(conn, fi);

			mysql_free_result(res);
			res = mysql_store_result(conn);
			row = mysql_fetch_row(res);

			if (atoi(row[0]) < 1)
			{
				cout << "the search results do not exits..." << endl;
				cout << "Press any key to continue..." << endl;
				_getch();
				viewInOutStocks();
			}

			cout << endl;
			cout << "\t\t\t\t--- List of Searched Details ---" << endl << endl;

			string search_query = "select STOCKS_ID,STOCKS_NAME,STOCKS_CATEGORY,STOCKS_QUANTITY,STOCKS_LOCATION,STOCKS_INDATE,STOCKS_OUTDATE,MODIFIED_BY from in_out_stocks where STOCKS_ID = '" + id + "' ";

			const char* q = search_query.c_str();
			qstate = mysql_query(conn, q);

			if (!qstate) 
			{
				cout << setw(11) << "STOCKS_ID" << setw(17) << "STOCKS_NAME" << setw(9) << "   " << "STOCKS_CATEGORY" << setw(20) << "    STOCK_QUANTITY" << setw(5) << "    STOCKS_LOCATION" << setw(5) << "    STOCKS_INDATE" << setw(20) << "STOCKS_OUTDATE" << setw(20) << "MODIFIED BY" << endl;
				//Color(7);
				cout << endl;

				res = mysql_store_result(conn);
				while (row = mysql_fetch_row(res))
				{
					cout << setw(9) << row[0] << setw(18) << row[1] << setw(22) << row[2] << setw(17) << row[3] << setw(20) << row[4] << setw(15) << "   " << setw(1) << row[5] << setw(18) << row[6] << setw(24) << row[7] << endl << endl;
				}

			}
			else
				cout << "Query Execution Problem!" << mysql_errno(conn) << endl;

			barchart();  //utk display stock chart
			cout << endl << endl;
			char choose2;
			cout << "Do you want to make a searching again?(y/N)\n";
			cin >> choose2;
			if (choose2 == 'y' || choose2 == 'Y')
			{
				viewInOutStocks();
			}
			else
			{
				AdminStockMenu();
			}
		}
		else if (choice == 2)
		{
			string name;
			cout << "Enter name : ";
			getline(cin, name);

			string search_query2 = "select count(*) from stocks where STOCKS_NAME like '%" + name + "%'";  //utk check samada stok wujud ke tak
			const char* fi = search_query2.c_str();
			qstate = mysql_query(conn, fi);

			mysql_free_result(res);
			res = mysql_store_result(conn);
			row = mysql_fetch_row(res);

			if (atoi(row[0]) < 1)
			{
				cout << "the search results do not exits..." << endl;
				cout << "Press any key to continue..." << endl;
				_getch();
				viewInOutStocks();
			}

			cout << endl;
			cout << "\t\t\t\t--- List of Searched Details ---" << endl << endl;

			string search_query = "select STOCKS_ID,STOCKS_NAME,STOCKS_CATEGORY,STOCKS_QUANTITY,STOCKS_LOCATION,STOCKS_INDATE,STOCKS_OUTDATE,MODIFIED_BY from in_out_stocks where STOCKS_NAME like '%" + name + "%' ";

			const char* q = search_query.c_str();
			qstate = mysql_query(conn, q);

			if (!qstate)  
			{
				cout << setw(11) << "STOCKS_ID" << setw(17) << "STOCKS_NAME" << setw(9) << "   " << "STOCKS_CATEGORY" << setw(20) << "    STOCK_QUANTITY" << setw(5) << "    STOCKS_LOCATION" << setw(5) << "    STOCKS_INDATE" << setw(20) << "STOCKS_OUTDATE" << setw(20) << "MODIFIED BY" << endl;
				//Color(7);
				cout << endl;

				res = mysql_store_result(conn);
				while (row = mysql_fetch_row(res))
				{
					cout << setw(9) << row[0] << setw(18) << row[1] << setw(22) << row[2] << setw(17) << row[3] << setw(20) << row[4] << setw(15) << "   " << setw(1) << row[5] << setw(18) << row[6] << setw(24) << row[7] << endl << endl;
				}

			}
			else
				cout << "Query Execution Problem!" << mysql_errno(conn) << endl;

			barchart();  //utk display stock chart
			cout << endl << endl;
			char choose2;
			cout << "Do you want to make a searching again?(y/N)\n";
			cin >> choose2;
			if (choose2 == 'y' || choose2 == 'Y')
			{
				viewInOutStocks();
			}
			else
			{
				AdminStockMenu();
			}
		
		}
		else
		 AdminStockMenu();
		
	} while (true);

}

void AdminStockMenu() //ini utk admin stock menu
{
	system("cls");

	int choose ;
	//Color(228);
	cout << "---Admin Stocks Menu ---" << endl<<endl;
	//Color(7);
	cout << "1. Register Stocks " << endl;
	cout << "2. View Stocks " << endl;
	cout << "3. Update Stocks" << endl;
	cout << "4. Checkout Stocks " << endl;
	cout << "5. View stocks in and out status " << endl;
	cout << "6. exit Stocks Menu" << endl;
	cout << "Please Enter your Choice : ";
	cin >> choose;

	switch (choose)
	{
	case 1:
		RegisterStocks();
		break;
	case 2:
		ViewStocks();
		break;
	case 3:
		UpdateStocks();
		break;
	case 4:
	    CheckoutStocks();
		break;
	case 5:
		viewInOutStocks();
		break;
	case 6:
		AdminMainmenu();
		break; 
	default:
		cout << "Your Choice is not in the list. Please Enter again. Press Enter To Continue.... " << endl;
		_getch();
		system("cls");
		AdminStockMenu();
	}
}


void RegisterStocks()
{
	system("cls");
	string name, ID, price, quantity, location, supplier, product_category, date;//month,year;

	char choose;
	cout << "---Stock Registeration---" << endl << endl;
	cin.ignore(1, '\n'); 

	cout << "What is the Product category :                                                                        Press 'x' to exit" << endl;
	cout << "a) Healthcare" << endl;
	cout << "b) furniture" << endl;
	cout << "c) Kitchenware" << endl;
	cout << "d) frozenfood" << endl;
	cout << "e) food" << endl;
	cout << "f) vehicle part" << endl << endl;
	cout << "Please Select Your Product Category : ";
	cin >> choose;
	
	{
		if (choose == 'a'|| choose == 'A')
		{
			product_category = "Healthcare";
			string search_query2 = "select count(*) from stocks where STOCKS_CATEGORY = '" + product_category + "'";
			const char* fi = search_query2.c_str();
			qstate = mysql_query(conn, fi);

			mysql_free_result(res);
			res = mysql_store_result(conn);
			row = mysql_fetch_row(res);

			if (atoi(row[0]) > sectionsize)
			{
				cout << endl;
				cout << "Healthcare Section is full!!!" << endl;
				cout << "Sorry...You cannot put any more stocks in this section..." << endl << endl;
				cout << "there is only " << atoi(row[0]) << " space left in this section" << endl;
				cout << "Press any key to continue..." << endl;
				_getch();
				system("cls");
				MenuChoosing();
			}

		}

		if (choose == 'b' || choose == 'B')
		{
			product_category = "furniture";
			string search_query2 = "select count(*) from stocks where STOCKS_CATEGORY = '" + product_category + "'";
			const char* fi = search_query2.c_str();
			qstate = mysql_query(conn, fi);

			mysql_free_result(res);
			res = mysql_store_result(conn);
			row = mysql_fetch_row(res);

			if (atoi(row[0]) > sectionsize)
			{
				cout << endl;
				cout << "furniture Section is full!!!" << endl;
				cout << "Sorry...You cannot put any more stocks in this section..." << endl << endl;
				cout << "there is only " << atoi(row[0]) << " space left in this section" << endl;
				cout << "Press any key to continue..." << endl;
				_getch();
				system("cls");
				MenuChoosing();
			}

		}


		if (choose == 'c' || choose == 'C')
		{
			product_category = "Kitchenware";
			string search_query2 = "select count(*) from stocks where STOCKS_CATEGORY = '" + product_category + "'";
			const char* fi = search_query2.c_str();
			qstate = mysql_query(conn, fi);

			mysql_free_result(res);
			res = mysql_store_result(conn);
			row = mysql_fetch_row(res);

			if (atoi(row[0]) > sectionsize)
			{
				cout << endl;
				cout << "Kitchenware Section is full!!!" << endl;
				cout << "Sorry...You cannot put any more stocks in this section..." << endl << endl;
				cout << "there is only " << atoi(row[0]) << " space left in this section" << endl;
				cout << "Press any key to continue..." << endl;
				_getch();
				system("cls");
				MenuChoosing();
			}

		}


		if (choose == 'd' || choose == 'D')
		{
			product_category = "frozenfood";
			string search_query2 = "select count(*) from stocks where STOCKS_CATEGORY = '" + product_category + "'";
			const char* fi = search_query2.c_str();
			qstate = mysql_query(conn, fi);

			mysql_free_result(res);
			res = mysql_store_result(conn);
			row = mysql_fetch_row(res);

			if (atoi(row[0]) > sectionsize)
			{
				cout << endl;
				cout << "Frozen food Section is full!!!" << endl;
				cout << "Sorry...You cannot put any more stocks in this section..." << endl << endl;
				cout << "there is only " << atoi(row[0]) << " space left in this section" << endl;
				cout << "Press any key to continue..." << endl;
				_getch();
				system("cls");
				MenuChoosing();
			}

		}


		if (choose == 'e' || choose == 'E')
		{
			product_category = "food";
			string search_query2 = "select count(*) from stocks where STOCKS_CATEGORY = '" + product_category + "'";
			const char* fi = search_query2.c_str();
			qstate = mysql_query(conn, fi);

			mysql_free_result(res);
			res = mysql_store_result(conn);
			row = mysql_fetch_row(res);

			if (atoi(row[0]) > sectionsize)
			{
				cout << endl;
				cout << "Food Section is full!!!" << endl;
				cout << "Sorry...You cannot put any more stocks in this section..." << endl << endl;
				cout << "there is only " << atoi(row[0]) << " space left in this section" << endl;
				cout << "Press any key to continue..." << endl;
				_getch();
				system("cls");
				MenuChoosing();
			}

		}


		if (choose == 'f' || choose == 'F')
		{
			product_category = "Vehiclepart";
			string search_query2 = "select count(*) from stocks where STOCKS_CATEGORY = '" + product_category + "'";
			const char* fi = search_query2.c_str();
			qstate = mysql_query(conn, fi);

			mysql_free_result(res);
			res = mysql_store_result(conn);
			row = mysql_fetch_row(res);

			if (atoi(row[0]) > sectionsize)
			{
				cout << endl;
				cout << "Vehiclepart Section is full!!!" << endl;
				cout << "Sorry...You cannot put any more stocks in this section..." << endl << endl;
				cout << "there is only " << atoi(row[0]) << " space left in this section" << endl;
				cout << "Press any key to continue..." << endl;
				_getch();
				system("cls");
				MenuChoosing();
			}

		}
	    else if(choose == 'x'||choose =='X')
		{
				cout << "hello good\n";
				system("pause");
				if (typecp == "a")
				{
					AdminStockMenu();
				}
				if (typecp == "b")
				{
					Staffmenu();
				}	
		}  
    }
	
	cout << "your stock category is " << product_category<<endl;
	cin.ignore(1, '\n'); 
	cout << "Product ID : ";
	ID:
	getline(cin, ID);

	string search_query = "select count(*) from stocks where STOCKS_ID = '" + ID + "'";
	const char* m = search_query.c_str();
	qstate = mysql_query(conn, m);

	mysql_free_result(res);
	res = mysql_store_result(conn);
	row = mysql_fetch_row(res);

	if (atoi(row[0]) > 0)
	{
		cout << "   Error. The stock ID you inserted has been used." << endl; //////
		cout << "   Please Re enter again." << endl;
		cout << "  Enter stock ID : ";
		goto ID;
	}


	cout << "Name of Product : ";
	getline(cin, name);
	cout << "Quantity of Product : ";
	cin>>quantity;

	{
		string search_query2 = "select count(*) from stocks where STOCKS_CATEGORY = '" + product_category + "'";
		const char* fi = search_query2.c_str();
		qstate = mysql_query(conn, fi);

		mysql_free_result(res);
		res = mysql_store_result(conn);
		row = mysql_fetch_row(res);
		
		stringstream ss;  //line 334-337. to convert string to integer value
		int i;
		ss << quantity;   // extact the value from string
		ss >> i;          // i adalah wakil utk quantity dlm integer

		if (atoi(row[0])+i > sectionsize)
		{
			cout << endl;
			cout << product_category<<" section is full!!!" << endl;
			cout << "Sorry...You cannot put any more stocks in this section..." << endl << endl;
			cout << "there is only " << sectionsize-(atoi(row[0]) + i) << " space left in this section" << endl;
			cout << "Press any key to continue..." << endl;
			_getch();
			system("cls");
			MenuChoosing();
		}
	}
	cin.ignore(1, '\n');
	cout << "Stock Location : ";
	ID2:
	getline(cin, location);

	string search_query4 = "select count(*) from stocks where STOCKS_LOCATION = '" + location + "'";
	const char* mq = search_query4.c_str();
	qstate = mysql_query(conn, mq);

	mysql_free_result(res);
	res = mysql_store_result(conn);
	row = mysql_fetch_row(res);

	if (atoi(row[0]) > 0)
	{
		cout << "   Error. The stock location you inserted has been used." << endl; //////
		cout << "   Please Re enter again." << endl;
		cout << "  Enter stock location : ";
		goto ID2;
	}

	cout << "Price : ";
	getline(cin, price);
	cout << "Supplier name :";
	getline(cin, supplier);
	cout << endl;

	cout << "Enter Date (eg. 00/00/0000): ";
	Enter:
	getline(cin,date);
	if (checkinput(date) > 0)
	{
		cout << "    Error. Please enter again : ";
		goto Enter;
	}
	
	string indate = date; "/"; 
	string outdate = "     -";
	
	string insert_query2 = "insert into in_out_stocks(STOCKS_ID,STOCKS_NAME,STOCKS_CATEGORY,STOCKS_QUANTITY,STOCKS_LOCATION,STOCKS_INDATE,STOCKS_OUTDATE,MODIFIED_BY) values ('" + ID + "','" + name + "','" + product_category + "','" + quantity + "', '" + location + "','" +indate + "','" + outdate + "','" + userID + "')";
	const char* qi = insert_query2.c_str();
	qstate = mysql_query(conn, qi);
	

	string insert_query = "insert into stocks(STOCKS_ID,STOCKS_NAME,STOCKS_CATEGORY,STOCKS_QUANTITY, STOCKS_LOCATION,STOCKS_PRICE,Supplier_name,RegisterarID) values ('" + ID + "','" + name + "','"+product_category+"','" + quantity + "', '" + location + "','" + price + "','" + supplier + "','"+userID+"')";

	const char* q = insert_query.c_str();
	qstate = mysql_query(conn, q);

	if (!qstate)
		cout << endl << "Stocks is successful added in database. " << endl;
	else
		cout << "Query Execution Prolem!" << mysql_errno(conn) << endl;
	do
	{
		cout << "Do you want add another Stock? (y/n): ";
		cin >> choose;
		if (choose == 'y' || choose == 'Y')
			RegisterStocks();
		else if (choose == 'n' || choose == 'N')
			MenuChoosing();
			cout << "Hello Hallo Bye bye " << endl;
	} while (choose != 'y' && choose != 'Y' && choose != 'n' && choose != 'N');

}


void ViewStocks()     //viewstocks function dh digabungkan dgn Searchstock function
{
	system("cls");
	int choice;
	cout << "--- View Stocks Menu ---\n\n";
	cout << "Do you want to view all stocks or search specific stocks?                                             Press '3' to exit" << endl;
	cout << "Press 1 : for viewing all stocks." << endl;
	cout << "Press 2 : for searching specific stocks." << endl;
	cin >> choice;

	switch (choice)
	{
	case 1:
		system("cls");
		cout << "\t\t\t\t------- List of All Stocks -------" << endl << endl;

		qstate = mysql_query(conn, "select * from stocks");

		if (!qstate)
		{
			cout << setw(11) << "STOCKS_ID" << setw(17) << "STOCKS_NAME" << setw(9) << "   " << "STOCKS_CATEGORY" << setw(20) << "    STOCK_QUANTITY" << setw(5) << "    STOCKS_LOCATION" << setw(5) << "    STOCKS_Price" << setw(20) << "supplier_name" <<setw(20)<<"RegisterarID"<< endl;
			//Color(7);
			cout << endl;

			res = mysql_store_result(conn);
			while (row = mysql_fetch_row(res))
			{
				cout << setw(9) << row[0] << setw(18) << row[1] << setw(22) << row[2] << setw(17) << row[3] << setw(20) << row[4] << setw(15) << "RM " << setw(1) << row[5] << setw(18) << row[6] << setw(24) << row[7] << endl << endl;
			}
		}
		else
			cout << "Query Execution Problem!" << mysql_errno(conn) << endl;

		barchart();  //utk display stock chart

		cout << "Press any key to continue...." << endl;
		_getch();
		cout << endl << endl;
		system("cls");
		MenuChoosing();
	
	case 2:
		SearchStocks();
	case 3:
		{
			cout << "hello good\n";
			if (typecp == "a")
			{
				AdminStockMenu();
			}
			if (typecp == "b")
			{
				Staffmenu();
			}
			else
				cout << "nooooooooooooooooooooooooooooooooooooooo\n";

		}
	default:
		cout << "Wrong input. Please enter Again." << endl;
		cin.ignore(100, '\n');
		_getch();
		ViewStocks();
	}
	
}

void barchart()
{
	int healthcare, furniture, Kitchenware, frozenfood, food, vehiclepart;
	string select_query = "select count(STOCKS_CATEGORY) from stocks where STOCKS_CATEGORY = 'Healthcare'";
	const char* q = select_query.c_str();
	qstate = mysql_query(conn, q);

	mysql_free_result(res);
	res = mysql_store_result(conn);
	row = mysql_fetch_row(res);

	healthcare = atoi(row[0]);

	string select_query2 = "select count(STOCKS_CATEGORY) from stocks where STOCKS_CATEGORY = 'furniture'";
	const char* q2 = select_query2.c_str();
	qstate = mysql_query(conn, q2);

	mysql_free_result(res);
	res = mysql_store_result(conn);
	row = mysql_fetch_row(res);

	furniture = atoi(row[0]);

	string select_query3 = "select count(STOCKS_CATEGORY) from stocks where STOCKS_CATEGORY = 'Kitchenware'";
	const char* q3 = select_query3.c_str();
	qstate = mysql_query(conn, q3);

	mysql_free_result(res);
	res = mysql_store_result(conn);
	row = mysql_fetch_row(res);

	Kitchenware = atoi(row[0]);

	string select_query4 = "select count(STOCKS_CATEGORY) from stocks where STOCKS_CATEGORY = 'frozenfood'";
	const char* q4 = select_query4.c_str();
	qstate = mysql_query(conn, q4);

	mysql_free_result(res);
	res = mysql_store_result(conn);
	row = mysql_fetch_row(res);

	frozenfood = atoi(row[0]);

	string select_query5 = "select count(STOCKS_CATEGORY) from stocks where STOCKS_CATEGORY = 'food'";
	const char* q5 = select_query5.c_str();
	qstate = mysql_query(conn, q5);

	mysql_free_result(res);
	res = mysql_store_result(conn);
	row = mysql_fetch_row(res);

	food = atoi(row[0]);

	string select_query6 = "select count(STOCKS_CATEGORY) from stocks where STOCKS_CATEGORY = 'Vehiclepart'";
	const char* q6 = select_query6.c_str();
	qstate = mysql_query(conn, q6);

	mysql_free_result(res);
	res = mysql_store_result(conn);
	row = mysql_fetch_row(res);

	vehiclepart = atoi(row[0]);

	cout << endl;
	int value[] = { healthcare, furniture, Kitchenware, frozenfood, food, vehiclepart };
	string value_str[] = { " healthcare ", " furniture  ", " Kitchenware", " frozenfood ", " food       ", " vehiclepart" };

	cout << endl << endl;
	cout << "Total Stock Statistic\n";
	cout << "....................." << endl;
	for (int i = 0; i <= 5; i++)        // utk buat barchart
	{
		cout << "             ";
		for (int l = 0; l < (value[i] * 3); l++)
		{
			cout << "__";
		}
		cout << endl;
		cout << value_str[i]<< ":";
		for (int j = 0; j < value[i] * 3; j++)
		{
			cout << "__";
		}

		cout << "|" << setw(7) << value[i];
		cout << endl;
		/*
		cout << value_str[i] <<" :";
		for (int j = 0; j < value[i] * 3; j++)
		{
			cout << "____________";
		}
		//setw(30);
		cout << setw(6) << value[i];
		cout << endl;*/
	}
	cout << endl;
}


void UpdateStocks()
{
	int stock = 0;
	string stocks_id;
	int newquantity;

	system("cls");
	cout << "--- Update Stocks Menu ---" << endl<<endl;
	cout << "                                                                                                      Press 'x' to exit" << endl;
	cout << "Enter Stocks ID : ";
	cin >> stocks_id;  // global variable 


	string name, quantity, price, location, supplier;

	int chooseUpdate = 0;

	if (stocks_id == "x" || stocks_id == "X")
	{
		if (typecp == "a")
		{
			AdminStockMenu();
		}
		if (typecp == "b")
		{
			Staffmenu();
		}
	}

	string search_query2 = "select count(*) from stocks where STOCKS_ID = '" + stocks_id + "'";
	const char* fi = search_query2.c_str();
	qstate = mysql_query(conn, fi);

	mysql_free_result(res);
	res = mysql_store_result(conn);
	row = mysql_fetch_row(res);

	if (atoi(row[0]) < 1)
	{
		cout << endl;
		cout << "The stock you searched do not exits" << endl;
		cout << "Please re enter again" << endl << endl;
		cout << "Press any key to continue..." << endl;
		_getch();
		system("cls");
		UpdateStocks();
	}

	do
	{
		system("cls");
		char choose;
		string search_query = "select STOCKS_ID,STOCKS_NAME,STOCKS_QUANTITY,STOCKS_LOCATION,STOCKS_PRICE,Supplier_Name,RegisterarID from STOCKS where STOCKS_ID = '" + stocks_id + "'";  // Tak tahu knapa salah.

		const char* q = search_query.c_str();
		qstate = mysql_query(conn, q);
		res = mysql_store_result(conn);
		while (row = mysql_fetch_row(res))
		{
			cout << "--- Current Details of Stocks ---" << endl<<endl;
			cout << "Stocks ID : " << row[0] << "(Uneditable)"
			    << "\nStocks RegisterarID : " << row[6]<< "(Uneditable)"
				<< "\n\n1. Name: " << row[1]
				<< "\n2. Quantity: " << row[2]
				<< "\n3. Location:" << row[3]
				<< "\n4. Price: RM  " << row[4]
				<< "\n5. Supplier Name: " << row[5]
				<< "\n6. Save";
		}
		cout << "\nChoose one : ";
		cin >> chooseUpdate;
		cin.ignore(1, '\n');
		if (chooseUpdate == 1)
		{
			cout << "insert New name :";
			getline(cin, name);
			string update_query = "update stocks set STOCKS_NAME= '" + name + "' where STOCKS_ID = '" + stocks_id + "'";

			const char* q = update_query.c_str();
			qstate = mysql_query(conn, q);

		}
		else if (chooseUpdate == 2)
		{
			string search_query2 = "select STOCKS_QUANTITY from stocks where STOCKS_ID = '" + stocks_id + "'";
			const char* fi = search_query2.c_str();
			qstate = mysql_query(conn, fi);

			mysql_free_result(res);
			res = mysql_store_result(conn);
			row = mysql_fetch_row(res);
			 stock = atoi(row[0]);
			 cout << "   There is only " << sectionsize - atoi(row[0]) << " unit space in this section\n";
			
			cout << "Insert New Stock Quantity : ";
			cin >> newquantity;
			if (newquantity + atoi(row[0]) > sectionsize)
			{
				cout << "\n\n# # The stocks have exceed the section space by " << (newquantity + atoi(row[0])) - sectionsize << " unit.\n";
				cout << "# # To make a successful update. Follow this steps: 1) put only the right amount of quantity into this section.\n";
				cout << "                                                    2) After that, register balance stocks as a new stocks and\n";
				cout << "                                                       assign it with new id and location.\n\n ";
				system("pause");
				UpdateStocks();

			}
			quantity = to_string(stock + newquantity);
			string update_query = "update Stocks set STOCKS_QUANTITY = '" + quantity + "' where STOCKS_ID = '" + stocks_id + "'"; //

			const char* q = update_query.c_str();
			qstate = mysql_query(conn, q);
			string quantity_cp = quantity;

			string insert_query = "INSERT INTO in_out_stocks SELECT * FROM stocks";
			const char* qi = insert_query.c_str();
			qstate = mysql_query(conn, qi);

			cin.ignore(1000, '\n');
			string date;
			cout << "\nEnter Date (eg. 00/00/0000): ";
			getline(cin,date);
			string indate = date,outdate= "     -";

			string update_query2 = "update in_out_stocks set STOCKS_INDATE= '" + indate + "',STOCKS_OUTDATE = '"+outdate+"' where STOCKS_QUANTITY = '" + quantity_cp + "'"; 
			const char* qf = update_query2.c_str();
			qstate = mysql_query(conn, qf);
		}
		else if (chooseUpdate == 3)
		{
			cout << "insert Stocks_location :";
			getline(cin, location);
			string update_query = "update Stocks set STOCKS_LOCATION ='" + location + "'where STOCKS_ID = '" + stocks_id + "'";

			const char* q = update_query.c_str();
			qstate = mysql_query(conn, q);
		}
		else if (chooseUpdate == 4)
		{
			cout << "insert New Price : RM ";
			getline(cin, price);
			string update_query = "update stocks set STOCKS_PRICE = '" + price + "'where STOCKS_ID= '" + stocks_id + "'";

			const char* q = update_query.c_str();
			qstate = mysql_query(conn, q);
		}
		else if (chooseUpdate == 5)
		{
			cout << "insert supplier name :";
			getline(cin, supplier);
			string update_query = "update stocks set supplier_name= '" + supplier + "' where STOCKS_ID = '" + stocks_id + "'";

			const char* q = update_query.c_str();
			qstate = mysql_query(conn, q);
		}
		else if (chooseUpdate == 6)
		{
			cout << "\n\nThe change have been saved...\n\n\n";
			string select_query = "select * from stocks where STOCKS_ID = '" + stocks_id + "'";

			const char* q = select_query.c_str();
			qstate = mysql_query(conn, q);

			cout << setw(11) << "STOCKS_ID" << setw(17) << "STOCKS_NAME" << setw(9) << "   " << "STOCKS_CATEGORY" << setw(20) << "    STOCK_QUANTITY" << setw(5) << "    STOCKS_LOCATION" << setw(5) << "    STOCKS_Price" << setw(20) << "supplier_name" << setw(20) << "RegisterarID" << endl;
			//Color(7);
			cout << endl;

			res = mysql_store_result(conn);
			while (row = mysql_fetch_row(res))
			{
				cout << setw(9) << row[0] << setw(18) << row[1] << setw(22) << row[2] << setw(17) << row[3] << setw(20) << row[4] << setw(15) << "RM " << setw(1) << row[5] << setw(18) << row[6] << setw(24) << row[7] << endl << endl;
			}
			cout << "\n\n\n";

			do
			{
				cout << "Do you want update another Stock? (y/n): ";
				cin >> choose;
				if (choose == 'y' || choose == 'Y')
					UpdateStocks();
				else if (choose == 'n' || choose == 'N')
					MenuChoosing();
				cout << "Hello Hallo Bye bye " << endl;
			} while (choose != 'y' && choose != 'Y' && choose != 'n' && choose != 'N');
		}
		else
		{
			cout << "\n";
			cout << "Wrong choice.Please enter again!" << endl;
			cout << "Please Enter your choice : ";
			cin >> choose;
		}
	} while (true);
}


void CheckoutStocks() 
{
	string stocks_id;
	char choose;
	system("cls");
	cout << " ~~~ Checkout Stocks Menu ~~~\n\n";
	cout << "Enter Stocks ID : ";
	cin >> stocks_id;


	string search_query4 = "select STOCKS_ID,STOCKS_NAME,STOCKS_CATEGORY,STOCKS_QUANTITY,STOCKS_LOCATION from stocks where STOCKS_ID = '" + stocks_id + "'";
	const char* fo = search_query4.c_str();
	qstate = mysql_query(conn, fo);

	mysql_free_result(res);
	res = mysql_store_result(conn);
	row = mysql_fetch_row(res);

	string id_cp = row[0], name_cp = row[1], category_cp = row[2], quantity_cp = row[3], location_cp = row[4];

	/*cout << endl;
	string date;
	cin.ignore(100, '\n');
	cout << "Enter Date (eg. 00/00/0000): ";
Enter:
	getline(cin, date);
	if (checkinput(date) > 0)
	{
		cout << "    Error. Please enter again : ";
		goto Enter;
	}
	string indate = "    -";
	string outdate = date;
	//month; "/"; year;   //ada salah

	cout << "Helo4 \n";
	string insert_query3 = "insert into in_out_stocks(STOCKS_ID,STOCKS_NAME,STOCKS_CATEGORY,STOCKS_QUANTITY,STOCKS_LOCATION,STOCKS_INDATE,STOCKS_OUTDATE,MODIFIED_BY) values ('" +id_cp+ "','"+name_cp+"','"+category_cp+"','"+quantity_cp+"', '"+location_cp+"','" + indate + "','" + outdate + "','" + userID + "')";
	const char* qf = insert_query3.c_str();
	qstate = mysql_query(conn, qf);
	*/
	do
	{
		cout << "\t\t\t\t--- List of Searched Stocks ---" << endl << endl;

		string search_query = "select STOCKS_ID,STOCKS_NAME,STOCKS_CATEGORY,STOCKS_QUANTITY,STOCKS_LOCATION,STOCKS_PRICE,Supplier_Name from STOCKS where STOCKS_ID = '" + stocks_id + "' ";
		const char* q = search_query.c_str();
		qstate = mysql_query(conn, q);

		if (!qstate)
		{
			//Color(10);
			cout << setw(11) << "STOCKS_ID" << setw(17) << "STOCKS_NAME" << setw(9) << "   " << "STOCKS_CATEGORY" << setw(20) << "    STOCK_QUANTITY" << setw(5) << "    STOCKS_LOCATION" << setw(5) << "    STOCKS_Price" << setw(20) << "supplier_name" << endl;
			//Color(7);

			res = mysql_store_result(conn);
			while (row = mysql_fetch_row(res))
			{
				cout << setw(9) << row[0] << setw(18) << row[1] << setw(12) << "   " << row[2] << setw(17) << row[3] << setw(19) << row[4] << setw(15) << "RM " << setw(5) << row[5] << setw(9) << " " << row[6] << endl;
			}

		}
		else
			cout << "Query Execution Problem!" << mysql_errno(conn) << endl;

		cout << endl << endl;
	
		char choice;
		int  custom;
		cout << "Do you want to checkout all stocks or checkout custom number of stocks?                             ['x' to exit]  " << endl;
		cout << "Press 1 : for checkout all stocks." << endl;
		cout << "Press 2 : for checkout custom number of stocks." << endl;
		cin >> choice;
		system("cls");

		cout << "\t\t\t\t--- List of Searched Stocks ---" << endl << endl;

		string search_query2 = "select STOCKS_ID,STOCKS_NAME,STOCKS_CATEGORY,STOCKS_QUANTITY,STOCKS_LOCATION,STOCKS_PRICE,Supplier_Name from STOCKS where STOCKS_ID = '" + stocks_id + "' ";

		const char* qi = search_query2.c_str();
		qstate = mysql_query(conn, qi);

		if (!qstate)
		{
			//Color(10);
			cout << setw(11) << "STOCKS_ID" << setw(17) << "STOCKS_NAME" << setw(9) << "   " << "STOCKS_CATEGORY" << setw(20) << "    STOCK_QUANTITY" << setw(5) << "    STOCKS_LOCATION" << setw(5) << "    STOCKS_Price" << setw(20) << "supplier_name" << endl;
			//Color(7);

			res = mysql_store_result(conn);
			while (row = mysql_fetch_row(res))
			{
				cout << setw(9) << row[0] << setw(18) << row[1] << setw(12) << "   " << row[2] << setw(17) << row[3] << setw(19) << row[4] << setw(15) << "RM " << setw(5) << row[5] << setw(9) << " " << row[6] << endl;
			}

		}
		else
			cout << "Query Execution Problem!" << mysql_errno(conn) << endl;

		cout << endl << endl;


		if (choice == '1')
		{
			cout << "are you sure want to checkout this Stocks? (y/n): ";
			cin >> choose;
			if (choose == 'y' || choose == 'Y')
			{
				string delete_query = "delete from stocks where STOCKS_ID = '" + stocks_id + "'";
				const char* q = delete_query.c_str();
				qstate = mysql_query(conn, q);
				if (!qstate)
				{
					cout << " The Stocks has been checkout. Press Enter to Continue...";
					_getch();
					ViewStocks();
					cout << "Press Enter to Continue...";
					_getch();
					system("cls");
					MenuChoosing();
				}
				else
				{
					cout << " Query Execution Problem!" << mysql_errno(conn) << endl;
				}
			}
			else if (choose == 'n' || choose == 'N')
			{
				ViewStocks();
				_getch();
				MenuChoosing();
			}
		}
		if (choice == '2')
		{
			cout << "Please Enter how many stocks quantity that wanted to be checked out : ";
			cin >> custom;
			cout << "Are you sure to checkout " << custom << " stocks?(y/n):" << endl;
			cin >> choose;

			if (choose == 'y' || choose == 'Y')
			{
				
				string search_query2 = "select STOCKS_QUANTITY from stocks where STOCKS_ID = '" + stocks_id + "'";
				const char* fi = search_query2.c_str();
				qstate = mysql_query(conn, fi);

				mysql_free_result(res);
				res = mysql_store_result(conn);
				row = mysql_fetch_row(res);
				custom = atoi(row[0]) - custom;

				stringstream ss;       //line 334-337. to convert string to integer value
				string st_cus;
				ss << custom;          // extact the value custom
				ss >> st_cus;          // st_cus adalah wakil utk custom dlm string

				//update stock quantity
				string update_query = "update stocks set STOCKS_QUANTITY ='" + st_cus + "' where STOCKS_ID ='" + stocks_id + "' ";
				const char* q = update_query.c_str();
				qstate = mysql_query(conn, q);
				cout << "hello3\n";

				if (!qstate)
				{
					cout << endl;
					string date;
					cin.ignore(100, '\n');
					cout << "Enter Date (eg. 00/00/0000): ";
				Enter:
					getline(cin, date);
					if (checkinput(date) > 0)
					{
						cout << "    Error. Please enter again : ";
						goto Enter;
					}
					string indate = "     -";
					string outdate = date;

					cout << "Helo4 \n";
					string insert_query3 = "insert into in_out_stocks(STOCKS_ID,STOCKS_NAME,STOCKS_CATEGORY,STOCKS_QUANTITY,STOCKS_LOCATION,STOCKS_INDATE,STOCKS_OUTDATE,MODIFIED_BY) values ('" + id_cp + "','" + name_cp + "','" + category_cp + "','" + quantity_cp + "', '" + location_cp + "','" + indate + "','" + outdate + "','" + userID + "')";
					const char* qf = insert_query3.c_str();
					qstate = mysql_query(conn, qf);


					cout << " The Stocks has been checkout. Press any key to Continue..." << endl << endl;
					_getch();

					string search_query2 = "select STOCKS_ID,STOCKS_NAME,STOCKS_CATEGORY,STOCKS_QUANTITY,STOCKS_LOCATION,STOCKS_PRICE,Supplier_Name from STOCKS where STOCKS_ID = '" + stocks_id + "' ";

					const char* qi = search_query2.c_str();
					qstate = mysql_query(conn, qi);

					if (!qstate)
					{
						//Color(10);
						cout << setw(11) << "STOCKS_ID" << setw(17) << "STOCKS_NAME" << setw(9) << "   " << "STOCKS_CATEGORY" << setw(20) << "    STOCK_QUANTITY" << setw(5) << "    STOCKS_LOCATION" << setw(5) << "    STOCKS_Price" << setw(20) << "supplier_name" << endl;
						//Color(7);

						res = mysql_store_result(conn);
						while (row = mysql_fetch_row(res))
						{
							cout << setw(9) << row[0] << setw(18) << row[1] << setw(12) << "   " << row[2] << setw(17) << row[3] << setw(19) << row[4] << setw(15) << "RM " << setw(5) << row[5] << setw(9) << " " << row[6] << endl;
						}

					}
					else
						cout << "Query Execution Problem!" << mysql_errno(conn) << endl;

					cout << endl << endl;
					cout << "Press any key to continue..." << endl;
					_getch();
					system("cls");
					MenuChoosing();
				}
				else
				{
					cout << " Query Execution Problem!" << mysql_errno(conn) << endl;
				}

			}
			else if (choose == 'n' || choose == 'N')
			{
				ViewStocks();
				_getch();
				MenuChoosing();
			}
		}
		
		if (choice == 'x' || choice == 'X')
		{
			cout << "hello good\n";
			if (typecp == "a")
			{
				AdminStockMenu();
			}
			if (typecp == "b")
			{
				Staffmenu();
			}
			else
				cout << "nooooooooooooooooooooooooooooooooooooooo\n";
			
		}
		else
		{
			cout << "\n";
			cout << "Wrong choice.Please enter again!" << endl;
			_getch();
			system("cls");
			CheckoutStocks();
		}

	}while (choose != 'y' && choose != 'Y' && choose != 'n' && choose != 'N');
}


void SearchAsker()
{
	char choose;
	do
	{
		cout << "Do you want to search another stocks ? (y/n)" << endl;
		cin >> choose;
		if (choose == 'y' || choose == 'Y')
			SearchStocks();
		else if (choose == 'n' || choose == 'N')
			system("cls");
		MenuChoosing();
		cout << "Hello Hallo Bye bye " << endl;
	} while (choose != 'y' && choose != 'Y' && choose != 'n' && choose != 'N');
}

void SearchStocks()   // function ni gabung dgn function ViewStocks()
{
	system("cls");
	string id, name, price, supplier;
	int choice;
	cin.ignore(1, '\n');

	cout <<"Please Enter what types of searched you want to use : " << endl;
	cout <<"1) Search Stocks by stock ID.\n";
	cout <<"2) Search Stocks by stock name.\n"; 
	cout <<"3) Search Stocks by stock Price.\n"; 
	cout <<"4) Search Stocks by stock supplier.\n";
	cout <<"5) Search Stocks by stock RegisterarID.\n";
	cout <<"6) exit search.\n";
	cout << "Enter your Choice :";
	cin >> choice;
	cout << endl;

	cin.ignore();

	do
	{
		if (choice == 1)  
		{
			cout << "Enter ID : ";
			cin >> id;

			string search_query2 = "select count(*) from stocks where STOCKS_ID = '" + id + "'";  //utk check samada stok wujud ke tak
			const char* fi = search_query2.c_str();
			qstate = mysql_query(conn, fi);

			mysql_free_result(res);
			res = mysql_store_result(conn);
			row = mysql_fetch_row(res);

			if (atoi(row[0]) < 1)
			{
				cout << "the stock you want to search does not exits..." << endl;
				cout << "It might not registered yet or the stocks have been checked out from the warehouse." << endl;
				cout << "For futher information, please contact your manager" << endl << endl;
				cout << "Press any key to continue..." << endl;
				_getch();
				SearchStocks();
			}

			cout << endl;
			cout << "\t\t\t\t--- List of Searched Stocks ---" << endl << endl;

			string search_query = "select STOCKS_ID,STOCKS_NAME,STOCKS_CATEGORY,STOCKS_QUANTITY,STOCKS_LOCATION,STOCKS_PRICE,Supplier_Name,RegisterarID from STOCKS where STOCKS_ID = '" + id + "' ";

			const char* q = search_query.c_str();
			qstate = mysql_query(conn, q);

			if (!qstate)
			{
				cout << setw(11) << "STOCKS_ID" << setw(17) << "STOCKS_NAME" << setw(9) << "   " << "STOCKS_CATEGORY" << setw(20) << "    STOCK_QUANTITY" << setw(5) << "    STOCKS_LOCATION" << setw(5) << "    STOCKS_Price" << setw(20) << "supplier_name" << setw(20) << "RegisterarID" << endl;
				//Color(7);
				cout << endl;

				res = mysql_store_result(conn);
				while (row = mysql_fetch_row(res))
				{
					cout << setw(9) << row[0] << setw(18) << row[1] << setw(22) << row[2] << setw(17) << row[3] << setw(20) << row[4] << setw(15) << "RM " << setw(1) << row[5] << setw(18) << row[6] << setw(24) << row[7] << endl << endl;
				}

			}
			else
				cout << "Query Execution Problem!" << mysql_errno(conn) << endl;

			barchart();  //utk display stock chart
			cout << endl << endl;
			SearchAsker();
		}

		if (choice == 2) 
		{
			cout << "Enter name: ";
			getline(cin, name);
			string search_query2 = "select count(*) from stocks where STOCKS_NAME like '%" + name + "%'";
			const char* fi = search_query2.c_str();
			qstate = mysql_query(conn, fi);

			mysql_free_result(res);
			res = mysql_store_result(conn);
			row = mysql_fetch_row(res);

			if (atoi(row[0]) < 1)
			{
				cout << "the stock you want to search does not exits..." << endl;
				cout << "It might not registered yet or the stocks have been checked out from the warehouse."<<endl;
				cout << "For futher information, please contact your manager" << endl<<endl;
				cout << "Press any key to continue..." << endl; 
				_getch();  
				SearchStocks();        
			}

			cout << endl;
			cout << "\t\t\t\t--- List of Searched Stocks ---" << endl << endl;

			string search_query = "select STOCKS_ID,STOCKS_NAME,STOCKS_CATEGORY,STOCKS_QUANTITY,STOCKS_LOCATION,STOCKS_PRICE,Supplier_Name,RegisterarID from STOCKS where STOCKS_NAME like '%" + name + "%' ";
			const char* q = search_query.c_str();
			qstate = mysql_query(conn, q);

			if (!qstate)
			{
				cout << setw(11) << "STOCKS_ID" << setw(17) << "STOCKS_NAME" << setw(9) << "   " << "STOCKS_CATEGORY" << setw(20) << "    STOCK_QUANTITY" << setw(5) << "    STOCKS_LOCATION" << setw(5) << "    STOCKS_Price" << setw(20) << "supplier_name" << setw(20) << "RegisterarID" << endl;
				//Color(7);
				cout << endl;

				res = mysql_store_result(conn);
				while (row = mysql_fetch_row(res))
				{
					cout << setw(9) << row[0] << setw(18) << row[1] << setw(22) << row[2] << setw(17) << row[3] << setw(20) << row[4] << setw(15) << "RM " << setw(1) << row[5] << setw(18) << row[6] << setw(24) << row[7] << endl << endl;
				}

			}
			else
				cout << "Query Execution Problem!" << mysql_errno(conn) << endl;

			barchart();  //utk display stock chart
			cout << endl << endl;
			SearchAsker();
		}

		if (choice == 3) 
		{
			cout << "Enter Price : RM ";
			cin >> price;

			string search_query2 = "select count(*) from stocks where STOCKS_PRICE like '%" + price + "%'";
			const char* fi = search_query2.c_str();
			qstate = mysql_query(conn, fi);

			mysql_free_result(res);
			res = mysql_store_result(conn);
			row = mysql_fetch_row(res);

			if (atoi(row[0]) < 1)
			{
				cout << "the stock you want to search does not exits..." << endl;
				cout << "It might not registered yet or the stocks have been checked out from the warehouse." << endl;
				cout << "For futher information, please contact your manager" << endl << endl;
				cout << "Press any key to continue..." << endl;
				_getch();
				SearchStocks();
			}

			cout << endl;
			cout << "\t\t\t\t--- List of Searched Stocks ---" << endl << endl;

			string search_query = "select STOCKS_ID,STOCKS_NAME,STOCKS_CATEGORY,STOCKS_QUANTITY,STOCKS_LOCATION,STOCKS_PRICE,Supplier_Name,RegisterarID from STOCKS where STOCKS_PRICE = '" + price + "' ";
			const char* q = search_query.c_str();
			qstate = mysql_query(conn, q);

			if (!qstate)
			{
				cout << setw(11) << "STOCKS_ID" << setw(17) << "STOCKS_NAME" << setw(9) << "   " << "STOCKS_CATEGORY" << setw(20) << "    STOCK_QUANTITY" << setw(5) << "    STOCKS_LOCATION" << setw(5) << "    STOCKS_Price" << setw(20) << "supplier_name" << setw(20) << "RegisterarID" << endl;
				//Color(7);
				cout << endl;

				res = mysql_store_result(conn);
				while (row = mysql_fetch_row(res))
				{
					cout << setw(9) << row[0] << setw(18) << row[1] << setw(22) << row[2] << setw(17) << row[3] << setw(20) << row[4] << setw(15) << "RM " << setw(1) << row[5] << setw(18) << row[6] << setw(24) << row[7] << endl << endl;
				}

			}
			else
				cout << "Query Execution Problem!" << mysql_errno(conn) << endl;

			barchart();  //utk display stock chart
			cout << endl << endl;
			SearchAsker();

		}

		if (choice == 4) 
		{
			cout << "Enter Supplier name : ";
			getline(cin, supplier);

			string search_query2 = "select count(*) from stocks where supplier_name like '%" + supplier + "%'";
			const char* fi = search_query2.c_str();
			qstate = mysql_query(conn, fi);

			mysql_free_result(res);
			res = mysql_store_result(conn);
			row = mysql_fetch_row(res);

			if (atoi(row[0]) < 1)
			{
				cout << "the stock you want to search does not exits..." << endl;
				cout << "It might not registered yet or the stocks have been checked out from the warehouse." << endl;
				cout << "For futher information, please contact your manager" << endl << endl;
				cout << "Press any key to continue..." << endl;
				_getch();
				SearchStocks();
			}

			cout << endl;
			cout << "\t\t\t\t--- List of Searched Stocks ---" << endl << endl;

			string search_query = "select STOCKS_ID,STOCKS_NAME,STOCKS_CATEGORY,STOCKS_QUANTITY,STOCKS_LOCATION,STOCKS_PRICE,Supplier_Name,RegisterarID from STOCKS where Supplier_name like '%" + supplier + "%' ";

			const char* q = search_query.c_str();
			qstate = mysql_query(conn, q);

			if (!qstate)
			{
				cout << setw(11) << "STOCKS_ID" << setw(17) << "STOCKS_NAME" << setw(9) << "   " << "STOCKS_CATEGORY" << setw(20) << "    STOCK_QUANTITY" << setw(5) << "    STOCKS_LOCATION" << setw(5) << "    STOCKS_Price" << setw(20) << "supplier_name" << setw(20) << "RegisterarID" << endl;
				//Color(7);
				cout << endl;

				res = mysql_store_result(conn);
				while (row = mysql_fetch_row(res))
				{
					cout << setw(9) << row[0] << setw(18) << row[1] << setw(22) << row[2] << setw(17) << row[3] << setw(20) << row[4] << setw(15) << "RM " << setw(1) << row[5] << setw(18) << row[6] << setw(24) << row[7] << endl << endl;
				}

			}
			else
				cout << "Query Execution Problem!" << mysql_errno(conn) << endl;

			barchart();  //utk display stock chart
			cout << endl << endl;
			SearchAsker();
		}
		if (choice == 5)
		{
			string registerarID;
			cout << "Enter Registerar ID : ";
			cin >> registerarID;

			string search_query2 = "select count(*) from stocks where RegisterarID = '" + registerarID + "'";
			const char* fi = search_query2.c_str();
			qstate = mysql_query(conn, fi);

			mysql_free_result(res);
			res = mysql_store_result(conn);
			row = mysql_fetch_row(res);

			if (atoi(row[0]) < 1)
			{
				cout << "the stock you want to search does not exits..." << endl;
				cout << "It might not registered yet or the stocks have been checked out from the warehouse." << endl;
				cout << "For futher information, please contact your manager" << endl << endl;
				cout << "Press any key to continue..." << endl;
				_getch();
				SearchStocks();
			}

			cout << endl;
			cout << "\t\t\t\t                 --- List of Searched Stocks ---" << endl << endl;

			string search_query = "select STOCKS_ID,STOCKS_NAME,STOCKS_CATEGORY,STOCKS_QUANTITY,STOCKS_LOCATION,STOCKS_PRICE,Supplier_Name,RegisterarID from STOCKS where RegisterarID ='" + registerarID + "' ";

			const char* q = search_query.c_str();
			qstate = mysql_query(conn, q);

			if (!qstate)
			{
				cout << setw(11) << "STOCKS_ID" << setw(17) << "STOCKS_NAME" << setw(9) << "   " << "STOCKS_CATEGORY" << setw(20) << "    STOCK_QUANTITY" << setw(5) << "    STOCKS_LOCATION" << setw(5) << "    STOCKS_Price" << setw(20) << "supplier_name" << setw(20) << "RegisterarID" << endl;
				//Color(7);
				cout << endl;

				res = mysql_store_result(conn);
				while (row = mysql_fetch_row(res))
				{
					cout << setw(9) << row[0] << setw(18) << row[1] << setw(22) << row[2] << setw(17) << row[3] << setw(20) << row[4] << setw(15) << "RM " << setw(1) << row[5] << setw(18) << row[6] << setw(24) << row[7] << endl << endl;
				}

			}
			else
				cout << "Query Execution Problem!" << mysql_errno(conn) << endl;

			barchart();  //utk display stock chart
			cout << endl << endl;
			SearchAsker();
		}

		if (choice == 6)
		{
			system("cls");
			MenuChoosing();
		}

		else
		{
			cout << "\n";
			cout << "Wrong choice.Please enter again!" << endl;
			cout << "Press any key to continue..." << endl;
			_getch();
			system("cls");
			SearchStocks();
		}

	} while (true);
	
}
	
int logout()
{

	return 0;
}

void MenuChoosing()
{
	if (typecp == "a")
		AdminStockMenu();
	else
		Staffmenu();
}
	
void InOutStocks(string date1,string month1,string year1)  //tak digunakan
{

}