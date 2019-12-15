#include<iostream>
#include<fstream>
#include<ctime>
#include<iomanip>
#include<cstring>
#include<cctype>
#include<cstdlib>
#include"Search_Book.cpp"
using namespace std;
class AllBook{
	private:
		int width = 20;
		int book_no;
		fstream book_file;
		fstream prev_issue_file;
		Search srch;
	bool alpha(string s){
		for(int x=0;x<s.length();x++){
			if(isdigit(s[x])){
				return false;
			}
		}
		return true;
	}
	void calc_sr(){
		fstream file;
		all_book temp_bk;
		file.open("database/all_book.dat",ios::in|ios::out|ios::binary);
		file.seekg(0,ios::end);
		long last = file.tellg();
		file.seekg(0,ios::beg);
		book_no = 0;
		while(!file.eof() && file.tellg() < last){
			file.read((char *)&temp_bk,sizeof(temp_bk));
			temp_bk.sr_no = ++book_no;
			file.seekp(file.tellg()- sizeof(temp_bk));
			file.write((char *)&temp_bk,sizeof(temp_bk));
		}
		file.close();
	}
	public:
		AllBook(){
			book_no = 0;
			try{
				book_file.open("database/all_book.dat",ios::in|ios::app);
			}
			catch(string ex){
				book_file.open("database/all_book.dat",ios::in|ios::out);
			}
			book_file.seekg(0,ios::end);
			long last = book_file.tellg();
			book_file.seekg(0,ios::beg);
			while(!book_file.eof() && book_file.tellg() < last){
				all_book bk;
				book_file.read((char*)&bk,sizeof(bk));
				book_no = bk.sr_no;
			}
			book_file.close();
		}
		~AllBook(){
			book_file.close();
		}
		void show_all_book(){
			int width = 20;
			ifstream file;
			calc_sr();
			file.open("database/all_book.dat",ios::binary);
			file.seekg(0,ios::end);
			long last = file.tellg();
			file.seekg(0,ios::beg);
			all_book bk;
			cout << left << setw(width-10) << "Sr.no" << setw(width+10) << "Name" << setw(width) << "Writer" << setw(width) << "publisher" << setw(width) << "Available" << endl;
			while(!file.eof() && file.tellg() < last){
				file.read((char*)&bk,sizeof(bk));
				cout << left<< setw(width-10) << bk.sr_no << setw(width+10) << bk.book_name << setw(width) << bk.writer << setw(width) << bk.pub;
				if(srch.srch_iss_bk(bk.sr_no) == -1){
					cout << setw(width) << "Avail." << endl;
				}
				else{
					cout << setw(width) << "Not Avail." << endl;
				}
			}
			file.close();
			cout << "Done!\n";
		}
		void add_book(){
			char choice;
			ofstream file;
			string temp_inp="";
			all_book bk;
			file.open("database/all_book.dat",ios::in|ios::app|ios::binary|ios::ate);
			calc_sr();
			bk.sr_no = ++book_no;
			cout << "Enter the book name: ";
			getline(cin,temp_inp,'\n');
			strcpy(bk.book_name,temp_inp.c_str());
			cout << "Enter the writer name: ";
			getline(cin,temp_inp,'\n');
			strcpy(bk.writer,temp_inp.c_str());
			cout << "Enter the publisher name: ";
			getline(cin,temp_inp,'\n');
			strcpy(bk.pub,temp_inp.c_str());
			bk.avail = true;
			file.write((char*)&bk,sizeof(bk));
			file.close();
			cout << "Adding new book !!!\n";
			cout << "===========================\n";
		}
		void remv_book(){
			string inp;
			fstream org_file,temp_file;
			all_book bk;
			char nm[30];
			org_file.open("database/all_book.dat",ios::in|ios::binary);
			temp_file.open("database/temp_all.dat",ios::out|ios::binary);
			cout << "enter the Book name or SR.NO: ";
			getline(cin,inp,'\n');
			if(alpha(inp)){
				strcpy(nm,inp.c_str());
				long pos = srch.srch_all_bk(nm);
				if(pos != -1){
					org_file.seekg(0,ios::end);
					long last = org_file.tellg();
					org_file.seekg(0,ios::beg);
					while(!org_file.eof() && org_file.tellg() < last){
						org_file.read((char *)&bk,sizeof(bk));
						if((org_file.tellg()-sizeof(bk)) != pos){
							temp_file.write((char *)&bk,sizeof(bk));
						}
						else{
							continue;
						}
					}
					org_file.close();
					temp_file.close();
					
					remove("database/all_book.dat");
					rename("database/temp_all.dat","database/all_book.dat");
					cout << "Book Removed\n";
				}
				else{
					cout << "Book not found!\n";
					return;
				}
			}
			
			else{
				strcpy(nm,inp.c_str());
				int sr = atoi(nm);
				long pos = srch.srch_all_bk(sr);
				if(pos != -1){
					org_file.seekg(0,ios::end);
					long last = org_file.tellg();
					org_file.seekg(0,ios::beg);
					while(!org_file.eof() && org_file.tellg() < last){
						org_file.read((char *)&bk,sizeof(bk));
						if((org_file.tellg()-sizeof(bk)) != pos){
							temp_file.write((char *)&bk,sizeof(bk));
						}
						else{
							continue;
						}
					}
					org_file.close();
					temp_file.close();
					
					remove("database/all_book.dat");
					rename("database/temp_all.dat","database/all_book.dat");
					calc_sr();
					cout << "Book Removed\n";
					
				}
				else{
					cout << "Book not found!\n";
					return;
				}
			}
		}
		void search_book(){
			string inp;
			fstream org_file;
			all_book bk;
			char nm[30];
			org_file.open("database/all_book.dat",ios::in|ios::binary);
			cout << "enter the Book name or SR.NO: ";
			getline(cin,inp,'\n');
			if(alpha(inp)){
				strcpy(nm,inp.c_str());
				long pos = srch.srch_all_bk(nm);
				if(pos != -1){
					org_file.seekg(pos,ios::beg);
					org_file.read((char *)&bk,sizeof(bk));
					cout << "=====================================================================================\n";
					cout << left << setw(width) << "Sr.no" << setw(width) << "Name" << setw(width) << "Writer" << setw(width) << "publisher" << setw(width) << "Available" << endl;
					cout << left<< setw(width) << bk.sr_no << setw(width) << bk.book_name << setw(width) << bk.writer << setw(width) << bk.pub;
					if(bk.avail){
						cout << setw(width) << "Avail." << endl;
					}
					else{
						cout << setw(width) << "Not Avail." << endl;
					}
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
				long pos = srch.srch_all_bk(sr);
				if(pos != -1){
					org_file.seekg(pos,ios::beg);
					org_file.read((char *)&bk,sizeof(bk));
					cout << "=====================================================================================\n";
					cout << left << setw(width) << "Sr.no" << setw(width) << "Name" << setw(width) << "Writer" << setw(width) << "publisher" << setw(width) << "Available" << endl;
					cout << left<< setw(width) << bk.sr_no << setw(width) << bk.book_name << setw(width) << bk.writer << setw(width) << bk.pub;
					if(bk.avail){
						cout << setw(width) << "Avail." << endl;
					}
					else{
						cout << setw(width) << "Not Avail." << endl;
					}
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
		
		void update_book(){
			
			
					
			string inp,temp_inp;
			fstream org_file;
			all_book bk,temp_bk;
			char nm[30];
			
			cout << "enter the Book name or SR.NO: ";
			getline(cin,inp,'\n');
			if(alpha(inp)){
				org_file.open("database/all_book.dat",ios::in|ios::app|ios::binary);
				strcpy(nm,inp.c_str());
				long pos = srch.srch_all_bk(nm);
				if(pos != -1){
					//update all book datatbase
					org_file.seekg(pos,ios::beg);
					org_file.read((char *)&temp_bk,sizeof(temp_bk));
					cout << "Enter updated Data:\n";
					cout << "++++++++++++++++++++++++++++++++++\n";
					
					cout << "Enter the book name: ";
					getline(cin,temp_inp,'\n');
					strcpy(bk.book_name,temp_inp.c_str());
					cout << "Enter the writer name: ";
					getline(cin,temp_inp,'\n');
					strcpy(bk.writer,temp_inp.c_str());
					cout << "Enter the publisher name: ";
					getline(cin,temp_inp,'\n');
					strcpy(bk.pub,temp_inp.c_str());
					
					if(strcmp(bk.book_name,"") == 0){
						strcpy(bk.book_name,temp_bk.book_name);
					}
					if(strcmp(bk.writer,"")== 0){
						strcpy(bk.writer,temp_bk.writer);
					}
					if(strcmp(bk.pub,"") == 0){
						strcpy(bk.pub,temp_bk.pub);
					}
					bk.avail = true;
					bk.sr_no = temp_bk.sr_no;
					pos = srch.srch_all_bk(nm);
					org_file.seekg(pos,ios::beg);
					org_file.write((char *)&bk,sizeof(bk));
					org_file.close();
				}
				else{
					cout << "Book not found\n";
					org_file.close();
					return;	
				}
			}
			else{
				org_file.open("database/all_book.dat",ios::in|ios::app|ios::binary);
				strcpy(nm,inp.c_str());
				int sr = atoi(nm);
				long pos = srch.srch_all_bk(sr);
				if(pos != -1){
					org_file.seekg(pos,ios::beg);
					org_file.read((char *)&temp_bk,sizeof(temp_bk));
					
					cout << "Enter updated Data:\n";
					cout << "++++++++++++++++++++++++++++++++++\n";
					
					cout << "Enter the book name: ";
					getline(cin,temp_inp,'\n');
					strcpy(bk.book_name,temp_inp.c_str());
					cout << "Enter the writer name: ";
					getline(cin,temp_inp,'\n');
					strcpy(bk.writer,temp_inp.c_str());
					cout << "Enter the publisher name: ";
					getline(cin,temp_inp,'\n');
					strcpy(bk.pub,temp_inp.c_str());
					
					if(strcmp(bk.book_name,"") == 0){
						strcpy(bk.book_name,temp_bk.book_name);
					}
					if(strcmp(bk.writer,"")== 0){
						strcpy(bk.writer,temp_bk.writer);
					}
					if(strcmp(bk.pub,"")==0){
						strcpy(bk.pub,temp_bk.pub);
					}
					bk.avail = true;
					bk.sr_no = temp_bk.sr_no;
					pos = srch.srch_all_bk(nm);
					org_file.seekp(pos,ios::beg);
					org_file.write((char *)&bk,sizeof(bk));
					org_file.close();
					cout << "Done\n";
				}
				else{
					org_file.close();
					cout << "Book not found\n";
					return;
					
				}
					
			}
			
		}
		
		void avail_book(){
			
			int width = 20;
			ifstream file;
			file.open("database/all_book.dat",ios::binary|ios::in);
			file.seekg(0,ios::end);
			long last = file.tellg();
			file.seekg(0,ios::beg);
			all_book bk;
			cout << left << setw(width) << "Sr.no" << setw(width) << "Name" << setw(width) << "Writer" << setw(width) << "publisher" << setw(width) << "Available" << endl;
			while(!file.eof() && file.tellg() < last){
				file.read((char*)&bk,sizeof(bk));
				if(bk.avail){
					cout << left<< setw(width) << bk.sr_no << setw(width) << bk.book_name << setw(width) << bk.writer << setw(width) << bk.pub;
					cout << setw(width) << "Avail." << endl;
				}
			}
			file.close();
			cout << "Done!\n";
			
			
		}
		
};
