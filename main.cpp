/*19CS10014: Ayush Pattnayak
Library Management System
Assignment 1*/
#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string> 
#include <cstring>
#include <dirent.h>
using namespace std;

class book{
    public :
        string filename;
        string title;
        string author;
        
};


string qtab = "         ";
string tab = "      ";

void addtoindex(DIR* dr, struct dirent *d,long long& nbooks){
    fstream myFile("index.txt", fstream::out | fstream::app);
    long long x= nbooks;
    int i=-1;
    while(d->d_name[i+1]!='\0') i++;
    if(i>=3 && d->d_name[i-3]=='.' && d->d_name[i-2]=='t' && d->d_name[i-1]=='x' && d->d_name[i]=='t'){
        string s(d->d_name);
        cout<<s<<" is a text file and has been taken into the system.\nWhat type of a book is it? ::";
        string type;
        //scanf("%[^\n]",type); getchar();
        cin>>type;
        //cin.ignore (std::numeric_limits<std::streamsize>::max(), '\n'); 
        cin.ignore();
        nbooks++;
        string append_string = (to_string(x+1) + ") " + s + " -----------" + type + "\n");

        
        myFile.write(append_string.c_str(), append_string.length());
    }

    myFile.close();

}

void newly_added(DIR* dr, struct dirent *d,long long& nbooks){
    fstream myFile("index.txt", fstream::out | fstream::app);
    long long x= nbooks;
    int i=-1,t=0;
    while(d->d_name[i+1]!='\0') i++;
    if(i>=3 && d->d_name[i-3]=='.' && d->d_name[i-2]=='t' && d->d_name[i-1]=='x' && d->d_name[i]=='t'){
        string s(d->d_name);
        cout<<s<<" is a text file and has been newly added to the system.\nWhat type of a book is it? ::";
        string type;
        //scanf("%[^\n]",type); getchar();
        cin>>type;
        //cin.ignore (std::numeric_limits<std::streamsize>::max(), '\n'); 
        cin.ignore();
        nbooks++;
        string append_string = (to_string(x+1) + ") " + s + " -----------" + type + "\n");

        
        myFile.write(append_string.c_str(), append_string.length());
    }
    
}

int checktxt(string s){
    int i=-1,t=0;
    while(s[i+1]!='\0') i++;
    if(i>=3 && s[i-3]=='.' && s[i-2]=='t' && s[i-1]=='x' && s[i]=='t'){
        return 1;
    }
    else return 0;   
}

int alreadynotpresent(vector <string> v,string k){
    int len = v.size();
    for(int i=0;i<len;i++){
        if(v[i]==k) return 0;
    }
    return 1;
}

void print_details(vector <book> v){
        int sz = v.size();
        cout<<"The information for "<<sz<<" books is as such:\n\n";
        for(int i=0;i<sz;i++){
            cout<<"\n"<<i+1<<") FileName: "<<v[i].filename;
            cout<<"\n  Title   : "<<v[i].title;
            cout<<"\n  Author  : "<<v[i].author;
            cout<<"\n";
        }
 }


