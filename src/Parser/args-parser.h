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
 * @file args-parser.h
 * @brief Command line arguments parser
 * @bug There are no known bugs
 * @see https://github.com/Edhey/practica-1-automata-con-pila.git
 * Revision history:
 */

#ifndef ARGSPARSER_H_
#define ARGSPARSER_H_

#include <iostream>
#include <stdexcept>
#include <string>

#include "../PDAFactory/pda-type.h"

/**
 * @brief Clase para parsear argumentos de línea de comandos
 */
class ArgsParser {
public:
  std::string input_file;
  std::string output_file;
  PDAType automata_type;
  bool trace_mode = false;

  /**
   * @brief Constructor que parsea los argumentos
   */
  ArgsParser(int argc, char* argv[]) {
    if (argc < 3) {
      printUsage(argv[0]);
      throw std::invalid_argument("Insufficient arguments");
    }

    try {
      automata_type = AutomataTypeHelper::fromString(argv[1]);
    } catch (const std::invalid_argument& e) {
      std::cerr << "Error: " << e.what() << std::endl;
      printUsage(argv[0]);
      throw;
    }

    input_file = argv[2];

    for (int i = 3; i < argc; ++i) {
      std::string arg = argv[i];

      if (arg == "-o" || arg == "--output") {
        if (i + 1 < argc) {
          output_file = argv[++i];
        } else {
          throw std::invalid_argument(
              "Option -o/--output requires an argument");
        }
      } else if (arg == "-t" || arg == "--trace") {
        trace_mode = true;
      } else if (arg == "-h" || arg == "--help") {
        printUsage(argv[0]);
        std::exit(0);
      } else {
        std::cerr << "Warning: Unknown option '" << arg << "'" << std::endl;
      }
    }
  }

private:
  void printUsage(const char* program_name) {
    std::cout << "Usage: " << program_name
              << " <type> <input_file> [options]\n\n"
              << "Arguments:\n"
              << "  <type>         Automata type: es|fs|PDAES|PDAFS\n"
              << "  <input_file>   Path to the automata definition file\n\n"
              << "Options:\n"
              << "  -o, --output <file>   Write trace/results to file\n"
              << "  -t, --trace           Enable trace mode\n"
              << "  -h, --help            Show this help message\n\n"
              << "Examples:\n"
              << "  " << program_name << " es automata.pda\n"
              << "  " << program_name
              << " PDAFS automata.pda -o output.txt -t\n";
  }
};

#endif  // ARGSPARSER_H_