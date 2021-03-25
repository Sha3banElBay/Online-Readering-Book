#include <bits/stdc++.h>
using namespace std;

class View
{
public:
	static int ShowMenu(const vector<string>& menu)
	{
		cout << "Menu :\n";
		for(int i=0 ; i<menu.size() ; i++)
		{
			cout << "\t" << i+1 << " " << menu[i] << '\n';
		}
		return ReadInt(1 , menu.size());
	}

	static int ReadInt(int start , int end)
	{
		cout << "\nEnter Number From  " << start << "  to  " << end << " : ";
		int NewChoice;
		cin >> NewChoice;
		if(NewChoice>=start && NewChoice<=end)
			return NewChoice;

		cout << "ERROR : FUCK U , Try Again\n";
		return ReadInt(start , end);
	}

};


class Book
{
	int isbn;
	string title;
	string author;
	vector<string> pages;

public:
	void Reader(int isbn)
	{
		string str;
		SetIsbn(isbn);

		cout << "Enter Title: ";
		cin >> str;
		SetTitle(str);

		cout << "Enter Author Name: ";
		cin >> str;
		SetAuthor(str);

		cout << "Enter How many pages: ";
		int pages_count;
		cin >> pages_count;


		for (int page = 0; page < pages_count; ++page)
		{
			cout << "Enter page # " << page + 1 << ": ";
			cin >> str;
			pages.push_back(str); // why not set?
		}

	}

	void PrintBook() const
	{
		cout << "\n Book ISBN : " << GetIsbn();
		cout << "\n Book Name : " << GetTitle();
		cout << "\n Book Autohr : " << GetAuthor();
		cout << "\n Book Size : " << GetBookSize();
		for (int i = 0; i < GetBookSize(); i++)
		{
			cout << "\nPage notes : " << this->pages[i] << "\n";
		}
	}

	string GetPage(int n) const
	{
		if (n > GetBookSize() - 1)
			return "\nInvalid Number *_*\n";
		return pages[n - 1];
	}


	const string& GetAuthor() const
	{
		return author;
	}

	void SetAuthor(const string& author)
	{
		this->author = author;
	}


	const int& GetIsbn()const
	{
		return isbn;
	}
	void SetIsbn(const int& isbn)
	{
		this->isbn = isbn;
	}


	const vector<string>& GetPages() const
	{
		return pages;
	}
	void SetPages(const vector<string>& pages)
	{
		this->pages = pages;
	}


	const string& GetTitle()const
	{
		return title;
	}
	void SetTitle(const string& title)
	{
		this->title = title;
	}


	const int GetBookSize() const
	{
		return pages.size();
	}

	string ToString()
	{
		return title;
	}

};




class ReadingSession
{


	static int TotalSessions;
private:
	const Book* book; // Why?
	int CurrentPage;

public:
	ReadingSession() : ReadingSession(nullptr)
	{

	}
	// why const ?
	ReadingSession(const Book* book) : book(book), CurrentPage(0)
	{

	}


	void PrintSession() const
	{
		cout << "\nCurrent Page : " << GetCurrentPageNumber();
		cout << "\nBook Info: ";
		book->PrintBook();
	}

	int GetCurrentPageNumber() const
	{
		return CurrentPage;
	}
	void BackOnePage()
	{
		CurrentPage = max(0 , CurrentPage-1);
	}

	void GoNextPage()
	{
		CurrentPage = min(CurrentPage+1 , book->GetBookSize()-1);
	}

};

int ReadingSession::TotalSessions = 0;



class User
{
private:
	bool IsAdmin;
	string name;
	string username;
	string password;
	vector<ReadingSession*>Session; // Why destructor such as book* in Reading Session Class??

public:
	User() : IsAdmin (false)
	{

	}

	~User()
	{
		for(int i=0 ; i<Session.size() ; i++)
		{
			delete Session[i];
			Session[i] = nullptr;
		}
	}


	void ReadUser(const string& user_name)
	{
		SetUserName(user_name);

		string str;

		cout << "\nEnter User Name : ";
		cin >> str;

		cout << "\nEnter name: ";
		cin >> str;
		SetName(str);

		cout << "\nEnter Password : ";
		cin >> str;
		SetPassword(str);


		cout << "\nFor Admin press 1 | User Press 0 : ";
		bool Admin;
		cin >> Admin;
		SetIsAdmin(Admin);

	}


	void PrintAllSessions() const
	{
		cout << "\n";
		if(Session.size()==0)
			cout << "\n No available Sessions :(";

		else
			for(int i=0 ; i<Session.size() ; i++)
			{
				cout << "\nSession " << i+1;
				Session[i]->PrintSession();
				cout << '\n';
			}
		cout << '\n';
	}

	void AddSession(const Book* book)
	{
		// don't Understand pointers here ! & why not const is error ?
		ReadingSession* NewSession = new ReadingSession(book);
		Session.push_back(NewSession);
		cout << "\nSession added successfully";
	}

	const vector<ReadingSession*>& GetSessions() const
	{
		// Note: Although the return is const vector, but the pointer is not const, so someone can cause problems using setters on pointer
		return Session;	// No set
	}

	const string& GetName() const
	{
		return name;
	}

	const string& GetPassword() const
	{
		return password;
	}

	const bool& isAdmin() const
	{
		return IsAdmin;
	}

	void SetUserName(const string& username)
	{
		this->username = username;
	}

	void SetPassword(const string& password)
	{
		this->password = password;
	}

	void SetName(const string& name)
	{
		this->name = name;
	}

	void SetIsAdmin(const bool& admin)
	{
		this->IsAdmin = admin;
	}

};


