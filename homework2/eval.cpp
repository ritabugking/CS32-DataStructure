//
//  eval.cpp
//  mazestack
//
//  Created by YI-JU WANG on 2017/2/5.
//  Copyright © 2017年 YI-JU WANG. All rights reserved.
//

#include <stack>
#include <iostream>
#include <string>
#include <stdio.h>
#include <cassert>
using namespace std;

// Evaluates a boolean expression
// Postcondition: If infix is a syntactically valid infix boolean
//   expression, then postfix is set to the postfix form of that
//   expression,
//   result is set to the value of the expression (where
//   in that expression, each digit k represents element k of the
//   values array), and the function returns zero.  If infix is not a
//   syntactically valid expression, the function returns 1.  (In that
//   case, postfix may or may not be changed, but result must be
//   unchanged.)


int evaluate(string infix, string& postfix, bool& result)
{
    bool values[2] = {true, false};
    // Convert the infix expression to postfix expression
    if (infix=="")
        return 1;
    
    stack<char> operatorStack;  // Initialize the operator stack to empty
    postfix = "";   // Initialize postfix to empty
    bool syntaxCheckPrths = false;
    bool syntaxCheckExcalm = false;
    bool syntaxCheckPrths2 = false;
    bool syntaxCheckOpr = false;
    bool syntaxCheckChr = false;
    
    // For each character ch in the infix string
    for (int i=0; i<infix.length(); i++)
    {
        
        char temp;
        temp = infix[i];
        
        // Switch (ch)
        switch (temp) {
                // case operand:
            case 'T':
            case 'F':
                syntaxCheckPrths = false;
                syntaxCheckExcalm = false;
                syntaxCheckOpr = false;
                syntaxCheckChr = true;
                syntaxCheckPrths2 = false;
                postfix += temp;    // append ch to end of postfix
                break;
                
                // case operator:
                // While the stack is not empty and precedence of ch <= precedence of stack top
                // append the stack top to postfix
                // pop the stack
                // push ch onto the stack
            case '!':
                if (syntaxCheckChr)
                    return 1;
                if (syntaxCheckPrths2)
                    return 1;
                syntaxCheckPrths = false;
                syntaxCheckExcalm = true;
                syntaxCheckOpr = false;
                syntaxCheckChr = false;
                syntaxCheckPrths2 = false;
                if (!operatorStack.empty()){
                    while (operatorStack.top()=='!'){
                        char popout = operatorStack.top();
                        postfix += popout;
                        operatorStack.pop();
                    }
                }
                operatorStack.push('!');
                break;
                
            case '&':
                if (!syntaxCheckChr && !syntaxCheckPrths2)
                    return 1;
                if (!operatorStack.empty()){
                    while(operatorStack.top()=='&' || operatorStack.top()=='!'){
                        char popout = operatorStack.top();
                        postfix += popout;
                        operatorStack.pop();
                    }
                }
                operatorStack.push('&');
                syntaxCheckPrths = false;
                syntaxCheckExcalm = false;
                syntaxCheckOpr = true;
                syntaxCheckChr = false;
                syntaxCheckPrths2 = false;
                break;
                
            case '|':
                if (!syntaxCheckChr && !syntaxCheckPrths2)
                    return 1;
                if (!operatorStack.empty()){
                    while(operatorStack.top()=='|' || operatorStack.top()=='&' || operatorStack.top()=='!'){
                        char popout = operatorStack.top();
                        postfix += popout;
                        operatorStack.pop();
                    }
                }
                operatorStack.push('|');
                syntaxCheckPrths = false;
                syntaxCheckExcalm = false;
                syntaxCheckOpr = true;
                syntaxCheckChr = false;
                syntaxCheckPrths2 = false;
                break;
                
                // case '(':
                // push ch onto the operator stack
            case '(':
                if (syntaxCheckChr)
                    return 1;
                if (syntaxCheckPrths2)
                    return 1;
                syntaxCheckPrths = true;
                syntaxCheckExcalm = false;
                syntaxCheckOpr = false;
                syntaxCheckChr = false;
                syntaxCheckPrths2 = false;
                operatorStack.push('(');
                break;
                
                // case ')':
                // pop stack until matching '('
            case ')':
                if (!syntaxCheckChr && !syntaxCheckPrths2)
                    return 1;
                
                if(!operatorStack.empty()){
                    // While stack top is not '('
                    // append the stack top to postfix
                    // pop the stack
                    while(operatorStack.top()!='('){
                        char popout = operatorStack.top();
                        postfix += popout;
                        operatorStack.pop();
                    }
                    operatorStack.pop();  // pop the stack, remove the '('
                }
                syntaxCheckPrths = false;
                syntaxCheckExcalm = false;
                syntaxCheckOpr = false;
                syntaxCheckChr = false;
                syntaxCheckPrths2 = true;
                break;
                
            case ' ':
                break;
                
            default:
                return 1;
        }
        
    }
    
    // While the stack is not empty, append the stack top to postfix
    // pop the stack
    while(!operatorStack.empty()){
        if(operatorStack.top()=='(' || operatorStack.top()==')')
        {
            return 1;
        }
        else
        {
            postfix += operatorStack.top();
            operatorStack.pop();
        }
    }
    if (postfix=="")
        return 1;
    /*
     
     
     
     
     else //
     set operand2 to the top of the operand stack
     pop the stack
     set operand1 to the top of the operand stack
     pop the stack
     apply the operation that ch represents to operand1 and
     operand2, and push the result onto the stack
     When the loop is finished, the operand stack will contain one item,
     the result of evaluating the expression
     */
    // evaluation of the postfix expression and convert it to the result
    bool tempResult;
    stack<bool> resultStack;    // Initialize the operand stack to empty
    for (int i=0; i<postfix.length(); i++)
    {
        bool temp1, temp2;
        
        switch (postfix[i]) {   // For each character ch in the postfix string
                //  if ch is an operand, push the value that ch represents onto the operand stack
            case 'T':
                resultStack.push(values[postfix[i]-'T']);
                break;
            case 'F':
                resultStack.push(values[postfix[i]-'F'+1]);
                break;
                //  if ch is a binary operator
                //  set temp2 to the top of the operand stack, and set temp1 to the operand under the top
            case '!':
                if (resultStack.empty())
                    return 1;
                resultStack.top()=!resultStack.top();
                break;
            case '&':
                if (resultStack.empty())
                    return 1;
                temp2 = resultStack.top();
                resultStack.pop();
                if (resultStack.empty())
                    return 1;
                temp1 = resultStack.top();
                resultStack.pop();
                //  apply the & operation that ch represents to operand1 and
                //  operand2, and push the result onto the stack
                resultStack.push(temp1 && temp2);
                break;
            case '|':
                if (resultStack.empty())
                    return 1;
                temp2 = resultStack.top();
                resultStack.pop();
                if (resultStack.empty())
                    return 1;
                temp1 = resultStack.top();
                resultStack.pop();
                //  apply the | operation that ch represents to operand1 and
                //  operand2, and push the result onto the stack
                resultStack.push(temp1 || temp2);
                break;
                
            default:
                break;
        }
        
    }
    
    tempResult = resultStack.top();
    resultStack.pop();
    
    if (!resultStack.empty())
        return 1;
    
    result = tempResult;
    
    return 0;
    
}
/*
 int main()
 {
 string pf;
 bool answer;
 assert(evaluate("(T&T)!T", pf, answer) == 1);
 assert(evaluate("T| F", pf, answer) == 0  &&  pf == "TF|"  &&  answer);
 assert(evaluate("T|", pf, answer) == 1);
 assert(evaluate("F F", pf, answer) == 1);
 assert(evaluate("TF", pf, answer) == 1);
 assert(evaluate("()", pf, answer) == 1);
 assert(evaluate("T(F|T)", pf, answer) == 1);
 assert(evaluate("T(&T)", pf, answer) == 1);
 assert(evaluate("(T&(F|F)", pf, answer) == 1);
 assert(evaluate("", pf, answer) == 1);
 assert(evaluate("F  |  !F & (T&F) ", pf, answer) == 0  &&  pf == "FF!TF&&|"  &&  !answer);
 assert(evaluate(" F  ", pf, answer) == 0 &&  pf == "F"  &&  !answer);
 assert(evaluate("((T))", pf, answer) == 0 &&  pf == "T"  &&  answer);
 cout << "Passed all tests" << endl;
 }
 
 */
