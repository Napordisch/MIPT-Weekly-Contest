#include "cstring.h"

size_t Strlen(const char* str) {
  size_t len = 0;
  while (str[len] != '\0') {
    len++;
  }
  return len;
}

int Strcmp(const char* first, const char* second) {
  size_t shorter_str;
  size_t first_len = Strlen(first);
  size_t second_len = Strlen(second);
  if (first_len <= second_len) {
    shorter_str = first_len;
  } else {
    shorter_str = second_len;
  q}
  for (size_t i = 0; i < shorter_str; i++) {
    if (first[i] != second[i]) {
      return first[i] - second[i];
    }
  }
  return first_len - second_len;
}

int Strncmp(const char* first, const char* second, size_t count) {
  size_t shorter_str;
  size_t first_len = Strlen(first);
  size_t second_len = Strlen(second);

  if (first_len <= second_len) {
    shorter_str = first_len;
  } else {
    shorter_str = second_len;
  }

  for (size_t i = 0; i < count; i++) {
    if (i >= shorter_str) {
      return first_len - second_len;
    }
    if (first[i] != second[i]) {
      return first[i] - second[i];
    }
  }
  return 0;
}

char* (char* dest, const char* src, size_t count) {
  size_t src_len = Strlen(src);
  for (size_t i = 0; i < count; i++) {
    if (i <= src_len) {
      dest[i] = src[i];
    } else {
      dest[i] = '\0';
    }
  }
  return dest;
}

char* Strcpy(char* dest, const char* src) {
  size_t src_len = Strlen(src);
  for (size_t i = 0; i <= src_len; i++) {
    dest[i] = src[i];
  }
  return dest;
}

char* Strcat(char* dest, const char* src) {
  size_t dest_len = Strlen(dest);
  size_t src_len = Strlen(src);
  for (size_t i = 0; i <= src_len; i++) {
    dest[dest_len + i] = src[i];
  }
  return dest;
}

const char* Strchr(const char* str, char symbol) {
  size_t str_len = Strlen(str);
  for (size_t i = 0; i <= str_len; i++) {
    if (str[i] == symbol) {
      return &str[i];
    }
  }
  return nullptr;
}

const char* Strrchr(const char* str, char symbol) {
  size_t str_len = Strlen(str);
  const char* wanted = nullptr;
  for (size_t i = 0; i <= str_len; i++) {
    if (str[i] == symbol) {
      wanted = &str[i];
    }
  }
  return wanted;
}

char* Strncat(char* dest, const char* src, size_t count) {
  size_t dest_len = Strlen(dest);
  if (Strlen(src) < count) {
    return Strcat(dest, src);
  }
  for (size_t i = 0; i < count; i++) {
    dest[dest_len + i] = src[i];
  }
  dest[dest_len + count] = '\0';
  return dest;
}

size_t Strspn(const char* dest, const char* src) {
  size_t dest_len = Strlen(dest);
  size_t src_len = Strlen(src);
  size_t found = 0;
  for (size_t i = 0; i < dest_len; i++) {
    bool current_found = false;
    for (size_t j = 0; j < src_len; j++) {
      if (dest[i] == src[j]) {
        current_found = true;
        found++;
        break;
      }
    }
    if (!current_found) {
      break;
    }
  }
  return found;
}

size_t Strcspn(const char* dest, const char* src) {
  size_t dest_len = Strlen(dest);
  size_t src_len = Strlen(src);
  size_t not_found = 0;
  for (size_t i = 0; i < dest_len; i++) {
    bool current_not_found = true;
    for (size_t j = 0; j < src_len; j++) {
      if (dest[i] == src[j]) {
        current_not_found = false;
        break;
      }
    }
    if (!current_not_found) {
      break;
    }
    not_found++;
  }
  return not_found;
}

const char* Strpbrk(const char* dest, const char* breakset) {
  size_t dest_len = Strlen(dest);
  size_t breakset_len = Strlen(breakset);
  for (size_t i = 0; i < dest_len; i++) {
    for (size_t j = 0; j < breakset_len; j++) {
      if (dest[i] == breakset[j]) {
        return &dest[i];
      }
    }
  }
  return nullptr;
}

const char* Strstr(const char* str, const char* pattern) {
  size_t str_len = Strlen(str);
  size_t pattern_len = Strlen(pattern);
  if (pattern_len == 0) {
    return &str[0];
  }
  for (size_t i = 0; i <= str_len; i++) {
    if (pattern[0] == str[i]) {
      size_t d = i;
      for (size_t j = 0; j < pattern_len; j++) {
        if (pattern[j] != str[j + d]) {
          break;
        }
        if (j == pattern_len - 1) {
          return &str[i];
        }
      }
    }
  }
  return nullptr;
}
