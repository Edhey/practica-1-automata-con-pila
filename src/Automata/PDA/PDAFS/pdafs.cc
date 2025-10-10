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

/**
 * @brief Pushes a string of symbols onto the stack in reverse order.
 * This function iterates over the given string from end to beginning,
 * pushing each symbol onto the provided stack. Symbols equal to PDA::EPSILON
 * are skipped. Before pushing, each symbol is checked against the stack
 * alphabet using checkStackAlphabet(). If any symbol is not valid, the function
 * returns false and stops pushing further symbols.
 *
 * @param stack Reference to the stack where symbols will be pushed.
 * @param push_string The string of symbols to push onto the stack.
 * @return true if all symbols were successfully pushed; false if any symbol is
 * invalid.
 */
bool PDAFS::pushStringOntoStack(std::stack<char>& stack,
                                const std::string& push_string) {
  for (int i = static_cast<int>(push_string.size()) - 1; i >= 0; --i) {
    char symbol = push_string[i];
    if (symbol == PDA::EPSILON)
      continue;
    if (!checkStackAlphabet(symbol))
      return false;
    stack.push(symbol);
  }
  return true;
}

/**
 * @brief Checks if a given configuration is accepting for the PDA.
 * Determines whether the provided configuration is in an accepting state,
 * which requires that the entire input has been processed and the current
 * state is one of the final states.
 *
 * @param configuration The current configuration of the PDA, including state
 * and input position.
 * @param input The input string being processed by the PDA.
 * @return true if the configuration is accepting (input fully consumed and
 * state is final), false otherwise.
 */
bool PDAFS::isAcceptingConfiguration(const Configuration& configuration,
                                     const std::string& input) const {
  if (configuration.input_position != input.size())
    return false;
  return final_states.find(configuration.state->getId()) != final_states.end();
}

void PDAFS::processInputTransitions(std::queue<Configuration>& queue,
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
      queue.push(Configuration(next_state, new_stack, current.input_position + 1));
    }
  }
}

/**
 * @brief Processes epsilon (empty input) transitions for a given PDA
 * configuration. This function examines all possible epsilon transitions from
 * the current state, using the top symbol of the stack. For each valid epsilon
 * transition, it updates the stack according to the transition's push string,
 * and enqueues the resulting configuration into the provided configuration
 * queue for further exploration.
 *
 * @param config_queue Queue to which new configurations resulting from epsilon
 * transitions are added.
 * @param current The current PDA configuration, including state, stack, and
 * input position.
 */
void PDAFS::processEpsilonTransitions(std::queue<Configuration>& config_queue,
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
      config_queue.push(
          Configuration(next_state, new_stack, current.input_position));
    }
  }
}

/**
 * @brief Determines whether a given input string is accepted by the pushdown
 * automaton.
 * This function checks if the input string consists only of symbols from the
 * input alphabet. It then simulates the automaton's execution using a
 * breadth-first search over possible configurations, considering both
 * input-consuming and epsilon transitions. The function returns true if an
 * accepting configuration is reached, and false otherwise.
 *
 * @param input The input string to be checked for acceptance.
 * @return true if the input string is accepted by the automaton, false
 * otherwise.
 */
bool PDAFS::isAccepted(
    const std::string& input,
    std::optional<std::reference_wrapper<std::ostream>> trace) {
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