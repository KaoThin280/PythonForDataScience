#include <math.h>
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <vector>
using namespace std;

//cau truc thoi gian cho viec quan ly
struct timeSlot{
	int day; //ngay thu may
	int from; //gio bat dau
	int to; //gio ket thuc
} aTime;

//swap 2 khoang thoi gian
void swapTime(timeSlot &ts1, timeSlot &ts2){
	timeSlot temp = ts1;
	ts1 = ts2;
	ts2 = temp;
}

//sap xep thu tu thoi gian
void sortTimeSlot(vector<timeSlot> &ts){
	timeSlot temp;
	for (int i =0; i<ts.size();i++){
		for (int j =0; j<ts.size()-1;j++){
			if (ts.at(i).day > ts.at(j).day) {
				swapTime(ts.at(i), ts.at(j));
			}
			if (ts.at(i).day == ts.at(j).day){
				if (ts.at(i).from > ts.at(j).from) {
					swapTime(ts.at(i), ts.at(j));
				}
			}
		}
	}
}
//hien thi thoi gian
void showTimeSlot(timeSlot ts){
	cout<<"ngay thu: "<<ts.day<<"\t";
	cout<<"tu luc: "<<ts.from<<"\t";
	cout<<"ket thuc luc: "<<ts.to<<endl;
}

//kiem tra phu hop thoi gian de thanh vien co the tham gia hoi dong
// ts1: thoi gian du kien to chuc, ts2: thoi gian san co cua thanh vien
bool isFitTime(timeSlot ts1, timeSlot ts2){
	if (ts1.day != ts2.day) return false;
	return ts1.from >= ts2.from and ts1.to <= ts2.to;
}

//kiem tra xung dot thoi gian to chuc
bool isTimeConflicted(timeSlot ts1, timeSlot ts2){
	if (ts1.day != ts2.day) return false; //truong hop 1 (TH1): khac ngay
	if (ts1.to > ts2.from) return true; //TH2: chua ket thuc hoi dong 1 ma da bat dau hoi dong 2
	//if (ts1.from < ts2.to) return true;	//TH3: chua 
	if (ts1.from == ts2.from and ts1.to == ts2.to) return true;
}

//cau truc 1 thanh vien: ten, hoc ham, hoc vi, cac khoang thoi gian co san
struct Member {
    string name;
    string academicRank;
    string degree;
    vector<timeSlot> availableSlots;
} aMember;

//them thoi gian co san cho thanh vien
void addTimeSlot(Member & mem, timeSlot ts){
	mem.availableSlots.push_back(ts);
}
//sap xep thoi gian san co cua thanh vien
void sortAvailableSlots(Member mem){
	sortTimeSlot(mem.availableSlots);
}

//hien thi thong tin cua 1 thanh vien
void showMemberInfor(Member mem){
	cout<<"Ten: "<<mem.name<<endl;
	cout<<"Hoc ham: "<<mem.academicRank<<endl;
	cout<<"Hoc vi: "<<mem.degree<<endl;
	cout<<"Thoi gian co san:\n";
	for (int i=0; i< mem.availableSlots.size();i++) {
		//cout<<mem.availableSlots.size()<<endl;
    	cout<<"\t"; showTimeSlot(mem.availableSlots.at(i));
  	}
  	cout<<"------------------------------------------------------------------------------------\n";
}

//cau truc 1 hoi dong: ten khoa, danh sach thanh vien, thoi gian du kien
struct ThesisDefenseBoard {
    string departmentName;
    vector<Member> members;
    vector<timeSlot> scheduledTime;
} aTDB;

//sap xep lich to chuc cua 1 hoi dong
void sortTDBtime(ThesisDefenseBoard TDB){
	sortTimeSlot(TDB.scheduledTime);
}

//them 1 thanh vien vao hoi dong
bool addMember(ThesisDefenseBoard & TDB, Member mem){
	//neu thanh vien co thoi gian thich hop thi se duoc them vao (true)
	for (int i = 0;i<TDB.scheduledTime.size(); i++){
		for (int j = 0;j<mem.availableSlots.size(); j++){
			if(isFitTime(TDB.scheduledTime.at(i), mem.availableSlots.at(j))==true){
				TDB.members.push_back(mem);
				return true;
			}
		}	
	}
	return false; //thanh vien khong co khung gio thich hop
}

