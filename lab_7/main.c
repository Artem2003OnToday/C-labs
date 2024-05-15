#include <math.h>
#include <stdbool.h>
#include <stdio.h>

enum DayOfWeek {
    kMonday = 1,
    kTuesday,
    kWednesday,
    kThursday,
    kFriday,
    kSaturday,
    kSunday
};

const char* ToString(enum DayOfWeek dow) {
    switch (dow) {
        case kMonday:
            return "monday";
        case kTuesday:
            return "tuesaday";
        case kWednesday:
            return "wednesday";
        case kThursday:
            return "thursday";
        case kFriday:
            return "friday";
        case kSaturday:
            return "saturday";
        case kSunday:
            return "sunday";
    }
}

struct Point {
    double x, y;
};

struct Rectangle {
    struct Point a, b;
};

double get_square(struct Rectangle rect) {
    return fabs(rect.a.x - rect.b.x) * fabs(rect.a.y - rect.b.y);
}

union DeviceState {
    struct {
        bool play : 1;
        bool pause : 1;
        bool record : 1;
    } status;
    unsigned int state;
};

int main() {
    { // 1
        printf("%s\n", ToString(kMonday));
    }
    { // 2
        struct Rectangle r;
        r.a.x = 0; r.a.y = 0;
        r.b.x = 5; r.b.y = 5;
        printf("%f\n", get_square(r)); // 25
    }
    { // 3
        union DeviceState device;
        scanf("%d", &device.state);

        printf("Device status:\n");
        printf("Play: %s\n", (device.status.play) ? "ON" : "OFF");
        printf("Pause: %s\n", (device.status.pause) ? "ON" : "OFF");
        printf("Record: %s\n", (device.status.record) ? "ON" : "OFF");
    }
}
