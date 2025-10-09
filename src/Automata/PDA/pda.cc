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
 * This function clears all elements from the stack and pushes the initial stack symbol
 * to ensure the stack starts with the correct configuration for the automaton.
 */
void PDA::resetStack() {
  while (!stack.empty()) {
    stack.pop();
  }
  stack.push(initial_stack_symbol);
}
