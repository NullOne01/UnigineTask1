#ifndef UNIGINETASK1_UTILS_H
#define UNIGINETASK1_UTILS_H

class Utils {
public:
    static constexpr double PI = 3.14159265359;

    static double degToRad(double degrees) {
        return degrees * (PI / 180);
    }
};

#endif //UNIGINETASK1_UTILS_H
