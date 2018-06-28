/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Operand.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrassokh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/02 09:40:48 by mrassokh          #+#    #+#             */
/*   Updated: 2018/05/02 09:40:53 by mrassokh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPERAND_HPP
#define OPERAND_HPP
#include "IOperand.hpp"
#include "OperandFactory.hpp"
#include "Exceptions.hpp"
#include <cmath>
#include <vector>
#include <algorithm>
#include <climits>
#include <cfloat>
#include <iomanip>

//ENUMERATION FOR ARITHMETIC ACTIONS
enum eARITHMETIC{
    ADD,
    SUB,
    MUL,
    DIV,
    MOD
};

class OperandFactory;

template <class T, eOperandType operandType>
    class Operand : public IOperand
    {
     public:
         Operand();
         Operand(std::string value);
         Operand(Operand const & rhs);
         Operand& operator = (Operand const & rhs);
         virtual ~Operand();

         virtual int getPrecision( void ) const; // Precision of the type of the instance
         virtual eOperandType getType( void ) const; // Type of the instance
         virtual IOperand const * operator + ( IOperand const & rhs ) const; // Sum
         virtual IOperand const * operator - ( IOperand const & rhs ) const; // Difference
         virtual IOperand const * operator * ( IOperand const & rhs ) const; // Product
         virtual IOperand const * operator / ( IOperand const & rhs ) const; // Quotient
         virtual IOperand const * operator % ( IOperand const & rhs ) const; // Modulo
         virtual std::string const & toString( void ) const; // String representation of the instance

	 T                                              		getValue() const;
	 std::vector<void* (*)(std::string const & value)>      	getToValueFunction() const;
	std::vector<std::string (*)(double const &leftValue,
		 		double const &rightValue)>		getResultFunction() const;
	 OperandFactory*                                		getOperandFactory() const;
         void                                           		setOperandFactory(const OperandFactory* operandFactory);

    private:
		T*   	                                          	m_operand;
         	OperandFactory*                                		m_operandFactory;
         	eOperandType                                   		m_operandType;
         	int                                            		m_precision;

		 //Output value
		 std::string                                    	m_toStringOutput;

		 //Array of pointers to functions which convert string value to accordingly type
         	std::vector<void* (*)(std::string const & value)>      m_toValueFunc;

		 //Array of pointers to ARITHMETIC functions which returns result in string representation
		 std::vector<std::string (*)(
			 double const &leftValue,
			 double const &rightValue)>     		m_resultFunc;

		 //Create new m_operand from string value using m_toValueFunc
		 void*                                          	createMOperand(std::string const & value) const;

		 //Initialize new Operand class
		 void                                           	init();
		 void                                           	first_step_init();

		 //Functions which convert string value to accordingly type
         	static void						*toInt8(std::string const & value);
         	static void						*toInt16(std::string const & value);
         	static void						*toInt32(std::string const & value);
         	static void						*toFloat(std::string const & value);
         	static void 						*toDouble(std::string const & value);

		 //ARITHMETIC functions which returns result in string representation
		 static std::string					resultAdd(double const & leftValue, double const & rightValue);
		 static std::string					resultSub(double const & leftValue, double const & rightValue);
		 static std::string					resultMult(double const & leftValue, double const & rightValue);
		 static std::string					resultDiv(double const & leftValue, double const & rightValue);
		 static std::string					resultMod(double const & leftValue, double const &rightValue);

		 //Exceptions
		 static ValueOverflowException 				exceptOverflow;
		 static ValueUnderflowException 			exceptUnderflow;
	 	 static DivideByZeroException				exceptDivideZero;
	 	 static	ModByZeroException				exceptModZero;
	 	 static	ValueUnderflowOrOverflowException		exceptUnderflowOverflow;
	};
#endif // OPERAND_HPP
