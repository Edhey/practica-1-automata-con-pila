PdaData PdaParser::parse() {
  std::ifstream file(file_name_);
  if (!file.is_open()) {
    throw std::runtime_error("Error: No se pudo abrir el archivo " +
                             file_name_);
  }

  PdaData data;
  std::string line;
  int line_number = 0;

  try {
    // 1. Leer estados
    if (!readNonCommentLine(file, line)) {
      throw std::runtime_error("Error: Archivo vacío o sin estados");
    }
    line_number++;
    data.states = tokenize(line);
    if (data.states.empty()) {
      throw std::runtime_error("Error línea " + std::to_string(line_number) +
                               ": No se encontraron estados");
    }

    // 2. Leer alfabeto de entrada
    if (!readNonCommentLine(file, line)) {
      throw std::runtime_error("Error: Falta alfabeto de entrada");
    }
    line_number++;
    auto input_tokens = tokenize(line);
    for (const auto& token : input_tokens) {
      if (token.length() != 1) {
        throw std::runtime_error(
            "Error línea " + std::to_string(line_number) +
            ": Los símbolos del alfabeto deben ser de un carácter");
      }
      data.input_alphabet.push_back(token[0]);
    }

    // 3. Leer alfabeto de pila
    if (!readNonCommentLine(file, line)) {
      throw std::runtime_error("Error: Falta alfabeto de pila");
    }
    line_number++;
    auto stack_tokens = tokenize(line);
    for (const auto& token : stack_tokens) {
      if (token.length() != 1) {
        throw std::runtime_error(
            "Error línea " + std::to_string(line_number) +
            ": Los símbolos del alfabeto de pila deben ser de un carácter");
      }
      data.stack_alphabet.push_back(token[0]);
    }

    // 4. Leer estado inicial
    if (!readNonCommentLine(file, line)) {
      throw std::runtime_error("Error: Falta estado inicial");
    }
    line_number++;
    auto initial_tokens = tokenize(line);
    if (initial_tokens.size() != 1) {
      throw std::runtime_error("Error línea " + std::to_string(line_number) +
                               ": Debe haber exactamente un estado inicial");
    }
    data.initial_state = initial_tokens[0];

    // 5. Leer símbolo inicial de pila
    if (!readNonCommentLine(file, line)) {
      throw std::runtime_error("Error: Falta símbolo inicial de pila");
    }
    line_number++;
    auto initial_stack_tokens = tokenize(line);
    if (initial_stack_tokens.size() != 1 ||
        initial_stack_tokens[0].length() != 1) {
      throw std::runtime_error(
          "Error línea " + std::to_string(line_number) +
          ": Debe haber exactamente un símbolo inicial de pila");
    }
    data.initial_stack_symbol = initial_stack_tokens[0][0];

    // 6. Leer estados finales
    if (!readNonCommentLine(file, line)) {
      throw std::runtime_error("Error: Faltan estados finales");
    }
    line_number++;
    data.final_states = tokenize(line);
    if (data.final_states.empty()) {
      throw std::runtime_error("Error línea " + std::to_string(line_number) +
                               ": Debe haber al menos un estado final");
    }

    // 7. Leer transiciones
    while (readNonCommentLine(file, line)) {
      line_number++;
      auto tokens = tokenize(line);

      if (tokens.size() != 5) {
        throw std::runtime_error(
            "Error línea " + std::to_string(line_number) +
            ": Formato de transición incorrecto. " +
            "Formato esperado: estado_actual símbolo_entrada tope_pila "
            "estado_siguiente cadena_a_apilar");
      }

      PdaData::Transition transition;
      transition.current_state = tokens[0];
      transition.input_symbol = tokens[1].length() == 1 ? tokens[1][0] : '\0';
      transition.stack_top = tokens[2].length() == 1 ? tokens[2][0] : '\0';
      transition.next_state = tokens[3];
      transition.push_string = tokens[4];

      // Validar formato
      if (tokens[1].length() != 1) {
        throw std::runtime_error(
            "Error línea " + std::to_string(line_number) +
            ": El símbolo de entrada debe ser de un carácter");
      }
      if (tokens[2].length() != 1) {
        throw std::runtime_error("Error línea " + std::to_string(line_number) +
                                 ": El tope de pila debe ser de un carácter");
      }

      data.transitions.push_back(transition);
    }

  } catch (const std::exception& e) {
    file.close();
    throw;
  }

  file.close();
  return data;
}
