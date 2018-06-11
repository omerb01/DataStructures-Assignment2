//
// Created by Omer on 03/05/2018.
//

#include <exception>

#ifndef DATASTRUCTURES_HW1_EXCEPTIONS_H
#define DATASTRUCTURES_HW1_EXCEPTIONS_H

#define NEW_EXCEPTION(exp, from) \
    class exp : public from{\
    public: \
        virtual const char* what() const throw(){\
            return #exp;\
    }}

NEW_EXCEPTION(AVLTreeException, std::exception);
NEW_EXCEPTION(AVLElementNotFound, AVLTreeException);

NEW_EXCEPTION(HashTableException, std::exception);
NEW_EXCEPTION(HashElementNotFound, HashTableException);

NEW_EXCEPTION(MinHeapElementNotFound, std::exception);
NEW_EXCEPTION(MinHeapBadAlloc, std::exception);

NEW_EXCEPTION(OasisException, std::exception);
NEW_EXCEPTION(OasisInvalidInput, OasisException);
NEW_EXCEPTION(OasisFailure, OasisException);
NEW_EXCEPTION(OasisAlloctionFailure, OasisException);

#endif //DATASTRUCTURES_HW1_EXCEPTIONS_H
