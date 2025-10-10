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
 * @file main.cc
 * @brief Main file for the Pushdown Automaton Simulator
 * @bug There are no known bugs
 * @see https://github.com/Edhey/practica-1-automata-con-pila.git
 * Revision history:
 */

#include <fstream>
#include <iostream>
#include <memory>

#include "IO/InputStrategy/console-input-strategy.h"
#include "IO/InputStrategy/file-input-strategy.h"
#include "IO/OutputStrategy/console-output-strategy.h"
#include "IO/OutputStrategy/file-output-strategy.h"
#include "PDAFactory/pda-factory.h"
#include "Parser/args-parser.h"

/**
 * @brief Creates the appropriate input strategy based on arguments
 */
std::unique_ptr<InputStrategy> createInputStrategy(const ArgsParser& args) {
  if (args.hasInputStringsFile()) {
    return std::make_unique<FileInputStrategy>(args.getInputStringsFile());
  }
  return std::make_unique<ConsoleInputStrategy>();
}

/**
 * @brief Creates the appropriate output strategy based on arguments
 */
std::unique_ptr<OutputStrategy> createOutputStrategy(const ArgsParser& args) {
  if (args.hasOutputFile()) {
    return std::make_unique<FileOutputStrategy>(args.getOutputFile(),
                                                args.isTraceEnabled());
  }
  return std::make_unique<ConsoleOutputStrategy>(args.isTraceEnabled());
}

/**
 * @brief Processes input strings through the automaton
 */
void processInputs(PDA* pda, InputStrategy* input_strategy,
                   OutputStrategy* output_strategy) {
  auto inputs_opt = input_strategy->readInputs();

  if (!inputs_opt.has_value()) {
    std::cerr << "Error: Could not read inputs" << std::endl;
    return;
  }

  const auto& inputs = inputs_opt.value();
  auto trace_stream = output_strategy->getStream();

  std::cout << "\nProcessing " << inputs.size() << " input string(s)...\n"
            << std::endl;

  for (const auto& input : inputs) {
    bool accepted = pda->isAccepted(input, trace_stream);
    output_strategy->writeResult(input, accepted);
  }

  output_strategy->finalize();
}

/**
 * @brief Main entry point
 */
int main(int argc, char* argv[]) {
  auto args_opt = ArgsParser::parse(argc, argv);
  if (!args_opt.has_value()) {
    return 1;
  }

  ArgsParser args = args_opt.value();

  auto pda =
      PDAFactory::createAutomata(args.getAutomataType(), args.getInputFile());
  if (!pda) {
    std::cerr << "Error: Could not create automaton" << std::endl;
    return 1;
  }
  std::cout << "Automaton created successfully!\n" << std::endl;

  auto input_strategy = createInputStrategy(args);
  auto output_strategy = createOutputStrategy(args);

  processInputs(pda.get(), input_strategy.get(), output_strategy.get());

  return 0;
}
