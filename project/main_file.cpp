#include<iostream>
#include"all_bk_cls.cpp"
#include"iss_bk_cls.cpp"
#include"prev_bk_cls.cpp"
using namespace std;
int main(){
	AllBook allbk;
	IssueBook issbk;
	PrevBook prevbk;
	
	strt_menu:
		int *choice;
		choice = new int;
		do{
			cout << "+++++++++++++++++++++++Library Managemant+++++++++++++++++++++++++\n";
			cout << "1. Admin Mode\n";
			cout << "2. User Mode\n";
			cout << "0. Exit\n";
			cout << "enter Your Choice: ";
			cin >> *choice;
			cin.ignore();
		}while(*choice<0 || *choice>2);
		switch(*choice){
			case 0:
				return 0;
				break;
			case 1:
				admin_menu:
					delete choice;
					choice = new int;
					do{
						cout << "+++++++++++++++++++++++Admin Mode+++++++++++++++++++++++++\n";
						cout << "1. Show All Books\n";
						cout << "2. Show Issue Books\n";
						cout << "3. Show Previous Issue Book\n";
						cout << "4. Add new Book\n";
						cout << "5. Issue new Book\n";
						cout << "6. Remove Book\n";
						cout << "7. Remove issue Book\n";
						cout << "8. Search issue Book\n";
						cout << "9. Search Book\n";
						cout << "0. Go Back\n";
						cout << "Enter your choice: ";
						cin >> *choice;
						cin.ignore();
					}while(*choice<0 || *choice>9);
				
					switch(*choice){
						case 0:
							goto strt_menu;
							break;
						case 1:
							cout << "+++++++++++++++++++++++All Books++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n";
							allbk.show_all_book();
							goto admin_menu;
							break;
						case 2:
							cout << "+++++++++++++++++++++++Issue Books++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n";
							issbk.show_iss_book();
							goto admin_menu;
							break;
						case 3:
							cout << "+++++++++++++++++++++++Show previous issue book+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n";
							prevbk.prev_book_show();
							goto admin_menu;
							break;
						case 4:
							cout << "+++++++++++++++++++++++Add new book+++++++++++++++++++++++++\n";
							allbk.add_book();
							goto admin_menu;
							break;
						case 5:
							cout << "+++++++++++++++++++++++Issue New Book+++++++++++++++++++++++++\n";
							issbk.add_iss_book();
							goto admin_menu;
							break;
						case 6:
							cout << "+++++++++++++++++++++++Remove Book+++++++++++++++++++++++++\n";
							allbk.remv_book();
							goto admin_menu;
							break;
						case 7:
							cout << "+++++++++++++++++++++++Remove Issue Book+++++++++++++++++++++++++\n";
							issbk.remove_iss_bk();
							goto admin_menu;
							break;
						case 8:
							cout << "+++++++++++++++++++++++Search Issue Book+++++++++++++++++++++++++\n";
							issbk.search_iss_bk();
							goto admin_menu;
							break;
						case 9:
							cout << "+++++++++++++++++++++++Searching Book+++++++++++++++++++++++++\n";
							allbk.search_book();
							goto admin_menu;
							break;
						default:
							goto admin_menu;
							cout << "Invalid input\n";
							break;
					}
			
					break;
			case 2:
				delete choice;
				choice - new int;
				do{
					cout << "+++++++++++++++++++++++User Mode+++++++++++++++++++++++++\n";
					cout << "1. Show Books\n";
					cout << "Enter your choice: ";
					cin >> *choice;
					cin.ignore();
				}while(*choice<1 || *choice >2);
				switch(*choice){
					case 1:
						cout << "+++++++++++++++++++++++All Books+++++++++++++++++++++++++\n";
						allbk.show_all_book();
						goto strt_menu;
						break;
					default:
						goto strt_menu;
						break;
				}
				break;
				default:
					goto strt_menu;
					break;
		}
}
	
