#include <string>

int check(std::string str, char c) {
    int len;
    int i;

    len = str.length() - 1;
    if (str.find(&c) == -1 && len > 0)
        return 1;
    for (i = 0; i < len; i++)
        if (str[i] != c)
            return -2;
    return 0;
}

int count_words(std::string str, char c) {
    int len;
    int count = 1;
    int i = 0;
    int j;

    if (check(str, c) != -2)
        return check(str, c);
    len = str.length() - 1;
    for (j = 0; str[j] == c; j++)
        i++;
    for (j = len; str[j] == c; j--)
        len--;
    for (; i < len; i++) {
        if (str[i] == c && str[i + 1] != c)
            count++;
    }
    return count;
}

std::string* strsplit(std::string str, char del, int *len) {
    int count = count_words(str, del);
    std::string* mas = new std::string [count];

    int current_char = 0;

    for (int i = 0; i < count; i++) {
        while (current_char < str.length() && str[current_char] == del)
            current_char++;
        while (current_char < str.length() && str[current_char] != del)
            mas[i].append(1, str[current_char++]);
    }
    *len = count;
    return mas;
}
