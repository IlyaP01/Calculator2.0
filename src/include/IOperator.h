/**
 * @file
 * @brief IBinaryOperator and IUnaryOperator header file
 * @authors Pavlov Ilya
 *
 * Contains IBinaryOperator and IUnaryOperator pure virtual classes declarations
 */

#pragma once

#include "IOperation.h"

constexpr int PLUS_PRIORITY = 10; ///< Priority of sum for using in dlls
constexpr int MUL_PRIORITY = 20;  ///< Priority of multiplication for using in dlls

/**
 * Interface for all loaded binary operators 
 */
class IBinaryOperator : public IOperation {
public:
	/**
	 * Associativity type
	 */
	enum class AssocType {
		LEFT,
		RIGHT
	};

	/**
	 * Returns associativity type of operator
	 * @return associativity type of operator
	 */
	virtual AssocType GetAssocType() const noexcept = 0;

	/**
	 * Apply operator
	 * @return result
	 */
	virtual double operator()(double lhs, double rhs) const = 0;
	virtual int Priority() const noexcept = 0;
};

/**
 * Interface for all loaded unary operators
 */
class IUnaryOperator : public IOperation {
public:
	/**
	 * Affix type 
	 */
	enum class AffixType {
		PREFIX,
		POSTFIX
	};

	/**
	 * Returns affix type of operator
	 * @return affix type of operator
	 */
	virtual AffixType GetAffixType() const noexcept = 0;

	/**
	 * Apply operator
	 * @return result
	 */
	virtual double operator()(double val) const = 0;
};
