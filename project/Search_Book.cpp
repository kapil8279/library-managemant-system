//functionality for searching book
#ifndef SEARCH_BOOK_CPP
#define SEARCH_BOOK_CPP
#include<fstream>
#include<iostream>
#include<cstring>
#include<cctype>
using namespace std;
struct all_book{
	int sr_no;
	char book_name[30];
	char writer[30];
	char pub[30];
	bool avail;
};

struct student{
	int sr_no;
	char name[30];
	char cls[5];
	char sec;
};

struct issue_book{
	all_book book;
	student std;
	bool avail;
	char issue_time[30];
};

struct prev_issue{
	all_book book;
	student std;
	char issue_time[30];
	char retrn_time[30];
	bool avail;
};



// class for search the book from file;
class Search{
	fstream all_bk_file;
	fstream iss_bk_file;
	fstream prev_bk_file;
	public:
		Search(){
			/*
			all_bk_file.open("database/all_book.dat",ios::in|ios::binary);
			iss_bk_file.open("database/issue_book.dat",ios::in|ios::binary);
			prev_bk_file.open("database/prev_issue.dat",ios::in|ios::binary);
			*/
		}
		~Search(){
			/*
			all_bk_file.close();
			iss_bk_file.close();
			prev_bk_file.close();
			*/
		}
		long srch_all_bk(int all_bk_sr);
		long srch_all_bk(char all_bk_nm[30]);
		long srch_iss_bk(int iss_sr);
		long srch_iss_bk(char iss_bk[30]);
		long srch_prev_bk(int prev_bk_sr);
		long srch_stud(char stud_nm[30]);
		long srch_prev_bk(char prev_bk_nm[30]);
};


// search book from all book database
long Search::srch_all_bk(char all_bk_nm[30]){
	Search::all_bk_file.open("database/all_book.dat",ios::in|ios::binary);
	long pos = -1;
	all_bk_file.seekg(0,ios::end);
	long end_point = all_bk_file.tellg();
	all_bk_file.seekg(0,ios::beg);
	while(!all_bk_file.eof() && all_bk_file.tellg()< end_point){
		all_book bk;
		all_bk_file.read((char *)&bk,sizeof(bk));
		if(strcmp(bk.book_name,all_bk_nm) == 0){
			pos = all_bk_file.tellg() - sizeof(bk);
			break;
		}
	}
	Search::all_bk_file.close();
	return pos;
}
long Search::srch_all_bk(int all_bk_sr){
	Search::all_bk_file.open("database/all_book.dat",ios::in|ios::binary);
	long pos = -1;
	all_bk_file.seekg(0,ios::end);
	long end_point = all_bk_file.tellg();
	all_bk_file.seekg(0,ios::beg);
	while(!all_bk_file.eof() && all_bk_file.tellg()< end_point){
		all_book bk;
		all_bk_file.read((char *)&bk,sizeof(bk));
		if(bk.sr_no == all_bk_sr){
			pos = all_bk_file.tellg() - sizeof(bk);
			break;
		}
	}
	Search::all_bk_file.close();
	return pos;
}

long Search::srch_iss_bk(char iss_bk[30]){
	iss_bk_file.open("database/issue_book.dat",ios::in|ios::binary);
	long pos = -1;
	iss_bk_file.seekg(0,ios::end);
	long end_point = iss_bk_file.tellg();
	iss_bk_file.seekg(0,ios::beg);
	while(!iss_bk_file.eof() && iss_bk_file.tellg()< end_point){
		issue_book bk;
		iss_bk_file.read((char *)&bk,sizeof(bk));
		if(strcmp(bk.book.book_name,iss_bk) == 0){
			pos = iss_bk_file.tellg() - sizeof(bk);
			break;
		}
	}
	Search::iss_bk_file.close();
	return pos;
}

long Search::srch_iss_bk(int iss_sr){
	iss_bk_file.open("database/issue_book.dat",ios::in|ios::binary);
	long pos = -1;
	iss_bk_file.seekg(0,ios::end);
	long end_point = iss_bk_file.tellg();
	iss_bk_file.seekg(0,ios::beg);
	while(!iss_bk_file.eof() && iss_bk_file.tellg()< end_point){
		issue_book bk;
		iss_bk_file.read((char *)&bk,sizeof(bk));
		if(bk.book.sr_no == iss_sr){
			pos = iss_bk_file.tellg() - sizeof(bk);
			break;
		}
	}
	Search::iss_bk_file.close();
	return pos;
}

long Search::srch_prev_bk(char prev_bk_nm[30]){
	prev_bk_file.open("database/prev_issue.dat",ios::in|ios::binary);
	long pos = -1;
	prev_bk_file.seekg(0,ios::end);
	long end_point = prev_bk_file.tellg();
	prev_bk_file.seekg(0,ios::beg);
	while(!prev_bk_file.eof() && prev_bk_file.tellg()< end_point){
		prev_issue bk;
		prev_bk_file.read((char *)&bk,sizeof(bk));
		if(strcmp(bk.book.book_name,prev_bk_nm) == 0){
			pos = prev_bk_file.tellg() - sizeof(bk);
			break;
		}
	}
	Search::prev_bk_file.close();
	return pos;
}

long Search::srch_prev_bk(int prev_bk_sr){
	prev_bk_file.open("database/prev_issue.dat",ios::in|ios::binary);
	long pos = -1;
	prev_bk_file.seekg(0,ios::end);
	long end_point = prev_bk_file.tellg();
	prev_bk_file.seekg(0,ios::beg);
	while(!prev_bk_file.eof() && prev_bk_file.tellg()< end_point){
		prev_issue bk;
		prev_bk_file.read((char *)&bk,sizeof(bk));
		if(bk.book.sr_no == prev_bk_sr){
			pos = prev_bk_file.tellg() - sizeof(bk);
			break;
		}
	}
	Search::prev_bk_file.close();
	return pos;
}

long Search::srch_stud(char stud_nm[30]){
	prev_bk_file.open("database/prev_issue.dat",ios::in|ios::binary);
	long pos = -1;
	prev_bk_file.seekg(0,ios::end);
	long end_point = prev_bk_file.tellg();
	prev_bk_file.seekg(0,ios::beg);
	while(!prev_bk_file.eof() && prev_bk_file.tellg()< end_point){
		prev_issue bk;
		prev_bk_file.read((char *)&bk,sizeof(bk));
		if(strcmp(bk.std.name,stud_nm)){
			pos = prev_bk_file.tellg() - sizeof(bk);
			break;
		}
	}
	Search::prev_bk_file.close();
	return pos;
}
#endif
