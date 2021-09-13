#include "forward_chaining.h"

void ForwardChaining::SearchForVariable()
{
	for (unsigned int i = (statement_number_f*5 + 1); i < clause_variable_list.size(); i++)
	{
		if(strcmp(condition_variable.c_str(), clause_variable_list[i].c_str()) == 0)
		{
			statement_number_f = i/5 + 1;
			clause_number = 0;
			return;
		}
	}
	statement_number_f = 0;
	return;
}

void ForwardChaining::InitializeConditionVariable(string init_value)
{
	condition_variable = init_value;
}

int ForwardChaining::StartForwardChaining(string condition_variable_value)
{
	unsigned int i;

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
	variable_list[condition_variable] = condition_variable_value;
	conclusion_variable_q.push(condition_variable);
	statement_number_f = 0;
	while (!conclusion_variable_q.empty())
	{
		SearchForVariable();
		if (statement_number_f == 0)
		{
			break;
		}
		do
		{
			clause_number++;
			curr_variable = clause_variable_list[(statement_number_f - 1)*5 + clause_number];
			if (strcmp(curr_variable.c_str(), "") == 0) break;
			if (strcmp(variable_list[curr_variable].c_str(), "") == 0) InstantiatedCurrVariable();
		} while(strcmp(rules[statement_number_f][clause_number-1].c_str(), variable_list[curr_variable].c_str()) == 0);

		if (strcmp(curr_variable.c_str(), "") == 0)
		{
			condition_variable = conclusion_list[statement_number_f];
			variable_list[condition_variable] = rules[statement_number_f][clause_number-1];
			conclusion_variable_q.pop();
			conclusion_variable_q.push(condition_variable);
			cout << condition_variable << " = " << variable_list[condition_variable] << endl;
		}

	}



	return 0;
}
