#include "forecast.h"

int WSNumWC(float num1, float num2) {
    std::string str1 = std::to_string(num1);
    std::string str2 = std::to_string(num2);
    int a = str1.find('.');
    int b = str2.find('.');


    return 11 - (str1.find('.') + str2.find('.'));
}

int WSNumT(int num) {
    std::string str = std::to_string(num);
    return 12 - str.size();
}

int WSNumH(float num1, int num2) {
    std::string str1 = std::to_string(num1);
    std::string str2 = std::to_string(num2);
    int num = 8 - (str1.find('.') + str2.size());
    return num;
}

void forecast::Print(int city, int count) {

    std::cout << "Forecast: " << cities_[city].name_ << ", " << cities_[city].country_ << '\n';

    for (size_t i = 0; i < count; i++) {
        PrintInfo(cities_[city].info_[i]);
    }
}



void forecast::PrintInfo(DailyInfo& info) {
    std::cout << "                                                       ┌─────────────┐                                                       \n";
    std::cout << "┌──────────────────────────────┬───────────────────────┤   " + info.morning.date + ' ' + info.morning.month + "   ├───────────────────────┬──────────────────────────────┐\n";
    std::cout << "│           Morning            │             Noon      └──────┬──────┘    Evening            │            Night             │\n";
    std::cout << "├──────────────────────────────┼──────────────────────────────┼──────────────────────────────┼──────────────────────────────┤\n";
    std::cout << "│" + pictures_[info.morning.weather_code][0] << info.morning.description
              << "│" + pictures_[info.noon.weather_code][0] << info.noon.description
              << "│" + pictures_[info.evening.weather_code][0] << info.evening.description
              << "│" + pictures_[info.night.weather_code][0] << info.night.description << "│\n";

    std::cout.setf(std::ios::fixed);
    std::cout.precision(1);

    std::cout << "│" + pictures_[info.morning.weather_code][1] << info.morning.temperature << '(' << info.morning.apparent_temperature  << ')'
              << std::setw(WSNumWC(info.morning.temperature, info.morning.apparent_temperature)) << ' '
              << "│" + pictures_[info.noon.weather_code][1] << info.noon.temperature << '(' << info.noon.apparent_temperature << ')'
              << std::setw(WSNumWC(info.noon.temperature, info.noon.apparent_temperature)) << ' '
              << "│" + pictures_[info.evening.weather_code][1] << info.evening.temperature << '(' << info.evening.apparent_temperature << ')'
              << std::setw(WSNumWC(info.evening.temperature, info.evening.apparent_temperature)) << ' '
              << "│" + pictures_[info.night.weather_code][1] << info.night.temperature << '(' << info.night.apparent_temperature << ')'
              << std::setw(WSNumWC(info.night.temperature, info.night.apparent_temperature)) << ' '<< "│\n";

    std::cout << "│" + pictures_[info.morning.weather_code][2] << info.morning.wind_speed << " km/h"
              << std::setw(WSNumT(info.morning.wind_speed)) << ' '
              << "│" + pictures_[info.noon.weather_code][2] << info.noon.wind_speed << " km/h"
              << std::setw(WSNumT(info.noon.wind_speed)) << ' '
              << "│" + pictures_[info.evening.weather_code][2] << info.evening.wind_speed << " km/h"
              << std::setw(WSNumT(info.evening.wind_speed)) << ' '
              << "│" + pictures_[info.night.weather_code][2] << info.night.wind_speed << " km/h"
              << std::setw(WSNumT(info.night.wind_speed)) << ' ' <<  "│\n";

    std::cout << "│" + pictures_[info.morning.weather_code][3] << info.morning.visibility << " km"
              << std::setw(WSNumT(info.morning.visibility) + 2) << ' '
              << "│" + pictures_[info.noon.weather_code][3] << info.noon.visibility << " km"
              << std::setw(WSNumT(info.noon.visibility) + 2) << ' '
              << "│" + pictures_[info.evening.weather_code][3] << info.evening.visibility << " km"
              << std::setw(WSNumT(info.evening.visibility) + 2) << ' '
              << "│" + pictures_[info.night.weather_code][3] << info.night.visibility << " km"
              << std::setw(WSNumT(info.night.visibility) + 2) << ' ' <<  "│\n";

    std::cout << "│" + pictures_[info.morning.weather_code][4] << info.morning.precipitation << " mm | " << info.morning.humidity << '%'
              << std::setw(WSNumH(info.morning.precipitation, info.morning.humidity)) << ' '
              << "│" + pictures_[info.noon.weather_code][4] << info.noon.precipitation << " mm | " << info.noon.humidity << '%'
              << std::setw(WSNumH(info.noon.precipitation, info.noon.humidity)) << ' '
              << "│" + pictures_[info.evening.weather_code][4] << info.evening.precipitation << " mm | " << info.evening.humidity << '%'
              << std::setw(WSNumH(info.evening.precipitation, info.evening.humidity)) << ' '
              << "│" + pictures_[info.night.weather_code][4] << info.night.precipitation << " mm | " << info.night.humidity << '%'
              << std::setw(WSNumH(info.night.precipitation, info.night.humidity)) << ' '<< "│\n";

    std::cout << "└──────────────────────────────┴──────────────────────────────┴──────────────────────────────┴──────────────────────────────┘\n";

}

