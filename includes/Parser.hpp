/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrassokh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/04 16:40:03 by mrassokh          #+#    #+#             */
/*   Updated: 2018/05/04 16:40:06 by mrassokh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_HPP
# define PARSER_HPP

# include <vector>
# include <algorithm>
# include <string>
# include <cctype>
# include <iostream>
# include "Exceptions.hpp"
# include "Command.hpp"
# include <regex>

class Parser
{
public:
	static Parser 							*getParser();

	void 									parse(std::shared_ptr<std::vector<std::shared_ptr<std::vector<std::string>>>> m_tokenLines,
											std::shared_ptr<std::vector<Command *>> commandStack,
											std::shared_ptr<std::string> errorLog,
											std::shared_ptr<int> validFlag);

private:
	Parser();
	Parser(Parser const & rhs) = delete;
	Parser & operator = (Parser const & rhs) = delete;
	virtual ~Parser();

	const std::regex 											m_push_regex;
	const std::regex 											m_pop_regex;
	const std::regex 											m_dump_regex;
	const std::regex 											m_assert_regex;
	const std::regex 											m_addition_regex;
	const std::regex 											m_subtract_regex;
	const std::regex 											m_multiply_regex;
	const std::regex 											m_divide_regex;
	const std::regex 											m_modulo_regex;
	const std::regex 											m_print_regex;
	const std::regex 											m_exit_regex;
	const std::regex 											m_power_regex;
	const std::regex 											m_root_regex;
	const std::regex 											m_revert_regex;
	const std::regex 											m_min_regex;
	const std::regex 											m_max_regex;
	const std::regex 											m_int8_regex;
	const std::regex 											m_int16_regex;
	const std::regex 											m_int32_regex;
	const std::regex 											m_float_regex;
	const std::regex 											m_double_regex;
	const std::regex 											m_digit_regex;

	std::vector<std::regex>										m_instr_regex;
	std::vector<std::regex>										m_value_regex;

	std::vector<void (Parser::*)
		(std::string const & value,
		std::shared_ptr<std::vector<Command *>> commandStack,
		int counter)>											m_fill_command_func;
	std::vector<void (Parser::*)
		(std::string const & value,
		std::shared_ptr<std::vector<Command *>> commandStack,
		 int counter, eCommandType type)>						m_fill_value_func;

	UnexpectedValueAfterCommand									m_valueAfterCommand;
	WrongValueFormat											m_wrongValueFormat;
	WrongInstructionFormat 										m_wrongInstrFormat;

	void 								fillPush(std::string const & value,
		 										std::shared_ptr<std::vector<Command *>> commandStack, int counter);
	void 								fillPop(std::string const & value,
												std::shared_ptr<std::vector<Command *>> commandStack, int counter);
	void 								fillDump(std::string const & value,
		 										std::shared_ptr<std::vector<Command *>> commandStack, int counter);
	void 								fillAssert(std::string const & value,
												std::shared_ptr<std::vector<Command *>> commandStack, int counter);
	void 								fillAdd(std::string const & value,
												std::shared_ptr<std::vector<Command *>> commandStack, int counter);
	void 								fillSub(std::string const & value,
												std::shared_ptr<std::vector<Command *>> commandStack, int counter);
	void 								fillMul(std::string const & value,
												std::shared_ptr<std::vector<Command *>> commandStack, int counter);
	void 								fillDiv(std::string const & value,
												std::shared_ptr<std::vector<Command *>> commandStack, int counter);
	void 								fillMod(std::string const & value,
												std::shared_ptr<std::vector<Command *>> commandStack, int counter);
	void 								fillPrint(std::string const & value,
												std::shared_ptr<std::vector<Command *>> commandStack, int counter);
	void 								fillExit(std::string const & value,
												std::shared_ptr<std::vector<Command *>> commandStack, int counter);
	void 								fillPower(std::string const & value,
												std::shared_ptr<std::vector<Command *>> commandStack, int counter);
	void 								fillRoot(std::string const & value,
												std::shared_ptr<std::vector<Command *>> commandStack, int counter);
	void 								fillRevert(std::string const & value,
												std::shared_ptr<std::vector<Command *>> commandStack, int counter);
	void 								fillMin(std::string const & value,
												std::shared_ptr<std::vector<Command *>> commandStack, int counter);
	void 								fillMax(std::string const & value,
												std::shared_ptr<std::vector<Command *>> commandStack, int counter);

	void 								fillValue(std::string const & value,
												std::shared_ptr<std::vector<Command *>> commandStack,
												int counter, eCommandType type);


};

#endif
