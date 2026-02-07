#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <iomanip>
#include <sstream>
#include <numeric>

struct Mark {
    std::string subject_;
    size_t mark_;
};

struct StudentData {
    std::string name_;
    size_t number_;
    std::vector<Mark> marks_;
    
    double getAverage() const {
        if (marks_.empty()) return 0.0;
        double sum = 0.0;
        for (const auto& mark : marks_) {
            sum += mark.mark_;
        }
        return sum / marks_.size();
    }
    
    size_t getTotal() const {
        size_t sum = 0;
        for (const auto& mark : marks_) {
            sum += mark.mark_;
        }
        return sum;
    }
    
    bool hasSubject(const std::string& subject) const {
        for (const auto& mark : marks_) {
            if (mark.subject_ == subject) {
                return true;
            }
        }
        return false;
    }
    
    bool hasUnsatisfactory() const {
        for (const auto& mark : marks_) {
            if (mark.mark_ >= 1 && mark.mark_ <= 3) {
                return true;
            }
        }
        return false;
    }
};

bool IsEmptyFile(std::ifstream& file) {
    return file.peek() == std::ifstream::traits_type::eof();
}

class StudentManager {
private:
    std::map<size_t, StudentData> students_;
    
public:
    bool loadFromFile(const std::string& filename) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Error opening file: " << filename << std::endl;
            return false;
        }
        
        if (IsEmptyFile(file)) {
            std::cerr << "File is empty: " << filename << std::endl;
            file.close();
            return false;
        }
        
        std::string line;
        while (std::getline(file, line)) {
            if (line.empty()) continue;
            
            StudentData student;
            student.name_ = line;
            
            if (!std::getline(file, line)) break;
            std::istringstream iss(line);
            iss >> student.number_;
            
            while (std::getline(file, line) && !line.empty()) {
                std::istringstream markStream(line);
                Mark mark;
                markStream >> mark.subject_ >> mark.mark_;
                student.marks_.push_back(mark);
            }
            
            students_[student.number_] = student;
        }
        
        file.close();
        std::cout << "Data loaded from file: " << filename << std::endl;
        return true;
    }
    
    void printSortedByNumber() {
        std::cout << "\n=== Students sorted by record book number ===\n";
        std::cout << std::left << std::setw(30) << "Name" 
                  << std::setw(15) << "Record book #" 
                  << "Subjects and marks" << std::endl;
        std::cout << std::string(80, '-') << std::endl;
        
        for (const auto& [number, student] : students_) {
            std::cout << std::left << std::setw(30) << student.name_
                      << std::setw(15) << student.number_;
            
            for (const auto& mark : student.marks_) {
                std::cout << mark.subject_ << ":" << mark.mark_ << " ";
            }
            std::cout << std::endl;
        }
    }
    
    void printAverages() {
        std::cout << "\n=== Average mark for each student ===\n";
        std::cout << std::left << std::setw(30) << "Name" 
                  << std::setw(15) << "Record book #" 
                  << std::setw(10) << "Average" << std::endl;
        std::cout << std::string(60, '-') << std::endl;
        
        for (const auto& [number, student] : students_) {
            double average = student.getAverage();
            std::cout << std::left << std::setw(30) << student.name_
                      << std::setw(15) << student.number_
                      << std::fixed << std::setprecision(2) << average << std::endl;
        }
    }
    
    void printSortedByName() {
        std::cout << "\n=== Students sorted alphabetically ===\n";
        std::cout << std::left << std::setw(5) << "No" 
                  << std::setw(30) << "Name" 
                  << std::setw(15) << "Record book #" 
                  << std::setw(12) << "Average" << std::endl;
        std::cout << std::string(67, '-') << std::endl;
        
        std::vector<std::pair<size_t, StudentData>> sortedStudents;
        for (const auto& item : students_) {
            sortedStudents.push_back(item);
        }
        
        std::sort(sortedStudents.begin(), sortedStudents.end(),
            [](const auto& a, const auto& b) {
                if (a.second.name_ == b.second.name_) {
                    return a.second.getAverage() > b.second.getAverage();
                }
                return a.second.name_ < b.second.name_;
            });
        
        size_t counter = 1;
        for (const auto& [number, student] : sortedStudents) {
            std::cout << std::left << std::setw(5) << counter++
                      << std::setw(30) << student.name_
                      << std::setw(15) << student.number_
                      << std::fixed << std::setprecision(2) << student.getAverage() << std::endl;
        }
    }
    
    void printStudentsByAverageRange(double minAvg, double maxAvg) {
        std::cout << "\n=== Students with average in range [" 
                  << minAvg << ", " << maxAvg << "] ===\n";
        
        std::vector<std::pair<size_t, StudentData>> filteredStudents;
        for (const auto& item : students_) {
            double avg = item.second.getAverage();
            if (avg >= minAvg && avg <= maxAvg) {
                filteredStudents.push_back(item);
            }
        }
        
        std::sort(filteredStudents.begin(), filteredStudents.end(),
            [](const auto& a, const auto& b) {
                return a.second.getAverage() > b.second.getAverage();
            });
        
        if (filteredStudents.empty()) {
            std::cout << "No students found in this range." << std::endl;
            return;
        }
        
        std::cout << std::left << std::setw(30) << "Name" 
                  << std::setw(15) << "Record book #" 
                  << std::setw(12) << "Average" << std::endl;
        std::cout << std::string(62, '-') << std::endl;
        
        for (const auto& [number, student] : filteredStudents) {
            std::cout << std::left << std::setw(30) << student.name_
                      << std::setw(15) << student.number_
                      << std::fixed << std::setprecision(2) << student.getAverage() << std::endl;
        }
    }
    
    void printStudentsBySubject(const std::string& subject) {
        std::cout << "\n=== Students who took subject: " << subject << " ===\n";
        
        std::vector<std::pair<size_t, StudentData>> result;
        for (const auto& item : students_) {
            if (item.second.hasSubject(subject)) {
                result.push_back(item);
            }
        }
        
        if (result.empty()) {
            std::cout << "No students found for this subject." << std::endl;
            return;
        }
        
        std::cout << std::left << std::setw(30) << "Name" 
                  << std::setw(15) << "Record book #" 
                  << "Mark" << std::endl;
        std::cout << std::string(70, '-') << std::endl;
        
        for (const auto& [number, student] : result) {
            std::cout << std::left << std::setw(30) << student.name_
                      << std::setw(15) << student.number_;
            
            for (const auto& mark : student.marks_) {
                if (mark.subject_ == subject) {
                    std::cout << mark.mark_;
                    break;
                }
            }
            std::cout << std::endl;
        }
    }
    
    void printSubjectStatistics() {
        std::cout << "\n=== Subject statistics ===\n";
        std::cout << "Number of students per subject:\n";
        
        std::map<std::string, size_t> subjectCount;
        
        for (const auto& [number, student] : students_) {
            for (const auto& mark : student.marks_) {
                subjectCount[mark.subject_]++;
            }
        }
        
        if (subjectCount.empty()) {
            std::cout << "No subject data." << std::endl;
            return;
        }
        
        std::cout << std::left << std::setw(20) << "Subject" 
                  << "Students count" << std::endl;
        std::cout << std::string(40, '-') << std::endl;
        
        for (const auto& [subject, count] : subjectCount) {
            std::cout << std::left << std::setw(20) << subject 
                      << count << std::endl;
        }
    }
    
    void printSubjectAverages() {
        std::cout << "\n=== Average marks per subject ===\n";
        
        std::map<std::string, std::pair<double, size_t>> subjectStats;
        
        for (const auto& [number, student] : students_) {
            for (const auto& mark : student.marks_) {
                subjectStats[mark.subject_].first += mark.mark_;
                subjectStats[mark.subject_].second++;
            }
        }
        
        if (subjectStats.empty()) {
            std::cout << "No subject data." << std::endl;
            return;
        }
        
        std::vector<std::pair<std::string, double>> subjectAverages;
        for (const auto& [subject, stats] : subjectStats) {
            double average = stats.first / stats.second;
            subjectAverages.emplace_back(subject, average);
        }
        
        std::sort(subjectAverages.begin(), subjectAverages.end(),
            [](const auto& a, const auto& b) {
                return a.second > b.second;
            });
        
        std::cout << std::left << std::setw(20) << "Subject" 
                  << "Average" << std::endl;
        std::cout << std::string(35, '-') << std::endl;
        
        for (const auto& [subject, average] : subjectAverages) {
            std::cout << std::left << std::setw(20) << subject 
                      << std::fixed << std::setprecision(2) << average << std::endl;
        }
    }
    
    void printStudentsWithMaxTotal() {
        std::cout << "\n=== Students with maximum total marks ===\n";
        
        if (students_.empty()) {
            std::cout << "No student data." << std::endl;
            return;
        }
        
        size_t maxTotal = 0;
        for (const auto& [number, student] : students_) {
            size_t total = student.getTotal();
            if (total > maxTotal) {
                maxTotal = total;
            }
        }
        
        std::vector<std::pair<size_t, StudentData>> topStudents;
        for (const auto& item : students_) {
            if (item.second.getTotal() == maxTotal) {
                topStudents.push_back(item);
            }
        }
        
        std::cout << "Maximum total marks: " << maxTotal << std::endl;
        std::cout << "Number of students: " << topStudents.size() << std::endl;
        
        std::cout << std::left << std::setw(30) << "Name" 
                  << std::setw(15) << "Record book #" 
                  << std::setw(15) << "Total marks" 
                  << std::setw(12) << "Average" << std::endl;
        std::cout << std::string(77, '-') << std::endl;
        
        for (const auto& [number, student] : topStudents) {
            std::cout << std::left << std::setw(30) << student.name_
                      << std::setw(15) << student.number_
                      << std::setw(15) << student.getTotal()
                      << std::fixed << std::setprecision(2) << student.getAverage() << std::endl;
        }
    }
    
    void printStudentsWithUnsatisfactory() {
        std::cout << "\n=== Students with unsatisfactory marks (1-3) ===\n";
        
        std::vector<std::pair<size_t, StudentData>> unsatisfactoryStudents;
        for (const auto& item : students_) {
            if (item.second.hasUnsatisfactory()) {
                unsatisfactoryStudents.push_back(item);
            }
        }
        
        if (unsatisfactoryStudents.empty()) {
            std::cout << "No students with unsatisfactory marks." << std::endl;
            return;
        }
        
        std::cout << "Number of students: " << unsatisfactoryStudents.size() << std::endl;
        
        std::cout << std::left << std::setw(30) << "Name" 
                  << std::setw(15) << "Record book #" 
                  << "Unsatisfactory marks" << std::endl;
        std::cout << std::string(80, '-') << std::endl;
        
        for (const auto& [number, student] : unsatisfactoryStudents) {
            std::cout << std::left << std::setw(30) << student.name_
                      << std::setw(15) << student.number_;
            
            bool first = true;
            for (const auto& mark : student.marks_) {
                if (mark.mark_ >= 1 && mark.mark_ <= 3) {
                    if (!first) std::cout << ", ";
                    std::cout << mark.subject_ << ":" << mark.mark_;
                    first = false;
                }
            }
            std::cout << std::endl;
        }
    }
    
    size_t getStudentCount() const {
        return students_.size();
    }
};

