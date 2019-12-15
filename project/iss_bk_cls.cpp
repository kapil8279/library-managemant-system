#include<iostream>
#include<string>
#include<cctype>
#include<sstream>
#include<ctime>
#include<iomanip>
#include<cstdlib>
#include"Search_book.cpp"
using namespace std;
using namespace std;
class IssueBook{
	private:
		int width = 15;
		fstream issue_file;
		Search srch;
		fstream book_file;
		fstream prev_issue_file;
		bool alpha(string s){
			for(int x=0;x<s.length();x++){
				if(isdigit(s[x])){
					return false;
				}
			}
			return true;
		}
		
		string gettime(){
			string dt = "";
			time_t now = time(0);
			tm *lmt = localtime(&now);
			stringstream day,mon,yer;
			day << lmt->tm_mday;
			dt += day.str();
			dt += "/"; 
			mon << lmt->tm_mon+1;
			dt += mon.str();
			dt += "/";
			yer << lmt->tm_year+1900;
			dt += yer.str();
			return dt;
			
		}
		
		
		bool avlble(string inp){
			string temp_inp;
			fstream org_file;
			all_book bk,temp_bk;
			long src_pos;
			char nm[30];
			org_file.open("database/issue_book.dat",ios::in|ios::binary);
			if(alpha(inp)){
				strcpy(nm,inp.c_str());
				long pos = srch.srch_iss_bk(nm);
				if(pos != -1){
					org_file.close();
					return false;
				}
				else{
					org_file.close();
					return true;
				}
			}
			else{
				strcpy(nm,inp.c_str());
				int sr = atoi(nm);
				long pos = srch.srch_all_bk(sr);
				if(pos != -1){
					org_file.close();
					return false;
				}
				else{
					org_file.close();
					return true;
				}
			}
		}
		
		
		
		
	public:
		IssueBook(){
			try{
				book_file.open("database/all_book.dat",ios::in|ios::app);
			}
			catch(string ex){
				book_file.open("database/all_book.dat",ios::in|ios::out);
			}
			
			try{
				issue_file.open("database/issue_book.dat",ios::in|ios::app);
			}
			catch(string ex){
				issue_file.open("database/issue_book.dat",ios::in|ios::out);
			}
			
			try{
				prev_issue_file.open("database/prev_issue.dat",ios::in|ios::app);
			}
			catch(string ex){
				prev_issue_file.open("database/prev_issue.dat",ios::in|ios::out);
			}
			book_file.close();
			issue_file.close();
			prev_issue_file.close();
		}
		~IssueBook(){
			issue_file.close();
		}
		void show_iss_book(){
			ifstream file;
			file.open("database/issue_book.dat",ios::in|ios::binary);
			file.seekg(0,ios::end);
			long last = file.tellg();
			file.seekg(0,ios::beg);
			issue_book bk;
			cout << left << setw(width) << "Book Sr.no" << setw(width) << "Book Name" << setw(width) << "Stud SR.NO" << setw(width) << "Stud. Name" << setw(width) << "Stud class" << setw(width) << "Stud section"<< setw(width) << "Issue date" << endl;
			while(!file.eof() && file.tellg() < last){
				file.read((char*)&bk,sizeof(bk));
				cout << left<< setw(width) << bk.book.sr_no << setw(width) << bk.book.book_name << setw(width) << bk.std.sr_no << setw(width) << bk.std.name << setw(width) << bk.std.cls << setw(width) << bk.std.sec << setw(width) << bk.issue_time << endl;
			}
			file.close();
			cout << "Done!\n";
		}
		void add_iss_book(){
			char choice;
			long src_pos;
			ofstream file;
			file.open("database/issue_book.dat",ios::app|ios::binary|ios::ate);
			fstream allbk_file;
			allbk_file.open("database/all_book.dat",ios::in|ios::out|ios::binary);
			prev_issue_file.open("database/prev_issue.dat",ios::app|ios::binary|ios::ate);
			string temp_inp="";
			issue_book bk;
			all_book temp_bk;
			prev_issue prev_bk;
			cout << "Enter the book name(Enter 0 to exist): ";
			getline(cin,temp_inp,'\n');
			if(strcmp(temp_inp.c_str(),"0")== 0){
				return;
			}
			else{
				strcpy(bk.book.book_name,temp_inp.c_str());
			}
			if(!avlble(temp_inp)){
				cout << "Book not Available\n";
				return;
			}
			cout << "Enter the SR.NO of student: ";
			cin >> bk.std.sr_no;
			cin.ignore();
			cout << "Enter the student name: ";
			getline(cin,temp_inp,'\n');
			strcpy(bk.std.name,temp_inp.c_str());
			cout << "Enter the student class: ";
			getline(cin,temp_inp,'\n');
			strcpy(bk.std.cls,temp_inp.c_str());
			cout << "Enter the student section: ";
			cin.get(bk.std.sec);
			bk.avail = false;
			strcpy(bk.issue_time,gettime().c_str());
			src_pos = srch.srch_all_bk(bk.book.book_name);
			allbk_file.seekg(src_pos,ios::beg);
			allbk_file.read((char *)&temp_bk,sizeof(temp_bk));
			bk.book.sr_no = temp_bk.sr_no;
			src_pos = 0;
			//update prev isuue bokk database
				
			prev_bk.book = bk.book;
			prev_bk.std = bk.std;
			strcpy(prev_bk.issue_time,bk.issue_time);
			string empt_tm = "None";
			strcpy(prev_bk.retrn_time,empt_tm.c_str());
			prev_bk.avail = false;
				
				
			//update all book datatbase
				
			src_pos =  srch.srch_all_bk(bk.book.book_name);
			allbk_file.seekg(src_pos,ios::beg);
			allbk_file.read((char *)&temp_bk,sizeof(temp_bk));
			temp_bk.avail = false;
			allbk_file.seekp(src_pos,ios::beg);
			allbk_file.write((char *)&temp_bk,sizeof(temp_bk));
				
				
			file.write((char*)&bk,sizeof(bk));
			prev_issue_file.write((char *)&prev_bk,sizeof(prev_bk));
	
			file.close();
			prev_issue_file.close();
			allbk_file.close();
			cout << "Updating Record !!!\n";
			cout << "===========================\n";
		}
		
		
		
