/*
 * Backward_Chaining.cpp
 *
 *  Created on: Sep 5, 2021
 *      Author: nader
 */
using namespace std;
#include <vector>
#include <string>
#include <queue>
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string.h>
// statement number and next statement number
int statement_number, clause_number;
string curr_variable, main_conclusion;
string condition_variable("PROFESSION");
char * buff;
vector<vector<string>> rules;
unordered_map<string,string> variable_list, conclusion_value_list;
vector<string> clause_variable_list, conclusion_list;
queue<string> conclusion_variable_q;
void ParseRules(vector<vector<string>> &Rules)
{
	filebuf rules_buf;
	rules_buf.open("Forward_Rules.txt",ios::in);
	istream rules_file(&rules_buf);
	string Expected_IF("    IF");
	string Expected_THEN("        THEN");
	vector<string> current_rule;
	string line;
	getline(rules_file,line);
	while(rules_file)
	{
		auto res = mismatch(Expected_IF.begin(), Expected_IF.end(), line.begin());

		if (res.first == Expected_IF.end())
		{
			string latter_half = line.substr(line.find("= "), line.size());
			latter_half = latter_half.substr(2, latter_half.size());
			current_rule.push_back(latter_half.substr(0, latter_half.find(" ")));
		}

		res = mismatch(Expected_THEN.begin(), Expected_THEN.end(), line.begin());
		if (res.first == Expected_THEN.end())
		{
			string latter_half = line.substr(line.find("= ") + 2, line.size());
			current_rule.push_back(latter_half);
			Rules.push_back(current_rule);
			current_rule.clear();
		}
		getline(rules_file,line);
	}
}

void ParseVariables(unordered_map<string,string> &variable_list)
{
	filebuf backward_ds_buf;
	backward_ds_buf.open("Forward_Variable_List.txt",ios::in);
	istream ds_file(&backward_ds_buf);
	string line;
	getline(ds_file,line);
	while(ds_file)
	{
		variable_list[line] = "";
		getline(ds_file,line);
	}
}

void ParseConclusions(vector<string> &conclusion_list)
{
	filebuf backward_ds_buf;
	backward_ds_buf.open("Forward_Conclusion_List.txt",ios::in);
	istream ds_file(&backward_ds_buf);
	string line;
	getline(ds_file, line);
	while(ds_file)
	{
		conclusion_list.push_back(line);
		conclusion_value_list[line] = "";
		getline(ds_file,line);
	}
}

void ParseClauses(vector<string> &clause_variable_list)
{
	filebuf backward_ds_buf;
	backward_ds_buf.open("Forward_Clause_Variable_List.txt",ios::in);
	istream ds_file(&backward_ds_buf);
	string line;
	getline(ds_file, line);
	int i = 1;
	while(ds_file)
	{
		clause_variable_list.push_back(line);
		if(i % 4 == 0) clause_variable_list.push_back("");
		getline(ds_file,line);
		i++;
	}
}

void instantiate_curr_variable()
{
	cout << "Input YES or NO for " << curr_variable << endl << flush;
	cin >> variable_list[curr_variable];
}

void search_for_variable()
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
int main()
{
	vector<string> dummy_v;
	string dummy_s("");
	dummy_v.push_back("");
	rules.push_back(dummy_v);
	clause_variable_list.push_back(dummy_s);
	conclusion_list.push_back(dummy_s);
	ParseRules(rules);
	ParseVariables(variable_list);
	ParseConclusions(conclusion_list);
	ParseClauses(clause_variable_list);
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

	string condition_variable_value("AGRICULTURE");
	cout << "Condition Variable is " << condition_variable << ": " << condition_variable_value << endl << flush;
	variable_list[condition_variable] = condition_variable_value;
	conclusion_variable_q.push(condition_variable);
	statement_number = 0;
	while (!conclusion_variable_q.empty())
	{
		search_for_variable();
		if (statement_number == 0)
		{
			break;
		}
		do
		{
			clause_number++;
			curr_variable = clause_variable_list[(statement_number - 1)*5 + clause_number];
			if (strcmp(curr_variable.c_str(), "") == 0) break;
			if (strcmp(variable_list[curr_variable].c_str(), "") == 0) instantiate_curr_variable();
		} while(strcmp(rules[statement_number][clause_number-1].c_str(), variable_list[curr_variable].c_str()) == 0);

		if (strcmp(curr_variable.c_str(), "") == 0)
		{
			condition_variable = conclusion_list[statement_number];
			variable_list[condition_variable] = rules[statement_number][clause_number-1];
			conclusion_variable_q.pop();
			conclusion_variable_q.push(condition_variable);
			cout << condition_variable << " = " << variable_list[condition_variable] << endl;
		}

	}



	return 0;
}


