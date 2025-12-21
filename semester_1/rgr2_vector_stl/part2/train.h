#pragma once

#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include "time_utility.h"

using TrainId = size_t;
using namespace time_utility;

enum class TrainType { PASSENGER = 0, FREIGHT = 1, HIGH_SPEED = 2, SUBWAY = 3, SPECIALIZED = 4 };

class Train {
private:
    TrainId id_;
    TrainType type_;
    std::string destination_;
    std::time_t dispatch_time_;
    std::time_t travelling_time_;

    static std::string formatTime(std::time_t time) {
        std::tm* tm = std::localtime(&time);
        if (tm == nullptr) {
            return "N/A";
        }
        char buffer[6];
        std::strftime(buffer, sizeof(buffer), "%H:%M", tm);
        return std::string(buffer);
    }

public:
    Train() : id_(0), type_(TrainType::PASSENGER), dispatch_time_(0), travelling_time_(0) {
    }

    Train(TrainId id, TrainType type, const std::string& destination, std::time_t dispatch_time,
          std::time_t travelling_time)
        : id_(id),
          type_(type),
          destination_(destination),
          dispatch_time_(dispatch_time),
          travelling_time_(travelling_time) {
    }

    TrainId getId() const {
        return id_;
    }
    TrainType getType() const {
        return type_;
    }
    std::string getDestination() const {
        return destination_;
    }
    std::time_t getDispatchTime() const {
        return dispatch_time_;
    }
    std::time_t getTravellingTime() const {
        return travelling_time_;
    }

    static Train fromString(const std::string& str) {
        std::istringstream iss(str);
        TrainId id;
        int type_int;
        std::string destination;
        std::string dispatch_str, travel_str;

        iss >> id >> type_int >> destination >> dispatch_str >> travel_str;

        size_t colon_pos = dispatch_str.find(':');
        if (colon_pos == std::string::npos) {
            throw std::invalid_argument("Invalid dispatch time format");
        }
        int dispatch_hours = std::stoi(dispatch_str.substr(0, colon_pos));
        int dispatch_minutes = std::stoi(dispatch_str.substr(colon_pos + 1));
        std::time_t dispatch_time = SetTime(dispatch_hours, dispatch_minutes);

        colon_pos = travel_str.find(':');
        if (colon_pos == std::string::npos) {
            throw std::invalid_argument("Invalid travel time format");
        }
        int travel_hours = std::stoi(travel_str.substr(0, colon_pos));
        int travel_minutes = std::stoi(travel_str.substr(colon_pos + 1));
        std::time_t travel_time = SetTime(travel_hours, travel_minutes);

        TrainType type = static_cast<TrainType>(type_int);

        return Train(id, type, destination, dispatch_time, travel_time);
    }

    void print() const {
        std::string type_str;
        switch (type_) {
            case TrainType::PASSENGER:
                type_str = "PASSENGER";
                break;
            case TrainType::FREIGHT:
                type_str = "FREIGHT";
                break;
            case TrainType::HIGH_SPEED:
                type_str = "HIGH_SPEED";
                break;
            case TrainType::SUBWAY:
                type_str = "SUBWAY";
                break;
            case TrainType::SPECIALIZED:
                type_str = "SPECIALIZED";
                break;
            default:
                type_str = "UNKNOWN";
        }

        std::string dispatch_str = formatTime(dispatch_time_);
        std::string travel_str = formatTime(travelling_time_);

        std::cout << std::left << std::setw(8) << id_ << std::setw(15) << type_str << std::setw(25)
                  << destination_ << std::setw(12) << dispatch_str << std::setw(12) << travel_str
                  << std::endl;
    }

    bool operator<(const Train& other) const {
        return dispatch_time_ < other.dispatch_time_;
    }
};
