#ifndef APT_ASSIGNMENT_1_VALIDATION_H
#define APT_ASSIGNMENT_1_VALIDATION_H

void remove_whitespace(std::string &string);

bool has_more_than_two_columns(const std::string &string);

bool has_characters(const std::string &string);

bool has_special_characters(const std::string &string);

bool column_data_is_correct(const std::string &string);

bool cli_input_is_correct(int argc, char *argv[]);

#endif //APT_ASSIGNMENT_1_VALIDATION_H
