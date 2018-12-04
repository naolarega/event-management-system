#include<iostream>        // basic input output header file
#include<windows.h>       // win32/64 api
#include<string>          // prototypes string functions
#include<fstream>         // header file  for file manipulation
#include<ctime>           // header file for time related function

using namespace std;

int Loop,choice;          // variables used for common loops and decision making
ofstream wfile;
int check_;

struct date{              // the structure for the linked list
    int Day;
    int Month;
    int Year;
    string EventTitle;
    string category;
    string location;
    string note;
    date *next;
}*head=NULL;
date *check=head;

void Load(){                         //this function loads from a file to linked list
    string check;
    ifstream rfile;
    rfile.open("date");
    rfile>>check;
    rfile.close();
    rfile.open("date");
    if(check.length()==0){
        rfile.close();
    }
    else{
        while(!rfile.eof()){
            date *newDate=new date;
            rfile>>newDate->EventTitle;
            rfile>>newDate->Day;
            rfile>>newDate->Month;
            rfile>>newDate->Year;
            rfile>>newDate->category;
            rfile>>newDate->location;
            rfile>>newDate->note;
            if(head==NULL){
                head=newDate;
                newDate->next=NULL;
            }
            else{
                newDate->next=head;
                head=newDate;
            }
        }
        rfile.close();
    }
}

date *save(date *temp=head){                    //this function saves events to a file using recursion
    if(head==NULL){                               //it has a date return type and *temp as parameter
        wfile.close();
        return 0;
    }
    else{
        if(temp->next==NULL&&temp!=head){
            wfile<<endl<<temp->EventTitle<<endl
                 <<temp->Day<<endl
                 <<temp->Month<<endl
                 <<temp->Year<<endl
                 <<temp->category<<endl
                 <<temp->location<<endl
                 <<temp->note;
            wfile.close();
            return 0;
        }
        else if(temp==head&&temp->next==NULL){
            wfile<<temp->EventTitle<<endl
                 <<temp->Day<<endl
                 <<temp->Month<<endl
                 <<temp->Year<<endl
                 <<temp->category<<endl
                 <<temp->location<<endl
                 <<temp->note;
            wfile.close();
            return 0;
        }
        else if(temp==head&&temp->next!=NULL){
            wfile<<temp->EventTitle<<endl
                 <<temp->Day<<endl
                 <<temp->Month<<endl
                 <<temp->Year<<endl
                 <<temp->category<<endl
                 <<temp->location<<endl
                 <<temp->note;
            return save(temp=temp->next);
        }
        else{
            wfile<<endl<<temp->EventTitle<<endl
                 <<temp->Day<<endl
                 <<temp->Month<<endl
                 <<temp->Year<<endl
                 <<temp->category<<endl
                 <<temp->location<<endl
                 <<temp->note;
            return save(temp=temp->next);
        }
    }
}

void CreateEvent(int _day,                       //this function creates a new event it has _day _month _year integer data type
                 int _month,                     //and _eventitle _category _location and _note string data type parameters
                 int _year,
                 string _eventitle,
                 string _category,
                 string _location,
                 string _note){
    date *newDate=new date;
    newDate->Day=_day;
    newDate->Month=_month;
    newDate->Year=_year;
    newDate->EventTitle=_eventitle;
    newDate->category=_category;
    newDate->location=_location;
    newDate->note=_note;
    if(head==NULL){
        newDate->next=NULL;
        head=newDate;
    }
    else{
        newDate->next=head;
        head=newDate;
    }
}

void searchEvent(string eventSearch){                // this function is return typeless function used to search an event
    if(head==NULL){                                   // with eventsearch parameter
        cout<<"\n        no event!!!"<<endl;
    }
    else{
        date *temp=head;
        while(temp->next!=NULL&&temp->EventTitle!=eventSearch){
            temp=temp->next;
        }
        if(temp->next==NULL&&temp->EventTitle!=eventSearch){
            cout<<" event not found"<<endl;
        }
        else{
            cout<<"event title: "<<temp->EventTitle<<endl;
            cout<<"       date: "<<temp->Day<<"/"<<temp->Month<<"/"<<temp->Year<<endl;
            cout<<"   category: "<<temp->category<<endl;
            cout<<"   location: "<<temp->location<<endl;
            cout<<"       note: "<<temp->note<<endl;
        }
    }
}

