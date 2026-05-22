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

int toSeconds(std::string t) {
    int h = (t[0]-'0')*10 + (t[1]-'0');
    int m = (t[3]-'0')*10 + (t[4]-'0');
    int s = (t[6]-'0')*10 + (t[7]-'0');
    return h*3600 + m*60 + s;
}

void print(Runner a[], int n) {
    for (int i = 0; i < n; i++) {
        std::cout << a[i].number << " " << a[i].last << " " << a[i].first << " " << a[i].middle << " " << a[i].time << " " << a[i].club << std::endl;
    }
}

void bubbleTime(Runner a[], int n) {
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (a[j].time > a[j+1].time) {
                Runner t = a[j];
                a[j] = a[j+1];
                a[j+1] = t;
            }
        }
    }
}

bool cmpClub(Runner a, Runner b) {
    if (a.club == b.club) return a.last > b.last;
    return a.club > b.club;
}

void bubbleClub(Runner a[], int n) {
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (cmpClub(a[j], a[j+1])) {
                Runner t = a[j];
                a[j] = a[j+1];
                a[j+1] = t;
            }
        }
    }
}

int partitionTime(Runner a[], int l, int r) {
    int pivot = a[r].time;
    int i = l - 1;
    for (int j = l; j < r; j++) {
        if (a[j].time < pivot) {
            i++;
            Runner t = a[i];
            a[i] = a[j];
            a[j] = t;
        }
    }
    Runner t = a[i+1];
    a[i+1] = a[r];
    a[r] = t;
    return i+1;
}

void quickTime(Runner a[], int l, int r) {
    if (l < r) {
        int p = partitionTime(a, l, r);
        quickTime(a, l, p-1);
        quickTime(a, p+1, r);
    }
}

int partitionClub(Runner a[], int l, int r) {
    Runner pivot = a[r];
    int i = l - 1;
    for (int j = l; j < r; j++) {
        if (!cmpClub(a[j], pivot)) {
            i++;
            Runner t = a[i];
            a[i] = a[j];
            a[j] = t;
        }
    }
    Runner t = a[i+1];
    a[i+1] = a[r];
    a[r] = t;
    return i+1;
}

void quickClub(Runner a[], int l, int r) {
    if (l < r) {
        int p = partitionClub(a, l, r);
        quickClub(a, l, p-1);
        quickClub(a, p+1, r);
    }
}

int main() {
    std::ifstream file("input.txt");
    Runner a[100];
    int n = 0;

    while (file >> a[n].number >> a[n].last >> a[n].first >> a[n].middle >> a[n].start >> a[n].finish) {
        std::getline(file, a[n].club);
        if (a[n].club.size() > 0 && a[n].club[0] == ' ') a[n].club.erase(0,1);
        int st = toSeconds(a[n].start);
        int fn = toSeconds(a[n].finish);
        a[n].time = fn - st;
        n++;
    }

    std::cout << "Spartak:" << std::endl;
    for (int i = 0; i < n; i++) {
        if (a[i].club == "Спартак") {
            std::cout << a[i].number << " " << a[i].last << " " << a[i].time << std::endl;
        }
    }

    int limit = 2*3600 + 50*60;

    std::cout << "Better than 2:50:00:" << std::endl;
    for (int i = 0; i < n; i++) {
        if (a[i].time < limit) {
            std::cout << a[i].number << " " << a[i].last << " " << a[i].time << std::endl;
        }
    }

    Runner b[100];
    for (int i = 0; i < n; i++) b[i] = a[i];

    bubbleTime(b, n);
    std::cout << "Bubble sort by time:" << std::endl;
    print(b, n);

    for (int i = 0; i < n; i++) b[i] = a[i];
    quickTime(b, 0, n-1);
    std::cout << "Quick sort by time:" << std::endl;
    print(b, n);

    for (int i = 0; i < n; i++) b[i] = a[i];
    bubbleClub(b, n);
    std::cout << "Bubble sort by club+last:" << std::endl;
    print(b, n);

    for (int i = 0; i < n; i++) b[i] = a[i];
    quickClub(b, 0, n-1);
    std::cout << "Quick sort by club+last:" << std::endl;
    print(b, n);

    return 0;
}