void createTestFile(const std::string& filename) {
    std::ofstream file(filename);
    file << "Иванов И.И.\n";
    file << "1001\n";
    file << "Mathematics 8\n";
    file << "Physics 7\n";
    file << "Informatics 9\n";
    file << "\n";
    
    file << "Петров П.П.\n";
    file << "1003\n";
    file << "Mathematics 4\n";
    file << "Physics 6\n";
    file << "Chemistry 8\n";
    file << "\n";
    
    file << "Сидоров С.С.\n";
    file << "1002\n";
    file << "Mathematics 7\n";
    file << "Physics 9\n";
    file << "Informatics 7\n";
    file << "Chemistry 6\n";
    file << "\n";
    
    file << "Алексеев А.А.\n";
    file << "1004\n";
    file << "Mathematics 3\n";
    file << "Physics 4\n";
    file << "Informatics 5\n";
    file << "\n";
    
    file << "Иванов И.И.\n";
    file << "1005\n";
    file << "Mathematics 9\n";
    file << "Physics 9\n";
    file << "Informatics 10\n";
    
    file.close();
    std::cout << "Test file created: " << filename << std::endl;
}

int main() {
    StudentManager manager;
    
    std::string filename = "students.txt";
    createTestFile(filename);
    
    if (!manager.loadFromFile(filename)) {
        std::cerr << "Failed to load data. Program terminated." << std::endl;
        return 1;
    }
    
    manager.printSortedByNumber();
    manager.printAverages();
    manager.printSortedByName();
    manager.printStudentsByAverageRange(6.0, 8.0);
    manager.printStudentsBySubject("Informatics");
    manager.printSubjectStatistics();
    manager.printSubjectAverages();
    manager.printStudentsWithMaxTotal();
    manager.printStudentsWithUnsatisfactory();
    
    std::cout << "\nTotal students in database: " << manager.getStudentCount() << std::endl;
    
    return 0;
}
