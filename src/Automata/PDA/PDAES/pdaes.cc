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
 * @brief Implementation of the class PDAES, a Pushdown Automaton that accepts
 * by Empty Stack
 * @bug There are no known bugs
 * @see https://github.com/Edhey/practica-1-automata-con-pila.git
 * Revision history:
 */

#include "pdaes.h"

/**
 * @brief Pushes a string onto the stack in reverse order
 * @param stack Stack to push onto
 * @param push_string String to push
 * @return true if all symbols are valid, false if there is an error
 */
bool PDAES::pushStringOntoStack(std::stack<char>& stack,
                                const std::string& push_string) {
  for (int i = static_cast<int>(push_string.size()) - 1; i >= 0; --i) {
    char symbol = push_string[i];

    if (symbol == PDA::EPSILON)
      continue;

    if (!checkStackAlphabet(symbol)) {
      std::cerr << "Error: Stack symbol '" << symbol
                << "' not in stack alphabet" << std::endl;
      return false;
    }

    stack.push(symbol);
  }
  return true;
}

/**
 * @brief Tries all transitions that consume an input symbol
 * @param state Current state
 * @param stack Current stack
 * @param input Remaining input string
 * @param stack_top Symbol at the top of the stack
 * @return true if any branch accepts, false otherwise
 */
bool PDAES::tryInputTransitions(
    const State<PDATransitionKey, PDATransitionValue>* state,
    std::stack<char> stack, const std::string& input, char stack_top) {
  if (input.empty())
    return false;

  char current_symbol = input[0];
  PDATransitionKey key{current_symbol, stack_top};

  auto range = state->getTransitions().equal_range(key);
  for (auto it = range.first; it != range.second; ++it) {
    const PDATransitionValue& transition = it->second;

    std::stack<char> new_stack = stack;
    new_stack.pop();

    if (!pushStringOntoStack(new_stack, transition.push_string))
      return false;

    if (isAcceptedRecursive(this->getStateById(transition.next_state_id),
                            new_stack, input.substr(1))) {
      return true;
    }
  }

  return false;
}

/**
 * @brief Tries all epsilon transitions (without consuming input)
 * @param state Current state
 * @param stack Current stack
 * @param input Remaining input string
 * @param stack_top Symbol at the top of the stack
 * @return true if any branch accepts, false otherwise
 */
bool PDAES::tryEpsilonTransitions(
    const State<PDATransitionKey, PDATransitionValue>* state,
    std::stack<char> stack, const std::string& input, char stack_top) {
  PDATransitionKey epsilon_key{PDA::EPSILON, stack_top};

  auto range = state->getTransitions().equal_range(epsilon_key);

  for (auto it = range.first; it != range.second; ++it) {
    const PDATransitionValue& transition = it->second;

    std::stack<char> new_stack = stack;
    new_stack.pop();

    if (!pushStringOntoStack(new_stack, transition.push_string))
      return false;

    if (isAcceptedRecursive(this->getStateById(transition.next_state_id),
                            new_stack, input)) {
      return true;
    }
  }

  return false;
}

/**
 * @brief Recursive function to check acceptance by empty stack
 * @param state Current state
 * @param stack Current stack
 * @param input Remaining input string
 * @return true if accepted, false otherwise
 */
bool PDAES::isAcceptedRecursive(
    const State<PDATransitionKey, PDATransitionValue>* state,
    std::stack<char> stack, const std::string& input) {
  if (stack.empty()) {
    return input.empty();
  }

  if (state == nullptr) {
    return false;
  }
  const char stack_top = stack.top();

  if (tryInputTransitions(state, stack, input, stack_top)) {
    return true;
  }

  if (tryEpsilonTransitions(state, stack, input, stack_top)) {
    return true;
  }

  return false;
}

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
  return isAcceptedRecursive(this->getStateById(this->initial_state),
                             this->stack, input);
}