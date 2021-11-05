#pragma once

#include "IOperation.h"

constexpr int PLUS_PRIORITY = 10;
constexpr int MUL_PRIORITY = 20;

class IBinaryOperator : public IOperation {
public:
	enum class AssocType {
		LEFT,
		RIGHT
	};

	virtual AssocType GetAssocType() const noexcept = 0;
	virtual double operator()(double lhs, double rhs) const = 0;
	virtual int Priority() const noexcept = 0;
};

class IUnaryOperator : public IOperation {
public:
	enum class AffixType {
		PREFIX,
		POSTFIX
	};
	virtual AffixType GetAffixType() const noexcept = 0;
	virtual double operator()(double val) const = 0;
};
