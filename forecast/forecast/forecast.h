#pragma once
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>
#include <vector>
#include <iostream>
#include <iostream>
#include <vector>
#include <string>
#include <exception>
#include <unordered_map>
#include <conio.h>

struct Info {
    std::string       date;
    std::string       month;
    int               time_of_day;
    std::string       description;
    float             temperature;
    float             apparent_temperature;
    int               wind_speed;
    int               visibility;
    float             precipitation;
    int               humidity;
    int               weather_code;
};

struct DailyInfo {
    Info morning;
    Info noon;
    Info evening;
    Info night;
};

class forecast {
public:

    void PrintInfo(DailyInfo& info);
    void Print(int city, int count);

    void fun() {
        GetConfig();
        ApiNinjasRequest();
        OpenMeteoRequest();

        int cur = 0;
        int count = 1;

        Print(cur, count);

        while (true) {
            char key = getch();
            if (key == 27) {
                exit(0)  ;
            } else if (key == 'n') {
                if (cur == cities_.size() - 1) {
                    cur = 0;
                } else {
                    cur++;
                }

                system("cls");
                Print(cur, count);

            } else if (key == 'p') {
                if (cur == 0) {
                    cur = cities_.size() - 1;
                } else {
                    cur--;
                }
                system("cls");
                Print(cur, count);

            } else if (key == '+') {
                if (count < config.days_count_) {
                    count++;

                    system("cls");
                    Print(cur, count);
                }
            } else if (key == '-') {
                if (count > 1) {
                    count--;

                    system("cls");
                    Print(cur, count);
                }
            }
        }
    }

private:
    void ApiNinjasRequest();
    void OpenMeteoRequest();

    Info GetInfo(nlohmann::json& json, int time);
    void GetConfig();
    void WeatherDescription(std::string& des, int& code);
    void GetMonth(std::string& month);

private:
    struct City {
        std::string name_;
        std::string country_;
        float longitude_{};
        float latitude_{};
        Info cur_info_;

        std::vector<DailyInfo> info_;
    };

    struct Config {
        size_t days_count_;
        size_t frequency_;
        std::vector<std::string> cities_;
    } config;

    std::vector<City> cities_;


    const std::vector<std::vector<std::string>> pictures_ {
            {
                        "    \\   /    ",
                        "     .-.     ",
                        "  - (   ) -  ",
                        "     `-'     ",
                        "    /   \\    "
            },
            {
                        "   \\         ",
                        " _ /\"\".-.    ",
                        "   \\_(   ).  ",
                        "   /(___(__) ",
                        "             "
            },
            {
                        "             ",
                        " _ - _ - _ - ",
                        "  _ - _ - _  ",
                        " _ - _ - _ - ",
                        "             "
            },
            {
                          "     .-.     ",
                          "    (   ).   ",
                          "   (___(__)  ",
                          "    ' ' ' '  ",
                          "   ' ' ' '   "
            },
            {
                          "     .-.     ",
                          "    (   ).   ",
                          "   (___(__)  ",
                          "    ' * ' *  ",
                          "   * ' * '   "
            },
            {
                          "     .-.     ",
                          "    (   ).   ",
                          "   (___(__)  ",
                          "  ,',',','   ",
                          "  ,',',','   "
            },
            {
                           " _`/\"\".-.    ",
                           "  ,\\_(   ).  ",
                           "   /(___(__) ",
                           "     ' * ' * ",
                           "    * ' * '  "
            },
            {
                          "     .-.     ",
                          "    (   ).   ",
                          "   (___(__)  ",
                          "    *  *  *  ",
                          "   *  *  *   "
            },
            {
                           " _`/\"\".-.    ",
                           "  ,\\_(   ).  ",
                           "   /(___(__) ",
                           "    * * * *  ",
                           "   * * * *   "
            },
            {
                           " _`/\"\".-.    ",
                           "  ,\\_(   ).  ",
                           "   /(___(__) ",
                           "    * * * *  ",
                           "   * * * *   "
            },
            {
                            " _`/\"\".-.    ",
                            "  ,\\_(   ).  ",
                            "   /(___(__) ",
                            "     *7 *7 * ",
                            "    *  *  *  "
            },
            {
                            "    .-.      ",
                            "     __)     ",
                            "    (        ",
                            "     `-'     ",
                            "      •      "
            }
    };
};
