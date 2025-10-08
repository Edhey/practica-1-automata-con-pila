/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Asignatura: Complejidad Computacional
 * Curso: 4º
 * Práctica 1: Pushdown Automaton Simulator
 * @author Himar Edhey Hernández Alonso
 * Correo: alu0101552392@ull.edu.es
 * @date Sep 15 2025
 * @file pdaes.cc
 * @brief Declaration of the class PDAES, a Pushdown Automaton that accepts by
 * Empty Stack
 * @bug There are no known bugs
 * @see https://github.com/Edhey/practica-1-automata-con-pila.git
 * Revision history:
 */

#include "pdaes.h"

#include <format>

/**
 * @brief Checks if the input string is accepted by the PDA.
 * @param input The input string to be checked.
 * @return True if the input is accepted, false otherwise.
 */
bool PDAES::isAccepted(const std::string& input) {
  if (!this->checkInputAlphabet(input)) {
    std::cerr
        << "Error: Input string contains symbols not in the input alphabet"
        << std::endl;
    return false;
  }
  this->resetStack();
  return isAccepted(this->getStateById(this->initial_state), this->stack,
                    input);
}

bool PDAES::isAccepted(const State<PDATransitionKey, PDATransitionValue>* state,
                       std::stack<char> stack, std::string input) {
  if (stack.empty()) {
    if (input.empty() || (input[0] == PDA::EPSILON && input.size() == 1)) {
      return true;
    } else {
      return false;
    }
  }

  if (state == nullptr) {
    return false;
  }

  const char stack_top = stack.top();
  if (!input.empty()) {
    char current_symbol = input[0];
    PDATransitionKey key{current_symbol, stack_top};

    auto range = state->getTransitions().equal_range(key);
    for (auto it = range.first; it != range.second; ++it) {
      const PDATransitionValue& transition = it->second;
      std::stack<char> new_stack = stack;
      new_stack.pop();
      for (int i = transition.push_string.size() - 1; i >= 0; --i) {
        char symbol = transition.push_string[i];
        if (symbol != PDA::EPSILON && !checkStackAlphabet(symbol)) {
          std::cerr << "Error: Stack symbol '" << symbol
                    << "' not in stack alphabet" << std::endl;
          return false;
        }
        if (symbol != PDA::EPSILON) {
          new_stack.push(symbol);
        }
      }
      if (isAccepted(this->getStateById(transition.next_state_id), new_stack,
                     input.substr(1))) {
        return true;
      }
    }
  }

  PDATransitionKey epsilon_key{PDA::EPSILON, stack_top};
  auto range = state->getTransitions().equal_range(epsilon_key);
  for (auto it = range.first; it != range.second; ++it) {
    const PDATransitionValue& transition = it->second;
    std::stack<char> new_stack = stack;
    new_stack.pop();
    for (int i = transition.push_string.size() - 1; i >= 0; --i) {
      char symbol = transition.push_string[i];
      if (symbol != PDA::EPSILON && !checkStackAlphabet(symbol)) {
        std::cerr << std::format(
                         "Error: Stack symbol '{}' not in stack alphabet",
                         symbol)
                  << std::endl;
        return false;
      }
      if (symbol != PDA::EPSILON) {
        new_stack.push(symbol);
      }
    }
    if (isAccepted(this->getStateById(transition.next_state_id), new_stack,
                   input)) {
      return true;
    }
  }

  return false;
}