//MAIN
int main(){
    struct dirent *d;
    DIR *dr;
    //dr = opendir(".");
    long long num_books = 0;
    cout<< "\n\nWelcome to my Library Management System. At the moment, there are no books listed with us. Give the path of a directory first:\n";
    
    fstream file_index; //object of fstream class
    file_index.open("index.txt", ios::out);
    if (!file_index){
        cout << "Could not open file" << endl;
        return 0;
    }
    cout << "File index.txt has been created." << endl;
    file_index <<qtab<<"Welcome to the LMS. Here we store the books and their information.\n" << endl;


    char input_dirpath[1000];
    scanf("%[^\n]",input_dirpath); getchar();
    const char* dir_path = input_dirpath;
    //cout<<"Enter path of directory here: (default-->present directory) ";
    //cin>>dir_path;
    
    //LISTING ALL FILES HERE:
    dr = opendir(dir_path);
    if(dr!=NULL)
    {
        cout<<"List of Files & Folders here:-\n";
        for(d=readdir(dr); d!=NULL; d=readdir(dr)){
            cout<<d->d_name<<endl;
            //v.push_back(d->d_name);
        }
        closedir(dr);
    }
    else
        cout<<"\nError Occurred!";
    
    
    //ADDING TXT FILES TO INDEX FOR FIRST TIME
    vector<string> v;
    vector<book> booklist(0,book());
    bool notxt=true;
    dr = opendir(dir_path);
    
    if(dr!=NULL){
        
        cout<<"Working on .txt files here:-\n";
        for(d=readdir(dr); d!=NULL; d=readdir(dr)){
            addtoindex(dr,d,num_books);
            if(checktxt(d->d_name)==1) {
                v.push_back(d->d_name);
                ifstream file1(d->d_name);
                string line="";
                book data;
                data.filename = d->d_name;
                if (file1.is_open()){
                    while ( getline (file1,line) ){
                            string linecom = line;
                            int ind=7;
                            int a=0,b=0;
                            linecom.resize(7);
                            if(linecom=="Title: "){
                                while(line[ind]!='\0'&&ind<255){
                                    data.title+=line[ind];
                                    ind++;
                                    a=1;
                                }
                            }
                            else if(linecom=="Author:"){
                                while(line[ind]!='\0'&&ind<255){
                                    data.author+=line[ind];
                                    ind++;
                                    b=1;
                                }
                            } 
                            
                            line="";
                            linecom="";
                            if(a*b>0) break;
                        }
                        booklist.push_back(data);
                    file1.close();
                }

                notxt = false;
            }
        }
        if(notxt==true){
            cout<<"\nNo text files found.\n\n";
        }
        closedir(dr);

    }
    else{
        cout<<"\nError Occurred!";
    }
    
    
    //CHECKING FOR NEW FILES
    string chk;
    cout<<"Do you want to check for new files? Enter no to exit, yes to continue checking.\n  ";
    getline(cin,chk);
     while(chk!="NO"&&chk!="no"){
            dr = opendir(dir_path);
            if(dr!=NULL)
            {
                cout<<"Checking new .txt files here:-\n";
                for(d=readdir(dr); d!=NULL; d=readdir(dr)){
                    if(checktxt(d->d_name)==1 && alreadynotpresent(v,d->d_name)==1){
                        newly_added(dr,d,num_books);
                        v.push_back(d->d_name);
                    }
                }
                closedir(dr);
            }
            else{
                cout<<"\nError Occurred!";
            }

            cout<<"\n\nContinue check for new files? Enter no to exit, yes to continue checking.\n\n  ";
            getline(cin,chk);
    }

    file_index.close();
    long long x = num_books;
    fstream myFile("index.txt", fstream::out | fstream::app);
    string append_string = (qtab+qtab+"Presently there are " + to_string(x) + " books listed here.");
    myFile.write(append_string.c_str(), append_string.length());

    

    //file_index <<qtab<<qtab<<"Presently there are "<<num_books<<"books listed here."<< endl;

    
    //file.close();

    //USE CASE 2

    cout<<"Enter yes to display information of all books:";
    chk="";
    getline(cin,chk);

    if(chk=="yes"||chk=="YES"||chk=="Yes"){
        
        print_details(booklist);
    }

    vector <int> titleind,authind;
    int titlecnt=0,authcnt=0;
    cout<<"Enter yes to search by title:";
    chk="";
    getline(cin,chk);

    if(chk=="yes"||chk=="YES"||chk=="Yes"){
        cout<<"Enter the title:";
        chk="";
        getline(cin,chk);
        int sz = v.size();
        
        for(int i=0;i<sz;i++){
            if(booklist[i].title.find(chk) != std::string::npos){
                titleind.push_back(i);
                titlecnt++;
            }
        }
        if(titlecnt>0) 
        {
            cout<<"Here is a matching result:\n\n";
            int index = titleind[0];

            dr = opendir(dir_path);
            if(dr!=NULL){
                for(d=readdir(dr); d!=NULL; d=readdir(dr)){
                    if(d->d_name==booklist[index].filename){
                        ifstream file1 (d->d_name);
                        string line;
                        if (file1.is_open()){
                            while ( getline (file1,line) && line[0]!='*'){                                
                            }
                            for(int y=0;y<50;y++){
                                getline(file1,line);
                                cout<<line<<"\n";
                            }
                               
                            file1.close();
                        }
                        break;
                    }
                }
        
                closedir(dr);
                        
                }
                
            }
    

        }

    cout<<"Enter yes to search by author:";
    chk="";
    getline(cin,chk);

    if(chk=="yes"||chk=="YES"||chk=="Yes"){
        cout<<"Enter the author name:";
        chk="";
        getline(cin,chk);
        int sz = v.size();
        
        
        for(int i=0;i<sz;i++){
            if(booklist[i].author.find(chk) != std::string::npos){
                authind.push_back(i);
                authcnt++;
            }
        }

        if(authcnt>0) 
        {
            cout<<"Here is a matching result:\n\n";
            int index = authind[0];

            dr = opendir(dir_path);
            if(dr!=NULL){
                for(d=readdir(dr); d!=NULL; d=readdir(dr)){
                    if(d->d_name==booklist[index].filename){
                        ifstream file1 (d->d_name);
                        string line;
                        if (file1.is_open()){
                            while ( getline (file1,line) && line[0]!='*'){                                
                            }
                            for(int y=0;y<50;y++){
                                getline(file1,line);
                                cout<<line<<"\n";
                            }
                               
                            file1.close();
                        }
                        break;
                    }
                }
        
                closedir(dr);
                        
                }
                closedir(dr);
            }
    }





    system("pause");
    return 0;
}