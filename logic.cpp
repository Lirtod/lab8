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

std::string bestTime(Runner a[], int n) {
    int best = a[0].time;

    for (int i = 1; i < n; i++) {
        if (a[i].time < best) best = a[i].time;
    }

    int h = best / 3600;
    int m = (best % 3600) / 60;
    int s = best % 60;

    std::string res;

    if (h < 10) res += "0";
    res += std::to_string(h) + ":";

    if (m < 10) res += "0";
    res += std::to_string(m) + ":";

    if (s < 10) res += "0";
    res += std::to_string(s);

    return res;
}
