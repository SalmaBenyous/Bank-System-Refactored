

#include <iostream>
#include <string>
#include <vector>
#include<fstream>
#include <iomanip>
#include <cstdlib> // Required header for exit()

using namespace std;

//string ClientList = "ClientsList.txt";

enum enOperations{ShowClients =1,AddClient=2,DeleteClient=3,UpdateCleint=4,FindClient=5,ExitProgramm=6};

struct sClients
{
	string AccountNumber;
	string PinCode;
	string FullName;
	string PhoneNumber;
	double AccountBalance=0;
};
//definition 
bool isAccountExist(string AccountNumber, vector <sClients> &Clients,sClients &Client);
void StartProgramm(vector <sClients>& Clients);
void ClientCard(sClients& Client);
void HeaderOfOperation(string Message);

void ShowMenuScreen()
{
	cout << "=========================================\n";
	cout << "\t\tMain Menu Screen\n";
	cout << "=========================================\n";
	cout << "\t[1] Show Clients List.\n";
	cout << "\t[2] Add New Client.\n";
	cout << "\t[3] Delete Client.\n";
	cout << "\t[4] Update Client Info.\n";
	cout << "\t[5] Find Client.\n";
	cout << "\t[6] Exit.\n";
	cout << "=========================================\n";

}
enOperations ReadOperation()
{
	short Choose = 0;
	cout << "Choose what do you want to do? [1 to 6]? ";
	cin >> Choose;
	return (enOperations)Choose;

}
vector <string> SplitFunction(string S1,string Seperator=" ## ")
{
	string Word;
	vector <string> Words;
	short Pos = 0;
	while ((Pos=S1.find(Seperator))!=string::npos)
	{
		Word = S1.substr(0, Pos);
		if (Word != "")
		{
			Words.push_back(Word);
		}
		S1=S1.erase(0, Pos + Seperator.length());
	}
	if (S1 != "")
	{
		Words.push_back(S1);
	}
	return Words;
}
sClients  ConvertLineToRecord(string Line)
{
	vector <string> Words = SplitFunction(Line);
	sClients Client;
	Client.AccountNumber = Words[0];//Account Number
	Client.PinCode = Words[1];//Pin Code
	Client.FullName = Words[2];// Full Name
	Client.PhoneNumber = Words[3];// Phone Number
	Client.AccountBalance = stod(Words[4]);// Balance Account
	return Client;
}
string ConvertRecordToLine(sClients Client ,string Seperator=" ## ")
{
	string S1 = "";
	S1 += Client.AccountNumber + Seperator;
	S1 += Client.PinCode + Seperator;
	S1 += Client.FullName + Seperator;
	S1 += Client.PhoneNumber + Seperator;
	S1 += to_string(Client.AccountBalance) + Seperator;
	S1 += "\n";
	return S1;
}
vector <sClients> LoadDataFromFile()
{
	fstream MyFile;
	sClients Client;
	vector <sClients> Clients;
	MyFile.open("ClientsList.txt", ios::in); //Read Mode
	if (MyFile.is_open())
	{
		string Line;
		while (getline(MyFile, Line))
		{
			if (Line.empty())
			{
				continue;
			}
			Client = ConvertLineToRecord(Line);
			Clients.push_back(Client);
		}
		MyFile.close();
		return Clients;

	}
	return Clients;
	
}
void HeaderTable(short size)
{
	cout << "\t\t\tClient List " << size << " Client(s)\n";
	cout << "---------------------------------------------------------------------------------------------\n";
	cout << left << setw(20) << "| Account Number";
	cout << left << setw(15) << "| Pin Code";
	cout << left << setw(25) << "| Client Name";
	cout << left << setw(15) << "| Phone";
	cout << left << setw(15) << "| Balance";
	cout << "|";
	cout << "\n---------------------------------------------------------------------------------------------\n";

}
void ShowCllient(sClients Client)
{
	cout << left << setw(20) << "| " + Client.AccountNumber; // Account Number
	cout << left << setw(15) << "| " + Client.PinCode; // Pin
	cout << left << setw(25) << "| " + Client.FullName; // Name
	cout << left << setw(15) << "| " + Client.PhoneNumber; // Phone
	cout << left << setw(15) << "| " + to_string(Client.AccountBalance); // Balance
	cout << "|";
	cout << "\n---------------------------------------------------------------------------------------------\n";
}
void ShowClientsList(vector <sClients> &Clients)
{
	system("cls");
	if (Clients.size() > 0)
	{
		HeaderTable(Clients.size());

		for (sClients& C : Clients)
		{
			ShowCllient(C);
		}
	}
	else
	{
		cout << "\t\t There are not Data Found!\n";
	}
	

}
void SavaDataToFile(vector <sClients> &Clients)
{
	fstream MyFile;
	MyFile.open("ClientsList.txt", ios::out);
	if (MyFile.is_open())
	{
		for (sClients& C : Clients) {
			MyFile << ConvertRecordToLine(C);
		}
	}
	MyFile.close();
}
sClients ReadClient(vector <sClients>& Clients)
{
	sClients Client;
	cout << "Enter the Account Number:";
	getline(cin >> ws , Client.AccountNumber);
	while (isAccountExist(Client.AccountNumber,Clients,Client))
	{
		system("cls");
		HeaderOfOperation("Adding New Client...");
		cout << "This Account is alread exists , Enter Account Number:";
		getline(cin >> ws, Client.AccountNumber);
	} 
	cout << "Enter the Pin Code:";
	getline(cin, Client.PinCode);
	cout << "Enter the Full Name:";
	getline(cin, Client.FullName);
	cout << "Enter the Phone Number:";
	getline(cin, Client.PhoneNumber);
	cout << "Enter the Balance Account:";
	cin >> Client.AccountBalance;
	return Client;
}
bool isAccountExist(string AccountNumber, vector <sClients>& Clients,sClients &Client)
{
	
	for (sClients& C : Clients)
	{
		if (C.AccountNumber == AccountNumber)
		{
			Client = C;
			return true;
		}
	}
	return false;
}
sClients AddNewClient(vector <sClients>& Clients)
{
	system("cls");
	HeaderOfOperation("Adding New CLient..");
	sClients C;
	C= ReadClient(Clients);
	return C;

}
void HeaderOfOperation(string Message)
{
	system("cls");
	cout << "\n##################################################\n";
	cout << "\t\t" << Message << endl;
	cout << "##################################################\n\n";
}
void AddClientsToFile(vector <sClients> &Clients)
{
	char AddAgain = 'Y';
	HeaderOfOperation("Adding New CLient..");
	while (toupper(AddAgain) == 'Y')
	{
		sClients Client= AddNewClient(Clients);
		//add the new client to vector
		Clients.push_back(Client);
		cout << "Do you want to add more Client? Y/N";
		cin >> AddAgain;
	}
	//refresh data 
	SavaDataToFile(Clients);
}
bool FindClientByAccountNumber(string AccountNumber,vector <sClients> &Clients,sClients &Client)
{
	if (isAccountExist(AccountNumber, Clients, Client))
	{
		ClientCard(Client);
		return true;
	}
	return false;
}

