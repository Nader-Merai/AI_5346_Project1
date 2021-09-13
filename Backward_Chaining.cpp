///*
// * Backward_Chaining.cpp
// *
// *  Created on: Sep 5, 2021
// *      Author: nader
// */
//using namespace std;
//#include <vector>
//#include <string>
//#include <stack>
//#include <iostream>
//#include <fstream>
//#include <unordered_map>
//#include <string.h>
//// statement number and next statement number
//int statement_number, next_statement_number;
//string curr_variable, main_conclusion;
//char * buff;
//vector<vector<string>> rules;
//unordered_map<string,string> variable_list, conclusion_value_list;
//vector<string> conclusion_list;
//vector<string> clause_variable_list;
//stack<int> stmt_stack, cls_stack;
//void ParseRules(vector<vector<string>> &Rules)
//{
//	filebuf rules_buf;
//	rules_buf.open("Backward_Rules.txt",ios::in);
//	istream rules_file(&rules_buf);
//	string Expected_IF("    IF");
//	string Expected_THEN("        THEN");
//	vector<string> current_rule;
//	string line;
//	getline(rules_file,line);
//	while(rules_file)
//	{
//		auto res = mismatch(Expected_IF.begin(), Expected_IF.end(), line.begin());
//
//		if (res.first == Expected_IF.end())
//		{
//			string latter_half = line.substr(line.find("= "), line.size());
//			latter_half = latter_half.substr(2, latter_half.size());
//			current_rule.push_back(latter_half.substr(0, latter_half.find(" ")));
//		}
//
//		res = mismatch(Expected_THEN.begin(), Expected_THEN.end(), line.begin());
//		if (res.first == Expected_THEN.end())
//		{
//			string latter_half = line.substr(line.find("= ") + 2, line.size());
//			current_rule.push_back(latter_half);
//			Rules.push_back(current_rule);
//			current_rule.clear();
//		}
//		getline(rules_file,line);
//	}
//}
//
//void ParseVariables(unordered_map<string,string> &variable_list)
//{
//	filebuf backward_ds_buf;
//	backward_ds_buf.open("Backwards_Variable_List.txt",ios::in);
//	istream ds_file(&backward_ds_buf);
//	string line;
//	getline(ds_file,line);
//	while(ds_file)
//	{
//		variable_list[line] = "";
//		getline(ds_file,line);
//	}
//}
//
//void ParseConclusions(vector<string> &conclusion_list)
//{
//	filebuf backward_ds_buf;
//	backward_ds_buf.open("Backwards_Conclusion_List.txt",ios::in);
//	istream ds_file(&backward_ds_buf);
//	string line;
//	getline(ds_file, line);
//	while(ds_file)
//	{
//		conclusion_list.push_back(line);
//		conclusion_value_list[line] = "";
//		getline(ds_file,line);
//	}
//}
//
//void ParseClauses(vector<string> &clause_variable_list)
//{
//	filebuf backward_ds_buf;
//	backward_ds_buf.open("Backwards_Clause_Variable_List.txt",ios::in);
//	istream ds_file(&backward_ds_buf);
//	string line;
//	getline(ds_file, line);
//	int i = 1;
//	while(ds_file)
//	{
//		clause_variable_list.push_back(line);
//		if(i % 4 == 0) clause_variable_list.push_back("");
//		getline(ds_file,line);
//		i++;
//	}
//}
//
//void determine_member_conclusion_list()
//{
//	statement_number = 0;
//
//	unsigned int i = next_statement_number;
//	while((strcmp(curr_variable.c_str(), conclusion_list[i].c_str()) != 0) && (i < conclusion_list.size()-1))
//	{
//		i=i+1;
//	}
//
//	if (strcmp(curr_variable.c_str(), conclusion_list[i].c_str()) == 0) statement_number = i;
//
//}
//
//void push_on_stacks()
//{
//	stmt_stack.push(statement_number);
//	cls_stack.push(1);
//}
//
//void instantiate_curr_variable_()
//{
//	cout << "Input YES or NO for " << curr_variable << endl << flush;
//	cin >> variable_list[curr_variable];
//}
//
//int main()
//{
//
//	vector<string> dummy_v;
//	string dummy_s("");
//	rules.push_back(dummy_v);
//	conclusion_list.push_back(dummy_s);
//	clause_variable_list.push_back(dummy_s);
//	ParseRules(rules);
//	ParseVariables(variable_list);
//	ParseConclusions(conclusion_list);
//	ParseClauses(clause_variable_list);
//	unsigned int i;
//
//	cout << "Conclusion List:" << endl;
//	for (i = 1; i < conclusion_list.size(); i++)
//		cout << "Conclusion number " << i << ": " << conclusion_list[i] << endl;
//
//	cout << "Hit return to continue" << flush;
//	cin.ignore();
//
//	cout << "Variable List:" << endl;
//	i = 1;
//	for (auto kv : variable_list)
//	{
//		cout <<  "Variable number " << i << ": " << kv.first << endl;
//		i++;
//	}
//
//	cout << "Hit return to continue" << flush;
//	cin.ignore();
//
//	cout << "Clause Variable List:" << endl;
//	for (i = 1; i < clause_variable_list.size(); i++)
//	{
//		if (i % 5 == 1)
//			cout << "Clause " << (i/5 + 1) << ":" << endl;
//		cout << "Variable " << (!(i%5) ? 5 : (i%5)) << ": " << clause_variable_list[i] << endl;
//	}
//	cout << "Enter Conclusion\n" << flush;
//	cin >> main_conclusion;
//	curr_variable = main_conclusion;
//	bool conclusion_found = false;
//	next_statement_number = 1;
//	determine_member_conclusion_list();
//	if (statement_number == 0)
//	{
//		cout << "NO CONCLUSION WAS FOUND."  << endl << flush;
//		return 0;
//	}
//	push_on_stacks();
//	while(!conclusion_found)
//	{
//		i = (stmt_stack.top() - 1) * 5 + cls_stack.top();
//		curr_variable = clause_variable_list[i];
//		if (strcmp(curr_variable.c_str(), "") == 0)
//		{
//			curr_variable = conclusion_list[stmt_stack.top()];
//			conclusion_value_list[curr_variable] = rules[statement_number][cls_stack.top() - 1];
//			if (curr_variable == main_conclusion) break;
//			stmt_stack.pop();
//			cls_stack.pop();
//			statement_number = stmt_stack.top();
//			curr_variable = conclusion_list[stmt_stack.top()];
//			continue;
//		}
//		int tmp = next_statement_number;
//		next_statement_number = 1;
//		determine_member_conclusion_list();
//		next_statement_number = tmp;
//		if (statement_number != 0 &&
//				strcmp(conclusion_value_list[curr_variable].c_str(),"") == 0)
//		{
//			push_on_stacks();
//			continue;
//		}
//		else if (strcmp(conclusion_value_list[curr_variable].c_str(),"") != 0)
//		{
//			statement_number = stmt_stack.top();
//			if (strcmp(conclusion_value_list[curr_variable].c_str(), rules[statement_number][cls_stack.top() - 1].c_str()) == 0)
//			{
//				int curr_clause = cls_stack.top() + 1;
//				cls_stack.pop();
//				cls_stack.push(curr_clause);
//				continue;
//			}
//			else
//			{
//				curr_variable = conclusion_list[stmt_stack.top()];
//				cls_stack.pop();
//				stmt_stack.pop();
//				next_statement_number++;
//				determine_member_conclusion_list();
//				if (statement_number == 0)
//				{
//					cout << "NO CONCLUSION WAS FOUND."  << endl << flush;
//					return 0;
//				}
//				push_on_stacks();
//			}
//		}
//		statement_number = stmt_stack.top();
//		if (strcmp(variable_list[curr_variable].c_str(), "") == 0)	instantiate_curr_variable_();
//		if (strcmp(variable_list[curr_variable].c_str(), rules[statement_number][cls_stack.top() - 1].c_str()) == 0)
//		{
//			int curr_clause = cls_stack.top() + 1;
//			cls_stack.pop();
//			cls_stack.push(curr_clause);
//			continue;
//		}
//		else
//		{
//			curr_variable = conclusion_list[stmt_stack.top()];
//			cls_stack.pop();
//			stmt_stack.pop();
//			next_statement_number++;
//			determine_member_conclusion_list();
//			if (statement_number == 0)
//			{
//				cout << "NO CONCLUSION WAS FOUND."  << endl << flush;
//				return 0;
//			}
//			push_on_stacks();
//		}
//	}
//
//	cout << "FINAL CONCLUSION " << curr_variable << " :" << conclusion_value_list[curr_variable] << endl << flush;
//
//	return 0;
//}
//
//
