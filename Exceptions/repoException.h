//
// Created by tuddy on 20-May-22.
//

#ifndef POO2022_VALDIATION_3LAYER_REPO_EXCEPTION_H
#define POO2022_VALDIATION_3LAYER_REPO_EXCEPTION_H


#include "customException.h"

class repoException: public customException {
public:
    repoException(const char *string) : customException(string) {}
};


#endif //POO2022_VALDIATION_3LAYER_REPO_EXCEPTION_H
