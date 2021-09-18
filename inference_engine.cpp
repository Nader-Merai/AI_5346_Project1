#include "inference_engine.h"

void InferenceEngine::InitializeDummy()
{
	vector<string> dummy_v;
	string dummy_s("");
	rules.push_back(dummy_v);
	conclusion_list.push_back(dummy_s);
	clause_variable_list.push_back(dummy_s);
}

void InferenceEngine::ParseRules(string rules_filename)
{
	filebuf rules_buf;
	rules_buf.open(rules_filename,ios::in);
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
			rules.push_back(current_rule);
			current_rule.clear();
		}
		getline(rules_file,line);
	}
}

void InferenceEngine::ParseVariables(string variables_filename)
{
	filebuf backward_ds_buf;
	backward_ds_buf.open(variables_filename,ios::in);
	istream ds_file(&backward_ds_buf);
	string line;
	getline(ds_file,line);
	while(ds_file)
	{
		variable_list[line] = "";
		getline(ds_file,line);
	}
}

void InferenceEngine::ParseConclusions(string conclusions_filename)
{
	filebuf backward_ds_buf;
	backward_ds_buf.open(conclusions_filename,ios::in);
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

void InferenceEngine::ParseClauses(string clause_variable_list_filename)
{
	filebuf backward_ds_buf;
	backward_ds_buf.open(clause_variable_list_filename,ios::in);
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