//xoa 1 thanh vien hoi dong o vi tri i
bool removeMemberAtIndex(ThesisDefenseBoard & TDB, int i){
	if (TDB.members.size() == 0) return false; //khong co ai trong danh sach thanh vien
	TDB.members.at(i) = TDB.members.at(TDB.members.size()-1);
	TDB.members.pop_back();
	return true;
}

//hien thi thong tin hoi dong
void showTDB(ThesisDefenseBoard TDB){
	cout<<"Khoa: "<< TDB.departmentName<<"************************************************************"<<endl;
	cout<<"Thoi gian du kien: " << endl;
	for (int i = 0;i<TDB.scheduledTime.size(); i++){
		cout<<"\t";
		showTimeSlot(TDB.scheduledTime.at(i));
	}
	cout<<"Danh sach thanh vien:"<<endl;
	cout<<"----------------------------------------------\n";
	for (int j = 0;j<TDB.members.size(); j++){
		showMemberInfor(TDB.members.at(j));
	}
}

//kiem tra hoi dong cua 1 khoa co the duoc to chuc dua tren tung khoang thoi gian du kien hay khong
bool canBeHold(ThesisDefenseBoard TDB){
	int count;
	if (TDB.members.size() < 3) {
		//cout<<"Hien chua du so luong thanh vien toi thieu!"<<endl;
		return false;
	}
	//kiem tra moi khoang thoi gian to chuc co du 3 thanh vien khong
	for (int day =0; day< TDB.scheduledTime.size(); day++){
		count = 0;
		for(int i = 0; i< TDB.members.size();i++){
			for(int j = 0; j<TDB.members.at(i).availableSlots.size();j++){
				if(isFitTime(TDB.scheduledTime.at(day),TDB.members.at(i).availableSlots.at(j)) == true) count++; 
			}
		}
		if(count < 3) return false;
	}
	return true;
}

//kiem tra xung dot lich cua 1 hoi dong
bool isSelfConflicted(ThesisDefenseBoard TDB){
	for(int i=0; i< TDB.scheduledTime.size();i++){
		for(int j=i+1; j< TDB.scheduledTime.size();j++){
			if(isTimeConflicted(TDB.scheduledTime.at(i), TDB.scheduledTime.at(j))) return true;
		}
	}
	return false;
}
//kiem tra trung lich giua 2 hoi dong
bool isTDBconflicted(ThesisDefenseBoard TDB1, ThesisDefenseBoard TDB2) {
	bool flag = false;
	//so sanh tung ngay to chuc cua 2 hoi dong
	for (int i = 0; i< TDB1.scheduledTime.size(); i++){
		for (int j = 0; j< TDB2.scheduledTime.size(); j++){
			//phat hien xung dot va dua ra thoi gian xung dot
			if (isTimeConflicted(TDB1.scheduledTime.at(i), TDB2.scheduledTime.at(j)) == true){
				flag = true;
				/*
				cout<<"xung dot lich:\n";
				cout<<TDB1.departmentName; showTimeSlot(TDB1.scheduledTime.at(i));
				cout<<TDB2.departmentName; showTimeSlot(TDB2.scheduledTime.at(j));
				*/
			}
		}
	}
	return flag;
}

//swap 2 hoi dong
void swapTDB(ThesisDefenseBoard TDB1, ThesisDefenseBoard TDB2){
	ThesisDefenseBoard temp = TDB1;
	TDB1 = TDB2;
	TDB2 = temp;
}

//sap xep danh sach hoi dong
void sortSchedule(vector<ThesisDefenseBoard> & schedule){
	for (int i=0; i< schedule.size(); i++){
		for (int j=0; j<schedule.size(); j++){
			if(schedule.at(i).scheduledTime.at(0).day > schedule.at(j).scheduledTime.at(0).day) {
				swapTDB(schedule.at(i),schedule.at(j));
			}
			if (schedule.at(i).scheduledTime.at(0).day == schedule.at(j).scheduledTime.at(0).day){
				if (schedule.at(i).scheduledTime.at(0).from > schedule.at(j).scheduledTime.at(0).from){
					swapTDB(schedule.at(i),schedule.at(j));
				}
			}
		}
	}
}

