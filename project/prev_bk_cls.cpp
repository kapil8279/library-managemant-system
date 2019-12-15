#include<fstream>
#include<iostream>
#include<cstring>
#include<cctype>
#include<iomanip>
#include"Search_book.cpp"
using namespace std;
class PrevBook{
	private:
		fstream prev_issue_file;
	public:
		PrevBook(){
			try{
				prev_issue_file.open("database/prev_issue.dat",ios::in|ios::app);
			}
			catch(string ex){
				prev_issue_file.open("database/prev_issue.dat",ios::in|ios::out);
			}
			prev_issue_file.close();
		}
		~PrevBook(){;
			prev_issue_file.close();
		}
		void prev_book_show(){
			int width = 15;
			ifstream file;
			file.open("database/prev_issue.dat",ios::binary);
			file.seekg(0,ios::end);
			long last = file.tellg();
			file.seekg(0,ios::beg);
			prev_issue bk;
			cout << left << setw(10) << "Sr.no" << setw(width+10) << "Book Name" << setw(10)<< "Stud. SR.NO" << setw(width+10) << "Student name" << setw(10) << "class" << setw(10) << "Section" << setw(width)<< "issue date" << setw(width) << "Return date" << endl;
			while(!file.eof() && file.tellg() < last){
				file.read((char*)&bk,sizeof(bk));
				cout << left<< setw(10) << bk.book.sr_no << setw(width+10) << bk.book.book_name << setw(10) << bk.std.sr_no << setw(width+10) << bk.std.name << setw(10) << bk.std.cls << setw(10) << bk.std.sec << setw(width) << bk.issue_time << setw(width) << bk.retrn_time << endl;
			}
			file.close();
			cout << "Done!\n";
		}
};
