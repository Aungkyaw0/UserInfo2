#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#define SIZE 100
#define NAME "Data.txt"//
using namespace std;
typedef unsigned short int usi;
//Function Delcaration
void insertData();
void read();
void readAllData();
void updateData();

//CLASS
class Data
{
    protected:
        int id;
        char username[SIZE];
        char password[SIZE];
        char location[SIZE];
        int amount;
        int age; 
    
};
class DataSet:public Data
{
    public:
        DataSet()
        {
            //username = "";
            //password = "";
            //location = "";
            id = 0;
            amount = 0;
            age = 0;
        }
        int getID();
        void getData();
        void Insert(DataSet data);   
        void readData(); 
        void displayData();
        int readTheData();
        void updateID(int y);
};

int DataSet::getID()
{
    int x = 0;
    ifstream obj;
    DataSet tmp;

    obj.open(NAME, ios::in);
    if(!obj)
    {
        cout << "Sorry";
    }
    else
    {
        while(!obj.eof())
        {
            obj.read((char *)&tmp, sizeof(tmp));
        }
        x = tmp.id;
        //cout << "ID :: " <<x;
        
    }
    obj.close();
    return x+1;
    
}
void DataSet::getData()
{
    cin.clear();
    cin.ignore();
    cout << "Enter the username ::> ";
    cin.getline(this->username, SIZE);
    cout << "Enter the password ::> ";
    cin.getline(this->password, SIZE);
    cout << "Enter the location ::> ";
    cin.getline(this->location, SIZE);
    cout << "Enter the the age  ::> ";
    cin >> this->age;
    cout << "Enter the amount   ::> ";
    cin >> this->amount;
    id = getID();
    //myData.Insert(myData);  
}
void DataSet::Insert(DataSet data)
{
    DataSet tmp;
    ifstream obj;
    usi status = 0;
    obj.open(NAME, ios::in);
    if(obj)
    {
        while(!obj.eof())
        {
            obj.read((char *)&tmp, sizeof(tmp));
            if(strcmp(data.username, tmp.username) == 0)
            {
                cout << "Sorry You Can't InsertData \"\""<< data.username<< " \"\" Was alreay exist"<< endl;
                status = 1;
                break;
            }
        }
    }

    if(status == 0)
    {
        fstream out;
        out.open(NAME, ios::app | ios::out);
        if(!out)
        {
            cout << "Sorry";
        }
        else
        {
        
            out.write((char*)&data, sizeof(data));
            cout << "\nInserting Done\n";
            out.close();
        }

    }
    
}
void DataSet::readData()
{
    ifstream obj;
    DataSet tmp;
    obj.open(NAME, ios::in);
    if(!obj)
    {
        cout << "Sorry";
    }
    else
    {
        while(!obj.eof())
        {
            obj.read((char *)& tmp, sizeof(tmp));
        }
    }
    
}
void DataSet::displayData()
{
    cout << "Record For ID :: " << this->id << "\n-------------------" << endl;
    cout << "ID       ::> " << this->id << endl;
    cout << "Username ::> " << this->username << endl;
    cout << "Password ::> " << this->password << endl;
    cout << "Location ::> " << this->location << endl;
    cout << "Age      ::> " << this->age << endl;
    cout << "Amount   ::> " << this->amount << endl;
    cout << "----------------------------\n" << endl;

}
int DataSet::readTheData()
{
    int count = 0;usi tmpInt = 0, p_status = 0;
    int usr_status = 0;
    char usrName[SIZE]; 
    char pass[SIZE];
    cout << "FINDING DATA FROM DATA BASE\n------------------------------\n";
    cout << "Enter the username ::> ";
    cin >> usrName;
    cout << "Enter the password ::> ";
    cin >> pass;

    DataSet tmp;
    ifstream obj;
    obj.open(NAME, ios::in);
    if(!obj)
    {
        cout << "Sorry";
        exit(1);
    }
    while(!obj.eof())
    {
        obj.read((char *)&tmp, sizeof(tmp));
        tmpInt++;
        if(strcmp(usrName, tmp.username) == 0)
        {
            usr_status = 1;
            if(strcmp(pass, tmp.password) == 0)
            {
                cout << "\nWelcome " << usrName << "\n------------------------\n";
                tmp.displayData();
                count = tmpInt -1;
                p_status = 1;
                break;
            }
            else
            {
                cout << "\nYour Password is wrong" << endl;
            }
        }
        
        
    }
    if(usr_status == 0)
    {
        cout << "Sorry There is NO DATA FOR " << usrName;
    }
    if(p_status == 0)
    {
        count = 404;
    }
    obj.close();
    return count;

}
void DataSet::updateID(int y)
{
    this->id = y+1;
}
int main()
{

    while(true)
    {
        usi op = 0;
        cout << "Welcome From The Database\n----------------------------\n"
             << "1. Insert Data\n2. Find Data\n3. Update Data\n4. View All Data\n5. Exit\n"
             << "Enter the operation number ::> ";
        cin >> op;
        switch (op)
        {
        case 1:
            insertData();
            break;
        case 2:
            read();
            break;
        case 3:
            updateData();
            break;
        case 4:
            readAllData();
            break;
        case 5:
            exit(1);
            break;
        default:
            break;
        }
           
    }

}

void insertData()
{

    char oc;
    cout << "Inserting Data to DATABASE\n-----------------------------------\n";
    DataSet myTest;
    while(true)
    {
        cout << "Insert Your Information\n-----------------------------\n";
        myTest.getData();
        myTest.Insert(myTest);
        cout << "Do You Want TO Add More(y,n) ::> ";
        cin >> oc;
        if(oc != 'y' && oc != 'Y')
        {
            break;
        }
    }

}
void readAllData()
{
    DataSet tmp;

    ifstream obj;
    obj.open(NAME, ios::in);

    if(!obj)
    {
        cout << "Sorry";
    }
    else
    {
        cout << "RECORD OF USERS\n--------------------\n";
        while(true)
        {
            obj.read((char *)&tmp, sizeof(tmp));
            if(obj.eof())
            {
                break;
            }
            tmp.displayData();            
        }
        
    }
    obj.close();
    
}
void read()
{
    DataSet test;
    test.readTheData();
}

void updateData()
{
    DataSet tmp;
    int status = 0; long pos;
    cout << "UPDATION DATA SESSION\n----------------------------" << endl;
    status = tmp.readTheData();
    cout << "STATUS ::> " << status << endl;
    if(status != 404)
    {
        fstream obj;
        obj.open(NAME, ios::in | ios::binary | ios::out);
        obj.seekp(0);
        //pos = obj.tellp();
        //cout << "POS :> "<<pos << endl;
        obj.seekp((sizeof(tmp) * status));
        //pos = obj.tellp();
        //cout << "POS :> "<<pos << endl;        
        tmp.getData();
        tmp.updateID(status);
        obj.write((char *)& tmp, sizeof(tmp));
        cout << "Updation Done";
    }


}