void TextColor(int clr,int bol,string str){          // this function used to change the color of the text
    HANDLE  hConsole;                                 // and its background
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int col=clr;
    FlushConsoleInputBuffer(hConsole);
    SetConsoleTextAttribute(hConsole, col);
    if(bol==1)
        cout << str <<endl;
    if(bol==0)
        cout<< str;
    SetConsoleTextAttribute(hConsole, 15);
}

void option_(){                                        // this function is a used in options to return to main menu
        TextColor(2,1,"1 back to top");                 // or the the previous menu
        TextColor(2,1,"2 main menu");
        cin>>choice;
        if(choice==1)
            Loop=0;
        else if(choice==2){
            Loop=1;        }
        else{
            system("cls");
            cout<<"invalid key"<<endl;
            system("pause");
        }
}

void editEvent(string searchEvent,
               int day_,
               int month_,
               int year_,
               string event_,
               string category_,
               string location_,
               string note_){                                //  this function edits events
    if(head==NULL){
        cout<<"\n        no event!!!"<<endl;
    }
    else{
        date *temp=head;
        while(temp->next!=NULL&&temp->EventTitle!=searchEvent){
            temp=temp->next;
        }
        if(temp->next==NULL&&temp->EventTitle!=searchEvent){
            cout<<"\n the event you are trying to edit does not exist"<<endl;;
        }
        else{
            temp->EventTitle=event_;
            temp->Day=day_;
            temp->Month=month_;
            temp->Year=year_;
            temp->category=category_;
            temp->location=location_;
            temp->note=note_;
        }
    }
}

string deleteEvent(string eventDelete){                                // this function deletes existing event
    if(head==NULL){
        return "\n        no event!!!";
    }
    else{
        date *temp=head;
        date *temp2;
        if(temp->next==NULL&&temp->EventTitle==eventDelete){
            head=NULL;
            delete temp;
            return " deleted";
        }
        else{
            while(temp->next!=NULL&&temp->EventTitle!=eventDelete){
                temp2=temp;
                temp=temp->next;
            }
            if(temp->next==NULL&&temp->EventTitle!=eventDelete){
                return " event does not exist";
            }
            else if(temp==head&&temp->EventTitle==eventDelete){
                head=temp->next;
                delete temp;
                return " deleted";
            }
            else if(temp->next==NULL&&temp->EventTitle==eventDelete){
                temp2->next=NULL;
                delete temp;
                return " deleted";
            }
            else{
                temp2->next=temp->next;
                delete temp;
                return " deleted";
            }
        }
    }
}

void viewAll(){
    if(head==NULL){
        cout<<"\n        no event!!!"<<endl;
    }
    else{
        date *temp=head;
        while(temp->next!=NULL){
            cout<<"------------------------"<<endl;
            cout<<"event name: "<<temp->EventTitle<<endl;
            cout<<"      date: "<<temp->Day<<"/"<<temp->Month<<"/"<<temp->Year<<endl;
            cout<<"  category: "<<temp->category<<endl;
            cout<<"  location: "<<temp->location<<endl;
            cout<<"      note: "<<temp->note<<endl;
            temp=temp->next;
        }
            cout<<"------------------------"<<endl;
            cout<<"event name: "<<temp->EventTitle<<endl;
            cout<<"      date: "<<temp->Day<<"/"<<temp->Month<<"/"<<temp->Year<<endl;
            cout<<"  category: "<<temp->category<<endl;
            cout<<"  location: "<<temp->location<<endl;
            cout<<"      note: "<<temp->note<<endl;
    }
}