void forecast::ApiNinjasRequest() {
    for (size_t i = 0; i < config.cities_.size(); i++) {
        const cpr::Url ApiNinjasURL{"https://api.api-ninjas.com/v1/city"};

        cpr::Response response = cpr::Get(ApiNinjasURL,
                                          cpr::Header{{"X-Api-Key", "SYr+ghYfFlMvIeS7JYy0AA==k5Qso3CgxOiBJEAu"}},
                                          cpr::Parameters{{"name", config.cities_[i]}});
        nlohmann::json json_text = nlohmann::json::parse(response.text);

        if (response.status_code == 200 && !json_text[0].empty()) {
            City city;
            city.name_ = config.cities_[i];
            city.country_ = json_text[0]["country"];
            city.latitude_ = json_text[0]["latitude"];
            city.longitude_ = json_text[0]["longitude"];

            cities_.emplace_back(city);
        } else {
            throw std::invalid_argument("Bad city");
        }
    }
}

Info forecast::GetInfo(nlohmann::json& json, int time) {
    Info info;

    info.temperature = json["hourly"]["temperature_2m"][time];
    std::string date = json["hourly"]["time"][time];
    info.date = date.substr(8, 2);
    info.month = date.substr(5, 2);
    GetMonth(info.month);

    info.weather_code = json["hourly"]["weathercode"][time];
    WeatherDescription(info.description, info.weather_code);

    info.wind_speed = json["hourly"]["windspeed_10m"][time];
    info.time_of_day = time / 6;

    info.humidity = json["hourly"]["relativehumidity_2m"][time];
    info.precipitation = json["hourly"]["precipitation"][time];
    info.visibility = json["hourly"]["visibility"][time];
    info.visibility /= 1000;
    info.apparent_temperature = json["hourly"]["apparent_temperature"][time];

    return info;
}

void forecast::OpenMeteoRequest() {
    for (auto & city : cities_) {
        const cpr::Url OpenMeteoURL{"https://api.open-meteo.com/v1/forecast"};
        cpr::Response response = cpr::Get(OpenMeteoURL,
                                          cpr::Parameters{{"longitude", std::to_string(city.longitude_)},
                                                          {"latitude", std::to_string(city.latitude_)},
                                                          {"forecast_days", std::to_string(config.days_count_)},
                                                          {"current_weather", "true"},
                                                          {"hourly", "apparent_temperature"},
                                                          {"hourly", "temperature_2m"},
                                                          {"hourly", "visibility"},
                                                          {"hourly", "precipitation"},
                                                          {"hourly", "relativehumidity_2m"},
                                                          {"hourly", "weathercode"},
                                                          {"hourly", "windspeed_10m"}
                                          });

        nlohmann::json json_text = nlohmann::json::parse(response.text);

        std::string date = json_text["current_weather"]["time"];
        int cur_time = std::stoi(date.substr(11, 2)) + 3;
        city.cur_info_ = GetInfo(json_text, cur_time);

        for (size_t i = 0; i < config.days_count_; i++) {
            DailyInfo daily_info;
            daily_info.morning = GetInfo(json_text, 5 + 24*i);
            daily_info.noon = GetInfo(json_text, 11 + 24*i);
            daily_info.evening = GetInfo(json_text, 17 + 24*i);
            daily_info.night = GetInfo(json_text, 23 + 24*i);

            city.info_.emplace_back(daily_info);
        }
    }
}

void forecast::GetConfig() {
    std::ifstream f("../config/config.csv");
    noskipws(f);
    char c;
    std::string string_config;
    while (f >> c) {
        string_config += c;
    }
    nlohmann::json json_config = nlohmann::json::parse(string_config);

    config.days_count_ = json_config["days"];
    config.frequency_ = json_config["frequency"];
    for (const auto& name : json_config["cities"]) {
        config.cities_.emplace_back(name);
    }
}

void forecast::WeatherDescription(std::string& des, int& code) {
    switch (code) {
        case 0:
            des = "Clear sky        ";
            code = 0;
            break;
        case 1:
        case 2:
        case 3:
            des = "Mainly clear     ";
            code = 1;
            break;
        case 45:
        case 48:
            des = "Fog              ";
            code = 2;
            break;
        case 51:
        case 53:
        case 55:
            des = "Drizzle          ";
            code = 3;
            break;
        case 56:
        case 57:
            des = "Freezing Drizzle ";
            code = 4;
            break;
        case 61:
        case 63:
        case 65:
            des = "Rain             ";
            code = 5;
            break;
        case 66:
        case 67:
            des = "Freezing Rain    ";
            code = 6;
            break;
        case 71:
        case 73:
        case 75:
            des = "Snow fall        ";
            code = 7;
            break;
        case 77:
            des = "Snow grains      ";
            code = 8;
            break;
        case 80:
        case 81:
        case 82:
        case 85:
        case 86:
            des = "Snow showers     ";
            code = 9;
            break;
        case 96:
        case 99:
            des = "Thunderstorm     ";
            code = 10;
            break;
        default:
            code = 11;
            break;
    }
}

void forecast::GetMonth(std::string& month) {
    int num = stoi(month);
    if (num == 1) {
        month = "Jan.";
    } else if (num == 2) {
        month = "Feb.";
    } else if (num == 3) {
        month = "Mar.";
    } else if (num == 4) {
        month = "Apr.";
    } else if (num == 5) {
        month = "May.";
    } else if (num == 6) {
        month = "Jun.";
    } else if (num == 7) {
        month = "Jul.";
    } else if (num == 8) {
        month = "Aug.";
    } else if (num == 9) {
        month = "Sep.";
    } else if (num == 10) {
        month = "Oct.";
    } else if (num == 11) {
        month = "Nov.";
    } else {
        month = "Dec.";
    }
}



