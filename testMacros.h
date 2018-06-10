//
// Created by Omer on 06/05/2018.
//

#ifndef DATASTRUCTURES_HW1_TESTMACROS_H
#define DATASTRUCTURES_HW1_TESTMACROS_H

#include <exception>
#include <iostream>
#include <sstream>

using std::ostringstream;
using std::string;
using std::cout;
using std::cerr;
using std::endl;
using std::exception;

#define PRINT_ERROR(str) cerr << "Error in line: "  \
<< __LINE__ << ". Error is: " << (str) << "." << endl;

#define ASSERT_NO_EXCEPTION(t) \
    try{ \
        t; \
    } catch(const exception& e){ \
        PRINT_ERROR(string("Caught exception ") + e.what()); \
        return false; \
    }
#define ASSERT_EXCEPTION(t, exc) \
    try{ \
        t; \
        PRINT_ERROR("No exception"); \
        return false; \
    } catch(const exc& e){}catch(const exception& e){\
        PRINT_ERROR(string(" Wrong exception caught: ") + e.what());\
        return false; \
    }

#define ASSERT_TRUE(t) \
    try{ \
        if(!(t)){\
            PRINT_ERROR((string(#t) + " is false"));\
            return false;\
        } \
    } catch(const exception& e) { \
        PRINT_ERROR(string("Caught exception ") + e.what());\
        return false; \
    }

#define ASSERT_FALSE(t) \
    try{ \
        if(t){\
            PRINT_ERROR((string(#t) + " is true"));\
            return false;\
        } \
    } catch(const exception& e) { \
        PRINT_ERROR(string("Caught exception ") + e.what());\
        return false; \
    }

#define RUN_TEST(t) \
    try { \
        if(t()){ \
            cout << #t << ": has passed :)" << endl; \
        } else { \
            cerr << #t << " has failed :(" << endl;\
        } \
    } catch(const exception& e){ \
        cerr << #t << "has failed with exception: " << e.what(); \
        cerr <<endl;\
    } catch(...) {\
        cerr << #t << "has failed with unknown exception" << endl;\
    }

bool VerifyOutput(ostringstream& output, const string& expected_output){
    if(expected_output != output.str()){
        cerr << "\nExpected output:\n" << expected_output << endl;
        cerr << "\nActual Output:\n" << output.str() << endl;
        return false;
    }
    output.clear();
    output.str("");
    return true;
}

#endif //DATASTRUCTURES_HW1_TESTMACROS_H