void viewCalender(){                                // this function display the days of the month
    int c=3;
    for(Loop=0;Loop==0;){                            //which the system shows
        int dflt=6;int dyb=dflt;int stck[42];int d=1;
        int m,n;
        int ly=4;
        system("cls");
        cout<<endl<<endl;
        TextColor(5,1,"================================================================================");
        TextColor(14,1,"                               ::: calender :::");
        TextColor(5,1,"--------------------------------------------------------------------------------");
        if(c==3){
        cout<<"enter year: ";
        cin>>n;
        cout<<"enter month: ";
        cin>>m;}
        else if(c==1){
            m++;
            if(m>13){
                m=1;
                n++;
            }
        }
        else if(c==2){
            m--;
            if(m<1){
                m=13;
                n--;
            }
        }
        if(m==1){cout<<"                             meskerem  "<<n<<endl;}
        else if(m==2){cout<<"                             tikimt  "<<n<<endl;}
        else if(m==3){cout<<"                             hidar  "<<n<<endl;}
        else if(m==4){cout<<"                             tahsas  "<<n<<endl;}
        else if(m==5){cout<<"                             tir  "<<n<<endl;}
        else if(m==6){cout<<"                             yekatit  "<<n<<endl;}
        else if(m==7){cout<<"                             megabit  "<<n<<endl;}
        else if(m==8){cout<<"                             miazia  "<<n<<endl;}
        else if(m==9){cout<<"                             ginbot  "<<n<<endl;}
        else if(m==10){cout<<"                            sene  "<<n<<endl;}
        else if(m==11){cout<<"                            hamle  "<<n<<endl;}
        else if(m==12){cout<<"                            nehase  "<<n<<endl;}
        else if(m==13){cout<<"                            puagume  "<<n<<endl;}
        TextColor(10,1,"\n   mon  |   tue  |   wed  |  thur  |   fri  |   sat  |   sun  |");
                 cout<<"------------------------------------------------------------"<<endl;
                 for(int yr=1903;yr<=2030;yr++){
                    for(int mnth=1;mnth<=13;){
                        if(mnth==m&&yr==n){
                            int v=0;
                            while(v<42){
                                if(mnth<13){
                                    if(v<dyb||v>dyb+29){
                                        stck[v]=NULL;
                                    }
                                    else{
                                        stck[v]=d;
                                        d++;
                                    }
                                    v++;
                                }
                                else if(mnth==13){
                                    if(ly!=4&&(v<dyb||v>dyb+4)){
                                        stck[v]=NULL;
                                    }
                                    else if(ly==4&&(v<dyb||v>dyb+5)){
                                        stck[v]=NULL;
                                    }
                                    else{
                                        stck[v]=d;
                                        d++;
                                    }
                                    v++;
                                }
                            }
                            break;
                        }
                        else{
                            if(mnth==13){
                                if(ly==4){
                                    dyb--;
                                    ly=0;
                                }
                                else if(ly!=4){
                                    dyb=dyb-2;
                                }
                                else{
                                    dyb++;
                                }
                            }
                            else{
                                dyb+=2;
                            }
                            mnth++;
                            if(dyb>6){
                                dyb=dyb-7;
                            }
                        }
                    }
                    ly++;
                 }
                 for(int g=0;g<42;g++){
                    if(g==6||g==13||g==20||g==27||g==34||g==41){
                        if(stck[g]==0){
                            cout<<"        |"<<endl;
                        }
                        else{
                            if(stck[g]<10&&stck[g]!=0){
                                cout<<"    "<<stck[g]<<"   |"<<endl;
                            }
                            else{
                                cout<<"    "<<stck[g]<<"  |"<<endl;
                            }
                        }
                        cout<<"_______________________________________________________________"<<endl;
                    }
                    else{
                        if(stck[g]==0){
                            cout<<"        |";
                        }
                        else{
                            if(stck[g]<10&&stck[g]!=0){
                                cout<<"    "<<stck[g]<<"   |";
                            }
                            else{
                                cout<<"    "<<stck[g]<<"  |";
                            }
                        }
                    }
                 }
           cout<<endl<<"------------------------------------------------------------"<<endl;
           cout<<"  '1' next    '2' previous   '3' goto  '4' main menu"<<endl;
           cin>>c;
           if(c==4){Loop=1;}
        }
    Loop=0;
}

void easterEgg(){                                // this function is written us an entertainment
    int r;
    system("cls");
    srand(time(0));
    r=rand()%6;
    if(r==0){
        cout<<"     in english, the days of the week are named after"<<endl
            <<"      the saxon gods(monday->moon tuesday->tiw wednesday->woden"<<endl
            <<"        thursday->thor etc)"<<endl;
    }
    else if(r==1)
        cout<<"       the oldest calender is 30000 years old. an engraved "<<endl
            <<"          bone plaque found at blanchard"<<endl;
    else if(r==2)
        cout<<"      ethiopian calender is the only calender with 13 month"<<endl
            <<"       with 5 days and 6 days every 4 years"<<endl;
    else if(r==3)
        TextColor(11,1,"calender management system");
    else if(r==4)
        TextColor(11,1,"event management system");
    else if(r==5)
        TextColor(11,1,"event(calender) management system");
    else if(r==6)
        TextColor(11,1,"hello world");
    system("pause");
}

void welcomeWindow(){                               //welcome window function
    TextColor(13,1,"\n\n\n\n                          welcome to event management\n                                     system\n");
          _sleep(2000);
                TextColor(6,1,"                                     Loading\n");
          _sleep(1000);
          cout<<"            ";
    for(int y=52;y>0;y--){
        if(y>1){
          TextColor(7+10*16,0," ");
            _sleep(50);
            }
        else{
          TextColor(7+10*16,1," ");
          TextColor(11,0,"\n\n                                      done                           ");
        }
    }
    _sleep(2000);
}

