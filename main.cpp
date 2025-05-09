// library management system

#include <iostream>
#include <map>
#include <vector>

using namespace std;

class User
{
  public:
    string name;
    map<string, bool> permissions = {
        {"allowed to add books", true}

    };
};

class Book
{
  public:
    string name;

    //User currently_utilized_by;
    string used_dates[200] = {};
    //map <string, User> utilized_by;

    //User currently_reserved_by;
    string reserved_dates[200] = {};
    //map <string, User> reserved_by;

    int condition;

  public:
    bool is_reserved()
    {
        return true;
    }
};

class Category{
  public:
    string name;
    map<string, Book> books = {};
    vector<string> books_key;

  public:
    Book add_book(string book_name, int condition)
    {
        Book book_to_add;
        book_to_add.name = book_name;
        book_to_add.condition = condition;

        books_key.push_back(book_name);
        books.insert({book_name, book_to_add});
        return book_to_add;
    };

  public:
    void remove_book(string book_name)
    {
        for (int i = 0; i == books_key.size() - 1; ++i)
        {
            if (books_key[i] == book_name)
            {
                books_key.erase(books_key.begin() + i);
            };
        };
        books.erase(book_name);
    };
};

class Library{
  public:
    string name;
    vector<string> category_key;
    map<string, Category> categorys;

  public: Category add_category(string category_name){
        Category category_to_add;
        category_to_add.name = category_name;
        
        category_key.push_back(category_name);
        categorys.insert({category_name, category_to_add});
        return category_to_add;
    }

  public: void remove_category(string category_name){
        //category_key.erase(category_name);
        categorys.erase(category_name);
    }
    
  public: void print_categorys(){
      for (int i = 0;i<=category_key.size();i+=1){
         cout<<"  "<<category_key[i]<<endl;
      }
   }
};

class Corparation{
  public:
    string name;
    vector<string> library_key;
    map<string, Library> librarys = {};

  public: Library add_library(string library_name){
        Library library_to_add;
        library_to_add.name = library_name;

        library_key.push_back(library_name);
        librarys.insert({library_name, library_to_add});
        return library_to_add;
   }
   
  public: void print_librarys(){
     for (int i = 0;i<=library_key.size()-1;i+=1){
        cout<<"  "<<library_key[i]<<endl;
     }
  }
};

class Admin : public User
{
  public:
    string name;
    //permissions["allowed to add books"] = true;
};

class Command{
  public:
    string name;
    string discription;
    bool needs_dir;
    vector<string> args = {};
};

Corparation Company;
bool running = true;
string current_focus[2];

Command create_command(string name, vector<string> args, string discription, bool dir_access){
    Command new_command;
    new_command.name = name;
    new_command.discription = discription;
    new_command.args = args;
    new_command.needs_dir  = dir_access;
    return new_command;
};

vector<Command> add_commands(){
    string discription;
    vector<string> args_vec;
    vector<Command> commands;

    args_vec = {"Name"};
    discription = "Creates a new Library.";
    commands.push_back(create_command("add-library", args_vec, discription, false));

    args_vec = {"Name", "Which Library"};
    discription = "Creates a new Category.";
    commands.push_back(create_command("add-category", args_vec, discription, true));
    
    args_vec = {"Name","Condition","Which Library","Which Category"};
    discription = "Creates a new Book.";
    commands.push_back(create_command("add-book", args_vec, discription, true));
    
    args_vec = {"Which Library"};
    discription = "Sets the default Library to use.";
    commands.push_back(create_command("set-current-library", args_vec, discription, true));
    
    args_vec = {"Which Library", "Which Category"};
    discription = "Sets the default Category to use.";
    commands.push_back(create_command("set-current-category", args_vec, discription, true));
  
    args_vec = {};
    discription = "Displays the default Library/Category to use.";
    commands.push_back(create_command("view-current-focus", args_vec, discription, false));
    
    args_vec = {};
    discription = "Displays all Librarys.";
    commands.push_back(create_command("all-librarys", args_vec, discription, false));
    
    args_vec = {"Which Library"};
    discription = "Displays all categorys.";
    commands.push_back(create_command("all-categorys", args_vec, discription, false));

    args_vec = {};
    discription = "Displays all commands.";
    commands.push_back(create_command("all-commands", args_vec, discription, false));

   args_vec = {};
   discription = "Exits the program.";
   commands.push_back(create_command("kill", args_vec, discription, false));
   
   return commands;
};

