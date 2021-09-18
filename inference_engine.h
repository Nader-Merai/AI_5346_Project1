#ifndef INFERENCE_ENGINE_H_
#define INFERENCE_ENGINE_H_
#include <vector>
#include <string>
#include <stack>
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string.h>
#include <queue>
using namespace std;

class InferenceEngine
{
	public:
		InferenceEngine() = default;
		void ParseRules(string rules_filename);
		void ParseVariables(string variables_filename);
		void ParseConclusions(string conclusions_filename);
		void ParseClauses(string clause_variable_list_filename);
		void InitializeDummy();
		~InferenceEngine() = default;


	protected:
		string curr_variable;
		vector<vector<string>> rules;
		unordered_map<string,string> variable_list, conclusion_value_list;
		vector<string> conclusion_list;
		vector<string> clause_variable_list;

};



#endif /* INFERENCE_ENGINE_H_ */
