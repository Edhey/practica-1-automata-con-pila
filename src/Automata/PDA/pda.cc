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
 * @file pda.cc
 * @brief Implementation of PDA class
 * @bug There are no known bugs
 * @see https://github.com/Edhey/practica-1-automata-con-pila.git
 * Revision history:
 */

#include "pda.h"

/**
 * @brief Resets the stack to its initial state.
 *
 * This function clears all elements from the stack and pushes the initial stack
 * symbol to ensure the stack starts with the correct configuration for the
 * automaton.
 */
void PDA::resetStack() {
  while (!stack.empty()) {
    stack.pop();
  }
  stack.push(initial_stack_symbol);
}

/**
 * @brief Converts the stack to a string representation.
 * @param stack The stack to convert.
 * @return A string representing the stack contents from top to bottom.
 */
std::string PDA::stackToString(const std::stack<char>& stack) const {
  std::stack<char> temp_stack = stack;
  std::string result;
  while (!temp_stack.empty()) {
    result += temp_stack.top();
    temp_stack.pop();
  }
  if (result.empty()) {
    result = PDA::EPSILON;
  }
  return result;
}

/**
 * @brief Prints the current configuration of the PDA.
 * @param out The output stream to print to.
 * @param stack The current stack of the PDA.
 * @param state The current state of the PDA.
 * @param input The remaining input string.
 * @return The output stream.
 */
std::ostream& PDA::printConfiguration(
    std::ostream& out, const std::stack<char>& stack,
    const State<PDATransitionKey, PDATransitionValue>& state,
    const std::string& input, int depth) const {
  std::string input_display =
      input.empty() ? std::string(1, PDA::EPSILON) : input;
  out << std::left << " | " << std::setw(15) << state.getId() << " | "
      << std::setw(15) << input_display << " | " << std::setw(15)
      << stackToString(stack) << " | " << std::setw(15) << depth << " | "
      << std::setw(15)
      << PDATransitionPrinter::formatTransition(state.getTransitions());
  out << " |\n";
  return out;
}

/**
 * @brief Prints the header for the PDA configuration output.
 * @param out The output stream to print to.
 * @return The output stream.
 */
std::ostream& PDA::printHeader(std::ostream& out) const {
  const int kWidth = 15;
  const int kBarsNum = 5;
  const int kBarsWidth = 3;
  const int kTotalWidth = kWidth * kBarsNum + kBarsWidth * (kBarsNum + 1);
  out << std::left << " | " << std::setw(kWidth) << "State"
      << " | " << std::setw(kWidth) << "Input"
      << " | " << std::setw(kWidth) << "Stack"
      << " | " << std::setw(kWidth) << "Depth"
      << " | " << std::setw(kWidth) << "Transition"
      << " |\n";
  out << std::string(kTotalWidth, '-') << "\n";
  return out;
}
