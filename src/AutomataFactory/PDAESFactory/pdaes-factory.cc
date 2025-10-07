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
 * @file pdaes-factory.cc
 * @brief Implementation of PDAESFactory class
 * @bug There are no known bugs
 * @see https://github.com/Edhey/practica-1-automata-con-pila.git
 * Revision history:
 */

#include "pdaes-factory.h"

PDAESFactory::PDAESFactory(const std::string& filename) : filename_(filename) {}

std::unique_ptr<Automata<PDATransitionKey, PDATransitionValue>>
PDAESFactory::CreateAutomaton() {
  PdaESParser parser(filename_);
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