void ClientCard(sClients &Client)
{
	HeaderOfOperation("Details of Client");
	cout << "Account Number: " << Client.AccountNumber << endl;
	cout << "Pin Code: " << Client.PinCode << endl;
	cout << "Full NAame: " << Client.FullName << endl;
	cout << "Phone Number: " << Client.PhoneNumber << endl;
	cout << "Account Balance: " << Client.AccountBalance << endl;
	cout << "---------------------------------------------------\n";
}
void GoBackToProgramm(vector <sClients>& Clients)
{
	system("pause");
	StartProgramm(Clients);
}
string ReadAccountNumber()
{
    string AccountNumber;
	cout << "Please Enter an Account Number:";
	cin >> AccountNumber;
	return AccountNumber;

}
void DeleteClientByAccountNumber(string AccountNumber, vector <sClients> &Clients)
{
	
	for (auto it=Clients.begin();it!=Clients.end();it++)
	{
		
		if (it->AccountNumber == AccountNumber)
		{
			Clients.erase(it);
			cout << "\nClient deleted Succssesfully!\n";
			SavaDataToFile(Clients);
			return;
		}
	}
}

bool DeleteClients(vector <sClients> &Clients)
{
	sClients Client;
	HeaderOfOperation("Deleting Client...");
	string AccountNumber = ReadAccountNumber();
	char AnswerForDelete='N';
	if(FindClientByAccountNumber(AccountNumber,Clients,Client))
	{
		cout << "Are you sure you want to delete this Client? Y/N";
		cin >> AnswerForDelete;
		if (toupper(AnswerForDelete) == 'Y')
		{
			DeleteClientByAccountNumber(AccountNumber, Clients);
			return true;
		}
	}
	else
	{
		cout << "This Account Number [" << AccountNumber << "] is not exist :-)\n";
		return false;
	}
	
}