//xep lich to chuc cac hoi dong
void autoSchedule(vector<ThesisDefenseBoard> & schedule) {
	sortSchedule(schedule);
	for(int i=0; i<schedule.size();i++){
		//kiem tra xung dot thoi gian cua 1 hoi dong
		if(isSelfConflicted(schedule.at(i))){
			cout<<"Co 1 hoi dong xung dot thoi gian!";
			return;
		}
		//kiem tra so luong thanh vien tung hoi dong
		if(canBeHold(schedule.at(i)) == false){
			cout<<"Co 1 hoi dong khong du thanh vien!\n";
			return;
		}
		for(int j=i+1; j< schedule.size(); j++){
			//kiem tra xung dot giua cac hoi dong
			if(isTDBconflicted(schedule.at(i), schedule.at(j)) == true){
				cout<<"Co xung dot giua 2 hoi dong!\n";
				return;
			}
		}
	}
	cout<<"Sap xep thanh cong.\n";
	for(int i=0; i<schedule.size();i++){
		showTDB(schedule.at(i));
	}
}

//tim mot hoi dong trong lich thong qua ten khoa
//tra ve vi tri cua hoi dong trong lich
int searchTDBbyName(vector<ThesisDefenseBoard> & schedule, string departmentName) {
	for (int i=0; i< schedule.size(); i++){
		if(schedule.at(i).departmentName == departmentName){
			//showTDB(schedule.at(i));
			return i;
		}
	}
	return -1;
}

//tim 1 thanh vien co trong khoa
bool findMemberInTDB(ThesisDefenseBoard TDB, string memberName){
	for(int i =0; i< TDB.members.size(); i++){
		if(TDB.members.at(i).name.find(memberName) != std::string::npos) return true;
	}
	return false;
}

//tim cac hoi dong ma thanh vien tham gia
void searchTDBofMember(vector<ThesisDefenseBoard> & schedule, string departmentName, string memberName) {
	int i = searchTDBbyName(schedule, departmentName);
	//kiem tra hoi dong co trong lich trinh khong
	if (i == -1) {
		cout<<"Hoi dong khoa chua duoc them vao lich!\n";
		return;
	}
	//kiem tra thanh vien co tham gia vao hoi dong do khong
	if(findMemberInTDB(schedule.at(i), memberName) == true){
		showTDB(schedule.at(i));
		return;
	}
	cout<<memberName<<" hien khong tham gia vao hoi dong khoa "<<departmentName<<endl;
	return;
}

