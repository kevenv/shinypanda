/**
    @file IDs.h
    @author Vincent Girard <vin100_jrare@hotmail.com>
    @version 1.0

    @section LICENSE



    @section DESCRIPTION

    This file contains an enum of the ID for object.
*/
#ifndef SPE_IDS_H
#define SPE_IDS_H

namespace spe
{
/**
    @enum ID
    @brief The ID for each object.
    This enum is there to make sure that no ID are used twice and to simplify the verification process.
    It must contains only distincts prime numbers as values.
*/
enum class ID
{
    MOVING_OBJECT = 2,
    CHARACTER = 3,
    ENEMY = 5,
    PLAYER = 7,
    PANDA = 11,

};

}

#endif