		void search_iss_bk(){
			
			string inp;
			fstream org_file;
			issue_book bk;
			char nm[30];
			org_file.open("database/issue_book.dat",ios::in|ios::binary);
			cout << "enter the Book name or SR.NO: ";
			getline(cin,inp,'\n');
			if(alpha(inp)){
				strcpy(nm,inp.c_str());
				long pos = srch.srch_iss_bk(nm);
				if(pos != -1){
					org_file.seekg(pos,ios::beg);
					org_file.read((char *)&bk,sizeof(bk));
					cout << "=====================================================================================\n";
					cout << left << setw(width) << "Book Sr.no" << setw(width) << "Book Name" << setw(width) << "Stud SR.NO" << setw(width) << "Stud. Name" << setw(width) << "Stud class" << setw(width) << "Stud section"<< setw(width) << "Issue date" << endl;
					cout << left<< setw(width) << bk.book.sr_no << setw(width) << bk.book.book_name << setw(width) << bk.std.sr_no << setw(width) << bk.std.name << setw(width) << bk.std.cls << setw(width) << bk.std.sec << setw(width) << bk.issue_time << endl;
					cout << "=====================================================================================\n";
					org_file.close();
				}
				else{
					cout << "Book not found!\n";
					org_file.close();
					return;
				}
			}
			
			else{
				strcpy(nm,inp.c_str());
				int sr = atoi(nm);
				long pos = srch.srch_iss_bk(sr);
				if(pos != -1){
					org_file.seekg(pos,ios::beg);
					org_file.read((char *)&bk,sizeof(bk));
					cout << "=====================================================================================\n";
					cout << left << setw(width) << "Book Sr.no" << setw(width) << "Book Name" << setw(width) << "Stud SR.NO" << setw(width) << "Stud. Name" << setw(width) << "Stud class" << setw(width) << "Stud section"<< setw(width) << "Issue date" << endl;
					cout << left<< setw(width) << bk.book.sr_no << setw(width) << bk.book.book_name << setw(width) << bk.std.sr_no << setw(width) << bk.std.name << setw(width) << bk.std.cls << setw(width) << bk.std.sec << setw(width) << bk.issue_time << endl;
					cout << "=====================================================================================\n";
					org_file.close();
				}
				else{
					org_file.close();
					cout << "Book not found!\n";
					return;
				}
			}
			
		}
		
		
		void remove_iss_bk(){
			string inp;
			fstream org_file,temp_file,all_bk_file,prev_bk_file;
			issue_book bk;
			long src_pos;
			char nm[30];
			org_file.open("database/issue_book.dat",ios::in|ios::binary);
			temp_file.open("database/temp_all.dat",ios::out|ios::binary);
			
			cout << "enter the Book name or SR.NO: ";
			getline(cin,inp,'\n');
			if(alpha(inp)){
				strcpy(nm,inp.c_str());
				long pos = srch.srch_iss_bk(nm);
				if(pos != -1){
					org_file.seekg(0,ios::end);
					long last = org_file.tellg();
					org_file.seekg(0,ios::beg);
					while(!org_file.eof() && org_file.tellg() < last){
						org_file.read((char *)&bk,sizeof(bk));
						if((org_file.tellg()-sizeof(bk)) != pos){
							temp_file.write((char *)&bk,sizeof(bk));
						}
					}
					// update previous book
					prev_bk_file.open("database/prev_issue.dat",ios::app|ios::binary|ios::in);
					prev_issue prev_book;
					src_pos = srch.srch_prev_bk(nm);
					prev_bk_file.seekg(src_pos,ios::beg);
					prev_bk_file.read((char *)&prev_book,sizeof(prev_book));
					src_pos = prev_bk_file.tellg()-sizeof(prev_book);
					prev_book.avail = true;
					string tm = gettime();
					strcpy(prev_book.retrn_time,tm.c_str());
					prev_bk_file.seekg(src_pos,ios::beg);
					prev_bk_file.write((char *)&prev_book,sizeof(prev_book));
					prev_bk_file.close();
					
					org_file.close();
					temp_file.close();
					
					remove("database/issue_book.dat");
					rename("database/temp_all.dat","database/issue_book.dat");
				}
				else{
					org_file.close();
					temp_file.close();
					cout << "Book not found!\n";
					return;
				}
			}
			
			else{
				strcpy(nm,inp.c_str());
				int sr = atoi(nm);
				long pos = srch.srch_iss_bk(sr);
				if(pos != -1){
					org_file.seekg(0,ios::end);
					long last = org_file.tellg();
					org_file.seekg(0,ios::beg);
					while(!org_file.eof() && org_file.tellg() < last){
						org_file.read((char *)&bk,sizeof(bk));
						if((org_file.tellg()-sizeof(bk)) != pos){
							temp_file.write((char *)&bk,sizeof(bk));
						}
					}
					prev_bk_file.open("database/prev_issue.dat",ios::app|ios::binary|ios::in);
					prev_issue prev_book;
					pos = srch.srch_prev_bk(sr);
					prev_bk_file.seekg(pos,ios::beg);
					prev_bk_file.read((char *)&prev_book,sizeof(prev_book));
					prev_book.avail = true;
					strcpy(prev_book.retrn_time,gettime().c_str());
					pos = prev_bk_file.tellg()-sizeof(prev_book);
					prev_bk_file.seekg(pos,ios::beg);
					prev_bk_file.write((char *)&prev_book,sizeof(prev_book));
					prev_bk_file.close();
					
					org_file.close();
					temp_file.close();
					
					remove("database/issue_book.dat");
					rename("database/temp_all.dat","database/issue_book.dat");
					
				}
				else{
					org_file.close();
					temp_file.close();
					cout << "Book not found!\n";
					return;
				}
			}
		}
};
