/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Exceptions.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrassokh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/29 08:27:43 by mrassokh          #+#    #+#             */
/*   Updated: 2018/04/29 08:27:45 by mrassokh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Exceptions.hpp"

const char *  Exit::what () const throw ()
{
   return "exit!!!";
}

const char *  WrongStringFormat::what () const throw ()
{
   return "Wrong string format!";
}

const char *  WrongInstructionFormat::what () const throw ()
{
   return "Wrong instruction format!";
}

const char *  EmptyFile::what () const throw ()
{
   return "Empty file!";
}

const char *  WrongValueFormat::what () const throw ()
{
   return "Wrong Value Format!";
}


const char *  UnexpectedValueAfterCommand::what () const throw ()
{
   return "Unexpected value after command!";
}

const char *  WrongInputArgumentCount::what () const throw ()
{
   return "Input one file or nothing, please!";
}

const char *  ExitNotFind::what () const throw ()
{
   return "Exit not find!";
}

const char *  TopStackIsNotINT8::what () const throw ()
{
   return "Top of the stack is not char!";
}

const char *  CharIsNotPrintable::what () const throw ()
{
   return "Char is not printable!";
}

const char *  StackSizeLessTwo::what () const throw ()
{
   return "StackSize less then 2! Arithmetic operation forbidden!";
}

const char *  AssertFail::what () const throw ()
{
   return "Assert fail! Why? It's very very dark matter!";
}

const char *  StackIsEmpty::what () const throw ()
{
   return "My dear child! Stack is empty! Go home!";
}

const char *  ValueOverflowException::what () const throw ()
{
   return "Value of operand overflow!!!";
}

const char *  ValueUnderflowException::what () const throw ()
{
   return "Value of operand underflow!!!";
}

const char *  ValueUnderflowOrOverflowException::what () const throw ()
{
   return "Value of new operand overflow or underflow!!!";
}


const char *  DivideByZeroException::what () const throw ()
{
   return "Divide by zero!!!";
}

const char *  ModByZeroException::what () const throw ()
{
   return "Mod by zero!!!";
}