void UpdateClientByAccountNumber(string AccountNumber,vector <sClients> &Clients)
{
	for (auto it = Clients.begin(); it != Clients.end(); it++)
	{
		if (it->AccountNumber == AccountNumber)
		{
			cout << "Enter the new Full Name:";
			getline(cin >> ws, it->FullName);
			cout << "Enter the new Phone Number:";
			getline(cin, it->PhoneNumber);
			cout << "Enter the new Balance Accoount:";
			cin >> it->AccountBalance;
			return;
		}
	}
}
bool UpdateClients(vector <sClients>& Clients)
{
	HeaderOfOperation("Updating Client...");
	sClients Client;
	string AccountNumber = ReadAccountNumber();
	char AnswerForUpdate = 'N';
	if (FindClientByAccountNumber(AccountNumber, Clients, Client))
	{
		cout << "Are you sure you want to update this Client? Y/N";
		cin >> AnswerForUpdate;
		if (toupper(AnswerForUpdate) == 'Y')
		{
			//ClientCard(Client);
			UpdateClientByAccountNumber(AccountNumber, Clients);
			cout << "Updated Client Succssesfully!";
			//refresh data
			SavaDataToFile(Clients);
			return true;
		}
		
	}
	else
	{
		cout << "This Account Number [" << AccountNumber << "] is not exist :-)\n";
		return false;
	}
}
void FindClients(vector <sClients> &Clients)
{
	HeaderOfOperation("Finding  a Client...");
	sClients Client;
	FindClientByAccountNumber(ReadAccountNumber(), Clients,Client);
	return;
}
void Exit()
{
	HeaderOfOperation("Ending Programm...");
	cout << "Programm end :)\n\n";
	exit(0);
}
void HandleMenuChoice(enOperations Choose, vector <sClients> &Clients)
{
	switch (Choose)
	{
	case AddClient:
		//system("cls");
		AddClientsToFile(Clients);
		GoBackToProgramm(Clients);
		break;
	case ShowClients:
		//system("cls");
		ShowClientsList(Clients);
		GoBackToProgramm(Clients);
		break;
	case DeleteClient:
		//system("cls");
		DeleteClients(Clients);
		GoBackToProgramm(Clients);
		break;
	case UpdateCleint:
		//system("cls");
		UpdateClients(Clients);
		GoBackToProgramm(Clients);
		break;
	case FindClient:
		//system("cls");
		FindClients(Clients);
		GoBackToProgramm(Clients);
		break;
	case ExitProgramm:
		//system("cls");
		Exit();
		break;
	default:
		break;
	}
}



void StartProgramm(vector <sClients>& Clients)
{
	system("cls");
	ShowMenuScreen();
	//ReadOperation();
	HandleMenuChoice(ReadOperation(), Clients);
}


int main()
{
	vector <sClients> Clients = LoadDataFromFile();
	StartProgramm(Clients);
}

