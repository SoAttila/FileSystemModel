#pragma once
#include <string>
#include <vector>

using namespace std;

class FileFolder //virtual
{
protected:
    string _name;
    double _size;
    string _location;
public:
    FileFolder(string name, double size, string location)
    {
        this->_name=name;
        this->_size=size;
        this->_location=location;
    }
    ~FileFolder() {}
    string getName() {return _name;}
    virtual double getSize() {return 0;}
    string getLocation() {return _location;}
    virtual bool isFolder() const {return false;}
    virtual bool isFile() const {return false;}
};

class File : public FileFolder
{
    protected:
        string _extension;
    public:
        File(string name, double size, string location, string extension): FileFolder(name,size,location),_extension(extension) {}
        ~File() {}
        virtual bool isFile() const override {return true;}
        virtual double getSize() {return _size;}
        string getExtension() {return _extension;}
};

class Folder : public FileFolder
{
    protected:
        bool _root;
        vector<FileFolder*> _content;
    public:
        Folder(string name, string location, bool root): FileFolder(name,0,location),_root(root),_content(vector<FileFolder*>()) {}
        ~Folder() {}
        virtual bool isFolder() const override {return true;}
        vector<FileFolder*> getContent() {return _content;}
        void addFile(string name, string extension, double size)
        {
            _content.push_back(new File(name,size,this->getLocation()+"/"+name,extension));
        }
        void addFolder(string name)
        {
            _content.push_back(new Folder(name, this->getLocation()+"/"+name,false));
        }
        virtual double getSize()
        {
            double size=0;
            for (int i=0;i<_content.size();i++)
            {
                size+=_content[i]->getSize();
            }
            return size;
        }
};
