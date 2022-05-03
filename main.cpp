#include <iostream>
#include <conio.h>
#include "FileFolder.hpp"

using namespace std;

vector<Folder> root_folders= vector<Folder>();
Folder* current_folder;

void createRootFolder()
{
    cout << "Please input the name of the root folder: ";
    string root_name;
    cin >> root_name;
    root_folders.push_back(Folder(root_name,root_name,true));
    cout<< "Root folder \'"+root_name+"\' successfully created." <<endl;
    cout<<endl;
}

vector<string> split(string s, string del)
{
    vector<string> words=vector<string>();
    int start = 0;
    int end = s.find(del);
    while (end != -1) {
        words.push_back(s.substr(start, end - start));
        start = end + del.size();
        end = s.find(del, start);
    }
    words.push_back(s.substr(start, end - start));
    return words;
}

bool changeLocation()
{
    string target_location;
    cout << "Please input the target location: ";
    cin >> target_location;
    vector<string> folders=split(target_location,"/");
    if (folders.size()==0) folders.push_back("");
    Folder* curr_folder=nullptr;
    int i=0;
    for (;i<root_folders.size();i++)
    {
        if (folders[0]==root_folders[i].getName()) {curr_folder=&root_folders[i];}
    }
    if (curr_folder==nullptr)
    {
        cout <<"Root folder named: \'"+folders[0]+ "\' not found!" << endl;
        return false;
    }
    for (int i=1;i<folders.size();i++)
    {
        bool curr_folder_found=false;
        int j=0;
        for (;j<curr_folder->getContent().size() && !curr_folder_found;j++)
        {
            if (curr_folder->getContent().at(j)->isFolder() && curr_folder->getContent().at(j)->getName()==folders[i])
            {
                curr_folder=dynamic_cast<Folder*>(curr_folder->getContent()[j]);
                curr_folder_found=true;
            }
        }
        if (j==curr_folder->getContent().size()) 
        {
            cout <<"Folder named: \'"+folders[i]+"\' at \'"+ curr_folder->getLocation()+"\' not found!" << endl;
            return false;
        }
    }
    current_folder= curr_folder;
    cout << "Location successfully changed to \'"+target_location+"\'" <<endl;
    return true;
}

void addFile()
{
    string filename;
    string extension;
    double size;
    cout << "Please input the following parameters:"<<endl;
    cout << "File name: ";
    cin >>filename;
    cout << "File extension: ";
    cin >>extension;
    cout << "File size (KB): ";
    cin>> size;
    if (current_folder!=nullptr)
    {
        bool already_exists=false;
        int i=0;
        for (;i<current_folder->getContent().size() && !already_exists;i++)
        {
            if (current_folder->getContent().at(i)->isFile())
            {
                File* curr_file=static_cast<File*>(current_folder->getContent().at(i));
                if (curr_file->getName()==filename && curr_file->getExtension()==extension)
                {
                    already_exists=true;
                }
            }
        }
        if (!already_exists)
        {
            current_folder->addFile(filename,extension,size);
            cout << "File named \'"+filename+"."+extension+"\', size: "+to_string(size)+"KB  successfully created at \'"+current_folder->getLocation() +"\'!"<<endl;
        }
        else
        {
            cout <<"File named \'"+filename+"."+extension+"\' already exists at \'"+current_folder->getLocation()+"\'!"<<endl;
        }
    }
    else
    {
        cout << "Current folder is not defined!" <<endl;
    }
}

void addFolder()
{
    string foldername;
    cout << "Please input the name of the folder: ";
    cin >> foldername;
    if (current_folder!=nullptr)
    {
        bool already_exists=false;
        int i=0;
        for (;i<current_folder->getContent().size() && !already_exists;i++)
        {
            if (current_folder->getContent().at(i)->isFolder())
            {
                Folder* curr_folder=static_cast<Folder*>(current_folder->getContent().at(i));
                if (curr_folder->getName()==foldername)
                {
                    already_exists=true;
                }
            }
        }
        if (!already_exists)
        {
            current_folder->addFolder(foldername);
            cout << "Folder named \'"+foldername+"\' successfully created at \'"+current_folder->getLocation() +"\'!"<<endl;
        }
        else
        {
            cout <<"Folder named \'"+foldername+"\' already exists at "+current_folder->getLocation()+"!"<<endl;
        }
    }
    else
    {
        cout << "Current folder is not defined!" <<endl;
    }
}

void size()
{
    if (current_folder!=nullptr)
    {
        cout<<"Size of the current folder: "+to_string(current_folder->getSize())+" KB"<<endl;
    }
    else
    {
        cout << "Current folder is not defined!" <<endl;
    }
}
void printLocation()
{
    if (current_folder!=nullptr)
    {
        cout<< "The current locations is: "+current_folder->getLocation() <<endl;
    }
    else
    {
        cout << "Current folder is not defined!" <<endl;
    }
}

void printContent()
{
    if (current_folder!=nullptr)
    {
        if (current_folder->getContent().size()==0)
        {
            cout<< "The current folder is empty!" <<endl;
        }
        else cout <<"The content of the current folder:"<<endl;
        for (int i=0;i<current_folder->getContent().size();i++)
        {
            if (current_folder->getContent().at(i)->isFolder())
            {
                cout <<current_folder->getContent().at(i)->getName()+" \t";
            }
            else
            {
                File* curr_file = dynamic_cast<File*>(current_folder->getContent().at(i));
                cout << curr_file->getName()+"."+curr_file->getExtension()+" \t";
            }
        }
    }
    else
    {
        cout << "Current folder is not defined!" <<endl;
    }
}

void printOptions()
{
    cout<<endl;
    cout << "Please input an option!" <<endl;
    cout << " 0. - Quit" << endl;
    cout << " 1. - Create new root folder" << endl;
    cout << " 2. - Change location" << endl;
    cout << " 3. - Add a file" << endl;
    cout << " 4. - Add a folder" << endl;
    cout << " 5. - Get size of the current folder" << endl;
    cout << " 6. - Print current location" << endl;
    cout << " 7. - Print the content of the current folder" << endl;
    cout << endl;
    cout << ">>>>>>>>>>>>>>" ;
}

void menu()
{
    int option=-1;
    while (option!=0)
    {
        printOptions();
        if (cin >> option)
        {
            cout <<endl;
            system("cls");
            switch (option)
            {
                case 0:
                    break;
                case 1:
                    createRootFolder();
                    break;
                case 2:
                    changeLocation();
                    break;
                case 3:
                    addFile();
                    break;
                case 4:
                    addFolder();
                    break;
                case 5:
                    size();
                    break;
                case 6:
                    printLocation();
                    break;
                case 7:
                    printContent();
                    break;
                default:
                    cout<< "Invalid choice!" <<endl;
                    break;
            }
        }
        else
        {
            cout <<"Invalid choice!"<<endl;
            cin.clear();
            cin.ignore();
            option=-1;
        }
        getch();
    }
}

int main()
{
    menu();
    return 0;
}