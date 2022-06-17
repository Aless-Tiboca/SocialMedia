#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <sstream>
#include <iomanip>
#include "TAD/Array.h"
#include "../Exceptions/domainException.h"

using namespace std;

inline Array<string> splitWithDelim(const string &s, char delim) {
    Array<string> result;
    stringstream ss (s);
    string item;

    while (getline (ss, item, delim)) {
        result.pushBack (item);
    }

    return result;
}

inline bool compareDates(string a, string b){
    tm tm;
    istringstream ss(a);
    ss >> get_time(&tm, "%d/%m/%Y %H:%M:%S");
    if (ss.fail()) {
        throw domainException("Parse failed");
    }
    time_t time1 = mktime(&tm);
    ss.clear();
    ss.str(b);
    ss >> get_time(&tm, "%d/%m/%Y %H:%M:%S");
    if (ss.fail()) {
        throw domainException("Parse failed");
    }
    time_t time2 = mktime(&tm);

    return time1<time2;
}
template <class T>
inline int binarySearch(Array<T> arr, T entity){
    int mid, beg = 0, end = arr.getSize() - 1;
    while ( beg <= end)
    {
        mid = (beg + end) / 2;
        if (arr[mid] == entity)
        {
            return mid;
        }
        else if (arr[mid] > entity)
        {
            end = mid - 1;
        }
        else if (arr[mid] < entity)
        {
            beg = mid + 1;
        }
    }
// If the element does not exist in the array, return -1.
    return -1;
}


#endif