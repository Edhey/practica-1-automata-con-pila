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
 * @file args-parser.cc
 * @brief Implementation of the class ArgsParser
 * @bug There are no known bugs
 * @see https://github.com/Edhey/practica-1-automata-con-pila.git
 * Revision history:
 */

#include "args-parser.h"

#include <iostream>

void ArgsParser::printUsage() {
  std::cout
      << "Usage: stack-automaton <mode> <input_file.txt> [options]\n\n"
      << "Modes:\n"
      << "  <es|PDAES|emptystack> - Empty Stack PDA\n"
      << "  <fs|PDAFS|finalstate> - Final State PDA\n\n"
      << "Options:\n"
      << "  -i, --input <file>     Read input strings from file\n"
      << "  -o, --output <file>    Write results to file\n"
      << "  -t, --trace            Enable execution trace\n"
      << "  -h, --help             Show this help message\n\n"
      << "Examples:\n"
      << "  stack-automaton es automaton.txt\n"
      << "  stack-automaton fs automaton.txt -i strings.txt -o results.txt\n"
      << "  stack-automaton PDAES automaton.txt --trace\n"
      << "  stack-automaton PDAFS automaton.txt -i strings.txt -t -o trace.txt\n"
      << std::endl;
}

std::optional<ArgsParser> ArgsParser::parse(int argc, char* argv[]) {
  if (argc < 3) {
    std::cerr << "Error: Insufficient arguments\n" << std::endl;
    printUsage();
    return std::nullopt;
  }

  for (int i = 1; i < argc; ++i) {
    std::string arg = argv[i];
    if (arg == "-h" || arg == "--help") {
      printUsage();
      return std::nullopt;
    }
  }

  std::string mode = argv[1];
  AutomataType type;

  if (mode == "es") {
    type = AutomataType::PDAES;
  } else if (mode == "fs") {
    type = AutomataType::PDAFS;
  } else {
    std::cerr << "Error: Invalid mode '" << mode << "'\n" << std::endl;
    printUsage();
    return std::nullopt;
  }

  std::string input_file = argv[2];
  std::optional<std::string> input_strings_file;
  std::optional<std::string> output_file;
  bool trace_enabled = false;

  for (int i = 3; i < argc; ++i) {
    std::string arg = argv[i];

    if (arg == "-i" || arg == "--input") {
      if (i + 1 >= argc) {
        std::cerr << "Error: Missing argument for " << arg << std::endl;
        return std::nullopt;
      }
      input_strings_file = argv[++i];
    } else if (arg == "-o" || arg == "--output") {
      if (i + 1 >= argc) {
        std::cerr << "Error: Missing argument for " << arg << std::endl;
        return std::nullopt;
      }
      output_file = argv[++i];
    } else if (arg == "-t" || arg == "--trace") {
      trace_enabled = true;
    } else {
      std::cerr << "Error: Unknown option '" << arg << "'\n" << std::endl;
      printUsage();
      return std::nullopt;
    }
  }

  return ArgsParser(type, input_file, input_strings_file, output_file,
                    trace_enabled);
}
