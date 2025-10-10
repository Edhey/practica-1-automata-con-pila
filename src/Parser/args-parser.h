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
 * @brief Definition of the class ArgsParser
 * @bug There are no known bugs
 * @see https://github.com/Edhey/practica-1-automata-con-pila.git
 * Revision history:
 */

#ifndef PARSER_ARGS_PARSER_H_
#define PARSER_ARGS_PARSER_H_

#include <optional>
#include <string>

#include "../PDAFactory/pda-type.h"

class ArgsParser {
public:
  static void printUsage();
  static std::optional<ArgsParser> parse(int argc, char* argv[]);
  AutomataType getAutomataType() const { return automata_type_; }
  std::string getInputFile() const { return input_file_; }
  bool hasInputStringsFile() const { return input_strings_file_.has_value(); }
  std::string getInputStringsFile() const {
    return input_strings_file_.value();
  }
  bool hasOutputFile() const { return output_file_.has_value(); }
  std::string getOutputFile() const { return output_file_.value(); }
  bool isTraceEnabled() const { return trace_enabled_; }

private:
  ArgsParser(AutomataType type, const std::string& file,
             std::optional<std::string> input_strings,
             std::optional<std::string> output, bool trace)
      : automata_type_(type),
        input_file_(file),
        input_strings_file_(input_strings),
        output_file_(output),
        trace_enabled_(trace) {}

  AutomataType automata_type_;
  std::string input_file_;
  std::optional<std::string> input_strings_file_;
  std::optional<std::string> output_file_;
  bool trace_enabled_;
};

#endif  // PARSER_ARGS_PARSER_H_