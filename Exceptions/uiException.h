//
// Created by tuddy on 20-May-22.
//

#ifndef POO2022_VALDIATION_3LAYER_UI_EXCEPTION_H
#define POO2022_VALDIATION_3LAYER_UI_EXCEPTION_H


#include "customException.h"

class uiException: public customException {
public:
    uiException(const char *string) : customException(string) {}
};


#endif //POO2022_VALDIATION_3LAYER_UI_EXCEPTION_H