void show_current_focus(){
   cout<<"  Library:  "<<current_focus[0];
   cout<<"  Library:  "<<current_focus[0];
};

void show_all_commands(vector<Command> all_commands){
    cout << endl<< "Commands:" << endl;
    for (int i = 0; i <= all_commands.size()-1; i += 1){
        Command command = all_commands[i];
        cout<< "   " <<command.name<<" -> "<<command.discription<<endl;
    }
    cout<<endl;
};

void exacute_commands(vector<Command> all_commands){
   map<string, string> args_input = {};
   vector<string> args;
   string command;
   string input;
   
   cout<<endl<<"Enter Command:   "; cin>>command; 
  
   for (int j = 0;j <= all_commands.size()-1;j += 1){
      if (all_commands[j].name == command){
         args = all_commands[j].args;
         if (!args.empty()){
            cout<<endl;
            for (int i = 0; i <= args.size()-1;i+=1){
               cout<<args[i]+":   ";  
               cin>>input;
               args_input.insert({args[i], input});
   }}}}
   /*for (int i = 0;i<=args.size()-1;i+=1){
       if (args[i].contains("Which")){
         cout<<"djdh";
   }}*/
   if (command == "add-category"){Company.add_library(args_input["Name"]);};
   if (command == "add-library"){Company.add_library(args_input["Name"]);};
   //if (command == "add-book"){Company.}
  if (command == "add-book"){cout<<Company.librarys[args_input["Which Library"]].categorys[args_input["Which Category"]].add_book(args_input["Name"], args_input["Condition"]);};
   if (command == "set-current-library"){current_focus[0] = args_input[0];};   
  // if (command=="set-current-category")
   if (command == "view-current-focus"){show_current_focus();};;
   if (command == "all-librarys"){Company.print_librarys();};
   if (command == "all-categorys"){Company.librarys[args_input["Which Library"]].print_categorys();};
   if (command == "all-books"){Company.librarys[args_input[""]];};
   if (command == "all-commands"){show_all_commands(all_commands);};
   if (command == "kill"){running = false;};
};

int main(int argc, char *argv[]){
    vector<Command> all_commands = add_commands();
    while (running){
        exacute_commands(all_commands);
    };
};
// library management system

#include <iostream>
#include <map>
#include <vector>

using namespace std;

class User
{
  public:
    string name;
    map<string, bool> permissions = {
        {"allowed to add books", true}

    };
};

class Book
{
  public:
    string name;

    //User currently_utilized_by;
    string used_dates[200] = {};
    //map <string, User> utilized_by;

    //User currently_reserved_by;
    string reserved_dates[200] = {};
    //map <string, User> reserved_by;

    int condition;

  public:
    bool is_reserved()
    {
        return true;
    }
};

class Category{
  public:
    string name;
    map<string, Book> books = {};
    vector<string> books_key;

  public:
    Book add_book(string book_name, int condition)
    {
        Book book_to_add;
        book_to_add.name = book_name;
        book_to_add.condition = condition;

        books_key.push_back(book_name);
        books.insert({book_name, book_to_add});
        return book_to_add;
    };

  public:
    void remove_book(string book_name)
    {
        for (int i = 0; i == books_key.size() - 1; ++i)
        {
            if (books_key[i] == book_name)
            {
                books_key.erase(books_key.begin() + i);
            };
        };
        books.erase(book_name);
    };
};

class Library{
  public:
    string name;
    vector<string> category_key;
    map<string, Category> categorys;

