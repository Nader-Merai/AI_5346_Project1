/*
 * Backward_Chaining.cpp
 *
 *  Created on: Sep 5, 2021
 *      Author: nader
 */
#include "backwards_chaining.h"
#include "forward_chaining.h"

int main()
{
	BackwardsChaining backwards_chaining_engine = BackwardsChaining();
	backwards_chaining_engine.InitializeDummy();
	backwards_chaining_engine.ParseVariables("Backwards_Variable_List.txt");
	backwards_chaining_engine.ParseRules("Backwards_Rules.txt");
	backwards_chaining_engine.ParseConclusions("Backwards_Conclusion_List.txt");
	backwards_chaining_engine.ParseClauses("Backwards_Clause_Variable_List.txt");
	ForwardChaining forward_chaining_engine = ForwardChaining();
	forward_chaining_engine.InitializeDummy();
	forward_chaining_engine.ParseVariables("Forward_Variable_List.txt");
	forward_chaining_engine.ParseRules("Forward_Rules.txt");
	forward_chaining_engine.ParseConclusions("Forward_Conclusion_List.txt");
	forward_chaining_engine.ParseClauses("Forward_Clause_Variable_List.txt");
	forward_chaining_engine.InitializeConditionVariable("PROFESSION");
	forward_chaining_engine.StartForwardChaining(backwards_chaining_engine.StartBackwardChaining());
}



