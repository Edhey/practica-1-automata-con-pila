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
  ArgsParser()
      : input_file(""),
        output_file(""),
        pda_type(PDAType::PDAES),
        trace_mode(false) {}
  static std::optional<ArgsParser> parse(int argc, char* argv[]);
  std::string getInputFile() const { return input_file; }
  std::string getOutputFile() const { return output_file; }
  PDAType getPDAType() const { return pda_type; }
  bool isTraceMode() const { return trace_mode; }

private:
  std::string input_file;
  std::string output_file;
  PDAType pda_type;
  bool trace_mode = false;
  static void printUsage(const char* program_name);
};

#endif  // ARGSPARSER_H_