  public: Category add_category(string category_name){
        Category category_to_add;
        category_to_add.name = category_name;
        
        category_key.push_back(category_name);
        categorys.insert({category_name, category_to_add});
        return category_to_add;
    }

  public: void remove_category(string category_name){
        //category_key.erase(category_name);
        categorys.erase(category_name);
    }
    
  public: void print_categorys(){
      for (int i = 0;i<=category_key.size();i+=1){
         cout<<"  "<<category_key[i]<<endl;
      }
   }
};

class Corparation{
  public:
    string name;
    vector<string> library_key;
    map<string, Library> librarys = {};

  public: Library add_library(string library_name){
        Library library_to_add;
        library_to_add.name = library_name;

        library_key.push_back(library_name);
        librarys.insert({library_name, library_to_add});
        return library_to_add;
   }
   
  public: void print_librarys(){
     for (int i = 0;i<=library_key.size()-1;i+=1){
        cout<<"  "<<library_key[i]<<endl;
     }
  }
};

class Admin : public User
{
  public:
    string name;
    //permissions["allowed to add books"] = true;
};

class Command{
  public:
    string name;
    string discription;
    bool needs_dir;
    vector<string> args = {};
};

Corparation Company;
bool running = true;
string current_focus[2];

Command create_command(string name, vector<string> args, string discription, bool dir_access){
    Command new_command;
    new_command.name = name;
    new_command.discription = discription;
    new_command.args = args;
    new_command.needs_dir  = dir_access;
    return new_command;
};

vector<Command> add_commands(){
    string discription;
    vector<string> args_vec;
    vector<Command> commands;

    args_vec = {"Name"};
    discription = "Creates a new Library.";
    commands.push_back(create_command("add-library", args_vec, discription, false));

    args_vec = {"Name", "Which Library"};
    discription = "Creates a new Category.";
    commands.push_back(create_command("add-category", args_vec, discription, true));
    
    args_vec = {"Name","Condition","Which Library","Which Category"};
    discription = "Creates a new Book.";
    commands.push_back(create_command("add-book", args_vec, discription, true));
    
    args_vec = {"Which Library"};
    discription = "Sets the default Library to use.";
    commands.push_back(create_command("set-current-library", args_vec, discription, true));
    
    args_vec = {"Which Library", "Which Category"};
    discription = "Sets the default Category to use.";
    commands.push_back(create_command("set-current-category", args_vec, discription, true));
  
    args_vec = {};
    discription = "Displays the default Library/Category to use.";
    commands.push_back(create_command("view-current-focus", args_vec, discription, false));
    
    args_vec = {};
    discription = "Displays all Librarys.";
    commands.push_back(create_command("all-librarys", args_vec, discription, false));
    
    args_vec = {"Which Library"};
    discription = "Displays all categorys.";
    commands.push_back(create_command("all-categorys", args_vec, discription, false));

    args_vec = {};
    discription = "Displays all commands.";
    commands.push_back(create_command("all-commands", args_vec, discription, false));

   args_vec = {};
   discription = "Exits the program.";
   commands.push_back(create_command("kill", args_vec, discription, false));
   
   return commands;
};

void show_current_focus(){
   cout<<"  Library:  "<<current_focus[0];
   cout<<"  Library:  "<<current_focus[0];
};

void show_all_commands(vector<Command> all_commands){
    cout << endl<< "Commands:" << endl;
    for (int i = 0; i <= all_commands.size()-1; i += 1){
        Command command = all_commands[i];
        cout<< "   " <<command.name<<" -> "<<command.discription<<endl;
    }
    cout<<endl;
};

