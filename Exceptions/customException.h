//
// Created by tuddy on 20-May-22.
//

#ifndef POO2022_VALDIATION_3LAYER_CUSTOM_EXCEPTION_H
#define POO2022_VALDIATION_3LAYER_CUSTOM_EXCEPTION_H

#include <stdexcept>

class customException: public std::exception {
private:
    const char *message;
public:
    /**
     * Constructor
     */
    customException(const char *message) : message(message) {}

    /**
     * Getter for exception message
     */
    const char *what() const noexcept override {
        return message;
    }
};


#endif //POO2022_VALDIATION_3LAYER_CUSTOM_EXCEPTION_H
