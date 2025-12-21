#include "train.h"
#include <vector>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <limits>
#include <ctime>

bool IsEmptyFile(std::ifstream& file) {
    return file.peek() == std::ifstream::traits_type::eof();
}

std::vector<Train> loadTrainsFromFile(const std::string& filename) {
    std::vector<Train> trains;
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error: Cannot open file " << filename << std::endl;
        return trains;
    }

    if (IsEmptyFile(file)) {
        std::cerr << "Error: File " << filename << " is empty" << std::endl;
        return trains;
    }

    std::string line;
    while (std::getline(file, line)) {
        if (!line.empty()) {
            try {
                Train train = Train::fromString(line);
                trains.push_back(train);
            } catch (const std::exception& e) {
                std::cerr << "Error reading line: " << line << std::endl;
                std::cerr << "Reason: " << e.what() << std::endl;
            }
        }
    }

    file.close();
    return trains;
}

void printTableHeader() {
    std::cout << std::left << std::setw(8) << "ID" << std::setw(15) << "Type" << std::setw(25)
              << "Destination" << std::setw(12) << "Dispatch" << std::setw(12) << "Travel"
              << std::endl;
    std::cout << std::string(72, '-') << std::endl;
}

std::time_t parseTime(const std::string& time_str) {
    size_t colon_pos = time_str.find(':');
    if (colon_pos == std::string::npos) {
        throw std::invalid_argument("Invalid time format. Expected HH:MM");
    }

    int hours = std::stoi(time_str.substr(0, colon_pos));
    int minutes = std::stoi(time_str.substr(colon_pos + 1));

    if (hours < 0 || hours > 23) {
        throw std::invalid_argument("Hours must be in range 0-23");
    }
    if (minutes < 0 || minutes > 59) {
        throw std::invalid_argument("Minutes must be in range 0-59");
    }

    return SetTime(hours, minutes);
}

std::string formatTravelTime(std::time_t travel_time) {
    std::tm* tm = std::localtime(&travel_time);
    if (tm == nullptr) {
        return "N/A";
    }

    int hours = tm->tm_hour;
    int minutes = tm->tm_min;

    std::ostringstream oss;
    oss << hours << " hours " << std::setw(2) << std::setfill('0') << minutes << " minutes";
    return oss.str();
}

int main() {
    std::cout << "=== Train Management System ===" << std::endl;
    std::cout << std::endl;

    std::cout << "1. Loading train data from file..." << std::endl;
    std::vector<Train> trains = loadTrainsFromFile("trains.txt");

    if (trains.empty()) {
        std::cout << "File is empty or contains no valid data." << std::endl;
        return 1;
    }

    std::cout << "Loaded " << trains.size() << " trains." << std::endl;
    std::cout << std::endl;

    std::cout << "2. Sorting trains by dispatch time..." << std::endl;
    std::sort(trains.begin(), trains.end());

    std::cout << "Sorting result:" << std::endl;
    printTableHeader();
    for (const auto& train : trains) {
        train.print();
    }
    std::cout << std::endl;

    std::cout << "3. Finding trains in specified time range" << std::endl;
    std::cout << "Enter start time (HH:MM): ";
    std::string start_time_str;
    std::cin >> start_time_str;

    std::cout << "Enter end time (HH:MM): ";
    std::string end_time_str;
    std::cin >> end_time_str;

    try {
        std::time_t start_time = parseTime(start_time_str);
        std::time_t end_time = parseTime(end_time_str);

        if (start_time > end_time) {
            std::swap(start_time, end_time);
            std::swap(start_time_str, end_time_str);
        }

        std::vector<Train> trains_in_range;
        for (const auto& train : trains) {
            if (train.getDispatchTime() >= start_time && train.getDispatchTime() <= end_time) {
                trains_in_range.push_back(train);
            }
        }

        std::cout << std::endl;
        std::cout << "Trains in time range " << start_time_str << " - " << end_time_str << ":" << std::endl;
        if (trains_in_range.empty()) {
            std::cout << "No trains found." << std::endl;
        } else {
            printTableHeader();
            for (const auto& train : trains_in_range) {
                train.print();
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    std::cout << std::endl;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "4. Finding trains by destination" << std::endl;
    std::cout << "Enter destination: ";
    std::string destination;
    std::getline(std::cin, destination);

    std::vector<Train> trains_to_destination;
    for (const auto& train : trains) {
        if (train.getDestination() == destination) {
            trains_to_destination.push_back(train);
        }
    }

    std::cout << std::endl;
    std::cout << "Trains to " << destination << ":" << std::endl;
    if (trains_to_destination.empty()) {
        std::cout << "No trains found." << std::endl;
    } else {
        printTableHeader();
        for (const auto& train : trains_to_destination) {
            train.print();
        }
    }
    std::cout << std::endl;

    std::cout << "5. Finding trains by type and destination" << std::endl;
    std::cout
        << "Enter train type (0-PASSENGER, 1-FREIGHT, 2-HIGH_SPEED, 3-SUBWAY, 4-SPECIALIZED): ";
    int type_int;
    std::cin >> type_int;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Enter destination: ";
    std::getline(std::cin, destination);

    TrainType type = static_cast<TrainType>(type_int);
    std::vector<Train> trains_by_type_and_destination;

    for (const auto& train : trains) {
        if (train.getType() == type && train.getDestination() == destination) {
            trains_by_type_and_destination.push_back(train);
        }
    }

    std::cout << std::endl;
    std::cout << "Trains of type " << type_int << " to " << destination << ":" << std::endl;
    if (trains_by_type_and_destination.empty()) {
        std::cout << "No trains found." << std::endl;
    } else {
        printTableHeader();
        for (const auto& train : trains_by_type_and_destination) {
            train.print();
        }
    }
    std::cout << std::endl;

    std::cout << "6. Finding fastest train to destination" << std::endl;
    std::cout << "Enter destination: ";
    std::getline(std::cin, destination);

    std::vector<Train> fastest_candidates;
    for (const auto& train : trains) {
        if (train.getDestination() == destination) {
            fastest_candidates.push_back(train);
        }
    }

    if (fastest_candidates.empty()) {
        std::cout << "No trains to " << destination << " found." << std::endl;
    } else {
        auto fastest_train =
            *std::min_element(fastest_candidates.begin(), fastest_candidates.end(),
                              [](const Train& a, const Train& b) {
                                  return a.getTravellingTime() < b.getTravellingTime();
                              });

        std::cout << std::endl;
        std::cout << "Fastest train to " << destination << ":" << std::endl;
        printTableHeader();
        fastest_train.print();

        std::cout << "Travel time: " << formatTravelTime(fastest_train.getTravellingTime()) << std::endl;
    }

    std::cout << std::endl;
    std::cout << "=== Program finished ===" << std::endl;

    return 0;
}