void event(){                                  // this function calls createevent viewevent
    int d=01,m=01,y=1900,k=0;                  // searchevent editevent and deleteevent functions
    string evt="note_specified",ct="note_specified",lc="note_specified",nt="note_specified",fl;
    for(Loop=0;Loop==0;){
        system("cls");
        cout<<endl<<endl;
        TextColor(5,1,"================================================================================");
        TextColor(14,1,"                               ::: events :::");
        TextColor(5,1,"--------------------------------------------------------------------------------");
        TextColor(7,0,"         1,");TextColor(11,1,"  add event");
        TextColor(7,0,"         2,");TextColor(11,1,"view all events");
        TextColor(7,0,"         3,");TextColor(11,1," search event");
        TextColor(7,0,"         4,");TextColor(11,1,"  edit event");
        TextColor(7,0,"         5,");TextColor(11,1," delete event");
        TextColor(7,0,"         6,");TextColor(13,1,"    back");
        cout<<endl<<">> ";
        cin>>choice;
        switch(choice){
            case 1:{
                system("cls");
                cout<<endl<<endl;
                TextColor(5,1,"================================================================================");
                TextColor(14,1,"                               ::: events :::");
                TextColor(5,1,"--------------------------------------------------------------------------------");
                        cout<<"                                 create event"<<endl
                            <<"                        ------------------------------"<<endl;
                cout<<endl<<"   enter the day: ";
                cin>>d;
                      cout<<"   month: ";
                cin>>m;
                      cout<<"   year: ";
                cin>>y;
                      cout<<"   event title: ";
                cin>>evt;
                for(check_=1;check_==1;){
                    if(head==NULL){
                        check_=0;
                    }
                    else{
                        check=head;
                        while(check->next!=NULL&&check->EventTitle!=evt){
                            check=check->next;
                        }
                        if(check->EventTitle==evt){
                            cout<<endl<<"   event with the same title exists!!! enter again: ";
                            cin>>evt;
                        }
                        else{
                            check_=0;
                        }
                    }
                }
                      cout<<"   category of the event: ";
                cin>>ct;
                      cout<<"   location: ";
                cin>>lc;
                      cout<<"   note: ";
                cin>>nt;
                CreateEvent(d,m,y,evt,ct,lc,nt);
                cout<<"------------------------------"<<endl;
                option_();
                break;
            }
            case 2:{
                system("cls");
                cout<<endl<<endl;
                TextColor(5,1,"================================================================================");
                TextColor(14,1,"                               ::: events :::");
                TextColor(5,1,"--------------------------------------------------------------------------------");
                        cout<<"                               available events"<<endl
                            <<"                       ------------------------------"<<endl;
                cout<<"------------------------------"<<endl;
                viewAll();
                cout<<"------------------------------"<<endl;
                option_();
                break;
            }
            case 3:{
                system("cls");
                cout<<endl<<endl;
                TextColor(5,1,"================================================================================");
                TextColor(14,1,"                               ::: events :::");
                TextColor(5,1,"--------------------------------------------------------------------------------");
                        cout<<"                                 search event"<<endl
                            <<"                       ------------------------------"<<endl;
                cout<<"      enter the title of the event"<<endl;
                cin>>fl;
                cout<<"------------------------------"<<endl;
                searchEvent(fl);
                cout<<"------------------------------"<<endl;
                option_();
                break;
            }
            case 4:{
                system("cls");
                cout<<endl<<endl;
                TextColor(5,1,"================================================================================");
                TextColor(14,1,"                               ::: events :::");
                TextColor(5,1,"--------------------------------------------------------------------------------");
                        cout<<"                                edit an event"<<endl
                            <<"                        ------------------------------"<<endl;
                if(head==NULL){
                    cout<<"     no event available for editing!!!"<<endl;
                }
                else{
                cout<<"     enter the title of the event you want to edit"<<endl<<">>";
                cin>>fl;
                check=head;
                while(check->next!=NULL&&check->EventTitle!=fl){
                    check=check->next;
                }
                if(check->next==NULL&&check->EventTitle!=fl){
                    cout<<"     event your are trying to edit does not exist"<<endl;
                }
                else{
                    cout<<"------------------------------"<<endl;
                    cout<<"     enter the new event title: ";
                    cin>>evt;
                    for(check_=1;check_==1;){
                        if(head==NULL){
                            check_=0;
                        }
                        else{
                            check=head;
                            while(check->next!=NULL&&check->EventTitle!=evt){
                                check=check->next;
                            }
                            if(check->EventTitle==evt){
                                cout<<"     event with the same title exists!!! enter again: ";
                                cin>>evt;
                            }
                            else{
                                check_=0;
                            }
                        }
                    }
                    cout<<"     enter the new day: ";
                    cin>>d;
                    cout<<"     enter the new month: ";
                    cin>>m;
                    cout<<"     enter the new year: ";
                    cin>>y;
                    cout<<"     enter the new category: ";
                    cin>>ct;
                    cout<<"     enter the new location: ";
                    cin>>lc;
                    cout<<"     enter the new note: ";
                    cin>>nt;
                    editEvent(fl,d,m,y,evt,ct,lc,nt);
                    }
                }
                cout<<"------------------------------"<<endl;
                option_();
                break;
            }
            case 5:{
                system("cls");
                cout<<endl<<endl;
                TextColor(5,1,"================================================================================");
                TextColor(14,1,"                               ::: events :::");
                TextColor(5,1,"--------------------------------------------------------------------------------");
                        cout<<"                               delete an event"<<endl
                            <<"                       ------------------------------"<<endl;
                cout<<"     enter the title of the event you want to delete"<<endl;
                cin>>fl;
                cout<<"------------------------------"<<endl;
                cout<<deleteEvent(fl)<<endl;
                cout<<"------------------------------"<<endl;
                option_();
                break;
            }
            case 6:{
                Loop=1;
                break;
            }
            default:{
                cout<<endl<<"                invalid option"<<endl;
                option_();
                break;
            }
        }
    }
    Loop=0;
}

