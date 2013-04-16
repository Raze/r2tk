/* HEADER
 *
 * File: r2-argument-parser.hpp
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
 *   along with this program.  If not, see <http://www.gnu.org/licenses/>;.
 *
 * Comments:
 * A number of classes for parsing an argument list in the form (e.g.):
 *
 *	application --option-long-name [parameters] -o [parameters] -ab [application-arguments]
 *
 * Derive the Option class to define the options that are valid for your application.
 *
 * Register your derived Option objects with the ArgumentParser before calling ArgumentParser::Run().
 * In the end, the method Appear() will be called, along with the number of times the option appeared in
 * the command-line.
 *
 * Every option can have a long name and a short name (one letter). The short names
 * can be combined into one option, as seen with option -a and -b combined to -ab in the
 * above example. This is for convenience.
 *
 * All options can have parameters that must follow them. An option that must have a
 * parameter following it CANNOT be combined with other options in the form -ab. Doing
 * this will throw a runtime exception.
 *
 * TODO:
 * + Option is a too general name. Might come up again. Either we namespace the argument parser, or
 *   we make a prefix for the Option class.
 *
 * Depends on:
 *  + r2::ExceptionAssert
 *  + r2::ExceptionRuntime
 *
 * Updates:
 *	 2011-08-14 (Rarosu) - 
 *		Added r2 prefix to exception macro
 *		Added Exception namespace and removed Exception prefix from ExceptionArgumentParser.
 */

#ifndef R2_ARGUMENT_PARSER_HPP
#define R2_ARGUMENT_PARSER_HPP

#include <string>
#include <map>
#include <vector>
#include "r2-assert.hpp"
#include "r2-exception.hpp"

#define r2ExceptionArgumentParserM(p_message)	r2::Exception::ArgumentParser(p_message, __FILE__, __LINE__)

namespace r2 {
	class ArgumentParser;
	
	namespace Exception {
		/* Thrown if the argument parser run into any errors
		 */
		class ArgumentParser : public Runtime {
		public:
			/**
			* Create an exception
			* @param p_message An explaining text of the error
			* @param p_file The file the exception happened in. Use __FILE__.
			* @param p_line The line the exception happened at. Use __LINE__.
			*/
			ArgumentParser(const std::string& p_message, const std::string& p_file, const int p_line_number) throw();
		
			/**
			 * Create an exception without file/line stamp.
			 * @param p_message An explaining text of the error
			 */
			explicit ArgumentParser(const std::string& p_message) throw();
		
			/**
			 * Virtual destructor - for inheritance purposes.
			 */
			virtual ~ArgumentParser() throw();
		private:
			static const std::string K_CATEGORY;
		};
	}
	
	
	/* Derive this class and implement the Appear() method.
	 * Options can be registered with ArgumentParser.
	 */
	class Option {
	friend class ArgumentParser;
	public:
		Option(const std::string& p_name, const char p_short = 0, const int p_parameters_needed = 0) : m_name(p_name), m_short(p_short), m_parameters_needed(p_parameters_needed), m_parser(0) {}
		Option(const std::string& p_name, const int p_parameters_needed = 0) : m_name(p_name), m_short(0), m_parameters_needed(p_parameters_needed), m_parser(0) {} 
		Option(const char p_short, const int p_parameters_needed = 0) : m_short(p_short), m_parameters_needed(p_parameters_needed), m_parser(0) {}
		Option(const int p_parameters_needed = 0) : m_parameters_needed(p_parameters_needed), m_short(0), m_parser(0) {}
		virtual ~Option() throw() {}
		
		char Short() const { return m_short; }
		const std::string& Name() const { return m_name; }
		int ParametersNeeded() const { return m_parameters_needed; }
		
		void SetShort(const char p_short) {
			r2AssertM(m_parser == 0, "Shouldn't change values after added to the Parser");
			m_short = p_short;
		}
		void SetName(const std::string& p_name) {
			r2AssertM(m_parser == 0, "Shouldn't change values after added to the Parser");
			m_name = p_name;
		}
		virtual void SetParametersNeeded(const unsigned int p_parameters_needed) { 
			r2AssertM(m_parser == 0, "Shouldn't change values after added to the Parser");
			m_parameters_needed = p_parameters_needed;
		}
			
		bool HasName() { return m_name.size() != 0; }
		bool HasShort() { return m_short != 0; }
			
			
		/* 
		 * @param is the position of the application arguments
		 * @return the application argument from the position.
		 */
		const std::string& Parameter(unsigned int p_n) const { return m_parameters[p_n]; }
		
		/*
		 * @return the number of application arguments.
		 */
		unsigned int NumOfParameters() const { return m_parameters.size(); }
		
		/*
		 * @return all of the application parameters.
		 */
		const std::vector<std::string> Parameters() const { return m_parameters; }
		
	protected:
		
		virtual void Appear(unsigned int p_time) {}
		
	private:
		unsigned int m_parameters_needed;
		std::string m_name;
		char m_short;
		
		std::vector<std::string> m_parameters;
		
		ArgumentParser* m_parser;
		
		void AddParameter(const std::string& p_parameter);
		void SetParser(ArgumentParser* p_parser) { m_parser = p_parser; }
	};



	class Flag : public Option {
	public:
		Flag(const std::string& p_name, const char p_short = 0) : Option(p_name,p_short, 0), m_flagged(false) {}
		Flag(const char p_short = 0) : Option(p_short), m_flagged(false) {}
		operator bool() const { return m_flagged; }
	private:
		bool m_flagged;
		void Appear(int p_time) {
			if (p_time > 0) throw r2ExceptionArgumentParserM("Flags should only appear once");
			m_flagged = true;
		}
		
		virtual void SetParametersNeeded(const unsigned int p_parameters_needed) {
			r2AssertM(false, "This method should never be called - a flag cannot have parameters");
		} 
	};
	
	class ArgumentParser {
	private:
		class OptionOccurrence {
		public:
			OptionOccurrence(Option* p_option) : m_option(p_option), m_times(0) {}
			Option* /*const*/ m_option;
			
			void Appear();
		private:
			unsigned int m_times;
		};
	public:
		ArgumentParser();
		void Run(int argc, char* argv[]);
		
		const std::string& Path() const { return m_path; }
		
		
		/* 
		 * @param p_n is the position of the application arguments
		 * @return the application argument from the position.
		 */
		const std::string& Arg(unsigned int p_n) const { return m_args[p_n]; }
		
		/*
		 * @return the number of application arguments.
		 */
		unsigned int NumOfArgs() const { return m_args.size(); }
		
		/*
		 * @return all of the application parameters.
		 */
		const std::vector<std::string>& Args() const { return m_args; }
		
		
		void Add(Option* p_option);
	private:
		std::string m_path;
		
		// Left over Arguments
		std::vector<std::string> m_args;
		
		std::vector<OptionOccurrence> m_option_occurrences;
		std::map<char, int> m_shorts;
		std::map<std::string, int> m_names;
	};
}

#endif // R2_ARGUMENT_PARSER_HPP
