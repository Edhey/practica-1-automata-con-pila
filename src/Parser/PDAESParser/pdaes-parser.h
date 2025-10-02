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
 * @file state.h
 * @brief Definition of
 * @bug There are no known bugs
 * @see https://github.com/Edhey/practica-1-automata-con-pila.git
 * Revision history:
 */

#ifndef PARSER_PDAESPARSER_PDAES_PARSER_H_
#define PARSER_PDAESPARSER_PDAES_PARSER_H_

#include "../pda-parser.h"

class PdaESParser : public PdaParser {
public:
  explicit PdaESParser(const std::string& file_name) : PdaParser(file_name) {}
  std::expected<PdaData, ParseError> parse() override;
};

#endif  // PARSER_PDAESPARSER_PDAES_PARSER_H_