void exacute_commands(vector<Command> all_commands){
   map<string, string> args_input = {};
   vector<string> args;
   string command;
   string input;
   
   cout<<endl<<"Enter Command:   "; cin>>command; 
  
   for (int j = 0;j <= all_commands.size()-1;j += 1){
      if (all_commands[j].name == command){
         args = all_commands[j].args;
         if (!args.empty()){
            cout<<endl;
            for (int i = 0; i <= args.size()-1;i+=1){
               cout<<args[i]+":   ";  
               cin>>input;
               args_input.insert({args[i], input});
   }}}}
   /*for (int i = 0;i<=args.size()-1;i+=1){
       if (args[i].contains("Which")){
         cout<<"djdh";
   }}*/
   if (command == "add-category"){Company.add_library(args_input["Name"]);};
   if (command == "add-library"){Company.add_library(args_input["Name"]);};
   //if (command == "add-book"){Company.}
  if (command == "add-book"){cout<<Company.librarys[args_input["Which Library"]].categorys[args_input["Which Category"]].add_book(args_input["Name"], args_input["Condition"]);};
   if (command == "set-current-library"){current_focus[0] = args_input[0];};   
  // if (command=="set-current-category")
   if (command == "view-current-focus"){show_current_focus();};;
   if (command == "all-librarys"){Company.print_librarys();};
   if (command == "all-categorys"){Company.librarys[args_input["Which Library"]].print_categorys();};
   if (command == "all-books"){Company.librarys[args_input[""]];};
   if (command == "all-commands"){show_all_commands(all_commands);};
   if (command == "kill"){running = false;};
};

