/*
 * Copyright 2020 Casey Sanchez
 */

#include "expression_composer.hpp"

ExpressionComposer::ExpressionComposer(std::shared_ptr<Node> const &node_ptr, std::map<std::string, std::shared_ptr<Node>> const &node_map) : node_ptr(node_ptr), node_map(node_map)
{
}

std::string ExpressionComposer::Compose() const
{
    return Compose(node_ptr);
}

std::string ExpressionComposer::Compose(std::shared_ptr<Node> const &node_ptr, uint32_t precedence) const
{
    if (node_ptr->Type() == "Variable") {
        auto node_it = std::find_if(std::cbegin(node_map), std::cend(node_map), 
            [node_ptr](std::pair<std::string, std::shared_ptr<Node>> const &node_pair) {  
                return node_pair.second == node_ptr;
            });

        if (node_it != std::cend(node_map)) {
            return node_it->first;
        }
        else {
            return std::to_string(node_ptr->Value());
        }
    }
    else if (node_ptr->Type() == "Constant") {
        auto node_it = std::find_if(std::cbegin(node_map), std::cend(node_map), 
            [node_ptr](std::pair<std::string, std::shared_ptr<Node>> const &node_pair) {  
                return node_pair.second == node_ptr;
            });

        if (node_it != std::cend(node_map)) {
            return node_it->first;
        }
        else {
            return std::to_string(node_ptr->Value());
        }
    }
    else if (node_ptr->Type() == "Exponentiation") {
        std::shared_ptr<Exponentiation> exponentiation = std::dynamic_pointer_cast<Exponentiation>(node_ptr);

        return Compose(exponentiation->LhsPtr(), 0) + "^" + Compose(exponentiation->RhsPtr(), 0);
    }
    else if (node_ptr->Type() == "Affirmation") {
        std::shared_ptr<Affirmation> affirmation = std::dynamic_pointer_cast<Affirmation>(node_ptr);

        if (precedence < 1) {
            return "(+" + Compose(affirmation->NodePtr(), 1) + ")";
        }

        return "+" + Compose(affirmation->NodePtr(), 1);
    }
    else if (node_ptr->Type() == "Negation") {
        std::shared_ptr<Negation> negation = std::dynamic_pointer_cast<Negation>(node_ptr);

        if (precedence < 1) {
            return "(-" + Compose(negation->NodePtr(), 1) + ")";
        }

        return "-" + Compose(negation->NodePtr(), 1);
    }
    else if (node_ptr->Type() == "Multiplication") {
        std::shared_ptr<Multiplication> multiplication = std::dynamic_pointer_cast<Multiplication>(node_ptr);

        if (precedence < 2) {
            return "(" + Compose(multiplication->LhsPtr(), 2) + "*" + Compose(multiplication->RhsPtr(), 2) + ")";
        }

        return Compose(multiplication->LhsPtr(), 2) + "*" + Compose(multiplication->RhsPtr(), 2);
    }
    else if (node_ptr->Type() == "Division") {
        std::shared_ptr<Division> division = std::dynamic_pointer_cast<Division>(node_ptr);

        if (precedence < 2) {
            return "(" + Compose(division->LhsPtr(), 2) + "/" + Compose(division->RhsPtr(), 2) + ")";
        }

        return Compose(division->LhsPtr(), 2) + "/" + Compose(division->RhsPtr(), 2);
    }
    else if (node_ptr->Type() == "Addition") {
        std::shared_ptr<Addition> addition = std::dynamic_pointer_cast<Addition>(node_ptr);

        if (precedence < 3) {
            return "(" + Compose(addition->LhsPtr(), 3) + "+" + Compose(addition->RhsPtr(), 3) + ")";
        }

        return Compose(addition->LhsPtr(), 3) + "+" + Compose(addition->RhsPtr(), 3);
    }
    else if (node_ptr->Type() == "Subtraction") {
        std::shared_ptr<Subtraction> subtraction = std::dynamic_pointer_cast<Subtraction>(node_ptr);

        if (precedence < 3) {
            return "(" + Compose(subtraction->LhsPtr(), 3) + "-" + Compose(subtraction->RhsPtr(), 3) + ")";
        }

        return Compose(subtraction->LhsPtr(), 3) + "-" + Compose(subtraction->RhsPtr(), 3);
    }
    else if (node_ptr->Type() == "Sin") {
        std::shared_ptr<Sin> sin = std::dynamic_pointer_cast<Sin>(node_ptr);

        return "sin" + Compose(sin->NodePtr(), 0);
    }
    else if (node_ptr->Type() == "Cos") {
        std::shared_ptr<Cos> cos = std::dynamic_pointer_cast<Cos>(node_ptr);

        return "cos" + Compose(cos->NodePtr(), 0);
    }
    else if (node_ptr->Type() == "Tan") {
        std::shared_ptr<Tan> tan = std::dynamic_pointer_cast<Tan>(node_ptr);

        return "tan" + Compose(tan->NodePtr(), 0);
    }
    else if (node_ptr->Type() == "Asin") {
        std::shared_ptr<Asin> asin = std::dynamic_pointer_cast<Asin>(node_ptr);

        return "asin" + Compose(asin->NodePtr(), 0);
    }
    else if (node_ptr->Type() == "Acos") {
        std::shared_ptr<Acos> acos = std::dynamic_pointer_cast<Acos>(node_ptr);

        return "acos" + Compose(acos->NodePtr(), 0);
    }
    else if (node_ptr->Type() == "Atan") {
        std::shared_ptr<Atan> atan = std::dynamic_pointer_cast<Atan>(node_ptr);

        return "atan" + Compose(atan->NodePtr(), 0);
    }
    else if (node_ptr->Type() == "Sqrt") {
        std::shared_ptr<Sqrt> sqrt = std::dynamic_pointer_cast<Sqrt>(node_ptr);

        return "sqrt" + Compose(sqrt->NodePtr(), 0);
    }
    else if (node_ptr->Type() == "Abs") {
        std::shared_ptr<Abs> abs = std::dynamic_pointer_cast<Abs>(node_ptr);

        return "abs" + Compose(abs->NodePtr(), 0);
    }
    else if (node_ptr->Type() == "Exp") {
        std::shared_ptr<Exp> exp = std::dynamic_pointer_cast<Exp>(node_ptr);

        return "exp" + Compose(exp->NodePtr(), 0);
    }
    else if (node_ptr->Type() == "Log") {
        std::shared_ptr<Log> log = std::dynamic_pointer_cast<Log>(node_ptr);

        return "log" + Compose(log->NodePtr(), 0);
    }

    throw std::invalid_argument("Node of unknown type: " + node_ptr->Type());
}