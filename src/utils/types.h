//
// Created by Spark on 02/05/2019.
//

#ifndef DREAMINENGINE_TYPES_H
#define DREAMINENGINE_TYPES_H

#include <typeindex>

typedef std::type_index TypeIndex;

template<typename T>
inline TypeIndex getTypeIndex()
{
    return std::type_index(typeid(T));
}

#endif //DREAMINENGINE_TYPES_H
