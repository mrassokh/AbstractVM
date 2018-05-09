/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Exceptions.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrassokh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/29 08:28:40 by mrassokh          #+#    #+#             */
/*   Updated: 2018/04/29 08:28:47 by mrassokh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXCEPTIONS_HPP
# define EXCEPTIONS_HPP
# include <exception>

class   Exit : public std::exception {
		const char * what () const throw ();
};

class   WrongStringFormat : public std::exception {
		const char * what () const throw ();
};

class   WrongInstructionFormat : public std::exception {
		const char * what () const throw ();
};

class   EmptyFile : public std::exception {
		const char * what () const throw ();
};

class  WrongValueFormat : public std::exception {
		const char * what () const throw ();
};

class  UnexpectedValueAfterCommand : public std::exception {
		const char * what () const throw ();
};

class  WrongInputArgumentCount: public std::exception {
		const char * what () const throw ();
};

class ExitNotFind : public std::exception {
		const char * what () const throw ();
};

class TopStackIsNotINT8 : public std::exception {
		const char * what () const throw ();
};

class CharIsNotPrintable : public std::exception {
		const char * what () const throw ();
};

class StackSizeLessTwo : public std::exception {
		const char * what () const throw ();
};

class AssertFail : public std::exception {
		const char * what () const throw ();
};

class StackIsEmpty : public std::exception {
		const char * what () const throw ();
};

class ValueOverflowException : public std::exception {
		const char * what () const throw ();
};


class ValueUnderflowException : public std::exception {
	 const char * what () const throw ();
};

class ValueUnderflowOrOverflowException : public std::exception {
	 const char * what () const throw ();
};

class DivideByZeroException : public std::exception {
	 const char * what () const throw ();
};

class ModByZeroException : public std::exception {
	 const char * what () const throw ();
};

#endif
