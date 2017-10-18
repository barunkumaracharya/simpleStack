//
//  main.cpp
//  stack
//
//  Created by Эльдар Дамиров on 11.10.2017.
//  Copyright © 2017 Эльдар Дамиров. All rights reserved.
//

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <functional>

#include <time.h>


#include "fileIO.h"



const int poisonInt = 12345678;
const double poisonDouble = NAN;
const float poisonFloat = NAN;
const char poisonChar = '~';





template <typename typeOfData> class stack
    {
    public:
        
        
        stack ( size_t newStackCapacity )
            {
            stackCapacity = newStackCapacity;
            init();
            }
        
        ~stack()
            {
            
            }
        

        
        typeOfData* getBeginningOfStack()
            {
            if ( beginningOfStack == nullptr )
                {
                printf ( "Stack isn't initialized, or some error during init has occured. (Note that returning value in this case isn't prorep one) ¯|_(ツ)_/¯ \n" );
                listOfErrors = listOfErrors + "In getBeginningOfStack: " + "Stack isn't initialized, or some error during init has occured. (Note that returning value in this case isn't prorep one) ¯|_(ツ)_/¯ \n";
                return nullptr;
                }
            return beginningOfStack;
            }
        
        typeOfData* getCurrentFreeElement()
            {
            if ( ( currentFreeElement == nullptr ) || ( currentFreeElement < beginningOfStack ) )
                {
                printf ( "Current free element is out of range or even hasn't been initialized, maybe something is wrong with stack pointer. (Note that returning value in this case isn't prorep one) ¯|_(ツ)_/¯ \n" );
                listOfErrors = listOfErrors + "In getCurrentFreeElement: " + "Current free element is out of range or even hasn't been initialized, maybe something is wrong with stack pointer. (Note that returning value in this case isn't prorep one) ¯|_(ツ)_/¯ \n";
                return nullptr;
                }
                
            return currentFreeElement;
            }
        
        size_t getStackCapacity()
            {
            if ( stackCapacity == 0 )
                {
                printf ( "Something is wrong with stack storage or stack capacity value hasn't been updated. ¯|_(ツ)_/¯ \n" );
                listOfErrors = listOfErrors + "In getStackCapacity: " + "Something is wrong with stack storage or stack capacity value hasn't been updated. ¯|_(ツ)_/¯ \n";
                return -1;
                }
                
            return stackCapacity;
            }
        
        int setBeginningOfStack ( typeOfData* newBeginningOfStack )
            {
            if ( newBeginningOfStack == nullptr )
                {
                printf ( "New beginning of stack is incorrect. (Note that returning value in this case isn't prorep one) ¯|_(ツ)_/¯ \n" );
                listOfErrors = listOfErrors + "In setBeginningOfStack: " + "New beginning of stack is incorrect. (Note that returning value in this case isn't prorep one) ¯|_(ツ)_/¯ \n";

                return -1;
                }
            
            beginningOfStack = newBeginningOfStack;
            
            return 0;
            }
        
        int setCurrentFreeElement ( typeOfData* newCurrentFreeElement )
            {
            if ( newCurrentFreeElement == nullptr )
                {
                printf ( "New current free element is incorrect. (Note that returning value in this case isn't prorep one) ¯|_(ツ)_/¯ \n" );
                listOfErrors = listOfErrors + "In setCurrentFreeElement: " + "New current free element is incorrect. (Note that returning value in this case isn't prorep one) ¯|_(ツ)_/¯ \n";

                return -1;
                }
                
            currentFreeElement = newCurrentFreeElement;
            
            return 0;
            }
        
        int setStackCapacity ( size_t newStackCapacity )
            {
            if ( newStackCapacity == 0 )
                {
                printf ( "Something is wrong with stack storage or stack capacity value hasn't been updated. ¯|_(ツ)_/¯ \n" );
                listOfErrors = listOfErrors + "In setStackCapacity: " + "Something is wrong with stack storage or stack capacity value hasn't been updated. ¯|_(ツ)_/¯ \n";
                return -1;
                }
                
            stackCapacity = newStackCapacity;
                
            return 0;
            }
        
        int push ( typeOfData elementToPush )
            {
            if ( currentFreeElement > ( beginningOfStack + ( stackCapacity - 1 ) ) )
                {
                printf ( "Bad access, trying to access element out of range. ¯|_(ツ)_/¯ \n" );
                listOfErrors = listOfErrors + "In PUSH: " + "Bad access, trying to access element out of range. ¯|_(ツ)_/¯ \n";
                return -1;
                }
            
            *currentFreeElement = elementToPush;
            currentFreeElement++;
            
            if ( ( currentFreeElement ) == ( beginningOfStack + ( stackCapacity - 1 ) ) )
                {
                enlargeStack();
                }
            
            return 0;
            }
        
        int clear()
            {
            if ( ( currentFreeElement == nullptr ) || ( currentFreeElement == nullptr ) )
                {
                printf ( "Stack isn't initialized, or some error during init has occured. ¯|_(ツ)_/¯ \n" );
                listOfErrors = listOfErrors + "In CLEAR: " + "Stack isn't initialized, or some error during init has occured. ¯|_(ツ)_/¯ \n";
                return -1;
                }
                
            currentFreeElement = beginningOfStack;
            
            return 0;
            }
        
        typeOfData* top()
            {
            if ( ( ( currentFreeElement - 1 ) == nullptr ) || ( beginningOfStack == nullptr ) )
                {
                printf ( "Current free element is out of range or even hasn't been initialized, maybe something is wrong with stack pointer. (Note that returning value in this case isn't prorep one) ¯|_(ツ)_/¯ \n" );
                listOfErrors = listOfErrors + "In TOP: " + "Current free element is out of range or even hasn't been initialized, maybe something is wrong with stack pointer. (Note that returning value in this case isn't prorep one) ¯|_(ツ)_/¯ \n";

                return nullptr;
                }
            
            if ( ( currentFreeElement - 1 ) < beginningOfStack )
                {
                return beginningOfStack;
                }
            else
                {
                return ( currentFreeElement - 1 );
                }
                
            }
        
        int pop()
            {
            if ( ( currentFreeElement - 1 ) <  beginningOfStack )
                {
                printf ( "Current top element is out of range or even hasn't been initialized, maybe something is wrong with stack pointer. ¯|_(ツ)_/¯ \n" );
                listOfErrors = listOfErrors + "In POP: " + "Current top element is out of range or even hasn't been initialized, maybe something is wrong with stack pointer. ¯|_(ツ)_/¯ \n";

                return -1;
                }
                
            currentFreeElement--;
            
            return 0;
            }
        
        bool empty()
            {
            if ( ( currentFreeElement == nullptr ) || ( currentFreeElement == nullptr ) )
                {
                printf ( "Stack isn't initialized, or some error during init has occured. (Note that returning value in this case isn't prorep one) ¯|_(ツ)_/¯ \n" );
                listOfErrors = listOfErrors + "In EMPTY: " + "Stack isn't initialized, or some error during init has occured. (Note that returning value in this case isn't prorep one) ¯|_(ツ)_/¯ \n";

                return false;
                }
            
            if ( currentFreeElement == beginningOfStack )
                {
                return true;
                }
            else
                {
                return false;
                }
            }
        
        int size()
            {
            if ( ( beginningOfStack == nullptr ) || ( currentFreeElement < beginningOfStack ) || ( currentFreeElement == nullptr ) )
                {
                printf ( "Stack isn't initialized, or some error during init has occured. (Note that returning value in this case isn't prorep one) ¯|_(ツ)_/¯ \n" );
                listOfErrors = listOfErrors + "In SIZE: " + "Stack isn't initialized, or some error during init has occured. (Note that returning value in this case isn't prorep one) ¯|_(ツ)_/¯ \n";

                return -1;
                }
                
            int currentSize = ( currentFreeElement - beginningOfStack );
            
            return currentSize;
            }
        
        int swap ( stack stackToSwapWith )
            {
            typeOfData* tempBeginningOfStack = stackToSwapWith.getBeginningOfStack();
            typeOfData* tempCurrentFreeElement = stackToSwapWith.getCurrentFreeElement();
            size_t tempStackCapacity = stackToSwapWith.getStackCapacity();
            
            if ( ( tempBeginningOfStack == nullptr ) || ( tempCurrentFreeElement == nullptr ) || ( tempStackCapacity == 0 ) )
                {
                printf ( "One of the swapping stacks isn't initialised or working wrong. ¯|_(ツ)_/¯ \n" );
                listOfErrors = listOfErrors + "In SWAP: " + "One of the swapping stacks isn't initialised or working wrong. ¯|_(ツ)_/¯ \n";
                
                return -1;
                }
                
            stackToSwapWith.setBeginningOfStack ( beginningOfStack );
            stackToSwapWith.setCurrentFreeElement ( currentFreeElement );
            stackToSwapWith.setStackCapacity ( stackCapacity );
            
            beginningOfStack = tempBeginningOfStack;
            currentFreeElement = tempCurrentFreeElement;
            stackCapacity = tempStackCapacity;
            
            return 0;
            }
        
        
        int dump()
            {
            writeToFile dumpOutput ( "dump.txt", 10000 );

            
            std::string firstLine = "Errors: ";
            if ( listOfErrors.size() == 0 )
                {
                firstLine = firstLine + "none of them. \n";
                }
            else
                {
                firstLine = firstLine + "\n";
                }
            
            for ( int i = 0; i < firstLine.size(); i++ )
                {
                dumpOutput.writeNextChar ( firstLine [ i ] );
                }
            
            for ( int i = 0; i < listOfErrors.size(); i++ )
                {
                dumpOutput.writeNextChar ( listOfErrors [ i ] );
                }
                
            
            dumpOutput.writeString ( "\n Stack is" );
            if ( ok() == true )
                {
                dumpOutput.writeString ( " ok.\n" );
                }
            else
                {
                dumpOutput.writeString ( "n't ok.\n" );
                }
            
            for ( int i = 0; i < getStackCapacity(); i++ )
                {
                dumpOutput.writeString ( "\n[ " );
                
                if ( *( beginningOfStack + i ) != poisonValue )
                    {
                    dumpOutput.writeNextChar ( ( typeOfData ) * ( beginningOfStack + i ) );
                    }
                else
                    {
                    dumpOutput.writeString ( " Here is poison value " );
//                    dumpOutput.writeString ( "%" );
                    }
                dumpOutput.writeString ( " ]" );
                }
                
                
            for ( int i = 0; i < getStackCapacity(); i++ )
                {
                std::cout << ( typeOfData ) *( beginningOfStack + i ) << std::endl;
                }
            // make POISON_INT, POISON_DOUBLE

            return 0;
            }
            
        
    
    private:
        typeOfData* beginningOfStack = nullptr;

        size_t stackCapacity = 0;
        typeOfData* currentFreeElement = nullptr;
        typeOfData poisonValue = NULL;
        std::string listOfErrors = "";
        
        int init()
            {
            beginningOfStack = ( typeOfData* ) calloc ( stackCapacity, sizeof ( typeOfData ) );
            
            if ( typeid ( typeOfData ).name() == typeid ( int ).name() )
                {
                poisonValue = poisonInt;
                }
            else if ( typeid ( typeOfData ).name() == typeid ( double ).name() )
                {
                poisonValue = poisonDouble;
                }
            else if ( typeid ( typeOfData ).name() == typeid ( float ).name() )
                {
                poisonValue = poisonFloat;
                }
            else if ( typeid ( typeOfData ).name() == typeid ( char ).name() )
                {
                poisonValue = poisonChar;
                }
            else
                {
                poisonValue = NAN;
                }
            
            for ( int i = 0; i < getStackCapacity(); i++ )
                {
                *( beginningOfStack + i ) = poisonValue;
                }
            
            if ( beginningOfStack == nullptr )
                {
                printf ( "Beginning pointer isn't correct. ¯|_(ツ)_/¯ \n" );
                return -1;
                }
            
            currentFreeElement = beginningOfStack;
            
            return 0;
            }
            
        bool ok()
            {
            return false;
            }
            
        int enlargeStack()
            {
            if ( beginningOfStack == nullptr )
                {
                printf ( "Beginning pointer isn't correct. ¯|_(ツ)_/¯ \n" );
                return -1;
                }
                
                
            int tempCurrentFreeElement = ( currentFreeElement - beginningOfStack );
            
            beginningOfStack = ( typeOfData* ) realloc ( beginningOfStack, ( ( stackCapacity * 2 ) * sizeof ( typeOfData ) ) );
            stackCapacity = stackCapacity * 2;
        
            
            currentFreeElement = ( beginningOfStack + tempCurrentFreeElement );
        
            for ( typeOfData* i = currentFreeElement; i < ( beginningOfStack + stackCapacity ); i++ )
                {
                *i = poisonValue;
                }
            
            return 0;
            }
        
        
    };



int main(int argc, const char * argv[])
    {
    stack <int> myStack ( 2 );
    myStack.push ( 4 );
    myStack.push ( 6 );
    myStack.push ( 1 );
    myStack.push ( 17 );
    myStack.push ( 0 );
    myStack.pop();
    myStack.pop();
    
    myStack.dump();

//    printf ( "%d", *myStack.top() );
    
    return 0;
    }

