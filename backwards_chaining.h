/*
 * backwards_chaining.h
 *
 *  Created on: Sep 13, 2021
 *      Author: nader
 */

#ifndef BACKWARDS_CHAINING_H_
#define BACKWARDS_CHAINING_H_
#include "inference_engine.h"

class BackwardsChaining : public InferenceEngine
{
	public:
		BackwardsChaining() = default;
		~BackwardsChaining() = default;
		string StartBackwardChaining();
	protected:
		int statement_number{};
		int next_statement_number{};
		string main_conclusion;
		char * buff{};
		stack<int> stmt_stack, cls_stack;
		void DetermineMemberConclusionList();
		void PushOnStacks();
		void PrintIntermediateResults();
		void InstantiatedCurrVariable();


};


#endif /* BACKWARDS_CHAINING_H_ */
