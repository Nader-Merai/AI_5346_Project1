/*
 * Backward_Chaining.cpp
 *
 *  Created on: Sep 5, 2021
 *      Author: nader
 */
using namespace std;
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string.h>

void ParseRulesf(vector<vector<string>> &Rules)
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
			string latter_half = line.substr(line.find("THEN "), line.size());
			latter_half = latter_half.substr(5, latter_half.size());
			current_rule.push_back(latter_half);
			Rules.push_back(current_rule);
			current_rule.clear();
		}
		getline(rules_file,line);
	}
}

void ParseVariablesf(unordered_map<string,string> &variable_list)
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

void ParseConclusionsf(vector<string> &conclusion_list)
{
	filebuf backward_ds_buf;
	backward_ds_buf.open("Forward_Conclusion_List.txt",ios::in);
	istream ds_file(&backward_ds_buf);
	string line;
	getline(ds_file, line);
	while(ds_file)
	{
		conclusion_list.push_back(line);
		getline(ds_file,line);
	}
}

void ParseClausesf(vector<string> &clause_variable_list)
{
	filebuf backward_ds_buf;
	backward_ds_buf.open("Forward_Clause_Variable_List.txt",ios::in);
	istream ds_file(&backward_ds_buf);
	string line;
	getline(ds_file, line);
	while(ds_file)
	{
		clause_variable_list.push_back(line);
		getline(ds_file,line);
	}
}

//int main()
//{
//	vector<vector<string>> rules;
//	unordered_map<string,string> variable_list;
//	vector<string> conclusion_list;
//	vector<string> clause_variable_list;
//	ParseRulesf(rules);
//	ParseVariablesf(variable_list);
//	ParseConclusionsf(conclusion_list);
//	ParseClausesf(clause_variable_list);
////	for (vector<string> rule : rules)
////	{
////		for (string element : rule)
////			cout << element << " ";
////		cout << endl;
////	}
////	cout << variable_list.size() << endl;
////	for (auto kv : variable_list)
////		cout << kv.first << endl;
////	for (string conclusion : conclusion_list)
////	{
////		cout << conclusion <<  endl;
////	}
//
////	for (string clause : clause_variable_list)
////	{
////		cout << clause <<  endl;
////	}
//
//	return 0;
//}


