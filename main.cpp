#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <curl/curl.h>

struct Date {
    std::string day;
    std::string monthStr;
    std::string monthNum;
    std::string year;

    std::string hours;
    std::string minutes;
    std::string seconds;
};

std::string MonthStringToNum(const Date &date) {
    if (date.monthStr == "Jan")
        return "01";
    if (date.monthStr == "Feb")
        return "02";
    if (date.monthStr == "Mar")
        return "03";
    if (date.monthStr == "Apr")
        return "04";
    if (date.monthStr == "May")
        return "05";
    if (date.monthStr == "Jun")
        return "06";
    if (date.monthStr == "Jul")
        return "07";
    if (date.monthStr == "Aug")
        return "08";
    if (date.monthStr == "Sep")
        return "09";
    if (date.monthStr == "Oct")
        return "10";
    if (date.monthStr == "Nov")
        return "11";
    if (date.monthStr == "Dec")
        return "12";
    return "00";
}

int main(int argc, char *argv[]) {
    CURL *curl1;
    CURL *curl2;
    CURLcode res;
    FILE *file1 = fopen("verbose", "w+");
    FILE *file2 = fopen(argv[1], "w+");
    curl1 = curl_easy_init();
    curl2 = curl_easy_init();
    if (curl1 && curl2) {
        curl_easy_setopt(curl1, CURLOPT_URL, "http://www.google.com");
        curl_easy_setopt(curl1, CURLOPT_VERBOSE, 1L);
        curl_easy_setopt(curl1, CURLOPT_STDERR, file1);
        curl_easy_setopt(curl1, CURLOPT_WRITEDATA, nullptr);

        curl_easy_setopt(curl2, CURLOPT_URL, "https://example.com");
        curl_easy_setopt(curl2, CURLOPT_SSL_VERIFYPEER, 0);
        curl_easy_setopt(curl2, CURLOPT_VERBOSE, 1L);
        curl_easy_setopt(curl2, CURLOPT_STDERR, file2);
        curl_easy_setopt(curl2, CURLOPT_WRITEDATA, nullptr);

        res = curl_easy_perform(curl1);
        res = curl_easy_perform(curl2);
        fclose(file1);
        fclose(file2);
        curl_easy_cleanup(curl1);
        curl_easy_cleanup(curl2);
    }
    std::fstream input("verbose.txt");
    std::stringstream dateStream;
    std::string dateString;
    while (std::getline(input, dateString)) {
        if (dateString.find("Date") != -1)
            break;
    }
    Date date;
    dateString.erase(dateString.begin(), dateString.begin() + 13);
    dateStream << dateString;
    std::getline(dateStream, date.day, ' ');
    std::getline(dateStream, date.monthStr, ' ');
    date.monthNum = MonthStringToNum(date);
    std::getline(dateStream, date.year, ' ');
    std::getline(dateStream, date.hours, ':');
    std::getline(dateStream, date.minutes, ':');
    std::getline(dateStream, date.seconds, ' ');

// Windows
//    std::string dateSys = "date " + date.day + '-' + date.monthNum + '-' + date.year;
//    std::string timeSys = "time " + date.hours + ':' + date.minutes + ':' + date.seconds;
//
//    char *cStrDateSys = new char[dateSys.length()+1];
//    strcpy(cStrDateSys, dateSys.c_str());
//    char *cStrTimeSys = new char[timeSys.length()+1];
//    strcpy(cStrTimeSys, timeSys.c_str());
//    system(cStrDateSys);
//    system(cStrTimeSys);
//    delete[] cStrDateSys;
//    delete[] cStrTimeSys;

//Linux
    std::string dateSys = "sudo date " + date.monthNum + date.day + date.hours + date.minutes +
                          date.year + '.' + date.seconds;
    char *cStrDateSys = new char[dateSys.length()+1];
    strcpy(cStrDateSys, dateSys.c_str());
    system(cStrDateSys);
    delete[] cStrDateSys;


    system("pause");
    return 0;
}