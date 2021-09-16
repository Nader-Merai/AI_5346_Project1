#include "backwards_chaining.h"

void BackwardsChaining::DetermineMemberConclusionList()
{
	statement_number = 0;

	unsigned int i = next_statement_number;
	while((strcmp(curr_variable.c_str(), conclusion_list[i].c_str()) != 0) && (i < conclusion_list.size()-1))
	{
		i=i+1;
	}

	if (strcmp(curr_variable.c_str(), conclusion_list[i].c_str()) == 0) statement_number = i;

}

void BackwardsChaining::PushOnStacks()
{
	stmt_stack.push(statement_number);
	cls_stack.push(1);
}

void BackwardsChaining::PrintIntermediateResults()
{
	std::cout << "\nVariable List:\n";
	for (auto& t : variable_list)
	    std::cout << t.first << ": "
	              << t.second <<"\n";

	std::cout << "\nStatement Stack:\n";
	stack<int> stmt_stack_tmp = stmt_stack;
	while(!stmt_stack_tmp.empty())
	{
	    int top_element = stmt_stack_tmp.top();
	    std::cout << top_element << endl;
	    stmt_stack_tmp.pop();
	}

	std::cout << "\nClause Stack:\n";
	stack<int> cls_stack_tmp = cls_stack;
	while(!cls_stack_tmp.empty())
	{
		int top_element = cls_stack_tmp.top();
		std::cout << top_element << endl;
		cls_stack_tmp.pop();
	}

	std::cout << "\nStatement Number:\n";
	cout << statement_number << endl << flush;

	std::cout << "\nNext Statement Number:\n";
	cout << next_statement_number << endl << endl << flush;

}

string BackwardsChaining::StartBackwardChaining()
{
	unsigned int i;

	cout << "Conclusion List:" << endl;
	for (i = 1; i < conclusion_list.size(); i++)
		cout << "Conclusion number " << i << ": " << conclusion_list[i] << endl;

	cout << "Hit return to continue" << flush;
	cin.ignore();

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
	cout << "Enter Conclusion\n" << flush;
	cin >> main_conclusion;
	curr_variable = main_conclusion;
	bool conclusion_found = false;
	next_statement_number = 1;
	DetermineMemberConclusionList();
	if (statement_number == 0)
	{
		cout << "NO CONCLUSION WAS FOUND."  << endl << flush;
		return "NOTHING";
	}
	PushOnStacks();
	while(!conclusion_found)
	{
		PrintIntermediateResults();
		i = (stmt_stack.top() - 1) * 5 + cls_stack.top();
		curr_variable = clause_variable_list[i];
		if (strcmp(curr_variable.c_str(), "") == 0)
		{
			curr_variable = conclusion_list[stmt_stack.top()];
			conclusion_value_list[curr_variable] = rules[statement_number][cls_stack.top() - 1];
			if (curr_variable == main_conclusion) break;
			stmt_stack.pop();
			cls_stack.pop();
			statement_number = stmt_stack.top();
			curr_variable = conclusion_list[stmt_stack.top()];
			continue;
		}
		int tmp = next_statement_number;
		next_statement_number = 1;
		DetermineMemberConclusionList();
		next_statement_number = tmp;
		if (statement_number != 0 &&
				strcmp(conclusion_value_list[curr_variable].c_str(),"") == 0)
		{
			PushOnStacks();
			continue;
		}
		else if (statement_number != 0 && strcmp(conclusion_value_list[curr_variable].c_str(),"") != 0)
		{
			statement_number = stmt_stack.top();
			if (strcmp(conclusion_value_list[curr_variable].c_str(), rules[statement_number][cls_stack.top() - 1].c_str()) == 0)
			{
				int curr_clause = cls_stack.top() + 1;
				cls_stack.pop();
				cls_stack.push(curr_clause);
				continue;
			}
			else
			{
				curr_variable = conclusion_list[stmt_stack.top()];
				cls_stack.pop();
				stmt_stack.pop();
				next_statement_number++;
				DetermineMemberConclusionList();
				if (statement_number == 0)
				{
					cout << "NO CONCLUSION WAS FOUND."  << endl << flush;
					return "NOTHING";
				}
				PushOnStacks();
			}
		}
		statement_number = stmt_stack.top();
		if (strcmp(variable_list[curr_variable].c_str(), "") == 0)	InstantiatedCurrVariable();
		if (strcmp(variable_list[curr_variable].c_str(), rules[statement_number][cls_stack.top() - 1].c_str()) == 0)
		{
			int curr_clause = cls_stack.top() + 1;
			cls_stack.pop();
			cls_stack.push(curr_clause);
			continue;
		}
		else
		{
			curr_variable = conclusion_list[stmt_stack.top()];
			cls_stack.pop();
			stmt_stack.pop();
			next_statement_number++;
			DetermineMemberConclusionList();
			if (statement_number == 0)
			{
				cout << "NO CONCLUSION WAS FOUND."  << endl << flush;
				return "NOTHING";
			}
			PushOnStacks();
		}
	}

	PrintIntermediateResults();

	cout << "FINAL CONCLUSION " << curr_variable << " :" << conclusion_value_list[curr_variable] << endl << flush;

	return conclusion_value_list[curr_variable];
}
