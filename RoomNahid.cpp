#include <bits/stdc++.h>
using namespace std;

struct Booking {
    string room;
    int startMinutes;
    int endMinutes;
};

// Convert "HH:MM AM/PM" → minutes since midnight
int toMinutes(string time) {
    int h, m;
    char colon;
    string ampm;
    stringstream ss(time);
    ss >> h >> colon >> m >> ampm;

    if ((ampm == "PM"|| ampm=="pm") && h != 12) h += 12;
    if ((ampm == "AM"|| ampm=="am") && h == 12) h = 0;

    return h * 60 + m;
}

// Convert "HH:MM to HH:MM" → Booking with minutes
Booking parseBooking(string room, string timeRange) {
    size_t pos = timeRange.find(" to ");
    string start = timeRange.substr(0, pos);
    string end = timeRange.substr(pos + 4);
    return {room, toMinutes(start), toMinutes(end)};
}

int main() {
    // Organize bookings by day and room
    map<string, map<string, vector<Booking>>> schedule;
   // ===== Example bookings for Sunday =====
    vector<tuple<string, string, string>> rawBookings = {
        {"108","Sunday","1:00 PM to 2:15 PM"},
{"108","Sunday","2:15 PM to 3:30 PM"},
{"108","Sunday","9:00 AM to 10:15 AM"},
{"109","Sunday","1:00 PM to 2:15 PM"},
{"109","Sunday","2:15 PM to 3:30 PM"},
{"306","Sunday","9:00 AM to 10:15 AM"},
{"307","Sunday","10:15 AM to 11:30 AM"},
{"307","Sunday","1:00 PM to 2:15 PM"},
{"307","Sunday","2:15 PM to 3:30 PM"},
{"307","Sunday","9:00 AM to 10:15 AM"},
{"309","Sunday","1:00 PM to 2:15 PM"},
{"309","Sunday","2:15 PM to 3:30 PM"},
{"309","Sunday","9:00 AM to 10:15 AM"},
{"310","Sunday","1:00 PM to 2:15 PM"},
{"310","Sunday","2:15 PM to 3:30 PM"},
{"310","Sunday","9:00 AM to 10:15 AM"},
{"311","Sunday","1:00 PM to 2:15 PM"},
{"311","Sunday","10:15 AM to 11:30 AM"},
{"401","Sunday","11:30 AM to 12:45 PM"},
{"401","Sunday","1:00 PM to 2:15 PM"},
{"404","Sunday","3:30 PM to 4:45 PM"},
{"405","Sunday","9:00 AM to 10:15 AM"},
{"406","Sunday","11:30 AM to 12:45 PM"},
{"408","Sunday","10:15 AM to 11:30 AM"},
{"408","Sunday","11:30 AM to 12:45 PM"},
{"408","Sunday","3:30 PM to 4:45 PM"},
{"409","Sunday","11:30 AM to 12:45 PM"},
{"409","Sunday","3:30 PM to 4:45 PM"},
{"501","Sunday","11:30 AM to 12:45 PM"},
{"501","Sunday","3:30 PM to 4:45 PM"},
{"502","Sunday","1:00 PM to 2:15 PM"},
{"503","Sunday","11:30 AM to 12:45 PM"},
{"506","Sunday","3:30 PM to 4:45 PM"},
{"507","Sunday","11:30 AM to 12:45 PM"},
{"507","Sunday","3:30 PM to 4:45 PM"},
{"508","Sunday","9:00 AM to 10:15 AM"},
{"508","Sunday","10:15 AM to 11:30 AM"},
{"509","Sunday","10:15 AM to 11:30 AM"},
{"509","Sunday","11:30 AM to 12:45 PM"},
{"GL-1","Sunday","11:30 AM to 12:45 PM"},
{"GL-2","Sunday","1:00 PM to 2:15 PM"},
{"GL-2","Sunday","3:30 PM to 4:45 PM"},
{"GL-2","Sunday","9:00 AM to 10:15 AM"},
{"GL-4","Sunday","10:15 AM to 11:30 AM"},

// ==== Monday ====
{"108","Monday","10:15 AM to 11:30 AM"},
{"108","Monday","11:30 AM to 12:45 PM"},
{"108","Monday","3:30 PM to 4:45 PM"},
{"109","Monday","10:15 AM to 11:30 AM"},
{"109","Monday","11:30 AM to 12:45 PM"},
{"109","Monday","3:30 PM to 4:45 PM"},
{"306","Monday","1:00 PM to 2:15 PM"},
{"306","Monday","2:15 PM to 3:30 PM"},
{"307","Monday","9:00 AM to 10:15 AM"},
{"307","Monday","10:15 AM to 11:30 AM"},
{"307","Monday","2:15 PM to 3:30 PM"},
{"309","Monday","9:00 AM to 10:15 AM"},
{"309","Monday","11:30 AM to 12:45 PM"},
{"309","Monday","1:00 PM to 2:15 PM"},
{"310","Monday","11:30 AM to 12:45 PM"},
{"310","Monday","2:15 PM to 3:30 PM"},
{"310","Monday","3:30 PM to 4:45 PM"},
{"311","Monday","9:00 AM to 10:15 AM"},
{"311","Monday","10:15 AM to 11:30 AM"},
{"401","Monday","1:00 PM to 2:15 PM"},
{"401","Monday","2:15 PM to 3:30 PM"},
{"401","Monday","3:30 PM to 4:45 PM"},
{"404","Monday","9:00 AM to 10:15 AM"},
{"404","Monday","10:15 AM to 11:30 AM"},
{"404","Monday","11:30 AM to 12:45 PM"},
{"405","Monday","1:00 PM to 2:15 PM"},
{"405","Monday","2:15 PM to 3:30 PM"},
{"406","Monday","9:00 AM to 10:15 AM"},
{"406","Monday","10:15 AM to 11:30 AM"},
{"408","Monday","1:00 PM to 2:15 PM"},
{"408","Monday","2:15 PM to 3:30 PM"},
{"409","Monday","9:00 AM to 10:15 AM"},
{"409","Monday","1:00 PM to 2:15 PM"},
{"501","Monday","10:15 AM to 11:30 AM"},
{"501","Monday","2:15 PM to 3:30 PM"},
{"502","Monday","9:00 AM to 10:15 AM"},
{"502","Monday","11:30 AM to 12:45 PM"},
{"502","Monday","3:30 PM to 4:45 PM"},
{"503","Monday","1:00 PM to 2:15 PM"},
{"503","Monday","2:15 PM to 3:30 PM"},
{"504","Monday","9:00 AM to 10:15 AM"},
{"504","Monday","11:30 AM to 12:45 PM"},
{"505","Monday","10:15 AM to 11:30 AM"},
{"505","Monday","1:00 PM to 2:15 PM"},
{"506","Monday","9:00 AM to 10:15 AM"},
{"506","Monday","11:30 AM to 12:45 PM"},
{"507","Monday","9:00 AM to 10:15 AM"},
{"507","Monday","1:00 PM to 2:15 PM"},
{"507","Monday","2:15 PM to 3:30 PM"},
{"508","Monday","1:00 PM to 2:15 PM"},
{"508","Monday","2:15 PM to 3:30 PM"},
{"509","Monday","1:00 PM to 2:15 PM"},
{"509","Monday","2:15 PM to 3:30 PM"},
{"509","Monday","3:30 PM to 4:45 PM"},
{"GL-1","Monday","1:00 PM to 2:15 PM"},
{"GL-1","Monday","2:15 PM to 3:30 PM"},
{"GL-2","Monday","9:00 AM to 10:15 AM"},
{"GL-2","Monday","11:30 AM to 12:45 PM"},
{"GL-4","Monday","9:00 AM to 10:15 AM"},
{"GL-4","Monday","11:30 AM to 12:45 PM"},
// ==== Tuesday ====
{"109","Tuesday","9:00 AM to 10:15 AM"},
{"109","Tuesday","1:00 PM to 2:15 PM"},
{"203","Tuesday","3:30 PM to 4:45 PM"},
{"205","Tuesday","11:30 AM to 12:45 PM"},
{"302","Tuesday","9:00 AM to 10:15 AM"},
{"307","Tuesday","9:00 AM to 10:15 AM"},
{"307","Tuesday","1:00 PM to 2:15 PM"},
{"307","Tuesday","2:15 PM to 3:30 PM"},
{"309","Tuesday","9:00 AM to 10:15 AM"},
{"309","Tuesday","3:30 PM to 4:45 PM"},
{"310","Tuesday","9:00 AM to 10:15 AM"},
{"310","Tuesday","2:15 PM to 3:30 PM"},
{"311","Tuesday","11:30 AM to 12:45 PM"},
{"311","Tuesday","2:15 PM to 3:30 PM"},
{"401","Tuesday","11:30 AM to 12:45 PM"},
{"404","Tuesday","3:30 PM to 4:45 PM"},
{"405","Tuesday","11:30 AM to 12:45 PM"},
{"408","Tuesday","9:00 AM to 10:15 AM"},
{"408","Tuesday","10:15 AM to 11:30 AM"},
{"408","Tuesday","11:30 AM to 12:45 PM"},
{"409","Tuesday","1:00 PM to 2:15 PM"},
{"501","Tuesday","9:00 AM to 10:15 AM"},
{"501","Tuesday","1:00 PM to 2:15 PM"},
{"501","Tuesday","2:15 PM to 3:30 PM"},
{"502","Tuesday","1:00 PM to 2:15 PM"},
{"502","Tuesday","2:15 PM to 3:30 PM"},
{"503","Tuesday","9:00 AM to 10:15 AM"},
{"503","Tuesday","11:30 AM to 12:45 PM"},
{"504","Tuesday","11:30 AM to 12:45 PM"},
{"505","Tuesday","3:30 PM to 4:45 PM"},
{"506","Tuesday","11:30 AM to 12:45 PM"},
{"506","Tuesday","1:00 PM to 2:15 PM"},
{"506","Tuesday","2:15 PM to 3:30 PM"},
{"507","Tuesday","9:00 AM to 10:15 AM"},
{"507","Tuesday","10:15 AM to 11:30 AM"},
{"507","Tuesday","11:30 AM to 12:45 PM"},
{"508","Tuesday","10:15 AM to 11:30 AM"},
{"508","Tuesday","11:30 AM to 12:45 PM"},
{"509","Tuesday","2:15 PM to 3:30 PM"},
{"GL-1","Tuesday","10:15 AM to 11:30 AM"},
{"GL-1","Tuesday","11:30 AM to 12:45 PM"},
{"GL-2","Tuesday","3:30 PM to 4:45 PM"},
// ==== Wednesday ====
{"108","Wednesday","11:30 AM to 12:45 PM"},
{"108","Wednesday","1:00 PM to 2:15 PM"},
{"108","Wednesday","2:15 PM to 3:30 PM"},
{"109","Wednesday","1:00 PM to 2:15 PM"},
{"109","Wednesday","2:15 PM to 3:30 PM"},
{"307","Wednesday","9:00 AM to 10:15 AM"},
{"309","Wednesday","9:00 AM to 10:15 AM"},
{"309","Wednesday","1:00 PM to 2:15 PM"},
{"310","Wednesday","9:00 AM to 10:15 AM"},
{"310","Wednesday","10:15 AM to 11:30 AM"},
{"311","Wednesday","9:00 AM to 10:15 AM"},
{"311","Wednesday","10:15 AM to 11:30 AM"},
{"401","Wednesday","1:00 PM to 2:15 PM"},
{"404","Wednesday","3:30 PM to 4:45 PM"},
{"405","Wednesday","1:00 PM to 2:15 PM"},
{"405","Wednesday","2:15 PM to 3:30 PM"},
{"408","Wednesday","1:00 PM to 2:15 PM"},
{"408","Wednesday","2:15 PM to 3:30 PM"},
{"409","Wednesday","11:30 AM to 12:45 PM"},
{"501","Wednesday","9:00 AM to 10:15 AM"},
{"501","Wednesday","3:30 PM to 4:45 PM"},
{"502","Wednesday","11:30 AM to 12:45 PM"},
{"502","Wednesday","3:30 PM to 4:45 PM"},
{"503","Wednesday","11:30 AM to 12:45 PM"},
{"506","Wednesday","9:00 AM to 10:15 AM"},
{"506","Wednesday","10:15 AM to 11:30 AM"},
{"507","Wednesday","1:00 PM to 2:15 PM"},
{"508","Wednesday","11:30 AM to 12:45 PM"},
{"508","Wednesday","1:00 PM to 2:15 PM"},
{"509","Wednesday","11:30 AM to 12:45 PM"},
{"509","Wednesday","3:30 PM to 4:45 PM"},
{"GL-1","Wednesday","11:30 AM to 12:45 PM"},
// ==== Thursday ====
{"109","Thursday","1:00 PM to 2:15 PM"},
{"301","Thursday","9:00 AM to 10:15 AM"},
{"307","Thursday","9:00 AM to 10:15 AM"},
{"307","Thursday","10:15 AM to 11:30 AM"},
{"309","Thursday","1:00 PM to 2:15 PM"},
{"309","Thursday","10:15 AM to 11:30 AM"},
{"309","Thursday","3:30 PM to 4:45 PM"},
{"310","Thursday","11:30 AM to 12:45 PM"},
{"311","Thursday","9:00 AM to 10:15 AM"},
{"311","Thursday","10:15 AM to 11:30 AM"},
{"400","Thursday","1:00 PM to 2:15 PM"},
{"405","Thursday","1:00 PM to 2:15 PM"},
{"405","Thursday","2:15 PM to 3:30 PM"},
{"408","Thursday","1:00 PM to 2:15 PM"},
{"408","Thursday","3:30 PM to 4:45 PM"},
{"409","Thursday","1:00 PM to 2:15 PM"},
{"501","Thursday","3:30 PM to 4:45 PM"},
{"502","Thursday","9:00 AM to 10:15 AM"},
{"502","Thursday","3:30 PM to 4:45 PM"},
{"503","Thursday","11:30 AM to 12:45 PM"},
{"503","Thursday","3:30 PM to 4:45 PM"},
{"504","Thursday","9:00 AM to 10:15 AM"},
{"504","Thursday","11:30 AM to 12:45 PM"},
{"505","Thursday","1:00 PM to 2:15 PM"},
{"505","Thursday","2:15 PM to 3:30 PM"},
{"506","Thursday","1:00 PM to 2:15 PM"},
{"506","Thursday","2:15 PM to 3:30 PM"},
{"507","Thursday","1:00 PM to 2:15 PM"},
{"507","Thursday","2:15 PM to 3:30 PM"},
{"508","Thursday","10:15 AM to 11:30 AM"},
{"GL-1","Thursday","1:00 PM to 2:15 PM"},
{"GL-2","Thursday","11:30 AM to 12:45 PM"},
{"GL-2","Thursday","1:00 PM to 2:15 PM"},
// ===== Sunday =====
// ===== Sunday =====
{"306","Sunday","9:00 AM to 10:15 AM"},
{"301","Sunday","9:00 AM to 10:15 AM"},
{"502","Sunday","9:00 AM to 10:15 AM"},
{"408","Sunday","9:00 AM to 10:15 AM"},
{"109","Sunday","9:00 AM to 10:15 AM"},
{"506","Sunday","9:00 AM to 10:15 AM"},
{"204","Sunday","9:00 AM to 10:15 AM"},

{"306","Sunday","10:30 AM to 11:45 AM"},
{"301","Sunday","10:30 AM to 11:45 AM"},
{"505","Sunday","10:30 AM to 11:45 AM"},
{"109","Sunday","10:30 AM to 11:45 AM"},
{"506","Sunday","10:30 AM to 11:45 AM"},

{"301","Sunday","12:00 PM to 1:15 PM"},
{"506","Sunday","12:00 PM to 1:15 PM"},
{"306","Sunday","12:00 PM to 1:15 PM"},

{"301","Sunday","1:30 PM to 2:45 PM"},
{"506","Sunday","1:30 PM to 2:45 PM"},

{"306","Sunday","3:00 PM to 4:15 PM"},

// ===== Monday =====
{"301","Monday","9:00 AM to 10:15 AM"},
{"506","Monday","9:00 AM to 10:15 AM"},
{"306","Monday","9:00 AM to 10:15 AM"},

{"301","Monday","10:30 AM to 11:45 AM"},
{"205","Monday","10:30 AM to 11:45 AM"},
{"306","Monday","10:30 AM to 11:45 AM"},
{"100","Monday","10:30 AM to 11:45 AM"},

{"306","Monday","12:00 PM to 1:15 PM"},
{"301","Monday","12:00 PM to 1:15 PM"},
{"140","Monday","12:00 PM to 1:15 PM"},
{"506","Monday","12:00 PM to 1:15 PM"},

{"101","Monday","1:30 PM to 2:45 PM"},
{"506","Monday","1:30 PM to 2:45 PM"},
{"106","Monday","1:30 PM to 2:45 PM"},

{"301","Monday","3:00 PM to 4:15 PM"},
{"305","Monday","3:00 PM to 4:15 PM"},
{"506","Monday","3:00 PM to 4:15 PM"},
{"106","Monday","3:00 PM to 4:15 PM"},

{"301","Monday","4:30 PM to 5:45 PM"},

// ===== Tuesday =====
{"403","Tuesday","9:00 AM to 10:15 AM"},
{"301","Tuesday","9:00 AM to 10:15 AM"},
{"506","Tuesday","9:00 AM to 10:15 AM"},

{"301","Tuesday","10:30 AM to 11:45 AM"},
{"506","Tuesday","10:30 AM to 11:45 AM"},
{"100","Tuesday","10:30 AM to 11:45 AM"},

{"301","Tuesday","12:00 PM to 1:15 PM"},
{"506","Tuesday","12:00 PM to 1:15 PM"},
{"306","Tuesday","12:00 PM to 1:15 PM"},
{"100","Tuesday","12:00 PM to 1:15 PM"},

{"301","Tuesday","1:30 PM to 2:45 PM"},
{"301","Tuesday","3:00 PM to 4:15 PM"},
{"301","Tuesday","4:30 PM to 5:45 PM"},

// ===== Wednesday =====
{"204","Wednesday","9:00 AM to 10:15 AM"},
{"406","Wednesday","9:00 AM to 10:15 AM"},
{"306","Wednesday","9:00 AM to 10:15 AM"},

{"506","Wednesday","10:30 AM to 11:45 AM"},
{"306","Wednesday","10:30 AM to 11:45 AM"},

{"506","Wednesday","12:00 PM to 1:15 PM"},
{"306","Wednesday","12:00 PM to 1:15 PM"},
{"301","Wednesday","12:00 PM to 1:15 PM"},

{"506","Wednesday","1:30 PM to 2:45 PM"},
{"306","Wednesday","1:30 PM to 2:45 PM"},
{"301","Wednesday","1:30 PM to 2:45 PM"},

// ===== Thursday =====
{"204","Thursday","9:00 AM to 10:15 AM"},

{"301","Thursday","10:30 AM to 11:45 AM"},
{"203","Thursday","10:30 AM to 11:45 AM"},
{"506","Thursday","10:30 AM to 11:45 AM"},

{"506","Thursday","12:00 PM to 1:15 PM"},
{"204","Thursday","12:00 PM to 1:15 PM"},

{"506","Thursday","1:30 PM to 2:45 PM"},

{"301","Thursday","3:00 PM to 4:15 PM"},
{"301","Thursday","4:30 PM to 5:45 PM"},
    };

    // Populate schedule
    for (auto &b : rawBookings) {
        string room, day, timeRange;
        tie(room, day, timeRange) = b;
        schedule[day][room].push_back(parseBooking(room, timeRange));
    }

    // Sort bookings for each room by start time
     for (auto &dayPair : schedule) {
        for (auto &roomPair : dayPair.second) {
            sort(roomPair.second.begin(), roomPair.second.end(), 
                 [](Booking a, Booking b){ return a.startMinutes < b.startMinutes; });
        }
    }

    // User input
    string day, startTime, endTime;
    cout << "Enter day (e.g., Sunday) : ";
    getline(cin, day);
    cout << "Enter start time (e.g., 10:15 AM) : ";
    getline(cin, startTime);
    cout << "Enter end time (e.g., 11:30 AM) : ";
    getline(cin, endTime);

    int searchStart = toMinutes(startTime);
    int searchEnd = toMinutes(endTime);

    if (schedule.find(day) == schedule.end()) {
        cout << "Oto class korar lagi jan jar ni!!" << endl;
        return 0;
    }

    bool anyFree = false;
    for (auto &roomPair : schedule[day]) {
        string room = roomPair.first;
        vector<Booking> &bookings = roomPair.second;

        int current = searchStart;
        vector<pair<int,int>> freeSlots;

        for (auto &b : bookings) {
            if (b.endMinutes <= current) continue; // booking before search
            if (b.startMinutes >= searchEnd) break; // booking after search
            if (b.startMinutes > current)//start 12:45 & end 1:30 
            {
                freeSlots.push_back({current, min(searchEnd, b.startMinutes)});
            }
            current = max(current, b.endMinutes);
        }

        if (current < searchEnd) {
            freeSlots.push_back({current, searchEnd});
        }

        if (!freeSlots.empty()) {
            anyFree = true;
            cout << "Room " << room << " is FREE in the following intervals:" << endl;
            for (auto &slot : freeSlots) {
                int startH = slot.first / 60, startM = slot.first % 60;
                int endH = slot.second / 60, endM = slot.second % 60;
                int duration = slot.second - slot.first;
                cout << "  " << setw(2) << setfill('0') << startH << ":"
                     << setw(2) << setfill('0') << startM << " to "
                     << setw(2) << setfill('0') << endH << ":"
                     << setw(2) << setfill('0') << endM 
                     << " (" << duration << " mins)" << endl;
            }
        }
    }

    if (!anyFree) cout << "No rooms are free in this interval." << endl;

    return 0;

}
