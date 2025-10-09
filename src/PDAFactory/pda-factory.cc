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
 * @file pda-factory.cc
 * @brief Implementation of PDAFactory class
 * @bug There are no known bugs
 * @see https://github.com/Edhey/practica-1-automata-con-pila.git
 * Revision history:
 */

#include "pda-factory.h"

/**
 * @brief Creates a PDA (Pushdown Automaton) of type ES (Empty Stack).
 * @param filename Path to the PDA definition file.
 * @return A unique pointer to the created PDA, or nullptr on error.
 */
std::unique_ptr<PDA> PDAFactory::createPDAES(const std::string& filename) {
  PdaESParser parser(filename);
  auto data = parser.parse();
  if (!data) {
    std::cerr << "Error parsing PDA file: " << data.error().message
              << " at line " << data.error().line_number << std::endl;
    return nullptr;
  }

  auto pda = std::make_unique<PDAES>();
  pda->setStates(data->states);
  pda->setInputAlphabet(data->input_alphabet);
  pda->setStackAlphabet(data->stack_alphabet);
  pda->setInitialState(data->initial_state);
  pda->setInitialStackSymbol(data->initial_stack_symbol);
  pda->resetStack();

  return pda;
}

/**
 * @brief Creates a PDA (Pushdown Automaton) of type FS (Final State).
 * @param filename Path to the PDA definition file.
 * @return A unique pointer to the created PDA, or nullptr on error.
 */
std::unique_ptr<PDA> PDAFactory::createPDAFS(const std::string& filename) {
  PdaFSParser parser(filename);
  auto data = parser.parse();
  if (!data) {
    std::cerr << "Error parsing PDA file: " << data.error().message
              << " at line " << data.error().line_number << std::endl;
    return nullptr;
  }

  auto pda = std::make_unique<PDAFS>();
  pda->setStates(data->states);
  pda->setInputAlphabet(data->input_alphabet);
  pda->setStackAlphabet(data->stack_alphabet);
  pda->setInitialState(data->initial_state);
  pda->setInitialStackSymbol(data->initial_stack_symbol);
  pda->resetStack();
  pda->setFinalStates(data->final_states);

  return pda;
}
