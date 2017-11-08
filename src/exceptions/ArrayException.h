/*!
    \author dkuleshov3 
    \date 08.11.2017
*/

#pragma once

#include "TDepoException.h"

class ArrayException: public TDepoException
{
    public:
        explicit ArrayException(std::wstring text);
        ~ArrayException();
};