void about(){                           // this function displays some details of of the program
        system("cls");
        cout<<endl<<endl;
        TextColor(5,1,"================================================================================");
        TextColor(14+2*16,1,"                                ::: about :::                                   ");
        TextColor(5,1,"--------------------------------------------------------------------------------");
        TextColor(11,1,"                                 calender 0.5\n");
        TextColor(10,1,"                                    credit\n");
        TextColor(12,1,"                                Omer mohammed");
        TextColor(12,1,"                                 Natnael wube");
        TextColor(12,1,"                                  Naol arega");
        TextColor(12,1,"                               Zerubabel eshetu");
        TextColor(12,1,"                                yonatan naizgy");
        cout<<endl;
        system("pause");
}

void mainMenu(){                        // this is the main menu function which is displayed at
    for(Loop=0;Loop==0;){                 // beginning of execution
        system("cls");
        cout<<endl<<endl;
        TextColor(7,1,"                           =====[]=====[]=====");
        TextColor(7,0,"                           #");TextColor(11,0,"#################");TextColor(7,1,"#");
        TextColor(7,0,"                           #");TextColor(11,0,"#################");TextColor(7,1,"#");
        TextColor(7,1,"                           #                 #");
        TextColor(7,1,"                           #      D D D D D  #");
        TextColor(7,1,"                           #  D D D D D D D  #");
        TextColor(7,1,"                           #  D D D D D D D  #");
        TextColor(7,1,"                           #  D D D D D D    #");
        TextColor(7,1,"                           #                 #");
        TextColor(7,1,"                           ###################");
        TextColor(5,1,"================================================================================");
        TextColor(0+7*16,1,"                     ::: event management system :::                            ");
        TextColor(5,1,"--------------------------------------------------------------------------------");
        TextColor(7,0,"       1,");
        TextColor(11,1,"view calender");
        TextColor(7,0,"       2,");
        TextColor(11,1,"manage event");
        TextColor(7,0,"       3,");
        TextColor(11,1,"about");
        TextColor(7,0,"       4,");
        TextColor(12,1,"exit");
        cout<<endl<<">> ";
        cin>>choice;
        switch(choice){
            case 1:{
                viewCalender();
                break;
            }
            case 2:{
                event();
                break;
            }
            case 3:{
                about();
                break;
            }
            case 4:{
                Loop=1;
                break;
            }
            case 804:{
                easterEgg();
                break;
            }
            default:{
                system("cls");
                cout<<"error::invalid input"<<endl;
                system("pause");
            }
        }
    }
    Loop=0;
}

int main(){
    Load();
    welcomeWindow();
    mainMenu();
    TextColor(10,0,"\n>>saving...");
    _sleep(2000);
    wfile.open("date",ios::trunc);
    save();
return 0;
}
