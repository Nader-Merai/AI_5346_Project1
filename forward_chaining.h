/*
 * forward_chaining.h
 *
 *  Created on: Sep 13, 2021
 *      Author: nader
 */

#ifndef FORWARD_CHAINING_H_
#define FORWARD_CHAINING_H_
#include "inference_engine.h"

class ForwardChaining : public InferenceEngine
{
	public:
		ForwardChaining() = default;
		~ForwardChaining() = default;
		int StartForwardChaining(string condition_variable_value);
		void InitializeConditionVariable(string init_value);
	protected:
		int statement_number_f{};
		int clause_number{};
		queue<string> conclusion_variable_q;
		void SearchForVariable();
		string condition_variable;
		void PrintIntermediateResults();
		void InstantiatedCurrVariable();
};



#endif /* FORWARD_CHAINING_H_ */
