#include "forward_chaining.h"

void ForwardChaining::SearchForVariable()
{
	for (unsigned int i = (statement_number*5 + 1); i < clause_variable_list.size(); i++)
	{
		if(strcmp(condition_variable.c_str(), clause_variable_list[i].c_str()) == 0)
		{
			statement_number = i/5 + 1;
			clause_number = 0;
			return;
		}
	}
	statement_number = 0;
	return;
}

void ForwardChaining::InitializeConditionVariable(string init_value)
{
	condition_variable = init_value;
}

void ForwardChaining::PrintIntermediateResults()
{
	std::cout << "\nVariable List:\n";
	for (auto& t : variable_list)
	    std::cout << t.first << ": "
	              << t.second <<"\n";

	std::cout << "\nConclusion Variable Queue Stack:\n";
	queue<string> conclusion_variable_q_tmp = conclusion_variable_q;
	while(!conclusion_variable_q_tmp.empty())
	{
	    string top_element = conclusion_variable_q_tmp.front();
	    std::cout << top_element << endl;
	    conclusion_variable_q_tmp.pop();
	}

	std::cout << "\nStatement Number:\n";
	cout << statement_number << endl << flush;

	std::cout << "\nClause Number:\n";
	cout << clause_number << endl << endl << flush;

}

void ForwardChaining::InstantiatedCurrVariable()
{
	PrintIntermediateResults();
	cout << "Input YES or NO for " << curr_variable << endl << flush;
	cin >> variable_list[curr_variable];
}

int ForwardChaining::StartForwardChaining(string condition_variable_value)
{
	unsigned int i;

	// Printing out the shape of the read data structures
	cout << "Variable List:" << endl;
	i = 1;
	for (auto kv : variable_list)
	{
		cout <<  "Variable number " << i << ": " << kv.first << endl;
		i++;
	}

	cout << "Hit return to continue" << flush;
	cin.ignore();

	cout << "Clause Variable List:" << endl;
	for (i = 1; i < clause_variable_list.size(); i++)
	{
		if (i % 5 == 1)
			cout << "Clause " << (i/5 + 1) << ":" << endl;
		cout << "Variable " << (!(i%5) ? 5 : (i%5)) << ": " << clause_variable_list[i] << endl;
	}

	cout << "Condition Variable is " << condition_variable << ": " << condition_variable_value << endl << flush;

	// initial variable initialization and pushed into the queue
	variable_list[condition_variable] = condition_variable_value;
	conclusion_variable_q.push(condition_variable);
	statement_number = 0;
	while (!conclusion_variable_q.empty())
	{
		SearchForVariable();
		// we reached the final entry in the clause variable list without finding an appropriate entry, so pop from the queue and continue
		if (statement_number == 0)
		{
			conclusion_variable_q.pop();
			continue;
		}
		do
		{
			clause_number++;
			// retrieve the variable name
			curr_variable = clause_variable_list[(statement_number - 1)*5 + clause_number];
			if (strcmp(curr_variable.c_str(), "") == 0) break;
			if (strcmp(variable_list[curr_variable].c_str(), "") == 0) InstantiatedCurrVariable();
		} while(strcmp(rules[statement_number][clause_number-1].c_str(), variable_list[curr_variable].c_str()) == 0);

		// this means that we reached the end of the rule since an empty string seperates between rules in the clause variable list, which means rule applies
		if (strcmp(curr_variable.c_str(), "") == 0)
		{
			condition_variable = conclusion_list[statement_number];
			variable_list[condition_variable] = rules[statement_number][clause_number-1];
			conclusion_variable_q.push(condition_variable);
			cout << condition_variable << " = " << variable_list[condition_variable] << endl;
		}

	}
	return 0;
}

