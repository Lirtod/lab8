#include <iostream>
#include <fstream>
#include <string>

struct Runner {
    int number;
    std::string last;
    std::string first;
    std::string middle;
    std::string start;
    std::string finish;
    std::string club;
    int time;
};

int toSeconds(std::string t);
std::string bestTime(Runner a[], int n);

int main() {
    std::ifstream file("input.txt");
    Runner a[100];
    int n = 0;

    while (file >> a[n].number >> a[n].last >> a[n].first >> a[n].middle >> a[n].start >> a[n].finish) {
        std::getline(file, a[n].club);
        if (!a[n].club.empty() && a[n].club[0] == ' ')
            a[n].club.erase(0, 1);

        int st = toSeconds(a[n].start);
        int fn = toSeconds(a[n].finish);
        a[n].time = fn - st;

        n++;
    }

    std::cout << bestTime(a, n) << std::endl;

    return 0;
}
