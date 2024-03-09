#include <iostream>

int main() {
  std::string template_1, template_2;
  std::cin >> template_1 >> template_2;
  uint16_t len_1 = template_1.size();
  uint16_t len_2 = template_2.size();
  uint16_t i_1 = 0;
  uint16_t i_2 = 0;
  uint16_t str_len = len_1 > len_2 ? len_1 : len_2;
  char* ans = new char[str_len];
  uint16_t ans_i = 0;
  uint16_t min_str_len = 0;
  while (i_1 < len_1 && i_2 < len_2) {
    // equal symbols
    if (template_1[i_1] == template_2[i_2] && template_2[i_2] != '*' && template_1 != '?') {
      ans[ans_i] = template_1[i_1];
      min_str_len++;
      i_1++;
      i_2++;
    }
    else if (template_1[i_1] == '?' && template_2[i_2] == '?') {
      ans[ans_i] = 'a';
      min_str_len++;
      i_1++;
      i_2++;
    }
    // ? and letter
    else if ((template_1[i_1] == '?' && template_2[i_2] != '*') ||
             (template_1[i_2] == '?' && template_2[i_1] != '*')) {
      min_str_len++;
      i_1++;
      i_2++;
    }
    // * in 1
    else if (template_1[i_1] == '*') {
      uint16_t temp_i_2 = i_2;
      while (template_2[temp_i_2 + 1] != template_1[i_1 + 1]) {
        min_str_len++;
        temp_i_2++;
      }
      i_2 = temp_i_2 + 1;
      i_1++
    }
    // * in 2
    else if (template_2[i_2] == '*') {
      uint16_t temp_i_1 = i_1;
      while (template_2[i_2 + 1] != template_1[temp_i_1 + 1]) {
        min_str_len++;
        temp_i_1++;
      }
      i_1 = temp_i_1 + 1;
      i_2++;
    }
  }
}