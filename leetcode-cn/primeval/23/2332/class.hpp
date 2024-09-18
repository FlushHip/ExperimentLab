#include "headers.h"

class Solution {
public:
    int latestTimeCatchTheBus(vector<int>& buses,
        vector<int>& passengers,
        int capacity) {
        std::sort(buses.begin(), buses.end());
        std::sort(passengers.begin(), passengers.end());
        // std::cout << std::tuple<std::vector<int>, std::vector<int>>(
        //                  buses, passengers)
        //           << std::endl;
        uint32_t passengerIndex = 0, singleBusPassengerCount = 0;
        for (int bus : buses) {
            singleBusPassengerCount = capacity;
            while (passengerIndex < passengers.size() &&
                passengers[passengerIndex] <= bus &&
                singleBusPassengerCount > 0) {
                ++passengerIndex;
                --singleBusPassengerCount;
            }
        }
        int lastIndex = --passengerIndex;
        int result =
            singleBusPassengerCount > 0 ? buses.back() : passengers[lastIndex];
        while (lastIndex >= 0 && passengers[lastIndex] == result) {
            --result;
            --lastIndex;
        }
        return result;
    }
};