class UserManager
{

private:
	map<string, User*> mapUserNameToUser;
	User* currentUser;

public:
	UserManager() : currentUser(nullptr)
	{

	}

	~UserManager()
	{
		for (auto it = mapUserNameToUser.begin(); it != mapUserNameToUser.end(); it++)
		{
			delete it->second;
			it->second = nullptr;
		}

		delete currentUser ;
		currentUser = nullptr;
	}

	void AcsessSystem()
	{
		int choice = View::ShowMenu({"Login" , "SignUp"});
		if(choice==1) Login();
		else SignUp();
	}

	void Login()
	{
		while(true)
		{
			cout << "\nEnter User name : ";
			string username;
			cin >> username;

			cout << "\nEnter Password : ";
			string password;
			cin >> password;


			if(mapUserNameToUser.count(username) && mapUserNameToUser[username]->GetPassword() == password)
			{
				currentUser = mapUserNameToUser[username];
				cout << "\nLogin Done Successfully ";
				break;
			}
			else
				cout << "\nFuck U , userName or password is wrong , try Again";

		}
	}

	void SignUp()
	{
		while (true)
		{
			cout << "\nEnter User Name : ";
			string userName;
			cin >> userName;

			if (mapUserNameToUser.count(userName))
			{
				cout << "\nFuck U , UserName Already Exist , Try Again";
				continue;
			}
			User* Newuser = new User;
			Newuser->ReadUser(userName);

			mapUserNameToUser[userName] = Newuser;
			cout << "\nSignup Done Successfully " << endl;

			break;
		}

	}

	void LogoutCurrentUser()
	{
		//delete currentUser; why not ?
		currentUser = nullptr;
	}

	const User* GetCurrentUser() const
	{
		return currentUser;
	}

	void AddSessionToCurrentUser(const Book* book)
	{
		currentUser->AddSession(book);
	}

};


class BookManager
{
private:
	map<int,Book*>mapISBNtoBook;

public:
	int ReadNewISBN()
	{
		int isbn;
		cout << "\nEnter book ISBN : ";
		cin >> isbn;

		if(mapISBNtoBook.count(isbn))
		{
			cout << "FUCK U Book Is Already Exist , Try Again";
			return ReadNewISBN();
		}
		else
		{
		////////////	mapISBNtoBook[isbn];
			return isbn;
		}
	}

	BookManager()
	{

	}
	~BookManager()
	{
		for (auto it= mapISBNtoBook.begin(); it != mapISBNtoBook.end(); it++)
			{
				delete it->second;
				it->second = nullptr;
			}
	}

	void AddBook()
	{
		int isbn = ReadNewISBN();
		Book* newBook = new Book();
		newBook->Reader(isbn);
		mapISBNtoBook[newBook->GetIsbn()] = newBook;
	}

	void PrintAllBooks() const
	{
		cout << '\n';
		if (mapISBNtoBook.size() == 0)
		{
			cout << "\nNo available books yet";
		}
		else
		{
			int counter = 1;
			for (auto it = mapISBNtoBook.begin(); it != mapISBNtoBook.end(); it++)
			{
				cout << "\nBook " << counter;
				it->second->PrintBook();
				counter++;

			}
		}
		cout << '\n';
	}

	bool CheckBook(int isbn) const
	{
		return mapISBNtoBook.count(isbn);
	}

	const Book* GetBook(int isbn)
	{
		if(mapISBNtoBook.count(isbn))
			return mapISBNtoBook[isbn];

		return nullptr;
	}


};

class BookReadingSystem
{
	UserManager* usersManager;
	BookManager* booksManager;
public:
	BookReadingSystem() : usersManager( new UserManager()) , booksManager(new BookManager())
	{

	}
	~BookReadingSystem()
	{
		delete usersManager;
		usersManager = nullptr;

		delete booksManager;
		booksManager = nullptr;
	}

	void RunSystem()
	{
		usersManager->AcsessSystem();
		if(usersManager->GetCurrentUser() == nullptr)
		{
			RunSystem();
		}
		else if(usersManager->GetCurrentUser()->isAdmin())
			ShowAdminMenu();
		else if(!usersManager->GetCurrentUser()->isAdmin())
			ShowUserMenu();

	}


	void ShowAdminMenu()
	{
		int choice = View::ShowMenu({ "Add Book" , "Show All Books"  , "Logout" });

		if (choice == 1)
		{
			booksManager->AddBook();
			ShowAdminMenu();
		}
		else if(choice == 2)
		{
			booksManager->PrintAllBooks();
			ShowAdminMenu();

		}
		else
		{
			usersManager->LogoutCurrentUser();
			RunSystem();
		}
	}

	void ShowUserMenu()
	{
		int choice = View::ShowMenu({ "Create Session" , "Show All Books" , "Show My Sessions" , "Logout" });

		if (choice == 1)
		{
			while (true)
			{

				cout << "\nEnter book isbn : ";
				int isbn;
				cin >> isbn;
				if (!booksManager->CheckBook(isbn))
				{
					cout << "\nBook not exist , try again";
					continue;
				}

				usersManager->AddSessionToCurrentUser(booksManager->GetBook(isbn));

				break;
			}
		}


		else if (choice == 2)
		{
			booksManager->PrintAllBooks();
		}
		else if (choice == 3)
		{
			usersManager->GetCurrentUser()->PrintAllSessions();
		}
		else
		{
			usersManager->LogoutCurrentUser();
			RunSystem();
			return;
		}
		ShowUserMenu();


	}




};

int main()
{

	BookReadingSystem sys;
	sys.RunSystem();
	return 0;
}