int main(int argc, char *argv[]){
    vector<Command> all_commands = add_commands();
    while (running){
// library management system

#include <iostream>
#include <map>
#include <vector>

using namespace std;

class User
{
  public:
    string name;
    map<string, bool> permissions = {
        {"allowed to add books", true}

    };
};

class Book
{
  public:
    string name;

    //User currently_utilized_by;
    string used_dates[200] = {};
    //map <string, User> utilized_by;

    //User currently_reserved_by;
    string reserved_dates[200] = {};
    //map <string, User> reserved_by;

    int condition;

  public:
    bool is_reserved()
    {
        return true;
    }
};

class Category{
  public:
    string name;
    map<string, Book> books = {};
    vector<string> books_key;

  public:
    Book add_book(string book_name, int condition)
    {
        Book book_to_add;
        book_to_add.name = book_name;
        book_to_add.condition = condition;

        books_key.push_back(book_name);
        books.insert({book_name, book_to_add});
        return book_to_add;
    };

  public:
    void remove_book(string book_name)
    {
        for (int i = 0; i == books_key.size() - 1; ++i)
        {
            if (books_key[i] == book_name)
            {
                books_key.erase(books_key.begin() + i);
            };
        };
        books.erase(book_name);
    };
};

class Library{
  public:
    string name;
    vector<string> category_key;
    map<string, Category> categorys;

  public: Category add_category(string category_name){
        Category category_to_add;
        category_to_add.name = category_name;
        
        category_key.push_back(category_name);
        categorys.insert({category_name, category_to_add});
        return category_to_add;
    }

  public: void remove_category(string category_name){
        //category_key.erase(category_name);
        categorys.erase(category_name);
    }
    
  public: void print_categorys(){
      for (int i = 0;i<=category_key.size();i+=1){
         cout<<"  "<<category_key[i]<<endl;
      }
   }
};

class Corparation{
  public:
    string name;
    vector<string> library_key;
    map<string, Library> librarys = {};

  public: Library add_library(string library_name){
        Library library_to_add;
        library_to_add.name = library_name;

        library_key.push_back(library_name);
        librarys.insert({library_name, library_to_add});
        return library_to_add;
   }
   
  public: void print_librarys(){
     for (int i = 0;i<=library_key.size()-1;i+=1){
        cout<<"  "<<library_key[i]<<endl;
     }
  }
};

class Admin : public User
{
  public:
    string name;
    //permissions["allowed to add books"] = true;
};

class Command{
  public:
    string name;
    string discription;
    bool needs_dir;
    vector<string> args = {};
};

Corparation Company;
bool running = true;
string current_focus[2];

Command create_command(string name, vector<string> args, string discription, bool dir_access){
    Command new_command;
    new_command.name = name;
    new_command.discription = discription;
    new_command.args = args;
    new_command.needs_dir  = dir_access;
    return new_command;
};

vector<Command> add_commands(){
    string discription;
    vector<string> args_vec;
    vector<Command> commands;

    args_vec = {"Name"};
    discription = "Creates a new Library.";
    commands.push_back(create_command("add-library", args_vec, discription, false));

    args_vec = {"Name", "Which Library"};
    discription = "Creates a new Category.";
    commands.push_back(create_command("add-category", args_vec, discription, true));
    
    args_vec = {"Name","Condition","Which Library","Which Category"};
    discription = "Creates a new Book.";
    commands.push_back(create_command("add-book", args_vec, discription, true));
    
    args_vec = {"Which Library"};
    discription = "Sets the default Library to use.";
    commands.push_back(create_command("set-current-library", args_vec, discription, true));
    
    args_vec = {"Which Library", "Which Category"};
    discription = "Sets the default Category to use.";
    commands.push_back(create_command("set-current-category", args_vec, discription, true));
  
    args_vec = {};
    discription = "Displays the default Library/Category to use.";
    commands.push_back(create_command("view-current-focus", args_vec, discription, false));
    
    args_vec = {};
    discription = "Displays all Librarys.";
    commands.push_back(create_command("all-librarys", args_vec, discription, false));
    
    args_vec = {"Which Library"};
    discription = "Displays all categorys.";
    commands.push_back(create_command("all-categorys", args_vec, discription, false));

    args_vec = {};
    discription = "Displays all commands.";
    commands.push_back(create_command("all-commands", args_vec, discription, false));

   args_vec = {};
   discription = "Exits the program.";
   commands.push_back(create_command("kill", args_vec, discription, false));
   
   return commands;
};

void show_current_focus(){
   cout<<"  Library:  "<<current_focus[0];
   cout<<"  Library:  "<<current_focus[0];
};

void show_all_commands(vector<Command> all_commands){
    cout << endl<< "Commands:" << endl;
    for (int i = 0; i <= all_commands.size()-1; i += 1){
        Command command = all_commands[i];
        cout<< "   " <<command.name<<" -> "<<command.discription<<endl;
    }
    cout<<endl;
};

void exacute_commands(vector<Command> all_commands){
   map<string, string> args_input = {};
   vector<string> args;
   string command;
   string input;
   
   cout<<endl<<"Enter Command:   "; cin>>command; 
  
   for (int j = 0;j <= all_commands.size()-1;j += 1){
      if (all_commands[j].name == command){
         args = all_commands[j].args;
         if (!args.empty()){
            cout<<endl;
            for (int i = 0; i <= args.size()-1;i+=1){
               cout<<args[i]+":   ";  
               cin>>input;
               args_input.insert({args[i], input});
   }}}}
   /*for (int i = 0;i<=args.size()-1;i+=1){
       if (args[i].contains("Which")){
         cout<<"djdh";
   }}*/
   if (command == "add-category"){Company.add_library(args_input["Name"]);};
   if (command == "add-library"){Company.add_library(args_input["Name"]);};
   //if (command == "add-book"){Company.}
  if (command == "add-book"){cout<<Company.librarys[args_input["Which Library"]].categorys[args_input["Which Category"]].add_book(args_input["Name"], args_input["Condition"]);};
   if (command == "set-current-library"){current_focus[0] = args_input[0];};   
  // if (command=="set-current-category")
   if (command == "view-current-focus"){show_current_focus();};;
   if (command == "all-librarys"){Company.print_librarys();};
   if (command == "all-categorys"){Company.librarys[args_input["Which Library"]].print_categorys();};
   if (command == "all-books"){Company.librarys[args_input[""]];};
   if (command == "all-commands"){show_all_commands(all_commands);};
   if (command == "kill"){running = false;};
};

int main(int argc, char *argv[]){
    vector<Command> all_commands = add_commands();
    while (running){
        exacute_commands(all_commands);
    };
};
        exacute_commands(all_commands);
    };
};
