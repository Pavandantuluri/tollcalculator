#include<iostream>
#include <ctime>
using namespace std;
 
class Vehicle
{
    private:
    
    int toll=0;
    string vehicle;
    public:
    
    void setType(string vehicle_type){
       vehicle = vehicle_type;
    }
    
    string getType(){
       return vehicle;
    }
    

    void setToll(int stoll){
        toll = stoll+toll;
        if (toll>60){
            toll = 60;
        }
    }
    int getToll(){
        return toll;
    };
};
 


int dayofweek(int date, int month, int year)
{
    static int t[] = { 0, 3, 2, 5, 0, 3,
                       5, 1, 4, 6, 2, 4 };
    year -= month < 3;
    return ( year + year / 4 - year / 100 +
             year / 400 + t[month - 1] + date) % 7;
}
bool checkWeekday(int day) {
    
    if(day == 0 || day == 6) {   //Sunday(0) and Saturday(6)
        
        return true;
    }
    else {
       return false;
    }
}

bool checkHoliday(int day,int month){
 if((((day == 1 ) && month == 1 ) || ((day == 1 || day == 23) && month == 5 ) || month==7 || (day == 1  && month == 11 ) || ((day == 24 || day == 25 || day == 26 || day == 31) && month == 12 )   )){
    return true;
   }
   else{
    return false;
   }
}

bool checkTollFreeVehicle(string vehicle){

    if (vehicle =="Car" || vehicle == "Motorbike" ){
         return true;
    }
    else{
    return false;
   }
}

int getTollPrice(int hour, int minute){
    int tollprice;
    if (hour == 6 && minute >= 0 && minute <= 29) {
    return 8;
    }
    else if (hour == 6 && minute >= 30 && minute <= 59){return 13;} 
    else if (hour == 7 && minute >= 0 && minute <= 59) {return 18;}
    else if (hour == 8 && minute >= 0 && minute <= 29) {return 13;}
    else if (hour >= 8 && hour <= 14 && minute >= 30 && minute <= 59) {return 8;}
    else if (hour == 15 && minute >= 0 && minute <= 29) return 13;
    else if (hour == 15 && minute >= 0 || hour == 16 && minute <= 59) {return 18;}
    else if (hour == 17 && minute >= 0 && minute <= 59) {return 13;}
    else if (hour == 18 && minute >= 0 && minute <= 29) {return 8;}
    else {return 0;}
}

int totalTollPrice(string vehicle, time_t datetime[],int size){
Vehicle v;
v.setType(vehicle);
for(int i = 0; i<size;i++){
  tm *ltm = localtime(&datetime[i]);
  int year = 1900 + ltm->tm_year;
  int month = 1 + ltm->tm_mon;
  int day = ltm->tm_mday;
  int hour = ltm->tm_hour;
  int minutes = ltm->tm_min;
  int weekday = dayofweek(day, month, year);
  bool checkWeekend =  checkWeekday(weekday);
  bool checkHolidays = checkHoliday(day,month); 
  bool checkTollFreeVehicles = checkTollFreeVehicle(v.getType());
 if(!checkWeekend || !checkHolidays || !checkTollFreeVehicles){
    int toll = getTollPrice(hour,minutes);
    v.setToll(toll);
 }
 else{
    v.setToll(0);
 }
 
  }
 
 /* */
 return v.getToll(); 
}



int main()
{
// Case1: calculate toll
    time_t now = time(0);    
    
    string s = "Car";
    time_t datetime [] = {now,now,now};
    int  size = sizeof(datetime)/sizeof(datetime[0]);
    
    //cout << totalTollPrice(s,datetime,size) << endl;
    
// Case2: calculate toll if more than 60

    time_t now1 = time(0);    
    
    string s1 = "Car";
    time_t datetime1 [] = {now,now,now,now,now,now,now,now,now};
    int  size1 = sizeof(datetime1)/sizeof(datetime1[0]);
    
    cout <<  totalTollPrice(s1,datetime1,size1) << endl;
 

// Case3: Toll Free Vehicle

    time_t now2 = time(0);    
    
    string s2 = "Car1";
    time_t datetime2 [] = {now,now,now,now,now,now,now,now,now};
    int  size2 = sizeof(datetime2)/sizeof(datetime2[0]);
    
    cout <<  totalTollPrice(s2,datetime2,size2) << endl;
    return 0;
}
