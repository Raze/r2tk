/* SOURCE
 *
 * File: r2-argument-parser.cpp
 * Created by: Rasmus Jarl (Raze Dux) and Lars Woxberg (Rarosu)
 * Created on: August 07 2011, 01:49
 *
 * License:
 *   Copyright (C) 2011 Rasmus Jarl
 *
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU Lesser General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU Lesser General Public License for more details.
 *
 *   You should have received a copy of the GNU Lesser General Public License
 *   along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Comments:
 *
 * Updates:
 *
 */

#include "r2-argument-parser.hpp"

namespace r2 {
	void Option::AddParameter(const std::string& p_parameter) {
		m_parameters.push_back(p_parameter);
	}


	namespace Exception {
		const std::string ArgumentParser::K_CATEGORY("Argument Parser Error");

		ArgumentParser::ArgumentParser(const std::string& p_message, const std::string& p_file, const int p_line_number) throw() :
			Runtime(p_message, K_CATEGORY, p_file, p_line_number) {}

		ArgumentParser::ArgumentParser(const std::string& p_message) throw() :
			Runtime(p_message, K_CATEGORY) {}

		ArgumentParser::~ArgumentParser() throw() {}
	}
	
	ArgumentParser::ArgumentParser() {
		
	}
	
	
	
	
	
	
	
	void ArgumentParser::OptionOccurrence::Appear() {
		m_option->Appear(m_times++);
	}
	
	void ArgumentParser::Run(int argc, char* argv[]) {
		m_path = argv[0];
		
		// temporary variable for how many arguments last option still needs.
		int parameters_needed = 0;
		// The current Option expecting parameters.
		OptionOccurrence* parameter_occurence = 0;
		
		
		for(unsigned int argument_index = 1; argument_index < argc; ++argument_index) {
			std::string current_argument = argv[argument_index];
			
			
			if(current_argument[0] == '-') {
				// Is Short or Name.
				
				// Can't an option have no parameters? This if-statement includes all options, doesn't it?
				// If an option is currently require a parameter and a option is stated.
				// Ah, makes sense. parameters_needed might need another name, but I have no better idea atm :)
				// Neither do I.
				if(parameters_needed != 0) {
					// cast exception.
					throw r2ExceptionArgumentParserM(std::string("Argument parser expected parameters after option: ") + parameter_occurence->m_option->m_name);
				}
				
				if(current_argument[1] != '-') {
					// Is Short.
					std::string shorts = current_argument.substr(1);
					for(unsigned int short_index = 0; short_index < shorts.size(); ++short_index) {
					
						// isn't this already checked outside this if-statement?
						// For loop for each short in a line. i.e -flck
						// Ah, gotcha
						if(parameters_needed != 0) {
							// Cast exception.
							// Paramater expected.
							throw r2ExceptionArgumentParserM(std::string("Short cannot be combined (has required parameters): ") + parameter_occurence->m_option->m_short + ((parameter_occurence->m_option->m_name.length() > 0) ? ("(" + parameter_occurence->m_option->m_name + ")") : "" ));           
						}
						char current_short = shorts[short_index];
						
						// Check if we recognize the option
						std::map<char, int>::iterator position = m_shorts.find(current_short);
						if(position != m_shorts.end()) {
							OptionOccurrence* current_occurence = &m_option_occurrences[position->second]; // Get Occurrence.
							
							parameters_needed = current_occurence->m_option->ParametersNeeded(); // Get Options Parameter needed.
							if(parameters_needed != 0) {
								parameter_occurence = current_occurence;
							} else {
								current_occurence->Appear(); // Call on the options Appear(current_times).
							}
						} else {
							// Cast exception...
							// Short isn't found.
							throw r2ExceptionArgumentParserM(std::string("Could not find short: ") + current_argument);
						}
					}
				} else {
					// Is Name.
					
					 // stripe the '--' from the argument.
					// Check if we recognize the option
					std::string name = current_argument.substr(1);
					std::map<std::string, int>::iterator position = m_names.find(name);
					if (position != m_names.end()) {
						// option exists
						OptionOccurrence* current_occurence = &m_option_occurrences[position->second]; // Get Occurrence.
						
						parameters_needed = current_occurence->m_option->ParametersNeeded(); // Get Options Parameter needed.
						if(parameters_needed != 0) {
							parameter_occurence = current_occurence; // Set parameter_occurence to current_occurence if it needs parameters
						} else {
							current_occurence->Appear(); // Call on the options Appear(current_times).
						}
						
					} else {
						throw r2ExceptionArgumentParserM(std::string("Could not find option: ") + name);
					}
				}
			} else if(parameters_needed) {
				parameter_occurence->m_option->AddParameter(current_argument);
				--parameters_needed;
				if(parameters_needed == 0) {
					parameter_occurence->Appear(); // Call on the options Appear(current_times), when all it's parameters are found.
				}
			} else
				m_args.push_back(current_argument);
		}
	}
	
	void ArgumentParser::Add(Option* p_option) {
		r2AssertM(p_option != 0, "Trying to add NULL Option pointer to the Argument Parser");
		
		p_option->SetParser(this);
		
		// Add the Option.
		m_option_occurrences.push_back(OptionOccurrence(p_option));
		
		// If the option has a short name add it as the key to the Option's position in m_options.
		if(p_option->HasShort()) m_shorts.insert(std::pair<char, int>(p_option->Short(), m_option_occurrences.size() - 1));
		
		// If the option has a name add it as the key to the Option's position in m_options.
		if(p_option->HasName()) m_names.insert(std::pair<std::string, int>(p_option->Name(), m_option_occurrences.size() - 1));
	}	
	
}