int main(){
/*	
note:
	Moi hoi dong khoa chi duoc chu tri boi cac thanh vien thuoc khoa do;
	Moi thanh vien chi co the duoc them vao hoi dong neu phu hop thoi gian;
*/	
//khoi tao danh sach cac khoa
string danhSachKhoa [7] = {"Khoa CNTT", "Khoa Luat", "Khoa Moi Truong", "Khoa Nghe Thuat", "Khoa Ngoai Ngu", "Khoa QTKD", "Khoa TV-VP"};
	
//khoi tao cac ngay to chuc hoi dong
	int days[5] = {2, 3, 4, 5, 6};
	
//khoi tao danh sach ten thanh vien
string memberFirstName[15]  = {"Kao Thin","Luon Cong Minh","Quan WhaLe","Luong Quoc Va","No Xay","Thanh Huang","Phuong","Bao","Hoa","Sang","Huy","Tai","TM Man","Gud Guy","Bad Guy"};
string memberLastName[6] = {" Nguyen", " Tran", " Phan", " Pham", " Luu", " Le"};

//khoi tao danh sach hoc ham
string academicRank[2] = {"Professor", "Associate Professor"};

//khoi tao danh sach hoc vi
string degree[4] = {"B.A", "engineer","Master", "Doctor"};

//khoi tao danh sach thanh vien
	vector<Member> ITmemberList;
	vector<Member> LAWmemberList;
	vector<Member> ENVIRONMENTALmemberList;
	vector<Member> ARTmemberList;
	vector<Member> LANGUAGEmemberList;
	vector<Member> BAmemberList;
	vector<Member> LOmemberList;
	//vector<vector<Member> > memberList;
	
//khoi tao ngau nhien thong tin thanh vien
/*
	aMember.name = memberFirstName[rand()%15];
	aMember.academicRank = academicRank[rand()%2];
	aMember.degree = degree[rand()%4];
*/
//khoi tao ngau nhien khoang thoi gian
/*
	aTime.day = days[rand()%5];
	aTime.from = rand()% 16 + 8;
	int from = aTime.from;
	aTime.to = (rand()% 16 + from) -from;
	
	addTimeSlot(aMember, aTime);
	//showMemberInfor(aMember);
*/
//test case:
	vector<timeSlot> TDBtime;
	vector<timeSlot> memberTime;
	aTime.day = 2; aTime.from = 8; aTime.to = 11; //thoi gian hoi dong 1
	TDBtime.push_back(aTime);
//case 1, 3, 4, 5
	aTime.day = 3; aTime.from = 9; aTime.to = 12; //thoi gian hoi dong 2

//case2
//	aTime.day = 2; aTime.from = 9; aTime.to = 12;
	
	TDBtime.push_back(aTime);
	aTime.day = 4; aTime.from = 12; aTime.to = 15; //thoi gian hoi dong 3
	TDBtime.push_back(aTime);
	aTime.day = 2; aTime.from = 8; aTime.to = 13; // thoi gian co san cua thanh vien 1 IT
	memberTime.push_back(aTime);
	aTime.day = 2; aTime.from = 8; aTime.to = 11; // thoi gian co san cua thanh vien 2 IT
	memberTime.push_back(aTime);
	aTime.day = 2; aTime.from = 8; aTime.to = 15; // thoi gian co san cua thanh vien 3 IT
	memberTime.push_back(aTime);
	
//case 1,3, 4, 5

	aTime.day = 3; aTime.from = 8; aTime.to = 13; // thoi gian co san cua thanh vien 4 LAW
	memberTime.push_back(aTime);
	aTime.day = 3; aTime.from = 8; aTime.to = 14; // thoi gian co san cua thanh vien 5 LAW
	memberTime.push_back(aTime);
	aTime.day = 3; aTime.from = 8; aTime.to = 12; // thoi gian co san cua thanh vien 6 LAW
	memberTime.push_back(aTime);


//case2
/*
	aTime.day = 2; aTime.from = 8; aTime.to = 13; // thoi gian co san cua thanh vien 4 LAW
	memberTime.push_back(aTime);
	aTime.day = 2; aTime.from = 8; aTime.to = 14; // thoi gian co san cua thanh vien 5 LAW
	memberTime.push_back(aTime);
	aTime.day = 2; aTime.from = 8; aTime.to = 12; // thoi gian co san cua thanh vien 6 LAW
	memberTime.push_back(aTime);
*/

//case 3:
/*
	aTime.day = 3; aTime.from = 8; aTime.to = 13; // thoi gian co san cua thanh vien 4 LAW
	memberTime.push_back(aTime);
	aTime.day = 3; aTime.from = 8; aTime.to = 14; // thoi gian co san cua thanh vien 5 LAW
	memberTime.push_back(aTime);
	aTime.day = 4; aTime.from = 8; aTime.to = 12; // thoi gian co san cua thanh vien 6 LAW
	memberTime.push_back(aTime);
*/

	aTime.day = 4; aTime.from = 11; aTime.to = 16; // thoi gian co san cua thanh vien 7 ENV
	memberTime.push_back(aTime);
	aTime.day = 4; aTime.from = 10; aTime.to = 15; // thoi gian co san cua thanh vien 8 ENV
	memberTime.push_back(aTime);
	aTime.day = 4; aTime.from = 8; aTime.to = 17; // thoi gian co san cua thanh vien 9 ENV
	memberTime.push_back(aTime);

//khoi tao 3 thanh vien khoa CNTT
	for (int i=0; i<3; i++){
		aMember.name = (memberFirstName[rand()% +15]) + (memberLastName[rand()% +6]);
		aMember.academicRank = academicRank[rand()% +2];
		aMember.degree = degree[rand()% + 4];
		aMember.availableSlots.push_back(memberTime.at(i));
		ITmemberList.push_back(aMember);
		aMember.availableSlots.pop_back();
	}
//khoi tao 3 thanh vien khoa Luat
	for (int i=0; i<3; i++){
		aMember.name = (memberFirstName[rand()% +15]) + (memberLastName[rand()% +6]);
		aMember.academicRank = academicRank[rand()% +2];
		aMember.degree = degree[rand()% + 4];
		aMember.availableSlots.push_back(memberTime.at(i+3));
		LAWmemberList.push_back(aMember);
		aMember.availableSlots.pop_back();
	}

//case 4
/*
		timeSlot extraTS;
		extraTS.day = 5; extraTS.from = 8; extraTS.to = 11;
		//khoi tao 3thanh vien cho ngay thu 2
		vector<Member> extraMember;
		for(int i =0; i<3; i++){
			aMember.name = (memberFirstName[rand()% +15]) + (memberLastName[rand()% +6]);
			aMember.academicRank = academicRank[rand()% +2];
			aMember.availableSlots.push_back(extraTS);
			LAWmemberList.push_back(aMember);
			aMember.availableSlots.pop_back();
		}
*/		
		
//case 5
		timeSlot extraTS;
		extraTS.day = 5; extraTS.from = 8; extraTS.to = 11;
		//khoi tao 3 thanh vien cho ngay thu 2
		vector<Member> extraMember;
		for(int i =0; i<2; i++){
			aMember.name = (memberFirstName[rand()% +15]) + (memberLastName[rand()% +6]);
			aMember.academicRank = academicRank[rand()% +2];
			aMember.availableSlots.push_back(extraTS);
			LAWmemberList.push_back(aMember);
			aMember.availableSlots.pop_back();
		}
		LAWmemberList.at(1).availableSlots.push_back(extraTS);
		

//khoi tao 3 thanh vien khoa Moi truong
	for (int i=0; i<3; i++){
		aMember.name = (memberFirstName[rand()% +15]) + (memberLastName[rand()% +6]);
		aMember.academicRank = academicRank[rand()% +2];
		aMember.degree = degree[rand()% + 4];
		aMember.availableSlots.push_back(memberTime.at(i+6));
		ENVIRONMENTALmemberList.push_back(aMember);
		aMember.availableSlots.pop_back();
	}
	
	
	
//khoi tao danh sach cac hoi dong
	vector<ThesisDefenseBoard> schedule;
	
//khoi tao hoi dong khoa CNTT
	aTDB.departmentName = danhSachKhoa[0];
	aTDB.members = ITmemberList;
	aTDB.scheduledTime.push_back(TDBtime.at(0));
	schedule.push_back(aTDB);
	aTDB.scheduledTime.pop_back();
	
//khoi tao hoi dong khoa Luat
	aTDB.departmentName = danhSachKhoa[1];
	aTDB.members = LAWmemberList;
	aTDB.scheduledTime.push_back(TDBtime.at(1));
	schedule.push_back(aTDB); schedule.at(1).scheduledTime.push_back(extraTS); //case 4, 5
	aTDB.scheduledTime.pop_back();
//khoi tao hoi dong khoa Moi truong
	aTDB.departmentName = danhSachKhoa[2];
	aTDB.members = ENVIRONMENTALmemberList;
	aTDB.scheduledTime.push_back(TDBtime.at(2));
	schedule.push_back(aTDB);
	aTDB.scheduledTime.pop_back();
	
//hien thi:
	//autoSchedule(schedule);
return 0;
}
/*
note: o cac test case se chi su dung it hon 7 hoi dong duoc de ra nham muc dich rut gon code nhung van co the tong quat duoc cac truong hop;
	 viec them thanh vien vao 1 hoi dong co the thong qua ham addMember() de dam bao thanh vien do co the tham du hoi dong.
cac test case:
	1. perfect (cac hoi dong co day du thanh vien, khong co xung dot thoi gian nen chi can sap xep)
	
	2. moi hoi dong dien ra trong 1 khoang thoi gian va co xung dot giua cac hoi dong
	
	3. moi hoi dong dien ra trong 1 khoang thoi gian va co hoi dong khong co du thanh vien chu tri
	
	4. moi hoi dong co the dien ra trong 2 khoang thoi gian
	
	5. moi hoi dong co the dien ra trong 2 khoang thoi gian, moi thanh vien co the co 2 thoi gian co san
*/
