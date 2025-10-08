/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Asignatura: Complejidad Computacional
 * Curso: 4º
 * Práctica 1: Pushdown Automaton Simulator
 * @author Himar Edhey Hernández Alonso
 * Correo: alu0101552392@ull.edu.es
 * @date Oct 06 2025
 * @file pdafs.cc
 * @brief Implementation of the class PDAFS
 * @bug There are no known bugs
 * @see https://github.com/Edhey/practica-1-automata-con-pila.git
 * Revision history:
 */

#include "pdafs.h"

bool PDAFS::pushStringOntoStack(std::stack<char>& st, const std::string& push) {
  for (int i = static_cast<int>(push.size()) - 1; i >= 0; --i) {
    char symbol = push[i];
    if (symbol == PDA::EPSILON)
      continue;
    if (!checkStackAlphabet(symbol))
      return false;
    st.push(symbol);
  }
  return true;
}

bool PDAFS::isAcceptingConfiguration(const Configuration& cfg,
                                     const std::string& input) const {
  if (cfg.input_position != input.size())
    return false;
  return final_states.find(cfg.state->getId()) != final_states.end();
}

void PDAFS::processInputTransitions(std::queue<Configuration>& q,
                                    const Configuration& current,
                                    const std::string& input) {
  if (current.input_position >= input.size())
    return;
  char stack_top = current.stack.top();
  char current_symbol = input[current.input_position];
  PDATransitionKey key{current_symbol, stack_top};

  const auto& transitions = current.state->getTransitions();
  auto range = transitions.equal_range(key);

  for (auto it = range.first; it != range.second; ++it) {
    const PDATransitionValue& transition = it->second;

    std::stack<char> new_stack = current.stack;
    new_stack.pop();

    if (!pushStringOntoStack(new_stack, transition.push_string))
      continue;

    State<PDATransitionKey, PDATransitionValue>* next_state =
        getStateById(transition.next_state_id);
    if (next_state != nullptr) {
      q.push(Configuration(next_state, new_stack, current.input_position + 1));
    }
  }
}

void PDAFS::processEpsilonTransitions(std::queue<Configuration>& q,
                                      const Configuration& current) {
  char stack_top = current.stack.top();
  PDATransitionKey epsilon_key{PDA::EPSILON, stack_top};

  const auto& transitions = current.state->getTransitions();
  auto range = transitions.equal_range(epsilon_key);

  for (auto it = range.first; it != range.second; ++it) {
    const PDATransitionValue& transition = it->second;

    std::stack<char> new_stack = current.stack;
    new_stack.pop();

    if (!pushStringOntoStack(new_stack, transition.push_string))
      continue;

    State<PDATransitionKey, PDATransitionValue>* next_state =
        getStateById(transition.next_state_id);
    if (next_state != nullptr) {
      q.push(Configuration(next_state, new_stack, current.input_position));
    }
  }
}

bool PDAFS::isAccepted(const std::string& input) {
  if (!this->checkInputAlphabet(input)) {
    std::cerr
        << "Error: Input string contains symbols not in the input alphabet"
        << std::endl;
    return false;
  }
  this->resetStack();

  State<PDATransitionKey, PDATransitionValue>* initial_state =
      this->getStateById(this->initial_state);
  if (initial_state == nullptr) {
    std::cerr << "Error: Initial state not found" << std::endl;
    return false;
  }

  std::queue<Configuration> queue;
  queue.push(Configuration(initial_state, this->stack, 0));

  while (!queue.empty()) {
    Configuration current = queue.front();
    queue.pop();

    if (isAcceptingConfiguration(current, input))
      return true;
    if (current.stack.empty())
      continue;

    processInputTransitions(queue, current, input);
    processEpsilonTransitions(queue, current);
  }

  return false;
}